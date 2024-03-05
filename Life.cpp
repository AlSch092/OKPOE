#include "Life.hpp"

namespace Life
{
	UINT Life::GetEntityHP(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");
		UINT CurrentHP = DereferenceSafe<UINT>(LifeAddr + Life::Offsets::CurHP);

		if (CurrentHP == NULL) //probably replace with try catch
			return -1;

		return CurrentHP;
	}

	UINT Life::GetEntityES(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT CurrentShield = DereferenceSafe<UINT>(LifeAddr + Life::Offsets::CurES);

		if (CurrentShield == NULL) //probably replace with try catch
			return -1;

		return CurrentShield;
	}

	UINT Life::GetEntityMana(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT CurrentMP = DereferenceSafe<UINT>(LifeAddr + Life::Offsets::CurMana);

		if (CurrentMP != NULL)
			return CurrentMP;

		return -1;
	}

	UINT Life::GetEntityMaxHP(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT MaxHP = DereferenceSafe<UINT>(LifeAddr + Life::Offsets::MaxHP);

		if (MaxHP == NULL)
			return -1;

		return MaxHP;
	}

	UINT Life::GetEntityMaxMana(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT MaxMana = DereferenceSafe<UINT>(LifeAddr + Life::Offsets::MaxMana);

		if (MaxMana == NULL)
			return -1;

		return MaxMana;
	}

	UINT Life::GetEntityMaxES(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT MaxShield = DereferenceSafe<UINT>(LifeAddr + Life::Offsets::MaxES);

		if (MaxShield == NULL)
			return -1;

		return MaxShield;
	}

	UINT Life::GetEntityHPRegen(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT HPRegen = DereferenceSafe<UINT>(LifeAddr + Life::Offsets::Regen);

		if (HPRegen == NULL)
			return -1;

		return HPRegen;
	}

	UINT Life::GetEntityManaRegen(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT ManaRegen = DereferenceSafe<UINT>(LifeAddr + Life::Offsets::ManaRegen);

		if (ManaRegen == NULL)
			return -1;

		return ManaRegen;
	}

	UINT Life::GetEntityReservedManaPercent(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT ReservedMP = DereferenceSafe<UINT>(LifeAddr + Life::Offsets::ReservedPercentMana);

		if (ReservedMP == NULL)
			return -1;

		return ReservedMP;
	}

	UINT Life::GetEntityReservedHPPercent(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT ReservedHP = DereferenceSafe<UINT>(LifeAddr + Life::Offsets::ReservedPercentHP);

		if (ReservedHP == NULL)
			return -1;

		return ReservedHP;
	}

}