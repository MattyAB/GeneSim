#include "population.h"
#include "globals.h"
#include "random.cpp"

Population::Population() {
	this->population.reserve(_populationsize_);
}

void Population::PopulateRand() {
	std::cout << "Generating population of size " << _populationsize_ << " with genenome length " << _genomesize_ << "...";

	for (uint16_t i = 0; i < _populationsize_; i++)
	{
		uint32_t* genome = new uint32_t[_genomesize_];
		ArrayRandom(genome, _genomesize_);
		uint16_t x = RandInt16() % _boardsize_;
		uint16_t y = RandInt16() % _boardsize_;
		this->population.push_back({ i, genome, 1, x, y });
	}

	std::cout << " Finished!\n";
}