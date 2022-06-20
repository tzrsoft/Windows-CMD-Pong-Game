#include "Vector2.h"
#include <cmath>

Vector2::Vector2(float initX, float initY) : x{ initX }, y{ initY }
{
}

Vector2 Vector2::getUnitVector(float angle)
{
	return { std::cosf(angle), std::sinf(angle) };
}

Vector2 Vector2::operator-()
{
	return { -x, -y };
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 operator*(const Vector2& v, float value)
{
	return { v.x * value, v.y * value };
}