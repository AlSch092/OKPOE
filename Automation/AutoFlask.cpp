#include "AutoFlask.hpp"

void AutoFlask::UseFlask(int index)
{
	UINT64 SendClass = GetSendClass();
	if (SendClass != 0 && SendClass != -1)
	{
		PacketWriter* p = PacketBuilder::ConsumeFlask(index);
		PacketBuilder::Send(p);
	}
}

void AutoFlask::BeginFlasker()
{
	this->isFlasking = true;
	this->FlaskerThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&AutoFlask::AutoFlasker, this, 0, 0);
}

void AutoFlask::AutoFlasker(LPVOID param) //todo: test
{
	AutoFlask* klass = reinterpret_cast<AutoFlask*>(param);
	
	klass->FillFlaskList();
	
	int HealthFlaskSlot = 0;
	int ManaFlaskSlot = 1;
	int SpeedFlaskSlot = 2;

	if (klass->Flasks.size() > 0)
	{
		HealthFlaskSlot = klass->HealthFlask->CellX;
		ManaFlaskSlot = klass->ManaFlask->CellX;
		SpeedFlaskSlot = klass->SpeedFlask->CellX;
	}
	else
	{
		printf("No flasks detected, defaulting to slots 0, 1.\n");
	}

	while (klass->isFlasking)
	{

			UINT CurrentHP = Life::GetEntityHP(AutoPlayer::GetLocalPlayer());
			UINT CurrentMP = Life::GetEntityMana(AutoPlayer::GetLocalPlayer());

			UINT MaxHP = Life::GetEntityMaxHP(AutoPlayer::GetLocalPlayer());
			UINT MaxMP = Life::GetEntityMaxHP(AutoPlayer::GetLocalPlayer());

			if (Robot->UsingFlasksAt50Percent)
			{
				UINT FiftyPercentHP = MaxHP / 2;
				UINT FiftyPercentMP = MaxMP / 2;


				if (CurrentHP <= klass->FlaskOnHP)
				{
					klass->UseFlask(HealthFlaskSlot);
					Sleep(100);
				}
	
				if (CurrentMP <= klass->FlaskOnMana)
				{
					klass->UseFlask(ManaFlaskSlot);
					Sleep(100);
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
		count++;

		if (wcsstr(i->FullName.c_str(), L"Life Flask") != NULL)
		{
			bHealthSlot = i->CellX;
			this->HealthFlask = i;
		}
		else if (wcsstr(i->FullName.c_str(), L"Mana Flask") != NULL)
		{
			bManaSlot = i->CellX;
			this->ManaFlask = i;
		}
		else if (wcsstr(i->FullName.c_str(), L"Quicksilver Flask") != NULL)
		{
			SpeedSlot = i->CellX;
			this->SpeedFlask = i;
		}
	}
}
