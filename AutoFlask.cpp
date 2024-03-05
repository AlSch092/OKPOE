#include "AutoFlask.hpp"

extern AutoPlayer* g_Robot;

void AutoFlask::UseFlask(int index)
{
	UINT64 SendClass = GetSendClass();
	if (SendClass != 0 && SendClass != -1)
	{
		PacketWriter* p = PacketBuilder::ConsumeFlask(index);
		PacketBuilder::Send(p);
	}
}

void AutoFlask::AutoFlasker(LPVOID param) //todo: test
{
	AutoFlask* klass = reinterpret_cast<AutoFlask*>(param);
	klass->isFlasking = true;
	klass->FillFlaskList();
	
	int HealthFlaskSlot = 0; //if not detected..
	int ManaFlaskSlot = 1;
	int SpeedFlaskSlot = 2;

	if (g_Robot->FlaskList.size() == 0) //inventory detected flasks
	{
		//read flasks from inv
		g_Robot->FlaskList = Inventory::GetFlasks(false);

		if (g_Robot->FlaskList.size() == 0)
		{
			printf("No flasks detected, defaulting to slots 0, 1.\n");
			HealthFlaskSlot = 0;
			ManaFlaskSlot = 1;
		}
	}
	else
	{
		HealthFlaskSlot = klass->HealthFlask->CellX;
		ManaFlaskSlot = klass->ManaFlask->CellX;
		SpeedFlaskSlot = klass->SpeedFlask->CellX;
	}

	DWORD dwTime = GetTickCount();

	while (klass->isFlasking)
	{
		if (!g_Robot->Attacker->IsBusy && !g_Robot->Disconnected)
		{
			Entity* player = g_Robot->GetLocalPlayer();
			UINT CurrentHP = Life::GetEntityHP(player);
			UINT CurrentMP = Life::GetEntityMana(player);

			UINT MaxHP = Life::GetEntityMaxHP(player);
			UINT MaxMP = Life::GetEntityMaxHP(player);

			delete player;

			if (g_Robot->UsingFlasksAt50Percent)
			{
				UINT FiftyPercentHP = MaxHP / 2;
				UINT FiftyPercentMP = MaxMP / 2;

				if (CurrentHP < FiftyPercentHP)
				{
					FileIO::Log("[AUTO FLASK] Using HP flask!\n");
					klass->UseFlask(HealthFlaskSlot); //change 0 to dynamic reading
					Sleep(2500);
				}

				if (CurrentMP < FiftyPercentMP)
				{
					FileIO::Log("[AUTO FLASK] Using MP flask!\n");
					klass->UseFlask(ManaFlaskSlot);
					Sleep(2500);
				}

			}
			else //todo , change frm g_Robot to this classes' vars
			{
				if (CurrentHP <= g_Robot->FlaskOnHitpoints)
				{
					FileIO::Log("[AUTO FLASK] Using HP flask!\n");
					klass->UseFlask(HealthFlaskSlot); //change 0 to dynamic reading
					Sleep(2500);

				}

				if (CurrentMP <= g_Robot->FlaskOnMana)
				{
					FileIO::Log("[AUTO FLASK] Using MP flask!\n");
					klass->UseFlask(ManaFlaskSlot);
					Sleep(2500);
				}
			}	

			if (GetTickCount() - dwTime >= 10000)
			{
				dwTime = GetTickCount();
				klass->UseFlask(2);
				klass->UseFlask(3);
				klass->UseFlask(4);
			}
		}

		Sleep(50);
	}
}

void AutoFlask::FillFlaskList()
{
	this->Flasks = Inventory::GetFlasks(false);

	int count = 1;

	byte bHealthSlot = 0;
	byte bManaSlot = 1;
	byte SpeedSlot = 2;

	for each (Item* i in this->Flasks)
	{
		wprintf(L"Flask %d: %s\n", count, i->FullName.c_str());
		count++;

		if (wcsstr(i->FullName.c_str(), L"Life Flask") != NULL)
		{
			bHealthSlot = i->CellX;
			printf("Health flask at slot %d\n", bHealthSlot);
			this->HealthFlask = i;
		}
		else if (wcsstr(i->FullName.c_str(), L"Mana Flask") != NULL)
		{
			bManaSlot = i->CellX;
			printf("Mana flask at slot %d\n", bManaSlot);
			this->ManaFlask = i;
		}
		else if (wcsstr(i->FullName.c_str(), L"Quicksilver Flask") != NULL)
		{
			SpeedSlot = i->CellX;
			printf("Speed flask at slot %d\n", SpeedSlot);
			this->SpeedFlask = i;
		}
	}
}