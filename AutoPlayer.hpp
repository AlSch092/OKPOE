#pragma once
#include <queue>
#include "Hotkeys.hpp"
#include "NetLogger.hpp"
#include "AutoTrader.hpp"
#include "ObjectMagicProperties.hpp"
#include "Life.hpp"
#include "Positioned.hpp"
#include "Targetable.hpp"
#include "MinimapIcon.hpp"
#include "Chest.hpp"
#include "WorldItem.hpp"
#include "Stack.hpp"
#include "Sockets.hpp"
#include "Mods.hpp"
#include "SkillGems.hpp"
#include "Declarations.hpp"
#include "Aim.hpp"
#include "FileIO.hpp"
#include "Actor.hpp"
#include "Player.hpp"
#include "Base.hpp"
#include "AutoAttacker.hpp"
#include "Inventory.hpp"
#include "AutoFlask.hpp"
#include "TaskHelper.hpp" 
#include "GroundItem.hpp"

using namespace std;

class TaskHelper;

namespace Input
{
	struct Inputs
	{
		Vector2 Position;
		UINT16 InputID;
		DWORD InteractionEntityID;
		int Delay;
	};

	enum InputIds
	{
		NONE = 0,
		FLARE = 0x8C00,
		DYNAMITE = 0x8F00,
		INTERACTION = 0x0266,
		RUN = 0x2909,
	};

	enum Status
	{
		IDLE = 0,
		DISCONNECTED,
		SCRIPT_RUNNING,
		PLAYER_DEAD,
		PLAYER_LOOTING,
		PLAYER_ATTACKING
	};
}

struct Trade; //compiler wants these declares before autoplayer
class NormalInventory; //forward decl
class CurrencyInventory;
class StashInventory;
class TradeInventory;
class AutoSeller;
class AutoFlask;
class Mapper;
struct Item;

class AutoPlayer
{
	public:

	AutoPlayer();

	//Entity instance, need to update this every map load, thus need to hook area change...
	Entity* LocalPlayer = NULL;
	Entity* GetLocalPlayer();

	std::string AccountName;

	struct lua_State* LUAController;
	bool LoopingScript;
	char* ScriptBuffer;

	std::queue<Input::Inputs*>* InputQueue = new std::queue<Input::Inputs*>;

	TaskHelper* GameHelper;

	Trade* AutoTrade = NULL;
	AutoSeller* Seller = NULL;
	AutoAttacker* Attacker = NULL;
	AutoFlask* Flasker = NULL;

	//Handles
	HANDLE ScriptingThread = NULL;
	HANDLE AutoChickenThread = NULL;
	HANDLE AutoFlaskThread = NULL;
	HANDLE InputThread = NULL;
	HANDLE haReduceRAM = NULL;
	HANDLE FollowPlayerThread = NULL;
	HANDLE MonsterHuntingThread = NULL;
	HANDLE HealthMonitorThread = NULL;
	HANDLE ElementLoggerThread = NULL;
	HANDLE AutoTradeThread = NULL;
	HANDLE LootingThread = NULL;
	HANDLE ClickablesOpenThread = NULL;

	int actionCounter = 0;

	//booleans
	bool isReducingRAM = false;
	bool isReducingCPU = false;
	bool AutoLooting = false;
	bool isLoggingOutbound = false;

	bool LoggingComponents = false;
	bool WritingToFile = false;
	bool isRandomizingScriptName = false;

	bool AutoFlasking = false;

	bool ReviveInSameMap = true;

	bool IsFollowingActor = false;
	bool isAutoOpeningChests = false;
	bool ChangingArea = false;

	bool PrintingValuableEntities = false;

	bool UsingBuiltInItemList = false;
	bool HotkeysEnabled = false;

	bool AutoReviving = true;
	bool ReviveSameMap = false;

	bool UsingDynamiteHack = false;

	bool EntityMsgsSupressed = true; //watch this
	//bool IsBusy = false;
	bool IsMoving = false;
	bool IsLooting = false;
	bool AutoTrading = false;
	bool DebugMode = false;

	bool BlightBotting = false;

	UINT32 FlaskOnHitpoints;
	UINT32 FlaskOnMana;
	bool UsingFlasks345OnMP = false;
	bool UsingFlasksAt50Percent = false;

	void BeginFlasking();
	void StopFlaskUsage();
	static void ChickenOnHitpoints();
	int ExitGameOnHP;

	typedef void(*ActionFunction)(UINT64, UINT16, DWORD, Vector2*);
	void Action(UINT16 SkillId, DWORD SelectedEntityID, Vector2* AtPosition);
	void EndAction();
	void Interaction(uint32_t entityId, uint16_t actionId);
	bool InteractIfInRange(Entity* e, int distanceMax);

	list<Entity*> EntityList;
	list<Entity*> MonsterList;
	list<GroundItem*> GroundItemList;
	list<Entity*> PlayerList;
	list<Item*> FlaskList;

	list<wstring> VisiblePortals;

	list<Entity*> StrongboxList;

	bool IsMonsterIgnored(Entity* e);

	static void FollowPlayer();
	void BeginAutoFollow();

	static void HandleEntitySpawn(UINT64 EntAddr);
	static void HandleEntityLabelSpawn(UINT64 pObject, LPCWSTR swLabel);
	static void HandleMonsterSpawn(Entity* e);
	static void HandleItemDrop(Entity* e);
	static void HandlePlayerControlled(Entity* e);
	static void HandleOnAreaChange();
	static void HandleAreaTransition(Entity* e);
	static void HandleStrongbox(Entity* e);

	UINT32 FollowingUID = 0;
	wchar_t FollowingPlayerName[50]; //todo: replace with wstring
	UINT16 FollowPlayerSkill = 0;
	Entity* FollowingPlayer;

	list<Entity*> BlightFoundationList;
	list<uint32_t> BlightFoundationIdList;
	bool isAutoConstructing = false;
	int ConstructingTowerTier = 1;

	list<wchar_t*> DoorsAndSwitches;
	list<wchar_t*> IgnoredEntities;
	bool isAutoEnteringAreaTransition = false;

	void PrintNotableEntities(Entity* e);

	bool IsCharacterStuck();
	static void Revive();
	bool IsEntityInList(wstring wc);

	//inventories
	StashInventory* GetStashInventories(int Pages);
	CurrencyInventory* GetCurrencyTab(int Page);

	NormalInventory* NormalInv;
	CurrencyInventory* CurrencyInv;
	StashInventory* StashInv[TABS_LOGGED];
	TradeInventory* TradeWindowLocal;
	TradeInventory* TradeWindowRemote;

	int AttackDelay;

	std::string ReadableAreaName;
	std::string NumberedAreaName;

	bool LootItems();
	static void AutolootItems();
	static void AutoOpenChests();

	bool LoggingHarvestExtractors = false;

	uint32_t WaypointId = 0;
	bool InTown = false;
	bool Disconnected = false;

	Mapper* mapHelper;

	std::list <wstring> itemsToStash;
	std::list <wstring> itemsToSell;

	bool StashItems();
	bool SellItemsToNPC();
	
	uint32_t NPCID_Sales = 0;
	uint32_t StashID = 0;

	void ExitNPCDialog();

	bool isRecordingMovement = false;
	static void PlayBackMovements();

	bool SpawnMap(uint16_t modifier, byte hero, byte endOption);
	static void RevealMap();

	Vector2 LastPosition;
	Vector2 SavedPosition; //for when the character dies or needs to use merchant then return to same place
	uint32_t SavedMapHash;
};


