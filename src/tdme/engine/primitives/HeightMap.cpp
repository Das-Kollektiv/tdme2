#include <tdme/engine/primitives/HeightMap.h>

#include <vector>

#include <reactphysics3d/collision/shapes/HeightFieldShape.h>
#include <reactphysics3d/collision/HeightField.h>
#include <reactphysics3d/mathematics/Vector3.h>
#include <reactphysics3d/utils/Message.h>

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
	float* heightValues,
	const Vector3& scale
) {
	this->scale.set(scale);
	this->columns = columns;
	this->rows = rows;
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
	this->world->physicsCommon.destroyHeightField(heightField);
	collisionShape = nullptr;
	world = nullptr;
}

void HeightMap::createCollisionShape(World* world) {
	if (this->world != nullptr && this->world != world) {
		Console::printLine("HeightMap::createCollisionShape(): already attached to a world.");
	}
	this->world = world;
	vector<reactphysics3d::Message> messages;
	heightField = world->physicsCommon.createHeightField(
		columns,
		rows,
		heightValues,
		reactphysics3d::HeightField::HeightDataType::HEIGHT_FLOAT_TYPE,
		messages
	);
	// dump messages
	for (const auto& message: messages) {
		auto getMessageTypeText = [](const reactphysics3d::Message& message) -> const string {
			switch (message.type) {
				case reactphysics3d::Message::Type::Error:
					return "ERROR";
				case reactphysics3d::Message::Type::Warning:
					return "WARNING";
				case reactphysics3d::Message::Type::Information:
					return "INFORMATION";
				default:
					return "INVALID";
			}
		};
		Console::printLine("HeightMap::createCollisionShape(): " + getMessageTypeText(message) + ": " + message.text);
	}
	//
	collisionShape = world->physicsCommon.createHeightFieldShape(
		heightField
	);
}

BoundingVolume* HeightMap::clone() const
{
	return new HeightMap(columns, rows, heightValues);
}

