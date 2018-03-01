#include <tdme/engine/physics/RigidBodyCloned.h>

#include <string>
#include <vector>

#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/engine/primitives/BoundingVolume.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::physics::RigidBodyCloned;

using tdme::engine::Transformations;
using tdme::engine::physics::World;
using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingVolume;

RigidBodyCloned::RigidBodyCloned(World* world, const string& id, bool enabled, int32_t typeId, BoundingVolume* obv, BoundingVolume* cbv, const Transformations& transformations, float restitution, float friction, float mass, const RigidBody::InertiaMatrixSettings& inverseInertiaSettings) :
	RigidBody(world, id, enabled, typeId, restitution, friction, mass, inverseInertiaSettings)
{
	this->world = world;
	this->idx = -1;
	this->id = id;
	this->rootId = id;
	this->enabled = enabled;
	this->typeId = typeId;
	this->collisionTypeIds = TYPEIDS_ALL;
	this->inverseInertiaSettings = inverseInertiaSettings;
	this->restitution = restitution;
	this->friction = friction;
	this->isSleeping_ = false;
	this->sleepingFrameCount = 0;
	setMass(mass);
	this->obv = obv;
	if (isStatic_ == true) {
		this->cbv = cbv;
	} else {
		this->cbv = obv->clone();
	}
	fromTransformations(transformations);
}

void RigidBodyCloned::dispose() {
	if (isStatic_ == false) {
		delete cbv;
	}
}

void RigidBodyCloned::fromTransformations(const Transformations& transformations)
{
	if (this->isStatic_ == true) {
		this->transformations.fromTransformations(transformations);
		return;
	}
	RigidBody::fromTransformations(transformations);
}
