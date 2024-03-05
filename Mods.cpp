#include "Mods.hpp"




bool Mods::IsIdentified(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Mods");
	bool isIded = false;

	if (CompAddr > NULL)
	{
		isIded = DereferenceSafe<bool>(CompAddr + Mods::Offsets::IsIdentified);
	}

	return isIded;
}

bool Mods::IsMirrored(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Mods");
	bool mirrored = false;

	if (CompAddr > NULL)
	{
		mirrored = DereferenceSafe<bool>(CompAddr + Mods::Offsets::IsMirrored);
	}

	return mirrored;
}

bool Mods::IsSynthesized(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Mods");
	bool synthesized = false;

	if (CompAddr > NULL)
	{
		synthesized = DereferenceSafe<bool>(CompAddr + Mods::Offsets::IsSynthesized);
	}

	return synthesized;
}

Mods::ItemRarities Mods::GetItemRarity(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Mods");
	int Rarity = 0;

	if (CompAddr != NULL)
	{
		CompAddr = CompAddr + Mods::Offsets::Rarity;
		Rarity = DereferenceSafe<int>(CompAddr);
		return (ItemRarities)Rarity;
	}

	return ItemRarities::Normal;
}

int Mods::GetItemLevel(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Mods");
	int ItemLevel = 0;

	if (CompAddr != NULL)
	{
		CompAddr = CompAddr + Mods::Offsets::ItemLevel;
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
		CompAddr = CompAddr + Mods::Offsets::RequiredLevel;
		requiredLevel = DereferenceSafe<int>(CompAddr);
	}

	return requiredLevel;
}

std::wstring Mods::GetUniqueName(Entity* e) //broken.... too stupid to update it properly
{
	return L"";
	UINT64 CompAddr = e->GetComponentAddress("Mods");

	std::wstring fullName;

	if (CompAddr != NULL)
	{
		CompAddr = CompAddr + Mods::Offsets::UniqueName;

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
					printf("NameAddr: %llX\n", NameAddr);

					if (NameAddr != NULL && NameAddr > 0x0000010000000000 && NameAddr != 0xFFFFFFFFFFFFFFFF)
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