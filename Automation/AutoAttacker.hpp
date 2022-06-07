#pragma once
#include "Packets.hpp"
#include "Entity.hpp"
#include "Actor.hpp"

class AutoAttacker
{
public:

	AutoAttacker();

	std::list<Entity*> MonsterList;
	std::list<wchar_t*> IgnoredMonsterNames;

	std::list<Entity*> CorpseList; //corpses have a max HP with 0 current HP, 

	uint16_t AttackingSkill = 0;
	uint16_t PortalSkill = 0;
	uint16_t MovementSkill = Input::InputIds::RUN; //default run

	std::list<Actor::ActorSkill*> ActorSkills; //actual skills on actor
	std::list<Actor::ActorSkill*> SkillsList; //skills from skills.ini file

	float AttackingDistance;

	bool IsHunting; //on/off switch

	bool IsAttacking;

	bool IsMoving;

	bool IsMelee; //sets attacking distance to 100

	bool IsFightingBoss; //prioritizes?

	bool UsingRighteousFire;
	void HandleRighteousFire(Entity* e);
	
	bool UsingRandomSkills;

	bool IsBusy = false; //for looting and other movements

	bool UsingVaalSkill = false;
	bool UsingTotems = false;
	bool UsingSkillsFromFile = false;

	bool KillMonster(Entity* mob);
	static void HuntingLoop();

	HANDLE Thread;
	HANDLE DodgingThread; //for dodging attacks

	void CastRandomSkill(Entity* e);
	void UseVaalSkill(Entity* e);
	void UseSingleAttack(Entity* e);

	bool DodgeMeleeAttack(Entity* e);
	bool DodgeProjectileAttack(Entity* e);
	bool DodgeVolatileAttack(Entity* e);

	bool PrepareCharacter();

	bool FillBuffListFromFile();
	bool FillSkillsListFromFile();
	void UseBuffList();
	void UseSkillsList();

	int FillActorSkillList();

	void WalkInFacingDirection();

	Entity* GetClosestMonster();

};
