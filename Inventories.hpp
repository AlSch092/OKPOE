#pragma once
#include "Entity.hpp"

namespace Inventories
{
	static UINT64 StartingPointOffset = 0x40;
	static UINT64 StructLengthOffset = 0x60;

	static UINT64 LeftHandOffset = StartingPointOffset + (0 * StructLengthOffset);
	static UINT64 RightHandOffset = StartingPointOffset + (1 * StructLengthOffset);
	static UINT64 ChestOffset = StartingPointOffset + (2 * StructLengthOffset);
	static UINT64 HelmetOffset = StartingPointOffset + (3 * StructLengthOffset);
	static UINT64 GlovesOffset = StartingPointOffset + (4 * StructLengthOffset);
	static UINT64 BootsOffset = StartingPointOffset + (5 * StructLengthOffset);
	static UINT64 AmuletOffset = StartingPointOffset + (6 * StructLengthOffset);
	static UINT64 LeftRingOffset = StartingPointOffset + (7 * StructLengthOffset);
	static UINT64 RightRingOffset = StartingPointOffset + (8 * StructLengthOffset);
	static UINT64 BeltOffset = StartingPointOffset + (9 * StructLengthOffset);

	Entity* GetLeftHandWeapon(Entity* e);
	Entity* GetRightHandWeapon(Entity* e);
	Entity* GetChestArmour(Entity* e);
	Entity* GetHelmet(Entity* e);
	Entity* GetGloves(Entity* e);
	Entity* GetBoots(Entity* e);
	Entity* GetLeftRight(Entity* e);
	Entity* GetRightRing(Entity* e);
	Entity* GetAmulet (Entity* e);
	Entity* GetBelt(Entity* e);
}