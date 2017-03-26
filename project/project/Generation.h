#pragma once
#include "Creature.h"
#include "World.h"
class Generation
{
public:
	int size;
	int number;
	bool generation_running;
	World world;
	void GenerateRandom();
	void DoGenerations();
	void Stop();
	void MeasureDistances();
	void KillAndBreed();
	void RemoveCreature(int index);
	Generation(int size);
	~Generation();
};