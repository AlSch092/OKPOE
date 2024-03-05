#pragma once
#include "Entity.hpp"

namespace Life
{
	namespace Offsets
	{
		const UINT64 ManaRegen = 0x200; //linear +4
		const UINT64 MaxMana = ManaRegen + 4;
		const UINT64 CurMana = MaxMana + 4;
		const UINT64 ReservedMana = CurMana + 4;
		const UINT64 ReservedPercentMana = ReservedMana + 4;

		const UINT64 MaxES = 0x22C;
		const UINT64 CurES = MaxES + 4; //todo: update this

		const UINT64 Regen = 0x250;
		const UINT64 MaxHP = 0x1A4; //48 63 88 ? ? ? ? 48 63 90 ? ? ? ? 3b d1 7e 07 b8 64 00 00 00
		const UINT64 CurHP = MaxHP + 4;
		const UINT64 ReservedHP = CurHP + 4; //update this
		const UINT64 ReservedPercentHP = ReservedHP + 4;
	}

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