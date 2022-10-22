#include "BSpline.h"
#include <iostream>

BSpline::BSpline()
: Curve()
{

}

BSpline::~BSpline()
{
}

void BSpline::_on_way_point_added()
{
	if(_way_points.size() < 4)
	{
		return;
	}

	int new_control_point_index=static_cast<int>(_way_points.size()) - 1;

	int pt=new_control_point_index - 3;

	for(int i=0; i<=_steps; i++)
	{
		float u=(float)i / (float)_steps;

		add_node(interpolate(u, _way_points[pt], _way_points[pt+1], _way_points[pt+2], _way_points[pt+3]));
	}
}

Vector BSpline::interpolate(float u, const Vector& P0, const Vector& P1, const Vector& P2, const Vector& P3)
{
	Vector point;
	point=u*u*u*((-1) * P0 + 3 * P1 - 3 * P2 + P3) / 6;
	point+=u*u*(3*P0 - 6 * P1+ 3 * P2) / 6;
	point+=u*((-3) * P0 + 3 * P2) / 6;
	point+=(P0+4*P1+P2) / 6;

	return point;
}

