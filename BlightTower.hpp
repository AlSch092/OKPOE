#pragma once
#include "Entity.hpp"

namespace BlightTower
{
	namespace Offsets
	{
		const UINT64 TowerType = 0x264; //get this
		const UINT64 TowerTier = 0x268;
	}


	enum Towers
	{
		None,
		Summon,
		Ice,
		Fire,
		Empower,
		Physical,
		Lightning,
		Chaos
	};

	Towers GetTowerType(Entity* e);
	int GetTowerTier(Entity* e);
}