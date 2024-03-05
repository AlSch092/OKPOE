/*
OKPOE - by alsch092
PLEASE DO NOT DISTRIBUTE!
*/

#include "NetLogger.hpp"
#include "AntiDebug.hpp"
#include "AutoLogin.hpp"
#include "MultiClient.hpp"
#include "Declarations.hpp"

extern int Main();
extern NetLogger* g_ProtectionServer;

HMODULE g_OurModule = 0;
HANDLE g_DebugThread = 0;
DWORD dwDebugThreadId = 0;

VOID CheckAutoLoginParameters()
{
	AutoLogin* loginHelper = new AutoLogin();

	if (loginHelper->ParseCommandLine())
	{
		printf("Software was launched with autologin parameters...\n");
	}
	else
	{
		printf("No command line could be parsed.\n");
	}
}

VOID InitializeGUI()
{
	UINT64 g_POEBase = (UINT64)GetModuleHandleA("PathOfExile.exe");
	
	//if (!g_POEBase)
	//	__fastfail(-1);

	g_ProtectionServer = new NetLogger();
	g_ProtectionServer->HelloApproved = g_ProtectionServer->SendHWID(); //todo: find way to get rid of the str in static mem for analysis

	if (g_ProtectionServer->HelloApproved)
	{
		if (g_ProtectionServer->TransactHeartbeat())
		{
			//CheckAutoLoginParameters();

			AllocConsole();
			freopen("CON", "w", stdout);
			freopen("CON", "r", stdin);

			g_OurModule = GetModuleHandleA("GoPoE.dll");
			Main();
		}
		else
		{
			if (FreeLibrary(GetModuleHandleA("GoPoE.dll")))		
				ExitProcess(0);		
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		g_OurModule = hModule;
		//g_DebugThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)AntiDebug::LoopDebugChecks, 0, 0, &dwDebugThreadId);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&InitializeGUI, 0, 0, 0);
	}break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}