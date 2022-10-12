#ifndef _H__VECTOR_H
#define _H__VECTOR_H

#include <string>

class Vector
{
public:
	double x;
	double y;
	double z;

public:
	Vector();
	Vector(double _x, double _y, double _z);
	Vector(const Vector& rhs);
	Vector& operator=(const Vector& rhs);

public:
	Vector cross(const Vector& rhs) const;
	Vector normalize() const;
	double dot(const Vector& rhs) const;
	double lengthSq() const;

public:
	Vector Truncate(double max_value) const;

public:
	Vector& operator-=(const Vector& rhs);
	Vector& operator+=(const Vector& rhs);
	Vector& operator*=(double value);
	Vector& operator/=(double value);

public:
	bool operator <=(const Vector& rhs) const;
	bool operator >=(const Vector& rhs) const;
	bool operator ==(const Vector& rhs) const;
	bool operator !=(const Vector& rhs) const;

public:
	void reset() { x=0; y=0; z=0; }

public:
	std::string toString() const;

public:
	double length() const;
};

Vector operator+(const Vector& v1, const Vector& v2);
Vector operator-(const Vector& v1, const Vector& v2);
Vector operator*(const Vector& v1, double value);
Vector operator*(double value, const Vector& v1);
Vector operator/(const Vector& v1, double value);

#endif