#pragma once
#include "Entity.hpp"

namespace Mods
{
	enum Rarities
	{
		Normal = 0,
		Magic,
		Rare,
		Unique
	};

	const UINT64 uniqueNameOffset = 0x30;
	const UINT64 isIdentifiedOffset = 0xA8;
	const UINT64 rarityOffset = 0xAC;
	const UINT64 implicitModsOffset = 0xB8;
	const UINT64 explicitModsOffset = 0xD0;
	const UINT64 enchantModsOffset = 0xE8;

	const UINT64 implicitStatsOffset = 0x1C0;
	const UINT64 enchantStatsOffset = 0x1D8;
	const UINT64 explicitStatsOffset = 0x1F0;
	const UINT64 craftedStatsOffset = 0x208;
	const UINT64 fracturedStatsOffset = 0x220;

	const UINT64 itemLevelOffset = 0x7C8;
	const UINT64 requiredLevelOffset = itemLevelOffset + 4;
	const UINT64 isMirroredOffset = requiredLevelOffset;
	const UINT64 isSynthesizedOffset = isMirroredOffset + 0x18;

	bool IsIdentified(Entity* e);
	bool IsMirrored(Entity* e);
	bool IsSynthesized(Entity* e);

	Rarities GetItemRarity(Entity* e);
	int GetItemLevel(Entity* e);
	int GetRequiredLevel(Entity* e);
}