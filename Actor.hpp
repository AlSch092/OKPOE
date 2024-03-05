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
		int FinishedCasting; //8
		int KeyDown; //0x0C
		bool CanBeUsedWithWeapon; //0x50
		bool CanBeUsed; //0x51 ? 0 == 1
		int TotalUses; //0x84
		bool IsCastedOnSelf; //0x8C?
		int Cooldown; //0x90
		int SoulsPerUse; //0x9c
		int TotalVaalUses; //0xA0

		bool isVaal; //
	};

	namespace SkillOffsets
	{
		const UINT64 Id = 0x10; //0x10;
		const UINT64 FinishedCasting = 0x08;
		const UINT64 KeyDown = 0x0C; //0x0C
		const UINT64 CanBeUsedWithWeapon = 0x80; //0x80
		const UINT64 CanBeUsed = 0x81; //0x81 ? 0 == 1
		const UINT64 TotalUses = 0x84; //0x84
		const UINT64 IsCastedOnSelf = 0x8C; //0x8C?
		const UINT64 Cooldown = 0x90; //0x8c
		const UINT64 SoulsPerUse = 0x9c; //0x9c
		const UINT64 MaxVaalUses = 0xA0; //0xA0
	}

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

	enum SkillIds
	{
		SinKitavaEnding = 0x1E87,
		GetUpFromGround = 0x289D,
		Flare = 0x8700,
		Dynamite = 0x8F00,
		UnkStance = 0x3B31,
		UnkStance2 = 0x3E14,
		Unknown1 = 0xA308,
		ShieldBlock = 0x37D9,
		UseCrucibleAltar = 0x8300,
	};

	namespace Offsets
	{
		const UINT64 ActionId = 0x210; //80 A3 ?? ?? ?? ?? EF 48 8D BB ?? ?? ?? ?? 81 3F 00 00 00 80
		const UINT64 ActionCount = ActionId + 2;
		const UINT64 AnimationId = 0x23C;
		const UINT64 LastEntityInteractionId = 0x240;
		const UINT64 HasMinionArrayOffset = 0x438;
		const UINT64 DeployedObjectArrayOffset = 0x450;

		const UINT64 Skills = 0x6C0;
		const UINT64 VaalSkills = Skills + 0x20;
	}

	bool IsAttacking(Entity* e);
	bool IsMoving(Entity* e);
	
	std::list<Actor::ActorSkill*> GetSkillList(Entity* e);
	ActionIDs GetCurrentActionID(Entity* e);
	int GetActionCount(Entity* e);

	std::list<Entity*> GetMinions(Entity* e);
};



	


