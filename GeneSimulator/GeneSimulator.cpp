#include <iostream>

#include "grid.h"
#include "population.h"

int main()
{
    std::cout << "Hello World!\n";
    Population pop = Population(100);
    pop.PopulateRand();
    Grid grid = Grid((uint16_t)1000, pop);
}