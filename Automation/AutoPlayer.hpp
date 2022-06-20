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
#include "Mapper.hpp"

//this is not a full copy of AutoPlayer.hpp -> certain sections have been omitted for privacy's sake

using namespace std;

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
struct Item;

class AutoPlayer
{
	public:
  
  struct lua_State* LUAController; //lua script object
  static Entity* GetLocalPlayer();
  
	bool IsLoopingScript = false;
  bool IsRandomizingScriptName = false;
	char* ScriptBuffer;
  
  std::queue<Input::Inputs*>* InputQueue = new std::queue<Input::Inputs*>; //old method of moving + actions, not longer needed
  
  AutoSeller* Seller = NULL; //Trade bot
  AutoAttacker* Attacker = NULL; //attacker bot
	AutoFlask* Flasker = NULL; //flasking bot
  
  //Handles
	HANDLE ScriptingThread = NULL;
  HANDLE AutoFlaskThread = NULL;
  HANDLE InputThread = NULL;
  HANDLE FollowPlayerThread = NULL;
  
  bool AutoLooting = false;
  
  bool AutoFlasking = false;
  bool AutoReviving = false;
	bool ReviveInSameMap = false;
  bool IsFollowingActor = false;
  bool isAutoOpeningChests = false;
  bool IsAutoChangingAreas = false;
  
  void Action(UINT16 SkillId, DWORD SelectedEntityID, Vector2* AtPosition);
	void EndAction();
	void Interaction(uint32_t entityId, uint16_t actionId);
  
  list<Entity*> GroundItemList;
	list<Entity*> EntityList;
	list<Entity*> PlayerList;
  
  list<Item*> FlaskList;
  
 	static void HandleInputQueue(); //thread func
	void BeginHandlingInput();

	static void FollowPlayer();
	void BeginAutoFollow();
  
  static void HandleEntitySpawn(UINT64 EntAddr);
  static void HandleOnAreaChange();
  
  Entity* FollowingPlayer;
  
  bool IsCharacterStuck();
  
  std::string ReadableAreaName;
	std::string NumberedAreaName;
  
  static void AutolootItems();
  static void AutoOpenChests();
  
  uint32_t WaypointId = 0;
	bool InTown = false;
	bool Disconnected = false;
  
  list <wstring> itemsToStash;
	list <wstring> itemsToSell;
  
  bool StashItems();
	bool SellItemsToNPC();
}
