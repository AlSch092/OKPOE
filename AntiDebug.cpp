#include "AntiDebug.hpp"

extern NetLogger* g_ProtectionServer;

void AntiDebug::LoopDebugChecks()
{
	bool looping = true;

	while (looping)
	{
		if (IsDebuggerPresent_1() || IsDebuggerPresent_2() || IsDebuggerPresent_3())
		{
			g_ProtectionServer->SendData("Debugger=1");
			ExitProcess(0);
		}

		Sleep(500);
	}
}

bool AntiDebug::IsDebuggerPresent_1() //closehandle
{
	__try
	{
		CloseHandle(NULL);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return true;
	}

	return false;
}

bool AntiDebug::IsDebuggerPresent_2() //winapi
{
	if (IsDebuggerPresent())
	{
		printf("IsDebuggerPresent = true?\n");
		return true;
	}

	BOOL pDebugger = false;

	if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &pDebugger))
	{
		if (pDebugger)
		{
			printf("CheckRemoteDebuggerPresent = true?\n");
			return true;
		}

	}

	return false;
}

bool AntiDebug::IsDebuggerPresent_3()
{
	if (GetModuleHandleW(L"vehdebug-x86_64.dll") != NULL)
		return true;

	return false;
}

