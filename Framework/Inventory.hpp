#pragma once
#include "Element.hpp"
#include "AutoPlayer.hpp"

namespace Inventory //inherited class from elemnt
{
	static const UINT64 PickupIndex = 0x420;
	static const UINT64 EntityOffset = 0x428;
	static const UINT64 CellXOffset = 0x430;
	static const UINT64 CellYOffset = CellXOffset + 4;
	static const UINT64 CellWidthOffset = 0x438;
	static const UINT64 CellHeightOffset = CellWidthOffset + 4;
	static const UINT64 IsHoveredOffset = 0x496;
	static const UINT64 AffinityFlagsOffset = 0x4D0; //only for inventories.. not trade windows?

	static const UINT64 TradeWindowOffset_OurItems = 0x458;//1st offset
	static const UINT64 TradeWindowOffset_TheirItems = 0x460;

	static const UINT64 TradeWindowOffset_OurItems2 = 0x6B8; //1st offset ... does this mean the new windows popping up become the first tabs of stash??
	static const UINT64 TradeWindowOffset_TheirItems2 = 0x6C0;

	//this ptr will have most if not all important windows, gg
	static const UINT64 CurrencyTabOffset = 0x4D0; //redo this for hopefully a smaller solution
	static const UINT64 StashTab1Offset = 0x6B8; //+8 for each tab..
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

	struct Item
	{
		Entity* ItemEnt;
		
		int CellX;
		int CellY;
		
		int Height;
		int Width;
		
		bool isHovered;
		
		int StashPage;
		
		UINT64 MemoryAddress;
		UINT32 ElementId;
		
		int stackSize;
		
		wstring UniqueName;
		wstring BaseName;
		wstring FullName; //Unique name + Base Name
		wstring PriceTag;

	};
	
}

class InventoryBase : ElementBase
{
public:

	InventoryBase() {};
	InventoryBase(UINT64 ElementAddr) : ElementAddress(ElementAddr) { }

	//virtual std::list<Inventory::Item*> GetInventoryItems();

	std::list<Inventory::Item*> Items;
	UINT64 ElementAddress;

	virtual bool DoesItemFitInSlots(Inventory::Item* itm, int CellX, int CellY) { return false; };
};

class NormalInventory : public InventoryBase
{
public:

	NormalInventory() {};
	
	std::list<Inventory::Item*> GetInventoryItems();
	Inventory::Item* GetInventoryItem(UINT64 StructAddr);

	virtual bool DoesItemFitInSlots(Inventory::Item* itm, int CellX, int CellY) { return false; }

	virtual ~NormalInventory() {};

	friend NormalInventory operator+= (NormalInventory lhs, Inventory::Item* rhs) //confusing
 	{
		lhs.Items.push_back(rhs);
	}

};

class StashInventory : public NormalInventory
{
public:
	void SetTabPermissions(byte p);
	void SetTabFlags(byte f);
	void SetTabAffinityFlags(UINT16 af);

	UINT16 GetAffinityFlags(UINT64 ElementAddr) { UINT16 af = DereferenceSafe<UINT16>(ElementAddr + Inventory::AffinityFlagsOffset); return af; }

	std::list<Inventory::Item*> GetInventoryItemsAtTab(int index);
	void ForceLoadTab(int index);

	int StashTabPage;
	string StashTabNickname;

	Inventory::InventoryTabPermissions Permissions;
	Inventory::InventoryTabFlags Flags;
	Inventory::InventoryTabAffinityFlags AffinityFlags;

	virtual bool DoesItemFitInSlots(Inventory::Item* itm, int CellX, int CellY) { return false; }

	virtual ~StashInventory() {};
};

class CurrencyInventory : public StashInventory
{
public:
	std::list<Inventory::Item*> GetInventoryItems();

	int ChaosOrbs, ExaltedOrbs, VaalOrbs, FusingOrbs, ChromaticOrbs = { 0 };

	virtual bool DoesItemFitInSlots(Inventory::Item* itm, int CellX, int CellY) { return false; }

	friend CurrencyInventory operator+= (CurrencyInventory lhs, Inventory::Item* rhs) //confusing
	{
		lhs.Items.push_back(rhs);
	}

	virtual ~CurrencyInventory() {};
};

class TradeInventory : public InventoryBase
{
public:
	std::list<Inventory::Item*> GetTradeWindowItems(int inventorySide, bool stashLoaded);
	bool ContainsItem(Inventory::TradeWindowSide side, wstring itemName, int quantity);
	
	Inventory::TradeWindowSide side;

	virtual bool DoesItemFitInSlots(Inventory::Item* itm, int CellX, int CellY) { return false; }

	virtual ~TradeInventory() {};
};
