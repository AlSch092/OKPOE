#include "Scripter.hpp"

extern AutoPlayer* Robot;
extern NetLogger* prot;
extern HMODULE DLLModule;

void Scripting::initializeLUA()
{
	Robot->LUAController = luaL_newstate();
	luaL_openlibs(Robot->LUAController);

	lua_register(Robot->LUAController, "GetLocalPlayer", Scripting::GetLocalPlayer);
	lua_register(Robot->LUAController, "PlayerLevel", Scripting::GetPlayerLvl);
	lua_register(Robot->LUAController, "PlayerExp", Scripting::GetPlayerExp);
	lua_register(Robot->LUAController, "PlayerName", Scripting::GetLocalPlayerName);
	lua_register(Robot->LUAController, "EntityName", Scripting::GetEntityPlayerName);
	lua_register(Robot->LUAController, "GetComponentAddress", Scripting::GetEntityComponentAddress);
	lua_register(Robot->LUAController, "GetEntityId", Scripting::GetEntityId);
	lua_register(Robot->LUAController, "GetEntityIdByPath", Scripting::GetEntityIdByName);
	lua_register(Robot->LUAController, "GetEntityByPath", Scripting::GetEntityByName);
	lua_register(Robot->LUAController, "IsEntityInList", Scripting::IsEntityInList);

	lua_register(Robot->LUAController, "Message", Scripting::PlayerMessage);

	//etc/util
	lua_register(Robot->LUAController, "MessageBox", Scripting::MessagePrompt);
	lua_register(Robot->LUAController, "Log", Scripting::LogToConsole);
	lua_register(Robot->LUAController, "Wait", Scripting::Wait);
	
	lua_register(Robot->LUAController,  "RevealMap", Scripting::RevealMap); //toggle hacks
	lua_register(Robot->LUAController,  "SetCameraZoom", Scripting::SetCameraZoom);
	lua_register(Robot->LUAController, "ReduceCPU", Scripting::ToggleReduceCPU);
	lua_register(Robot->LUAController, "ReduceRAM", Scripting::ToggleReduceRAM);

	//Network
	lua_register(Robot->LUAController,  "SendPacket", Scripting::OutPacket);
	lua_register(Robot->LUAController, "SpamPacket", Scripting::SpamPacket);
	lua_register(Robot->LUAController,  "ChangeHideout", Scripting::ChangeHideout);

	//Alive/gameplay related
	lua_register(Robot->LUAController,  "UseFlask", Scripting::UseFlask);
	lua_register(Robot->LUAController, "PlayerAlive", Scripting::IsPlayerAlive);
	lua_register(Robot->LUAController,  "Revive", Scripting::RevivePlayer);



	lua_register(Robot->LUAController,  "Action", Scripting::SendCharacterAction); //same as moveto with diff parameters, meant for skill casting
	lua_register(Robot->LUAController,  "Move", Scripting::MoveToPosition);
	lua_register(Robot->LUAController, "EndAction", Scripting::EndAction);
	lua_register(Robot->LUAController,  "Loot", Scripting::EntityInteraction);
	lua_register(Robot->LUAController,  "EntityInteraction", Scripting::EntityInteraction);
	lua_register(Robot->LUAController, "GetActionCount", Scripting::ActionCount);
	lua_register(Robot->LUAController, "GetActionId", Scripting::ActionId);
	lua_register(Robot->LUAController, "GetEntityPosition", Scripting::GetEntityPosition);
	lua_register(Robot->LUAController, "FollowPlayer", Scripting::FollowPlayer);
	lua_register(Robot->LUAController, "EnterAreaTransitions", Scripting::EnterAreaTransitions);
	lua_register(Robot->LUAController, "UseWaypoint", Scripting::UseWaypoint);
	lua_register(Robot->LUAController, "SelectInstance", Scripting::SelectInstance);
	lua_register(Robot->LUAController, "SpawnMapInstance", Scripting::SpawnAtlasPortals);

	//Targetable::
	lua_register(Robot->LUAController, "Targetable", Scripting::IsEntityTargetable);
	lua_register(Robot->LUAController, "Hovered", Scripting::IsEntityHovered); //with mouse coords

	//Chest::Component
	lua_register(Robot->LUAController, "Opened", Scripting::IsOpened);
	lua_register(Robot->LUAController, "Quality", Scripting::ChestQuality);
	lua_register(Robot->LUAController, "Locked", Scripting::IsLocked);
	lua_register(Robot->LUAController, "isStrongbox", Scripting::IsChestStrongbox);

	//Life::Component
	lua_register(Robot->LUAController,  "PlayerHP", Scripting::GetCurrentHP);
	lua_register(Robot->LUAController,  "PlayerMP", Scripting::GetCurrentMP);
	lua_register(Robot->LUAController,  "PlayerES", Scripting::GetCurrentES);
	lua_register(Robot->LUAController,  "PlayerMaxHP", Scripting::GetMaxHP);
	lua_register(Robot->LUAController,  "PlayerMaxMana", Scripting::GetMaxMana);
	lua_register(Robot->LUAController,  "PlayerMaxES", Scripting::GetMaxES);

	//league shit
	lua_register(Robot->LUAController,  "VisitDelveNode", Scripting::VisitDelveNode);
	lua_register(Robot->LUAController, "StartDelvePathing", Scripting::StartDelveNode);
	lua_register(Robot->LUAController, "BlightTower", Scripting::VisitDelveNode);


	lua_register(Robot->LUAController, "GetItemSockets", Scripting::GetItemSockets);
	lua_register(Robot->LUAController, "IsItemFullyLinked", Scripting::IsItemFullyLinked);

	lua_register(Robot->LUAController, "KillNearestMonster", Scripting::KillNearestMonster);
	lua_register(Robot->LUAController, "LootNearby", Scripting::LootGroundItems);

	lua_register(Robot->LUAController, "ExitNPCDialog", Scripting::ExitNPCDialog);
	lua_register(Robot->LUAController, "SelectNPCDialog", Scripting::SelectNPCDialog);

	lua_register(Robot->LUAController, "AcceptTrade", Scripting::AcceptTrade);
	lua_register(Robot->LUAController, "PlaceItemInTrade", Scripting::PlaceItemInTrade); //possibly duplicte of inventorytowindow
	lua_register(Robot->LUAController, "CancelTrade", Scripting::CancelTrade);

	lua_register(Robot->LUAController, "BlightTower", Scripting::BlightTower);
	lua_register(Robot->LUAController, "PlaceExplosives", Scripting::PlaceExplosive);

	lua_register(Robot->LUAController, "DiscardEntity", Scripting::DiscardEntity);

	lua_register(Robot->LUAController, "WindowItemToInventory", Scripting::WindowToInventory_Item);
	lua_register(Robot->LUAController, "InventoryItemToWindow", Scripting::InventoryToWindow_Item);

	lua_register(Robot->LUAController, "GetElements", Scripting::ReadAllElements);
	lua_register(Robot->LUAController, "ReadInventoryItems", Scripting::ReadInventoryItems);

	lua_register(Robot->LUAController, "UnloadOKPOE", Scripting::UnloadDLL);
}

void Scripting::ExecuteLUA()
{
	if (strncmp(Robot->ScriptBuffer, "Scripting Work Area", 25) == 0) //user was CLEARLY not ready.
		return;

	initializeLUA();

	std::ofstream tempFile;
	std::string fileName;

	if (Robot->isRandomizingScriptName)
	{
		fileName = randomStr(8) + ".LUA";
	}
	else
	{
		fileName = "untitled.LUA";
	}

	tempFile.open(fileName.c_str());

	tempFile.write(Robot->ScriptBuffer, strlen(Robot->ScriptBuffer));
	tempFile.close();

	if (Robot->ScriptBuffer == NULL || strcmp(Robot->ScriptBuffer, "") == 0)
	{
		return;
	}

	luaL_dofile(Robot->LUAController, fileName.c_str()); //execute LUA script
}

void Scripting::StopLUA(lua_State* lua_state)
{
	lua_close(Robot->LUAController);
	TerminateThread(Robot->ScriptingThread, 0);
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
	
	SendPacket(SendClass, hexbytes, length);
	
	delete[] hexbytes;
	return 0;
}

static int Scripting::SendCharacterAction(lua_State* LUAState)
{
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

		Robot->EndAction();
	}

	return 0;
}

static int Scripting::EntityInteraction(lua_State* LUAState)
{
	UINT32 EntityID = lua_tointeger(LUAState, 1);

	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		PacketWriter* p = PacketBuilder::EntityInteraction(EntityID, 0x266);
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());

		delete[] p->GetBuffer();
		delete p;

		Robot->EndAction();
	}

	return 0;
}

static int Scripting::MoveToPosition(lua_State* LUAState)
{
	const UINT32 X = lua_tointeger(LUAState, 1);
	const UINT32 Y = lua_tointeger(LUAState, 2);
	
	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		PacketWriter* p = PacketBuilder::Action(Input::InputIds::RUN, NULL, X, Y);
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());

		delete[] p->GetBuffer();
		delete p;

		Robot->EndAction();
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
	Entity* LocalEntity = AutoPlayer::GetLocalPlayer();
	INT currHP = Life::GetEntityHP(LocalEntity);
	lua_pushinteger(LUAState, currHP);

	return 1;
}

static int Scripting::GetMaxHP(lua_State* LUAState)
{
	Entity* LocalEntity = AutoPlayer::GetLocalPlayer();
	INT maxHP = Life::GetEntityMaxHP(LocalEntity);

	lua_pushinteger(LUAState, maxHP);
	return 1;
}

static int Scripting::GetCurrentMP(lua_State* LUAState)
{
	Entity* LocalEntity = AutoPlayer::GetLocalPlayer();
	INT currMP = Life::GetEntityMana(LocalEntity);

	lua_pushinteger(LUAState, currMP);
	return 1;
}

static int Scripting::GetMaxMana(lua_State* LUAState)
{
	Entity* LocalEntity = AutoPlayer::GetLocalPlayer();
	INT maxMana = Life::GetEntityMaxMana(LocalEntity);

	lua_pushinteger(LUAState, maxMana);
	return 1;
}

static int Scripting::GetCurrentES(lua_State* LUAState)
{
	Entity* LocalEntity = AutoPlayer::GetLocalPlayer();
	INT Shield = Life::GetEntityES(LocalEntity);

	lua_pushinteger(LUAState, Shield);
	return 1;
}


static int Scripting::GetMaxES(lua_State* LUAState)
{
	Entity* LocalEntity = AutoPlayer::GetLocalPlayer();
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

static int Scripting::ChangeHideout(lua_State* LUAState)
{
	const byte Hideout = lua_tointeger(LUAState, 1);
	UINT64 SendClass = GetSendClass();
	PacketWriter* p = PacketBuilder::SwapHideout((Hideouts)Hideout);
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
	Entity* ent = Robot->GetLocalPlayer();
	//push address, or ptr to lua stack..?
	lua_pushinteger(LUAState, ent->Address);
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

static int Scripting::ActionId(lua_State* LUAState)
{
	const UINT64 EntAddr = lua_tointeger(LUAState, 1);
	Entity* e = new Entity(EntAddr);
	Actor::ActionIDs action = Actor::GetCurrentActionID(e);
	lua_pushinteger(LUAState, action);
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
	Entity* LocalEntity = AutoPlayer::GetLocalPlayer();
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

	UINT64 PointerBase = (g_POEBase + prot->Offsets[3]); // -> Addr1
	UINT64 PointerTwo = *(UINT64*)PointerBase + 0x688;// Addr1 + 0x688 = Addr2
	UINT64 PointerThree = *(UINT64*)PointerTwo + 0x58; // Addr2 + 58 -> fin
	*(UINT16*)PointerThree = 1;

	return 0;
}

static int Scripting::SetCameraZoom(lua_State* LUAState)
{
	double fZoom = lua_tonumber(LUAState, 1);

	UINT64 g_POEBase = (UINT64)GetModuleHandleA(NULL);

	UINT64 PointerBase = (g_POEBase + prot->Offsets[3]); // -> ingamestate

	WritePointer<float>(PointerBase, Offsets::ZoomOffset, fZoom);

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
		SetHook((g_POEBase + Offsets::CPUReducer), CPUReduceHook);
	}
	else if (isReducing == false)
	{
		RemoveHook(g_POEBase + Offsets::CPUReducer, 10, (BYTE*)"\x49\x83\xC0\x04\x89\x41\x20\x49\x8B\xD2");
	}

	return 0;
}

static int Scripting::ToggleReduceRAM(lua_State* LUAState)
{
	bool isReducing = lua_toboolean(LUAState, 1);

	if (isReducing)
	{
		if (Robot->haReduceRAM == NULL)
			Robot->haReduceRAM = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ReduceRAM, 0, 0, 0);
	}
	else
	{
		TerminateThread(Robot->haReduceRAM, 0);
		Robot->haReduceRAM = NULL;
	}

	return 0;
}

static int Scripting::SetAutoExitHP(lua_State* LUAState) //SET ROBOT VAR
{
	int exitOnHP = lua_tointeger(LUAState, 1);
	Robot->ExitGameOnHP = exitOnHP;

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
	Entity e = Entity();
	e.Initialize(EntAddr);

	bool b = Chest::IsOpened(&e);

	lua_pushboolean(LUAState, b);

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

	return 0;
}


static int Scripting::GetPlayerLvl(lua_State* LUAState)
{
	Entity* LocalEntity = AutoPlayer::GetLocalPlayer();
	byte Lvl = Player::GetPlayerLevel(LocalEntity);
	
	lua_pushinteger(LUAState, Lvl);

	return 1;
}

static int Scripting::GetPlayerExp(lua_State* LUAState)
{
	Entity* LocalEntity = AutoPlayer::GetLocalPlayer();
	long exp = Player::GetPlayerExperience(LocalEntity);

	lua_pushinteger(LUAState, exp);

	return 1;
}

static int Scripting::GetLocalPlayerName(lua_State* LUAState)
{
	Entity* LocalEntity = AutoPlayer::GetLocalPlayer();

	std::wstring name = Player::GetPlayerName(LocalEntity);

	char utfName[50];
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &name[0], (int)name.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &name[0], (int)name.size(), &utfName[0], size_needed, NULL, NULL);

	lua_pushstring(LUAState, utfName);

	return 1;
}

static int Scripting::GetEntityPlayerName(lua_State* LUAState)
{
	const UINT64 EntAddr = lua_tointeger(LUAState, 1);
	Entity e;
	e.Initialize(EntAddr);

	std::wstring name = Player::GetPlayerName(&e);

	char utfName[50];
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &name[0], (int)name.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &name[0], (int)name.size(), &utfName[0], size_needed, NULL, NULL);

	lua_pushstring(LUAState, utfName);

	return 1;
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
		wcscpy(Robot->FollowingPlayerName, wName);
		Robot->IsFollowingActor = true;
		Robot->FollowPlayerSkill = Input::InputIds::RUN;
		wprintf(L"[AUTO-FOLLOW] Following: %s\n", Robot->FollowingPlayerName);
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

	Robot->isAutoEnteringAreaTransition = isEntering;

	return 0;
}

static int Scripting::GetItemSockets(lua_State* LUAState)
{
	UINT64 EntAddr = lua_tointeger(LUAState, 1);

	Entity* Item = new Entity(EntAddr);
	Entity* subItem = Item->GetSubObjectEntity();

	int Sockets = Sockets::GetNumberOfSockets(subItem);

	lua_pushinteger(LUAState, Sockets);

	return 1;
}

static int Scripting::IsItemFullyLinked(lua_State* LUAState)
{
	UINT64 EntAddr = lua_tointeger(LUAState, 1);

	Entity* Item = new Entity(EntAddr);
	Entity* subItem = Item->GetSubObjectEntity();

	bool Linked = Sockets::isItemFullyLinked(subItem);

	lua_pushboolean(LUAState, Linked);

	return 1;
}

static int Scripting::KillNearestMonster(lua_State* L)
{
	Vector2 v = Robot->GetLocalPlayer()->GetVector2();
	Vector2 TargetVector;
	Entity* entPtr;
	int distance = 0;
	int tempDistance = 0;

	for (auto& e : Robot->MonsterList)
	{
		Vector2 MobVector = e->GetVector2();
		distance = Distances::GetDistanceBetweenObjects(v.X, v.Y, MobVector.X, MobVector.Y);
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
		PacketWriter* p = PacketBuilder::Action(Robot->MainAttackingSkill, NULL, TargetVector.X, TargetVector.Y);
		UINT64 SendClass = GetSendClass();
		if (SendClass != NULL)
		{
			SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
			Robot->EndAction();
		}

		Sleep(100);
	}

	return 0;
}

static int Scripting::UnloadDLL(lua_State* L)
{
	FreeLibraryAndExitThread(DLLModule, 0);

	return 0;
}

static int Scripting::LootGroundItems(lua_State* L)
{
	Vector2 v = Robot->GetLocalPlayer()->GetVector2();

	for (auto& e : Robot->GroundItemList)
	{
		if (Distances::IsPointInCircle(v.X, v.Y, e->GetVector2().X, e->GetVector2().Y))
		{
			while (Targetable::IsTargetable(e))
			{
				PacketWriter* p = PacketBuilder::EntityInteraction(e->GetUniqueID(), 0x0266);
				UINT64 SendClass = GetSendClass();
				if (SendClass != NULL)
				{
					SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
					Robot->EndAction();
					Sleep(3000);
				}
			}

			Robot->GroundItemList.remove(e); //we assume item is looted as its no longer targetable
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

static int Scripting::AcceptTrade(lua_State* L)
{
	PacketWriter* p = PacketBuilder::AcceptTrade(2);
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
	const char* Name = lua_tostring(L, 1); // get function argument
	const char* Msg = lua_tostring(L, 2); // get function argument

	//todo make packet func to write string


	return 0;
}

static int Scripting::GetEntityComponentAddress(lua_State* L)
{
	UINT64 EntAddr = lua_tointeger(L, 1);
	EntAddr = EntAddr - sizeof(UINT64);

	const char* ComponentName = lua_tostring(L, 2); // get function argument
	UINT64 ComponentAddr = 0;

	Entity* e = new Entity(EntAddr);
	e->FillComponentList();

	ComponentAddr = e->GetComponentAddress((char*)ComponentName);

	FileIO::Log("Got entity component addr: %llX\n", ComponentAddr);

	if (ComponentAddr != NULL)
		lua_pushinteger(L, ComponentAddr);
	else
		lua_pushinteger(L, NULL);

	delete e;

	return 1;
}

static int Scripting::IsEntityInList(lua_State* L)
{
	bool inList = false;
	const char* filePath = lua_tostring(L, 1); // get function argument

	const size_t cSize = strlen(filePath) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, filePath, cSize);

	for each(auto& e in Robot->EntityList)
	{
		if (wcscmp(e->FilePath.c_str(), wc) == 0)
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

	for each(auto& e in Robot->EntityList)
	{
		if (wcscmp(e->FilePath.c_str(), wc) == 0)
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

static int Scripting::GetEntityIdByName(lua_State* L)
{
	bool inList = false;
	uint32_t id = 0;
	const char* filePath = lua_tostring(L, 1); // get function argument

	const size_t cSize = strlen(filePath) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, filePath, cSize);

	for each(auto& e in Robot->EntityList)
	{
		if (wcscmp(e->FilePath.c_str(), wc) == 0)
		{
			inList = true;
			id = e->GetUniqueID();
			lua_pushinteger(L, id);
			FileIO::Log("Returning id %d.\n", id);
			return 1;
		}
	}

	FileIO::Log("[DEBUG] Entity name not found in list. Could not get ID.\n");

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

	for each(auto& e in Robot->EntityList)
	{
		if (addr == e->Address-8)
		{
			Robot->EntityList.remove(e);
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

static int Scripting::IsCharacterStuck(lua_State* L)
{



	return 1;
}

static int Scripting::SpawnAtlasPortals(lua_State* L)
{
	//SpawnAtlasInstance(UINT16 ItemIndex, byte listSelection, byte callingMaven, byte masterSelection);
	short itemIndex = lua_tointeger(L, 1);
	byte listSelection = lua_tointeger(L, 2);
	byte callingMaven = lua_tointeger(L, 3);
	byte callingMaster = lua_tointeger(L, 4);

	PacketWriter* p = PacketBuilder::SpawnAtlasInstance(itemIndex, listSelection, callingMaven, callingMaster);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	return 0;
}

static int Scripting::InventoryToWindow_Item(lua_State* L)
{
	uint32_t index = lua_tointeger(L, 1);

	PacketWriter* p = PacketBuilder::InventoryToWindow(index);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}


	return 0;
}

static int Scripting::WindowToInventory_Item(lua_State* L)
{
	uint32_t index = lua_tointeger(L, 1);

	PacketWriter* p = PacketBuilder::WindowToInventory(index);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
	{
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	}

	return 0;
}

static int Scripting::ReadInventoryItems(lua_State* L)
{

	return 0;
}

static int Scripting::ReadAllElements(lua_State* L)
{
	Element::GetAllElements();
	return 0;
}
