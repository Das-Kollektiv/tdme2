#include <tdme/engine/Transformations.h>

#include <string>

#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>

using std::to_string;

using tdme::engine::Rotation;
using tdme::engine::Transformations;
using tdme::engine::model::RotationOrder;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;

Transformations::Transformations() 
{
	transformationsMatrix.identity();
	scale.set(1.0f, 1.0f, 1.0f);
	rotationsQuaternion.identity();
}

Transformations::~Transformations() {
}

void Transformations::fromTransformations(const Transformations& transformations)
{
	if (this == &transformations) return;

	// translation
	translation.set(transformations.translation);
	// scale
	scale.set(transformations.scale);
	// pivot
	pivot.set(transformations.pivot);
	// rotations
	auto rotationIdx = 0;
	for (auto rotation: transformations.rotations) {
		// do we have a rotation to reuse?
		if (rotationIdx == rotations.size()) {
			// nope, add a rotation
			rotations.push_back(Rotation(0.0f, Vector3(0.0f, 0.0f, 0.0f)));
		}		// copy
		rotations[rotations.size() - 1].fromRotation(rotation);
		// next
		rotationIdx++;
	}
	// remove unused rotations
	while (rotationIdx < rotations.size()) {
		removeRotation(rotations.size() - 1);
	}
	// copy matrices and such
	transformationsMatrix.set(transformations.transformationsMatrix);
	rotationsQuaternion.set(transformations.rotationsQuaternion);
}

void Transformations::fromMatrix(const Matrix4x4& matrix, RotationOrder* rotationOrder) {
	Vector3 eulerAngles;
	matrix.getScale(scale);
	matrix.getTranslation(translation);
	matrix.computeEulerAngles(eulerAngles);
	rotations.clear();
	rotations.push_back(Rotation(eulerAngles[rotationOrder->getAxis0VectorIndex()], rotationOrder->getAxis0()));
	rotations.push_back(Rotation(eulerAngles[rotationOrder->getAxis1VectorIndex()], rotationOrder->getAxis1()));
	rotations.push_back(Rotation(eulerAngles[rotationOrder->getAxis2VectorIndex()], rotationOrder->getAxis2()));
	update();
}

void Transformations::update()
{
	// matrices
	Matrix4x4 translationMatrix;
	Matrix4x4 scaleMatrix;
	Matrix4x4 rotationsMatrix;
	Matrix4x4 rotationsQuaternionMatrix;
	Matrix4x4 rotationsTranslationsMatrix;

	// transformation matrix identity
	transformationsMatrix.identity();
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
	// apply rotations
	rotationsMatrix.identity();
	//	pivot
	rotationsMatrix.translate(pivot.clone().scale(-1.0f));
	//	rotations
	rotationsQuaternion.computeMatrix(rotationsQuaternionMatrix);
	rotationsMatrix.multiply(rotationsQuaternionMatrix);
	//	pivot
	rotationsTranslationsMatrix.identity().translate(pivot);
	rotationsMatrix.multiply(rotationsTranslationsMatrix);
	// apply to transformation matrix
	transformationsMatrix.multiply(scaleMatrix);
	transformationsMatrix.multiply(rotationsMatrix);
	transformationsMatrix.multiply(translationMatrix);
}

void Transformations::invert() {
	translation.scale(-1.0f);
	scale.setX(1.0f / scale.getX());
	scale.setY(1.0f / scale.getY());
	scale.setZ(1.0f / scale.getZ());
	for (auto& rotation: rotations) {
		rotation.setAngle(rotation.getAngle() - 180.0f);
	}
	update();
}
