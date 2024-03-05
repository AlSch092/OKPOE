#include "Positioned.hpp"

Vector2 Positioned::GetGridPosition(Entity* e)
{
	Vector2 v = Vector2{ 0, 0 };
	UINT64 PositionedComponentPtr = e->GetComponentAddress("Positioned");
	
	if (PositionedComponentPtr == 0)
	{
		printf("No positioned component address found.\n");
		return { 0, 0 };
	}

	INT32 X = DereferenceSafe<INT32>(PositionedComponentPtr + Positioned::Offsets::GridPosition);
	INT32 Y = DereferenceSafe<INT32>(PositionedComponentPtr + (Positioned::Offsets::GridPosition + 4));

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
	UINT64 PositionedComponentPtr = e->GetComponentAddress("Positioned");
	
	if (PositionedComponentPtr == 0)
		return NULL;

	byte neutral = ReadPointer<byte>(PositionedComponentPtr, Positioned::Offsets::IsNeutral);
	
	return (bool)neutral;
}

Vector2 Positioned::GetGroundPosition(Entity* e)
{
	Vector2 v = { 0, 0 };
	UINT64 PositionedComponentPtr = e->GetComponentAddress("Positioned");

	if (PositionedComponentPtr == NULL)
	{
		printf("No positioned component address found.\n");
		return v;
	}

	INT32 X = DereferenceSafe<INT32>(PositionedComponentPtr + Positioned::Offsets::GroundPosition);
	INT32 Y = DereferenceSafe<INT32>(PositionedComponentPtr + (Positioned::Offsets::GroundPosition + 4));

	v.X = X;
	v.Y = Y;

	return v;
}

FLOAT Positioned::GetRotation(Entity* e)
{
	FLOAT Rotation = 0.0f;

	UINT64 PositionedComponentPtr = e->GetComponentAddress("Positioned");

	if (PositionedComponentPtr == 0)
	{
		printf("No positioned component address found.\n");
		return 0.0f;
	}

	Rotation = DereferenceSafe<FLOAT>(PositionedComponentPtr + Positioned::Offsets::Rotation);
	return Rotation;

}


void Positioned::SetRotation(Entity* e, FLOAT Rotation)
{
	UINT64 PositionedComponentPtr = e->GetComponentAddress("Positioned");
	UINT64 PoEBase = (UINT64)GetModuleHandleA(NULL);

	if (PositionedComponentPtr == 0)
	{
		printf("No positioned component address found.\n");
		return;
	}

	UINT64 RotAddr = PositionedComponentPtr + Positioned::Offsets::Rotation;
	*(FLOAT*)RotAddr = Rotation;
}

bool Positioned::IsFrozenOrDead(Entity* e)
{
	bool frozenOrDead = false;

	UINT64 PositionedComponentPtr = e->GetComponentAddress("Positioned");

	if (PositionedComponentPtr == 0)
	{
		printf("No positioned component address found.\n");
		return false;
	}

	byte status = DereferenceSafe<byte>(PositionedComponentPtr + Positioned::Offsets::IsNeutral);
	//DWORD status =  DereferenceSafe<DWORD>(PositionedComponentPtr + Positioned::Offsets::IsNeutral);

	if (status == 0x82) //0xFFFFFFFF vs 01 00 00 00
		frozenOrDead = true;

	return frozenOrDead;
}