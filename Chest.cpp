#include "Chest.hpp"

bool Chest::IsOpened(Entity* e)
{
	byte isOpened = false;

	UINT64 ChestComponentAddr = e->GetComponentAddress("Chest");

	if (ChestComponentAddr == 0)
	{
		return (bool)-1;
	}

	isOpened = DereferenceSafe<byte>(ChestComponentAddr + Chest::Offsets::IsOpened);
	return isOpened;
}

bool Chest::IsLocked(Entity* e)
{
	byte isLocked;
	UINT64 ChestComponentAddr = e->GetComponentAddress("Chest");

	if (ChestComponentAddr == 0)
	{
		return false;
	}

	isLocked = DereferenceSafe<byte>(ChestComponentAddr + Chest::Offsets::IsLocked);
	return isLocked;
}

byte Chest::GetQuality(Entity* e)
{
	byte quality;
	UINT64 ChestComponentAddr = e->GetComponentAddress("Chest");

	if (ChestComponentAddr == 0)
	{
		return (bool)-1;
	}

	quality = DereferenceSafe<byte>(ChestComponentAddr + Chest::Offsets::Quality);
	return quality;

}


bool Chest::IsStrongbox(Entity* e)
{
	byte isStrongbox;
	UINT64 ChestComponentAddr = e->GetComponentAddress("Chest");

	if (ChestComponentAddr == 0)
	{
		return (bool)-1;
	}

	isStrongbox = DereferenceSafe<byte>(ChestComponentAddr + Chest::Offsets::IsStrongbox);
	return isStrongbox;
}


