#pragma once
#include "Vec2.h"
#include <vector>
class Ground
{
public:
	double height;
	double friction;
	std::vector<Vec2> points;
	Ground(double height, double friction);
	void AddPoint(Vec2);
	~Ground();
};

