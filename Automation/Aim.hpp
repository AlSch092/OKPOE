#pragma once
#define NEARBY_RADIUS 200.00f;
#include <math.h>
#include "Structures.hpp"

namespace Directions
{
	//facing top right is positive in both directions, tilted cross
	const Vector2 Aim_TopLeft = { -10, 10 };
	const Vector2 Aim_BottomLeft = { -10, -10 };
	const Vector2 Aim_TopRight = { 10, 10 };
	const Vector2 Aim_BottomRight = { 10, -10 };

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
