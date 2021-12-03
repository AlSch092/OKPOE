#pragma once
#define MAX_RADIUS 210.00f;
#include <math.h>
#include "Structures.hpp"

namespace Directions
{
	//facing top right is positive in both directions, tilted cross
	const Vector2 Aim_TopLeft = { -1, 1 };
	const Vector2 Aim_BottomLeft = { -1, -1 };
	const Vector2 Aim_TopRight = { 1, 1 };
	const Vector2 Aim_BottomRight = { 1, -1 }; //unit vectors to position the character... can also be done writing the Tilt offset

	Vector2 GetDirectional(Vector2 v1, Vector2 v2);
}

namespace Distances
{
	int GetDistanceBetweenObjects(int x_A, int y_A, int x_B, int y_B);
	float AngleBetween(Vector2 v1, Vector2 v2);

	BOOL IsPointInCircle(FLOAT centerX, FLOAT centerY, FLOAT x, FLOAT y);
	BOOL IsInRectangle(FLOAT centerX, FLOAT centerY, FLOAT x, FLOAT y);

	BOOL IsPointInCircle(FLOAT centerX, FLOAT centerY, FLOAT x, FLOAT y, FLOAT Radius);
	BOOL IsInRectangle(FLOAT centerX, FLOAT centerY, FLOAT x, FLOAT y, FLOAT Radius);
}
