#pragma once

#include "population.h"

class Simulator {
private:
	Population& pop;
	Render& render;
public:
	Simulator(Population & pop, Render &render);
	void Simulate(int rounds, bool render);
	std::vector<Individual> GetSurvivors(int survivalcondition);
};