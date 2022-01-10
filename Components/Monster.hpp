/* ----------------------------------------------
OKPOE Components: Monster
Jan. 9 2022
------------------------------------------------ /*/

#pragma once
#include "Entity.hpp"

namespace Monster
{
	namespace Types
	{
		const UINT64 IdentifyingStringOffset = 0x00; //ptr
		const UINT64 IsSummonedOffset = 0x0C;
		const UINT64 ArmourOffset = 0x0D;
		const UINT64 EvasionOffset = 0x11;
		const UINT64 EnergyShieldOffset = 0x15;
		const UINT64 MovementSpeedOffset = 0x19;
	}

	namespace Varieties //exileAPI for this, credits
	{
		const UINT64 IdentifyingStringOffset = 0x00; //ptr
		const UINT64 MonsterTypeOffset = 0x10; //ptr to above
		const UINT64 AttackDistanceMinOffset = 0x20;
		const UINT64 AttackDistanceMaxOffset = 0x24;
		const UINT64 TotalModsOffset = 0x40;
		const UINT64 ModsPtrOffset = 0x48;
		const UINT64 MonsterNameOffset = 0xF4;
	}

	namespace InternalStruct //0x18 reference below
	{
		const UINT64 UnkStructPtrOffset = 0x08;
		const UINT64 VarietiesPtrOffset = 0x18;
		const UINT64 LevelOffset = 0x20;
	}

	const UINT64 HeaderOffset = 0x00;
	const UINT64 InternalPtrOffset = 0x18;

	int GetLevel(Entity* e);
	std::string GetName(Entity* e);
	bool IsSummoned(Entity* e);

}
