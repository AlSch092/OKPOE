#pragma once
#include <windows.h>
#include "Pointer.hpp"
#include <string>

namespace Buffs
{
	const UINT64 InternalObjOffset = 0x08;
	const UINT64 InternalNameOffset = 0x00; //from above offset
	const UINT64 InternalDescriptionOffset = 0x08;

	const UINT64 DurationOffset = 0x18;
	const UINT64 TimerOffset = 0x18;
	const UINT64 ChargesOffset = 0x18;

	std::wstring description(UINT64 RemoteAddr) { //try to get this working for gud code
//		return ReadPointer<std::wstring>(RemoteAddr + InternalObjOffset, InternalDescriptionOffset);
		return L"";
	}
}

