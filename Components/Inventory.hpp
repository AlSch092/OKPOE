#pragma once
#include "Element.hpp"

namespace Inventory //inherited class from elemnt
{
	static const UINT64 ElementId = 0x420;
	static const UINT64 EntityOffset = 0x428;
	static const UINT64 CellXOffset = 0x430;
	static const UINT64 CellYOffset = CellXOffset + 4;
	static const UINT64 CellWidthOffset = 0x438;
	static const UINT64 CellHeightOffset = CellWidthOffset + 4;
	static const UINT64 IsHoveredOffset = 0x496;
	static const UINT16 AffinityFlagsOffset = 0x4D0;

	enum InventoryTabPermissions : byte  //ty exileAPI for these enums
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

	enum InventoryTabAffinityFlags : short //0x4B0 offset
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
  UINT32 ElementId;
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

private:
	Inventory::InventoryTabPermissions Permissions;
	Inventory::InventoryTabFlags Flags;
	Inventory::InventoryTabAffinityFlags AffinityFlags; //more or less typeOf

};

class CurrencyInventory : public InventoryBase
{
public:
	std::list<Inventory::Item*> GetInventoryItems();
private:
	Inventory::InventoryTabPermissions Permissions;
	Inventory::InventoryTabFlags Flags;
	Inventory::InventoryTabAffinityFlags AffinityFlags; //more or less typeOf
};

class StashInventory : public InventoryBase
{

};
