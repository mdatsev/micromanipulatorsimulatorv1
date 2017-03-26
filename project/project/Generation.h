#pragma once
#include "Creature.h"
#include "World.h"
class Generation
{
public:
	int size;
	std::vector<Creature> creatures;
	World world;
	void GenerateRandom();
	void Simulate(int time);
	void MeasureDistances();
	void KillAndBreed();
	void RemoveCreature(int index);
	Generation(int size);
	~Generation();
};