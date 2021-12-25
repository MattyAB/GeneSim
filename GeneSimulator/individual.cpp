#include "individual.h"

Individual::Individual(uint16_t ID, uint32_t* genome, uint16_t genomelen, uint16_t x, uint16_t y)
	: ID(ID), genome(genome), genomelen(genomelen), network(genome) {
	this->x = x;
	this->y = y;
	// std::cout << "Hi from individual " << ID << "\n";
}