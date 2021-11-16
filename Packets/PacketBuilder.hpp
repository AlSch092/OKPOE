#pragma once
#include "PacketWriter.hpp"

namespace SendOpcodes
{
	const UINT16 SelectCharacter = 0x0D00;

	const UINT16 PlayerChat = 0x0800;
	const UINT16 ClickInventoryItem = 0x1B00;
	const UINT16 MoveInventoryItem = 0x1D00;
	const UINT16 PlaceSkillGemInSocket = 0x2000;
	const UINT16 LevelUpSkillGem = 0x2100;
	const UINT16 Flask = 0x4900;
	const UINT16 PlayerInput = 0x2B01;
	const UINT16 EntityInteraction = 0x2C01;
	const UINT16 PlayerInputContinuous = 0x2F01;
	const UINT16 PlayerStopInput = 0x3101;

	const UINT16 ChangeHideout = 0xC501;

	const UINT16 BlightTower = 0xCE01;

	const UINT16 StartDelveInstance = 0xB201;
	const UINT16 ToAzuriteMines = 0x2001;

	const UINT16 AscendCharacter = 0x2700;
	const UINT16 UseWaypoint = 0x3C00;
	const UINT16 ReviveCharacter = 0x4000;
	const UINT16 JoinInstance = 0x7600;
	const UINT16 ExitToCharacterScreen = 0xFB00;

	const UINT16 PartyInvite = 0x6500;
	const UINT16 CancelPartyInvite = 0x6600;
	const UINT16 ExitParty = 0x6800;

	const UINT16 TradePlayer = 0x7F00;
	const UINT16 CancelTrade = 0x7800;
	const UINT16 PlaceItemTrade = 0x7900;
	const UINT16 RetractTradeItem = 0x7A00;
	const UINT16 AcceptTrade = 0x7B00;

	const UINT16 SelectNPCDialog = 0x5900;
	const UINT16 ExitNPCDialog = 0x5B00;

	const UINT16 ChoosePantheonGod = 0x7001;
	const UINT16 PlaceExplosive = 0x1E02; 
}

namespace RecvOpcodes //derp..
{


}

enum Hideouts
{
	Cartographer = 0x11,
	NONE = 0x00
};

namespace PacketBuilder
{
	PacketWriter* ConsumeFlask(BYTE Slot);
	PacketWriter* Action(UINT16 SkillID, UINT32 EntityID, INT32 x, INT32 y);
	PacketWriter* ChainedAction(INT32 x, INT32 y);
	PacketWriter* EndAction();
	PacketWriter* EntityInteraction(DWORD id);
	PacketWriter* SwapHideout(Hideouts Hideout);
	PacketWriter* ChangeAscendency(BYTE JobClassID);
	PacketWriter* EnterDelveNode(uint32_t HorizontalDepth, uint32_t VerticalDepth, uint32_t HorizontalGridPosition, uint32_t VerticalGridPosition);
	PacketWriter* StartDelveInstance(uint32_t nNodes, uint32_t* pathways);
	PacketWriter* Revive(BOOL ReviveInTown);

	PacketWriter* UseWaypoint(UINT32 MapHash, UINT32 EntityId, BOOL EnteringDefaultInstance);
	PacketWriter* JoinInstance(BYTE InstanceListNum);

	PacketWriter* CreateBlightTower(uint32_t id, uint32_t type);
	PacketWriter* ExitToCharScreen();
	PacketWriter* SelectCharacter(BYTE Index);
	PacketWriter* MoveToAzuriteMine(UINT32 EntityID);

	PacketWriter* TradePlayer(uint32_t PlayerId);
	PacketWriter* CancelTrade(); //also for npcs

	PacketWriter* PurchaseNPCItem(uint32_t CellX, uint32_t CellY, byte Page, uint32_t InventoryCellX, uint32_t InventoryCellY, uint16_t Quantity);
	PacketWriter* PlaceItemInSellWindow(uint32_t itemIndex, byte CellX, byte CellY);
	PacketWriter* RetractTrade(uint32_t itemIndex);
	PacketWriter* AcceptTrade(uint32_t unk1); //seems to be 2 for NPCs

	PacketWriter* SelectNPCDialog(byte index);
	PacketWriter* ExitNPCDialog();

	PacketWriter* PlayerMessage(wchar_t* Msg);

	PacketWriter* MoveInventoryItem(uint32_t CellX, uint32_t CellY);
	PacketWriter* ClickInventoryItem();

	PacketWriter* LevelUpSkillGem(uint32_t InventorySlot, uint32_t ClickedCounter, uint32_t SocketLinksSlot);

	PacketWriter* UseWaypoint(uint16_t areaHash, uint32_t waypointEntID, bool openingInstanceList);

	PacketWriter* ChoosePantheonGod(byte index);

	PacketWriter* PlaceExplosive(int X, int Y, byte placementCount);

	PacketWriter* InviteToParty(wchar_t* characterName);
	PacketWriter* CancelPartyInvite(wchar_t* characterName);
	PacketWriter* EndParty(uint32_t seed);
}

