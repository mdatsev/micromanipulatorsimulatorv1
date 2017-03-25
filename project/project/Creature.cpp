#include "stdafx.h"
#include "Creature.h"
#include <random>
#include "Config.h"



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
void Creature::RemoveNode(int index)
{
	nodes.erase(nodes.begin() + index);
	for (Muscle& m : muscles)
	{
		if (m.node1_ID > index) m.node1_ID--;
		if (m.node2_ID > index) m.node2_ID--;
	}
}

void Creature::AddMuscle(Muscle m)
{
	muscles.push_back(m);
}

void Creature::CreateRandom()
{
	int overlapDistance = 5;
	nodes.clear();
	muscles.clear();
	std::uniform_int_distribution<int> distI(min_nodes, max_nodes);
	std::uniform_real_distribution<double> distD(0, 1);

	//todo
	int number_of_nodes = distI(gen);

	distI = std::uniform_int_distribution<int>(min_muscles, max_muscles);
	int number_of_muscles = distI(gen);
	double nodeX, nodeY;
	double size, friction, restitution, mass;
	double target_length, stiffness;

	int nodeId1, nodeId2;

	for (int i = 0; i < number_of_nodes; i++)
	{
		distD = std::uniform_real_distribution<double>(min_size, max_size);
		size = distD(gen);
		distD = std::uniform_real_distribution<double>(0, max_dimension - size);
		nodeX = distD(gen);
		nodeY = distD(gen);
		distD = std::uniform_real_distribution<double>(min_friction, max_friction);
		friction = distD(gen);
		distD = std::uniform_real_distribution<double>(min_restitution, max_friction);
		restitution = distD(gen);
		distD = std::uniform_real_distribution<double>(min_mass, max_mass);
		mass = distD(gen);
		AddNode(Node(Vec2(nodeX, nodeY), size, friction, restitution, mass, true));
	}
	for (Node& n : nodes)
	{
		CheckOverlap(n, overlapDistance);
	}
	for (int j = 0; j < number_of_muscles; j++)
	{
		bool isValid = true;
		distI = std::uniform_int_distribution<int>(0, number_of_nodes - 1);
		if (number_of_nodes == 2)
		{
			nodeId1 = 0;
			nodeId2 = 1;
		}
		else {
			nodeId1 = distI(gen);
			nodeId2 = distI(gen);
		}
		if (nodeId1 == nodeId2)
		{
			continue;
		}
		for (Muscle& m : muscles)
		{
			if ((nodeId1 == m.node1_ID && nodeId2 == m.node2_ID)
				|| (nodeId1 == m.node2_ID && nodeId2 == m.node1_ID))
			{
				isValid = false;
				//todo na tam po kusno da triq node
			}
		}
		if (!isValid) continue;
		distD = std::uniform_real_distribution<double>(min_stiffness, max_stiffness);
		stiffness = distD(gen);
		distD = std::uniform_real_distribution<double>(min_targetL, max_targetL);
		target_length = distD(gen);
		AddMuscle(Muscle(nodeId1, nodeId2, stiffness, target_length));

	}
	RemoveALoneNode();
	distI = std::uniform_int_distribution<int>(min_cycles, max_cycles);
	int number_of_cycles = distI(gen);
	for (Muscle& m : muscles)
	{
		for (int i = 0; i < number_of_cycles; i++)
		{
			distD = std::uniform_real_distribution<double>(min_length_multiplier, max_length_multiplier);
			double length_multiplier = distD(gen);
			distD = std::uniform_real_distribution<double>(min_phase_time, max_phase_time);
			double phase_time = distD(gen);
			m.length_cycle.push_back(LengthTimePair(length_multiplier, phase_time));
		}
		
	}
	
}

void Creature::Mutate()
{
	std::uniform_int_distribution<int> distI(0, 1);
	std::uniform_real_distribution<double> distD(0, 1);
	double chance = distD(gen);
	int number_of_nodes;
	int number_of_muscles;
	if (chance < large_mutation_chance)
	{
		int add_or_delete = distI(gen);  // add 1. remove 0
		int node_or_muscle = distI(gen); // node 1. muscle 0
		if (add_or_delete)
		{
			if (node_or_muscle) 
			{
				distI = std::uniform_int_distribution<int>(0, max_dimension);
				int nodeX = distI(gen);
				int nodeY = distI(gen);
				distD = std::uniform_real_distribution<double>(min_size, max_size);
				double size = distD(gen);
				distD = std::uniform_real_distribution<double>(min_friction, max_friction);
				double friction = distD(gen);
				distD = std::uniform_real_distribution<double>(min_restitution, max_friction);
				double restitution = distD(gen);
				distD = std::uniform_real_distribution<double>(min_mass, max_mass);
				double mass = distD(gen);
				AddNode(Node(Vec2(nodeX, nodeY), size, friction, restitution, mass, true));
				distI = std::uniform_int_distribution<int>(1, nodes.size() - 1);
				number_of_nodes = distI(gen);
				for (int i = 0; i < number_of_nodes - 1; i++)
				{
					distD = std::uniform_real_distribution<double>(min_stiffness, max_stiffness);
					double stiffness = distD(gen);
					distD = std::uniform_real_distribution<double>(min_targetL, max_targetL);
					double target_length = distD(gen);
					AddMuscle(Muscle(nodes.size() - 1, i, stiffness, target_length));
				}
			}
			else {
				bool isValid = true;
				distI = std::uniform_int_distribution<int>(0, nodes.size() - 1);
				int nodeId1 = distI(gen);
				int nodeId2 = distI(gen);
				if (nodeId1 != nodeId2)
				{
					for (Muscle& m : muscles)
					{
						if ((nodeId1 == m.node1_ID && nodeId2 == m.node2_ID)
							|| (nodeId1 == m.node2_ID && nodeId2 == m.node1_ID))
						{
							isValid = false;
						}
					}
					if (isValid)
					{
						distD = std::uniform_real_distribution<double>(min_stiffness, max_stiffness);
						double stiffness = distD(gen);
						distD = std::uniform_real_distribution<double>(min_targetL, max_targetL);
						double target_length = distD(gen);
						AddMuscle(Muscle(nodeId1, nodeId2, stiffness, target_length));
					}
				}
				
			}
			
		}
		else {
			distI = std::uniform_int_distribution<int>(0, nodes.size());
			int i = distI(gen);
			RemoveNode(i);
			int j = 0;
			for (Muscle& m : muscles)
			{
				if (m.node1_ID == i || m.node2_ID == i)
				{
					muscles.erase(muscles.begin() + j);
				}
				j++;
			}
			RemoveALoneNode();
		}
	}
	distI = std::uniform_int_distribution<int>(1, nodes.size());
	number_of_nodes = distI(gen);
	for (int i = 0; i < number_of_nodes; i++)
	{
		distD = std::uniform_real_distribution<double>(0, 1);
		chance = distD(gen);
		if (chance < mutation_chance)
		{
			double size_deviation = nodes[i].size / max_deviation;
			distD = std::uniform_real_distribution<double>(nodes[i].size - size_deviation, nodes[i].size + size_deviation);
			nodes[i].size = distD(gen);
			
		}
		distD = std::uniform_real_distribution<double>(0, 1);
		chance = distD(gen);
		if (chance < mutation_chance)
		{
			double friction_deviation = nodes[i].friction / max_deviation;
			distD = std::uniform_real_distribution<double>(nodes[i].friction - friction_deviation, nodes[i].friction + friction_deviation);
			nodes[i].friction = distD(gen);
		}
		distD = std::uniform_real_distribution<double>(0, 1);
		chance = distD(gen);
		if (chance < mutation_chance)
		{
			double restitution_deviation = nodes[i].restitution / max_deviation;
			distD = std::uniform_real_distribution<double>(nodes[i].restitution - restitution_deviation, nodes[i].restitution + restitution_deviation);
			nodes[i].restitution = distD(gen);
		}
		distD = std::uniform_real_distribution<double>(0, 1);
		chance = distD(gen);
		if (chance < mutation_chance)
		{
			double mass_deviation = nodes[i].mass / max_deviation;
			distD = std::uniform_real_distribution<double>(nodes[i].mass - mass_deviation, nodes[i].mass + mass_deviation);
			nodes[i].mass = distD(gen);
		}
	}
	distI = std::uniform_int_distribution<int>(min_nodes, max_nodes);
	number_of_muscles = distI(gen);
	for (int i = 0; i < number_of_muscles; i++)
	{
		distD = std::uniform_real_distribution<double>(0, 1);
		chance = distD(gen);
		if (chance < mutation_chance)
		{
			//double stiffness_deviation = muscles[i].stiffness / max_deviation;
			//distD = std::uniform_real_distribution<double>(muscles[i].stiffness - stiffness_deviation, muscles[i].stiffness + stiffness_deviation);
			//muscles[i].stiffness = distD(gen);
		}
		distD = std::uniform_real_distribution<double>(0, 1);
		chance = distD(gen);
		if (chance < mutation_chance)
		{
			//double targetL_deviation = muscles[i].rest_target_length/ max_deviation;
			//distD = std::uniform_real_distribution<double>(muscles[i].rest_target_length - targetL_deviation, muscles[i].rest_target_length + targetL_deviation);
			//muscles[i].rest_target_length = distD(gen);
		}
	}
}

void Creature::RemoveALoneNode()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		bool isValid = false;
		for (Muscle& m : muscles)
		{
			if (i == m.node1_ID || i == m.node2_ID)
			{
				isValid = true;
			}
		}
		if (!isValid)
		{
			RemoveNode(i);
			i--;
		}
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
			node.pos.x += 1;
			node.pos.y += 1;
		}
	}
}

Vec2 Creature::AveragePosition()
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
