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
	void CreateRandom();
	void CheckOverlap(Node& node, int overlapDistance);
	Vec2 AverageDistance();
};

