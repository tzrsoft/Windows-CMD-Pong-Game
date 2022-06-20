#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
	float x{};
	float y{};

	Vector2(float x = 0.0f, float y = 0.0f);
	static Vector2 getUnitVector(float angle); // returns a unit vector for given angle in radians

	Vector2 operator-();
	Vector2& operator+=(const Vector2& v);
	friend Vector2 operator*(const Vector2&, float);
};

#endif