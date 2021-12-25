#pragma once

#include "individual.h"
#include <vector>

class Population {
private:
//	const uint16_t size;
	std::vector<Individual> population;

public:
	Population();
	void PopulateRand();
};