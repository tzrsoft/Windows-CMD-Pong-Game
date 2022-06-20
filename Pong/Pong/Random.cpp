#include "Random.h"
#include <random>
#include <chrono>

std::mt19937 Random::mt{ static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()) };

int Random::getInt(int min, int max)
{
	return std::uniform_int_distribution<>{min, max}(mt);
}

bool Random::getBool()
{
	return std::uniform_int_distribution<>{0, 1}(mt);
}