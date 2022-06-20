#ifndef SCENE_H
#define SCENE_H

#include "Vector2.h"
#include <string>

class Scene
{
public:
	enum Object
	{
		thblock = 223, // top half block     "▀"
		bhblock = 220, // bottom half block  "▄"
		fblock = 219,  // full block         "█"
		square = 254,  // square             "■"

		null = ' ',
	};

private:
	const int m_width{};
	const int m_height{};
	const Vector2 m_center{};
	const Vector2 m_bounds{}; // this holds coordinates of bottom right corner, max X and min Y position character can go
	std::basic_string<unsigned char> m_scene; // because of we're using extended ASCII characters we need a string of unsigned char 

	static Scene& getInstance();

	Scene(int width, int height);

public:
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	static Scene& set(int width = 30, int height = 15);

	static int getWidth() { return getInstance().m_width; }
	static int getHeight() { return getInstance().m_height; }
	static const Vector2& getCenter() { return getInstance().m_center; }
	static const Vector2& getBounds() { return getInstance().m_bounds; }

	static void draw();
	static void replace(const Vector2&, Object);
	static Object getObjAtPoint(const Vector2&);
	static void display();

	friend bool inBounds(const Vector2&);
};

#endif