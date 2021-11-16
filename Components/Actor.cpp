#include "Actor.hpp"

Actor::ActionIDs Actor::GetCurrentActionID(Entity* e)
{
	Actor::ActionIDs Action = ACTION_UNKNOWN;
	UINT64 ActorCompAddr = e->GetComponentAddress("Actor");

	if (ActorCompAddr == 0)
	{
		printf("Could not get actor component addr at GetCurrentActionID(Ent* e)\n");
		return (ActionIDs)-1;
	}

	printf("[DEBUG] Actor comp: %llX\n", ActorCompAddr);
	
	byte bAction = DereferenceSafe<byte>(ActorCompAddr + Actor::ActionIdOffset);

	return (ActionIDs)bAction;
}

int Actor::GetActionCount(Entity* e)
{
	UINT64 ActorCompAddr = e->GetComponentAddress("Actor");
	int Count = 0;

	if (ActorCompAddr == 0)
	{
		return 0;
	}

	Count = DereferenceSafe<UINT>(ActorCompAddr + Actor::ActionOffset);

	return Count;
}

bool Actor::IsMoving(Entity* e)
{
	//if action ID == 0x80
	if (GetCurrentActionID(e) == ActionIDs::ACTION_MOVING)
		return true;

	return false;
}

bool Actor::IsAttacking(Entity* e)
{
	//if action ID == 0x80
	if (GetCurrentActionID(e) == ActionIDs::ACTION_MOVING)
		return true;

	return false;
}