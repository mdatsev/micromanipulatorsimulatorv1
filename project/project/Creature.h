#pragma once
#include "Node.h"
#include "Muscle.h"
#include <vector>

class Creature
{
public:
	std::vector<Node> nodes;
	std::vector<Muscle> muscles;
	Creature();
	~Creature();
	void AddNode(Node);
	void AddMuscle(Muscle);
	void CreateRandom(int min_nodes, int max_nodes, int min_size, int max_size, int min_friction, int max_friction, int min_restitution, int max_restitution, int min_mass, int max_mass, double max_dimension, int min_muscles, int max_muscles);
	void CheckOverlap(Node& node, int overlapDistance);
	Vec2 AverageDistance();
};

