#include "CatmullRom.h"
#include <iostream>

CatmullRom::CatmullRom()
: Curve()
{

}

CatmullRom::~CatmullRom()
{
}

void CatmullRom::_on_way_point_added()
{
	if(_way_points.size() < 4)
	{
		return;
	}

	int new_control_point_index=_way_points.size() - 1;
	int pt=new_control_point_index - 2;
	for(int i=0; i<=_steps; i++)
	{
		double u=(double)i / (double)_steps;

		add_node(interpolate(u, _way_points[pt-1], _way_points[pt], _way_points[pt+1], _way_points[pt+2]));
	}
}

Vector CatmullRom::interpolate(double u, const Vector& P0, const Vector& P1, const Vector& P2, const Vector& P3)
{
	Vector point;
	point=u*u*u*((-1) * P0 + 3 * P1 - 3 * P2 + P3) / 2;
	point+=u*u*(2*P0 - 5 * P1+ 4 * P2 - P3) / 2;
	point+=u*((-1) * P0 + P2) / 2;
	point+=P1;

	return point;
}

