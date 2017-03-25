#pragma once
#include <vector>
#include "Creature.h"

class World
{
public:
	std::vector<Creature> creatures;
	double time_running = 0;
	bool simulation_running;
	Ground* ground;
	double flat_ground_y;
	World();
	~World();
	HANDLE StartSimulation(double time);
	void StopSimulation();
	void AddCreature(Creature);
	void Clear();
	void Draw(HDC hdc, RECT rect, double scale, Vec2 center, bool debug = false);
	void Integrate(double dt);
};