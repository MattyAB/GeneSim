#pragma once

#include "population.h"

class Grid {
private:
	uint16_t* grid;
	Population population;

public:
	Grid(uint16_t size, Population &population);
};