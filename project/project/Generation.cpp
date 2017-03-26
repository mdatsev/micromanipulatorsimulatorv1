#include "stdafx.h"
#include "Generation.h"
#include <random>
#include <process.h>
#include "Config.h"


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
		world.creatures.push_back(c);
	}
}

void SimulateGen(void* param)
{
	Generation* gen = (Generation*)param;
	gen->generation_running = true;
	while (gen->generation_running)
	{
		//if (generations_num)
		//{
		//	gen->simulation_running = false;
		//}
		gen->world.time_running = 0;
		HANDLE hThread = gen->world.StartSimulation(one_generation_time);
		WaitForSingleObject(hThread, INFINITE);
		gen->MeasureDistances();
	}
}

void Generation::DoGenerations()
{
	_beginthread(SimulateGen, 0, (void *)this);
}

void Generation::Stop()
{
	generation_running = false;
}

void Generation::MeasureDistances()
{
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