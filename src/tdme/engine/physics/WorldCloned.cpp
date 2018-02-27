#include <tdme/engine/physics/WorldCloned.h>

#include <algorithm>
#include <map>
#include <string>

#include <tdme/math/Math.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/physics/ConstraintsEntity.h>
#include <tdme/engine/physics/ConstraintsSolver.h>
#include <tdme/engine/physics/PhysicsPartition.h>
#include <tdme/engine/physics/PhysicsPartitionOctTree.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/engine/physics/RigidBodyCloned.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/physics/WorldListener.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/VectorIteratorMultiple.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/StringUtils.h>

using std::remove;
using std::map;
using std::string;
using std::to_string;

using tdme::engine::physics::World;

using tdme::math::Math;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::ConstraintsEntity;
using tdme::engine::physics::ConstraintsSolver;
using tdme::engine::physics::PhysicsPartition;
using tdme::engine::physics::RigidBody;
using tdme::engine::physics::RigidBodyCloned;
using tdme::engine::physics::WorldCloned;
using tdme::engine::physics::WorldListener;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::LineSegment;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utils::VectorIteratorMultiple;
using tdme::utils::Pool;
using tdme::utils::Console;
using tdme::utils::StringUtils;

WorldCloned::WorldCloned(): World()
{
}

WorldCloned::~WorldCloned()
{
}

RigidBody* WorldCloned::createRigidBody(const string& id, bool enabled, int32_t typeId, BoundingVolume* obv, BoundingVolume* cbv, const Transformations& transformations, float restitution, float friction, float mass, const RigidBody::InertiaMatrixSettings& inverseInertiaSettings) {
	return new RigidBodyCloned(this, id, enabled, typeId, obv, cbv, transformations, restitution, friction, mass, inverseInertiaSettings);
}

RigidBody* WorldCloned::addRigidBody(RigidBody* rigidBody) {
	return World::addRigidBody(rigidBody);
}

void WorldCloned::synch(RigidBody* clonedRigidBody, RigidBody* rigidBody)
{
	clonedRigidBody->enabled = rigidBody->enabled;
	clonedRigidBody->isSleeping_ = rigidBody->isSleeping_;
	clonedRigidBody->collisionTypeIds = rigidBody->collisionTypeIds;
	if (clonedRigidBody->isStatic_ == false) clonedRigidBody->cbv->fromBoundingVolume(rigidBody->cbv);
	clonedRigidBody->isStatic_ = rigidBody->isStatic_;
	clonedRigidBody->mass = rigidBody->mass;
	clonedRigidBody->inverseMass = rigidBody->inverseMass;
	clonedRigidBody->force.set(rigidBody->force);
	clonedRigidBody->torque.set(rigidBody->torque);
	clonedRigidBody->orientation.set(rigidBody->orientation);
	clonedRigidBody->angularVelocity.set(rigidBody->angularVelocity);
	clonedRigidBody->linearVelocity.set(rigidBody->linearVelocity);
	clonedRigidBody->angularVelocityLast.set(rigidBody->angularVelocityLast);
	clonedRigidBody->movement.set(rigidBody->movement);
	clonedRigidBody->position.set(rigidBody->position);
	clonedRigidBody->worldInverseInertia.set(rigidBody->worldInverseInertia);
	clonedRigidBody->transformations.fromTransformations(rigidBody->transformations);
}

