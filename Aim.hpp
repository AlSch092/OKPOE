#pragma once
#define NEARBY_RADIUS 125.0f; //duno
#include <math.h>
#include "Structures.hpp"

namespace Distances
{
	int GetDistanceBetweenObjects(Vector2 A, Vector2 B);
	float AngleBetween(Vector2 v1, Vector2 v2);

	BOOL IsPointInCircle(FLOAT centerX, FLOAT centerY, FLOAT x, FLOAT y);
	BOOL IsInRectangle(FLOAT centerX, FLOAT centerY, FLOAT x, FLOAT y);

	BOOL IsPointInCircle(FLOAT centerX, FLOAT centerY, FLOAT x, FLOAT y, FLOAT Radius);
	BOOL IsInRectangle(FLOAT centerX, FLOAT centerY, FLOAT x, FLOAT y, FLOAT Radius);
}