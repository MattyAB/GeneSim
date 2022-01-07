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
	std::vector<float> Feedforward(std::vector<float> input);
	void SetLocation(uint16_t x, uint16_t y);

	uint16_t x;
	uint16_t y;
	uint8_t direction;
private:
	NeuralNet network;
};