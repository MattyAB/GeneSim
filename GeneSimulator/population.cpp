#include "population.h"

Population::Population(uint16_t size) : size(size) {
	this->population = new Individual[size];
}

void Population::PopulateRand() {
	uint32_t* genome = { 0x00000000 };
	for (int i = 0; i < this->size; i++)
	{
		Individual member = Individual(i, genome, 1, 0, 0);
	}
}