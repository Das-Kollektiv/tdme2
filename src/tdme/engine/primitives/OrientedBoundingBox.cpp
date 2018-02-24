#include <tdme/engine/primitives/OrientedBoundingBox.h>

#include <array>
#include <vector>

#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::array;
using std::vector;

using tdme::engine::primitives::OrientedBoundingBox;
using tdme::math::Math;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::Triangle;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

const array<int32_t, 3> OrientedBoundingBox::FACE0_INDICES = {{ 0, 4, 7 }};
const array<int32_t, 3> OrientedBoundingBox::FACE1_INDICES = {{ 7, 3, 0 }};
const array<int32_t, 3> OrientedBoundingBox::FACE2_INDICES = {{ 6, 5, 1 }};
const array<int32_t, 3> OrientedBoundingBox::FACE3_INDICES = {{ 1, 2, 6 }};
const array<int32_t, 3> OrientedBoundingBox::FACE4_INDICES = {{ 5, 4, 0 }};
const array<int32_t, 3> OrientedBoundingBox::FACE5_INDICES = {{ 0, 1, 5 }};
const array<int32_t, 3> OrientedBoundingBox::FACE6_INDICES = {{ 3, 7, 6 }};
const array<int32_t, 3> OrientedBoundingBox::FACE7_INDICES = {{ 6, 2, 3 }};
const array<int32_t, 3> OrientedBoundingBox::FACE8_INDICES = {{ 2, 1, 0 }};
const array<int32_t, 3> OrientedBoundingBox::FACE9_INDICES = {{ 0, 3, 2 }};
const array<int32_t, 3> OrientedBoundingBox::FACE10_INDICES = {{ 4, 5, 6 }};
const array<int32_t, 3> OrientedBoundingBox::FACE11_INDICES = {{ 6, 7, 4 }};
const array<array<int32_t,3>,12> OrientedBoundingBox::facesVerticesIndexes =
{{
	FACE0_INDICES, FACE1_INDICES, FACE2_INDICES, FACE3_INDICES,
	FACE4_INDICES, FACE5_INDICES, FACE6_INDICES, FACE7_INDICES,
	FACE8_INDICES, FACE9_INDICES, FACE10_INDICES, FACE11_INDICES
}};

const Vector3 OrientedBoundingBox::AABB_AXIS_X(1.0f, 0.0f, 0.0f);
const Vector3 OrientedBoundingBox::AABB_AXIS_Y(0.0f, 1.0f, 0.0f);
const Vector3 OrientedBoundingBox::AABB_AXIS_Z(0.0f, 0.0f, 1.0f);

OrientedBoundingBox::OrientedBoundingBox(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension)
{
	this->center.set(center);
	this->axes[0].set(axis0);
	this->axes[1].set(axis1);
	this->axes[2].set(axis2);
	this->halfExtension.set(halfExtension);
	this->vertices.resize(8);
	update();
}

OrientedBoundingBox::OrientedBoundingBox(BoundingBox* bb)
{
	this->halfExtension.set(bb->getMax()).sub(bb->getMin()).scale(0.5f);
	this->center.set(bb->getMin()).add(halfExtension);
	this->axes[0].set(AABB_AXIS_X);
	this->axes[1].set(AABB_AXIS_Y);
	this->axes[2].set(AABB_AXIS_Z);
	this->vertices.resize(8);
	update();
}

OrientedBoundingBox::OrientedBoundingBox() 
{
	this->center.set(0.0f, 0.0f, 0.0f);
	this->axes[0].set(AABB_AXIS_X);
	this->axes[1].set(AABB_AXIS_Y);
	this->axes[2].set(AABB_AXIS_Z);
	this->halfExtension.set(0.0f, 0.0f, 0.0f);
	this->vertices.resize(8);
	update();
}

const array<Vector3, 3>* OrientedBoundingBox::getAxes() const
{
	return &axes;
}

Vector3& OrientedBoundingBox::getHalfExtension()
{
	return halfExtension;
}

void OrientedBoundingBox::fromBoundingBox(BoundingBox* bb)
{
	this->halfExtension.set(bb->getMax()).sub(bb->getMin()).scale(0.5f);
	this->center.set(bb->getMin()).add(halfExtension);
	this->axes[0].set(AABB_AXIS_X);
	this->axes[1].set(AABB_AXIS_Y);
	this->axes[2].set(AABB_AXIS_Z);
	update();
}

void OrientedBoundingBox::fromOrientedBoundingBox(OrientedBoundingBox* obb)
{
	this->halfExtension.set(obb->halfExtension);
	this->center.set(obb->center);
	this->axes[0].set(obb->axes[0]);
	this->axes[1].set(obb->axes[1]);
	this->axes[2].set(obb->axes[2]);
	update();
}

void OrientedBoundingBox::fromBoundingVolume(BoundingVolume* original)
{
	// check for same type of original
	if (dynamic_cast< OrientedBoundingBox* >(original) != nullptr == false) {
		return;
	}
	auto obb = dynamic_cast< OrientedBoundingBox* >(original);
	center.set(obb->center);
	for (auto i = 0; i < axes.size(); i++)
		axes[i].set(obb->axes[i]);

	halfExtension.set(obb->halfExtension);
	for (auto i = 0; i < vertices.size(); i++)
		vertices[i].set(obb->vertices[i]);

}

void OrientedBoundingBox::fromBoundingVolumeWithTransformations(BoundingVolume* original, const Transformations& transformations)
{
	// check for same type of original
	if (dynamic_cast< OrientedBoundingBox* >(original) != nullptr == false) {
		return;
	}
	array<Vector3, 3> axisTransformed;
	Vector3 scale;
	auto obb = dynamic_cast< OrientedBoundingBox* >(original);
	auto& transformationsMatrix = transformations.getTransformationsMatrix();
	// apply rotation, scale, translation
	transformationsMatrix.multiply(obb->center, center);
	// apply transformations rotation + scale to axis
	transformationsMatrix.multiplyNoTranslation(obb->axes[0], axisTransformed[0]);
	transformationsMatrix.multiplyNoTranslation(obb->axes[1], axisTransformed[1]);
	transformationsMatrix.multiplyNoTranslation(obb->axes[2], axisTransformed[2]);
	// set up axes
	axes[0].set(axisTransformed[0]).normalize();
	axes[1].set(axisTransformed[1]).normalize();
	axes[2].set(axisTransformed[2]).normalize();
	// apply scale to half extension
	halfExtension.set(obb->halfExtension);
	halfExtension.scale(
		scale.set(
			axisTransformed[0].computeLength(),
			axisTransformed[1].computeLength(),
			axisTransformed[2].computeLength()
		)
	);
	// compute vertices
	update();
}

void OrientedBoundingBox::update()
{
	Vector3 axis;
	auto& halfExtensionXYZ = halfExtension.getArray();
	// just for my imagination
	//	near left top
	vertices[0].set(center);
	vertices[0].add(axis.set(axes[0]).scale(-halfExtensionXYZ[0]));
	vertices[0].add(axis.set(axes[1]).scale(-halfExtensionXYZ[1]));
	vertices[0].add(axis.set(axes[2]).scale(-halfExtensionXYZ[2]));
	// just for my imagination
	//	near right top
	vertices[1].set(center);
	vertices[1].add(axis.set(axes[0]).scale(+halfExtensionXYZ[0]));
	vertices[1].add(axis.set(axes[1]).scale(-halfExtensionXYZ[1]));
	vertices[1].add(axis.set(axes[2]).scale(-halfExtensionXYZ[2]));
	// just for my imagination
	//	near right bottom
	vertices[2].set(center);
	vertices[2].add(axis.set(axes[0]).scale(+halfExtensionXYZ[0]));
	vertices[2].add(axis.set(axes[1]).scale(+halfExtensionXYZ[1]));
	vertices[2].add(axis.set(axes[2]).scale(-halfExtensionXYZ[2]));
	// just for my imagination
	//	near left bottom
	vertices[3].set(center);
	vertices[3].add(axis.set(axes[0]).scale(-halfExtensionXYZ[0]));
	vertices[3].add(axis.set(axes[1]).scale(+halfExtensionXYZ[1]));
	vertices[3].add(axis.set(axes[2]).scale(-halfExtensionXYZ[2]));
	// just for my imagination
	//	far left top
	vertices[4].set(center);
	vertices[4].add(axis.set(axes[0]).scale(-halfExtensionXYZ[0]));
	vertices[4].add(axis.set(axes[1]).scale(-halfExtensionXYZ[1]));
	vertices[4].add(axis.set(axes[2]).scale(+halfExtensionXYZ[2]));
	// just for my imagination
	//	far right top
	vertices[5].set(center);
	vertices[5].add(axis.set(axes[0]).scale(+halfExtensionXYZ[0]));
	vertices[5].add(axis.set(axes[1]).scale(-halfExtensionXYZ[1]));
	vertices[5].add(axis.set(axes[2]).scale(+halfExtensionXYZ[2]));
	// just for my imagination
	//	far right bottom
	vertices[6].set(center);
	vertices[6].add(axis.set(axes[0]).scale(+halfExtensionXYZ[0]));
	vertices[6].add(axis.set(axes[1]).scale(+halfExtensionXYZ[1]));
	vertices[6].add(axis.set(axes[2]).scale(+halfExtensionXYZ[2]));
	// just for my imagination
	//	far left bottom
	vertices[7].set(center);
	vertices[7].add(axis.set(axes[0]).scale(-halfExtensionXYZ[0]));
	vertices[7].add(axis.set(axes[1]).scale(+halfExtensionXYZ[1]));
	vertices[7].add(axis.set(axes[2]).scale(+halfExtensionXYZ[2]));
	// sphere radius
	sphereRadius = halfExtension.computeLength();
}

void OrientedBoundingBox::computeClosestPointOnBoundingVolume(const Vector3& point, Vector3& closestPoint) const
{
	Vector3 direction;
	Vector3 tmp;
	direction.set(point).sub(center);
	closestPoint.set(center);
	auto& halfExtensionXYZ = halfExtension.getArray();
	for (auto i = 0; i < axes.size(); i++) {
		auto distance = Vector3::computeDotProduct(direction, axes[i]);
		if (distance > halfExtensionXYZ[i]) distance = halfExtensionXYZ[i];
		if (distance < -halfExtensionXYZ[i]) distance = -halfExtensionXYZ[i];
		closestPoint.add(tmp.set(axes[i]).scale(distance));
	}
}

void OrientedBoundingBox::computeNearestPointOnFaceBoundingVolume(const Vector3& pointInObb, Vector3& pointOnFace) const
{
	Vector3 direction;
	direction.set(pointInObb).sub(center);
	auto& halfExtensionXYZ = halfExtension.getArray();
	auto axisMinPenetration = 10000.0f;
	auto axisIdxLeastPenetration = 0;
	// detemine axis with min penetration
	for (auto i = 0; i < axes.size(); i++) {
		auto distance = Vector3::computeDotProduct(direction, axes[i]);
		if (distance > halfExtensionXYZ[i]) distance = halfExtensionXYZ[i];
		if (distance < -halfExtensionXYZ[i]) distance = -halfExtensionXYZ[i];

		float penetration;
		if (distance >= 0.0f) {
			penetration = halfExtensionXYZ[i] - distance;
		} else {
			penetration = halfExtensionXYZ[i] + distance;
		}
		// determine axis with min penetration
		if (penetration < axisMinPenetration) {
			axisMinPenetration = penetration;
			axisIdxLeastPenetration = i;
		}
	}
	//
	computeNearestPointOnFaceBoundingVolumeAxis(axisIdxLeastPenetration, pointInObb, pointOnFace);
}

void OrientedBoundingBox::computeNearestPointOnFaceBoundingVolumeAxis(int32_t axisIdx, const Vector3& pointInObb, Vector3& pointOnFace) const
{
	Vector3 direction;
	Vector3 tmp;
	direction.set(pointInObb).sub(center);
	auto halfExtensionXYZ = halfExtension.getArray();
	// compute point on obb face
	pointOnFace.set(center);
	for (auto i = 0; i < axes.size(); i++) {
		auto distance = Vector3::computeDotProduct(direction, axes[i]);
		if (distance > halfExtensionXYZ[i]) distance = halfExtensionXYZ[i];
		if (distance < -halfExtensionXYZ[i]) distance = -halfExtensionXYZ[i];
		if (i == axisIdx) {
			if (distance >= 0.0f) {
				pointOnFace.add(tmp.set(axes[i]).scale(+halfExtensionXYZ[i]));
			} else {
				pointOnFace.add(tmp.set(axes[i]).scale(-halfExtensionXYZ[i]));
			}
		} else {
			pointOnFace.add(tmp.set(axes[i]).scale(distance));
		}
	}
}

void OrientedBoundingBox::computeOppositePointOnFaceBoundingVolume(const Vector3& pointInObb, Vector3& pointOnFace) const
{
	Vector3 direction;
	direction.set(pointInObb).sub(center);
	auto halfExtensionXYZ = halfExtension.getArray();
	auto axisMinPenetration = 10000.0f;
	auto axisIdxLeastPenetration = 0;
	// detemine axis with min penetration
	for (auto i = 0; i < axes.size(); i++) {
		auto distance = Vector3::computeDotProduct(direction, axes[i]);
		if (distance > halfExtensionXYZ[i]) distance = halfExtensionXYZ[i];
		if (distance < -halfExtensionXYZ[i]) distance = -halfExtensionXYZ[i];
		float penetration;
		if (distance >= 0.0f) {
			penetration = halfExtensionXYZ[i] - distance;
		} else {
			penetration = halfExtensionXYZ[i] + distance;
		}
		// determine axis with min penetration
		if (penetration < axisMinPenetration) {
			axisMinPenetration = penetration;
			axisIdxLeastPenetration = i;
		}
	}
	computeOppositePointOnFaceBoundingVolumeAxis(axisIdxLeastPenetration, pointInObb, pointOnFace);
}

void OrientedBoundingBox::computeOppositePointOnFaceBoundingVolumeAxis(int32_t axisIdx, const Vector3& pointInObb, Vector3& pointOnFace) const
{
	Vector3 direction;
	Vector3 tmp;
	direction.set(pointInObb).sub(center);
	auto& halfExtensionXYZ = halfExtension.getArray();
	// compute point on obb face
	pointOnFace.set(center);
	for (auto i = 0; i < axes.size(); i++) {
		auto distance = Vector3::computeDotProduct(direction, axes[i]);
		if (distance > halfExtensionXYZ[i]) distance = halfExtensionXYZ[i];
		if (distance < -halfExtensionXYZ[i]) distance = -halfExtensionXYZ[i];
		if (i == axisIdx) {
			if (distance >= 0.0f) {
				pointOnFace.add(tmp.set(axes[i]).scale(-halfExtensionXYZ[i]));
			} else {
				pointOnFace.add(tmp.set(axes[i]).scale(+halfExtensionXYZ[i]));
			}
		} else {
			pointOnFace.add(tmp.set(axes[i]).scale(distance));
		}
	}
}

bool OrientedBoundingBox::containsPoint(const Vector3& point) const
{
	Vector3 direction;
	direction.set(point).sub(center);
	auto halfExtensionXYZ = halfExtension.getArray();
	for (auto i = 0; i < axes.size(); i++) {
		auto distance = Vector3::computeDotProduct(direction, axes[i]);
		if (distance > 0.0f) distance += -Math::EPSILON;
		if (distance < 0.0f) distance += +Math::EPSILON;
		if (distance > halfExtensionXYZ[i]) return false;
		if (distance < -halfExtensionXYZ[i]) return false;
	}
	return true;
}

bool OrientedBoundingBox::doesCollideWith(BoundingVolume* bv2, const Vector3& movement, CollisionResponse* collision)
{
	if (dynamic_cast< BoundingBox* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< BoundingBox* >(bv2), movement, collision);
	} else
	if (dynamic_cast< OrientedBoundingBox* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< OrientedBoundingBox* >(bv2), movement, collision);
	} else
	if (dynamic_cast< Sphere* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< Sphere* >(bv2), movement, collision);
	} else
	if (dynamic_cast< Capsule* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< Capsule* >(bv2), movement, collision);
	} else
	if (dynamic_cast< Triangle* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< Triangle* >(bv2), movement, collision);
	} else
	if (dynamic_cast< ConvexMesh* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< ConvexMesh* >(bv2), movement, collision);
	} else {
		return false;
	}
}

float OrientedBoundingBox::computeDimensionOnAxis(const Vector3& axis) const
{
	auto vertexOnAxis = Vector3::computeDotProduct(vertices[0], axis);
	auto min = vertexOnAxis;
	auto max = vertexOnAxis;
	for (auto i = 1; i < vertices.size(); i++) {
		vertexOnAxis = Vector3::computeDotProduct(vertices[i], axis);
		if (vertexOnAxis < min) min = vertexOnAxis;
		if (vertexOnAxis > max) max = vertexOnAxis;
	}
	return Math::abs(max - min);
}

BoundingVolume* OrientedBoundingBox::clone() const
{
	return new OrientedBoundingBox(
		center,
		axes[0],
		axes[1],
		axes[2],
		halfExtension
	);
}
