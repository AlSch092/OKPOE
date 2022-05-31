#pragma once
#include "Entity.hpp"
#include "Packets.hpp"

namespace Actor
{
	namespace Classes
	{
		static const wchar_t* ShadowPath = L"Metadata/Characters/DexInt/DexInt";
		static const wchar_t* TemplarPath = L"Metadata/Characters/StrInt/StrInt";
		static const wchar_t* DuelistPath = L"Metadata/Characters/StrDex/StrDex";
		static const wchar_t* MarauderPath = L"Metadata/Characters/Str/Str";
		static const wchar_t* ArcherPath = L"Metadata/Characters/Dex/Dex";
		static const wchar_t* WizardPath = L"Metadata/Characters/Int/Int";
		static const wchar_t* ScionPath = L"Metadata/Characters/StrDexInt/StrDexInt";
	};

	struct ActorSkill
	{
		UINT16 Id; //0x10;
		int KeyDown; //0x0C
		bool CanBeUsedWithWeapon; //0x50
		bool CanBeUsed; //0x51 ? 0 == 1
		int TotalUses; //0x54
		int Cooldown; //0x5c
		int SoulsPerUse; //0x6c
		int TotalVaalUses; //0x70
		bool isVaal; //
		bool IsCastedOnSelf; //0x58?
	};

	enum ActionIDs //powers of 2
	{
		ACTION_NONE = 0,
		ACTION_USING_SKILL = 2,
		ACTION_COOLDOWN = 16,
		ACTION_DEAD = 64,
		ACTION_MOVING = 128,
		ACTION_SHOREBOUND = 256,
		ACTION_HAS_MINES = 2048,
		ACTION_UNKNOWN = 0xFFFF, //invalid in our context
		
	};

	namespace Offsets
	{
		const UINT64 Action = 0x1A8;
		const UINT64 ActionId = 0x208;
		const UINT64 ActionCount = 0x20A;
		const UINT64 AnimationId = 0x234;

		const UINT64 HasMinionArrayOffset = 0x438;
		const UINT64 DeployedObjectArrayOffset = 0x450;

		const UINT64 Skills = 0x690;
		const UINT64 VaalSkills = 0x6B0;
	}

	bool IsAttacking(Entity* e);
	bool IsMoving(Entity* e);
	
	std::list<Actor::ActorSkill*> GetSkillList(Entity* e);
	ActionIDs GetCurrentActionID(Entity* e);
	int GetActionCount(Entity* e);

	std::list<Entity*> GetMinions(Entity* e);
};



	


