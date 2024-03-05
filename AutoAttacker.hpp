#define INTERACTION_MAX_DISTANCE 120

#pragma once
#include "Packets.hpp"
#include "Entity.hpp"
#include "Actor.hpp"

using namespace std;

struct Buff
{
	int Delay;
	short skillId;
	bool OnCooldown;
};

class AutoAttacker
{
public:

	AutoAttacker();

	list<Entity*> MonsterList;
	list<wstring> PriorityMonsters;

	std::list<Entity*> CorpseList; //corpses have a max HP with 0 current HP, 

	uint16_t AttackingSkill = 0;
	uint16_t PortalSkill = 0;
	uint16_t MovementSkill = 0x2909;

	std::list<Actor::ActorSkill*> ActorSkills; //actual skills on actor

	std::list<Actor::ActorSkill*> SkillsList; //skills from skills.ini file
	//std::list<uint16_t> BuffList; //skills from skills.ini file

	static uint16_t GetSkillIdFromSlot(wstring equipSlot);

	float AttackingDistance;

	bool IsHunting; //on/off switch
	bool IsAttacking; //busy status
	bool IsMoving;
	bool IsMelee; //sets attacking distance to 10
	bool IsFightingBoss; //prioritizes?

	bool UsingRighteousFire = false; //if so, run up to monsters and cast RF + vaal rf once every few seconds and put an autoflasker at around 1 HP...
	void HandleRighteousFire(Entity* e);
	
	bool UsingRandomSkills;

	bool IsBusy = false; //for looting and other movements
	bool HadDied = false;

	bool UsingVaalSkill = false;
	bool UsingTotems = false;
	bool UsingSkillsFromFile = false;

	bool IsSkillRanged = false;

	bool NoMonstersNearby = false;

	list<wstring> IgnoredMonsters;

	bool KillMonster(Entity* mob);
	static void HuntingLoop();

	HANDLE Thread;
	HANDLE DodgingThread; //for dodging attacks
	void DodgeCycle();

	void CastRandomSkill(Entity* e);
	bool UseSingleAttack(Entity* e);

	bool DodgeMeleeAttack(Entity* e);
	bool DodgeProjectileAttack(Entity* e);
	bool DodgeVolatileAttack(Entity* e);

	bool FillBuffListFromFile();
	bool FillSkillsListFromFile();
	void UseBuffList();
	void UseSkillsList();

	int FillActorSkillList();

	void WalkInFacingDirection();
	bool MoveTowardsMonster(Entity* e);

	Entity* GetClosestMonster();

	void CastSkillOnEntity(Actor::ActorSkill* skill, Entity* ent);
	void CastSkillOnSelf(uint16_t skillId);

	void OnPlayerDeath();

	Vector2 normalize(const Vector2& v);
	Vector2 calculateUnitVector(const Vector2& object1, const Vector2& object2);

};