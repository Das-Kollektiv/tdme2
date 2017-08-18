// Generated from /tdme/src/tdme/engine/primitives/Plane.java
#include <tdme/engine/primitives/Plane.h>

#include <tdme/math/Vector3.h>

using tdme::engine::primitives::Plane;
using tdme::math::Vector3;

Plane::Plane() 
{
	normal.set(0.0f, 0.0f, 0.0f);
	distance = 0.0f;
}

Plane::Plane(Vector3* normal, float distance) 
{
	this->normal.set(normal);
	this->distance = distance;
}

float Plane::getDistance()
{
	return distance;
}

void Plane::setDistance(float distance)
{
	this->distance = distance;
}

Vector3* Plane::getNormal()
{
	return &normal;
}
