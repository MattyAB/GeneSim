#include <cstdint>
#include <iostream>

#include "neuralnet.h"
#include "render.h"

class Individual {
public:
	const uint16_t ID;
	const uint32_t* genome;

	Individual(uint16_t ID = 25565, uint32_t* genome = {0}, uint16_t x = 0, uint16_t y = 0);

	IndivDrawData GetDrawData();

	uint16_t x;
	uint16_t y;
private:
	NeuralNet network;
};