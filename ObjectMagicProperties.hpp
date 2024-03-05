#pragma once
#include <Windows.h>

namespace ObjectMagicProperties
{
	static const char* rarity_names[] = { "Normal", "Magic", "Rare", "Unique" };

	static const UINT64 uniqueNameOffset = 0x20;
	static const UINT64 rarityOffset = 0x9C;
	static const UINT64 modsOffset = 0xB8;
	static const UINT64 statsOffset = 0x1E0;

}

//std::vector<Modifier> mods;
//std::vector<wstring> stats;