#include "stdafx.h"
#include "World.h"
#include <process.h>
#include "Config.h"

World::World()
{
}


World::~World()
{
}

void Simulate(void* param)
{
	World* world = (World*)param;
	world->simulation_running = true;
	while (world->simulation_running)
	{
		world->Integrate(delta_time);
	}
}

void World::StartSimulation()
{
	_beginthread(Simulate, 0, this);
}

void World::StopSimulation()
{
	simulation_running = false;
}

void World::AddCreature(Creature n)
{
	creatures.push_back(n);
}

void World::Clear()
{
	creatures.clear();
}

void World::Draw(HDC hdc, RECT rect, double scale, Vec2 center, bool debug)
{
	Vec2 top_left_point = Vec2(
		center.x - (rect.right * scale - rect.left * scale) / 2,
		center.y - (rect.bottom * scale - rect.top * scale) / 2);
	double xoff = -top_left_point.x;
	double yoff = -top_left_point.y;
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hBmp = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	SelectObject(hMemDc, hBmp);
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hMemDc, &rect, hBrush);
	HPEN redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN greenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN bluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	HPEN cyanPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	HBRUSH solidBrush = CreateSolidBrush(RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hMemDc, hBrush);
	for(Creature& c : creatures)
	{
		MoveToEx(hMemDc, World::ground->points[0].x * scale + xoff, World::ground->points[0].y * scale + yoff, NULL); //fixme drawing the same point twice
		for (Vec2& point : World::ground->points)
		{
			LineTo(hMemDc, point.x * scale + xoff, point.y * scale + yoff);
		}

		for (Node& n : c.nodes)
		{
			int color = n.friction * 255;
			if (color > 255)
				color = 255;
			color = 255 - color;
			HBRUSH brush = CreateSolidBrush(RGB(color, color, color));
			SelectObject(hMemDc, brush);
			DeleteObject(brush);
			Ellipse(hMemDc, 
				n.pos.x * scale - n.size * scale + xoff, 
				n.pos.y * scale - n.size * scale + yoff,
				n.pos.x * scale + n.size * scale + xoff, 
				n.pos.y * scale + n.size * scale + yoff);
		}

		for (Muscle& n : c.muscles)
		{
			double x1 = c.nodes[n.node1_ID].pos.x * scale + xoff;
			double y1 = c.nodes[n.node1_ID].pos.y * scale + yoff;
			double x2 = c.nodes[n.node2_ID].pos.x * scale + xoff;
			double y2 = c.nodes[n.node2_ID].pos.y * scale + yoff;
			MoveToEx(hMemDc, x1, y1, NULL);
			LineTo(hMemDc, x2, y2);
		}
	}

	if (debug)
	{
		for (Creature& c : creatures)
		{
			/*
			for (Node& n : c.nodes)
			{
				//draw velocity			
				MoveToEx(hMemDc, n.pos.x, n.pos.y, NULL);
				LineTo(hMemDc, n.pos.x + n.vel.x * 60, n.pos.y + n.vel.y * 60);

				//draw acceleration
				SelectObject(hMemDc, redPen);
				MoveToEx(hMemDc, n.pos.x, n.pos.y, NULL);
				LineTo(hMemDc, n.pos.x + n.acc.x * 3600, n.pos.y + n.acc.y * 3600);

				//draw forces
				SelectObject(hMemDc, bluePen);
				TCHAR buffer[80];
				SetTextColor(hMemDc, RGB(0, 0, 255));
				SetBkMode(hMemDc, TRANSPARENT);
				_stprintf_s(buffer, _T("x:%f"), n.pos.x);
				TextOut(hMemDc, n.pos.x, n.pos.y, buffer, _tcslen(buffer));
				MoveToEx(hMemDc, n.pos.x, n.pos.y, NULL);
				LineTo(hMemDc, n.pos.x + n.forces.x * 60, n.pos.y + n.forces.y * 60);

				SelectObject(hMemDc, cyanPen);
				_stprintf_s(buffer, _T("creatures:%d"), creatures.size());
				TextOut(hMemDc, 0, 0, buffer, _tcslen(buffer));

				//MoveToEx(hMemDc, n.pos.x, n.pos.y, NULL);
				//LineTo(hMemDc, n.pos.x + n.debug_vec2.x, n.pos.y + n.debug_vec2.y);
			}
			*/
			SelectObject(hMemDc, solidBrush);	
			Ellipse(hMemDc, 
				c.AveragePosition().x * scale - 2 + xoff,
				c.AveragePosition().y * scale - 2 + yoff,
				c.AveragePosition().x * scale + 2 + xoff,
				c.AveragePosition().y * scale + 2 + yoff);
		}
	}

	BitBlt(hdc, rect.left, rect.top, rect.right, rect.bottom, hMemDc, 0, 0, SRCCOPY);

	SelectObject(hMemDc, hOldPen);
	DeleteObject(solidBrush);
	DeleteObject(greenPen);
	DeleteObject(redPen);
	DeleteObject(bluePen);
	DeleteObject(cyanPen);
	DeleteObject(hBrush);
	DeleteObject(hBmp);
	DeleteDC(hMemDc);
}

void World::Integrate(double dt)
{
	for(Creature& c : creatures)
	{
		for (Node& n : c.nodes) 
		{
			n.forces = n.gravityForce;
		}

		for (Muscle& m : c.muscles)
		{
			Vec2 force_direction1 = c.nodes[m.node2_ID].pos - c.nodes[m.node1_ID].pos;
			force_direction1.Normalize();
			Vec2 force_direction2 = c.nodes[m.node1_ID].pos - c.nodes[m.node2_ID].pos;
			force_direction2.Normalize();
			double length = c.nodes[m.node1_ID].pos.Distance(c.nodes[m.node2_ID].pos);
			double displacement = length - m.target_length();
			if (m.length_cycle.size())
			{
				if (m.cycle_time > m.length_cycle[m.cycle_stage].time)
				{
					if (m.cycle_stage >= m.length_cycle.size() - 1)
					{
						m.cycle_stage = 0;
					}
					else
					{
						m.cycle_stage++;
					}
					m.cycle_time = 0;
				}
			}
			m.cycle_time += dt;
#if 0
			double forceMag = (1 - (m.target_length() / length)) *  m.stiffness;
			c.nodes[m.node1_ID].forces += force_direction1 * forceMag;
			c.nodes[m.node2_ID].forces += force_direction2 * forceMag;
#else
			double forceMag = m.stiffness * displacement;
			c.nodes[m.node1_ID].forces += force_direction1 * forceMag;
			c.nodes[m.node2_ID].forces += force_direction2 * forceMag;
#endif
		}


		for (Node& n : c.nodes)
		{
			n.CollideWithGround(ground, dt);
			//n.CollideFlat(500);
			n.forces -= n.vel * n.size * n.airFriction;
			n.acc = n.forces / n.mass;
			n.vel += n.acc * dt;
			n.pos += n.vel * dt;
		}
		time_running += dt;
	}
}
