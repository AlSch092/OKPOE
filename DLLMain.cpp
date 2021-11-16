#include "NetLogger.hpp"

extern int Main();
extern NetLogger* prot;

UINT64 g_POEBase;

VOID InitializeGUI()
{
  g_POEBase; = (UINT64)GetModuleHandle(NULL); //dont need to explicitly use module name.
	
	prot = new NetLogger();

	int LatestVer = AutoUpdate::CheckForUpdates("0.6.0");

	prot->HelloApproved  = prot->SendHWID("<ip to server>"); //todo: find way to get rid of the str in static mem for analysis

	if (prot->HelloApproved)
	{
		if (prot->TransactHeartbeat("<ip to server>"))
		{
			Main();
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		AllocConsole();
		freopen("CON", "w", stdout);
		freopen("CON", "r", stdin);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&InitializeGUI, 0, 0, 0);
	}break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
