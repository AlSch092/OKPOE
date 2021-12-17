#pragma once
#include "Entity.hpp"

namespace Base 
{
	const UINT64 InternalPtrOffset = 0x10;
	const UINT64 IsCorruptedOffset = 0xD8;
	const UINT64 IsShaperOffset = 0xD9;
	const UINT64 IsElderOffset = 0xDA;

	//internal struct
	const UINT64 sizeOffset = 0x10;
	const UINT64 BaseNameOffset = 0x18;
	const UINT64 LevelReqOffset = 0x38;

	std::wstring GetBaseName(Entity* e);
	bool IsElder(Entity* e);
	bool IsShaper(Entity* e);
	bool IsCorrupted(Entity* e);
}
