#include "Bezier.h"
#include <iostream>

Bezier::Bezier()
: Curve()
{

}

Bezier::~Bezier()
{
}

void Bezier::_on_way_point_added()
{
	if(_way_points.size() < 4)
	{
		return;
	}

	int new_control_point_index=_way_points.size() - 1;

	if(new_control_point_index == 3)
	{
		for(int i=0; i<=_steps; i++)
		{
			float u=(float)i / (float)_steps;

			add_node(interpolate(u, _way_points[0], _way_points[1], _way_points[2], _way_points[3]));
		}
	}
	else
	{
		if(new_control_point_index % 2 == 0)
		{
			return;
		}
		
		int pt=new_control_point_index - 2;
		for(int i=0; i<=_steps; i++)
		{
			float u=(float)i / (float)_steps;
			Vector point4=2 * _way_points[pt] - _way_points[pt-1];

			add_node(interpolate(u, _way_points[pt], point4, _way_points[pt+1], _way_points[pt+2]));
		}
	}
}

Vector Bezier::interpolate(float u, const Vector& P0, const Vector& P1, const Vector& P2, const Vector& P3)
{
	Vector point;
	point=u*u*u*((-1) * P0 + 3 * P1 - 3 * P2 + P3);
	point+=u*u*(3*P0 - 6 * P1+ 3 * P2);
	point+=u*((-3) * P0 + 3 * P1);
	point+=P0;

	return point;
}

