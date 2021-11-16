#pragma once
#include "Entity.hpp"

namespace Targetable
{
	static const UINT64 TargetableOffset = 0x48;
	static const UINT64 HoveringOffset = 0x50;

	bool IsTargetable(Entity* e);
	bool IsMouseOverEntity(Entity* e);
};