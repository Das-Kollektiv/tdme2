#include <tdme/engine/primitives/Sphere.h>

#include <reactphysics3d/collision/shapes/SphereShape.h>

#include <tdme/tdme.h>
#include <tdme/engine/physics/World.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::to_string;

using tdme::engine::physics::World;
using tdme::engine::primitives::Sphere;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::utilities::Console;

Sphere::Sphere()
{
	radius = Math::EPSILON;
}

Sphere::Sphere(const Vector3& center, float radius, const Vector3& scale)
{
	this->center.set(center);
	this->radius = radius;
	setScale(scale);
}

Sphere::~Sphere() {
	destroyCollisionShape();
}

float Sphere::getRadius() const
{
	return radius;
}

void Sphere::setScale(const Vector3& scale) {
	// store new scale
	this->scale.set(scale);

	// remove old collision shape
	if (collisionShape != nullptr) delete collisionShape;
	collisionShape = nullptr;

	//
	collisionShapeLocalTranslation.set(center).scale(scale);
	collisionShapeLocalTransform.setPosition(reactphysics3d::Vector3(collisionShapeLocalTranslation.getX(), collisionShapeLocalTranslation.getY(), collisionShapeLocalTranslation.getZ()));
}

void Sphere::destroyCollisionShape() {
	// remove collision shape
	if (collisionShape == nullptr) return;
	this->world->physicsCommon.destroySphereShape(static_cast<reactphysics3d::SphereShape*>(collisionShape));
	collisionShape = nullptr;
	world = nullptr;
}

void Sphere::createCollisionShape(World* world) {
	if (this->world != nullptr && this->world != world) {
		Console::println("Sphere::createCollisionShape(): already attached to a world.");
	}
	this->world = world;

	//
	collisionShape = world->physicsCommon.createSphereShape(
		Math::max(Math::EPSILON, radius * Math::max(Math::abs(scale.getZ()), Math::max(Math::abs(scale.getX()), Math::abs(scale.getY()))))
	);
	// compute bounding box
	computeBoundingBox();
}

BoundingVolume* Sphere::clone() const
{
	return new Sphere(center, radius, scale);
}

