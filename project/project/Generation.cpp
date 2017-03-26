#include "stdafx.h"
#include "Generation.h"
#include <random>
#include <algorithm>
#include "Config.h"
#include <process.h>
#include <mutex>
	
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
		gen->KillAndBreed();
		gen->world.generation_number++;
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
	for (Creature& c : world.creatures)
	{
		c.fitness = c.AveragePosition().x - c.fitness;
	}
}

void Generation::KillAndBreed()
{	
	world.g_num_mutex.lock();

	std::sort(world.creatures.begin(), world.creatures.end(), [](const Creature& lhs, const Creature& rhs) { return lhs.fitness > rhs.fitness; });
	std::uniform_int_distribution<int> distI(0, 1);
	/*
	int i = 0;
	int j = 0;
	while (i <= world.creatures.size() / 2)
	{
		distI = std::uniform_int_distribution<int>(1, generation_size - 1);
		int chance = distI(gen);
		if (j < chance)
		{
			RemoveCreature(j);
			i++;
		}
		j++;
	}
	*/
	world.creatures.erase(world.creatures.begin() + generation_size / 2, world.creatures.end());
	auto old_count = world.creatures.size();
	world.creatures.resize(2 * old_count);
	std::copy_n(world.creatures.begin(), old_count, world.creatures.begin() + old_count);
	for (Creature& c : world.creatures)
	{
		c.Mutate();
	}
	world.g_num_mutex.unlock();
}

void Generation::RemoveCreature(int index)
{
	world.creatures.erase(world.creatures.begin() + index);
}

Generation::Generation(int size) : size(size)
{
	
}


Generation::~Generation()
{
}