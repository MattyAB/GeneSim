#include <iostream>

#include "grid.h"
#include "population.h"
#include "globals.h"

int main(int argc, char **args)
{
    _populationsize_ = strtol(args[1], NULL, 16);
    _genomesize_ = strtol(args[2], NULL, 16);
    _boardsize_ = strtol(args[3], NULL, 16);

    Population pop = Population();
    pop.PopulateRand();
    Grid grid = Grid(pop);
}