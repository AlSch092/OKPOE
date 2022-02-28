#pragma once
#include "Element.hpp"
#include "AutoPlayer.hpp"

struct Item
{
	Entity* ItemEnt;

	int CellX;
	int CellY;

	int Height;
	int Width;

	int StashPage;

	UINT64 MemoryAddress;
	UINT32 ElementId;

	int stackSize;

	wstring UniqueName;
	wstring BaseName;
	wstring FullName; //Unique name + Base Name
	wstring PriceTag;

};

namespace Inventory //inherited class from elemnt
{
	static const UINT64 EntityIdOffset = 0x438;
	static const UINT64 EntityOffset = 0x440;
	static const UINT64 CellXOffset = 0x448;
	static const UINT64 CellYOffset = CellXOffset + 4;
	static const UINT64 CellWidthOffset = CellYOffset + 4;
	static const UINT64 CellHeightOffset = CellWidthOffset + 4;
	static const UINT64 IsHoveredOffset = 0x4AE;
	static const UINT64 AffinityFlagsOffset = 0x4D0; //needs updating

	static const UINT64 TradeWindowOffset_OurItems = 0x458;//1st offset
	static const UINT64 TradeWindowOffset_TheirItems = 0x460;

	static const UINT64 TradeWindowOffset_OurItems2 = 0x6B8; //
	static const UINT64 TradeWindowOffset_TheirItems2 = 0x6C0; //needs updating

	//this ptr will have most if not all important windows, gg
	static const UINT64 CurrencyTabOffset = 0x4D0; //redo this for hopefully a smaller solution
	static const UINT64 StashTab1Offset = 0x658; //+8 for each tab..
	static const UINT64 StashTab2Offset = StashTab1Offset + 8;
	static const UINT64 StashTab3Offset = StashTab2Offset + 8;
	static const UINT64 StashTab4Offset = StashTab3Offset + 8;

	static const UINT64 NPCTradeWindowOffset_OurItems = 0x6C0;
	static const UINT64 NPCTradeWindowOffset_TheirItems = TradeWindowOffset_OurItems - 8;

	enum TradeWindowSide
	{
		Remote = 0,
		Local
	};

	enum InventoryTabPermissions : byte //these 3 enums are copy pasta... no guarantee they're correct until I check manually
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

}

class InventoryBase : public ElementBase
{
public:

	InventoryBase() {};
	InventoryBase(UINT64 ElementAddr) : ElementAddress(ElementAddr) { }

	std::list<Item*> Items;
	UINT64 ElementAddress;

};

class NormalInventory : virtual public InventoryBase
{
public:

	NormalInventory() {};
	
	std::list<Item*> GetInventoryItems();
	Item* GetInventoryItem(UINT64 StructAddr);

	std::list<Item*> GetFlasks(bool isCached);

	virtual bool DoesItemFitInSlots(Item* itm, int CellX, int CellY) { return false; }

	friend NormalInventory operator+= (NormalInventory lhs, Item* rhs) 
 	{
		lhs.Items.push_back(rhs);
	}

	int OccupiedCells[12][5]; //12 by 5 ingame

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
	std::list<Item*> GetTradeWindowItems(int inventorySide, bool stashLoaded);
	bool ContainsItem(Inventory::TradeWindowSide side, wstring itemName, int quantity, bool fullStashLoaded);
	
	Inventory::TradeWindowSide side;

	virtual bool DoesItemFitInSlots(Item* itm, int CellX, int CellY) { return false; }

	int OccupiedCells[12][5]; //12 by 5 ingame

	virtual ~TradeInventory() {};
};
