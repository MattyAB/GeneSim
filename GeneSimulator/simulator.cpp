#include "simulator.h"

#include <stdexcept>

Simulator::Simulator(Population & population, Render & render) : pop(population), render(render)
{

}

void Simulator::Simulate(int rounds, bool torender)
{
	for (int i = 0; i < rounds; i++)
	{
		pop.Tick();
		if (torender)
		{
			render.DrawFrame({ pop.GetFrameData() });
		}
	}
}

std::vector<Individual> Simulator::GetSurvivors(int survivalcondition)
{
	std::vector<Individual> output = std::vector<Individual>();
	if (survivalcondition == 0)
	{
		for (int i = 0; i < _populationsize_; i++)
		{
			Individual indiv = pop.GetIndiv(i);
			if (indiv.x > (_boardsize_ / 2))
			{
				output.push_back(indiv);
			}
		}
	}
	else if (survivalcondition == 1)
	{
		for (int i = 0; i < _populationsize_; i++)
		{
			Individual indiv = pop.GetIndiv(i);
			if (indiv.x < (_boardsize_ / 2) && indiv.y < (_boardsize_ / 2))
			{
				output.push_back(indiv);
			}
		}
	}
	else
	{
		throw std::invalid_argument("No such survivalcondition");
	}
	return output;
}