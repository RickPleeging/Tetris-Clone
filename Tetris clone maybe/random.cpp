#include "random.h"


int generateRandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

