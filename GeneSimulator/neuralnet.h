#pragma once

#include "globals.h"
#include <vector>

struct Connection {
public:
	unsigned char inputnode;
	unsigned char outputnode;
	float weight;
};

class NeuralNet {
private:
	std::vector<Connection> connections;

public:
	NeuralNet(uint32_t* genome);
};