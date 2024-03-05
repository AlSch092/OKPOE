#pragma once
#include "Entity.hpp"

using namespace std;

namespace Mods
{
	enum ItemRarities
	{
		Normal = 0,
		Magic,
		Rare,
		Unique,
		Gem,
		Currency,
		Quest,
		Prophecy
	};

	struct ItemMod
	{
		string DisplayName;
		string Group; //?
		int Level;
		string PrettiedName;
		string Name;
		int Values[4]; 
	};

	const int ItemModStructSize = 0x38;
	const int ItemNameOffset = 0x04;
	const int ItemNameStructSize = 0x10;
	const int StatStructSize = 0x20;

	namespace Offsets
	{
		const UINT64 UniqueName = 0x38;
		const UINT64 IsIdentified = 0xA8; //use this in scriping func to skip items not needed
		const UINT64 Rarity = 0xAC;

		const UINT64 ImplicitMods = 0xB8;
		const UINT64 ExplicitMods = 0xD0;
		const UINT64 EnchantMods = 0xE8;

		const UINT64 ItemLevel = 0x220; 
		const UINT64 RequiredLevel = ItemLevel + 4;
		const UINT64 PtrToIncubatorObject = 0x228;
		const UINT64 IncubatorKillCount = 0x238;
		const UINT64 IsMirrored = 0x23D;
		const UINT64 IsSplit = 0x23E;
		const UINT64 IsUsable = 0x23F;
		const UINT64 IsSynthesized = 0x241;
	}

	namespace ExtendedInfo
	{
		namespace Offsets
		{
			const UINT64 ImplicitStatsArray = 0x08;
			const UINT64 EnchantedStatsArray = 0x48;
			const UINT64 ScourgeStatsArray = 0x88;
			const UINT64 ExplicitStatsArray = 0xC8;
			const UINT64 CraftedStatsArray = 0x108;
			const UINT64 FracturedStatsArray = 0x148;
		}
	}

	bool IsIdentified(Entity* e);
	bool IsMirrored(Entity* e);
	bool IsSynthesized(Entity* e);

	ItemRarities GetItemRarity(Entity* e);
	int GetItemLevel(Entity* e);
	int GetRequiredLevel(Entity* e);

	std::wstring GetUniqueName(Entity* e);
}