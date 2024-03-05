#include "BlightTower.hpp"

BlightTower::Towers BlightTower::GetTowerType(Entity* e)
{
	UINT64 BlightTowerComponentAddr = e->GetComponentAddress("BlightTower");
	BlightTower::Towers type = None;

	if (BlightTowerComponentAddr == NULL)
	{
		return type;
	}

	type = DereferenceSafe<BlightTower::Towers>(BlightTowerComponentAddr + BlightTower::Offsets::TowerType);

	return type;
}

int BlightTower::GetTowerTier(Entity* e)
{


	return 0;
}