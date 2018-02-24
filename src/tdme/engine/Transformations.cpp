#include <tdme/engine/Transformations.h>

#include <string>

#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>

using std::to_string;

using tdme::engine::Transformations;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utils::Console;

Transformations::Transformations() 
{
	transformationsMatrix.identity();
	scale.set(1.0f, 1.0f, 1.0f);
}

Transformations::~Transformations() {
}

Vector3& Transformations::getTranslation()
{
	return translation;
}

Vector3& Transformations::getScale()
{
	return scale;
}

Vector3& Transformations::getPivot()
{
	return pivot;
}

Rotations* Transformations::getRotations()
{
	return &rotations;
}

const Matrix4x4& Transformations::getTransformationsMatrix() const
{
	return transformationsMatrix;
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
	for (auto rotation: transformations.rotations.rotations) {
		// do we have a rotation to reuse?
		auto _rotation = rotationIdx < rotations.size() ? rotations.get(rotationIdx) : nullptr;
		//	nope?
		if (_rotation == nullptr) {
			// add it
			_rotation = new Rotation();
			rotations.add(_rotation);
		}
		// copy
		_rotation->fromRotation(rotation);
		// next
		rotationIdx++;
	}
	// remove unused rotations
	while (rotationIdx < rotations.size()) {
		rotations.remove(rotations.size() - 1);
	}
	// copy matrices and such
	transformationsMatrix.set(transformations.transformationsMatrix);
	rotations.quaternion.set(transformations.rotations.quaternion);
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
	rotations.update();
	// apply rotations
	rotationsMatrix.identity();
	//	pivot
	rotationsMatrix.translate(pivot.clone().scale(-1.0f));
	//	rotatations
	rotations.quaternion.computeMatrix(rotationsQuaternionMatrix);
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
	for (auto rotation: rotations.rotations) {
		rotation->setAngle(rotation->getAngle() - 180.0f);
	}
	update();
}
