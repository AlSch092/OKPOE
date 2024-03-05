#include "Targetable.hpp"

bool Targetable::IsTargetable(Entity* e)
{
	byte targetable = false;
	UINT64 TargetableAddr = e->GetComponentAddress("Targetable");

	if (TargetableAddr == 0)
	{
		printf("Could not get Targetable component..\n");
		return false;
	}

	targetable = DereferenceSafe<byte>(TargetableAddr + Targetable::TargetableOffset);
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

	hovering = DereferenceSafe<byte>(TargetableAddr + Targetable::HoveringOffset);
	return hovering;
}