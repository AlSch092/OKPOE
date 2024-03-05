#pragma once
#include "Entity.hpp"

namespace Player
{
	namespace Offsets
	{
		static const UINT64 _class = 0x158;
		static const UINT64 name = 0x160;
		static const UINT64 experience = 0x184;
		static const UINT64 level = 0x1A0; //needs updating
	}

	wchar_t* GetPlayerName(Entity* e);
	byte GetPlayerClass(Entity* e);
	long GetPlayerExperience(Entity* e);
	byte GetPlayerLevel(Entity* e);
}
