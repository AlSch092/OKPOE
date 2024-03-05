#pragma once
#include "Entity.hpp"

namespace Base 
{
	namespace Offsets
	{
		const UINT64 FurtherDetailsPtr = 0x10;

		const UINT64 PublicPrice = 0x60;

		const UINT64 Influence = 0xC6;
		const UINT64 IsCorrupted = 0xC7;
		const UINT64 IsShaper = 0xD9; //might need updating
		const UINT64 IsElder = 0xDA;

		const UINT64 BaseName = 0x30;
		const UINT64 LevelRequisite = 0x38; //update this

		const UINT64 ItemDescription = 0x78;
		const UINT64 PtrEntityPath = 0x80; //offset 0 from this will get you back to Metadata/...
		const UINT64 ItemType = 0x88; //offset 0 from this, you'll get a string like "StackableCurrency"
		const UINT64 BaseItemTypesPtr = 0x90;
		const UINT64 XBoxControllerDescription = 0x98;
	}
	

	std::wstring GetBaseName(Entity* e);
	bool IsElder(Entity* e);
	bool IsShaper(Entity* e);
	bool IsCorrupted(Entity* e);

	std::wstring GetPublicPrice(Entity* e);
}