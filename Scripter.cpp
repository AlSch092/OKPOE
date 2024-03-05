#include "Scripter.hpp"

extern AutoPlayer* g_Robot;
extern NetLogger* g_ProtectionServer;
extern HMODULE g_OurModule;

void Scripting::initializeLUA()
{
	g_Robot->LUAController = luaL_newstate();
	luaL_openlibs(g_Robot->LUAController);

	lua_register(g_Robot->LUAController, "Script", Scripting::RunScript);
	lua_register(g_Robot->LUAController, "SetWindowTitle", Scripting::SetWindowTitle);

	lua_register(g_Robot->LUAController, "GetLocalPlayer", Scripting::GetLocalPlayer);
	lua_register(g_Robot->LUAController, "GetPlayerLevel", Scripting::GetPlayerLvl);
	lua_register(g_Robot->LUAController, "GetPlayerExp", Scripting::GetPlayerExp);
	lua_register(g_Robot->LUAController, "GetPlayerName", Scripting::GetLocalPlayerName);
	lua_register(g_Robot->LUAController, "GetPlayerClass", Scripting::GetPlayerClass);
	lua_register(g_Robot->LUAController, "GetEntityName", Scripting::GetEntityPlayerName);
	lua_register(g_Robot->LUAController, "GetComponentAddress", Scripting::GetEntityComponentAddress);
	lua_register(g_Robot->LUAController, "GetEntityId", Scripting::GetEntityId);
	lua_register(g_Robot->LUAController, "GetEntityIdByPath", Scripting::GetEntityIdByName);
	lua_register(g_Robot->LUAController, "GetEntityByPath", Scripting::GetEntityByName);
	lua_register(g_Robot->LUAController, "IsEntityInList", Scripting::IsEntityInList);

	lua_register(g_Robot->LUAController, "Message", Scripting::PlayerMessage);

	//etc/util
	lua_register(g_Robot->LUAController, "MessageBox", Scripting::MessagePrompt);
	lua_register(g_Robot->LUAController, "Log", Scripting::LogToConsole);
	lua_register(g_Robot->LUAController, "Wait", Scripting::Wait);
	
	lua_register(g_Robot->LUAController,  "RevealMap", Scripting::RevealMap); //toggle hacks
	lua_register(g_Robot->LUAController,  "SetCameraZoom", Scripting::SetCameraZoom);
	lua_register(g_Robot->LUAController, "ReduceCPU", Scripting::ToggleReduceCPU);
	lua_register(g_Robot->LUAController, "ReduceRAM", Scripting::ToggleReduceRAM);

	//Network
	lua_register(g_Robot->LUAController,  "SendPacket", Scripting::OutPacket);
	lua_register(g_Robot->LUAController, "SpamPacket", Scripting::SpamPacket);
	lua_register(g_Robot->LUAController, "EnterHideout", Scripting::EnterPlayerHideout);
	lua_register(g_Robot->LUAController,  "ChangeHideout", Scripting::ChangeHideout);

	//Alive/gameplay related
	lua_register(g_Robot->LUAController,  "UseFlask", Scripting::UseFlask);
	lua_register(g_Robot->LUAController, "PlayerAlive", Scripting::IsPlayerAlive);
	lua_register(g_Robot->LUAController,  "Revive", Scripting::RevivePlayer);

	lua_register(g_Robot->LUAController,  "Action", Scripting::SendCharacterAction); //same as moveto with diff parameters, meant for skill casting
	lua_register(g_Robot->LUAController, "SelfSkill", Scripting::SelfSkill);
	lua_register(g_Robot->LUAController,  "Move", Scripting::MoveToPosition);
	lua_register(g_Robot->LUAController, "StartMovement", Scripting::StartMovement);
	lua_register(g_Robot->LUAController, "ContinueMovement", Scripting::ChainedMovement);
	lua_register(g_Robot->LUAController, "MovementSkill", Scripting::UseMovementSkill);
	lua_register(g_Robot->LUAController, "EndAction", Scripting::EndAction);
	lua_register(g_Robot->LUAController, "EntityInteraction", Scripting::EntityInteraction);
	lua_register(g_Robot->LUAController, "GetPlayerRotation", Scripting::GetPlayerRotation);
	lua_register(g_Robot->LUAController, "SetPlayerRotation", Scripting::SetPlayerRotation);

	lua_register(g_Robot->LUAController,  "Loot", Scripting::LootItems);

	lua_register(g_Robot->LUAController, "PlaceTotems", Scripting::PlaceTotems);

	lua_register(g_Robot->LUAController, "GetActionCount", Scripting::ActionCount);
	lua_register(g_Robot->LUAController, "GetActionId", Scripting::ActionId);
	lua_register(g_Robot->LUAController, "GetPlayerSkills", Scripting::GetActorSkills);
	lua_register(g_Robot->LUAController, "GetEntityPosition", Scripting::GetEntityPosition);

	lua_register(g_Robot->LUAController, "FollowPlayer", Scripting::FollowPlayer);

	lua_register(g_Robot->LUAController, "EnterAreaTransitions", Scripting::EnterAreaTransitions);

	lua_register(g_Robot->LUAController, "UseWaypoint", Scripting::UseWaypoint);
	lua_register(g_Robot->LUAController, "SelectInstance", Scripting::SelectInstance);
	lua_register(g_Robot->LUAController, "SpawnMapInstance", Scripting::SpawnAtlasPortals);

	//Targetable::
	lua_register(g_Robot->LUAController, "IsTargetable", Scripting::IsEntityTargetable);
	lua_register(g_Robot->LUAController, "IsHovered", Scripting::IsEntityHovered); //with mouse coords

	//Chest::Component
	lua_register(g_Robot->LUAController, "GetClosestStrongbox", Scripting::GetClosestStrongbox);
	lua_register(g_Robot->LUAController, "IsOpened", Scripting::IsOpened);
	lua_register(g_Robot->LUAController, "IsChestOpened", Scripting::IsChestOpened);
	lua_register(g_Robot->LUAController, "GetChestQuality", Scripting::ChestQuality);
	lua_register(g_Robot->LUAController, "IsLocked", Scripting::IsLocked);
	lua_register(g_Robot->LUAController, "IsStrongbox", Scripting::IsChestStrongbox);

	//Life::Component
	lua_register(g_Robot->LUAController,  "GetPlayerHP", Scripting::GetCurrentHP);
	lua_register(g_Robot->LUAController,  "GetPlayerMP", Scripting::GetCurrentMP);
	lua_register(g_Robot->LUAController,  "GetPlayerES", Scripting::GetCurrentES);
	lua_register(g_Robot->LUAController,  "GetPlayerMaxHP", Scripting::GetMaxHP);
	lua_register(g_Robot->LUAController,  "GetPlayerMaxMana", Scripting::GetMaxMana);
	lua_register(g_Robot->LUAController,  "GetPlayerMaxES", Scripting::GetMaxES);

	//league shit
	lua_register(g_Robot->LUAController,  "StartDelveNode", Scripting::VisitDelveNode);
	lua_register(g_Robot->LUAController, "StartDelvePathing", Scripting::StartDelveNode);
	lua_register(g_Robot->LUAController, "GetDelveEncounterObject", Scripting::GetDelveEncounterObject);

	lua_register(g_Robot->LUAController, "CreateBlightTower", Scripting::VisitDelveNode);

	lua_register(g_Robot->LUAController, "NumberOfItemSockets", Scripting::GetItemSockets);
	lua_register(g_Robot->LUAController, "IsItemFullyLinked", Scripting::IsItemFullyLinked);

	lua_register(g_Robot->LUAController, "GetMonsterCount", Scripting::GetNumberOfMonstersNearby);
	lua_register(g_Robot->LUAController, "KillNearestMonster", Scripting::KillNearestMonster);
	lua_register(g_Robot->LUAController, "LootNearby", Scripting::LootGroundItems);

	lua_register(g_Robot->LUAController, "ExitNPCDialog", Scripting::ExitNPCDialog);
	lua_register(g_Robot->LUAController, "SelectNPCDialog", Scripting::SelectNPCDialog);

	lua_register(g_Robot->LUAController, "AcceptTrade", Scripting::AcceptTrade);
	lua_register(g_Robot->LUAController, "PlaceItemInTrade", Scripting::PlaceItemInTrade); //possibly duplicte of inventorytowindow
	lua_register(g_Robot->LUAController, "CancelTrade", Scripting::CancelTrade);
	lua_register(g_Robot->LUAController, "InventoryItemToNPCTrade", Scripting::InventoryItemToNPCWindow);

	lua_register(g_Robot->LUAController, "BlightTower", Scripting::BlightTower);
	lua_register(g_Robot->LUAController, "PlaceExplosives", Scripting::PlaceExplosive);

	lua_register(g_Robot->LUAController, "DiscardEntity", Scripting::DiscardEntity);

	lua_register(g_Robot->LUAController, "WindowItemToInventory", Scripting::WindowToInventory_Item);
	lua_register(g_Robot->LUAController, "InventoryItemToWindow", Scripting::InventoryToWindow_Item);

	lua_register(g_Robot->LUAController, "InventoryItemToMapWindow", Scripting::InventoryToMapWindow);
	lua_register(g_Robot->LUAController, "InventoryItemIdToMapWindow", Scripting::InventoryIdToMapWindow);
	lua_register(g_Robot->LUAController, "MapWindowToInventory", Scripting::MapWindowToInventory);

	lua_register(g_Robot->LUAController, "GetElements", Scripting::ReadAllElements);
	lua_register(g_Robot->LUAController, "ReadInventory", Scripting::ReadInventoryItems);
	lua_register(g_Robot->LUAController, "ReadCurrencyTab", Scripting::ReadCurrencyStashTab);
	lua_register(g_Robot->LUAController, "ReadItemsAtTab", Scripting::GetItemsInStashTab);
	lua_register(g_Robot->LUAController, "ReadTradeItems", Scripting::ReadTradeWindowItems);
	lua_register(g_Robot->LUAController, "SelectStashTab", Scripting::SelectStashTab);
	lua_register(g_Robot->LUAController, "TestSell", Scripting::TestItemSell);
	lua_register(g_Robot->LUAController, "InventoryContainsItem", Scripting::InventoryContainsItem);
	lua_register(g_Robot->LUAController, "CurrencyTabContainsItem", Scripting::CurrencyTabContainsItem);
	lua_register(g_Robot->LUAController, "TradeWindowContainsItem", Scripting::WindowContainsItem);
	lua_register(g_Robot->LUAController, "GetItemCount", Scripting::GetNumberOfItems);

	lua_register(g_Robot->LUAController, "PartyInvite", Scripting::InviteToParty);
	lua_register(g_Robot->LUAController, "KickPartyMember", Scripting::KickFromParty);

	lua_register(g_Robot->LUAController, "KillEntity", Scripting::KillMonster);
	lua_register(g_Robot->LUAController, "PrintMonsterList", Scripting::PrintMonsterList);
	lua_register(g_Robot->LUAController, "PrintEntityList", Scripting::PrintEntityList);
	lua_register(g_Robot->LUAController, "ClearEntityList", Scripting::ClearEntityList);
	lua_register(g_Robot->LUAController, "ClearEntityFromList", Scripting::ClearEntityFromList);

	lua_register(g_Robot->LUAController, "GetAreaName", Scripting::GetCurrentMap);
	lua_register(g_Robot->LUAController, "GetNumberedAreaName", Scripting::GetNumberMapName);
	lua_register(g_Robot->LUAController, "UseInventoryItem", Scripting::UseInventoryItem); 
	lua_register(g_Robot->LUAController, "UseInventoryItemId", Scripting::UseInventoryItemId);
	
	lua_register(g_Robot->LUAController, "GetInventoryItemId", Scripting::GetInventoryItemId);
	lua_register(g_Robot->LUAController, "GetRandomMapItemId", Scripting::GetRandomMapId);

	lua_register(g_Robot->LUAController, "SelectCharacter", Scripting::SelectCharacter);
	lua_register(g_Robot->LUAController, "CheckIfStuck", Scripting::IsCharacterStuckInDirection);

	lua_register(g_Robot->LUAController, "IsInventoryFull", Scripting::IsInventoryFull);

	lua_register(g_Robot->LUAController, "UseBuffs", Scripting::UseBuffs);
	lua_register(g_Robot->LUAController, "UseSkills", Scripting::UseSkillsFromFile);

	lua_register(g_Robot->LUAController, "UnloadDLL", Scripting::UnloadDLL);

	lua_register(g_Robot->LUAController, "GetFlaskList", Scripting::GetFlaskList);

	lua_register(g_Robot->LUAController, "StashToInventory", Scripting::StashToInventory);
	lua_register(g_Robot->LUAController, "InventoryToStash", Scripting::InventoryToStash);

	lua_register(g_Robot->LUAController, "UseItemOnItem", Scripting::UseItemOnItem);
	lua_register(g_Robot->LUAController, "OpenNearbyChests", Scripting::OpenChests);
	
	lua_register(g_Robot->LUAController, "GetMonsterId", Scripting::GetMonstersId);

	lua_register(g_Robot->LUAController, "Keyboard", Scripting::SendWindowInput);
	lua_register(g_Robot->LUAController, "MouseInput", Scripting::MouseInput);

	lua_register(g_Robot->LUAController, "IsSummoned", Scripting::IsEntitySummoned);

	lua_register(g_Robot->LUAController, "GetWaypointId", Scripting::GetWaypointId);

	lua_register(g_Robot->LUAController, "SetHuntingMode", Scripting::SetHuntingMode);

	lua_register(g_Robot->LUAController, "UsePortalSkill", Scripting::UsePortalSkill);

	//lua_register(g_Robot->LUAController, "UnwiltCrops", Scripting::HarvestSpawn);

	lua_register(g_Robot->LUAController, "DistanceFrom", Scripting::DistanceFrom);

	lua_register(g_Robot->LUAController, "CleanBoxList", Scripting::CleanStrongboxList);
	lua_register(g_Robot->LUAController, "RemoveStrongbox", Scripting::RemoveStrongboxFromList);
	
	lua_register(g_Robot->LUAController, "GetPlayerActionId", Scripting::GetPlayerActionId);
	lua_register(g_Robot->LUAController, "WalkForwards", Scripting::WalkInDirectionFaced);
	lua_register(g_Robot->LUAController, "IsCharacterStuck", Scripting::IsCharacterStuck);
	

	lua_register(g_Robot->LUAController, "StashValuableItems", Scripting::StashValuableItems);
	lua_register(g_Robot->LUAController, "SellDisposableItems", Scripting::SellDisposableItems);
	lua_register(g_Robot->LUAController, "IdentifyInventoryItems", Scripting::IdentifyInventoryItems);

	lua_register(g_Robot->LUAController, "ShutdownAtTime", Scripting::ShutdownAtLocalTime);
	lua_register(g_Robot->LUAController, "ToggleSentinel", Scripting::ToggleSentinel);
	lua_register(g_Robot->LUAController, "GetGroundItemId", Scripting::GetLootableItemByName);

	lua_register(g_Robot->LUAController, "ScreenHasLabel", Scripting::CheckScreenHasLabel);
	
}

void Scripting::ExecuteLUA()
{
	if (strncmp(g_Robot->ScriptBuffer, "Scripting Work Area", 25) == 0) 
		return;

	initializeLUA();

	std::ofstream tempFile;
	std::string fileName;

	if (g_Robot->isRandomizingScriptName)
	{
		fileName = PacketHelper::randomStr(8) + ".LUA";
	}
	else
	{
		fileName = "untitled.LUA";
	}

	tempFile.open(fileName.c_str());

	tempFile.write(g_Robot->ScriptBuffer, strlen(g_Robot->ScriptBuffer));
	tempFile.close();

	if (g_Robot->ScriptBuffer == NULL || strcmp(g_Robot->ScriptBuffer, "") == 0)
	{
		return;
	}

	do 
	{
		luaL_dofile(g_Robot->LUAController, fileName.c_str()); //execute LUA script
	} while (g_Robot->LoopingScript);
}

void Scripting::StopLUA(lua_State* lua_state)
{	
	if (g_Robot->ScriptingThread != NULL)
	{
		lua_close(g_Robot->LUAController);
		TerminateThread(g_Robot->ScriptingThread, 0);
		g_Robot->ScriptingThread = NULL;
	}

}

//LUA Custom Functions
static int Scripting::MessagePrompt(lua_State* LUAState)
{
	const char* str = lua_tostring(LUAState, 1); // get function argument
	MessageBoxA(0, str, "OKPOE", 0);
	return 0;
}

int Scripting::Wait(lua_State* LUAState)
{
	int n = lua_gettop(LUAState);
	int delay = lua_tonumber(LUAState, 1);
	Sleep(delay);
	return 0;
}

static int Scripting::OutPacket(lua_State* LUAState)
{
	const char* str = lua_tostring(LUAState, 1);
	BYTE* hexbytes = PacketHelper::ToPacketFormat((char*)str);
	DWORD length = PacketHelper::GetPacketLength((char*)str);
	UINT64 SendClass = GetSendClass();
	
	
	PacketHelper::Send(SendClass, hexbytes, length);
	
	delete[] hexbytes;
	return 0;
}

static int Scripting::SendCharacterAction(lua_State* LUAState)
{
	if (g_Robot->Disconnected || g_Robot->Attacker->IsBusy)
		return 0;
	
	//get char xy
	USHORT SkillID = lua_tointeger(LUAState, 1);
	UINT32 GridX = lua_tointeger(LUAState, 2);
	UINT32 GridY = lua_tointeger(LUAState, 3);

	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		PacketWriter* p = PacketBuilder::Action(SkillID, NULL, GridX, GridY);
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());

		delete[] p->GetBuffer();
		delete p;

		g_Robot->EndAction();
	}

	return 0;
}

static int Scripting::EntityInteraction(lua_State* LUAState)
{
	UINT32 EntityID = lua_tointeger(LUAState, 1);

	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		Entity* player = g_Robot->GetLocalPlayer();
		Vector2 pV = player->GetVector2();

		PacketWriter* p = PacketBuilder::EntityInteraction(EntityID, 0x266);
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());

		delete p;

		g_Robot->EndAction();

		Sleep(200);

		Vector2 pV_2 = player->GetVector2();

		while (pV.X != pV_2.X && pV.Y != pV_2.Y) //wait to finish walking
		{
			pV = player->GetVector2();
			pV_2 = player->GetVector2();
			Sleep(50);
		}

		delete player;
	}

	return 0;
}

static int Scripting::MoveToPosition(lua_State* LUAState)
{
	const UINT32 X = lua_tointeger(LUAState, 1);
	const UINT32 Y = lua_tointeger(LUAState, 2);
	
	while (g_Robot->Attacker->IsAttacking || g_Robot->Attacker->IsBusy) //wait until done attacking if so
		Sleep(100);

	if (g_Robot->Attacker->MovementSkill > 0)
	{
		PacketWriter* p = PacketBuilder::Action(g_Robot->Attacker->MovementSkill, NULL, X, Y);
		PacketBuilder::Send(p);
		g_Robot->EndAction();
	}
	else
	{
		PacketWriter* p = PacketBuilder::Action(Input::InputIds::RUN, NULL, X, Y);
		PacketBuilder::Send(p);
		g_Robot->EndAction();
	}

	return 0;
}

static int Scripting::UseMovementSkill(lua_State* LUAState)
{
	const UINT32 X = lua_tointeger(LUAState, 1);
	const UINT32 Y = lua_tointeger(LUAState, 2);

	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		PacketWriter* p = PacketBuilder::Action(g_Robot->Attacker->MovementSkill, NULL, X, Y);
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());

		delete[] p->GetBuffer();
		delete p;

		g_Robot->EndAction();
	}
	
	return 0;
}

static int Scripting::UseFlask(lua_State* LUAState)
{
	const byte BeltSlot = lua_tointeger(LUAState, 1);

	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		PacketWriter* p = PacketBuilder::ConsumeFlask(BeltSlot);
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());

		delete[] p->GetBuffer();
		delete p;
	}

	return 0;
}

static int Scripting::GetCurrentHP(lua_State* LUAState)
{ 
	Entity* LocalEntity = g_Robot->GetLocalPlayer();
	INT currHP = Life::GetEntityHP(LocalEntity);
	lua_pushinteger(LUAState, currHP);
	delete LocalEntity;
	return 1;
}

static int Scripting::GetMaxHP(lua_State* LUAState)
{
	Entity* LocalEntity = g_Robot->GetLocalPlayer();
	INT maxHP = Life::GetEntityMaxHP(LocalEntity);

	lua_pushinteger(LUAState, maxHP);
	return 1;
}

static int Scripting::GetCurrentMP(lua_State* LUAState)
{
	Entity* LocalEntity = g_Robot->GetLocalPlayer();
	INT currMP = Life::GetEntityMana(LocalEntity);

	lua_pushinteger(LUAState, currMP);
	return 1;
}

static int Scripting::GetMaxMana(lua_State* LUAState)
{
	Entity* LocalEntity = g_Robot->GetLocalPlayer();
	INT maxMana = Life::GetEntityMaxMana(LocalEntity);

	lua_pushinteger(LUAState, maxMana);
	return 1;
}

static int Scripting::GetCurrentES(lua_State* LUAState)
{
	Entity* LocalEntity = g_Robot->GetLocalPlayer();
	INT Shield = Life::GetEntityES(LocalEntity);

	lua_pushinteger(LUAState, Shield);
	return 1;
}


static int Scripting::GetMaxES(lua_State* LUAState)
{
	Entity* LocalEntity = g_Robot->GetLocalPlayer();
	INT MaxShield = Life::GetEntityMaxES(LocalEntity);

	lua_pushinteger(LUAState, MaxShield);
	return 1;
}


static int Scripting::RevivePlayer(lua_State* LUAState)
{
	const bool inTown = lua_toboolean(LUAState, 1);

	UINT64 SendClass = GetSendClass();
	PacketWriter* p = PacketBuilder::Revive(inTown);
	SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());

	delete[] p->GetBuffer();
	delete p;

	return 0;
}

static int Scripting::EnterPlayerHideout(lua_State* LUAState)
{
	const char* playerName = lua_tostring(LUAState, 1);

	UINT64 SendClass = GetSendClass();
	PacketWriter* p = PacketBuilder::EnterPlayerHideout(playerName);
	SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	delete p;
	return 0;
}

static int Scripting::ChangeHideout(lua_State* LUAState)
{
	const byte Hideout = lua_tointeger(LUAState, 1);
	UINT64 SendClass = GetSendClass();
	PacketWriter* p = PacketBuilder::SwapHideout(Hideout);
	SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	delete p;
	return 0;
}


static int Scripting::VisitDelveNode(lua_State* LUAState)
{
	const int HorizontalDepth = lua_tointeger(LUAState, 1);
	const int VerticalDepth = lua_tointeger(LUAState, 2);
	const int HorizontalGrid = lua_tointeger(LUAState, 3);
	const int VerticalGrid = lua_tointeger(LUAState, 4);

	UINT64 SendClass = GetSendClass();
	PacketWriter* p = PacketBuilder::EnterDelveNode(HorizontalDepth, VerticalDepth, HorizontalGrid, VerticalGrid);
	SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	delete[] p->GetBuffer();
	delete p;
	return 0;
}

static int Scripting::StartDelveNode(lua_State* LUAState)
{
	const int HorizontalDepth = lua_tointeger(LUAState, 1);
	const int VerticalDepth = lua_tointeger(LUAState, 2);
	const int HorizontalGrid = lua_tointeger(LUAState, 3);
	const int VerticalGrid = lua_tointeger(LUAState, 4);

	UINT64 SendClass = GetSendClass();
	PacketWriter* p = PacketBuilder::EnterDelveNode(HorizontalDepth, VerticalDepth, HorizontalGrid, VerticalGrid);
	SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	delete[] p->GetBuffer();
	delete p;
	return 0;

}

static int Scripting::GetLocalPlayer(lua_State* LUAState)
{
	UINT64 LocalPlayerAddr = 0;
	
	Entity* e = g_Robot->GetLocalPlayer();
	
	//if (e != NULL)
		lua_pushinteger(LUAState, e->Address);

	delete e;

	return 1;
}

static int Scripting::IsEntityTargetable(lua_State* LUAState)
{
	const UINT64 EntAddr = lua_tointeger(LUAState, 1);
	printf("Scripting::IsEntTargetable %llx\n", EntAddr);
	
	Entity* e = new Entity(EntAddr);

	if (Targetable::IsTargetable(e))
	{
		lua_pushinteger(LUAState, true);
	}
	else
	{
		lua_pushinteger(LUAState, false);
	}

	return 1;
}


static int Scripting::IsEntityHovered(lua_State* LUAState)
{
	const UINT64 EntAddr = lua_tointeger(LUAState, 1);
	Entity* e = new Entity(EntAddr);

	if (Targetable::IsMouseOverEntity(e))
	{
		lua_pushboolean(LUAState, true);
	}
	else
	{
		lua_pushboolean(LUAState, false);
	}

	return 1;
}

static int Scripting::GetPlayerActionId(lua_State* LUAState)
{
	Actor::ActionIDs action = Actor::GetCurrentActionID(g_Robot->GetLocalPlayer());
	printf("ActionID: %d\n", action);
	lua_pushinteger(LUAState, action);
	return 1;
}

static int Scripting::GetEntityActionId(lua_State* L)
{
	UINT64 Ent = lua_tointeger(L, 1);
	Entity* e = new Entity(Ent);

	Actor::ActionIDs action = Actor::GetCurrentActionID(e);
	printf("ActionID: %d\n", action);
	lua_pushinteger(L, action);

	delete e;
	return 1;
}

static int Scripting::ActionId(lua_State* LUAState)
{
	const UINT64 EntAddr = lua_tointeger(LUAState, 1);
	printf("EntAddr: %llX\n", EntAddr);
	Entity* e = new Entity(EntAddr);

	Actor::ActionIDs action = Actor::GetCurrentActionID(e);
	lua_pushinteger(LUAState, action);
	delete e;
	return 1;
}

static int Scripting::ActionCount(lua_State* LUAState)
{
	const UINT64 EntAddr = lua_tointeger(LUAState, 1);
	Entity* e = new Entity(EntAddr);

	int actionCount = Actor::GetActionCount(e);
	lua_pushinteger(LUAState, actionCount);

	printf("Ent Addr: %llX\n", EntAddr);
	printf("Count: %d\n", actionCount);

	return 1;
}

static int Scripting::IsPlayerAlive(lua_State* LUAState)
{
	Entity* LocalEntity = g_Robot->GetLocalPlayer();
	INT currHP = Life::GetEntityHP(LocalEntity);

	if (currHP > 0)
		lua_pushboolean(LUAState, true);
	else if (currHP == 0)
		lua_pushboolean(LUAState, false);

	return 1;
}

static int Scripting::IsEntityAlive(lua_State* LUAState)
{
	const UINT64 EntAddr = lua_tointeger(LUAState, 1);

	Entity* e = new Entity(EntAddr);

	INT currHP = Life::GetEntityHP(e);

	if (currHP > 0)
		lua_pushboolean(LUAState, true);
	else if (currHP == 0)
		lua_pushboolean(LUAState, false);

	delete e;

	return 1;
}


//toggles for hax
static int Scripting::RevealMap(lua_State* LUAState)
{
	UINT64 g_POEBase = (UINT64)GetModuleHandleA("PathOfExile.exe");

	if (g_POEBase == -1)
		g_POEBase = (UINT64)GetModuleHandle(NULL);

	UINT64 PointerBase = (g_POEBase + g_ProtectionServer->Offsets[1]); // -> Addr1
	UINT64 PointerTwo = *(UINT64*)PointerBase + 0x688;// Addr1 + 0x688 = Addr2
	UINT64 PointerThree = *(UINT64*)PointerTwo + 0x58; // Addr2 + 58 -> fin
	*(UINT16*)PointerThree = 1;

	return 0;
}

static int Scripting::SetCameraZoom(lua_State* LUAState)
{
	double fZoom = lua_tonumber(LUAState, 1);

	UINT64 g_POEBase = (UINT64)GetModuleHandleA(NULL);

	UINT64 PointerBase = (g_POEBase + g_ProtectionServer->Offsets[1]); // -> ingamestate

	WritePointer<float>(PointerBase, Offsets::Hacks::NoZoomLimits, fZoom);

	return 0;
}

static int Scripting::LogToConsole(lua_State* LUAState)
{
	// Get the number of parameters
	int n = lua_gettop(LUAState);

	for (int i = 1; i <= n; i++)
	{

	}

	char* str = (char*)lua_tostring(LUAState, 1);
	int number = lua_tointeger(LUAState, 2);

	printf("[SCRIPT LOG] %s (%llX, %d)\n", str, (UINT64)str, (UINT32)str);
	return 0;
}

static int Scripting::ToggleReduceCPU(lua_State* LUAState)
{
	bool isReducing = lua_toboolean(LUAState, 1);

	UINT64 g_POEBase = (UINT64)GetModuleHandleA(NULL);

	if (isReducing)
	{
		SetHook((g_POEBase + Offsets::Hacks::GlobalLights), CPUReduceHook); //todo: fix this
	}
	else if (isReducing == false)
	{
		RemoveHook(g_POEBase + Offsets::Hacks::GlobalLights, 10, (BYTE*)"\x49\x83\xC0\x04\x89\x41\x20\x49\x8B\xD2");
	}

	return 0;
}

static int Scripting::ToggleReduceRAM(lua_State* LUAState)
{
	bool isReducing = lua_toboolean(LUAState, 1);

	if (isReducing)
	{
		if (g_Robot->haReduceRAM == NULL)
			g_Robot->haReduceRAM = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ReduceRAM, 0, 0, 0);
	}
	else
	{
		TerminateThread(g_Robot->haReduceRAM, 0);
		g_Robot->haReduceRAM = NULL;
	}

	return 0;
}

static int Scripting::SetAutoExitHP(lua_State* LUAState) //SET g_Robot VAR
{
	int exitOnHP = lua_tointeger(LUAState, 1);
	g_Robot->ExitGameOnHP = exitOnHP;

	return 0;
}

static int Scripting::ChestQuality(lua_State* LUAState)
{
	const UINT64 EntAddr = lua_tointeger(LUAState, 1);
	Entity* e = new Entity(EntAddr);

	return 1;
}

static int Scripting::IsLocked(lua_State* LUAState)
{
	const UINT64 EntAddr = lua_tointeger(LUAState, 1);
	Entity* e = new Entity(EntAddr);
	return 1;
}

static int Scripting::IsChestStrongbox(lua_State* LUAState)
{
	const UINT64 EntAddr = lua_tointeger(LUAState, 1);
	Entity* e = new Entity(EntAddr);

	return 1;
}

static int Scripting::IsOpened(lua_State* LUAState)
{
	const UINT64 EntAddr = lua_tointeger(LUAState, 1);
	Entity e = Entity(EntAddr);

	bool b = Chest::IsOpened(&e);

	lua_pushboolean(LUAState, b);

	return 1;
}

static int Scripting::IsChestOpened(lua_State* LUAState)
{
	const uint32_t entId = lua_tointeger(LUAState, 1);
		
	for each(Entity* e in g_Robot->EntityList)
	{
		if (e->GetUniqueID() == entId)
		{
			Entity ent = Entity(e->Address);

			bool b = Chest::IsOpened(&ent);
			lua_pushboolean(LUAState, b);
			return 1;
		}
	}
	
	lua_pushboolean(LUAState, false);
	return 1;

}

static int Scripting::GetEntityPosition(lua_State* LUAState)
{
	const UINT64 EntAddr = lua_tointeger(LUAState, 1);
	Entity* e = new Entity(EntAddr);
	Vector2 p = Positioned::GetGridPosition(e);

	if (p.X != 0 && p.Y != 0)
	{
		lua_pushinteger(LUAState, p.X);
		lua_pushinteger(LUAState, p.Y);

		delete e;

		return 2;
	}

	delete e;

	return 0; //return nothing on failure
}

static int Scripting::EndAction(lua_State* LUAState)
{
	UINT64 SendClass = GetSendClass();
	PacketWriter* p = PacketBuilder::EndAction();
	if (SendClass != 0)
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	
	delete[] p->GetBuffer();
	delete p;

	g_Robot->IsMoving = false;

	return 0;
}


static int Scripting::GetPlayerLvl(lua_State* LUAState)
{
	Entity* LocalEntity = g_Robot->GetLocalPlayer();
	byte Lvl = Player::GetPlayerLevel(LocalEntity);
	
	lua_pushinteger(LUAState, Lvl);

	return 1;
}

static int Scripting::GetPlayerExp(lua_State* LUAState)
{
	Entity* LocalEntity = g_Robot->GetLocalPlayer();
	long exp = Player::GetPlayerExperience(LocalEntity);

	lua_pushinteger(LUAState, exp);

	return 1;
}

static int Scripting::GetLocalPlayerName(lua_State* LUAState)
{
	Entity* LocalEntity = g_Robot->GetLocalPlayer();

	std::wstring name = Player::GetPlayerName(LocalEntity);

	if (name.size() > 0)
	{
		char utfName[50];
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &name[0], (int)name.size(), NULL, 0, NULL, NULL);
		std::string strTo(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &name[0], (int)name.size(), &utfName[0], size_needed, NULL, NULL);

		lua_pushstring(LUAState, utfName);

		return 1;
	}
	else
		return 0;

}

static int Scripting::GetEntityPlayerName(lua_State* LUAState)
{
	const UINT64 EntAddr = lua_tointeger(LUAState, 1);
	Entity* e = new Entity(EntAddr);
	std::wstring name = Player::GetPlayerName(e);

	if (name.size() > 0)
	{
		char utfName[50];
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &name[0], (int)name.size(), NULL, 0, NULL, NULL);
		std::string strTo(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &name[0], (int)name.size(), &utfName[0], size_needed, NULL, NULL);

		printf("%s\n", utfName);

		lua_pushstring(LUAState, utfName);

		delete e;

		return 1;
	}
	else
		return 0;


}

static int Scripting::SpamPacket(lua_State* LUAState)
{
	const int count = lua_tointeger(LUAState, 1);
	const int delay = lua_tointeger(LUAState, 2);
	const char* str = lua_tostring(LUAState, 3);

	BYTE* hexbytes = PacketHelper::ToPacketFormat((char*)str);
	DWORD length = PacketHelper::GetPacketLength((char*)str);

	for (int i = 0; i < count; i++)
	{
		UINT64 SendClass = GetSendClass();
		SendPacket(SendClass, hexbytes, length);
		Sleep(delay);
	}

	delete[] hexbytes;

	return 0;
}

static int Scripting::BuildBlightTower(lua_State* LUAState)
{

	return 0;
}

static int Scripting::FollowPlayer(lua_State* LUAState)
{
	const char* name = lua_tostring(LUAState, 1);
	wchar_t wName[50];
	mbstowcs(&wName[0], name, strlen(name)+1);

	if (wName != NULL)
	{
		wcscpy(g_Robot->FollowingPlayerName, wName);
		g_Robot->IsFollowingActor = true;
		g_Robot->FollowPlayerSkill = Input::InputIds::RUN;
		wprintf(L"[AUTO-FOLLOW] Following: %s\n", g_Robot->FollowingPlayerName);
		//need to hook entities then the rest will follow
	}
	else
	{
		printf("Failed to fetch playerName in Scripting::FollowPlayer.\n");
	}


	return 0;
}

static int Scripting::EnterAreaTransitions(lua_State* LUAState)
{
	bool isEntering = lua_toboolean(LUAState, 1);

	g_Robot->isAutoEnteringAreaTransition = isEntering;

	return 0;
}

static int Scripting::GetItemSockets(lua_State* LUAState)
{
	UINT64 EntAddr = lua_tointeger(LUAState, 1);

	Entity* Item = new Entity(EntAddr);
	GroundItem* subItem = Item->GetInnerItemEntity();

	int Sockets = Sockets::GetNumberOfSockets(subItem);

	lua_pushinteger(LUAState, Sockets);

	return 1;
}

static int Scripting::IsItemFullyLinked(lua_State* LUAState)
{
	UINT64 EntAddr = lua_tointeger(LUAState, 1);

	Entity* Item = new Entity(EntAddr);
	GroundItem* subItem = Item->GetInnerItemEntity();

	bool Linked = Sockets::isItemFullyLinked(subItem);

	lua_pushboolean(LUAState, Linked);

	return 1;
}

static int Scripting::KillNearestMonster(lua_State* L)
{
	Vector2 v = g_Robot->GetLocalPlayer()->GetVector2();
	Vector2 TargetVector;
	Entity* entPtr;
	int distance = 0;
	int tempDistance = 0;

	for (auto& e : g_Robot->Attacker->MonsterList)
	{
		Vector2 MobVector = e->GetVector2();
		distance = Distances::GetDistanceBetweenObjects(v, MobVector);
		printf("Distance from Mob %u: %d\n", e->GetUniqueID(), distance);
		
		if (distance < tempDistance)
		{
			
			if (MobVector.X != 0 && MobVector.Y != 0)
			{
				tempDistance = distance;
				TargetVector.X = MobVector.X; 
				TargetVector.Y = MobVector.Y;
				entPtr = e;
			}		
		}	
	}

	printf("Lowest distance: %d\n", tempDistance);

	while (Life::GetEntityHP(entPtr) > 0)
	{
		FileIO::Log("Entity HP > 0, Using skill.\n");
		//now use skill
		PacketWriter* p = PacketBuilder::Action(g_Robot->Attacker->AttackingSkill, NULL, TargetVector.X, TargetVector.Y);
		UINT64 SendClass = GetSendClass();
		if (SendClass != NULL)
		{
			SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
			g_Robot->EndAction();
		}

		Sleep(100);
	}

	return 0;
}

static int Scripting::UnloadDLL(lua_State* L)
{
	FreeLibraryAndExitThread(GetModuleHandleA("GoPoE.dll"), 1); //need to exit every thread ?	
	//FreeLibraryAndExitThread(g_OurModule, 1);

	return 0;
}

static int Scripting::LootGroundItems(lua_State* L)
{
	Vector2 v = g_Robot->GetLocalPlayer()->GetVector2();

	for (auto& e : g_Robot->GroundItemList)
	{
		if (Distances::IsPointInCircle(v.X, v.Y, e->GetVector2().X, e->GetVector2().Y))
		{
			if (Targetable::IsTargetable(e))
			{
				PacketWriter* p = PacketBuilder::EntityInteraction(e->GetUniqueID(), 0x0266);
				UINT64 SendClass = GetSendClass();
				if (SendClass != NULL)
				{
					SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
					g_Robot->EndAction();
					Sleep(1000);
					SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
					g_Robot->EndAction();
				}
			}

			g_Robot->GroundItemList.remove(e); //we assume item is looted as its no longer targetable
		}		
	}

	return 0;
}

static int Scripting::SelectNPCDialog(lua_State* L)
{
	byte index = lua_tointeger(L, 1);

	PacketWriter* p = PacketBuilder::SelectNPCDialog(index);
	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete[] p->GetBuffer();
	delete p;

	return 0;
}

static int Scripting::ExitNPCDialog(lua_State* L)
{
	PacketWriter* p = PacketBuilder::ExitNPCDialog();
	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete[] p->GetBuffer();
	delete p;

	return 0;
}


static int Scripting::PlaceItemInTrade(lua_State* L)
{
	uint32_t index = lua_tointeger(L, 1);
	byte CellX = lua_tointeger(L, 2);
	byte CellY = lua_tointeger(L, 3);

	PacketWriter* p = PacketBuilder::PlaceItemInSellWindow(index,CellX,CellY);
	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete[] p->GetBuffer();
	delete p;


	return 0;
}

static int Scripting::CancelTrade(lua_State* L) //not for npc trades!
{
	PacketWriter* p = PacketBuilder::CancelTrade();
	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete[] p->GetBuffer();
	delete p;

	return 0;
}

static int Scripting::PlayerMessage(lua_State* L)
{
	const char* Msg = lua_tostring(L, 1); // get function argument

	const size_t cSize = strlen(Msg) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, Msg, cSize);

	PacketWriter* p = PacketBuilder::PlayerMessage(wc);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete p;


	return 0;
}

static int Scripting::GetEntityComponentAddress(lua_State* L)
{
	UINT64 EntAddr = lua_tointeger(L, 1);
	EntAddr = EntAddr - sizeof(UINT64);

	const char* ComponentName = lua_tostring(L, 2); // get function argument
	UINT64 ComponentAddr = 0;

	Entity* e = new Entity(EntAddr);

	ComponentAddr = e->GetComponentAddress((char*)ComponentName);

	if (ComponentAddr > NULL)
	{
		FileIO::Log("Got entity component addr: %llX\n", ComponentAddr);

		if (ComponentAddr != NULL)
			lua_pushinteger(L, ComponentAddr);
		else
			lua_pushinteger(L, NULL);

		delete e;

		return 1;
	}
	else
	{
		FileIO::Log("Component was NULL..\n", ComponentAddr);
		return 0;
	}

}

static int Scripting::IsEntityInList(lua_State* L)
{
	bool inList = false;
	const char* filePath = lua_tostring(L, 1); // get function argument

	const size_t cSize = strlen(filePath) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, filePath, cSize);

	for each(auto& e in g_Robot->EntityList)
	{
		if (wcscmp(e->FilePath, wc) == 0)
		{
			inList = true;
		}
	}

	lua_pushboolean(L, inList);

	return 1;
}

static int Scripting::SelectPantheonGod(lua_State* L)
{
	byte god = lua_tointeger(L, 1);

	PacketWriter* p = PacketBuilder::ChoosePantheonGod(god);
	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete[] p->GetBuffer();
	delete p;

	return 0;
}

static int Scripting::GetEntityId(lua_State* L)
{
	uint32_t id = 0;
	uint64_t addr = lua_tointeger(L, 1);

	if (addr != NULL)
	{
		Entity* e = new Entity(addr - sizeof(UINT64));

		id = e->GetUniqueID();
		printf("id: %d\n", id);
		lua_pushinteger(L, id);
		delete e;

		return 1;
	}
	else
		return 0;
}

static int Scripting::UseWaypoint(lua_State* L) //for waypoints... zone to zone is an interaction with 0x0C as last short
{
	short mapHash = lua_tointeger(L, 1);
	uint32_t id = lua_tointeger(L, 2);
	bool newInstance = lua_toboolean(L, 3);

	PacketWriter* p = PacketBuilder::UseWaypoint(mapHash, id, newInstance);
	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete[] p->GetBuffer();
	delete p;

	return 0;
}

static int Scripting::GetEntityByName(lua_State* L)
{
	uint64_t EntityAddr = 0;
	bool inList = false;
	const char* filePath = lua_tostring(L, 1); // get function argument

	const size_t cSize = strlen(filePath) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, filePath, cSize);

	for each(auto& e in g_Robot->EntityList)
	{
		if (wcscmp(e->FilePath, wc) == 0)
		{
			inList = true;
			EntityAddr = e->Address - 8;
			lua_pushinteger(L, EntityAddr);
			FileIO::Log("Returning addr %llX.\n", EntityAddr);
			return 1;
		}
	}

	FileIO::Log("[DEBUG] Entity name not found in list. Could not get address.\n");

	return 0;
}

static int Scripting::GetEntityIdByName(lua_State* L) //works on full names only, not partial matches
{
	bool inList = false;
	uint32_t id = 0;
	const char* filePath = lua_tostring(L, 1); // get function argument

	const size_t cSize = strlen(filePath) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, filePath, cSize);

	for each(Entity* e in g_Robot->EntityList)
	{
		//__try
		//{
			wchar_t* s = e->GetFilePathFromMemory();
			if (s != NULL)
			{
				if (wcscmp(s, wc) == 0)
				{
					inList = true;
					id = e->GetUniqueID();
					lua_pushinteger(L, id);
					FileIO::Log("Returning id %d.\n", id);
					delete wc;
					return 1;
				}

				wprintf(L"%s\n", s);
			}
		//}
		//__except (EXCEPTION_EXECUTE_HANDLER)
		//{
		//	continue;
		//}
	}

	FileIO::Log("[DEBUG] Entity name not found in list. Could not get ID.\n");

	delete wc;
	return 0;
}

static int Scripting::BlightTower(lua_State* L)
{
	uint16_t id = lua_tointeger(L, 1);
	uint16_t type = lua_tointeger(L, 2);

	PacketWriter* p = PacketBuilder::CreateBlightTower(id, type);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete p;
	return 0;
}

static int Scripting::DiscardEntity(lua_State* L)
{
	uint64_t addr = lua_tointeger(L, 1);

	for each(auto& e in g_Robot->EntityList)
	{
		if (addr == e->Address-8)
		{
			g_Robot->EntityList.remove(e);
			FileIO::Log("Discarding entity with id %d.\n", e->GetUniqueID());
			break;
		}
	}


	return 0;
}

static int Scripting::SelectInstance(lua_State* L)
{
	byte instanceIndex = lua_tointeger(L, 1);

	PacketWriter* p = PacketBuilder::JoinInstance(instanceIndex);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete p;
	return 0;
}

static int Scripting::CallLUAFromC(lua_State* L)
{
	const char* name = lua_tostring(L, 1);
	lua_getglobal(L, name);  /* function to be called */

	/* call the function in Lua (2 arguments, 2 return) */
	if (lua_pcall(L, 2, 2, 0) != 0)
	{
		printf("error: %s\n", lua_tostring(L, -1));
		return 0;
	}
	int ret1 = lua_tonumber(L, -1);
	int ret2 = lua_tonumber(L, -1);
	printf("returned: %d %d\n", ret1, ret2);

	return 0;
}

static void Scripting::StackDump(lua_State *L) {
	int i;
	int top = lua_gettop(L);
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		int t = lua_type(L, i);
		switch (t) {

		case LUA_TSTRING:  /* strings */
			printf("`%s'", lua_tostring(L, i));
			break;

		case LUA_TBOOLEAN:  /* booleans */
			printf(lua_toboolean(L, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:  /* numbers */
			printf("%g", lua_tonumber(L, i));
			break;

		default:  /* other values */
			printf("%s", lua_typename(L, t));
			break;

		}
		printf("  ");  /* put a separator */
	}
	printf("\n");  /* end the listing */
}

static int Scripting::PlaceExplosive(lua_State* L)
{
	uint32_t x = lua_tointeger(L, 1);
	uint32_t y = lua_tointeger(L, 2);
	uint32_t count = lua_tointeger(L, 3);

	PacketWriter* p = PacketBuilder::PlaceExplosive(x, y, count);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete p;
	return 0;
}

static int Scripting::SpawnAtlasPortals(lua_State* L)
{
	//SpawnAtlasInstance(UINT16 ItemIndex, byte listSelection, byte callingMaven, byte masterSelection);
	short itemIndex = lua_tointeger(L, 1);
	byte listSelection = lua_tointeger(L, 2);
	byte callingMaven = lua_tointeger(L, 3);

	PacketWriter* p = PacketBuilder::SpawnAtlasInstance(itemIndex, listSelection, callingMaven);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	return 0;
}

static int Scripting::InventoryItemToNPCWindow(lua_State* L) //last 2 bytes of packet become 0xFF if autoclick
{
	const char* itemName = lua_tostring(L, 1);

	const size_t cSize = strlen(itemName) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, itemName, cSize);

	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		if (wcscmp(i->FullName.c_str(), wc) == 0)
		{
			PacketWriter* p = PacketBuilder::PlaceItemInSellWindow(i->InventoryEntityId, -1, -1);
			
			UINT64 SendClass = GetSendClass();

			if (SendClass != NULL)
			{
				SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
			}

			delete p;
		}
	}

	return 0;
}

static int Scripting::InventoryToWindow_Item(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	int page = lua_tointeger(L, 2);

	uint32_t entityId = 0;

	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		if (wcscmp(i->FullName.c_str(), wc) == 0)
		{
			entityId = i->InventoryEntityId;
		}
	}

	if (entityId)
	{
		PacketWriter* p = PacketBuilder::InventoryToStash(entityId, page);
		UINT64 SendClass = GetSendClass();

		if (SendClass != NULL)
		{
			SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
		}

		delete p;
	}

	return 0;
}

static int Scripting::WindowToInventory_Item(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	uint32_t entityId = 0;

	g_Robot->TradeWindowRemote->Items = g_Robot->TradeWindowRemote->GetTradeWindowItems(1, true);

	for each(Item* i in g_Robot->TradeWindowRemote->Items)
	{
		if (wcscmp(i->FullName.c_str(), wc) == 0)
		{
			entityId = i->InventoryEntityId;
		}
	}

	PacketWriter* p = PacketBuilder::WindowToInventory(entityId, 1);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	return 0;
}

static int Scripting::ReadInventoryItems(lua_State* L)
{
	uint64_t offset = lua_tointeger(L, 1);

	if (offset > 0)
	{
		g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems(offset);
	}
	else
	{
		g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();
	}
	
	for each(Item* i in g_Robot->NormalInv->Items)
	{
		wprintf(L"%s (x%d) at Slots %d, %d with ItemId %d.\n", i->FullName.c_str(), i->stackSize, i->CellX, i->CellY, i->InventoryEntityId);
	}

	return 1;
}

static int Scripting::ReadCurrencyStashTab(lua_State* L)
{
	static int tabPage = lua_tointeger(L, 1);
	g_Robot->CurrencyInv->Items = g_Robot->CurrencyInv->GetInventoryItems();

	for each(Item* i in g_Robot->CurrencyInv->Items)
	{
		wprintf(L"%s (x%d) at Slots %d, %d with ItemId %d.\n", i->FullName.c_str(), i->stackSize, i->CellX, i->CellY, i->InventoryEntityId);
	}

	return 0;
}

static int Scripting::GetItemAtSlots(lua_State * L)
{
	static int x = lua_tointeger(L, 1);
	static int y = lua_tointeger(L, 2);

	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		if (i->CellX == x && i->CellY == y)
		{
			wprintf(L"%s (x%d) at Slots %d, %d with ItemId %d.\n", i->FullName.c_str(), i->stackSize, i->CellX, i->CellY, i->InventoryEntityId);
			lua_pushinteger(L, i->InventoryEntityId);
			return 1;
		}
	}

	return 0;
}

static int Scripting::ReadAllElements(lua_State* L)
{
	std::list<ElementBase*> elements = Element::GetScreenElements();

	for each(ElementBase* element in elements)
	{
		wprintf(L"Element %d: Label: %s\n", element->GetElementId(), element->GetLabel().c_str()); 
	}

	//not sure how we're to push all the elements back to LUA
	return 0;
}

static int Scripting::SelectStashTab(lua_State* L)
{
	int tab = lua_tointeger(L, 1);

	PacketWriter* p = PacketBuilder::ChangeCurrentStashTab(tab);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}
	
	delete p;

	return 0;
}

static int Scripting::GetItemsInStashTab(lua_State* L)
{
	int tab = lua_tointeger(L, 1);

	if (g_Robot->StashInv != NULL)
	{
		g_Robot->StashInv[tab]->Items = g_Robot->StashInv[tab]->GetInventoryItemsAtTab(tab);

		for each(Item* i in g_Robot->StashInv[tab]->Items)
		{
			wprintf(L"Item Element %s (%s, %s) at %llX (Cell %d, %d)\n", i->ItemEnt->GetFilePathFromMemory(), i->BaseName.c_str(), i->UniqueName.c_str(), i->MemoryAddress, i->CellX, i->CellY);
		}
	}
	else
		printf("Stash not initialized..\n");

	return 0;
}

static int Scripting::TestItemSell(lua_State* L)
{
	g_Robot->AutoTradeThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&AutoSell, 0, 0, 0);

	return 0;
}

static int Scripting::ReadTradeWindowItems(lua_State* L)
{
	int side = lua_tointeger(L, 1);
	bool loadedStash = lua_toboolean(L, 2);

	if (side == Inventory::TradeWindowSide::Local)
	{
		g_Robot->TradeWindowLocal->Items = g_Robot->TradeWindowLocal->GetTradeWindowItems(side, loadedStash);

		for each(Item* i in g_Robot->TradeWindowLocal->Items)
		{
			wprintf(L"Item Element %s at %llX (Cell %d, %d)\n", i->ItemEnt->GetFilePathFromMemory(), i->MemoryAddress, i->CellX, i->CellY);
		}
	}
	else
	{
		g_Robot->TradeWindowRemote->Items = g_Robot->TradeWindowRemote->GetTradeWindowItems(side, loadedStash);

		for each(Item* i in g_Robot->TradeWindowRemote->Items)
		{
			wprintf(L"Item Element %s at %llX (Cell %d, %d)\n", i->ItemEnt->GetFilePathFromMemory(), i->MemoryAddress, i->CellX, i->CellY);
		}
	}

	return 0;
}

static int Scripting::InviteToParty(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	PacketWriter* p = PacketBuilder::InviteToParty(wc);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete p;

	return 0;
}

static int Scripting::KickFromParty(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	PacketWriter* p = PacketBuilder::CancelPartyInvite(wc);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete p;

	return 0;
}

static int Scripting::InventoryContainsItem(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();

	for each(auto& e in g_Robot->NormalInv->Items)
	{
		if (wcscmp(e->FullName.c_str(), wc) == 0)
		{
			lua_pushboolean(L, true);
			wprintf(L"Inventory contains item: %s\n", e->ItemEnt->GetFilePathFromMemory());
			return 1;
		}
	}

	lua_pushboolean(L, false);
	return 1;
}

static int Scripting::CurrencyTabContainsItem(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	for each (Item* i in g_Robot->CurrencyInv->Items)
	{
		if (wcscmp(wc, i->FullName.c_str()) == 0)
		{
			lua_pushboolean(L, true);
			wprintf(L"Inventory contains item: %s\n", i->ItemEnt->GetFilePathFromMemory());
			return 1;
		}
	}

	lua_pushboolean(L, false);
	return 1;
}

static int Scripting::StashTabPageContainsItem(lua_State* L)
{
	const int tab = lua_tointeger(L, 1);
	const char* name = lua_tostring(L, 2);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	for each (Item* i in g_Robot->StashInv[tab]->Items)
	{
		if (wcscmp(wc, i->FullName .c_str()) == 0)
		{
			lua_pushboolean(L, true);
			wprintf(L"Inventory contains item: %s\n", i->ItemEnt->GetFilePathFromMemory());
			return 1;
		}
	}

	lua_pushboolean(L, false);
	return 1;
}

static int Scripting::WindowContainsItem(lua_State* L)
{
	const int side = lua_tointeger(L, 1);
	const char* name = lua_tostring(L, 2);
	int quant = lua_tointeger(L, 3);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	if (side == Inventory::TradeWindowSide::Local)
	{
		if (g_Robot->TradeWindowLocal->ContainsItem((Inventory::TradeWindowSide)side, wc, quant, false))
		{
			lua_pushboolean(L, true);
			return 1;
		}

	}
	else if (side == Inventory::TradeWindowSide::Remote)
	{
		if (g_Robot->TradeWindowRemote->ContainsItem((Inventory::TradeWindowSide)side, wc, quant, false))
		{
			lua_pushboolean(L, true);
			return 1;
		}
	}

	lua_pushboolean(L, false);
	return 1;
	
}

static int Scripting::KillMonster(lua_State* L)
{
	uint64_t EntAddr = lua_tointeger(L, 1);

	if (EntAddr != NULL)
	{
		Entity* e = new Entity(EntAddr);
		g_Robot->Attacker->KillMonster(e);
		delete e;
	}

	return 0;
}

static int Scripting::GetNumberOfItems(lua_State* L)
{
	const char* Name = lua_tostring(L, 1);
	
	const size_t cSize = strlen(Name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, Name, cSize);

	int total = 0;

	for (int i = 0; i < 4; i++)
	{
		g_Robot->StashInv[i]->Items = g_Robot->StashInv[i]->GetInventoryItemsAtTab(i);

		for each (Item* item in g_Robot->StashInv[i]->Items)
		{
			if (wcscmp(wc, item->FullName.c_str()) == 0)
			{
				total += item->stackSize;
			}
		}
	}

	wprintf(L"Inventory contains %d items\n", total);
	lua_pushinteger(L, total);
	return 1;
}

static int Scripting::GetNumberOfInventoryItems(lua_State* L)
{
	const char* Name = lua_tostring(L, 1);

	const size_t cSize = strlen(Name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, Name, cSize);

	int total = 0;


	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();

	for each (Item* item in g_Robot->NormalInv->Items)
	{
		if (wcscmp(wc, item->FullName.c_str()) == 0)
		{
			total += item->stackSize;
		}
	}
	
	wprintf(L"Inventory contains %d items\n", total);
	lua_pushinteger(L, total);
	return 1;
}

/*
0 = Warrior
1 = Archer
2 = Mage
3 = Templar
4 = Shadow
5 = Duelist
6 = Scion
*/
static int Scripting::GetPlayerClass(lua_State* L)
{
	uint64_t EntAddr = lua_tointeger(L, 1);

	if (EntAddr != NULL)
	{
		Entity* e = new Entity(EntAddr);
		byte pClass = Player::GetPlayerClass(e);
		wprintf(L"PlayerClass: %d\n", pClass);

		lua_pushinteger(L, pClass);
		delete e;
		return 1;
	}

	return 0;
}

static int Scripting::AcceptTrade(lua_State* L) //this packet oddly changes based on # of items youre selling...?
{
	int unk1 = lua_tointeger(L, 1);

	PacketWriter* p = PacketBuilder::AcceptTrade(unk1);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete p;
	return 0;
}

static int Scripting::GetDelveEncounterObject(lua_State* L)
{
	for each(Entity* e in g_Robot->EntityList)
	{
		if (e != NULL)
		{
			if (e->GetFilePathFromMemory() != NULL)
			{
				if (wcsstr(e->GetFilePathFromMemory(), L"Delve/Objects/EncounterControlObjects") != NULL)
				{
					lua_pushinteger(L, e->GetUniqueID());
					return 1;
				}
			}
		}
	}

	return 0;
}

static int Scripting::PrintEntityList(lua_State* L)
{
	for each(Entity* e in g_Robot->EntityList)
	{
		if (e->GetFilePathFromMemory() != NULL)
			wprintf(L"%s (id: %d, at %llX)\n", e->GetFilePathFromMemory(), e->GetUniqueID(), e->Address);
	}

	return 0;
}

static int Scripting::PrintMonsterList(lua_State* L)
{
	for each (Entity * e in g_Robot->MonsterList)
	{
		if (e->GetFilePathFromMemory() != NULL)
			wprintf(L"%s (id: %d, at %llX)\n", e->GetFilePathFromMemory(), e->GetUniqueID(), e->Address);
	}

	return 0;
}

static int Scripting::ClearEntityList(lua_State* L)
{
	g_Robot->EntityList.clear();
	return 0;
}

static int Scripting::SelfSkill(lua_State* L) //works like a toggle, no bool
{
	if (g_Robot->Attacker->IsBusy || g_Robot->Disconnected)
		return 0;

	int SkillSlot = lua_tointeger(L, 1);

	Entity* e = g_Robot->GetLocalPlayer();

	if (e == NULL)
		return 0;

	DWORD id = e->GetUniqueID();
	delete e;
	
	PacketWriter* p = PacketBuilder::SelfSkill(id, SkillSlot);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete p;
	return 0;
}

static int Scripting::GetCurrentMap(lua_State* L)
{
	if (g_Robot->ReadableAreaName.size() > 0)
	{
		lua_pushstring(L, g_Robot->ReadableAreaName.c_str());
		return 1;
	}
	else
	{
		return 0;
	}
}

static int Scripting::GetNumberMapName(lua_State* L)
{
	if (g_Robot->NumberedAreaName.size() > 0)
	{
		lua_pushstring(L, g_Robot->NumberedAreaName.c_str());
		return 1;
	}
	else
		return 0;
}


static int Scripting::ExitToCharacterScreen(lua_State* L)
{
	PacketWriter* p = PacketBuilder::ExitToCharScreen();
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete p;
	return 0;
}

static int Scripting::ExitToLoginScreen(lua_State* L)
{
	PacketWriter* p = PacketBuilder::ExitToLoginScreen();
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete p;
	return 0;
}

static int Scripting::SelectCharacter(lua_State* L)
{
	BYTE index = lua_tointeger(L, 1);

	PacketWriter* p = PacketBuilder::SelectCharacter(index);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete p;

	return 0;
}

static int Scripting::Login(lua_State* L)
{
	return 0;
}

static int Scripting::UseInventoryItem(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	uint32_t entityId = 0;

	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		if (wcscmp(i->FullName.c_str(), wc) == 0)
		{
			entityId = i->InventoryEntityId;
		}
	}

	if (entityId)
	{
		PacketWriter* p = PacketBuilder::ConsumeInventoryItem(entityId);
		UINT64 SendClass = GetSendClass();

		if (SendClass != NULL)
		{
			SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
		}

		delete p;
	}

	return 1;
}

static int Scripting::UseInventoryItemId(lua_State* L)
{
	UINT32 Id = lua_tointeger(L, 1);

	PacketWriter* p = PacketBuilder::ConsumeInventoryItem(Id);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	delete p;
	

	return 1;
}

static int Scripting::IsCharacterStuck(lua_State* L)
{
	Vector2 v = g_Robot->GetLocalPlayer()->GetVector2();

	if (g_Robot->Disconnected || g_Robot->Attacker->IsBusy)
		return 0;

	Entity* e = g_Robot->GetLocalPlayer();

	if (e == NULL)
		return 0;

	while (Actor::GetCurrentActionID(e) != Actor::ActionIDs::ACTION_NONE)	
		Sleep(50);
	
	g_Robot->Attacker->WalkInFacingDirection();

	Sleep(500);

	Vector2 v2 = g_Robot->GetLocalPlayer()->GetVector2();

	if (v.X == v2.X && v.Y == v2.Y)
	{
		printf("[INFO] Player :: Wall Collision = true!\n");
		lua_pushboolean(L, true);
	}
	else
	{
		lua_pushboolean(L, false);
	}

	delete e;
	return 1;
}

static int Scripting::IsCharacterStuckInDirection(lua_State* L)
{
	int X = lua_tointeger(L, 1);
	int Y = lua_tointeger(L, 2);

	Vector2 v = g_Robot->GetLocalPlayer()->GetVector2();

	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		PacketWriter* p = PacketBuilder::Action(g_Robot->Attacker->MovementSkill, NULL, X, Y);
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
		delete p;
		g_Robot->EndAction();
	}
	else
		return 0;

	Sleep(1500);

	while (Actor::GetCurrentActionID(g_Robot->GetLocalPlayer()) != Actor::ActionIDs::ACTION_NONE)
	{
		Sleep(500);
	}

	Vector2 v2 = g_Robot->GetLocalPlayer()->GetVector2();

	if (v.X == v2.X && v.Y == v2.Y)
	{
		printf("[INFO] Player :: Wall Collision = true!\n");
		lua_pushboolean(L, true);
	}
	else
	{
		lua_pushboolean(L, false);
	}

	return 1;
}

static int Scripting::GetInventoryItemId(lua_State* L)
{
	const char* name = lua_tostring(L, 1);
	const UINT64 offset = lua_tointeger(L, 2);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems(offset);

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		if (wcscmp(i->FullName.c_str(), wc) == 0)
		{
			uint32_t itemId = i->InventoryEntityId;
			lua_pushinteger(L, itemId);
			return 1;
		}
	}
	
	//case if not found
	lua_pushinteger(L, 0);
	return 1;
}

static int Scripting::GetStashInventoryItemId(lua_State* L)
{
	const char* name = lua_tostring(L, 1);
	int tab = lua_tointeger(L, 2);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);


	g_Robot->StashInv[tab]->Items = g_Robot->StashInv[tab]->GetInventoryItems();

	for each(Item* i in g_Robot->StashInv[tab]->Items)
	{
		if (wcscmp(i->FullName.c_str(), wc) == 0)
		{
			uint32_t itemId = i->InventoryEntityId;
			lua_pushinteger(L, itemId);
			return 1;
		}
	}

	//case if not found
	lua_pushinteger(L, 0);
	return 1;
}

//12 long by 5 wide inventory
static int Scripting::IsInventoryFull(lua_State* L)
{
	bool full = false;
	int CellsOccupied = 0;

	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		int x = i->CellX; //check these offsets
		int y = i->CellY;
		int width = i->Width;
		int height = i->Height;

		int nCells = width * height;

		CellsOccupied += nCells;

		if (g_Robot->DebugMode)
		{
			printf("Cell taken by item (%s): %d\n", i->FullName.c_str(), nCells);
		}		
	}

	printf("Cells occupied: %d\n", CellsOccupied);

	if (CellsOccupied == 60)
		lua_pushboolean(L, true);
	else
		lua_pushboolean(L, false);

	return 1;
}

static int Scripting::GetMonsterCount(lua_State* L)
{
	int count = 0;

	for each(Entity* e in g_Robot->Attacker->MonsterList)
	{
		if (Life::GetEntityHP(e) > 0 && Targetable::IsTargetable(e))
			count++;
	}

	lua_pushinteger(L, count);

	return 1;
}

static int Scripting::UseBuffs(lua_State* L)
{
	/*if (g_Robot->Attacker->BuffList.size() == 0)
	{
		if (g_Robot->Attacker->FillBuffListFromFile())
		{
			g_Robot->Attacker->UseBuffList();
		}
		else
		{
			return 1;
		}
	}
	else
	{
		g_Robot->Attacker->UseBuffList();
	}*/

	return 1;
}

static int Scripting::UseSkillsFromFile(lua_State* L)
{
	if (g_Robot->Attacker->SkillsList.size() == 0)
	{
		if (g_Robot->Attacker->FillSkillsListFromFile())
		{
			g_Robot->Attacker->UseSkillsList();
		}
		else
		{
			return 1;
		}
	}
	else
	{
		g_Robot->Attacker->UseSkillsList();
	}


	return 1;
}

static int Scripting::GetFlaskList(lua_State* L)
{
	bool LoadedInv = lua_toboolean(L, 1);

	g_Robot->FlaskList = Inventory::GetFlasks(LoadedInv);

	int count = 1;

	for each(Item* i in g_Robot->FlaskList)
	{
		wprintf(L"Flask %d: %s\n", count, i->FullName.c_str());
		count++;
	}

	return 1;
}


static int Scripting::InventoryToStash(lua_State* L)
{
	const char* name = lua_tostring(L, 1);
	int tab = lua_tointeger(L, 2);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		if (wcscmp(wc, i->FullName.c_str()) == 0)
		{
			uint32_t entityId = i->InventoryEntityId;
			
			PacketWriter* p = PacketBuilder::AutoPlaceItemToStash(tab, entityId, 0);
			UINT64 SendClass = GetSendClass();

			if (SendClass != NULL)
			{
				SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
			}

			delete p;

			break;
		}
	}

	return 0;
}

static int Scripting::StashToInventory(lua_State* L)
{
	const char* name = lua_tostring(L, 1);
	int tab = lua_tointeger(L, 2);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	g_Robot->StashInv[tab]->Items = g_Robot->StashInv[tab]->GetInventoryItems();

	for each(Item* i in g_Robot->StashInv[tab]->Items)
	{
		if (wcscmp(wc, i->FullName.c_str()) == 0)
		{
			uint32_t entityId = i->InventoryEntityId;

			PacketWriter* p = PacketBuilder::AutoPlaceItemFromStash(tab, entityId, 0);
			PacketBuilder::Send(p);
			break;
		}
	}

	return 0;

}

static int Scripting::UseItemOnItem(lua_State* L)
{
	uint32_t inventory1 = lua_tointeger(L, 1);
	uint32_t itemId1 = lua_tointeger(L, 2);
	uint32_t inventory2 = lua_tointeger(L, 3);
	uint32_t itemId2 = lua_tointeger(L, 4);

	PacketWriter* p = PacketBuilder::UseItemOnOtherItem(inventory1, itemId1, inventory2, itemId2);
	PacketBuilder::Send(p);

	return 0;
}

static int Scripting::ChainedMovement(lua_State* L)
{
	int x = lua_tointeger(L, 1);
	int y = lua_tointeger(L, 2);
	
	PacketWriter* p = PacketBuilder::ChainedAction(x,y);
	PacketBuilder::Send(p);
    
	return 0;
}

static int Scripting::OpenChests(lua_State* L)
{
	for each(Entity* c in g_Robot->EntityList)
	{
		if (c->GetComponentAddress("Chest") > 0)
		{
			if (!Chest::IsLocked(c))
			{
				while (!Chest::IsOpened(c))
				{
					g_Robot->Attacker->IsBusy = true;
					PacketWriter* p = PacketBuilder::EntityInteraction(c->GetUniqueID(), Input::InputIds::INTERACTION);
					PacketBuilder::Send(p);
					g_Robot->EndAction();
					Sleep(1000);
				}
			}

			delete c;
		}
	}

	return 0;
}

//0x8D for atlas
//0x0D for retracting from atlas
static int Scripting::InventoryToMapWindow(lua_State* L)
{
	const char* name = lua_tostring(L, 1);
	const UINT64 offset = lua_tointeger(L, 2);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems(offset);

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		if (wcscmp(wc, i->FullName.c_str()) == 0)
		{
			uint32_t entityId = i->InventoryEntityId;

			PacketWriter* p = PacketBuilder::InventoryToMapWindow(entityId, 0, 0x8D);
			PacketBuilder::Send(p);
			lua_pushboolean(L, true);
			return 1;
		}
	}

	for each(Item* i in g_Robot->NormalInv->Items) //match partial name for random maps, InventoryToMapWindow("Map")
	{
		if (wcsstr(wc, i->FullName.c_str()) != NULL)
		{
			uint32_t entityId = i->InventoryEntityId;

			PacketWriter* p = PacketBuilder::InventoryToMapWindow(entityId, 0, 0x8D);
			PacketBuilder::Send(p);
			lua_pushboolean(L, true);
			return 1;
		}
	}

	lua_pushboolean(L, false);
	return 1;
}

static int Scripting::InventoryIdToMapWindow(lua_State* L)
{
	const uint32_t id = lua_tointeger(L, 1);

	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		if (id == i->InventoryEntityId)
		{
			PacketWriter* p = PacketBuilder::InventoryToMapWindow(id, 0, 0x8D);
			PacketBuilder::Send(p);
			lua_pushboolean(L, true);
			return 1;
		}
	}

	lua_pushboolean(L, false);
	return 1;
}


static int Scripting::MapWindowToInventory(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		if (wcscmp(wc, i->FullName.c_str()) == 0)
		{
			uint32_t entityId = i->InventoryEntityId;

			PacketWriter* p = PacketBuilder::InventoryToMapWindow(entityId, 0, 0x0D);
			PacketBuilder::Send(p);
			lua_pushboolean(L, true);
			return 1;
		}
	}

	lua_pushboolean(L, false);
	return 1;
}

static int Scripting::GetMonstersId(lua_State* L)
{
	if (g_Robot->Attacker->MonsterList.size() > 0)
	{
		for each(Entity* e in g_Robot->Attacker->MonsterList)
		{
			if (Life::GetEntityHP(e) > 0 && Targetable::IsTargetable(e))
			{
				Vector2 pV = g_Robot->GetLocalPlayer()->GetVector2();
				Vector2 eV = e->GetVector2();

				if (Distances::IsPointInCircle(pV.X, pV.Y, eV.X, eV.Y, 150))
				{
					lua_pushinteger(L, e->GetUniqueID());
					break;
				}
			}
		}
	}

	return 1;
}
//
//static int Scripting::HarvestSpawn(lua_State* L)
//{
//	g_Robot->SpawnHarvestInstances();
//	return 1;
//}

static int Scripting::ClearEntityFromList(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	for each (Entity* e in g_Robot->EntityList)
	{
		if (wcscmp(wc, e->FilePath) == 0)
		{
			g_Robot->EntityList.remove(e);
		}
	}

	return 0;
}

static int Scripting::SendWindowInput(lua_State* L)
{
	const char* cText = lua_tostring(L, 1);

	INPUT *keystroke;
	UINT i, character_count, keystrokes_to_send, keystrokes_sent;
	HWND notepad;

	const char *const text = cText;

	//Get the handle of the Notepad window.
	notepad = FindWindowA(NULL, ("Path of Exile"));
	if (notepad == NULL)
		return 0;


	//Bring the Notepad window to the front.
	if (!SetForegroundWindow(notepad))
		return 0;

	//Fill in the array of keystrokes to send.
	character_count = strlen(text);
	keystrokes_to_send = character_count * 2;
	keystroke = new INPUT[keystrokes_to_send];
	for (i = 0; i < character_count; ++i)
	{
		keystroke[i * 2].type = INPUT_KEYBOARD;
		keystroke[i * 2].ki.wVk = 0;
		keystroke[i * 2].ki.wScan = text[i];
		keystroke[i * 2].ki.dwFlags = KEYEVENTF_UNICODE;
		keystroke[i * 2].ki.time = 0;
		keystroke[i * 2].ki.dwExtraInfo = GetMessageExtraInfo();

		keystroke[i * 2 + 1].type = INPUT_KEYBOARD;
		keystroke[i * 2 + 1].ki.wVk = 0;
		keystroke[i * 2 + 1].ki.wScan = text[i];
		keystroke[i * 2 + 1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
		keystroke[i * 2 + 1].ki.time = 100;
		keystroke[i * 2 + 1].ki.dwExtraInfo = GetMessageExtraInfo();
	}

	//Send the keystrokes.
	keystrokes_sent = SendInput((UINT)keystrokes_to_send, keystroke, sizeof(*keystroke));
	delete[] keystroke;

	return 1;
}

static int Scripting::MouseInput(lua_State* L)
{
	int x = lua_tointeger(L, 1);
	int y = lua_tointeger(L, 2);

	POINT screenPoint;

	screenPoint.x = x;
	screenPoint.y = y;

	HWND handlePtr = WindowFromPoint(screenPoint);

	if (handlePtr) {
		int lParam = MAKELPARAM(screenPoint.x, screenPoint.y);

		PostMessage(handlePtr, WM_LBUTTONDOWN, 0, lParam);
		PostMessage(handlePtr, WM_LBUTTONUP, 0, lParam);
	}

	return 1;
}

static int Scripting::IsEntitySummoned(lua_State* L)
{
	UINT64 EntAddr = lua_tointeger(L, 1);

	Entity* e = new Entity(EntAddr);
	bool summoned = Monster::IsSummoned(e);

	lua_pushboolean(L, summoned);
	delete e;

	return 1;
}

static int Scripting::GetWaypointId(lua_State* L)
{
	lua_pushinteger(L, g_Robot->WaypointId);
	return 1;
}

static int Scripting::SetHuntingMode(lua_State* L)
{
	bool hunting = lua_toboolean(L, 1);

	g_Robot->Attacker->IsHunting = hunting;

	return 1;
}

static int Scripting::UsePortalSkill(lua_State* L)
{
	Entity* e = g_Robot->GetLocalPlayer();

	if (e != NULL)
	{
		if (g_Robot->Attacker->PortalSkill == 0)
		{
			printf("[ERROR] Portal skill was 0!\n");
			return 1;
		}

		PacketWriter* p = PacketBuilder::EntityInteraction(e->GetUniqueID(), g_Robot->Attacker->PortalSkill);
		PacketBuilder::Send(p);

		PacketWriter* p1 = PacketBuilder::EndAction();
		PacketBuilder::Send(p1);


		delete e;
	}

	return 1;
}

static int Scripting::GetClosestStrongbox(lua_State* L) //crashes now???
{
	int closestDistance = 100000;
	uint32_t closestUID = 0;
	Vector2 closestPos = { 0, 0 };

	for each(Entity* e in g_Robot->StrongboxList)
	{
		if (!Chest::IsOpened(e)) //&& Targetable::IsTargetable(e) ) //check offset for targetable
		{
			printf("Checking unopened box..\n");
			Vector2 pos = e->GetVector2();
			Vector2 pPos = g_Robot->GetLocalPlayer()->GetVector2();

			int apart = Distances::GetDistanceBetweenObjects(pos, pPos);

			if (apart < closestDistance)
			{
				if (e->GetUniqueID() > 0 && e->GetUniqueID() < 100000)
				{
					closestDistance = apart;
					closestUID = e->GetUniqueID();
					closestPos = pos;
				}
			}
		}
	}

	printf("returning closest id: %d (%d, %d)\n", closestUID, closestPos.X, closestPos.Y);
	lua_pushinteger(L, closestUID);
	return 1;
}

static int Scripting::MoveToStrongbox(lua_State* L)
{
	int closestDistance = 100000;
	uint32_t closestUID = 0;
	Vector2 closestPos = { 0, 0 };

	for each(Entity* e in g_Robot->StrongboxList)
	{
		if (!Chest::IsOpened(e))
		{
			Vector2 pos = e->GetVector2();
			Vector2 pPos = g_Robot->GetLocalPlayer()->GetVector2();

			int apart = Distances::GetDistanceBetweenObjects(pos, pPos);

			if (apart < closestDistance)
			{
				closestDistance = apart;
				closestUID = e->GetUniqueID();
				closestPos = pos;
			}
		}
	}

	Vector2 pPos = g_Robot->GetLocalPlayer()->GetVector2(); //need to get the vector aiming to the box and split it into smaller vectors
	//this will be ahuge pita to make with basic math, need some better way
	
	int moveX, moveY;

	if (pPos.X < closestPos.X)
	{
		moveX = 45;
	}
	else if (pPos.X > closestPos.X)
	{
		moveX = -45;
	}

	if (pPos.Y < closestPos.Y)
	{
		moveY = 45;
	}
	else if (pPos.Y > closestPos.Y)
	{
		moveY = -45;
	}

	pPos = g_Robot->GetLocalPlayer()->GetVector2();
}

static int Scripting::PlaceTotems(lua_State* L)
{
	if (g_Robot->Attacker->UsingTotems)
	{
			if (g_Robot->Attacker->AttackingSkill != 0)
			{
				g_Robot->Attacker->UseSingleAttack(g_Robot->GetLocalPlayer());
				Sleep(300);
			}
	}

	return 1;
}

static int Scripting::StashValuableItems(lua_State* L)
{
	printf("Stashing items...\n");

	if (g_Robot->StashItems())
	{
		printf("Finished stashing items!\n");
	}
	
	return 1;
}

static int Scripting::SellDisposableItems(lua_State* L)
{

	if (g_Robot->SellItemsToNPC())
	{
		printf("Finished selling items!\n");
	}

	return 1;
}

static int Scripting::GetRandomMapId(lua_State* L)
{
	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		if (wcsstr(i->FullName.c_str(), L"Map") != NULL)
		{
			if (FileIO::FileHasLine(L"./GoodMaps.ini", (wchar_t*)i->BaseName.c_str()))
			{
				uint32_t itemId = i->InventoryEntityId;
				lua_pushinteger(L, itemId);
				return 1;
			}
		}
	}

	printf("No desired map is in inventory, choosing a random map!\n");

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		if (wcsstr(i->FullName.c_str(), L"Map") != NULL)
		{
			uint32_t itemId = i->InventoryEntityId;
			lua_pushinteger(L, itemId);
			return 1;
		}
	}


	printf("No map is in inventory, returning 0.\n");

	//case if not found
	lua_pushinteger(L, 0);

	return 1;
}

static int Scripting::DistanceFrom(lua_State* L)
{
	uint32_t id = lua_tointeger(L, 1);

	Vector2 pPos = g_Robot->GetLocalPlayer()->GetVector2();

	for each(Entity* e in g_Robot->StrongboxList) //change back to entitylist when done testing...
	{
		if (e->GetUniqueID() == id)
		{
			Vector2 ePos = e->GetVector2();
			int Distance = Distances::GetDistanceBetweenObjects(pPos, ePos);
			lua_pushinteger(L, Distance);
			return 1;
		}
	}

	printf("DistanceFrom: Could not from ID %d.\n", id);
	lua_pushinteger(L, 0);
	return 1;
}

static int Scripting::CleanStrongboxList(lua_State* L)
{
	int EntriesRemoved = 0;

	Entity* toRemove[20] = { nullptr };

	for each(Entity* e in g_Robot->StrongboxList)
	{
		if (Chest::IsOpened(e))
		{
			toRemove[EntriesRemoved] = e;
			EntriesRemoved += 1;
		}
	}

	for (int i = 0; i < EntriesRemoved; i++)
	{
		printf("Removed box: %d\n", toRemove[i]->UniqueID);
		g_Robot->StrongboxList.remove(toRemove[i]);
		delete toRemove[i]; //check this
	}

	printf("Cleaned box list. Removed: %d\n", EntriesRemoved);

	return 1;
}

static int Scripting::RemoveStrongboxFromList(lua_State* L)
{

	return 1;
}

static int Scripting::StartMovement(lua_State* L)
{
	uint32_t x = lua_tointeger(L, 1);
	uint32_t y = lua_tointeger(L, 2);

	while (g_Robot->IsMoving)
		Sleep(200);

	g_Robot->IsMoving = true;
	PacketWriter* p = PacketBuilder::Action(Input::InputIds::RUN, 0, x, y); //dunno for directino
	PacketBuilder::Send(p);

	return 1;
}

static int Scripting::IdentifyInventoryItems(lua_State* L)
{
	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();

	uint32_t WisdomScrollID = 0;

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		if (wcscmp(i->FullName.c_str(), L"Scroll of Wisdom") == 0)
		{
			WisdomScrollID = i->InventoryEntityId;
		}
	}

	if (WisdomScrollID > 0)
	{
		for each(Item* i in g_Robot->NormalInv->Items)
		{
			PacketWriter* p = PacketBuilder::UseItemOnOtherItem(1, WisdomScrollID, 1, i->InventoryEntityId);
			PacketBuilder::Send(p);
			Sleep(500);
			wprintf(L"Identified item: %s\n", i->FullName.c_str());
		}
	}

	return 1;
}

static int Scripting::SetPlayerRotation(lua_State* L)
{
	double rot = lua_tonumber(L, 1);

	if (g_Robot->Disconnected)
		return 1;

	Entity* e = g_Robot->GetLocalPlayer();

	if (e == NULL)
		return 1;

	Positioned::SetRotation(e, rot);

	delete e;

	return 1;
}

static int Scripting::GetPlayerRotation(lua_State* L)
{
	FLOAT Rotation = Positioned::GetRotation(g_Robot->GetLocalPlayer());

	if (Rotation != 0.0f)
		lua_pushnumber(L, Rotation);
	else
		lua_pushnumber(L, 0.0f);

	printf("Player Rotation: %f\n", Rotation);

	return 1;
}

static int Scripting::WalkInDirectionFaced(lua_State* L)
{
	if (g_Robot->Attacker->IsBusy || g_Robot->Disconnected)
	{
		printf("[INFO] Disconnected or busy, can't walk forwards\n");
		return 0;
	}

	Entity* e = g_Robot->GetLocalPlayer();

	if (e == NULL)
		return 0;

	while (Actor::GetCurrentActionID(e) != 0) //avoid crashing, etc. THIS CAN GET STUCK ON PREDICTIVE MODE, for some reason action shows as not 0 but we arnt moving
		Sleep(10);

	FLOAT Rotation = Positioned::GetRotation(e);

	INT X = 40, Y = 15; //default incase a case isnt met

	if (Rotation >= 0.0f && Rotation <= 0.5235f)
	{
		X = 1;	Y = -25;
	}
	else if (Rotation >= 0.5235 && Rotation <= 0.7853)
	{
		X = 40;	Y = -30;
	}
	else if (Rotation >= 0.7853 && Rotation <= 1.0471)
	{
		X = -1;	Y = -35;
	}
	else if (Rotation >= 1.0471  && Rotation <= 1.5707)
	{
		X = 35;	Y = -18;
	}
	else if (Rotation >= 1.5707  && Rotation <= 2.0943)
	{
		X = 35;	Y = 5;
	}
	else if (Rotation >= 2.0943  && Rotation <= 2.3561)
	{
		X = 35;	Y = 20;
	}
	else if (Rotation >= 2.3561  && Rotation <= 2.6179)
	{
		X = 20;	Y = 20;	
	}
	else if (Rotation >= 2.6179  && Rotation <= 3.1415)
	{
		X = 30;	Y = 35;
	}
	else if (Rotation >= 3.1415   && Rotation <= 4.7123)
	{
		X = -1; Y = 35;
	}
	else if (Rotation >= 4.7123 && Rotation <= 6.29)
	{
		X = -35;	Y = -15;
	}
	else if (Rotation > 6.29)
	{
		X = 40; Y = 15;
	}

	g_Robot->Attacker->IsMoving = true;

	Vector2 pV = e->GetVector2();

	g_Robot->LastPosition.X = pV.X; g_Robot->LastPosition.Y = pV.Y;

	uint16_t movementSkill;

	if (g_Robot->Attacker->MovementSkill == 0)
		movementSkill = Input::InputIds::RUN; //just use normal run for now, adding a cooldown dash skill can crash
	else
		movementSkill = g_Robot->Attacker->MovementSkill;

	PacketWriter* p = PacketBuilder::Action(movementSkill, NULL, X, Y);
	PacketBuilder::Send(p);
	g_Robot->EndAction();

	Sleep(200);

	Vector2 pV_2 = e->GetVector2(); //checks whether we are stuck or not

	if (pV.X == pV_2.X && pV.Y == pV_2.Y)	
		lua_pushboolean(L, true);
	else
		lua_pushboolean(L, false);

	g_Robot->Attacker->IsMoving = false;

	delete e;
	return 1;
}

static int Scripting::GetNumberOfMonstersNearby(lua_State* L)
{
	int count = 0;

	if (g_Robot->Attacker->MonsterList.size() > 0)
	{
		for each(Entity* e in g_Robot->Attacker->MonsterList)
		{
			if (e->GetFilePathFromMemory() != NULL)
				count++;
		}
	}

	if (g_Robot->EntityList.size() > 0)
	{
		for each(Entity* e in g_Robot->EntityList)
		{
			if (e->GetFilePathFromMemory() != NULL)
			{
				if (wcsstr(e->GetFilePathFromMemory(), L"/Monster/") != NULL)
					count++;
			}

		}
	}


	lua_pushinteger(L, count);

	return 1;
}

static int Scripting::GetActorSkills(lua_State* L)
{
	if (g_Robot->Attacker->ActorSkills.size() > 0)
		g_Robot->Attacker->ActorSkills.clear();

	Entity* localPlayer = g_Robot->GetLocalPlayer();
	if (localPlayer != NULL)
	{
		g_Robot->Attacker->ActorSkills = Actor::GetSkillList(localPlayer);
	}
	else
	{
		printf("localPlayer was NULL!\n");
	}

	printf("Got %d skills\n", g_Robot->Attacker->ActorSkills.size());
	delete localPlayer;
	return 0;
}

static int Scripting::GetDeadMonsterId(lua_State* L)
{
	for each(Entity* e in g_Robot->Attacker->MonsterList)
	{
		if (Entity::IsCorpse(e))
		{
			lua_pushinteger(L, e->GetUniqueID());
			return 1;
		}
	}


	return 1;
}

static int Scripting::ShutdownAtLocalTime(lua_State* L)
{
	int _hour = lua_tointeger(L, 1);
	int _minute = lua_tointeger(L, 2);
	int _second = lua_tointeger(L, 3);

	time_t currentTime;
	struct tm *localTime;

	time(&currentTime);                   // Get the current time
	localTime = localtime(&currentTime);  // Convert the current time to the local time

	int Hour = localTime->tm_hour;
	int Min = localTime->tm_min;
	int Sec = localTime->tm_sec;

	std::cout << "The current time is : " << Hour << ":" << Min << ":" << Sec << std::endl;

	if (Hour >= _hour)
	{
		if (Min >= _minute)
		{
			if (Sec >= _second)
			{
				TerminateProcess(GetCurrentProcess(), 0);
			}
		}
	}

	return 1;
}

static int Scripting::ToggleSentinel(lua_State* L)
{
	//02 31 00 7C 00 02 00 02 
	bool out_in = lua_toboolean(L, 1); //0 = out
	byte index = lua_tointeger(L, 2);

	printf("%d, %d\n", out_in, index);

	PacketWriter* p = PacketBuilder::ToggleSentinelObject(0x7C, 2, out_in, index);
	PacketBuilder::Send(p);

	return 1;
}

static int Scripting::GetLootableItemByName(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	const size_t cSize = strlen(name) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, name, cSize);

	for each(Entity* e in g_Robot->EntityList)
	{
		if (e->GetFilePathFromMemory() != NULL)
		{
			if (e->GetComponentAddress("WorldItem") > 0)
			{
				GroundItem* item = e->GetInnerItemEntity();

				if (item != NULL)
				{
					wstring itemName = Inventory::FormItemName(item);
					UINT32 id = e->GetUniqueID();

					if (wcscmp(itemName.c_str(), wc) == 0)
					{
						wprintf(L"GetLootableItemByName found item with ID: %d (%s)\n", id, itemName);
						lua_pushinteger(L, id);
						delete item;
						return 1;
					}

					delete item;
				};
			}
		}	
	}

	lua_pushinteger(L, 0);
	return 1;
}

static int Scripting::CheckScreenHasLabel(lua_State* L)
{
	auto tLabel = lua_tostring(L, 1);

	const auto cSize = strlen(tLabel) + 1; //covert to wc
	auto wc = new wchar_t[cSize];
	mbstowcs(wc, tLabel, cSize);

	if (wcslen(wc) > 0)
	{
		for each(wstring portalLabel in g_Robot->VisiblePortals)
		{
			if (wcscmp(portalLabel.c_str(), wc) == 0)
			{
				wprintf(L"Found label on screen: %s\n", portalLabel.c_str());
				lua_pushboolean(L, true);
				return 1;
			}
		}

		if (Element::IsLabelOnScreen(std::wstring(wc)))
		{
			wprintf(L"Found label on screen: %s\n", wc);
			lua_pushboolean(L, true);
		}
		else
		{
			lua_pushboolean(L, false);
		}
	}

	return 1;
}

static int Scripting::RunScript(lua_State* L)
{
	auto scriptName = lua_tostring(L, 1);
	luaL_dofile(L, scriptName);

	return 1;
}

static int Scripting::LootItems(lua_State* L)
{
	printf("Looting items (if any exist)...\n");

	if(!g_Robot->Disconnected && !g_Robot->Attacker->IsBusy)
		g_Robot->LootItems();

	return 1;
}

static int Scripting::SetWindowTitle(lua_State* L)
{
	auto windowName = lua_tostring(L, 1);
	return 1;
}