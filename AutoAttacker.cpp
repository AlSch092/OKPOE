#include "AutoAttacker.hpp"
#include "AutoPlayer.hpp"

extern AutoPlayer* g_Robot;

AutoAttacker::AutoAttacker()
{
	this->IsBusy = false;
	this->IsHunting = false;
	this->IsFightingBoss = false;
	this->MovementSkill = Input::InputIds::RUN;
	this->UsingRandomSkills = false;

	//int skillsAdded = FillActorSkillList();

	IgnoredMonsters.push_back(L"Avatar"); //all harbingers
	IgnoredMonsters.push_back(L"AvatarAtlasMinion"); //all harbingers
	IgnoredMonsters.push_back(L"AvatarBossAtlas"); //all harbingers
	IgnoredMonsters.push_back(L"RaisedSkeletons/RaisedSkeleton"); //basic skeletons
	IgnoredMonsters.push_back(L"RaisedZombieStandard"); //basic zombies
	IgnoredMonsters.push_back(L"SummonedPhantasm"); //phantasm from skill gem
	IgnoredMonsters.push_back(L"GolemSummoned"); //all golems
	IgnoredMonsters.push_back(L"ElementalSummoned"); //all elemental golems
	IgnoredMonsters.push_back(L"HeraldOfAgonySpiderPlated");
	IgnoredMonsters.push_back(L"AnimatedItem/"); //all animated items
	IgnoredMonsters.push_back(L"NPCAllies/"); //all npc allies
	IgnoredMonsters.push_back(L"SummonedWolf@"); //summoned wolfs from unique ring
	IgnoredMonsters.push_back(L"Totems/HolyFireSprayTotem"); //holy flame totem
	IgnoredMonsters.push_back(L"NPC/"); //holy flame totem
	IgnoredMonsters.push_back(L"LeagueBetrayal/MasterNinjaCop"); //jun
	IgnoredMonsters.push_back(L"LeagueBetrayal/BetrayalBloodPool"); //holy flame totem
	IgnoredMonsters.push_back(L"RaisedSkeletons/NecromancerRaisedSkeletonStandard"); //holy flame totem
	IgnoredMonsters.push_back(L"LegionLeague/");
	IgnoredMonsters.push_back(L"Masters/");
	IgnoredMonsters.push_back(L"CrucibleScorch");

	PriorityMonsters.push_back(L"Totem");
	
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
					g_Robot->Attacker->IsAttacking = true;
					g_Robot->Interaction(e->GetUniqueID(), skill->Id);
					Sleep(g_Robot->AttackDelay);
					g_Robot->Attacker->IsAttacking = false;
				}
			}

		}
	}
}

void AutoAttacker::OnPlayerDeath()
{
	printf("[INFO] OnPlayerDeath called -> Casting auras, returning to previous area");

	Sleep(3000);

	if (this->ActorSkills.size() == 0)
	{
		FillActorSkillList();
	}

	for each (Actor::ActorSkill * skill in this->ActorSkills) //cast buffs
	{
		if (skill->IsCastedOnSelf)
		{
			CastSkillOnSelf(skill->Id);
			Sleep(800);
		}
	}
}

void AutoAttacker::CastSkillOnSelf(uint16_t skillId)
{
	Entity* local = g_Robot->GetLocalPlayer();

	while (Actor::GetCurrentActionID(local) != 0)
		Sleep(100);

	PacketWriter* p = PacketBuilder::SelfSkill(local->GetUniqueID(), skillId);
	PacketBuilder::Send(p);
	
	delete local; local = NULL;
}

void AutoAttacker::CastSkillOnEntity(Actor::ActorSkill* skill, Entity* ent)
{
	Entity* local = g_Robot->GetLocalPlayer();

	while (Actor::GetCurrentActionID(local) != 0)
		Sleep(10);

	g_Robot->Interaction(ent->GetUniqueID(), skill->Id);

	delete local; local = NULL;
}

void AutoAttacker::HandleRighteousFire(Entity* e)
{
	if (g_Robot->Attacker->ActorSkills.size() == 0)
	{
		int nAddedSkills = g_Robot->Attacker->FillActorSkillList();
		printf("Added %d skills..\n", nAddedSkills);
	}

	if (g_Robot->Attacker->ActorSkills.size() > 0)
	{
		g_Robot->Attacker->IsBusy = true;

		for each (Actor::ActorSkill* skill in g_Robot->Attacker->ActorSkills)
		{
			if (g_Robot->Attacker->UsingVaalSkill)
			{
				if (skill->Id == this->AttackingSkill) //use correct version of RF (vaal vs. non)
				{
					CastSkillOnSelf(skill->Id);
					Sleep(100);
				}
			}
			else
			{
				if (skill->Id == this->AttackingSkill) //use correct version of RF (vaal vs. non)
				{
					CastSkillOnSelf(skill->Id + 0x4000);
				}
			}
		}

		Entity* local = g_Robot->GetLocalPlayer();
		Vector2 v1 = e->GetVector2();
		Vector2 pV = local->GetVector2();
		delete local; local = NULL;

		g_Robot->InteractIfInRange(e, 400);

		g_Robot->Attacker->IsBusy = false;

		Sleep(2000); //slow does # packets sent
	}
}

bool AutoAttacker::UseSingleAttack(Entity* e)
{
	if (g_Robot->DebugMode)
	{
		printf("[DEBUG] UseSingleAttack: %llX\n", e->Address);
	}

	g_Robot->Attacker->IsAttacking = true;

	uint16_t skill = this->AttackingSkill;

	if (g_Robot->Attacker->ActorSkills.size() == 0)
	{
		int nAddedSkills = g_Robot->Attacker->FillActorSkillList();
		printf("Added %d skills..\n", nAddedSkills);

		if (nAddedSkills == 0)
		{
			printf("[ERROR] Added skills was 0 at UseSingleAttack!\n");
			return false;
		}
	}
		
	if (g_Robot->Attacker->ActorSkills.size() > 0)
	{
		bool bFoundSkill = false;

		for each (Actor::ActorSkill* skill in g_Robot->Attacker->ActorSkills) //holy shit this is too complicated
		{
			if (g_Robot->Attacker->UsingVaalSkill)
			{
				if (skill->Id == this->AttackingSkill + 0x4000) //using NORMAL VERSION OF VAAL SKILL
				{
					g_Robot->Interaction(e->GetUniqueID(), skill->Id);
					Sleep(g_Robot->AttackDelay);
					g_Robot->Attacker->IsAttacking = false;		
					bFoundSkill = true;
				}
			}
			else
			{
				if (skill->Id == this->AttackingSkill)
				{
					g_Robot->Interaction(e->GetUniqueID(), skill->Id);
					Sleep(g_Robot->AttackDelay);
					g_Robot->Attacker->IsAttacking = false;
					bFoundSkill = true;
				}
			}
		}

		if (!bFoundSkill)
		{
			printf("[ERROR] Could not find matching skill to: %x\n", this->AttackingSkill);
			return false;
		}
	}

	return true;
}

bool AutoAttacker::KillMonster(Entity* e) //returns false on bad condition or fail
{
	if (g_Robot->Attacker->IsBusy || g_Robot->InTown || g_Robot->Disconnected)
	{
		printf("Can't kill monster: busy!\n");
		return false;
	}

	auto Player = g_Robot->GetLocalPlayer();

	if (e == nullptr || Player == nullptr)
	{
		printf("[ERROR] LocalPLayer was NULL??\n");
		return false;
	}

	int life = Life::GetEntityHP(e);

	if (life > 0 && life != -1) //change this to while, make attacks chained?
	{
		while (Actor::GetCurrentActionID(Player) != 0)
			Sleep(100);

		if (g_Robot->Attacker->UsingRighteousFire)	
			HandleRighteousFire(e);		
		else if (g_Robot->Attacker->IsSkillRanged)	
			UseSingleAttack(e);	
		else if (g_Robot->Attacker->IsMelee)
		{
			if (g_Robot->InteractIfInRange(e, 250)) //if attacking stops working, check the 2nd param
			{
				Sleep(200);
				UseSingleAttack(e);
			}
		}
	}
	else
	{
		delete Player;
		return false;
	}

	delete Player;
	return true;
}

void AutoAttacker::DodgeCycle()
{
	bool dodging = true;

	printf("The program will try to dodge attacks when possible.. please make sure yuor Movement Skill is selected.\n");

	if (g_Robot->Attacker->MovementSkill == 0)
	{
		printf("Movement skill was 0! Could not start dodging thread.\n");
		return;
	}

	while (dodging && g_Robot->Attacker->IsHunting)
	{
		if (g_Robot->MonsterList.size() > 0)
		{
			for each(Entity* e in g_Robot->MonsterList)
			{
				//todo: finish this
			}
		}
	}
}

void AutoAttacker::HuntingLoop()
{
	printf("Starting hunting...\n");

	g_Robot->Attacker->IsAttacking = false;
	g_Robot->Attacker->HadDied = false; //glitch

	while (g_Robot->Attacker->IsHunting) //&& g_Robot->Attacker->IsHunting)
	{
		while (g_Robot->Attacker->IsBusy || g_Robot->Disconnected || g_Robot->InTown || g_Robot->IsLooting) //...and if busy also do nothing and wait
		{
			if (!g_Robot->Attacker->IsHunting)
			{
				printf("Ending hunting loop.\n");
				return;
			}

			Sleep(2000);
			printf("g_Robot->IsBusy or in Town!\n");
			continue;
		}

		//if (g_Robot->Attacker->HadDied) //we are now handling player deaths via a .lua script
		//{
		//	printf("[INFO] Casting skills after reviving...\n");
		//	g_Robot->Attacker->OnPlayerDeath();
		//	g_Robot->Attacker->HadDied = false;
		//}

		Entity* player = g_Robot->GetLocalPlayer();

		if (player != NULL)
		{
			if (Life::GetEntityHP(player) == 0)
			{
				printf("[INFO] Player has died, waiting...\n");
				Sleep(5000);
			}

			delete player;
		}

		if (g_Robot->MonsterList.size() > 0)
		{
			Entity* closest = g_Robot->Attacker->GetClosestMonster(); //does not call new or malloc! no need to delete this after each loop!
			
			if (closest != NULL)
			{
				Entity* pe = g_Robot->GetLocalPlayer();
				
				if (pe != NULL)
				{
					Vector2 pV = pe->GetVector2();

					int DistanceAway = Distances::GetDistanceBetweenObjects(pV, closest->GetVector2());

					printf("Closest mob: ID %d at (%d, %d) Life: %d (us: %d,%d -> %d)\n", closest->GetUniqueID(), closest->GetVector2().X, closest->GetVector2().Y, Life::GetEntityHP(closest), pV.X, pV.Y, DistanceAway);

					if (DistanceAway > INTERACTION_MAX_DISTANCE)
					{
						printf("Too far away to interact with mob, trying to move closer..\n");
						g_Robot->Attacker->MoveTowardsMonster(closest);
						Sleep(1500);
					}

					if (!g_Robot->Attacker->KillMonster(closest))
					{
						printf("Moving onto next monster..\n");
						delete pe; pe = nullptr;
						continue;
					}

					int life = Life::GetEntityHP(closest);

					if (life == 0 || life == -1) //remove dead entities from list
					{
						g_Robot->MonsterList.remove(closest);
						delete closest; closest = nullptr;
					}

					delete pe; pe = nullptr;
				}	
			}
		}
	}

	printf("Ended hunting loop!\n");
}

bool AutoAttacker::DodgeMeleeAttack(Entity* e) //todo: finish this
{
	Entity* local = g_Robot->GetLocalPlayer();
	Vector2 pV = local->GetVector2();
	Vector2 eV = e->GetVector2();
	delete local; local = NULL;
	byte Animation = Actor::GetCurrentActionID(e);

	if (Animation != 0 && Animation != 0x80) //
	{
		if (Distances::GetDistanceBetweenObjects(pV, eV) <= 20) //test
		{
			g_Robot->Attacker->IsBusy = true;
			//dodge here
			PacketWriter* p = PacketBuilder::Action(g_Robot->Attacker->MovementSkill, 0, 30, 10); 
			PacketBuilder::Send(p);
			g_Robot->EndAction();
			g_Robot->Attacker->IsBusy = false;
			return true;
		}
	}

	return false;
}

bool AutoAttacker::DodgeProjectileAttack(Entity* e) //todo: finish this
{
	Vector2 pV = g_Robot->GetLocalPlayer()->GetVector2();
	Vector2 eV = e->GetVector2();
	FLOAT Direction = 0.0f;
	
	if (Distances::IsPointInCircle(pV.X, pV.Y, eV.X, eV.Y, 30)) //test this
	{
		g_Robot->Attacker->IsBusy = true;
		//dodge here
		PacketWriter* p = PacketBuilder::Action(g_Robot->Attacker->MovementSkill, 0, 30, 10);
		PacketBuilder::Send(p);

		g_Robot->EndAction();
		g_Robot->Attacker->IsBusy = false;

		return true;
	}
	
	
	return false;
}

bool AutoAttacker::DodgeVolatileAttack(Entity* e) //todo: finish this
{
	Entity* local = g_Robot->GetLocalPlayer();
	Vector2 pV = local->GetVector2();
	Vector2 eV = e->GetVector2();
	delete local; local = NULL;

	if (Distances::GetDistanceBetweenObjects(pV, eV) < 30) //test
	{
		//dodge here
	}

	return true;
}

void AutoAttacker::UseSkillsList() //from file
{
	if (this->SkillsList.size() > 0)
	{
		g_Robot->Attacker->IsBusy = true;

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

		g_Robot->Attacker->IsBusy = false;
	}
}

uint16_t AutoAttacker::GetSkillIdFromSlot(wstring equipSlot)
{
	uint16_t skillId = 0;

	if (wcsstr(equipSlot.c_str(), L"Helmet 1") != NULL) //todo: generalize this function
		skillId = 0x8004;
	else if (wcsstr(equipSlot.c_str(), L"Helmet 2") != NULL)
		skillId = 0x8404;
	else if (wcsstr(equipSlot.c_str(), L"Helmet 3") != NULL)
		skillId = 0x8C04;
	else if (wcsstr(equipSlot.c_str(), L"Helmet 4") != NULL)
		skillId = 0x8804;
	else if (wcsstr(equipSlot.c_str(), L"Boots 1") != NULL)
		skillId = 0x8009;
	else if (wcsstr(equipSlot.c_str(), L"Boots 2") != NULL)
		skillId = 0x8409;
	else if (wcsstr(equipSlot.c_str(), L"Boots 3") != NULL)
		skillId = 0x8809;
	else if (wcsstr(equipSlot.c_str(), L"Boots 4") != NULL)
		skillId = 0x8C09;
	else if (wcsstr(equipSlot.c_str(), L"Gloves 1") != NULL)
		skillId = 0x8008;
	else if (wcsstr(equipSlot.c_str(), L"Gloves 2") != NULL)
		skillId = 0x8408;
	else if (wcsstr(equipSlot.c_str(), L"Gloves 3") != NULL)
		skillId = 0x8808;
	else if (wcsstr(equipSlot.c_str(), L"Gloves 4") != NULL)
		skillId = 0x8C08;
	else if (wcsstr(equipSlot.c_str(), L"LeftHand 1") != NULL)
		skillId = 0x8002;
	else if (wcsstr(equipSlot.c_str(), L"LeftHand 2") != NULL)
		skillId = 0x8402;
	else if (wcsstr(equipSlot.c_str(), L"LeftHand 3") != NULL)
		skillId = 0x8802;
	else if (wcsstr(equipSlot.c_str(), L"RightHand 1") != NULL)
		skillId = 0x8003;
	else if (wcsstr(equipSlot.c_str(), L"RightHand 2") != NULL)
		skillId = 0x8403;
	else if (wcsstr(equipSlot.c_str(), L"RightHand 3") != NULL)
		skillId = 0x8803;
	else if (wcsstr(equipSlot.c_str(), L"Body 1") != NULL)
		skillId = 0x8001;
	else if (wcsstr(equipSlot.c_str(), L"Body 2") != NULL)
		skillId = 0x8401;
	else if (wcsstr(equipSlot.c_str(), L"Body 3") != NULL)
		skillId = 0x8801;
	else if (wcsstr(equipSlot.c_str(), L"Body 4") != NULL)
		skillId = 0x8C01;
	else if (wcsstr(equipSlot.c_str(), L"Body 5") != NULL)
		skillId = 0x9001;
	else if (wcsstr(equipSlot.c_str(), L"Body 6") != NULL)
		skillId = 0x9401;
	else if (wcsstr(equipSlot.c_str(), L"Weapon 1") != NULL)
		skillId = 0x8002;
	else if (wcsstr(equipSlot.c_str(), L"Weapon 2") != NULL)
		skillId = 0x8402;
	else if (wcsstr(equipSlot.c_str(), L"Weapon 3") != NULL)
		skillId = 0x8802;
	else if (wcsstr(equipSlot.c_str(), L"Weapon 4") != NULL)
		skillId = 0x8C02;
	else if (wcsstr(equipSlot.c_str(), L"Weapon 5") != NULL)
		skillId = 0x9002;
	else if (wcsstr(equipSlot.c_str(), L"Weapon 6") != NULL)
		skillId = 0x9402;
	else if (wcsstr(equipSlot.c_str(), L"Bone Offering") != NULL)
		skillId = 0x97A7;
	else if (wcsstr(equipSlot.c_str(), L"Run") != NULL)
		skillId = 0x2909;
	
	return skillId;
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
			continue;		
		else
		{
			uint16_t skillId = AutoAttacker::GetSkillIdFromSlot(line);

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
	Entity* local = g_Robot->GetLocalPlayer();
	this->ActorSkills = Actor::GetSkillList(local);
	delete local; local = NULL;
	return this->ActorSkills.size();
}

void AutoAttacker::WalkInFacingDirection()
{
	while (g_Robot->Attacker->IsBusy || g_Robot->Disconnected)
		Sleep(200);

	Entity* local = g_Robot->GetLocalPlayer();

	while (Actor::GetCurrentActionID(local) != 0) //avoid crashing, etc
		Sleep(200);


	FLOAT Rotation = Positioned::GetRotation(local);

	INT X = 0, Y = 0;

	if (Rotation >= 0.0f && Rotation <= 0.5235f)
	{
		X = 1;
		Y = -25;
	}
	else if (Rotation >= 0.5235 && Rotation <= 0.7853)
	{
		X = 40;
		Y = -30;
	}
	else if (Rotation >= 0.7853 && Rotation <= 1.0471)
	{
		X = -1;
		Y = -35;
	}
	else if (Rotation >= 1.0471 && Rotation <= 1.5707)
	{
		X = 35;
		Y = -18;
	}
	else if (Rotation >= 1.5707 && Rotation <= 2.0943)
	{
		X = 35;
		Y = 5;
	}
	else if (Rotation >= 2.0943 && Rotation <= 2.3561)
	{
		X = 35;
		Y = 20;
	}
	else if (Rotation >= 2.3561 && Rotation <= 2.6179)
	{
		X = 20; //+, + quadrant
		Y = 20;
	}
	else if (Rotation >= 2.6179 && Rotation <= 3.1415)
	{
		X = 30;
		Y = 35;
	}
	else if (Rotation >= 3.1415 && Rotation <= 4.7123)
	{
		X = -1;
		Y = 35;
	}
	else if (Rotation >= 4.7123 && Rotation <= 6.29)
	{
		X = -35;
		Y = -15;
	}

	g_Robot->Attacker->IsMoving = true;

	Vector2 pV = local->GetVector2();

	g_Robot->LastPosition.X = pV.X; g_Robot->LastPosition.Y = pV.Y;

	uint16_t movementSkill;

	if (g_Robot->Attacker->MovementSkill == 0)
		movementSkill = Input::InputIds::RUN; //just use normal run for now, adding a cooldown dash skill can crash
	else
		movementSkill = g_Robot->Attacker->MovementSkill;

	PacketWriter* p = PacketBuilder::Action(movementSkill, NULL, X, Y);
	PacketBuilder::Send(p);
	g_Robot->EndAction();

	delete local; local = NULL;
}

Entity* AutoAttacker::GetClosestMonster()
{
	int closestDistance = 100000;
	uint32_t closestUID = 0;
	Entity* closest = NULL;
	Vector2 closestPos = { 0, 0 };

	if (g_Robot->Disconnected || g_Robot->Attacker->IsBusy || g_Robot->MonsterList.size() == 0)
		return NULL;
	
	__try
	{

		for each (auto e in g_Robot->MonsterList) //something in this crashes in some weird edge case.
		{
			if (DereferenceSafe<UINT64>(e->Address) == NULL)
				continue;

			if (e->GetComponentAddress("Monster") > 0)
			{
				if (!g_Robot->IsMonsterIgnored(e)) //for now  we will not place all these ifs on one line to catch any errors, etc that could come from each statement
				{
					int life = Life::GetEntityHP(e);

					if (life > 0 && life != -1)
					{
						if (Targetable::IsTargetable(e))
						{
							if (!Entity::IsCorpse(e))
							{
								if (e->GetUniqueID() > 0 && e->GetUniqueID() <= 500000)
								{
									Entity* local = g_Robot->GetLocalPlayer();

									Vector2 pos = e->GetVector2();
									Vector2 pPos = local->GetVector2();
									delete local; local = NULL;

									if (pos.X == 0 && pos.Y == 0)
										continue;

									if (pos.X > 100000 || pos.Y > 100000 || pos.X < -100000 || pos.Y < -100000)
										continue;

									int apart = Distances::GetDistanceBetweenObjects(pos, pPos);

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
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		// SEH handling 
		return NULL;
	}
	

	return closest;
}

bool AutoAttacker::MoveTowardsMonster(Entity* e)
{
	if (e == NULL)
		return false;

	Entity* local = g_Robot->GetLocalPlayer();

	Vector2 e_pos = e->GetVector2();
	Vector2 p_pos = local->GetVector2();

	//calculate needed direction vector
	Vector2 movementVector = calculateUnitVector(p_pos, e_pos);

	while (Actor::GetCurrentActionID(local) != 0)
		Sleep(10);

	printf("Moving towards monster: %d, %d\n", movementVector.Y/7, movementVector.X/7); //need to translate the vector into movement units... sigh

	PacketWriter* p = PacketBuilder::Action(0x2909, 0, movementVector.X/7, movementVector.Y/7);
	PacketBuilder::Send(p);
	PacketWriter* p1 = PacketBuilder::EndAction();
	PacketBuilder::Send(p1);

	delete local;
	return true;
}

Vector2 AutoAttacker::normalize(const Vector2& v) { //for unit vectors, but just returns 0,1 usually
	int length = std::sqrt(v.X * v.X + v.Y * v.Y);
	return { v.X / length, v.Y / length };
}

Vector2 AutoAttacker::calculateUnitVector(const Vector2& object1, const Vector2& object2) { //x,y maybe needs flipping
	Vector2 direction = { object2.X - object1.X, object2.Y - object1.Y };
	return direction;
}
