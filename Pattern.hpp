#pragma once
#include <Windows.h>


namespace Pattern
{
	BOOL Check(const BYTE* pData, const BYTE* bMask, const char* szMask);
	DWORD FindPattern(const BYTE *bMask, const char* szMask, DWORD dwOffset, DWORD dwStartAddress);

	namespace Signature
	{
		CONST BYTE SendPacketPattern[] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x10, 0x53, 0x33, 0xDB, 0x89, 0x4D, 0xF0 };
		//const uint32_t LogSendPacket = FindPattern(LogSendPacketPattern, "xxxxxxx????xxxxxx", 0, 0x00400000);
	}
}


