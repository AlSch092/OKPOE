#pragma once
#include "Entity.hpp"


namespace Positioned
{
	const UINT64 ComponentOwner = 0x08;
	const UINT64 IsNeutralOffset = 0x159; //0x81 == is_neutral
	
	const UINT64 PreviousVector = 0x1B0;
	const UINT64 RelativeVector = 0x1C8;

	const UINT64 GridPositionOffset = 0x1E8;
	
	const UINT64 RotationOffset = 0x1F0;

	const UINT64 InwardsAngleOffset = 0x204; //dunno, makes char look towards ground until paralell?
	const UINT64 CharacterScaleOffset = 0x208;
	const UINT64 CharacterSizeOffset = 0x20C; //float

	const UINT64 WorldPositionOffset = 0x218;

	 Vector2 GetGridPosition(Entity* e);

	 bool IsEntityNeutral(Entity* e);

};