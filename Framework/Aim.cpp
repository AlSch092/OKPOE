#include "Aim.hpp"

int Distances::GetDistanceBetweenObjects(int x_A, int y_A, int x_B, int y_B)
{
	double resultX = pow((double)(x_B - x_A), 2);
	double resultY = pow((double)(y_B - y_A), 2);
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

//test if coordinate (x, y) is within a radius from coordinate (center_x, center_y)
BOOL Distances::IsPointInCircle(FLOAT centerX, FLOAT centerY, FLOAT x, FLOAT y)
{
	//FLOAT radius = NEARBY_RADIUS;
	FLOAT radius = 50.0f;

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
	if (Distances::IsInRectangle(centerX, centerY, x, y))
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

Vector2 Directions::GetDirectional(Vector2 v1, Vector2 v2)
{
	int magnitude = 0;

	if (v2.X - v1.X >= 0) //mob is positive infront
	{
		if (v2.Y - v1.Y >= 0) //mob is ontop
		{
			return Directions::Aim_TopRight;
		}
		else if(v2.Y - v1.Y < 0) //mob is 
		{
			return Directions::Aim_BottomRight;
		}
	}
	else if (v2.X - v1.X < 0)
	{
		if (v2.Y - v1.Y >= 0)
		{
			return Directions::Aim_TopLeft;
		}
		else if (v2.Y - v1.Y < 0)
		{
			return Directions::Aim_BottomLeft;
		}
	}
}
