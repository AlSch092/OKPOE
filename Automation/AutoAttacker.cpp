#include "AutoAttacker.hpp"
#include "AutoPlayer.hpp"

extern AutoPlayer* Robot;

AutoAttacker::AutoAttacker()
{
	this->IsBusy = false;
	this->IsHunting = false;
	this->IsFightingBoss = false;
	this->MovementSkill = Input::InputIds::RUN;
	this->UsingRandomSkills = false;

	//int skillsAdded = FillActorSkillList();
}

void AutoAttacker::CastRandomSkill(Entity* e)
{
	if (this->ActorSkills.size() == 0)
	{
		FillActorSkillList();
	}

	for each(Actor::ActorSkill* skill in this->ActorSkills)
	{
		if (skill->CanBeUsedWithWeapon)
		{
			if (!skill->isVaal && !skill->IsCastedOnSelf) //non-vaal skill
			{
				if (skill->Id >= 0x8001 && skill->Id <= 0xF001)
				{
					Robot->Attacker->IsAttacking = true;
					Sleep(150);
					Robot->Interaction(e->GetUniqueID(), skill->Id);
					Sleep(Robot->AttackDelay);
					Robot->Attacker->IsAttacking = false;
				}
			}

		}
	}
}

void AutoAttacker::UseVaalSkill(Entity* e)
{


}

void AutoAttacker::HandleRighteousFire(Entity* e)
{
	if (Robot->Attacker->ActorSkills.size() == 0)
	{
		int nAddedSkills = Robot->Attacker->FillActorSkillList();
		printf("Added %d skills..\n", nAddedSkills);
	}

	if (Robot->Attacker->ActorSkills.size() > 0)
	{
		for each (Actor::ActorSkill* skill in Robot->Attacker->ActorSkills)
		{
			if (skill->Id == this->AttackingSkill) //use correct version of RF (vaal vs. non)
			{
				if (!Robot->IsBusy && !Robot->InTown)
				{
					PacketWriter* p = PacketBuilder::SelfSkill(Robot->GetLocalPlayer()->GetUniqueID(), skill->Id + 0x4000);
					PacketBuilder::Send(p);

					Sleep(500);

					p = PacketBuilder::SelfSkill(Robot->GetLocalPlayer()->GetUniqueID(), skill->Id);
					PacketBuilder::Send(p);

					Sleep(500);

					Robot->Interaction(e->GetUniqueID(), Input::InputIds::INTERACTION);
				}
			}
		}
	}
}

void AutoAttacker::UseSingleAttack(Entity* e)
{
	if (Robot->DebugMode)
	{
		printf("[DEBUG] UseSingleAttack: %llX\n", e->Address);
	}

	Robot->Attacker->IsAttacking = true;

	uint16_t skill = this->AttackingSkill;

	if (Robot->Attacker->ActorSkills.size() == 0)
	{
		int nAddedSkills = Robot->Attacker->FillActorSkillList();
		printf("Added %d skills..\n", nAddedSkills);
	}
		
	if (Robot->Attacker->ActorSkills.size() > 0)
	{
		for each (Actor::ActorSkill* skill in Robot->Attacker->ActorSkills)
		{
			if (skill->Id == this->AttackingSkill)
			{
				if (skill->isVaal && Robot->Attacker->UsingVaalSkill)
				{
					Robot->Interaction(e->GetUniqueID(), skill->Id + 0x4000);
					Sleep(Robot->AttackDelay);
					Robot->Attacker->IsAttacking = false;
				}
				else
				{
					Robot->Interaction(e->GetUniqueID(), skill->Id);
					Sleep(Robot->AttackDelay);
					Robot->Attacker->IsAttacking = false;
				}		
			}
		}
	}
}

bool AutoAttacker::KillMonster(Entity* e) //returns false on bad condition or fail
{
	if (Robot->IsBusy || Robot->InTown)
		return false;

	Entity* Player = Robot->GetLocalPlayer();

	if (Player == nullptr)
		return false;

	if (Life::GetEntityHP(e) > 0 && Life::GetEntityHP(e) != (UINT)-1) //change this to while, make attacks chained?
	{
		Actor::ActionIDs action = Actor::GetCurrentActionID(Player);

		if (action == Actor::ActionIDs::ACTION_NONE)
		{
			if (Robot->Attacker->UsingRighteousFire)
			{
				HandleRighteousFire(e);
			}
			else
			{
				printf("Using attack!\n");
				UseSingleAttack(e);
			}

		}
		//check if we are dead, return false?
		delete Player;
	}
	else
	{
		return false;
	}

	return true;
}


void AutoAttacker::HuntingLoop()
{
	printf("Starting hunting...\n");

	Robot->Attacker->IsAttacking = false;

	while (!Robot->Disconnected)
	{
		while (Robot->InTown) //do nothing until out of town
		{
			printf("Attacking in disabled in town..\n");
			Sleep(5000);
			continue;
		}

		while (Robot->Attacker->IsBusy || !Robot->Attacker->IsHunting) //...and if busy also do nothing and wait
		{
			Sleep(5000);
			printf("Robot->IsBusy!\n");
			continue;
		}

		if (Robot->EntityList.size() > 0)
		{
			Entity* closest = Robot->Attacker->GetClosestMonster();
			
			if (closest != NULL)
			{
				printf("Closest mob: %d at (%d, %d) Life: %d\n", closest->GetUniqueID(), closest->GetVector2().X, closest->GetVector2().Y, Life::GetEntityHP(closest));

				if (!Robot->Attacker->KillMonster(closest))
				{
					printf("Moving onto next monster..\n");
					continue;
				}
			}
			else
			{
				printf("No closest monster!\n");
			}
		}
	}

	printf("Ended hunting loop!\n");
}

bool AutoAttacker::DodgeMeleeAttack(Entity* e) //todo: finish this
{
	Vector2 pV = Robot->GetLocalPlayer()->GetVector2();
	Vector2 eV = e->GetVector2();

	byte Animation = Actor::GetCurrentActionID(e); //0x40 = unspawned?

	if (Animation != 0 && Animation != 0x80) //
	{
		if (Distances::GetDistanceBetweenObjects(pV.X, pV.Y, eV.X, eV.Y) <= 20) //test
		{
			Robot->IsBusy = true;
			//dodge here
			PacketWriter* p = PacketBuilder::Action(Robot->Attacker->MovementSkill, 0, 30, 10); //dunno for directino
			PacketBuilder::Send(p);
			Robot->EndAction();
			Robot->IsBusy = false;
			return true;
		}
	}

	return false;
}

bool AutoAttacker::DodgeProjectileAttack(Entity* e) //todo: finish this
{
	Vector2 pV = Robot->GetLocalPlayer()->GetVector2();
	Vector2 eV = e->GetVector2();
	FLOAT Direction = 0.0f;
	
	if (Distances::IsPointInCircle(pV.X, pV.Y, eV.X, eV.Y, 30)) //test this
	{
		Robot->IsBusy = true;
		//dodge here
		PacketWriter* p = PacketBuilder::Action(Robot->Attacker->MovementSkill, 0, 30, 10); //dunno for directino
		PacketBuilder::Send(p);

		Robot->EndAction();
		Robot->IsBusy = false;

		return true;
	}
	
	
	return false;
}

bool AutoAttacker::DodgeVolatileAttack(Entity* e) //todo: finish this
{
	Vector2 pV = Robot->GetLocalPlayer()->GetVector2();
	Vector2 eV = e->GetVector2();

	if (Distances::GetDistanceBetweenObjects(pV.X, pV.Y, eV.X, eV.Y) < 30) //test
	{
		//dodge here
	}

	return true;
}

void AutoAttacker::UseBuffList() //from file
{
	if (this->BuffList.size() > 0)
	{
		Robot->IsBusy = true;
		
		for each(uint16_t buff in this->BuffList)
		{
			printf("Casting buff: %d\n", buff);
			PacketWriter* p = PacketBuilder::SelfSkill(Robot->GetLocalPlayer()->GetUniqueID(), buff);
			PacketBuilder::Send(p);
			Sleep(1000);
		}

		Robot->IsBusy = false;
	}
}

void AutoAttacker::UseSkillsList() //from file
{
	if (this->SkillsList.size() > 0)
	{
		Robot->IsBusy = true;

		for each(Actor::ActorSkill* skill in this->SkillsList)
		{
			if (skill->CanBeUsedWithWeapon && skill->CanBeUsed == 0)
			{
				if (skill->Id >= 0x8001 && skill->Id <= 0xC001)
				{
					printf("Casting skill: %d\n", skill->Id);
					PacketWriter* p = PacketBuilder::Action(skill->Id, 0, 0, 0);
					PacketBuilder::Send(p);
					Sleep(1200);
				}

			}

		}

		Robot->IsBusy = false;
	}
}

bool AutoAttacker::FillBuffListFromFile()
{
	bool FoundLine = false;

	std::wifstream infile("./buffs.ini");
	std::wstring line;

	if (infile.bad())
	{
		printf("[ERROR] Couldn't read skills.ini! Please make sure it's in the PoE folder.\n");
		return false;
	}

	while (std::getline(infile, line)) //make this more portable
	{
		if (line[0] == L'/' && line[1] == L'/')
		{
			continue;
		}
		else
		{
			uint16_t skillId;

			if (line == L"Helmet 1") //finish this!
				skillId = 0x8004;
			else if (line == L"Helmet 2")
				skillId = 0x8404;
			else if (line == L"Helmet 3")
				skillId = 0x8C04;
			else if (line == L"Helmet 4")
				skillId = 0x8804;
			else if (line == L"Boots 1")
				skillId = 0x8009;
			else if (line == L"Boots 2")
				skillId = 0x8409;
			else if (line == L"Boots 3")
				skillId = 0x8809;
			else if (line == L"Boots 4")
				skillId = 0x8C09;
			else if (line == L"Gloves 1")
				skillId = 0x8008;
			else if (line == L"Gloves 2")
				skillId = 0x8408;
			else if (line == L"Gloves 3")
				skillId = 0x8808;
			else if (line == L"Gloves 4")
				skillId = 0x8C08;
			else if (line == L"LeftHand 1")
				skillId = 0x8002;
			else if (line == L"LeftHand 2")
				skillId = 0x8402;
			else if (line == L"LeftHand 3")
				skillId = 0x8802;
			else if (line == L"RightHand 1")
				skillId = 0x8003;
			else if (line == L"RightHand 2")
				skillId = 0x8403;
			else if (line == L"RightHand 3")
				skillId = 0x8803;
			else if (line == L"Body 1")
				skillId = 0x8001;
			else if (line == L"Body 2")
				skillId = 0x8401;
			else if (line == L"Body 3")
				skillId = 0x8C01;
			else if (line == L"Body 4")
				skillId = 0x9001;
			else if (line == L"Body 5")
				skillId = 0x9401;
			else if (line == L"Body 6")
				skillId = 0x9801;
			else if (line == L"Weapon 1")
				skillId = 0x8002;
			else if (line == L"Weapon 2")
				skillId = 0x8402;
			else if (line == L"Weapon 3")
				skillId = 0x8802;
			else if (line == L"Weapon 4")
				skillId = 0x8C02;
			else if (line == L"Weapon 5")
				skillId = 0x9002;
			else if (line == L"Weapon 6")
				skillId = 0x9402;
			else if (line == L"Bone Offering")
				skillId = 0x97A7;

			this->BuffList.push_back(skillId);
		}
	}

	infile.close();
	return true;
}

bool AutoAttacker::FillSkillsListFromFile() //file read for skills, maybe easier for users but not as powerful as ingame read
{
	bool FoundLine = false;

	std::wifstream infile("./skills.ini");
	std::wstring line;

	if (infile.bad())
	{
		printf("[ERROR] Couldn't read skills.ini! Please make sure it's in the PoE folder.\n");
		return false;
	}

	while (std::getline(infile, line)) //make this more portable
	{
		if (line[0] == L'/' && line[1] == L'/')
		{
			continue;
		}
		else
		{
			uint16_t skillId;

			if (wcsstr(line.c_str(), L"Helmet 1") != NULL) //finish this!
			{
				skillId = 0x8004;
			}
			else if (wcsstr(line.c_str(),  L"Helmet 2") != NULL)
				skillId = 0x8404;
			else if (wcsstr(line.c_str(),  L"Helmet 3") != NULL)
				skillId = 0x8C04;
			else if (wcsstr(line.c_str(),  L"Helmet 4") != NULL)
				skillId = 0x8804;
			else if (wcsstr(line.c_str(),  L"Boots 1") != NULL)
				skillId = 0x8009;
			else if (wcsstr(line.c_str(),  L"Boots 2") != NULL)
				skillId = 0x8409;
			else if (wcsstr(line.c_str(),  L"Boots 3") != NULL)
				skillId = 0x8809;
			else if (wcsstr(line.c_str(),  L"Boots 4") != NULL)
				skillId = 0x8C09;
			else if (wcsstr(line.c_str(),  L"Gloves 1") != NULL)
				skillId = 0x8008;
			else if (wcsstr(line.c_str(),  L"Gloves 2") != NULL)
				skillId = 0x8408;
			else if (wcsstr(line.c_str(),  L"Gloves 3") != NULL)
				skillId = 0x8808;
			else if (wcsstr(line.c_str(),  L"Gloves 4") != NULL)
				skillId = 0x8C08;
			else if (wcsstr(line.c_str(),  L"LeftHand 1") != NULL)
				skillId = 0x8002;
			else if (wcsstr(line.c_str(),  L"LeftHand 2") != NULL)
				skillId = 0x8402;
			else if (wcsstr(line.c_str(),  L"LeftHand 3") != NULL)
				skillId = 0x8802;
			else if (wcsstr(line.c_str(),  L"RightHand 1") != NULL)
				skillId = 0x8003;
			else if (wcsstr(line.c_str(),  L"RightHand 2") != NULL)
				skillId = 0x8403;
			else if (wcsstr(line.c_str(),  L"RightHand 3") != NULL)
				skillId = 0x8803;
			else if (wcsstr(line.c_str(),  L"Body 1") != NULL)
				skillId = 0x8001;
			else if (wcsstr(line.c_str(),  L"Body 2") != NULL)
				skillId = 0x8401;
			else if (wcsstr(line.c_str(),  L"Body 3") != NULL)
				skillId = 0x8C01;
			else if (wcsstr(line.c_str(),  L"Body 4") != NULL)
				skillId = 0x9001;
			else if (wcsstr(line.c_str(),  L"Body 5") != NULL)
				skillId = 0x9401;
			else if (wcsstr(line.c_str(),  L"Body 6") != NULL)
				skillId = 0x9801;
			else if (wcsstr(line.c_str(),  L"Weapon 1") != NULL)
				skillId = 0x8002;
			else if (wcsstr(line.c_str(),  L"Weapon 2") != NULL)
				skillId = 0x8402;
			else if (wcsstr(line.c_str(),  L"Weapon 3") != NULL)
				skillId = 0x8802;
			else if (wcsstr(line.c_str(),  L"Weapon 4") != NULL)
				skillId = 0x8C02;
			else if (wcsstr(line.c_str(),  L"Weapon 5") != NULL)
				skillId = 0x9002;
			else if (wcsstr(line.c_str(),  L"Weapon 6") != NULL)
				skillId = 0x9402;
			else if (wcsstr(line.c_str(),  L"Bone Offering") != NULL)
				skillId = 0x97A7;

			Actor::ActorSkill* skill = new Actor::ActorSkill();
			skill->Id = skillId;

			this->SkillsList.push_back(skill);
		}
	}

	infile.close();
	return true;
}

int AutoAttacker::FillActorSkillList() //ingame memory read, not file
{
	this->ActorSkills = Actor::GetSkillList(Robot->GetLocalPlayer());
	return this->ActorSkills.size();
}

void AutoAttacker::WalkInFacingDirection()
{
	while (Robot->IsBusy)
		Sleep(200);

	while (Actor::GetCurrentActionID(Robot->GetLocalPlayer()) != 0) //avoid crashing, etc
		Sleep(200);

	FLOAT Rotation = Positioned::GetRotation(Robot->GetLocalPlayer());

	INT X = 0;
	INT Y = 0;

	if (Rotation >= 0.0f && Rotation <= 0.5235f)
	{
		X = 1;
		Y = -15;
	}
	else if (Rotation >= 0.5235 && Rotation <= 0.7853)
	{
		X = 1;
		Y = -25;
	}
	else if (Rotation >= 0.7853 && Rotation <= 1.0471)
	{
		X = -1;
		Y = -35;
	}
	else if (Rotation >= 1.0471  && Rotation <= 1.5707)
	{
		X = -1;
		Y = 5;
	}
	else if (Rotation >= 1.5707  && Rotation <= 2.0943)
	{
		X = 35;
		Y = 5;
	}
	else if (Rotation >= 2.0943  && Rotation <= 2.3561)
	{
		X = 35;
		Y = 20;
	}
	else if (Rotation >= 2.3561  && Rotation <= 2.6179)
	{
		X = 20; //+, + quadrant
		Y = 20;
	}
	else if (Rotation >= 2.6179  && Rotation <= 3.1415)
	{
		X = 5;
		Y = 35;
	}
	else if (Rotation >= 3.1415   && Rotation <= 4.7123)
	{
		X = -1;
		Y = 35;
	}
	else if (Rotation >= 4.7123 && Rotation <= 6.29)
	{
		X = -35;
		Y = -15;
	}

	Vector2 pV = Robot->GetLocalPlayer()->GetVector2();

	uint16_t movementSkill = Input::InputIds::RUN; //just use normal run for now, adding a cooldown dash skill can crash

	PacketWriter* p = PacketBuilder::Action(movementSkill, NULL, X, Y);
	PacketBuilder::Send(p);
	Robot->EndAction();
}

Entity* AutoAttacker::GetClosestMonster()
{
	int closestDistance = 100000;
	uint32_t closestUID = 0;
	Entity* closest = NULL;
	Vector2 closestPos = { 0, 0 };

	for each(Entity* e in Robot->EntityList)
	{
		if (e->GetComponentAddress("Monster") > 0)
		{
			if (!Robot->IsMonsterSummoned(e)) //for now  we will not place all these ifs on one line to catch any errors, etc that could come from each statement
			{
				if (Life::GetEntityHP(e) > 0 && Life::GetEntityHP(e) != -1)
				{
					if (Targetable::IsTargetable(e))
					{
						if (!Entity::IsCorpse(e))
						{
							if (e->GetUniqueID() > 0 && e->GetUniqueID() <= 50000)
							{
								Vector2 pos = e->GetVector2();
								Vector2 pPos = Robot->GetLocalPlayer()->GetVector2();

								int apart = Distances::GetDistanceBetweenObjects(pos.X, pos.Y, pPos.X, pPos.Y);

								if (apart < closestDistance)
								{
										closestDistance = apart;
										closest = e;
										closestPos = pos;
								}
							}
						}
					}
				}
			}
		}
	}

	return closest;
}