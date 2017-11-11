#include <tdme/engine/primitives/SphereInternal.h>

#include <tdme/math/Vector3.h>

using tdme::engine::primitives::SphereInternal;
using tdme::math::Vector3;

SphereInternal::SphereInternal(const Vector3& center, float radius)
{
	this->center.set(center);
	this->radius = radius;
}

float SphereInternal::getRadius() const
{
	return radius;
}

void SphereInternal::setRadius(float radius)
{
	this->radius = radius;
}
