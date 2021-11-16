#include "Targetable.hpp"

bool Targetable::IsTargetable(Entity* e)
{
	byte targetable = false;
	UINT64 TargetableAddr = e->GetComponentAddress("Targetable");

	if (TargetableAddr == 0)
	{
		return false;
	}

	targetable = *(byte*)(TargetableAddr + Targetable::TargetableOffset);

	return targetable;
}

bool Targetable::IsMouseOverEntity(Entity* e)
{
	byte hovering = false;
	UINT64 TargetableAddr = e->GetComponentAddress("Targetable");

	if (TargetableAddr == 0)
	{
		return false;
	}

	hovering = *(byte*)(TargetableAddr + Targetable::HoveringOffset);

	return hovering;
}