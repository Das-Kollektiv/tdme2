#include <tdme/engine/primitives/Capsule.h>

#include <vector>

#include <ext/reactphysics3d/src/collision/shapes/CapsuleShape.h>

#include <tdme/math/Math.h>
#include <tdme/math/MathTools.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::primitives::Capsule;

using tdme::math::Math;
using tdme::math::MathTools;
using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Capsule::Capsule(const Vector3& a, const Vector3& b, float radius)
{
	this->a.set(a);
	this->b.set(b);
	this->radius = radius;

	// determine local translation
	Vector3 center;
	center.set(this->a).add(this->b).scale(0.5f);
	collisionShapeLocalTransform.setPosition(reactphysics3d::Vector3(center.getX(), center.getY(), center.getZ()));

	// determine local rotation
	Vector3 yAxis(0.0f, 1.0f, 0.0f);
	Vector3 abNormalized = a.clone().sub(b).normalize();
	auto& abNormalizedVectorXYZ = abNormalized.getArray();
	Vector3 rotationAxis;
	if (Math::abs(abNormalizedVectorXYZ[0]) < MathTools::EPSILON && Math::abs(abNormalizedVectorXYZ[2]) < MathTools::EPSILON) {
		rotationAxis.set(abNormalizedVectorXYZ[1], 0.0f, 0.0f);
	} else {
		Vector3::computeCrossProduct(yAxis, abNormalized, rotationAxis).normalize();
	}
	auto angle = Vector3::computeAngle(yAxis, abNormalized, yAxis);
	Quaternion rotationQuaternion;
	rotationQuaternion.rotate(angle, rotationAxis);
	collisionShapeLocalTransform.setOrientation(
		reactphysics3d::Quaternion(
			rotationQuaternion.getX(),
			rotationQuaternion.getY(),
			rotationQuaternion.getZ(),
			rotationQuaternion.getW()
		)
	);

	// rotate a,b that a and b live on y axis
	Quaternion inverseRotationQuaternion;
	inverseRotationQuaternion.rotate(-angle, rotationAxis);
	Vector3 aTransformed;
	Vector3 bTransformed;
	inverseRotationQuaternion.multiply(this->a, aTransformed);
	inverseRotationQuaternion.multiply(this->b, bTransformed);

	// create capsule
	collisionShape = new reactphysics3d::CapsuleShape(
		Math::max(0.1f, radius),
		Math::max(0.1f, bTransformed.clone().sub(aTransformed).scale(0.5f).computeLength() + radius * 2.0f)
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
