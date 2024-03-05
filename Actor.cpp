#include "Actor.hpp"

Actor::ActionIDs Actor::GetCurrentActionID(Entity* e)
{
	Actor::ActionIDs Action = ACTION_UNKNOWN;
	UINT64 ActorCompAddr = e->GetComponentAddress("Actor");

	if (ActorCompAddr == NULL)
	{
		printf("Could not get actor component addr at GetCurrentActionID(Ent* e)\n");
		return (ActionIDs)0;
	}
	
	byte bAction = DereferenceSafe<byte>(ActorCompAddr + Actor::Offsets::ActionId);
	return (ActionIDs)bAction;
}

int Actor::GetActionCount(Entity* e)
{
	UINT64 ActorCompAddr = e->GetComponentAddress(std::string("Actor"));
	int Count = 0;

	if (ActorCompAddr == NULL)
	{
		return 0;
	}

	Count = DereferenceSafe<UINT>(ActorCompAddr + Actor::Offsets::ActionCount);

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

std::list<Entity*> GetMinions(Entity* e)
{
	std::list<Entity*> Minions;

	UINT64 ActorCompAddr = e->GetComponentAddress("Actor");
	int Count = 0;

	if (ActorCompAddr == NULL)
	{
		return Minions;
	}

	UINT64 Address = DereferenceSafe<UINT64>(ActorCompAddr + Actor::Offsets::HasMinionArrayOffset);
	printf("Address: %llX\n", Address);

	return Minions;
}

std::list<Actor::ActorSkill*> Actor::GetSkillList(Entity* e)
{
	printf("Getting skills list...\n");

	std::list<ActorSkill*> Skills;

	UINT64 ActorCompAddr = e->GetComponentAddress("Actor");
	int Count = 0;

	if (ActorCompAddr == NULL)
	{
		printf("[ERROR] Could not get actor skills at GetSkillList!\n");
		return Skills;
	}

	UINT64 ArrayStart = DereferenceSafe<UINT64>(ActorCompAddr + Actor::Offsets::Skills);
	UINT64 ArrayEnd = DereferenceSafe<UINT64>(ActorCompAddr + Actor::Offsets::Skills + 8);
	UINT64 ArrayCurrent = ArrayStart + 8;

	printf("Skill list size: %lld\n", (ArrayEnd - ArrayStart) / 16);
	
	while (ArrayCurrent < ArrayEnd)
	{
		UINT64 SkillStruct = DereferenceSafe<UINT64>(ArrayCurrent);

		if (SkillStruct != NULL)
		{
			ActorSkill* skill = new ActorSkill();

			printf("Skill struct at: %llx\n", SkillStruct);
			skill->Id = DereferenceSafe<UINT16>(SkillStruct + Actor::SkillOffsets::Id);
			skill->KeyDown = DereferenceSafe<int>(SkillStruct + Actor::SkillOffsets::KeyDown);
			skill->CanBeUsedWithWeapon = DereferenceSafe<bool>(SkillStruct + Actor::SkillOffsets::CanBeUsedWithWeapon); //0x50
			skill->CanBeUsed = DereferenceSafe<bool>(SkillStruct + Actor::SkillOffsets::CanBeUsed); //0x51
			skill->TotalUses = DereferenceSafe<int>(SkillStruct + Actor::SkillOffsets::TotalUses); //0x54
			skill->Cooldown = DereferenceSafe<int>(SkillStruct + Actor::SkillOffsets::Cooldown); //0x5c
			skill->SoulsPerUse = DereferenceSafe<int>(SkillStruct + Actor::SkillOffsets::SoulsPerUse); //0x6c
			skill->TotalVaalUses = DereferenceSafe<int>(SkillStruct + Actor::SkillOffsets::MaxVaalUses); //0x70	
			skill->IsCastedOnSelf = DereferenceSafe<bool>(SkillStruct + Actor::SkillOffsets::IsCastedOnSelf); //0x58

			if (skill->TotalVaalUses > 0)
				skill->isVaal = true;

			printf("Actor Skill: %x\n", skill->Id);
			printf("Cooldown: %d\n", skill->Cooldown);
			printf("Can be used: %d\n", (skill->CanBeUsed == 0 ? skill->CanBeUsed : 0)); //should evaluate to 1
			printf("Can be used (weapon): %d\n", skill->CanBeUsedWithWeapon);
			printf("Total Uses: %d\n", skill->TotalUses);
			printf("Souls per use: %d\n", skill->SoulsPerUse);
			printf("Total Vaal uses: %d\n", skill->TotalVaalUses);
			printf("Is casted on self: %d\n", skill->IsCastedOnSelf);

			if (skill->TotalVaalUses >= 1)
				skill->isVaal = true;

			printf("Is Vaal skill: %d\n", skill->isVaal);
			printf("------------------------\n");

			Skills.push_back(skill);
		}

		ArrayCurrent += 16;
	}


	return Skills;
}