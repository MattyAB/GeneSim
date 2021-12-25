#include <random>
#include <ctime>

#include <iostream>

void RandInt(uint32_t* randint)
{
	uint32_t value = 0;
	for (int i = 0; i < 4; i++)
	{
		value += rand() << (8 * i);
	}
	*randint = value;
}

uint16_t RandInt16()
{
	uint16_t value = 0;
	for (int i = 0; i < 2; i++)
	{
		value += rand() << (8 * i);
	}
	return value;
}

void ArrayRandom(uint32_t* arrayptr, uint16_t length)
{
	std::time_t t = std::time(0);
	srand(t); // seed random number generator with our time - so that we don't get the same population every time!
	for (uint16_t i = 0; i < length; i++)
	{
		RandInt(&arrayptr[i]);
		// std::cout << arrayptr[i] << "\n"; // Just to check that our value we generate is in fact random!
	}
}