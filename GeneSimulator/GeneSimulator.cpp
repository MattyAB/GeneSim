#include <iostream>

#include <fstream>
#include <string>

#include "grid.h"
#include "population.h"
#include "globals.h"
#include "render.h"
#include "simulator.h"

const char config[] = "C:\\Users\\matth\\OneDrive\\Code\\C++\\GeneSimulator\\GeneSimulator\\config.txt";

int main(int argc, char **args)
{
    std::ifstream infile(config);
    std::string line;
    while (std::getline(infile, line))
    {
        size_t pos = line.find_first_of('=');
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        if (key == "populationsize")
            _populationsize_ = (uint16_t)std::stoi(value);
        else if (key == "genomesize")
            _genomesize_ = (uint16_t)std::stoi(value);
        else if (key == "boardsize")
            _boardsize_ = (uint16_t)std::stoi(value);
        else if (key == "inputneurons")
            _inputneurons_ = (uint16_t)std::stoi(value);
        else if (key == "hiddenneurons")
            _hiddenneurons_ = (uint16_t)std::stoi(value);
        else if (key == "outputneurons")
            _outputneurons_ = (uint16_t)std::stoi(value);
        else if (key == "populationstorage")
            _populationstorage_ = value;
        else if (key == "renderscale")
            _renderscale_ = (uint16_t)std::stoi(value);
    }

    Population pop = Population();
    pop.PopulateRand();
    //pop.LoadPopulation();


    Render render = Render();
    Simulator simulation = Simulator(pop, render);
    simulation.Simulate(100);

    render.SaveVideo();

    pop.StorePopulation();
}