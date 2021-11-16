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

	const UINT64 ActionOffset = 0x1A8;
	const UINT64 ActionIdOffset = 0x208;
	const UINT64 ActionCountOffset = 0x20A;
	const UINT64 AnimationId = 0x234;
	const UINT64 SkillsOffset = 0x690;
	const UINT64 VaalSkillsOffset = 0x6B0;

	bool IsAttacking(Entity* e);
	bool IsMoving(Entity* e);
	
	std::list<UINT16>* GetActorSkillList();
	ActionIDs GetCurrentActionID(Entity* e);
	int GetActionCount(Entity* e);
};



	


