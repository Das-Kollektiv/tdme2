#include "Vector.h"
#include <cmath>
#include <sstream>

Vector::Vector()
: x(0)
, y(0)
, z(0)
{

}

Vector::Vector(double _x, double _y, double _z)
: x(_x)
, y(_y)
, z(_z)
{
}

double Vector::length() const
{
	return sqrt(x*x + y* y + z*z);
}

bool Vector::operator==(const Vector& rhs) const
{
	if(this->x== rhs.x && this->y == rhs.y && this->z == rhs.z)
	{
		return true;
	}
	return false;
}

bool Vector::operator != (const Vector& rhs) const
{
	if(this->x== rhs.x && this->y == rhs.y && this->z == rhs.z)
	{
		return false;
	}
	return true;
}

bool Vector::operator<=(const Vector& rhs) const
{
	if(this->x <= rhs.x && this->y <= rhs.y && this->z <= rhs.z)
	{
		return true;
	}
	return false;
}

bool Vector::operator>=(const Vector& rhs) const
{
	if(this->x >= rhs.x && this->y >= rhs.y && this->z >= rhs.z)
	{
		return true;
	}
	return false;
}

Vector Vector::cross(const Vector& rhs) const
{
	double vx=this->y * rhs.z - this->z * rhs.y;
	double vy= - (this->x * rhs.z - this->z * rhs.x);
	double vz=this->x * rhs.y - this->y * rhs.x;

	return Vector(vx, vy, vz);
}

double Vector::dot(const Vector& rhs) const
{
	return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
}

double Vector::lengthSq() const
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

Vector Vector::Truncate(double max_value) const
{
	Vector v(x, y, z);
	double len=this->length();
	if(len == 0)
	{
		return v;
	}

	if(len > max_value)
	{
		v.x = x * max_value / len;
		v.y = y * max_value / len;
		v.z = z * max_value / len;
	}

	return v;
}

Vector Vector::normalize() const
{
	double vl = this->length();
	if(vl == 0)
	{
		return Vector();
	}

	double vx = this->x / vl;
	double vy = this->y / vl;
	double vz= this->z / vl;

	return Vector(vx, vy, vz);
}

Vector::Vector(const Vector& rhs)
{
	this->x=rhs.x;
	this->y=rhs.y;
	this->z=rhs.z;
}

Vector& Vector::operator=(const Vector& rhs)
{
	this->x=rhs.x;
	this->y=rhs.y;
	this->z=rhs.z;

	return *this;
}

Vector& Vector::operator+=(const Vector& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;

	return *this;
}

Vector& Vector::operator-=(const Vector& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;

	return *this;
}

Vector& Vector::operator*=(double value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;

	return *this;
}

Vector& Vector::operator/=(double value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;

	return *this;
}

std::string Vector::toString() const
{
	std::ostringstream oss;
	oss << "[" << x << ", " << y << ", " << z << "]";
	return oss.str();
}

Vector operator+(const Vector& v1, const Vector& v2)
{
	Vector v=v1;
	v+=v2;
	return v;
}

Vector operator-(const Vector& v1, const Vector& v2)
{
	Vector v=v1;
	v-=v2;
	return v;
}

Vector operator*(const Vector& v1, double value)
{
	Vector v=v1;
	v*=value;
	return v;
}

Vector operator/(const Vector& v1, double value)
{
	Vector v=v1;
	v/=value;
	return v;
}

Vector operator*(double value, const Vector& v1)
{
	Vector v=v1;
	v*=value;
	return v;
}