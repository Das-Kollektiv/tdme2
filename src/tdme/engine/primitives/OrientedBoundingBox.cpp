#include <tdme/engine/primitives/OrientedBoundingBox.h>

#include <array>
#include <vector>

#include <ext/reactphysics3d/src/collision/shapes/BoxShape.h>

#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>

using std::array;

using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Math;
using tdme::math::Vector3;
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
	setScale(Vector3(1.0f, 1.0f, 1.0f));
}

OrientedBoundingBox::OrientedBoundingBox(BoundingBox* bb)
{
	this->halfExtension.set(bb->getMax()).sub(bb->getMin()).scale(0.5f);
	this->center.set(bb->getMin()).add(halfExtension);
	this->axes[0].set(AABB_AXIS_X);
	this->axes[1].set(AABB_AXIS_Y);
	this->axes[2].set(AABB_AXIS_Z);
	setScale(Vector3(1.0f, 1.0f, 1.0f));
}

OrientedBoundingBox::OrientedBoundingBox() 
{
	this->center.set(0.0f, 0.0f, 0.0f);
	this->axes[0].set(AABB_AXIS_X);
	this->axes[1].set(AABB_AXIS_Y);
	this->axes[2].set(AABB_AXIS_Z);
	this->halfExtension.set(0.0f, 0.0f, 0.0f);
	setScale(Vector3(1.0f, 1.0f, 1.0f));
}

const array<Vector3, 8> OrientedBoundingBox::getVertices() const {
	array<Vector3, 8> vertices;
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
	//
	return vertices;
}

/**
 * @return faces vertices indexes
 */
const array<array<int32_t,3>,12>& OrientedBoundingBox::getFacesVerticesIndexes() {
	return facesVerticesIndexes;
}

const array<Vector3, 3>* OrientedBoundingBox::getAxes() const
{
	return &axes;
}

const Vector3& OrientedBoundingBox::getHalfExtension() const
{
	return halfExtension;
}

bool OrientedBoundingBox::setScale(const Vector3& scale) {
	if (this->scale.equals(scale) == false) {
		// store new scale
		this->scale.set(scale);

		// remove old collision shape
		if (collisionShape != nullptr) delete collisionShape;

		//
		collisionShapeLocalTranslation.set(center).scale(scale);
		collisionShapeLocalTransform.setPosition(reactphysics3d::Vector3(collisionShapeLocalTranslation.getX(), collisionShapeLocalTranslation.getY(), collisionShapeLocalTranslation.getZ()));
		collisionShapeLocalTransform.setOrientation(
			reactphysics3d::Quaternion(
				reactphysics3d::Matrix3x3(
					this->axes[0].getX(),
					this->axes[0].getY(),
					this->axes[0].getZ(),
					this->axes[1].getX(),
					this->axes[1].getY(),
					this->axes[1].getZ(),
					this->axes[2].getX(),
					this->axes[2].getY(),
					this->axes[2].getZ()
				)
			)
		);
		collisionShape = new reactphysics3d::BoxShape(
			reactphysics3d::Vector3(
				Math::max(Math::EPSILON, halfExtension.getX() * scale.getX()),
				Math::max(Math::EPSILON, halfExtension.getY() * scale.getY()),
				Math::max(Math::EPSILON, halfExtension.getZ() * scale.getZ())
			)
		);
		// compute bounding box
		computeBoundingBox();
		//
		return true;
	}

	//
	return false;
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
