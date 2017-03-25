#include "stdafx.h"
#include "Generation.h"
#include <random>


void Generation::GenerateRandom()
{
	for (int i = 0; i < size; i++)
	{
		Creature c;
		c.CreateRandom();
		if (c.nodes.size() == 0)
		{
			i--;
			continue;
		}
		//c.Mutate();
		creatures.push_back(c);
	}
}

void Generation::MeasureFitness()
{
	for (Creature& c : creatures)
	{
		c.fitness = c.AveragePosition().x;
		world.AddCreature(c);

	}
	HANDLE hThread = world.StartSimulation(15);
	WaitForSingleObject(world.hThread, INFINITE);
	for (Creature& c : creatures)
	{
		c.fitness = c.AveragePosition().x - c.fitness;
	}
}

void Generation::KillAndBreed()
{
	
}

Generation::Generation(int size) : size(size)
{
	
}


Generation::~Generation()
{
}