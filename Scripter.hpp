#pragma once

//LUA includes: loaded into binary
#include <fstream>
#include <vector>
#include "LUA/lua.hpp"
#include "LUA/lauxlib.h"
#include "LUA/lualib.h"
#include "AutoPlayer.hpp"
#include "Hooks.hpp"
#include "Hacks.hpp"
#include "Monster.hpp"
#include "Element.hpp"

namespace Scripting
{
	static void initializeLUA();
	void ExecuteLUA();
	void StopLUA(lua_State* lua_state);

	static int RunScript(lua_State* LUAState);

	//local
	static int GetLocalPlayer(lua_State* LUAState);
	static int GetPlayerLvl(lua_State* LUAState);
	static int GetPlayerExp(lua_State* LUAState);
	static int GetEntityPlayerName(lua_State* LUAState);
	static int GetLocalPlayerName(lua_State* LUAState);

	//util.
	static int MessagePrompt(lua_State* LUAState);
	static int Wait(lua_State* LUAState);
	static int LogToConsole(lua_State* LUAState);
	static int OutPacket(lua_State* LUAState);
	static int SpamPacket(lua_State* LUAState);

	static int SetAutoExitHP(lua_State* LUAState);
	static int UseFlask(lua_State* LUAState);
	static int IsPlayerAlive(lua_State* LUAState);
	
	//ent
	static int GetCurrentHP(lua_State* LUAState);
	static int GetCurrentMP(lua_State* LUAState);
	static int GetCurrentES(lua_State* LUAState);
	static int GetMaxHP(lua_State* LUAState);
	static int GetMaxMana(lua_State* LUAState);
	static int GetMaxES(lua_State* LUAState);
	static int IsEntityAlive(lua_State* LUAState);
	
	//Positioned Component Functions...
	static int MoveToPosition(lua_State* LUAState);
	static int ChainedMovement(lua_State* L);
	static int SelfSkill(lua_State* LUAState);
	static int SendCharacterAction(lua_State* LUAState);
	static int EntityInteraction(lua_State* LUAState);
	static int EndAction(lua_State* LUAState);
	static int GetEntityPosition(lua_State* LUAState);
	static int GetEntityId(lua_State* LUAState);

	//targeted
	static int IsEntityTargetable(lua_State* LUAState);
	static int IsEntityHovered(lua_State* LUAState);

	//actor
	static int ActionId(lua_State* LUAState);
	static int ActionCount(lua_State* LUAState);

	//chest
	static int ChestQuality(lua_State* LUAState);
	static int IsLocked(lua_State* LUAState);
	static int IsChestStrongbox(lua_State* LUAState);
	static int IsOpened(lua_State* LUAState);
	static int IsChestOpened(lua_State* LUAState);
	static int GetClosestStrongbox(lua_State* LUAState);

	//Packets, random stuff
	static int EnterPlayerHideout(lua_State* L);
	static int ChangeHideout(lua_State* LUAState);
	static int ThrowDynamite(lua_State* LUAState);
	static int ThrowFlare(lua_State* LUAState);
	static int VisitDelveNode(lua_State* LUAState);
	static int StartDelveNode(lua_State* LUAState);
	static int GetDelveEncounterObject(lua_State* L); //returns ID of any entity in list starting with "Metadata/Terrain/Leagues/Delve/Objects/EncounterControlObjects")

	static int RevivePlayer(lua_State* LUAState);
	static int IsCharacterStuck(lua_State* LUAState);

	//hacks toggle
	static int RevealMap(lua_State* LUAState);
	static int SetCameraZoom(lua_State* LUAState);
	static int ToggleReduceCPU(lua_State* LUAState);
	static int ToggleReduceRAM(lua_State* LUAState);
	static int ToggleReduceRAM(lua_State* LUAState);

	static int KillNearby(lua_State* LUAState);
	static int KillNearestMonster(lua_State* LUAState);

	static int BuildBlightTower(lua_State* LUAState);
	static int FollowPlayer(lua_State* LUAState);
	static int EnterAreaTransitions(lua_State* LUAState);

	static int GetItemSockets(lua_State* LUAState);
	static int IsItemFullyLinked(lua_State* LUAState);
	static int UnloadDLL(lua_State* LUAState);
	static int LootGroundItems(lua_State* L);

	static int SelectNPCDialog(lua_State* L);
	static int ExitNPCDialog(lua_State* L);

	static int AcceptTrade(lua_State* L);
	static int CancelTrade(lua_State* L);
	static int PlaceItemInTrade(lua_State* L);
	static int ExitNPCDialog(lua_State* L);

	static int PlayerMessage(lua_State* L);
	static int GetEntityComponentAddress(lua_State* L);
	static int IsEntityInList(lua_State* L);

	static int SelectPantheonGod(lua_State* L);

	static int UseWaypoint(lua_State* L);

	static int GetEntityByName(lua_State* L);
	static int GetEntityIdByName(lua_State* L);

	static int PlaceExplosive(lua_State* L);
	static int BlightTower(lua_State* L);
	static int DiscardEntity(lua_State* L);

	static int SelectInstance(lua_State* L);
	static int SpawnAtlasPortals(lua_State* L);

	static int InventoryToWindow_Item(lua_State* L);
	static int WindowToInventory_Item(lua_State* L);

	static int ReadAllElements(lua_State* L);
	static int ReadInventoryItems(lua_State* L);

	static int ReadCurrencyStashTab(lua_State* L);
	static int GetItemAtSlots(lua_State * L);
	static int GetItemsInStashTab(lua_State* L);
	static int SelectStashTab(lua_State* L);
	static int ReadTradeWindowItems(lua_State* L);

	static int InventoryContainsItem(lua_State* L);
	static int CurrencyTabContainsItem(lua_State* L);
	static int StashTabPageContainsItem(lua_State* L);
	static int WindowContainsItem(lua_State* L);

	static int GetNumberOfItems(lua_State* L);

	static int TestItemSell(lua_State* L);

	static int InviteToParty(lua_State* L);
	static int KickFromParty(lua_State* L);
	
	static int KillMonster(lua_State* L);
	static int GetNumberOfMonstersNearby(lua_State* L);

	static int CallLUAFromC(lua_State* L); //experimental
	static void StackDump(lua_State* L);

	static int GetPlayerClass(lua_State* L);

	static int InventoryItemToNPCWindow(lua_State* L);
	static int AcceptTrade(lua_State* L);
	static int PrintMonsterList(lua_State* L);
	static int PrintEntityList(lua_State* L);
	static int ClearEntityList(lua_State* L);

	static int GetCurrentMap(lua_State* L);
	static int GetNumberMapName(lua_State* L);

	static int UseInventoryItem(lua_State* L);
	static int UseInventoryItemId(lua_State* L);
	static int GetInventoryItemId(lua_State* L);
	static int GetStashInventoryItemId(lua_State* L);

	static int ExitToCharacterScreen(lua_State* L);
	static int ExitToLoginScreen(lua_State* L);

	static int Login(lua_State* L);
	static int SelectCharacter(lua_State* L);

	static int IsCharacterStuckInDirection(lua_State* L);
	static int UseMovementSkill(lua_State* LUAState);

	static int IsInventoryFull(lua_State* LUAState);
	static int GetMonsterCount(lua_State* L);
	static int GetNumberOfInventoryItems(lua_State* L);

	static int UseBuffs(lua_State* L);

	static int GetFlaskList(lua_State* L);

	static int StashToInventory(lua_State* L);
	static int InventoryToStash(lua_State* L);

	static int UseItemOnItem(lua_State* L);

	static int OpenChests(lua_State* L);

	static int InventoryToMapWindow(lua_State* L);
	static int InventoryIdToMapWindow(lua_State* L);
	static int MapWindowToInventory(lua_State* L);

	static int GetMonstersId(lua_State* L);

	//static int HarvestSpawn(lua_State* L);

	static int ClearEntityFromList(lua_State* L);
	
	static int SendWindowInput(lua_State* L);
	static int MouseInput(lua_State* L);

	static int IsEntitySummoned(lua_State* L);
	static int GetWaypointId(lua_State* L);

	static int SetHuntingMode(lua_State* L);

	static int UsePortalSkill(lua_State* L);
	static int PlaceTotems(lua_State* L);

	static int StashValuableItems(lua_State* L);
	static int SellDisposableItems(lua_State* L);

	static int InitializeMapSupport(lua_State* L);

	static int MoveToStrongbox(lua_State* L);
	static int GetRandomMapId(lua_State* L);

	static int DistanceFrom(lua_State* L);
	static int CleanStrongboxList(lua_State* L);

	static int StartMovement(lua_State* L);
	static int GetPlayerActionId(lua_State* LUAState);
	static int GetEntityActionId(lua_State* L);
	static int RemoveStrongboxFromList(lua_State* L);

	static int IdentifyInventoryItems(lua_State* L);

	static int GetPlayerRotation(lua_State* L);
	static int SetPlayerRotation(lua_State* L);

	static int WalkInDirectionFaced(lua_State* L);

	static int UseSkillsFromFile(lua_State* L);

	static int GetActorSkills(lua_State* L);

	static int GetDeadMonsterId(lua_State* L);

	static int ShutdownAtLocalTime(lua_State* L);

	static int ToggleSentinel(lua_State* L);

	static int GetLootableItemByName(lua_State* L);

	static int CheckScreenHasLabel(lua_State* L);

	static int LootItems(lua_State* L);

	static int SetWindowTitle(lua_State* L);
}


