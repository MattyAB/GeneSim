#pragma once

#include "individual.h"

class Population {
private:
	const uint16_t size;
	Individual* population;

public:
	Population(uint16_t size);
	void PopulateRand();
};