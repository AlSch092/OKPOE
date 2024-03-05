#pragma once
#include "PacketWriter.hpp"
#include "Declarations.hpp"
#include "Opcodes.hpp"
#include "enums.hpp"

namespace PacketBuilder
{
	bool Send(PacketWriter* packet);

	PacketWriter* ConsumeFlask(BYTE Slot);
	PacketWriter* Action(UINT16 SkillID, UINT32 EntityID, INT32 x, INT32 y);
	PacketWriter* PredictiveAction(UINT16 SkillID, UINT32 EntityID, INT32 x, INT32 y, uint16_t counter);
	PacketWriter* PredictiveInteraction(UINT16 SkillID, UINT32 EntityID, uint16_t counter);
	PacketWriter* SelfSkill(uint32_t bUnk1, uint16_t skillGemSlot);
	PacketWriter* ChainedAction(INT32 x, INT32 y);
	PacketWriter* EndAction();
	PacketWriter* EntityInteraction(uint32_t id, uint16_t interactionSkill);
	PacketWriter* EnterPlayerHideout(std::string playerName);
	PacketWriter* SwapHideout(byte Hideout);
	PacketWriter* ChangeAscendency(BYTE JobClassID);
	PacketWriter* EnterDelveNode(uint32_t HorizontalDepth, uint32_t VerticalDepth, uint32_t HorizontalGridPosition, uint32_t VerticalGridPosition);
	PacketWriter* StartDelveInstance(uint32_t nNodes, uint32_t* pathways);
	PacketWriter* Revive(BOOL ReviveInTown);

	PacketWriter* UseWaypoint(UINT32 MapHash, UINT32 EntityId, BOOL EnteringDefaultInstance);
	PacketWriter* JoinInstance(BYTE InstanceListNum);

	PacketWriter* CreateBlightTower(uint32_t id, uint32_t type);
	PacketWriter* ExitToCharScreen();
	PacketWriter* ExitToLoginScreen();
	PacketWriter* SelectCharacter(BYTE Index);
	PacketWriter* MoveToAzuriteMine(UINT32 EntityID);

	PacketWriter* TradePlayer(uint32_t PlayerId);
	PacketWriter* CancelTrade();

	PacketWriter* PurchaseNPCItem(uint32_t CellX, uint32_t CellY, byte Page, uint32_t InventoryCellX, uint32_t InventoryCellY, uint16_t Quantity);
	PacketWriter* PlaceItemInSellWindow(uint32_t itemIndex, byte CellX, byte CellY);
	PacketWriter* RetractTrade(uint32_t itemIndex);
	PacketWriter* AcceptTrade(uint32_t unk1);

	PacketWriter* SelectNPCDialog(byte index);
	PacketWriter* ExitNPCDialog();

	PacketWriter* PlayerMessage(wchar_t* Msg);

	PacketWriter* MoveInventoryItem(uint32_t CellX, uint32_t CellY);
	PacketWriter* ClickInventoryItem();

	PacketWriter* LevelUpSkillGem(uint32_t InventorySlot, uint32_t ClickedCounter, uint32_t SocketLinksSlot);

	PacketWriter* UseWaypoint(uint16_t areaHash, uint32_t waypointEntID, bool openingInstanceList);

	PacketWriter* SpawnAtlasInstance(UINT16 listSelection, byte masterSelection, byte consumeScarabs);
	PacketWriter* ChoosePantheonGod(byte index);

	PacketWriter* PlaceExplosive(int X, int Y, byte placementCount);

	PacketWriter* InviteToParty(wchar_t* characterName);
	PacketWriter* CancelPartyInvite(wchar_t* characterName);
	PacketWriter* EndParty(uint32_t seed);

	PacketWriter* InventoryToStash(uint32_t elementId, uint16_t page);
	PacketWriter* InventoryToAffinityStash(uint32_t elementId, uint16_t page);
	PacketWriter* WindowToInventory(uint32_t itemCounter, uint16_t page);

	PacketWriter* ChangeCurrentStashTab(uint16_t nTab);
	PacketWriter* CreateItemStack(uint32_t inventoryTab, uint32_t elementIndex, uint32_t splitOffAmount);

	PacketWriter* ConsumeInventoryItem(uint32_t itemEntId);

	PacketWriter* OpenKiracMapMission(uint32_t selection);

	PacketWriter* UpgradeDelveStat(uint16_t option);

	PacketWriter* AutoPlaceItemToStash(uint16_t tab, uint32_t entityId, bool inOut);
	PacketWriter* AutoPlaceItemFromStash(uint16_t tab, uint32_t entityId, bool inOut);
	PacketWriter* ItemToDivinationWindow(uint32_t entityId, bool inOut);

	PacketWriter* UpgradeDelveStat(byte refilling, byte upgradeSelection);
	PacketWriter* RefillDelveGoods(byte flare, byte dynamite);

	PacketWriter* SystemCommand(uint16_t option, int msgLen, wchar_t* msg);

	PacketWriter* UseItemOnOtherItem(uint32_t inventoryUsing, uint32_t itemId, uint32_t inventoryUseOn, uint32_t itemId2);

	PacketWriter* InventoryToMapWindow(uint32_t elementId, uint16_t unk, byte bUnk1);

	PacketWriter* StartSiegeInstance(uint16_t unk1, uint16_t unk2, uint32_t itemId, uint32_t tickCount);

	PacketWriter* PrepareHarvestExtractor(uint32_t entityId);
	PacketWriter* SpawnHarvestMonsters(uint32_t entityId);

	PacketWriter* ToggleSentinelObject(uint16_t innerOpcode, uint16_t payloadLength, bool out_in, byte nListIndex);//02 31 00 7C 00 02 00 00 

	PacketWriter* TeleportToPartyMember(std::string memberName);
}

