#pragma once
#include "Creature.h"
#include "World.h"
class Generation
{
public:
	int size;
	bool generation_running;
	std::vector<Creature> creatures;
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