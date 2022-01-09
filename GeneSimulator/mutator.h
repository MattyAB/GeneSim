#pragma once
#include <stdint.h>

class Mutator {
private:

public:
	Mutator();
	void MutateGene(uint32_t* gene);
};