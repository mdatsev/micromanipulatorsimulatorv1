#include "stdafx.h"
#include "Creature.h"
#include <random>



Creature::Creature()
{
}


Creature::~Creature()
{
}

void Creature::AddNode(Node n)
{
	nodes.push_back(n);
}

void Creature::AddMuscle(Muscle m)
{
	muscles.push_back(m);
}

void Creature::CreateRandom(int min_nodes, int max_nodes, int min_size, int max_size, int min_friction, int max_friction, int min_restitution, int max_restitution , int min_mass, int max_mass, double max_dimension, int min_muscles, int max_muscles)
{
	int seed = 24424234;
	int overlapDistance = 5;
	nodes.clear();
	muscles.clear();
	std::mt19937 gen(seed);
	std::uniform_int_distribution<int> dist(min_nodes, max_nodes);

	//todo
	int number_of_nodes = dist(gen);
	int nodeX, nodeY, size, friction, restitution, mass;

	for (int i = 0; i < number_of_nodes; i++)
	{
		dist = std::uniform_int_distribution<int>(0, max_dimension);
		nodeX = dist(gen);
		nodeY = dist(gen);
		dist = std::uniform_int_distribution<int>(min_size, max_size);
		size = dist(gen);
		dist = std::uniform_int_distribution<int>(min_friction, max_friction);
		friction = dist(gen);
		dist = std::uniform_int_distribution<int>(min_restitution, max_friction);
		restitution = dist(gen);
		dist = std::uniform_int_distribution<int>(min_mass, max_mass);
		mass = dist(gen);

		AddNode(Node(Vec2(nodeX, nodeY), size, friction, restitution, mass, true));
	}

	
}

void Creature::CheckOverlap(Node& node, int overlapDistance)
{
	for (Node& n : nodes)
	{
		#define left (n.pos.x - overlapDistance)
		#define right (n.pos.x + overlapDistance)
		#define top (n.pos.y - overlapDistance)
		#define bottom (n.pos.y + overlapDistance)
		if (left > node.pos.x + overlapDistance
			|| right < node.pos.x - overlapDistance
			|| top > node.pos.y + overlapDistance
			|| bottom < node.pos.y - overlapDistance)
		{
			
		}
	}
}

Vec2 Creature::AverageDistance()
{
	double avgX = 0;
	double avgY = 0;
	for (Node& n : nodes)
	{
		avgX += n.pos.x;
		avgY += n.pos.y;
	}
	int n = nodes.size();
	return Vec2(avgX / n, avgY / n);
}
