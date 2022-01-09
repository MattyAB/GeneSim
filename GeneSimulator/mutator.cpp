#include "mutator.h"
#include "globals.h"
#include "random.h"

Mutator::Mutator()
{

}

void Mutator::MutateGene(uint32_t* gene)
{
	uint16_t seed = RandInt16();
	if (seed % _mutationrate_ == 0)
	{
		*gene = (*gene) ^ (1 << (seed % 32));
	}
}