#include "WorldItem.hpp"
#include "Positioned.hpp"

Entity* WorldItem::GetEntityFromWorldItem(UINT64 ComponentAddr)
{
	if (ComponentAddr == 0)
		return NULL;
	
	UINT64 EntityAddr = DereferenceSafe<UINT64>(ComponentAddr + WorldItem::ItemOffset);

	Entity* e = new Entity(EntityAddr);

	//we now have a normal entity and can query its position, etc
	if (e == NULL)
		return NULL;

	return e;
}

Vector2 WorldItem::GetItemPosition(UINT64 ComponentAddr)
{
	if (ComponentAddr == 0)
	{
		return{ -1, -1 };
	}

	UINT64 EntityAddr = ComponentAddr + WorldItem::ItemOffset;

	Entity* e = new Entity(EntityAddr);

	if (e->ComponentListAddress != 0)
	{
		Vector2 Pos = Positioned::GetGridPosition(e);
		if (Pos.X != 0 && Pos.Y != 0)
			return Pos;

	}

	return { 0, 0 };
}