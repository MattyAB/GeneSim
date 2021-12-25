#include "neuralnet.h"
#include <iostream>

NeuralNet::NeuralNet(uint32_t* genome) 
{
	this->connections.reserve(_genomesize_);
	for (int i = 0; i < _genomesize_; i++)
	{
		uint32_t thisgene = genome[i];
		Connection connection = Connection();
		connection.inputnode = (unsigned char)((genome[i] >> 24) & 0xff);
		connection.outputnode = (unsigned char)((genome[i] >> 16) & 0xff);
		if((genome[i] & 0x8000) == 0x8000)
			connection.weight = (float)(genome[i] & 0x7fff) / (float)(1 << 13);
		else
			connection.weight = -(float)(genome[i] & 0x7fff) / (float)(1 << 13);
		this->connections.push_back(connection);
	}
}