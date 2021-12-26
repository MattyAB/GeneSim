#pragma once

#include "globals.h"
#include <vector>

struct Connection {
public:
	unsigned char inputnode;
	unsigned char outputnode;
	unsigned char inputlayer;
	unsigned char outputlayer;
	float weight;
};

class NeuralNet {
private:
	std::vector<Connection> connections;

public:
	NeuralNet(uint32_t* genome);
};