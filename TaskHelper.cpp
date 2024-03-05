#include "TaskHelper.hpp"

extern AutoPlayer* g_Robot;

bool TaskHelper::ExchangeDivinationCards(AutoPlayer* g_Robot)
{
	if (this->GetDivinationNPCID())
	{
		g_Robot->Interaction(this->GetDivinationNPCID(), Input::InputIds::INTERACTION);

		Sleep(3000);

		SelectNPCDialog(2);

		Sleep(1000);

		g_Robot->NormalInv->GetInventoryItems();

		if (g_Robot->NormalInv->Items.size() > 0)
		{
			for each(Item* i in g_Robot->NormalInv->Items)
			{
				wchar_t* path = i->ItemEnt->GetFilePathFromMemory();
				
				if (wcsstr(path, L"Divination") != NULL)
				{
					//send packet to exchange
				}

				delete path;
			}
		}
	}

	return true;
}

void TaskHelper::SelectNPCDialog(byte index)
{
	PacketWriter* p = PacketBuilder::SelectNPCDialog(index);

	if (p)
	{
		PacketBuilder::Send(p);
		printf("Selected NPC Dialog: %d\n", index);
	}

}

void TaskHelper::AutoClickSwitches()
{
	bool searching = true;

	while (searching)
	{
		Vector2 pPos = g_Robot->GetLocalPlayer()->GetVector2();

		for each (Entity * e in g_Robot->EntityList)
		{
			if (wcsstr(L"Switch", e->GetFilePathFromMemory()) != NULL) //fix string
			{
				//how to check if switch is already toggled? IsOpened?

				if (Targetable::IsTargetable(e) && !Chest::IsOpened(e)) 
				{
					Vector2 ePos = e->GetVector2();

					if (Distances::GetDistanceBetweenObjects(pPos, ePos) < 200)
					{
						g_Robot->Interaction(e->GetUniqueID(), Input::INTERACTION);

						Vector2 pPos_After = g_Robot->GetLocalPlayer()->GetVector2();

						if (pPos.X == pPos_After.X && pPos.Y == pPos_After.Y) //didnt move after interacting, unreachable object?
						{

						}
					}
				}
			}
		}
	}

}