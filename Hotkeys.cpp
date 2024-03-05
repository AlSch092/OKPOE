#include "Hotkeys.hpp"
#include "Offsets.hpp"
#include "Scripter.hpp"

extern AutoPlayer* g_Robot;
extern NetLogger* g_ProtectionServer;

void Hotkey::HandleKeypress()
{
	if (GetAsyncKeyState(VK_F1) & 0x01) //flasks
	{
		printf("F1 pressed..\n");
		
		if (g_Robot->UsingDynamiteHack)
		{
			printf("[OKPOE LOG] Dynamite Skills: OFF\n");
			g_Robot->UsingDynamiteHack = false;
		}
		else
		{
			g_Robot->UsingDynamiteHack = true;
			printf("[OKPOE LOG] Dynamite Skills: ON\n");
		}

	}
	else if (GetAsyncKeyState(VK_F2) & 0x01)
	{
		printf("F2 pressed..\n");
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Scripting::ExecuteLUA, 0, 0, 0);
	}
	else if (GetAsyncKeyState(VK_F3) & 0x01)
	{
		printf("F3 pressed..\n");
		UINT64 g_POEBase = (UINT64)GetModuleHandle(NULL);
		UINT64 PointerBase = (g_POEBase + g_ProtectionServer->Offsets[1]); // -> Addr1
		UINT64 PointerTwo = *(UINT64*)PointerBase + Offsets::Pointers::MaphackPtrOfs1;// Addr1 + 0x688 = Addr2
		UINT64 PointerThree = *(UINT64*)PointerTwo + Offsets::Pointers::RevealMap; // Addr2 + 58 -> fin
		*(UINT16*)PointerThree = 1;
	}
	else if (GetAsyncKeyState(VK_F4) & 0x01)
	{
		printf("F4 pressed..\n");

	}
	else if (GetAsyncKeyState(VK_F5) & 0x01)
	{
		printf("F5 pressed..\n");
		
		static bool spinner;

		UINT64 g_POEBase = (UINT64)GetModuleHandleA(NULL);

		if (spinner)
		{
			SetHook((g_POEBase + Offsets::Hacks::GlobalLights), CPUReduceHook); //fix this
			spinner = false;
		}
		else if (spinner == false)
		{
			RemoveHook(g_POEBase + Offsets::Hacks::GlobalLights, 10, (BYTE*)"\x49\x83\xC0\x04\x89\x41\x20\x49\x8B\xD2");
			spinner = true;
		}
	}
	else if (GetAsyncKeyState(VK_F6) & 0x01)
	{
		printf("F6 pressed..\n");

		static bool rspinner;

		UINT64 g_POEBase = (UINT64)GetModuleHandleA(NULL);

		if (rspinner)
		{
			if (g_Robot->haReduceRAM == NULL)
				g_Robot->haReduceRAM = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ReduceRAM, 0, 0, 0);
			rspinner = false;
		}
		else if (rspinner == false)
		{
			TerminateThread(g_Robot->haReduceRAM, 0);
			g_Robot->haReduceRAM = NULL;
			rspinner = true;
		}
		
	}
	else if (GetAsyncKeyState(VK_F7) & 0x01)
	{
		printf("F7 pressed..\n");
	}
	else if (GetAsyncKeyState(VK_F8) & 0x01)
	{
		printf("F8 pressed..\n");
	}
	else if (GetAsyncKeyState(VK_F9) & 0x01)
	{
		printf("F9 pressed..\n");
		PacketWriter* p = PacketBuilder::SwapHideout(0x11);
		if (GetSendClass() != NULL)
			SendPacket(GetSendClass(), (LPBYTE)p->GetBuffer(), p->GetSize());

		delete p;
	}
	else if (GetAsyncKeyState(VK_F10) & 0x01)
	{
		printf("F10 pressed..\n");
	}
	else if (GetAsyncKeyState(VK_F11) & 0x01)
	{
		printf("F11 pressed..\n");
	}
	else if (GetAsyncKeyState(VK_F12) & 0x01)
	{
		printf("F12 pressed..\n");
		ExitProcess(0);
	}
}
