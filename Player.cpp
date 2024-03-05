#include "Player.hpp"

byte Player::GetPlayerLevel(Entity* e)
{
	if (e == NULL)
		return 0;

	byte Level = 0;
	UINT64 PlayerCompAddr = e->GetComponentAddress("Player");

	if (PlayerCompAddr != 0)
	{
		PlayerCompAddr = DereferenceSafe<byte>(PlayerCompAddr + Player::Offsets::level);
	}

	return Level;
}

wchar_t* Player::GetPlayerName(Entity* e) //this crashes often...
{
	if (e == NULL)
		return NULL;

	wchar_t name[100] = { 0 };
	UINT64 PlayerCompAddr = e->GetComponentAddress("Player");

	wchar_t* strPtr = NULL;

	if (PlayerCompAddr > NULL)
	{
		//printf("Grabbing player name: %llX...\n", PlayerCompAddr);

		UINT64 PlayerNameAddr = PlayerCompAddr + Player::Offsets::name;
		
		if (PlayerNameAddr != NULL)
		{	
			//__try
			//{
				if (*(UINT64*)PlayerNameAddr > 0x010000000000 && *(UINT64*)PlayerNameAddr < 0x040000000000)
				{
					PlayerNameAddr = DereferenceSafe<UINT64>(PlayerNameAddr);

					wchar_t* strPtr = (wchar_t*)PlayerNameAddr;

					if (wcslen(strPtr) > 0)
					{
						wcscpy(&name[0], strPtr);
						//wprintf(L"GetPlayerName: %s\n", name);
						return strPtr;
					}
				}
				else
				{
					wchar_t* strPtr = (wchar_t*)PlayerNameAddr;

					if (wcslen(strPtr) > 0)
					{
						wcscpy(&name[0], strPtr);
						//wprintf(L"GetPlayerName: %s\n", name);
						return strPtr;
					}
				}
			//}
			//__except (EXCEPTION_EXECUTE_HANDLER)
			//{
			//	return NULL;
			//}
			
		}
		else
		{
			//printf("PlayerNameAddr was NULL!\n");
			return NULL;
		}
	}
	else
		printf("Entity::Player was NULL. No component.\n");

	return strPtr;
}

//Full job name in UNICODE ex: L"Ranger"
byte Player::GetPlayerClass(Entity* e)
{
	if (e == NULL)
		return 0;

	wchar_t wclass[25];
	std::wstring pClass;

	UINT64 PlayerCompAddr = e->GetComponentAddress("Player");

	if (PlayerCompAddr != 0)
	{
		PlayerCompAddr = PlayerCompAddr + Player::Offsets::_class;
		
		if (PlayerCompAddr != NULL)
			PlayerCompAddr = *(UINT64*)PlayerCompAddr;
		else
			return 0;

		PlayerCompAddr += 0x10;

		if (PlayerCompAddr != NULL)
			PlayerCompAddr = *(UINT64*)PlayerCompAddr;

		//grab and return name ptr?
		wcscpy(wclass, (const wchar_t*)PlayerCompAddr);
		pClass = std::wstring(wclass);
	}

	int JobClass = 0;

	if (pClass == L"Deadeye")
	{
		JobClass = 7;
	}
	else if (pClass == L"Ranger")
	{
		JobClass = 1;
	}
	else if (pClass == L"Raider")
	{
		JobClass = 8;
	}
	else if (pClass == L"Pathfinder")
	{
		JobClass = 9;
	}
	else if (pClass == L"Marauder")
	{
		JobClass = 0;
	}
	else if (pClass == L"Berserker")
	{
		JobClass = 10;
	}
	else if (pClass == L"Chieftain")
	{
		JobClass = 11;
	}
	else if (pClass == L"Juggernaut")
	{
		JobClass = 12;
	}
	else if (pClass == L"Witch")
	{
		JobClass = 2;
	}
	else if (pClass == L"Necromancer")
	{
		JobClass = 13;
	}
	else if (pClass == L"Occultist")
	{
		JobClass = 14;
	}
	else if (pClass == L"Elementalist")
	{
		JobClass = 15;
	}
	else if (pClass == L"Scion")
	{
		JobClass = 6;
	}
	else if (pClass == L"Ascendant")
	{
		JobClass = 16;
	}
	else if (pClass == L"Templar")
	{
		JobClass = 3;
	}
	else if (pClass == L"Inquisitor")
	{
		JobClass = 17;
	}
	else if (pClass == L"Hierophant")
	{
		JobClass = 18;
	}
	else if (pClass == L"Guardian")
	{
		JobClass = 19;
	}
	else if (pClass == L"Shadow")
	{
		JobClass = 4;
	}
	else if (pClass == L"Assassin")
	{
		JobClass = 20;
	}
	else if (pClass == L"Saboteur")
	{
		JobClass = 21;
	}
	else if (pClass == L"Trickster")
	{
		JobClass = 22;
	}
	else if (pClass == L"Duelist")
	{
		JobClass = 5;
	}
	else if (pClass == L"Slayer")
	{
		JobClass = 23;
	}
	else if (pClass == L"Gladiator")
	{
		JobClass = 24;
	}
	else if (pClass == L"Champion")
	{
		JobClass = 25;
	}
	
	return JobClass;
}

long Player::GetPlayerExperience(Entity* e)
{
	if (e == NULL)
		return 0;

	long exp = 0;
	UINT64 PlayerCompAddr = e->GetComponentAddress("Player");

	if (PlayerCompAddr != 0)
	{
		PlayerCompAddr = PlayerCompAddr + Player::Offsets::experience;
		exp = DereferenceSafe<long>(PlayerCompAddr);
	}

	return exp;
}