#include "stdafx.h"
#include "Muscle.h"


Muscle::Muscle(int connectionID1, int connectionID2, double stiffness, double target_length) :
	node1_ID(connectionID1), node2_ID(connectionID2), stiffness(stiffness), rest_target_length(target_length)
{
}


Muscle::~Muscle()
{
}

double Muscle::target_length()
{
	return length_cycle.size() ? rest_target_length * length_cycle[cycle_stage].length : rest_target_length;
}
