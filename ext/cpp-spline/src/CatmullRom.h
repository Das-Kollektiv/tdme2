#ifndef _H__CATMULL_ROM_H
#define _H__CATMULL_ROM_H

#include "Curve.h"

class CatmullRom : public Curve
{
public:
	CatmullRom();
	virtual ~CatmullRom();

protected:
	virtual void _on_way_point_added();

protected:
	Vector interpolate(double u, const Vector& P0, const Vector& P1, const Vector& P2, const Vector& P3);
};

#endif