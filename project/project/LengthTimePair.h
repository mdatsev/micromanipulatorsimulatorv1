#pragma once
class LengthTimePair
{
public:
	double length;
	double time;
	LengthTimePair(double length_multiplier, double time) : length(length_multiplier), time(time)
	{
	}

	~LengthTimePair()
	{
	}
};

