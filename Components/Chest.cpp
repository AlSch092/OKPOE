#include "Chest.hpp"

bool Chest::IsOpened(Entity* e)
{
	byte isOpened;
	UINT64 ChestComponentAddr = e->GetComponentAddress("Chest");

	if (ChestComponentAddr == 0)
	{
		return (bool)-1;
	}

	isOpened = *(byte*)(ChestComponentAddr + Chest::IsOpenedOffset);
	return isOpened;
}

bool Chest::IsLocked(Entity* e)
{
	byte isLocked;
	UINT64 ChestComponentAddr = e->GetComponentAddress("Chest");

	if (ChestComponentAddr == 0)
	{
		return (bool)-1;
	}

	isLocked = *(byte*)(ChestComponentAddr + Chest::IsLockedOffset);
	return isLocked;
}

bool Chest::IsStrongbox(Entity* e)
{
	byte isStrongbox;
	UINT64 ChestComponentAddr = e->GetComponentAddress("Chest");

	if (ChestComponentAddr == 0)
	{
		return (bool)-1;
	}

	isStrongbox = *(byte*)(ChestComponentAddr + Chest::IsStrongboxOffset);
	return isStrongbox;
}

byte Chest::GetQuality(Entity* e)
{
	byte quality;
	UINT64 ChestComponentAddr = e->GetComponentAddress("Chest");

	if (ChestComponentAddr == 0)
	{
		return (bool)-1;
	}

	quality = *(byte*)(ChestComponentAddr + Chest::QualityOffset);
	return quality;

}