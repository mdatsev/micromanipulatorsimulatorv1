#pragma once
#include "Creature.h"
class Generation
{
public:
	int size;
	std::vector<Creature> creatures;
	void GenerateRandom(int min_nodes, int max_nodes, int min_size, int max_size, int min_friction, int max_friction, int min_restitution, int max_restitution, int min_mass, int max_mass, double max_dimension, int min_muscles, int max_muscles);

	Generation(int size);
	~Generation();
};

