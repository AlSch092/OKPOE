#include "Aim.hpp"

int Distances::GetDistanceBetweenObjects(Vector2 A, Vector2 B)
{
	double resultX = pow((double)(B.X - A.X), 2);
	double resultY = pow((double)(B.Y - A.Y), 2);
	double FinalResult = sqrt(resultX + resultY);
	return (int)FinalResult;
}

FLOAT Distances::AngleBetween(Vector2 v1, Vector2 v2)
{
	float len1 = sqrt((FLOAT)(v1.X * v1.X + v1.Y * v1.Y));
	float len2 = sqrt((FLOAT)(v2.X * v2.X + v2.Y * v2.Y));

	float dot = v1.X * v2.X + v1.Y * v2.Y;

	float a = dot / (len1 * len2);

	if (a >= 1.0)
		return 0.0;
	else if (a <= -1.0)
		return 3.14;
	else
		return acos(a); // 0..PI
}

BOOL Distances::IsInRectangle(FLOAT centerX, FLOAT centerY, FLOAT x, FLOAT y)
{
	FLOAT radius = NEARBY_RADIUS;

	return x >= centerX - radius && x <= centerX + radius &&
		y >= centerY - radius && y <= centerY + radius;
}

BOOL Distances::IsInRectangle(FLOAT centerX, FLOAT centerY, FLOAT x, FLOAT y, FLOAT radius)
{
	return x >= centerX - radius && x <= centerX + radius &&
		y >= centerY - radius && y <= centerY + radius;
}

//test if coordinate (x, y) is within a radius from coordinate (center_x, center_y)
BOOL Distances::IsPointInCircle(FLOAT centerX, FLOAT centerY, FLOAT x, FLOAT y)
{
	FLOAT radius = NEARBY_RADIUS;

	if (Distances::IsInRectangle(centerX, centerY, x, y))
	{
		FLOAT dx = centerX - x;
		FLOAT dy = centerY - y;
		dx *= dx;
		dy *= dy;
		FLOAT distanceSquared = dx + dy;
		FLOAT radiusSquared = radius * radius;
		return distanceSquared <= radiusSquared;
	}
	return FALSE;
}

BOOL Distances::IsPointInCircle(FLOAT centerX, FLOAT centerY, FLOAT x, FLOAT y, FLOAT Radius)
{
	if (Distances::IsInRectangle(centerX, centerY, x, y, Radius))
	{
		FLOAT dx = centerX - x;
		FLOAT dy = centerY - y;
		dx *= dx;
		dy *= dy;
		FLOAT distanceSquared = dx + dy;
		FLOAT radiusSquared = Radius * Radius;
		return distanceSquared <= radiusSquared;
	}
	return FALSE;
}