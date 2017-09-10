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
	translationMatrix.identity();
	scale.set(1.0f, 1.0f, 1.0f);
	scaleMatrix.identity();
	rotationsQuaternionMatrix.identity();
	rotationsMatrix.identity();
	rotationsTranslationsMatrix.identity();
}

Vector3* Transformations::getTranslation()
{
	return &translation;
}

Vector3* Transformations::getScale()
{
	return &scale;
}

Vector3* Transformations::getPivot()
{
	return &pivot;
}

Rotations* Transformations::getRotations()
{
	return &rotations;
}

Matrix4x4* Transformations::getTransformationsMatrix()
{
	return &transformationsMatrix;
}

void Transformations::fromTransformations(Transformations* transformations)
{
	translation.set(&transformations->translation);
	scale.set(&transformations->scale);
	pivot.set(&transformations->pivot);
	auto rotationIdx = 0;
	for (; rotationIdx < transformations->rotations.size(); rotationIdx++) {
		auto rotation = transformations->rotations.get(rotationIdx);
		auto _rotation = rotationIdx < rotations.size() ? rotations.get(rotationIdx) : static_cast< Rotation* >(nullptr);
		if (_rotation == nullptr) {
			_rotation = new Rotation();
			rotations.add(_rotation);
		}
		_rotation->fromRotation(rotation);
	}
	while (rotationIdx < rotations.size()) {
		rotations.remove(rotations.size() - 1);
	}
	translationMatrix.set(&transformations->translationMatrix);
	scaleMatrix.set(&transformations->scaleMatrix);
	transformationsMatrix.set(&transformations->transformationsMatrix);
}

void Transformations::update()
{
	transformationsMatrix.identity();
	translationMatrix.identity()->translate(&translation);
	scaleMatrix.identity()->scale(&scale);
	rotations.update();
	rotationsMatrix.identity();
	rotationsPivot.set(&pivot)->scale(-1.0f);
	rotationsMatrix.translate(&rotationsPivot);
	rotations.quaternion.computeMatrix(&rotationsQuaternionMatrix);
	rotationsMatrix.multiply(&rotationsQuaternionMatrix);
	rotationsTranslationsMatrix.identity()->translate(&pivot);
	rotationsMatrix.multiply(&rotationsTranslationsMatrix);
	transformationsMatrix.multiply(&scaleMatrix);
	transformationsMatrix.multiply(&rotationsMatrix);
	transformationsMatrix.multiply(&translationMatrix);
}
