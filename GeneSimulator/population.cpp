#include "population.h"
#include "globals.h"
#include "random.cpp"

#include <iostream>
#include <fstream>
#include <sstream>

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
		framedata.push_back({ indiv.x, indiv.y, { 0xff, 0, 0 } });
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