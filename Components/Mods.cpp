#include "Mods.hpp"

bool Mods::IsIdentified(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Mods");
	bool isIded = false;

	if (CompAddr > NULL)
	{
		isIded = DereferenceSafe<bool>(CompAddr + Mods::isIdentifiedOffset);
	}

	return isIded;
}

bool Mods::IsMirrored(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Mods");
	bool mirrored = false;

	if (CompAddr > NULL)
	{
		mirrored = DereferenceSafe<bool>(CompAddr + Mods::isMirroredOffset);
	}

	return mirrored;
}

bool Mods::IsSynthesized(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Mods");
	bool synthesized = false;

	if (CompAddr > NULL)
	{
		synthesized = DereferenceSafe<bool>(CompAddr + Mods::isSynthesizedOffset);
	}

	return synthesized;
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

std::wstring Mods::GetUniqueName(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Mods");

	std::wstring fullName;

	if (CompAddr != NULL)
	{
		CompAddr = CompAddr + Mods::uniqueNameOffset;

		if (CompAddr != NULL)
		{
			UINT64 PtrListArray = DereferenceSafe<UINT64>(CompAddr);
			UINT64 PtrEndArray = DereferenceSafe<UINT64>(CompAddr + 8);		
			UINT64 Current = PtrListArray;
			int count = 0;

			while (Current <= PtrEndArray)
			{
				UINT64 NameRecord = DereferenceSafe<UINT64>(PtrListArray + (count * 0x10));
				UINT32 NameRecordCounter = DereferenceSafe<UINT32>(NameRecord);

				if (NameRecordCounter >= 1 && NameRecordCounter <= 10)
				{
					UINT64 NameAddr = DereferenceSafe<UINT64>(NameRecord + 4);

					if (NameAddr != NULL)
					{
						if (NameRecordCounter == 1)
						{
							fullName = std::wstring((const wchar_t*)NameAddr);
						}
						else
						{
							fullName = fullName + (const wchar_t*)NameAddr;
						}
					}
				}

				Current += 0x10;
				count += 1;
			}
		}

	}

	return fullName;
}
