#pragma once
class LengthTimePair
{
public:
	double length;
	double time;
	LengthTimePair(double force, double time) : length(force), time(time)
	{
	}

	~LengthTimePair()
	{
	}
};

