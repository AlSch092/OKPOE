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


namespace Scripting
{
	static void initializeLUA();
	void ExecuteLUA();
	void StopLUA(lua_State* lua_state);

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

	//Packets, random stuff
	static int ChangeHideout(lua_State* LUAState);
	static int ThrowDynamite(lua_State* LUAState);
	static int ThrowFlare(lua_State* LUAState);
	static int VisitDelveNode(lua_State* LUAState);
	static int StartDelveNode(lua_State* LUAState);
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

	static int CallLUAFromC(lua_State* L);

	static void StackDump(lua_State* L);
}


