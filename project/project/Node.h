#pragma once
#include "Vec2.h"
#include "Ground.h"
#include <vector>
#include <map>
class Node
{
	double oldTime = 0;
public:
	int debug_collides;
	Vec2 debug_vec2;
	Vec2 gravityForce;
	double size;
	double friction;
	double airFriction = 0.3;
	double mass;
	double restitution;
	Vec2 pos;
	Vec2 vel;
	Vec2 acc;
	Vec2 forces;
	Node(Vec2 pos, double size, double friction, double restitution, double mass = 1, bool gravity = true);
	~Node();
	void CollideWithGround(Ground*, double dt);
};

