#ifndef _H__BSPLINE_H
#define _H__BSPLINE_H

#include "Curve.h"

class BSpline : public Curve
{
public:
	BSpline();
	virtual ~BSpline();

protected:
	virtual void _on_way_point_added();

protected:
	Vector interpolate(double u, const Vector& P0, const Vector& P1, const Vector& P2, const Vector& P3);
};

#endif