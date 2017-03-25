#include "stdafx.h"
#include "Generation.h"


void Generation::GenerateRandom()
{
	for (int i = 0; i < size; i++)
	{
		Creature c;
//		c.CreateRandom;
		creatures.push_back(c);
	}
}

void Generation::MeasureFitness()
{
	for (Creature& c : creatures)
	{
		world.AddCreature(c);
	}
}

Generation::Generation(int size) : size(size)
{
	
}


Generation::~Generation()
{
}
