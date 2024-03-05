#pragma once
#include "Entity.hpp"

namespace Targetable
{
	static const UINT64 TargetableOffset = 0x48; //80 7F 48 00 74 21 80 7F 50 00 75 1b 80 7f 4d 00 74 15
	static const UINT64 HoveringOffset = 0x4A;

	bool IsTargetable(Entity* e);
	bool IsMouseOverEntity(Entity* e);
};