#pragma once
#include "Entity.hpp"

#define pi 3.141593
#define MAX_UNITS_WALKABLE 130

namespace Positioned
{
	namespace Offsets
	{
		const UINT64 ComponentOwner = 0x08;
		const UINT64 IsNeutral = 0x1E5; //0x81 == is_neutral

		const UINT64 IsMovingPtr = 0x1E8; //frozen and dead enemies, this is set to 0

		const UINT64 PreviousVector = 0x22C;
		const UINT64 RelativeVector = 0x244;

		const UINT64 GridPosition = 0x290; //2b 88 ? ? ? ? b8 39 01 00 00 66 89 45 d8 48 8d 05 ? ? ? ? 48 8d 80 ? ? ? ? 
		const UINT64 Rotation = GridPosition + 8; //in RADIANS, F3 0F 11 83 ?? ?? ?? ?? 0f 57 c9 0f 2f c8 76 10 f3 0f 58 05 ? ? ? ? f3 0f
		const UINT64 WorldPosition = GridPosition + 10; //need update

		const UINT64 GroundPosition = 0x2C4; //some sort of grid position

		const UINT64 CameraPos = Rotation + 0x24;

		const UINT64 InwardsAngle = 0x204; //need update
		const UINT64 CharacterScale = 0x208; //need update
		const UINT64 CharacterSize = 0x20C;  //need update


	}
	
	 Vector2 GetGridPosition(Entity* e);

	 bool IsEntityNeutral(Entity* e);

	 Vector2 GetGroundPosition(Entity* e);
	 FLOAT GetRotation(Entity* e);
	 void SetRotation(Entity* e, FLOAT Rotation);

	 bool IsFrozenOrDead(Entity* e);
};