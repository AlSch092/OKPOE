#include "MinimapIcon.hpp"
#include "FileIO.hpp"

void MinimapIcon::MapIconsHook(UINT64 MapIconStructAddr)
{
	UINT64 NextAddr = DereferenceSafe<UINT64>(MapIconStructAddr);
	UINT64 IconName = DereferenceSafe<UINT64>(NextAddr); //kek

	if (NextAddr != NULL)
	{
		if (wcscmp((wchar_t*)IconName, L"RitualRune") == 0) //RitualRuneFinished alternatively
		{
			FileIO::WriteColorTextConsole("Ritual encounter detected in map!\n", FOREGROUND_GREEN);
		}
		else if (wcscmp((wchar_t*)IconName, L"BlightCore") == 0)
		{
			FileIO::WriteColorTextConsole("Blight encounter detected in map!\n", FOREGROUND_GREEN);
		}
		else if (wcscmp((wchar_t*)IconName, L"BetryalIconCart") == 0)
		{
			FileIO::WriteColorTextConsole("Betryal Encounter (cart) nearby, be careful!\n", FOREGROUND_GREEN);
		}
		else if (wcscmp((wchar_t*)IconName, L"AfflictionInitiator") == 0)
		{
			FileIO::WriteColorTextConsole("Affliction/Delirium encounter detected nearby!\n", FOREGROUND_GREEN);
		}
		else if (wcscmp((wchar_t*)IconName, L"DelveMineralVein") == 0)
		{
			FileIO::WriteColorTextConsole("Niko sulphite detected nearby!\n", FOREGROUND_GREEN);
		}
		else if (wcscmp((wchar_t*)IconName, L"VaalSideArea") == 0)
		{
			FileIO::WriteColorTextConsole("Vaal side area nearby.\n", FOREGROUND_GREEN);
		}
		else if (wcscmp((wchar_t*)IconName, L"RewardBlight") == 0) //RewardAbyss, RewardGeneric
		{
			FileIO::WriteColorTextConsole("Blight map rewards present!\n", FOREGROUND_GREEN);
		}
		//MetamorphosisBoss    VaalSideArea
		else
			wprintf(L"[DEBUG] Icon/Label Found: %s\n", (wchar_t*)IconName);
	}

}