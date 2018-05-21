#include <tdme/engine/primitives/Capsule.h>

#include <string>
#include <vector>

#include <ext/reactphysics3d/src/collision/shapes/CapsuleShape.h>

#include <tdme/math/Math.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::to_string;

using tdme::engine::primitives::Capsule;

using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Capsule::Capsule(const Vector3& a, const Vector3& b, float radius)
{
	// TODO: order seem to matter, investigate!
	this->a.set(a);
	this->b.set(b);
	this->radius = radius;
	center.set(a).add(b).scale(0.5f);

	// determine local rotation around Y axis
	Vector3 yAxis(0.0f, -1.0f, 0.0f);
	Vector3 abNormalized = a.clone().sub(b).normalize();
	auto& abNormalizedVectorXYZ = abNormalized.getArray();
	Vector3 rotationAxis;
	if (Math::abs(abNormalizedVectorXYZ[0]) < Math::EPSILON && Math::abs(abNormalizedVectorXYZ[2]) < Math::EPSILON) {
		rotationAxis.set(abNormalizedVectorXYZ[1], 0.0f, 0.0f);
	} else {
		Vector3::computeCrossProduct(yAxis, abNormalized, rotationAxis).normalize();
	}
	auto angle = Vector3::computeAngle(yAxis, abNormalized, yAxis);
	Quaternion rotationQuaternion;
	rotationQuaternion.rotate(angle, rotationAxis);

	// set shape orientation
	collisionShapeLocalTransform.setOrientation(
		reactphysics3d::Quaternion(
			rotationQuaternion.getX(),
			rotationQuaternion.getY(),
			rotationQuaternion.getZ(),
			rotationQuaternion.getW()
		)
	);

	// rotate a,b that a and b live on y axis
	Vector3 aTransformed;
	Vector3 bTransformed;
	rotationQuaternion.multiply(this->a, aTransformed);
	rotationQuaternion.multiply(this->b, bTransformed);

	// determine local translation
	collisionShapeLocalTranslation.set(aTransformed).add(bTransformed).scale(0.5f);
	collisionShapeLocalTransform.setPosition(
		reactphysics3d::Vector3(
			collisionShapeLocalTranslation.getX(),
			collisionShapeLocalTranslation.getY(),
			collisionShapeLocalTranslation.getZ()
		)
	);

	// create capsule
	collisionShape = new reactphysics3d::CapsuleShape(
		Math::max(Math::EPSILON, radius),
		Math::max(Math::EPSILON, bTransformed.clone().sub(aTransformed).computeLength())
	);

	// compute bounding box
	computeBoundingBox();
}

float Capsule::getRadius() const
{
	return radius;
}

const Vector3& Capsule::getA() const
{
	return a;
}

const Vector3& Capsule::getB() const
{
	return b;
}

BoundingVolume* Capsule::clone() const
{
	return new Capsule(a, b, radius);
}
