#include "Headers/Vector2.h"
using GameEngine::Vector2;
#include <cmath>

float Vector2::Distance(Vector2& a, Vector2& b)
{
	float d;

	float diffX = a.x - b.x;

	float diffY = a.y - b.y;

	d = sqrt((diffY * diffY) + (diffX * diffX));

	return d;
}

Vector2& Vector2::Direction(Vector2& origin, Vector2& target)
{
	Vector2 dir;

	dir = target - origin;

	return dir;
}

Vector2& Vector2::Normalized(Vector2& vec)
{
	Vector2 norm;

	float w = sqrt(vec.x * vec.x + vec.y * vec.y);
	norm.x  = vec.x / w;
	norm.y	= vec.y / w;


	return norm;
}

Vector2& Vector2::normalized()
{
	Vector2 norm;

	float w = sqrt(x * x + y * y);
	norm.x = x / w;
	norm.y = y / w;


	return norm;
}
