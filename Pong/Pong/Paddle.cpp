#include "Vector2.h"
#include "Scene.h"
#include "Paddle.h"

Paddle::Paddle(const Vector2& p)
{
	for (int i{ 0 }; i < m_points.size(); ++i)
	{
		m_points[i] = Vector2{ p.x, p.y - i };
	}
}

void Paddle::draw()
{
	for (int i{ 0 }; i < m_points.size(); ++i)
	{
		Scene::replace(m_points[i], Scene::Object::fblock);
	}
}

void Paddle::moveUp(float speed)
{
	for (int i{ 0 }; i < m_points.size(); ++i)
	{
		m_points[i].y += speed;
	}
}

void Paddle::moveDown(float speed)
{
	for (int i{ 0 }; i < m_points.size(); ++i)
	{
		m_points[i].y -= speed;
	}
}