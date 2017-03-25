#pragma once
#include <algorithm>
#include <math.h>

class Vec2
{
public:
	double x;
	double y;
	Vec2(double x, double y) : x(x), y(y)
	{
	}

	Vec2() : x(0), y(0)
	{
	}

	~Vec2()
	{
	}

	void operator+=(const Vec2 &v) {
		x += v.x;
		y += v.y;
	}

	void operator*=(const double &right) {
		x *= right;
		y *= right;
	}

	void operator-=(const Vec2 &v) {
		x -= v.x;
		y -= v.y;
	}

	Vec2 operator+(const Vec2 &right) {
		return Vec2(x + right.x, y + right.y);
	}

	Vec2 operator-(const Vec2 & right)
	{
		return Vec2(x - right.x, y - right.y);

	}

	Vec2 operator*(const double &right) const 
	{
		return Vec2(x * right, y * right);
	}

	Vec2 operator/(const double &right) {
		return Vec2(x / right, y / right);
	}

	Vec2 operator-() {
		return Vec2(-x, -y);
	}

	double Magnitude() const
	{
		return sqrt(x * x + y * y);
	}


	double MagnitudeSq() const
	{
		return x * x + y * y;
	}


	void Normalize()
	{
		double length = Magnitude();
		if (length != 0) {
			x = x / length;
			y = y / length;
		}
	}

	Vec2 Normalized()
	{
		Vec2 result;
		double length = Magnitude();
		if (length != 0) {
			result.x = x / length;
			result.y = y / length;
		}
		return result;
	}

	double Distance(const Vec2& v2)
	{
		return sqrt(pow((v2.x - x), 2) + pow((v2.y - y), 2));
	}

	double DistanceSq(const Vec2& v2)
	{
		return pow((v2.x - x), 2) + pow((v2.y - y), 2);
	}

	double Dot(const Vec2& v2) const
	{
		return x*v2.x + y*v2.y;
	}

	Vec2 ProjectOnto(const Vec2& v2)
	{
		return v2 * (Dot(v2)) / (v2.MagnitudeSq());
	}
};

