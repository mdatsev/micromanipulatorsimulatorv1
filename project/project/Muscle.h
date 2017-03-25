#pragma once
#include "LengthTimePair.h"
#include <vector>
class Muscle
{
public:
	std::vector<LengthTimePair> length_cycle;
	double cycle_time = 0;
	int cycle_stage = 0;
	double rest_target_length;
	double stiffness;
	int node1_ID;
	int node2_ID;
	Muscle(int connectionID1, int connectionID2, double stiffness, double target_length);
	~Muscle();
	double target_length();
};

