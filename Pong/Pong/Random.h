#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random
{
private:
	static std::mt19937 mt;

public:
	static int getInt(int min, int max);
	static bool getBool();
};

#endif