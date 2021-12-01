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
	static const UINT64 AffinityFlagsOffset = 0x4D0;

	//this ptr will have most if not all important windows, gg
	static const UINT64 CurrencyTabOffset = 0x4D0; //redo this for hopefully a smaller solution
	static const UINT64 StashTab1Offset = 0x6B8; //+8 for each tab..
	static const UINT64 StashTab2Offset = StashTab1Offset + 8;
	static const UINT64 StashTab3Offset = StashTab2Offset + 8;
	static const UINT64 StashTab4Offset = StashTab3Offset + 8;



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
		uint64_t MemoryAddress;
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


};

class NormalInventory : public InventoryBase
{
public:

	NormalInventory() {};

	void SetTabPermissions(byte p);
	void SetTabFlags(byte f);
	void SetTabAffinityFlags(UINT16 af);

	UINT16 GetAffinityFlags(UINT64 ElementAddr) { UINT16 af = DereferenceSafe<UINT16>(ElementAddr + Inventory::AffinityFlagsOffset); return af; }
	std::list<Inventory::Item*> GetInventoryItems();
	Inventory::Item* GetInventoryItem(UINT64 StructAddr);



private:
	Inventory::InventoryTabPermissions Permissions;
	Inventory::InventoryTabFlags Flags;
	Inventory::InventoryTabAffinityFlags AffinityFlags;

};

class CurrencyInventory : public InventoryBase
{
public:
	std::list<Inventory::Item*> GetInventoryItems();
private:
	Inventory::InventoryTabPermissions Permissions;
	Inventory::InventoryTabFlags Flags;
	Inventory::InventoryTabAffinityFlags AffinityFlags;
};

class StashInventory : public NormalInventory
{
public:
	std::list<Inventory::Item*> GetInventoryItemsAtTab(int index);
	void ForceLoadTab(int index);
};
