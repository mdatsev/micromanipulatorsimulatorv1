#pragma once
#include <vector>
#include "Creature.h"

class World
{
	std::vector<Creature> creatures;
public:
	bool simulation_running;
	Ground* ground;
	double flat_ground_y;
	World();
	~World();
	void StartSimulation();
	void StopSimulation();
	void AddCreature(Creature);
	void Clear();
	void Draw(HDC, RECT, bool = false);
	void Integrate(double dt);
};