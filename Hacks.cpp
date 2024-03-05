#pragma once
#include "Hacks.hpp"
#include <Psapi.h>
#include <TlHelp32.h>

HANDLE ReduceRAMThread;

VOID WriteHackBytes(HACK hHack, BOOL bEnable) {
	if (bEnable) {
		DWORD dwOldProt;
		VirtualProtect((void*)hHack.dwAddress, hHack.nSize, PAGE_EXECUTE_READWRITE, &dwOldProt);
		memcpy((void*)hHack.dwAddress, (void*)hHack.szNewBytes, hHack.nSize);
	}
	else {
		memcpy((void*)hHack.dwAddress, (void*)hHack.szOriginalBytes, hHack.nSize);
	}
}

VOID ReduceRAM()
{
	while (1)
	{
		EmptyWorkingSet(GetCurrentProcess());
		Sleep(15000);
	}
}

void SetTransparent(HWND window)
{
	SetWindowLong(window, GWL_STYLE, WS_VISIBLE);
	SetWindowLong(window, GWL_EXSTYLE, (WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST));
}

void DisableTransparent(HWND window)
{
	SetWindowLong(window, GWL_STYLE, (WS_VISIBLE));
	SetWindowLong(window, GWL_EXSTYLE, (WS_EX_LAYERED | WS_EX_TOPMOST));
}

BOOL Hacks::Write(UINT64 dwAddress, byte* szOriginalBytes, byte* szNewBytes, INT nSize, BOOL bEnable)
{
	if (bEnable) {

		DWORD dwOldProt;

		if (!VirtualProtect((void*)dwAddress, nSize, PAGE_EXECUTE_READWRITE, &dwOldProt))
		{
			return false;
		}
		else
		{
			memcpy((void*)dwAddress, (void*)szNewBytes, nSize);
		}
		

	}
	else {
		memcpy((void*)dwAddress, (void*)szOriginalBytes, nSize);
	}

	return true;
}