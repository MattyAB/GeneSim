#include "neuralnet.h"
#include <iostream>

NeuralNet::NeuralNet(uint32_t* genome) 
{
	this->connections.reserve(_genomesize_);
	for (int i = 0; i < _genomesize_; i++)
	{
		uint32_t thisgene = genome[i];
		Connection connection = Connection();
		unsigned char inputloc = (unsigned char)(genome[i] >> 24) % (_inputneurons_ + _hiddenneurons_);
		unsigned char outputloc = (unsigned char)(genome[i] >> 16) % (_outputneurons_ + _hiddenneurons_);
		if (inputloc < _inputneurons_)
		{
			connection.inputlayer = 0;
			connection.inputnode = inputloc;
			// Input is layer 0. So our output can be either layer 1 or 2
			if (outputloc < _hiddenneurons_)
			{
				connection.outputlayer = 1;
				connection.outputnode = inputloc;
			}
			else
			{
				connection.outputlayer = 2;
				connection.outputnode = inputloc - _hiddenneurons_;
			}
		}
		else
		{
			connection.inputlayer = 1;
			connection.inputnode = inputloc - _inputneurons_;
			// Input is layer 1. So output has to be layer 2.
			connection.outputlayer = 2;
			connection.outputnode = outputloc % _outputneurons_;
		}

		if((genome[i] & 0x8000) == 0x8000)
			connection.weight = (float)(genome[i] & 0x7fff) / (float)(1 << 13);
		else
			connection.weight = -(float)(genome[i] & 0x7fff) / (float)(1 << 13);
		this->connections.push_back(connection);
	}
}