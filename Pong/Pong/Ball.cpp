#include "Vector2.h"
#include "Ball.h"
#include "Scene.h"
#include "Random.h"

float getRandomY()
{
	return -Random::getInt(-Scene::getCenter().y - 10, -Scene::getCenter().y + 10);
}

Ball::Ball(const Vector2& initPosition, const Vector2& initVelocity, bool initActive)
	: position{ initPosition }, velocity{ initVelocity }, active{ initActive }
{
}

Vector2 Ball::leftStartPos()
{
	return Vector2{ Scene::getCenter().x - 15.0f, getRandomY() };
}

Vector2 Ball::rightStartPos()
{
	return Vector2{ Scene::getCenter().x + 15.0f, getRandomY() };
}

void Ball::move(float elapsedTime)
{
	if (active)
		position += velocity * elapsedTime;
}

void Ball::gravityImpact(const Vector2& gravity, float elapsedTime)
{
	if (active)
		velocity += gravity * elapsedTime;
}

void Ball::bounce(BounceDir dir)
{
	switch (dir)
	{
	case upDown:
		velocity.y *= -1;
		return;
	case leftRight:
		velocity.x *= -1;
		return;
	}
}

void Ball::draw()
{
	if (active)
		Scene::replace(position, Scene::square);
}