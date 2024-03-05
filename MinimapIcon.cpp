#include "MinimapIcon.hpp"
#include "FileIO.hpp"

UINT64 CompareAddr = 0;
void MinimapIcon::MapIconsHook(UINT64 MapIconStructAddr)
{
	UINT64 NextAddr = DereferenceSafe<UINT64>(MapIconStructAddr);
	UINT64 IconName = DereferenceSafe<UINT64>(NextAddr); //kek

	if (CompareAddr == MapIconStructAddr)
	{
		return;
	}

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
		else if (wcscmp((wchar_t*)IconName, L"Expedition") == 0) //RewardAbyss, RewardGeneric
		{
			FileIO::WriteColorTextConsole("Expedition event present!\n", FOREGROUND_GREEN);
		}
		else
			wprintf(L"Icon: %s\n", (wchar_t*)IconName);
		
		CompareAddr = MapIconStructAddr;
	}

}

bool MinimapIcon::IsIconHidden(Entity* e)
{
	UINT64 addr = e->GetComponentAddress("MinimapIcon");

	printf("addr: %llX\n", addr);

	byte isHidden = DereferenceSafe<byte>(addr + MinimapIcon::Offsets::IsHidden);
	
	printf("[DEBUG] isHidden: %d\n", isHidden);

	return (bool)isHidden;
}

void MinimapIcon::SetIconVisibility(Entity* e, bool visible)
{
	UINT64 addr = e->GetComponentAddress("MinimapIcon");

	printf("addr: %llX\n", addr);

	WritePointer(addr, MinimapIcon::Offsets::IsHidden, &visible);

	printf("[DEBUG] Wrote minimapIcon visibility.\n");
}

std::wstring MinimapIcon::GetIconLabel(Entity* e)
{
	std::wstring name = NULL;

	if (e == NULL)
		return name;


	UINT64 addr = e->GetComponentAddress("MinimapIcon");
	UINT64 internalStruct = DereferenceSafe<UINT64>(addr + MinimapIcon::Offsets::IconInternalPtr);

	if (internalStruct)
	{
		UINT64 namePtr = DereferenceSafe<UINT64>(internalStruct + MinimapIcon::MinimapIconInternal::Offsets::IconNamePtr);

		if (namePtr != NULL)
		{
			name = std::wstring(reinterpret_cast<wchar_t*>(namePtr));
			wprintf(L"Minimap icon name: %s\n", name.c_str());
		}
	}

	return name;
}