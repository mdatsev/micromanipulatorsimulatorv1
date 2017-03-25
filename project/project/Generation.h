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
	void MeasureFitness();
	Generation(int size);
	~Generation();
};