#pragma once
#include "Entity.hpp"

namespace Monster
{
	namespace Types
	{
		namespace Offsets
		{
			const UINT64 IdentifyingString = 0x00; //ptr
			const UINT64 IsSummoned = 0x0C;
			const UINT64 Armour = 0x0D;
			const UINT64 Evasion = 0x11;
			const UINT64 EnergyShield = 0x15;
			const UINT64 MovementSpeed = 0x19;
		}
	}

	namespace Varieties
	{
		namespace Offsets
		{
			const UINT64 IdentifyingString = 0x00; //ptr
			const UINT64 TypesPointer = 0x10; //ptr to above
			const UINT64 AttackDistanceMin = 0x20;
			const UINT64 AttackDistanceMax = 0x24;
			const UINT64 TotalMods = 0x40;
			const UINT64 ModsPtr = 0x48;
			const UINT64 MonsterName = 0xF4;
		}
	}

	namespace InternalStruct //0x18 reference below
	{
		namespace Offsets
		{
			const UINT64 UnkStructPtr = 0x08;
			const UINT64 VarietiesPtr = 0x18;
			const UINT64 Level = 0x20;
		}
	}

	const UINT64 HeaderOffset = 0x00;
	const UINT64 InternalPtrOffset = 0x18;

	int GetLevel(Entity* e);
	std::string GetName(Entity* e);
	bool IsSummoned(Entity* e);



}