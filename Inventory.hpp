#pragma once
#include "Element.hpp"
#include "AutoPlayer.hpp"
#include "ElementBase.hpp"

class ElementItem : public ElementBase
{
public:
	Entity* ItemEnt;

	int CellX;
	int CellY;

	int Height;
	int Width;

	int StashPage;

	UINT64 MemoryAddress;
	UINT32 InventoryEntityId;

	int stackSize;

	wstring UniqueName;
	wstring BaseName;
	wstring FullName; //Unique name + Base Name
	wstring PriceTag;
};

struct Item // actually is an element . . . todo: change to class as above
{
	Entity* ItemEnt;

	int CellX;
	int CellY;

	int Height;
	int Width;

	int StashPage;

	UINT64 MemoryAddress;
	UINT32 InventoryEntityId;

	int stackSize;

	wstring UniqueName;
	wstring BaseName;
	wstring FullName; //Unique name + Base Name
	wstring PriceTag;

};

namespace Inventory //inherited class from elemnt..
{
	enum TradeWindowSide
	{
		Remote = 0,
		Local
	};

	enum InventoryTabPermissions : byte
	{
		None = 0,
		View = 1,
		Add = 2,
		Remove = 4
	};

	enum InventoryTabFlags : byte
	{
		RemoveOnly = 1,
		Unknown2 = 2,
		Premium = 4,
		Unknown3 = 8,
		Unknown1 = 0x10,
		Public = 0x20,
		MapSeries = 0x40,
		Hidden = 0x80
	};

	enum InventoryTabAffinityFlags : short
	{
		Currency = 0x0008,
		Unique = 0x0010,
		Map = 0x0020,
		Divination = 0x0040,
		Essence = 0x0100,
		Fragment = 0x0200,
		Delve = 0x1000,
		Blight = 0x2000,
		Meta = 0x3000,
		Delirium = 0x4000
	};

	enum Inventories
	{
		Normal = 1,
		AlvaReverseIncursion = 0x4C,
	};

	static const UINT64 EntityOffset = 0x370; //wrong
	static const UINT64 EntityIdOffset = 0x508;
	static const UINT64 CellXOffset = 0x440;
	static const UINT64 CellYOffset = CellXOffset + 4;
	static const UINT64 CellWidthOffset = 0x3D4;
	static const UINT64 CellHeightOffset = CellWidthOffset + 4;
	static const UINT64 IsHoveredOffset = 0x46E; //C6 87 6E 04 00 00 01 48 85 DB 74 46 80 BB 90 03 00 00 00 74 3D 8B 8B 60
	static const UINT64 AffinityFlagsOffset = 0x4D0; //needs updating

	static const UINT64 TradeWindowOffset_OurItems = 0x458;//1st offset
	static const UINT64 TradeWindowOffset_TheirItems = 0x460;

	static const UINT64 TradeWindowOffset_OurItems2 = 0x6B8; //1st offset ... does this mean the new windows popping up become the first tabs of stash??
	static const UINT64 TradeWindowOffset_TheirItems2 = 0x6C0; //needs updatings

	//this ptr will have most if not all important windows
	static const UINT64 CurrencyTabOffset = 0x4D0; //redo this for hopefully a smaller solution
	static const UINT64 StashTab1Offset = 0x658; //+8 for each tab..
	static const UINT64 StashTab2Offset = StashTab1Offset + 8;
	static const UINT64 StashTab3Offset = StashTab2Offset + 8;
	static const UINT64 StashTab4Offset = StashTab3Offset + 8;

	static const UINT64 NPCTradeWindowOffset_OurItems = 0x6C0;
	static const UINT64 NPCTradeWindowOffset_TheirItems = TradeWindowOffset_OurItems - 8;

	namespace Equipment
	{
		static const UINT64 Offset_Helmet = 0x1E8;
		static const UINT64 Offset_Amulet = Offset_Helmet + 8;
		static const UINT64 Offset_Lefthand = 0x208;
		static const UINT64 Offset_Righthand = Offset_Lefthand + 8;
		static const UINT64 Offset_BodyArmour = 0x220;
		static const UINT64 Offset_LeftRing = Offset_BodyArmour + 8;
		static const UINT64 Offset_RightRing = Offset_LeftRing + 8;
		static const UINT64 Offset_Gloves = Offset_RightRing + 8;
		static const UINT64 Offset_Belt = Offset_Gloves + 8;
		static const UINT64 Offset_Boots = Offset_Belt + 8;
	}

	static const UINT64 FlaskInvOffset = 0x248;
	static const UINT64 NormalInvOffset = FlaskInvOffset + 8; //TODO: GET AOB...

	std::list<Item*> GetFlasks(bool isCached);

	std::wstring FormInventoryItemName(Item* itm); //we need to refactor this code and make it templated for both grounditems and inventory
	std::wstring FormItemName(GroundItem* e);
}

class InventoryBase : public ElementBase
{
public:

	InventoryBase() { };

	std::list<Item*> Items;

	bool ContainsItem(wstring itemName)
	{
		for each(Item* i in this->Items)
		{
			if (i->FullName == itemName)
				return true;
		}

		return false;
	}
};

class NormalInventory : virtual public InventoryBase
{
public:

	std::list<Item*> GetInventoryItems();
	std::list<Item*> GetInventoryItems(UINT64 start_offset);

	Item* GetInventoryItem(UINT64 StructAddr);

	virtual bool DoesItemFitInSlots(Item* itm, int CellX, int CellY) { return false; }

	friend NormalInventory operator+= (NormalInventory lhs, Item* rhs) 
 	{
		lhs.Items.push_back(rhs);
	}


	bool isInventoryFull();

	virtual ~NormalInventory() {};
};

class StashInventory : virtual public NormalInventory
{
public:
	void SetTabPermissions(byte p);
	void SetTabFlags(byte f);
	void SetTabAffinityFlags(UINT16 af);

	UINT16 GetAffinityFlags(UINT64 ElementAddr) { UINT16 af = DereferenceSafe<UINT16>(ElementAddr + Inventory::AffinityFlagsOffset); return af; }

	std::list<Item*> GetInventoryItemsAtTab(int index);
	void ForceLoadTab(int index);

	int StashTabPage;
	string StashTabNickname;

	Inventory::InventoryTabPermissions Permissions;
	Inventory::InventoryTabFlags Flags;
	Inventory::InventoryTabAffinityFlags AffinityFlags;

	virtual bool DoesItemFitInSlots(Item* itm, int CellX, int CellY) { return false; }

	int OccupiedCells[12][12]; //12 by 12 ingame. we can put item index or whatever as the int to make a quick/dirty array hashmap

	virtual ~StashInventory() {};
};

class CurrencyInventory : virtual public InventoryBase //Multi-level inheritance example
{
public:
	std::list<Item*> GetInventoryItems();

	virtual bool DoesItemFitInSlots(Item* itm, int CellX, int CellY) { return false; }

	friend CurrencyInventory operator+= (CurrencyInventory lhs, Item* rhs) //confusing
	{
		lhs.Items.push_back(rhs);
	}

	virtual ~CurrencyInventory() {};
};

class TradeInventory : public NormalInventory
{
public:
	TradeInventory() {}

	std::list<Item*> GetTradeWindowItems(int inventorySide, bool stashLoaded);
	bool ContainsItem(Inventory::TradeWindowSide side, wstring itemName, int quantity, bool fullStashLoaded);
	
	Inventory::TradeWindowSide side;

	virtual bool DoesItemFitInSlots(Item* itm, int CellX, int CellY) { return false; }

	int OccupiedCells[12][5]; //12 by 5 ingame

	virtual ~TradeInventory() {};
};