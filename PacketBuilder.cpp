#include "PacketBuilder.hpp"
#include "Packets.hpp"
#include "Pointer.hpp"
#include "AutoPlayer.hpp"

extern AutoPlayer* g_Robot;

PacketWriter* PacketBuilder::ConsumeFlask(BYTE Slot)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::Flask);
	p->WriteZeros(3);
	p->Write<BYTE>(Slot);
	return p;
}

PacketWriter* PacketBuilder::Action(UINT16 SkillID, UINT32 EntityID, INT32 x, INT32 y)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PlayerInput);
	p->Write<DWORD>(PacketHelper::changeEndianness32(x));
	p->Write<DWORD>(PacketHelper::changeEndianness32(y));
	p->Write<UINT16>(PacketHelper::changeEndianness16(SkillID));
	p->Write<BYTE>(0x04);
	p->Write<BYTE>(0x08);
	p->Write<BYTE>(0x00);
	return p;
}

PacketWriter* PacketBuilder::EndAction()
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PlayerStopInput);
	return p;
}

PacketWriter* PacketBuilder::EntityInteraction(uint32_t id, uint16_t interactionSkill)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::EntityInteraction);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(id));
	p->Write<uint16_t>(PacketHelper::changeEndianness16(interactionSkill));
	p->Write<BYTE>(0x04);
	p->Write<BYTE>(0x08);
	p->Write<BYTE>(0x00);
	return p;
}

PacketWriter* PacketBuilder::EnterPlayerHideout(string playerName)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::EnterPlayerHideout);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(strlen(playerName.c_str())));
	p->WriteString(playerName);
	p->WriteZeros(2);
	p->Write<BYTE>(0x3B);
	return p;
}

PacketWriter* PacketBuilder::SwapHideout(byte Hideout)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::ChangeHideout);
	p->Write<byte>(0);
	p->Write<byte>(Hideout);
	return p;
}

PacketWriter* PacketBuilder::MoveToAzuriteMine(UINT32 EntityID)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::ToAzuriteMines);
	p->Write<UINT32>(EntityID); //always waypoint ID in our case/normal case
	return p;
}

PacketWriter* PacketBuilder::EnterDelveNode(UINT32 HorizontalDepth, UINT32 VerticalDepth, UINT32 HorizontalGridPosition, UINT32 VerticalGridPosition)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::StartDelveInstance);
	p->Write<USHORT>(1);
	p->Write<UINT32>(PacketHelper::changeEndianness32(HorizontalDepth));
	p->Write<UINT32>(PacketHelper::changeEndianness32(VerticalDepth));
	p->Write<UINT32>(PacketHelper::changeEndianness32(HorizontalGridPosition));
	p->Write<UINT32>(PacketHelper::changeEndianness32(VerticalGridPosition));
	return p;
}

PacketWriter* PacketBuilder::StartDelveInstance(uint32_t nNodes, uint32_t* pathways)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::StartDelveInstance);
	p->Write<USHORT>(nNodes);

	for (int i = 0; i < nNodes; i++)
	{
		p->Write<UINT32>(PacketHelper::changeEndianness32(pathways[0 * nNodes]));
		p->Write<UINT32>(PacketHelper::changeEndianness32(pathways[1 * nNodes]));
		p->Write<UINT32>(PacketHelper::changeEndianness32(pathways[2 * nNodes]));
		p->Write<UINT32>(PacketHelper::changeEndianness32(pathways[3 * nNodes]));
	}

	return p;
}

PacketWriter* PacketBuilder::Revive(BOOL ReviveInTown)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::ReviveCharacter);
	p->Write<BYTE>(ReviveInTown);
	return p;
}

PacketWriter* PacketBuilder::ChangeAscendency(BYTE JobClassID)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::AscendCharacter);
	p->Write<BYTE>(JobClassID);
	return p;
}


PacketWriter* PacketBuilder::JoinInstance(BYTE InstanceListNum)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::JoinInstance);
	p->Write<BYTE>(InstanceListNum); //0xFF = new instance
	return p;
}


PacketWriter* PacketBuilder::CreateBlightTower(uint32_t id, uint32_t type)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::BlightTower);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(id));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(type));
	return p;
}

PacketWriter* PacketBuilder::ExitToCharScreen()
{
	PacketWriter* p = new PacketWriter(SendOpcodes::ExitToCharacterScreen);
	return p;
}

PacketWriter* PacketBuilder::SelectCharacter(BYTE Index)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::SelectCharacter);
	p->Write<DWORD>(0);
	p->Write<BYTE>(Index);
	return p;
}

PacketWriter* PacketBuilder::ChainedAction(INT32 x, INT32 y)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PlayerInputContinuous);
	p->Write<UINT32>(PacketHelper::changeEndianness32(x));
	p->Write<UINT32>(PacketHelper::changeEndianness32(y));
	return p;
}

PacketWriter* PacketBuilder::TradePlayer(uint32_t PlayerId)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::TradePlayer);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(PlayerId));
	return p;
}

PacketWriter* PacketBuilder::CancelTrade()
{
	PacketWriter* p = new PacketWriter(SendOpcodes::CancelTrade);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(1));
	p->Write<BYTE>(0);
	return p;
}

PacketWriter* PacketBuilder::PlaceItemInSellWindow(uint32_t itemIndex, byte CellX, byte CellY)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PlaceItemNPCTrade);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(1));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(itemIndex));
	p->Write<byte>(CellX);
	p->Write<byte>(CellY);
	return p;
}

PacketWriter* PacketBuilder::InventoryToStash(uint32_t elementId, uint16_t page)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::InventoryToStash);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(page));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(elementId));
	p->Write<byte>(0);
	p->Write<byte>(0);
	p->Write<byte>(0);
	return p;
}

PacketWriter* PacketBuilder::InventoryToAffinityStash(uint32_t elementId, uint16_t page)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::InventoryToStashWithAffinity);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(elementId));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(1));
	p->Write<uint16_t>(PacketHelper::changeEndianness16(page));
	p->Write<byte>(1);

	return p;
}


PacketWriter* PacketBuilder::WindowToInventory(uint32_t elementId, uint16_t page)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::InventoryToMapWindow);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(page));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(elementId));
	p->Write<byte>(0);
	return p;
}

PacketWriter* PacketBuilder::InventoryToMapWindow(uint32_t elementId, uint16_t unk, byte bUnk1)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::InventoryToMapWindow);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(elementId));
	p->Write<uint16_t>(unk);
	p->Write<byte>(bUnk1);
	return p;
}


PacketWriter* PacketBuilder::RetractTrade(uint32_t itemIndex)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::RetractNPCTradeItem);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(itemIndex));
	return p;
}

PacketWriter* PacketBuilder::AcceptTrade(uint32_t unk)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::AcceptTrade);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(unk)); //not sure..
	return p;
}

PacketWriter* PacketBuilder::SelectNPCDialog(byte index)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::SelectNPCDialog);
	p->Write<byte>(index);
	return p;
}

PacketWriter* PacketBuilder::ExitNPCDialog()
{
	PacketWriter* p = new PacketWriter(SendOpcodes::ExitNPCDialog);
	return p;
}

PacketWriter* PacketBuilder::PlayerMessage(wchar_t* msg)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PlayerChat);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(wcslen(msg)));
	p->WriteWideString(msg, wcslen(msg));
	return p;
}

PacketWriter* PacketBuilder::ClickInventoryItem()
{
	PacketWriter* p = new PacketWriter(SendOpcodes::ClickInventoryItem);
	return p;
}

PacketWriter* PacketBuilder::MoveInventoryItem(uint32_t CellX, uint32_t CellY)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PlaceInventoryItem);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(1));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(CellX));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(CellY));
	p->Write<byte>(0);
	return p;
}


PacketWriter* PacketBuilder::LevelUpSkillGem(uint32_t InventorySlot, uint32_t ClickedCounter, uint32_t SocketLinksSlot) //goes counter-clockwise starting at top left
{
	PacketWriter* p = new PacketWriter(SendOpcodes::LevelUpSkillGem);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(InventorySlot));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(ClickedCounter));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(SocketLinksSlot));
	return p;
}

PacketWriter* PacketBuilder::UseWaypoint(uint16_t areaHash, uint32_t waypointEntID, bool openingInstanceList)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::UseWaypoint);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(areaHash));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(waypointEntID));

	if (openingInstanceList)
		p->Write<byte>(1);
	else
		p->Write<byte>(0);

	return p;
}

PacketWriter* PacketBuilder::ChoosePantheonGod(byte index)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::ChoosePantheonGod);
	p->Write<byte>(index);
	return p;
}

PacketWriter* PacketBuilder::PlaceExplosive(int X, int Y, byte placementCount)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PlaceExplosive);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(0x74));
	p->Write<uint16_t>(PacketHelper::changeEndianness16(0x0A));
	p->Write<byte>(0);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(X));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(Y));
	p->Write<byte>(placementCount);
	return p;
}

PacketWriter* PacketBuilder::InviteToParty(wchar_t* characterName)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PartyInvite);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(wcslen(characterName)));
	p->WriteWideString(std::wstring(characterName), wcslen(characterName));
	return p;
}

PacketWriter* PacketBuilder::CancelPartyInvite(wchar_t* characterName)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::CancelPartyInvite);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(wcslen(characterName)));
	p->WriteWideString(std::wstring(characterName), wcslen(characterName));
	return p;
}


PacketWriter* PacketBuilder::EndParty(uint32_t seed)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::ExitParty);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(seed));
	return p;
}

//00 9B 00 1E 08 03 first button ticked, no masters
//00 9B 00 35 05 00  shrines niko
//00 9B 00 35 08 00  shrines
//00 9B 00 1E 08 00  no options..
//00 9B 00 1E 02 00 -> with einhair, no list option
//00 9B 00 34 08 00 -> with abyss option, no masters
PacketWriter* PacketBuilder::SpawnAtlasInstance(UINT16 listSelection, byte masterSelection, byte consumeScarabs)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::LaunchAtlasMap);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(listSelection));
	p->Write<byte>(masterSelection);
	p->Write<byte>(consumeScarabs);
	return p;
}

PacketWriter* PacketBuilder::ChangeCurrentStashTab(uint16_t nTab)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::ChangeCurrentStashTab);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(nTab));
	p->Write<byte>(0);
	return p;
}

//you can place down the item normally after this packet (1d 00)
PacketWriter* PacketBuilder::CreateItemStack(uint32_t inventoryTab, uint32_t elementIndex, uint32_t splitOffAmount)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::CreateItemStack);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(inventoryTab));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(elementIndex));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(splitOffAmount));
	p->Write<byte>(0);
	return p;
}

PacketWriter* PacketBuilder::SelfSkill(uint32_t entityId, uint16_t skillGemSlot)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PlayerSelfSkill);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(entityId));
	p->Write<uint16_t>(PacketHelper::changeEndianness16(skillGemSlot));
	return p;
}

PacketWriter* PacketBuilder::ConsumeInventoryItem(uint32_t itemEntId)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::ConsumeInventoryItem);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(1));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(itemEntId));
	return p;
}

PacketWriter* PacketBuilder::ExitToLoginScreen()
{
	PacketWriter* p = new PacketWriter(SendOpcodes::ExitToLoginScreen);
	p->Write<byte>(0);
	return p;
}

PacketWriter* PacketBuilder::OpenKiracMapMission(uint32_t selection)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::OpenKiracMapMission);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(selection));
	return p;
}

PacketWriter* PacketBuilder::AutoPlaceItemToStash(uint16_t tab, uint32_t entityId, bool bUnk)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::InventoryToStashWithAffinity);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(tab));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(entityId));
	p->Write<byte>(bUnk);
	return p;
}

PacketWriter* PacketBuilder::AutoPlaceItemFromStash(uint16_t tab, uint32_t entityId, bool bUnk)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::AutoPlaceItemFromStash);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(tab));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(entityId));
	p->Write<byte>(bUnk);
	return p;
}

PacketWriter* PacketBuilder::UpgradeDelveStat(byte refilling, byte upgradeSelection)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::UpgradeDelveStat);
	p->Write<byte>(refilling);
	p->Write<byte>(upgradeSelection);
	return p;
}

PacketWriter* PacketBuilder::RefillDelveGoods(byte flare, byte dynamite)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::RefillDelveGoods);
	p->Write<byte>(flare);
	p->Write<byte>(dynamite);
	return p;
}


PacketWriter* PacketBuilder::SystemCommand(uint16_t option, int msgLen, wchar_t* msg)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::SystemCommand);
	p->Write<uint16_t>(option);
	p->Write<uint16_t>(msgLen);
	p->WriteWideString(msg, msgLen);
	return p;
}

PacketWriter* PacketBuilder::UseItemOnOtherItem(uint32_t inventoryUsing, uint32_t itemId, uint32_t inventoryUseOn, uint32_t itemId2)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::UseItemOnOtherItem);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(inventoryUsing));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(itemId));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(inventoryUseOn));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(itemId2));
	return p;
}


bool PacketBuilder::Send(PacketWriter* packet) //cleaner to put it all in here
{
	if (g_Robot->Disconnected)
	{
		delete packet->GetBuffer();
		delete packet;
		return false;
	}

	if (!g_Robot->Disconnected && !g_Robot->ChangingArea)
	{
		UINT64 SendClass = GetSendClass();

		if (SendClass != NULL)
		{
			if (DereferenceSafe<UINT64>(SendClass) != NULL)
			{
				if (packet->GetSize() > 0)
				{
					SendPacket(SendClass, (LPBYTE)packet->GetBuffer(), packet->GetSize());
					return true;
				}
			}
		}

		delete packet->GetBuffer();
		delete packet;
		return true;
	}

	return false;
}

//02 27 00 74 00 02 02 04  undo explosive
//02 27 00 74 00 0A 00 59 04 00 00 86 01 00 00 05  place explosivve
//02 27 00 77 00 08 00 EA 02 00 00 1A 06 44  start monster event
PacketWriter* PacketBuilder::StartSiegeInstance(uint16_t unk1, uint16_t unk2, uint32_t itemId, uint32_t tickCount)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::EventAction);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(unk1)); //0x0077
	p->Write<uint16_t>(PacketHelper::changeEndianness16(unk2)); //0x0008
	p->Write<uint32_t>(PacketHelper::changeEndianness32(itemId));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(GetTickCount()));
	return p;
}

PacketWriter* PacketBuilder::PrepareHarvestExtractor(uint32_t entityId)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PrepareHarvestExtractor);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(entityId));
	return p;
}

PacketWriter* PacketBuilder::SpawnHarvestMonsters(uint32_t entityId)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::HarvestCraft);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(entityId));
	return p;
}

PacketWriter* PacketBuilder::ToggleSentinelObject(uint16_t innerOpcode, uint16_t payloadLength, bool out_in, byte nListIndex)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::ToggleSentinelEntity);
	p->Write<uint16_t>(PacketHelper::changeEndianness16(innerOpcode)); //0x7C
	p->Write<uint16_t>(PacketHelper::changeEndianness16(payloadLength)); //0x02
	p->Write<byte>(out_in); //0 = make sentinel come out, 1 = bring back in
	p->Write<byte>(nListIndex); 
	return p;
}

PacketWriter* PacketBuilder::ItemToDivinationWindow(uint32_t entityId, bool inOut)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::InventoryToDivinationWindow);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(entityId));
	p->Write<bool>(inOut);
	return p;
}

PacketWriter* PacketBuilder::PredictiveAction(UINT16 SkillID, UINT32 EntityID, INT32 x, INT32 y, uint16_t count)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PredictiveInput);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(x));
	p->Write<uint32_t>(PacketHelper::changeEndianness32(y));
	p->Write<uint16_t>(PacketHelper::changeEndianness16(SkillID));
	p->Write<uint16_t>(PacketHelper::changeEndianness16(count));
	p->Write<byte>(0x04);
	p->Write<byte>(0x08);
	return p;
}

PacketWriter* PacketBuilder::PredictiveInteraction(UINT16 SkillID, UINT32 EntityID, uint16_t counter)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PredictiveInteraction);
	p->Write<uint32_t>(PacketHelper::changeEndianness32(EntityID));
	p->Write<uint16_t>(PacketHelper::changeEndianness16(SkillID));
	p->Write<uint16_t>(PacketHelper::changeEndianness16(counter));
	p->Write<byte>(0x04);
	p->Write<byte>(0x08);
	return p;
}

PacketWriter* PacketBuilder::TeleportToPartyMember(std::string memberName)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::TeleportPartyMember);
	p->Write<uint16_t>(PacketHelper::changeEndianness32(memberName.size()));
	p->WriteNoLengthString(memberName);

	return p;
}
