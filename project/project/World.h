#pragma once
#include <vector>
#include "Creature.h"

class World
{
	std::vector<Creature> creatures;
public:
	double time_running = 0;
	double delta_time = 0.001;
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