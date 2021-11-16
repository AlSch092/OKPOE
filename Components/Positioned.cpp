#include "Positioned.hpp"

Vector2 Positioned::GetGridPosition(Entity* e)
{
	Vector2 v = Vector2{ 0, 0 };
	UINT64 PositionedComponentPtr = e->PositionedComponentAddress;
	
	if (PositionedComponentPtr == 0)
	{
		printf("No positioned component address found.\n");
		return { 0, 0 };
	}

	INT32 X = DereferenceSafe<INT32>(PositionedComponentPtr + Positioned::GridPositionOffset);
	INT32 Y = DereferenceSafe<INT32>(PositionedComponentPtr + (Positioned::GridPositionOffset + 4));

	if (X == NULL || Y == NULL)
	{
		return { 0, 0 };
	}

	v.X = X;
	v.Y = Y;

	return v;
}

bool Positioned::IsEntityNeutral(Entity* e)
{
	UINT64 PositionedComponentPtr = e->PositionedComponentAddress;
	
	if (PositionedComponentPtr == 0)
		return NULL;

	byte neutral = ReadPointer<byte>(PositionedComponentPtr, Positioned::IsNeutralOffset);
	
	return (bool)neutral;
}