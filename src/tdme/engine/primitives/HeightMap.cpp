#include <tdme/engine/primitives/HeightMap.h>

#include <reactphysics3d/collision/shapes/HeightFieldShape.h>
#include <reactphysics3d/mathematics/Vector3.h>

#include <tdme/tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/engine/physics/World.h>
#include <tdme/utilities/Console.h>

using std::to_string;

using tdme::engine::primitives::HeightMap;

using tdme::engine::physics::World;
using tdme::math::Vector3;
using tdme::utilities::Console;

HeightMap::HeightMap(
	int columns,
	int rows,
	float minHeight,
	float maxHeight,
	float* heightValues,
	const Vector3& scale
) {
	this->scale.set(scale);
	this->columns = columns;
	this->rows = rows;
	this->minHeight = minHeight;
	this->maxHeight = maxHeight;
	this->heightValues = heightValues;
}

HeightMap::~HeightMap() {
	destroyCollisionShape();
}

void HeightMap::setScale(const Vector3& scale) {
	Console::printLine("HeightMap::setScale(): not supported!");
}

void HeightMap::destroyCollisionShape() {
	if (collisionShape == nullptr) return;
	this->world->physicsCommon.destroyHeightFieldShape(static_cast<reactphysics3d::HeightFieldShape*>(collisionShape));
	collisionShape = nullptr;
	world = nullptr;
}

void HeightMap::createCollisionShape(World* world) {
	if (this->world != nullptr && this->world != world) {
		Console::printLine("HeightMap::createCollisionShape(): already attached to a world.");
	}
	this->world = world;

	//
	collisionShape = world->physicsCommon.createHeightFieldShape(
		columns,
		rows,
		minHeight,
		maxHeight,
		heightValues,
		reactphysics3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE,
		1,
		1.0f,
		reactphysics3d::Vector3(scale.getX(), scale.getY(), scale.getZ())
	);
}

BoundingVolume* HeightMap::clone() const
{
	return new HeightMap(columns, rows, minHeight, maxHeight, heightValues);
}

