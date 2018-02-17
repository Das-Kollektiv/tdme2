#include <tdme/engine/Transformations.h>

#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>

using tdme::engine::Transformations;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;

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

Matrix4x4& Transformations::getTransformationsMatrix()
{
	return transformationsMatrix;
}

void Transformations::fromTransformations(Transformations* transformations)
{
	// translation
	translation.set(transformations->translation);
	// scale
	scale.set(transformations->scale);
	// pivot
	pivot.set(transformations->pivot);
	// rotations
	auto rotationIdx = 0;
	for (; rotationIdx < transformations->rotations.size(); rotationIdx++) {
		auto rotation = transformations->rotations.get(rotationIdx);
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
	}
	// remove unused rotations
	while (rotationIdx < rotations.size()) {
		rotations.remove(rotations.size() - 1);
	}
	// copy matrices and such
	transformationsMatrix.set(transformations->transformationsMatrix);
	rotations.quaternion.set(transformations->rotations.quaternion);
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
