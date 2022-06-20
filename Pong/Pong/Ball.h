#ifndef BALL_H
#define BALL_H

#include "Vector2.h"

class Ball
{
public:
	enum BounceDir
	{
		upDown,
		leftRight,
	};

	Vector2 position{};
	Vector2 velocity{};
	bool active{};

	Ball(const Vector2& position, const Vector2& velocity, bool active);

	static Vector2 leftStartPos();
	static Vector2 rightStartPos();

	void move(float elapsedTime);
	void gravityImpact(const Vector2& gravity, float elapsedTime);
	void bounce(BounceDir);
	void draw();
};

#endif