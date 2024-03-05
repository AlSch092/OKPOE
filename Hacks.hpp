#pragma once
#include <Windows.h>

struct HACK {
	UINT64 dwAddress;
	char* szOriginalBytes;
	char* szNewBytes;
	INT nSize;
};

VOID WriteHackBytes(HACK hHack, BOOL bEnable);
VOID ReduceRAM();

namespace Hacks
{
	struct HACK {
		UINT64 dwAddress;
		char* szOriginalBytes;
		char* szNewBytes;
		INT nSize;
	};

	VOID Write(HACK hHack, BOOL bEnable);
	BOOL Write(UINT64 dwAddress, byte* szOriginalBytes, byte* szNewBytes, INT nSize, BOOL bEnable);

	VOID ReduceRAM();
}

