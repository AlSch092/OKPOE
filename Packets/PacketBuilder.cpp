#include "PacketBuilder.hpp"
#include "Packets.hpp"

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
	p->Write<DWORD>(changeEndianness32(x));
	p->Write<DWORD>(changeEndianness32(y));
	p->Write<UINT16>(changeEndianness16(SkillID));
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

PacketWriter* PacketBuilder::EntityInteraction(DWORD id)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::EntityInteraction);
	p->Write<DWORD>(changeEndianness32(id));
	p->Write<UINT16>(0x6602);
	p->Write<BYTE>(0x04);
	p->Write<BYTE>(0x08);
	p->Write<BYTE>(0x00);
	return p;
}

PacketWriter* PacketBuilder::SwapHideout(Hideouts Hideout)
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
	p->Write<UINT32>(changeEndianness32(HorizontalDepth));
	p->Write<UINT32>(changeEndianness32(VerticalDepth));
	p->Write<UINT32>(changeEndianness32(HorizontalGridPosition));
	p->Write<UINT32>(changeEndianness32(VerticalGridPosition));
	return p;
}

PacketWriter* PacketBuilder::StartDelveInstance(uint32_t nNodes, uint32_t* pathways)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::StartDelveInstance);
	p->Write<USHORT>(nNodes);

	for (int i = 0; i < nNodes; i++)
	{
		p->Write<UINT32>(changeEndianness32(pathways[0 * nNodes]));
		p->Write<UINT32>(changeEndianness32(pathways[1 * nNodes]));
		p->Write<UINT32>(changeEndianness32(pathways[2 * nNodes]));
		p->Write<UINT32>(changeEndianness32(pathways[3 * nNodes]));
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
	p->Write<uint32_t>(changeEndianness32(id));
	p->Write<uint32_t>(changeEndianness32(type));
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
	p->Write<UINT32>(changeEndianness32(x));
	p->Write<UINT32>(changeEndianness32(y));
	return p;
}

PacketWriter* PacketBuilder::TradePlayer(uint32_t PlayerId)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::TradePlayer);
	p->Write<uint32_t>(changeEndianness32(PlayerId));
	return p;
}

PacketWriter* PacketBuilder::CancelTrade()
{
	PacketWriter* p = new PacketWriter(SendOpcodes::CancelTrade);
	p->Write<uint32_t>(changeEndianness32(1));
	p->Write<BYTE>(0);
	return p;
}

PacketWriter* PacketBuilder::PlaceItemInSellWindow(uint32_t itemIndex, byte CellX, byte CellY)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PlaceItemTrade);
	p->Write<uint32_t>(changeEndianness32(1));
	p->Write<uint32_t>(changeEndianness32(itemIndex));
	p->Write<byte>(CellX);
	p->Write<byte>(CellY);
	return p;
}

PacketWriter* PacketBuilder::RetractTrade(uint32_t itemIndex)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::RetractTradeItem);
	p->Write<uint32_t>(changeEndianness32(itemIndex));
	return p;
}

PacketWriter* PacketBuilder::AcceptTrade(uint32_t unk)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::AcceptTrade);
	p->Write<uint32_t>(changeEndianness32(2));
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
	PacketWriter* p = new PacketWriter(SendOpcodes::MoveInventoryItem);
	p->Write<uint32_t>(changeEndianness32(1));
	p->Write<uint32_t>(changeEndianness32(CellX));
	p->Write<uint32_t>(changeEndianness32(CellY));
	p->Write<byte>(0);
	return p;
}


PacketWriter* PacketBuilder::LevelUpSkillGem(uint32_t InventorySlot, uint32_t ClickedCounter, uint32_t SocketLinksSlot) //goes counter-clockwise starting at top left
{
	PacketWriter* p = new PacketWriter(SendOpcodes::LevelUpSkillGem);
	p->Write<uint32_t>(changeEndianness32(InventorySlot));
	p->Write<uint32_t>(changeEndianness32(ClickedCounter));
	p->Write<uint32_t>(changeEndianness32(SocketLinksSlot));
	return p;
}

PacketWriter* PacketBuilder::UseWaypoint(uint16_t areaHash, uint32_t waypointEntID, bool openingInstanceList)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::UseWaypoint);
	p->Write<uint16_t>(changeEndianness16(areaHash));
	p->Write<uint32_t>(changeEndianness32(waypointEntID));

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
	p->Write<uint16_t>(changeEndianness16(0x74));
	p->Write<uint16_t>(changeEndianness16(0x0A));
	p->Write<byte>(0);
	p->Write<uint32_t>(changeEndianness32(X));
	p->Write<uint32_t>(changeEndianness32(Y));
	p->Write<byte>(placementCount);
	return p;
}

PacketWriter* PacketBuilder::InviteToParty(wchar_t* characterName)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::PartyInvite);
	p->Write<uint16_t>(changeEndianness16(wcslen(characterName)));
	//p->WriteWString(characterName);
	return p;
}

PacketWriter* PacketBuilder::CancelPartyInvite(wchar_t* characterName)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::CancelPartyInvite);
	p->Write<uint16_t>(changeEndianness16(wcslen(characterName)));
	//p->WriteWString(characterName);
	return p;
}


PacketWriter* PacketBuilder::EndParty(uint32_t seed)
{
	PacketWriter* p = new PacketWriter(SendOpcodes::ExitParty);
	p->Write<uint32_t>(changeEndianness32(seed));
	return p;
}