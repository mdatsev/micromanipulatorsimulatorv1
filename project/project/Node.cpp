#include "stdafx.h"
#include "Node.h"
#include "World.h"
#include "Config.h"
#include <ctime>

Node::Node(Vec2 pos, double size, double friction, double restitution, double mass, bool gravity) :
	pos(pos), size(size), friction(friction), restitution(restitution), mass(mass), gravityForce(gravity ? Vec2(0, gravity_constant * mass) : Vec2(0, 0))
{
}

Node::~Node()
{
}

void Node::CollideWithGround(Ground* ground, double dt)
{
	debug_collides = -1;
	for (int i = 0; i < ground->points.size() - 1; i++)
	{
		Vec2& p1 = ground->points[i];
		Vec2& p2 = ground->points[i + 1];

		//check if in bounding box
#define left (p1.x <= p2.x ? p1.x : p2.x)
#define right (p1.x > p2.x ? p1.x : p2.x)
#define top (p1.y <= p2.y ? p1.y : p2.y)
#define bottom (p1.y > p2.y ? p1.y : p2.y)
		if (left > pos.x + size
			|| right < pos.x - size
			|| top > pos.y + size
			|| bottom < pos.y - size)
		{
			continue;
		}

		Vec2 ground_seg = p2 - p1;

		double part = std::fmax(0, std::fmin(1, (pos - p1).Dot(ground_seg) / ground_seg.MagnitudeSq()));
		Vec2 closest_point =  p1 + ground_seg * part;

		double d = pos.DistanceSq(closest_point);
		if (d <= size * size)
		{
			if (debug_collides == -1)
			{
				debug_collides = i;
			}
			Vec2 direction = pos - closest_point;
			//check side
			if (direction.Dot(vel) < 0 && ground_seg.y*vel.x < ground_seg.x*vel.y)
			{
				Vec2 impact = forces + (vel * (mass / dt));
				Vec2 parallel = impact.ProjectOnto(ground_seg);
				Vec2 perpendicular = (impact - parallel);
				Vec2 mirror = parallel - perpendicular;
				parallel = parallel.MagnitudeSq() < perpendicular.MagnitudeSq() * friction * friction ? Vec2(0, 0) : parallel - parallel.Normalized() * perpendicular.Magnitude() * friction;
				Vec2 mirror_perpendicular =  mirror - mirror.ProjectOnto(ground_seg);
				forces += parallel + mirror_perpendicular * restitution  - impact;
				pos = closest_point + direction.Normalized() * size;
			}
		}
	}
}