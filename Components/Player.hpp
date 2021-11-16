#pragma once
#include "Entity.hpp"

namespace Player
{
	static const UINT64 classOffset = 0x158;
	static const UINT64 nameOffset = 0x160;
	static const UINT64 experienceOffset = 0x184;
	static const UINT64 levelOffset = 0x196;

	std::wstring GetPlayerName(Entity* e);
	std::wstring GetPlayerClass(Entity* e);
	long GetPlayerExperience(Entity* e);
	byte GetPlayerLevel(Entity* e);
}
