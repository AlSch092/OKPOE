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

wchar_t* Mods::GetUniqueName(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Mods");
	wchar_t NamePtr[100] = { 0 };

	if (CompAddr != NULL)
	{
		CompAddr = CompAddr + Mods::uniqueNameOffset;

		if (CompAddr != NULL)
		{
			int Count = 0;
			UINT64 PtrListArray = DereferenceSafe<UINT64>(CompAddr);
			UINT64 PtrEndArray = DereferenceSafe<UINT64>(CompAddr + 8);

			UINT64 FirstNameRecord = DereferenceSafe<UINT64>(PtrListArray);
			UINT64 Current = FirstNameRecord;

			printf("PtrListArray: %llX\n", PtrListArray);
			printf("PtrEndArray: %llX\n", PtrEndArray);
			printf("Current: %llX\n", Current);

			while (Current < PtrEndArray)
			{
				int NameRecordCounter = DereferenceSafe<int>(Current);
				UINT64 NameAddr = DereferenceSafe<UINT64>(Current + 4);
				
				printf("Count: %d, NameAddr %llX\n", NameRecordCounter, NameAddr);

				if (NameAddr != NULL)
				{
					if (Count == 1)
					{
						wcscpy(NamePtr, (const wchar_t*) NameAddr);
					}
					else
					{
						wcscat(NamePtr, (const wchar_t*)NameAddr);
					}
				}

				Current += 0x10;
			}
		}

	}

	return NamePtr;
}
