#include "neuralnet.h"
#include <iostream>
#include <math.h>

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
				connection.outputnode = outputloc;
			}
			else
			{
				connection.outputlayer = 2;
				connection.outputnode = outputloc - _hiddenneurons_;
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

	std::vector<float> input;
	input.reserve(_inputneurons_);
	for (int i = 0; i < _inputneurons_; i++)
		input.emplace_back(i);

	Feedforward(input);
}

std::vector<float> NeuralNet::Feedforward(std::vector<float> input)
{
	std::vector<float> hidden;
	std::vector<float> hiddentanh;
	std::vector<float> output;
	std::vector<float> outputtanh;
	hidden.reserve(_hiddenneurons_);
	hiddentanh.reserve(_hiddenneurons_);
	output.reserve(_outputneurons_);
	outputtanh.reserve(_outputneurons_);

	for (int i = 0; i < _hiddenneurons_; i++)
	{
		hidden.emplace_back(0);
		hiddentanh.emplace_back(0);
	}
	for (int i = 0; i < _outputneurons_; i++)
	{
		output.emplace_back(0);
		outputtanh.emplace_back(0);
	}

	for (int i = 0; i < connections.size(); i++)
	{
		if (connections[i].outputlayer == 1)
		{
			hidden[connections[i].outputnode] = hidden[connections[i].outputnode] + connections[i].weight * input[connections[i].inputnode];
		}
	}

	for (int i = 0; i < _hiddenneurons_; i++)
		hiddentanh[i] = tanh(hidden[i]);

	for (int i = 0; i < connections.size(); i++)
	{
		if (connections[i].inputlayer == 0)
		{
			output[connections[i].outputnode] = output[connections[i].outputnode] + connections[i].weight * input[connections[i].inputnode];
		}
		else
		{
			output[connections[i].outputnode] = output[connections[i].outputnode] + connections[i].weight * hidden[connections[i].inputnode];
		}
	}

	for (int i = 0; i < _outputneurons_; i++)
		outputtanh[i] = tanh(output[i]);

	return outputtanh;
}

uint8_t* NeuralNet::GetColour()
{
	uint8_t col[3];
	col[0] = static_cast<uint8_t>((connections[0].weight + 4) * 32);
	col[1] = static_cast<uint8_t>((connections[1].weight + 4) * 32);
	col[2] = static_cast<uint8_t>((connections[2].weight + 4) * 32);
	return col;
}