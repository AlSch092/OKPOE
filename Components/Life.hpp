#pragma once
#include "Entity.hpp"

namespace Life
{
	const UINT64 ManaRegen = 0x1B0;
	const UINT64 MaxMana = 0x1B4;
	const UINT64 CurMana = 0x1B8;
	const UINT64 ReservedPercentMana = 0x1C0;

	const UINT64 MaxES = 0x1EC;
	const UINT64 CurES = 0x1F0;

	const UINT64 Regen = 0x248;
	const UINT64 MaxHP = 0x24C;
	const UINT64 CurHP = 0x250;
	const UINT64 ReservedPercentHP = 0x258;

	UINT GetEntityHP(Entity* e);
	UINT GetEntityES(Entity* e);
	UINT GetEntityMana(Entity* e);

	UINT GetEntityMaxHP(Entity* e);
	UINT GetEntityMaxMana(Entity* e);
	UINT GetEntityMaxES(Entity* e);

	UINT GetEntityHPRegen(Entity* e);
	UINT GetEntityManaRegen(Entity* e);
	UINT GetEntityReservedManaPercent(Entity* e);
	UINT GetEntityReservedHPPercent(Entity* e);

}