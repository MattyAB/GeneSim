#include "grid.h"

#include <cstdint>

Grid::Grid(uint16_t size, Population &pop) : population(pop) {
	this->grid = new uint16_t[size * size];
}