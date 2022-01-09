#include "population.h"
#include "globals.h"
#include "random.h"
#include "mutator.h"

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

	// Direction up/down neuron and left/right neuron
	if (population[indiv].direction == 0) // right
	{
		inputs.push_back(0.0f);
		inputs.push_back(1.0f);
	}
	if (population[indiv].direction == 1) // up
	{
		inputs.push_back(1.0f);
		inputs.push_back(0.0f);
	}
	if (population[indiv].direction == 2) // left
	{
		inputs.push_back(0.0f);
		inputs.push_back(-1.0f);
	}
	if (population[indiv].direction == 3) // down
	{
		inputs.push_back(-1.0f);
		inputs.push_back(0.0f);
	}

	for (int i = 0; i < _inputneurons_ - 3; i++) 
	{
		inputs.push_back(0.0f);
	}

	return inputs;
}

void Population::PushIndivMotorNeurons(int indiv, std::vector<float> neurondata)
{
	// Step forward neuron
	if (neurondata[0] >= 0.5)
	{
		uint16_t newx = population[indiv].x;
		uint16_t newy = population[indiv].y;

		if (population[indiv].direction == 0 && population[indiv].x < _boardsize_) // right
			newx += 1;
		if (population[indiv].direction == 1 && population[indiv].x > 0) // up
			newy += 1;
		if (population[indiv].direction == 2 && population[indiv].x > 0) // left
			newx -= 1;
		if (population[indiv].direction == 3 && population[indiv].x < _boardsize_) // down
			newy -= 1;

		if (!IndivAtLocation(newx, newy))
		{
			population[indiv].SetLocation(newx, newy);
		}
	}

	// Rotate neuron
	if (neurondata[1] >= 0.75) // Tanh means that this is hit when the raw output value is > 1
	{
		population[indiv].direction = (population[indiv].direction + 1) % 4;
	}
	if (neurondata[1] <= 0.25) // Tanh means that this is hit when the raw output value is < -1
	{
		population[indiv].direction = (uint8_t)(population[indiv].direction - 1) % 4;
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

Population::Population(std::vector<Individual> individuals)
{
	Mutator mutator = Mutator();

	this->population.reserve(_populationsize_);

	for (uint16_t i = 0; i < _populationsize_; i++) // Each new member
	{
		int parent1 = RandInt16() % individuals.size();
		int parent2 = RandInt16() % individuals.size();

		int counter = 16; // Counts how many times we have used this integer. If we have used this integer 15 times we pick a new one.
		uint16_t seed = 0;

		uint32_t* newgenome = new uint32_t[_genomesize_];

		for (int j = 0; j < _genomesize_; j++) // For each gene of the new member
		{
			if (counter == 16)
			{
				seed = RandInt16();
				counter = 0;
			}

			auto test = seed % 2 == 0;

			uint32_t newgene = (seed % 2 == 0) ? individuals[parent1].genome[j] : individuals[parent2].genome[j];
			seed = seed >> 1;

			mutator.MutateGene(&newgene);

			newgenome[j] = newgene;

			counter++;
		}

		uint16_t x = RandInt16() % _boardsize_;
		uint16_t y = RandInt16() % _boardsize_;
		this->population.push_back({ i, newgenome, x, y });
	}
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

Individual Population::GetIndiv(int i)
{
	return population[i];
}