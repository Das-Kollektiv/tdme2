#ifndef _H__VECTOR_H
#define _H__VECTOR_H

#include <string>

class Vector
{
public:
	float x;
	float y;
	float z;

public:
	Vector();
	Vector(float _x, float _y, float _z);
	Vector(const Vector& rhs);
	Vector& operator=(const Vector& rhs);

public:
	Vector cross(const Vector& rhs) const;
	Vector normalize() const;
	float dot(const Vector& rhs) const;
	float lengthSq() const;

public:
	Vector Truncate(float max_value) const;

public:
	Vector& operator-=(const Vector& rhs);
	Vector& operator+=(const Vector& rhs);
	Vector& operator*=(float value);
	Vector& operator/=(float value);

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
	float length() const;
};

Vector operator+(const Vector& v1, const Vector& v2);
Vector operator-(const Vector& v1, const Vector& v2);
Vector operator*(const Vector& v1, float value);
Vector operator*(float value, const Vector& v1);
Vector operator/(const Vector& v1, float value);

#endif
