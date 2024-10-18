#include "utilities.h"

int Utilities:: Randomise(int minValue, int maxValue) {
	if (minValue > maxValue) 
	{
		std::swap(minValue, maxValue);
	}
	int v = minValue + (rand() % (maxValue - minValue + 1));
	return v;
}