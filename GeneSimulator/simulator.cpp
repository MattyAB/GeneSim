#include "simulator.h"

Simulator::Simulator(Population & population, Render & render) : pop(population), render(render)
{

}

void Simulator::Simulate(int rounds)
{
	for (int i = 0; i < rounds; i++)
	{
		pop.Tick();
		render.DrawFrame({ pop.GetFrameData() });
	}
}