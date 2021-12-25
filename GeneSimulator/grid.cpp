#include "grid.h"

#include <cstdint>

Grid::Grid(Population &pop) : population(pop) {
	this->grid = new uint16_t[_boardsize_ * _boardsize_];
}