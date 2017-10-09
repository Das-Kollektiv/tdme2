#include <tdme/engine/Rotations.h>

#include <vector>

#include <tdme/engine/Rotation.h>
#include <tdme/math/Quaternion.h>

using std::vector;

using tdme::engine::Rotations;
using tdme::engine::Rotation;
using tdme::math::Quaternion;

Rotations::Rotations() 
{
}

Rotations::~Rotations() {
	for (auto rotation: rotations) {
		delete rotation;
	}
}

int32_t Rotations::size()
{
	return rotations.size();
}

Rotation* Rotations::get(int32_t index)
{
	return rotations.at(index);
}

void Rotations::add(Rotation* rotation)
{
	rotations.push_back(rotation);
}

void Rotations::set(int32_t index, Rotation* rotation)
{
	rotations[index] = rotation;
}

void Rotations::remove(int32_t index)
{
	Rotation* rotation = rotations.at(index);
	rotations.erase(rotations.begin() + index);
	delete rotation;
}

Quaternion& Rotations::getQuaternion()
{
	return quaternion;
}

void Rotations::fromRotations(Rotations* transformations)
{
	auto rotationIdx = 0;
	for (; rotationIdx < transformations->size(); rotationIdx++) {
		auto rotation = transformations->get(rotationIdx);
		auto _rotation = rotationIdx < rotations.size() ? rotations.at(rotationIdx) : nullptr;
		if (_rotation == nullptr) {
			_rotation = new Rotation();
			rotations.push_back(_rotation);
		}
		_rotation->fromRotation(rotation);
	}
	while (rotationIdx < rotations.size()) {
		Rotation* rotation = rotations[rotations.size() - 1];
		auto _rotation = rotations.erase(rotations.begin() + rotations.size() - 1);
		delete rotation;
	}
	this->quaternion.set(transformations->quaternion);
}

void Rotations::update()
{
	quaternion.identity();
	for (auto rotation: rotations) {
		rotation->update();
		quaternion.multiply(rotation->getQuaternion());
	}
}
