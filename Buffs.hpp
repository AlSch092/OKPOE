#pragma once
#include <windows.h>
#include "Pointer.hpp"
#include <string>

namespace Buffs
{
	namespace Offsets
	{
		const UINT64 DetailsPtr = 0x08;
		
		const UINT64 InternalName = 0x00; //from above offset
		const UINT64 InternalDescription = 0x08;
	}

	std::wstring description(UINT64 RemoteAddr) { //try to get this working for gud code
//		return ReadPointer<std::wstring>(RemoteAddr + InternalObjOffset, InternalDescriptionOffset);
		return L"";
	}
}

