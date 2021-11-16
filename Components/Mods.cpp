#include "Mods.hpp"

bool Mods::IsIdentified(Entity* e)
{
	return false;
}

bool Mods::IsMirrored(Entity* e)
{
	return false;
}

bool Mods::IsSynthesized(Entity* e)
{
	return false;
}

Mods::Rarities Mods::GetItemRarity(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Mods");
	int Rarity = 0;

	if (CompAddr != NULL)
	{
		CompAddr = CompAddr + Mods::rarityOffset;
		Rarity = DereferenceSafe<int>(CompAddr);
	}

	return Rarities::Normal;
}

int Mods::GetItemLevel(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Mods");
	int ItemLevel = 0;

	if (CompAddr != NULL)
	{
		CompAddr = CompAddr + Mods::itemLevelOffset;
	    ItemLevel = DereferenceSafe<int>(CompAddr);
	}

	return ItemLevel;
}

int Mods::GetRequiredLevel(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Mods");
	int requiredLevel = 0;

	if (CompAddr != NULL)
	{
		CompAddr = CompAddr + Mods::requiredLevelOffset;
		requiredLevel = DereferenceSafe<int>(CompAddr);
	}

	return requiredLevel;
}