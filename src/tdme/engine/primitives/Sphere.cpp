#include <tdme/engine/primitives/Sphere.h>

#include <ext/reactphysics3d/src/collision/shapes/SphereShape.h>

#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>

using std::to_string;

using tdme::engine::primitives::Sphere;
using tdme::math::Math;
using tdme::math::Vector3;

Sphere::Sphere()
{
	collisionShape = new reactphysics3d::SphereShape(radius);
	radius = Math::EPSILON;
}

Sphere::Sphere(const Vector3& center, float radius, const Vector3& scale)
{
	this->center.set(center);
	this->radius = radius;
	setScale(scale);
}

float Sphere::getRadius() const
{
	return radius;
}

void Sphere::setScale(const Vector3& scale) {
	// store new scale
	this->scale.set(scale);

	// remove old collision shape
	if (collisionShape != nullptr) delete collisionShape;

	collisionShapeLocalTranslation.set(center).scale(scale);
	collisionShapeLocalTransform.setPosition(reactphysics3d::Vector3(collisionShapeLocalTranslation.getX(), collisionShapeLocalTranslation.getY(), collisionShapeLocalTranslation.getZ()));
	collisionShape = new reactphysics3d::SphereShape(
		Math::max(Math::EPSILON, radius * Math::max(Math::abs(scale.getZ()), Math::max(Math::abs(scale.getX()), Math::abs(scale.getY()))))
	);
	// compute bounding box
	computeBoundingBox();
}

BoundingVolume* Sphere::clone() const
{
	return new Sphere(center, radius, scale);
}

