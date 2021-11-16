#pragma once
#include "Entity.hpp"

namespace Flask 
{
	CONST UINT64 InternalEntOffset = 0x28;
	CONST UINT64 InternalBaseOffset = 0x18; //offset from InternalEnt
	CONST UINT64 LifePerUseOffset = 0x4;
	CONST UINT64 ManaPerUseOffset = 0x0C;
	CONST UINT64 DurationOffset = 0x14; //offsets from InternalBase

	unsigned int GetLifePerUsage(Entity* e);
	unsigned int GetManaPerUsage(Entity* e);
	unsigned int GetUsageDuration(Entity* e);
}