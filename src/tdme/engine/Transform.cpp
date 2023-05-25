#include <tdme/engine/Transform.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>

using std::to_string;

using tdme::engine::model::RotationOrder;
using tdme::engine::Rotation;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;

void Transform::fromMatrix(const Matrix4x4& matrix, RotationOrder* rotationOrder) {
	matrix.getScale(scale);
	matrix.getTranslation(translation);
	auto eulerAngles = matrix.computeEulerAngles();
	rotations.clear();
	rotations.emplace_back(rotationOrder->getAxis0(), eulerAngles[rotationOrder->getAxis0VectorIndex()]);
	rotations.emplace_back(rotationOrder->getAxis1(), eulerAngles[rotationOrder->getAxis1VectorIndex()]);
	rotations.emplace_back(rotationOrder->getAxis2(), eulerAngles[rotationOrder->getAxis2VectorIndex()]);
	update();
}

void Transform::update()
{
	// matrices
	Matrix4x4 translationMatrix;
	Matrix4x4 scaleMatrix;

	// transform matrix identity
	transformMatrix.identity();
	// set up translation matrix
	translationMatrix.identity().translate(translation);
	// set up scale matrix
	scaleMatrix.identity().scale(scale);
	// create and multiply rotations
	rotationsQuaternion.identity();
	for (auto& rotation: rotations) {
		rotation.update();
		rotationsQuaternion.multiply(rotation.getQuaternion());
	}
	rotationsQuaternion.normalize();
	// apply to transform matrix
	transformMatrix.multiply(scaleMatrix);
	transformMatrix.multiply(rotationsQuaternion.computeMatrix());
	transformMatrix.multiply(translationMatrix);
}

Transform& Transform::invert() {
	//
	fromMatrix(transformMatrix.clone().invert(), RotationOrder::ZYX);
	//
	return *this;
}
