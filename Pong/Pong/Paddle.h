#ifndef PADDLE_H
#define PADDLE_H

#include "Vector2.h"
#include <array>

class Paddle
{
private:
	std::array<Vector2, 3> m_points;

public:
	Paddle(const Vector2& startPos);

	const Vector2 topPos() const { return m_points[0]; }
	const Vector2 downPos() const { return m_points[2]; }

	void draw();
	void moveUp(float speed);
	void moveDown(float speed);
};

#endif