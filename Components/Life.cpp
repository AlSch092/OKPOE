#include "Life.hpp"

namespace Life
{
	UINT Life::GetEntityHP(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		printf("Life addr: %llX\n", LifeAddr);

		UINT CurrentHP = DereferenceSafe<UINT>(LifeAddr + Life::CurHP);
		printf("[DEBUG] Hp: %d\n", CurrentHP);

		if (CurrentHP == NULL) //probably replace with try catch
			return -1;

		return CurrentHP;
	}

	UINT Life::GetEntityES(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT CurrentShield = DereferenceSafe<UINT>(LifeAddr + Life::CurES);

		if (CurrentShield == NULL) //probably replace with try catch
			return -1;

		return CurrentShield;
	}

	UINT Life::GetEntityMana(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT CurrentMP = DereferenceSafe<UINT>(LifeAddr + Life::CurMana);
		printf("[DEBUG] Mp: %d\n", CurrentMP);
		if (CurrentMP != NULL)
			return CurrentMP;

		return -1;
	}

	UINT Life::GetEntityMaxHP(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT MaxHP = DereferenceSafe<UINT>(LifeAddr + Life::MaxHP);

		if (MaxHP == NULL)
			return -1;

		return MaxHP;
	}

	UINT Life::GetEntityMaxMana(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT MaxMana = DereferenceSafe<UINT>(LifeAddr + Life::MaxMana);

		if (MaxMana == NULL)
			return -1;

		return MaxMana;
	}

	UINT Life::GetEntityMaxES(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT MaxShield = DereferenceSafe<UINT>(LifeAddr + Life::MaxES);

		if (MaxShield == NULL)
			return -1;

		return MaxShield;
	}

	UINT Life::GetEntityHPRegen(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT HPRegen = DereferenceSafe<UINT>(LifeAddr + Life::Regen);

		if (HPRegen == NULL)
			return -1;

		return HPRegen;
	}

	UINT Life::GetEntityManaRegen(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT ManaRegen = DereferenceSafe<UINT>(LifeAddr + Life::ManaRegen);

		if (ManaRegen == NULL)
			return -1;

		return ManaRegen;
	}

	UINT Life::GetEntityReservedManaPercent(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT ReservedMP = DereferenceSafe<UINT>(LifeAddr + Life::ReservedPercentMana);

		if (ReservedMP == NULL)
			return -1;

		return ReservedMP;
	}

	UINT Life::GetEntityReservedHPPercent(Entity* e)
	{
		UINT64 LifeAddr = e->GetComponentAddress("Life");

		UINT ReservedHP = DereferenceSafe<UINT>(LifeAddr + Life::ReservedPercentHP);

		if (ReservedHP == NULL)
			return -1;

		return ReservedHP;
	}

}