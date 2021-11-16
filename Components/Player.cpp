#include "Player.hpp"

byte Player::GetPlayerLevel(Entity* e)
{
	if (e == NULL)
		return 0;

	byte Level = 0;
	UINT64 PlayerCompAddr = e->GetComponentAddress("Player");

	if (PlayerCompAddr != 0)
	{
		PlayerCompAddr = PlayerCompAddr + Player::levelOffset;
		Level = *(byte*)PlayerCompAddr;
	}

	return Level;
}

std::wstring Player::GetPlayerName(Entity* e)
{
	if (e == NULL)
		return NULL;

	std::wstring name;
	wchar_t CharName[255];
	UINT64 PlayerCompAddr = e->GetComponentAddress("Player");

	if (PlayerCompAddr != NULL)
	{
		printf("Grabbing player name: %llX...\n", PlayerCompAddr);

		try
		{
			PlayerCompAddr = PlayerCompAddr + Player::nameOffset;
			PlayerCompAddr = DereferenceSafe<UINT64>(PlayerCompAddr);

			if (PlayerCompAddr != NULL)
			{
				wcscpy(CharName, (const wchar_t*)PlayerCompAddr);
				name = std::wstring(CharName);
			}
			else
				return NULL;
		}
		catch (...) { return NULL; }

	}

	return name;
}

std::wstring Player::GetPlayerClass(Entity* e)
{
	if (e == NULL)
		return 0;

	wchar_t wclass[25];
	std::wstring playerClass;
	UINT64 PlayerCompAddr = e->GetComponentAddress("Player");

	if (PlayerCompAddr != 0)
	{
		PlayerCompAddr = PlayerCompAddr + Player::classOffset;
		PlayerCompAddr = *(UINT64*)PlayerCompAddr;

		//grab and return name ptr?
		wcscpy(wclass, (const wchar_t*)PlayerCompAddr);
		playerClass = std::wstring(wclass);
	}
	
	return playerClass;
}

long Player::GetPlayerExperience(Entity* e)
{
	if (e == NULL)
		return 0;

	long exp = 0;
	UINT64 PlayerCompAddr = e->GetComponentAddress("Player");

	if (PlayerCompAddr != 0)
	{
		PlayerCompAddr = PlayerCompAddr + Player::experienceOffset;
		exp = *(long*)PlayerCompAddr;
	}

	return exp;
}