#pragma once

#include "individual.h"
#include <vector>

class Population {
private:
//	const uint16_t size;
	std::vector<Individual> population;
	std::vector<float> GetIndivSensoryNeurons(int indiv);
	void PushIndivMotorNeurons(int indiv, std::vector<float> neurondata);
	bool IndivAtLocation(uint16_t x, uint16_t y);

public:
	Population();
	Population(std::vector<Individual> previouspopulation);
	void PopulateRand();
	void StorePopulation();
	void LoadPopulation();
	std::vector<IndivDrawData> GetFrameData();

	Individual GetIndiv(int i);

	void Tick();
};