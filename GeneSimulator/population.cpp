#include "population.h"
#include "globals.h"
#include "random.h"

#include <iostream>
#include <fstream>
#include <sstream>

// TEMP: Just to check our video rendering works okay.
void Population::Tick()
{
	std::vector<std::vector<float>> outputs = std::vector<std::vector<float>>();
	outputs.reserve(_populationsize_);
	for (int i = 0; i < _populationsize_; i++)
	{
		std::vector<float> input = GetIndivSensoryNeurons(i);
		outputs.push_back(population[i].Feedforward(input));
	}

	for (int i = 0; i < _populationsize_; i++)
	{
		PushIndivMotorNeurons(i, outputs[i]);
	}
}

std::vector<float> Population::GetIndivSensoryNeurons(int indiv)
{
	std::vector<float> inputs = std::vector<float>();
	inputs.reserve(_inputneurons_);

	// 1 neuron
	inputs.push_back(1.0f);

	for (int i = 0; i < _inputneurons_ - 1; i++) 
	{
		inputs.push_back(0.0f);
	}

	return inputs;
}

// WHY IS THIS SIZE 48???

void Population::PushIndivMotorNeurons(int indiv, std::vector<float> neurondata)
{
	// Step forward neuron
	if (neurondata[0] >= 0.5)
	{
		uint16_t newx = population[indiv].x;
		uint16_t newy = population[indiv].y;

		if (population[indiv].direction == 0)
			newx += 1;
		if (population[indiv].direction == 1)
			newx -= 1;
		if (population[indiv].direction == 2)
			newy += 1;
		if (population[indiv].direction == 3)
			newy -= 1;

		if (!IndivAtLocation(newx, newy))
		{
			population[indiv].SetLocation(newx, newy);
		}
	}
}

bool Population::IndivAtLocation(uint16_t x, uint16_t y)
{
	for (int i = 0; i < _populationsize_; i++)
	{
		if (population[i].x == x && population[i].y == y)
			return true;
	}
	return false;
}

Population::Population() 
{
	this->population.reserve(_populationsize_);
}

std::vector<IndivDrawData> Population::GetFrameData()
{
	std::vector<IndivDrawData> framedata;
	framedata.reserve(_populationsize_);

	for (Individual indiv : population)
	{
		framedata.push_back(indiv.GetDrawData());
	}

	return framedata;

}

void Population::PopulateRand() 
{
	std::cout << "Generating population of size " << _populationsize_ << " with genenome length " << _genomesize_ << "...";

	SeedRandom();

	for (uint16_t i = 0; i < _populationsize_; i++)
	{
		uint32_t* genome = new uint32_t[_genomesize_];
		ArrayRandom(genome, _genomesize_);
		uint16_t x = RandInt16() % _boardsize_;
		uint16_t y = RandInt16() % _boardsize_;
		this->population.push_back({ i, genome, x, y });
	}

	std::cout << " Finished!\n";
}

void Population::StorePopulation()
{
	std::ofstream FileWrite(_populationstorage_);

	for (int i = 0; i < _populationsize_; i++)
	{
		for (int j = 0; j < _genomesize_; j++)
		{
			FileWrite << std::to_string(this->population[i].genome[j]);
			if (j != _genomesize_ - 1)
				FileWrite << ",";
		}
		if(i != _populationsize_ - 1)
			FileWrite << "\n";
	}

	FileWrite.close();
}

void Population::LoadPopulation()
{
	std::ifstream FileRead(_populationstorage_);
	std::string line;

	uint16_t j = 0;
	while (std::getline(FileRead, line))
	{
		uint32_t* genome = new uint32_t[_genomesize_];
		uint16_t i = 0;
		std::stringstream stream(line);
		while (stream.good())
		{
			std::string substr;
			getline(stream, substr, ',');
			genome[i] = static_cast<uint32_t>(std::stoul(substr)); // Is there a buffer overrun here?
			i++;
		}
		uint16_t x = RandInt16() % _boardsize_;
		uint16_t y = RandInt16() % _boardsize_;
		this->population.push_back({ j, genome, x, y });
		j++;
	}

	FileRead.close();
}