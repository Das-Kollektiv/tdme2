#include <tdme/engine/primitives/Sphere.h>

#include <vector>

#include <ext/reactphysics3d/src/collision/shapes/SphereShape.h>

#include <tdme/math/Math.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Vector3.h>

using std::to_string;
using std::vector;

using tdme::engine::primitives::Sphere;
using tdme::math::Math;
using tdme::math::MathTools;
using tdme::math::Vector3;

Sphere::Sphere() 
{
	collisionShape = new reactphysics3d::SphereShape(radius);
}

Sphere::Sphere(const Vector3& center, float radius)
{
	this->center.set(center);
	this->radius = radius;
	collisionShapeLocalTranslation.set(center);
	collisionShapeLocalTransform.setPosition(reactphysics3d::Vector3(collisionShapeLocalTranslation.getX(), collisionShapeLocalTranslation.getY(), collisionShapeLocalTranslation.getZ()));
	collisionShape = new reactphysics3d::SphereShape(
		Math::max(MathTools::EPSILON, radius)
	);
	// compute bounding box
	computeBoundingBox();
}

float Sphere::getRadius() const
{
	return radius;
}

BoundingVolume* Sphere::clone() const
{
	return new Sphere(center, radius);
}

