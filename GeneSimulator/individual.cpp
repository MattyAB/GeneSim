#include "individual.h"
#include "random.h"

Individual::Individual(uint16_t ID, uint32_t* genome, uint16_t x, uint16_t y)
	: ID(ID), genome(genome), network(genome) {
	this->x = x;
	this->y = y;
	this->direction = RandomTwoBit();
}

IndivDrawData Individual::GetDrawData()
{
	uint8_t* col = network.GetColour();
	return IndivDrawData({ this->x, this->y, { col[0], col[1], col[2] }});
}

std::vector<float> Individual::Feedforward(std::vector<float> input)
{
	return this->network.Feedforward(input);
}

void Individual::SetLocation(uint16_t x, uint16_t y)
{
	this->x = x;
	this->y = y;
}