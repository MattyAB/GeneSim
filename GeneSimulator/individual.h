#include <cstdint>

#include <iostream>

class Individual {
public:
	const uint16_t ID;
	const uint32_t* genome;
	const uint16_t genomelen;

	uint16_t x;
	uint16_t y;

	Individual(uint16_t ID = 25565, uint32_t* genome = {0}, uint16_t genomelen = 0, uint16_t x = 0, uint16_t y = 0);
	//Individual() : ID(25565), genome({ 0x00000000 }), genomelen(1) {};

};