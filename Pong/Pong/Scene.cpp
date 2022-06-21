#include "Vector2.h"
#include "Scene.h"
#include <iostream>
#include <string>

int pointToIndex(const Vector2& p)
{
	return (-(int)p.y * Scene::getWidth() + (int)p.x);
}

bool inBounds(const Vector2& p)
{
	Scene& instance{ Scene::getInstance() };
	return p.x > 0.5f && p.x < instance.getBounds().x && p.y < -0.5f && p.y > instance.getBounds().y;
}

Scene::Scene(int width, int height)
	: m_width{ (width >= 30) ? width : 30 },
	m_height{ (height >= 15) ? height : 15 },
	m_center{ width * 0.5f, -height * 0.5f },
	m_bounds{ width - 1.5f, -height + 0.5f }
{
	m_scene.resize(m_width * m_height);
}

Scene& Scene::getInstance()
{
	static Scene& s_ref{ set() };
	return s_ref;
}

Scene& Scene::set(int width, int height)
{
	static Scene s_scene{ width, height };
	return s_scene;
}

void Scene::draw()
{
	for (int i{ 0 }; i < set().m_scene.length(); ++i)
	{
		Scene& instance{ getInstance() };

		// Convert index to integer x and y coordinates
		int x{ i % instance.m_width };
		int y{ -i / instance.m_width };

		if (x + 1 == instance.m_width)
		{
			instance.m_scene[i] = '\n';
		}
		else if (x == 0 || x == (instance.m_width - 2))
		{
			instance.m_scene[i] = static_cast<unsigned char>(fblock);
		}
		else if (y == 0)
		{
			instance.m_scene[i] = static_cast<unsigned char>(thblock);
		}
		else if (y == -(instance.m_height - 1))
		{
			instance.m_scene[i] = static_cast<unsigned char>(bhblock);
		}
		else
			instance.m_scene[i] = ' ';
	}
}

void Scene::replace(const Vector2& p, Object obj)
{
	if (inBounds(p))
		getInstance().m_scene.at(pointToIndex(p)) = static_cast<unsigned char>(obj);
}

Scene::Object Scene::getObjAtPoint(const Vector2& p)
{
	if (inBounds(p))
		return static_cast<Object>(getInstance().m_scene.at(pointToIndex(p)));
	return null;
}

void Scene::display()
{
	std::cout << getInstance().m_scene.data();
}