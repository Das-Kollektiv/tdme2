#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <reactphysics3d/body/RigidBody.h>
#include <reactphysics3d/collision/shapes/CollisionShape.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/CollisionListener.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::remove;
using std::string;
using std::vector;

using tdme::engine::physics::CollisionListener;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Dynamic rigid/static rigid/collision body class
 * @author Andreas Drewke
 */
class tdme::engine::physics::Body final
{
	friend class World;

public:
	enum BodyType {
		BODYTYPE_STATIC,
		BODYTYPE_DYNAMIC,
		BODYTYPE_KINEMATIC,
		BODYTYPE_COLLISION_STATIC,
		BODYTYPE_COLLISION_DYNAMIC
	};

	static constexpr uint16_t COLLISION_TYPEID_STATIC { 1 };
	static constexpr uint16_t COLLISION_TYPEID_DYNAMIC { 2 };
	static constexpr uint16_t COLLISION_TYPEID_3 { 4 };
	static constexpr uint16_t COLLISION_TYPEID_4 { 8 };
	static constexpr uint16_t COLLISION_TYPEID_5 { 16 };
	static constexpr uint16_t COLLISION_TYPEID_6 { 32 };
	static constexpr uint16_t COLLISION_TYPEID_7 { 64 };
	static constexpr uint16_t COLLISION_TYPEID_8 { 128 };
	static constexpr uint16_t COLLISION_TYPEID_9 { 256 };
	static constexpr uint16_t COLLISION_TYPEID_10 { 512 };
	static constexpr uint16_t COLLISION_TYPEID_11 { 1024 };
	static constexpr uint16_t COLLISION_TYPEID_12 { 2048 };
	static constexpr uint16_t COLLISION_TYPEID_13 { 4096 };
	static constexpr uint16_t COLLISION_TYPEID_14 { 8192 };
	static constexpr uint16_t COLLISION_TYPEID_15 { 16384 };
	static constexpr uint16_t COLLISION_TYPEID_16 { 32768 };
	static constexpr uint16_t COLLISION_TYPEID_ALL { 65535 };

	/**
	 * @return no rotation inertia tensor
	 */
	inline static const Vector3 getNoRotationInertiaTensor() {
		return Vector3(0.0f, 0.0f, 0.0f);
	}

private:
	World* world { nullptr };
	reactphysics3d::RigidBody* rigidBody { nullptr };
	string id;
	BodyType type;
	float restitution;
	float friction;
	float mass;
	uint16_t collisionTypeIds;
	uint16_t collisionTypeId;
	Vector3 inertiaTensor;
	Transform transform;
	Vector3 transformScale;
	vector<BoundingVolume*> boundingVolumes;
	vector<reactphysics3d::Collider*> colliders;
	vector<CollisionListener*> collisionListener;

	/**
	 * Protected constructor
	 * @param world world
	 * @param id id
	 * @param type type
	 * @param enabled enabled
	 * @param collisionTypeId collision type id
	 * @param transform transform
	 * @param restitution restitution
	 * @param friction friction
	 * @param mass mass in kg
	 * @param inertiaTensor inertia tensor vector
	 * @param boundingVolumes bounding volumes
	 */
	Body(World* world, const string& id, BodyType type, bool enabled, uint16_t collisionTypeId, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*> boundingVolumes);

	/**
	 * Destructor
	 */
	~Body();

	/**
	 * Reset proxy shapes
	 */
	void resetColliders();

	/**
	 * Fire on collision
	 * @param other other
	 * @param collisionResponse collision response
	 */
	void fireOnCollision(Body* other, CollisionResponse& collisionResponse);

	/**
	 * Fire on collision begin
	 * @param other other
	 * @param collisionResponse collision response
	 */
	void fireOnCollisionBegin(Body* other, CollisionResponse& collisionResponse);

	/**
	 * Fire on collision end
	 * @param other other
	 */
	void fireOnCollisionEnd(Body* other);

public:

	/**
	 * @return id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * Return type, see TYPE_*
	 * @return type
	 */
	inline BodyType getType() {
		return type;
	}

	/**
	 * @return type id
	 */
	inline uint16_t getCollisionTypeId() {
		return collisionTypeId;
	}

	/**
	 * Set collision type id
	 * @param typeId type id
	 */
	void setCollisionTypeId(uint16_t typeId);

	/**
	 * @return collision type ids bitmask
	 */
	inline uint16_t getCollisionTypeIds() {
		return collisionTypeIds;
	}

	/**
	 * Set up collision type ids
	 * @param collisionTypeIds collisionTypeIds
	 */
	void setCollisionTypeIds(uint16_t collisionTypeIds);

	/**
	 * @return if enabled
	 */
	inline bool isEnabled() {
		return rigidBody->isActive();
	}

	/**
	 * Set up if rigid body is enabled
	 * @param enabled enabled
	 */
	inline void setEnabled(bool enabled) {
		rigidBody->setIsActive(enabled);
		if (enabled == true) rigidBody->setIsSleeping(false);
	}

	/**
	 * @return if sleeping
	 */
	inline bool isSleeping() {
		return rigidBody->isSleeping();
	}

	/**
	 * Set sleeping
	 * @param sleeping sleeping
	 */
	inline void setSleeping(bool sleeping) {
		rigidBody->setIsSleeping(sleeping);
	}

	/**
	 * @deprecated this method should be removed
	 * @return bounding volumes
	 */
	inline vector<BoundingVolume*>& getBoundingVolumes() {
		return boundingVolumes;
	}

	/**
	 * Add bounding volume
	 * @param boundingVolume bounding volume
	 */
	void addBoundingVolume(BoundingVolume* boundingVolume);

	/**
	 * Compute bounding box transformed
	 */
	inline BoundingBox computeBoundingBoxTransformed() {
		auto aabb = rigidBody->getAABB();
		return BoundingBox(
			Vector3(
				aabb.getMin().x,
				aabb.getMin().y,
				aabb.getMin().z
			),
			Vector3(
				aabb.getMax().x,
				aabb.getMax().y,
				aabb.getMax().z
			)
		);
	}

	/**
	 * @return friction
	 */
	inline float getFriction() {
		return friction;
	}

	/**
	 * Set up friction
	 * @param friction friction
	 */
	void setFriction(float friction);

	/**
	 * @return restitution / bouncyness
	 */
	inline float getRestitution() {
		return restitution;
	}

	/**
	 * Set up restitution
	 * @param restitution restitution
	 */
	void setRestitution(float restitution);

	/**
	 * @return mass
	 */
	inline float getMass() {
		return mass;
	}

	/**
	 * Set up mass
	 * @param mass mass
	 */
	inline void setMass(float mass) {
		this->mass = mass;
		rigidBody->setMass(mass);
	}

	/**
	 * @return linear velocity
	 */
	inline const Vector3 getLinearVelocity() {
		return Vector3(
			rigidBody->getLinearVelocity().x,
			rigidBody->getLinearVelocity().y,
			rigidBody->getLinearVelocity().z
		);
	}

	/**
	 * Set linear velocity
	 * @param linearVelocity velocity
	 */
	inline void setLinearVelocity(const Vector3& linearVelocity) {
		rigidBody->setLinearVelocity(reactphysics3d::Vector3(linearVelocity.getX(), linearVelocity.getY(), linearVelocity.getZ()));
	}

	/**
	 * @return angular velocity
	 */
	inline const Vector3 getAngularVelocity() {
		return Vector3(
			rigidBody->getAngularVelocity().x,
			rigidBody->getAngularVelocity().y,
			rigidBody->getAngularVelocity().z
		);
	}

	/**
	 * Set angular velocity
	 * @param angularVelocity angular velocity
	 */
	inline void setAngularVelocity(const Vector3& angularVelocity) {
		rigidBody->setAngularVelocity(reactphysics3d::Vector3(angularVelocity.getX(), angularVelocity.getY(), angularVelocity.getZ()));
	}

	/**
	 * @return return linear damping
	 */
	inline float getLinearDamping() {
		return rigidBody->getLinearDamping();
	}

	/**
	 * Set linear damping
	 * @param linearDamping linear damping
	 */
	inline void setLinearDamping(float linearDamping) {
		rigidBody->setLinearDamping(linearDamping);
	}

	/**
	 * @return return angular damping
	 */
	inline float getAngularDamping() {
		return rigidBody->getAngularDamping();
	}

	/**
	 * Set angular damping
	 * @param angularDamping anuglar damping
	 */
	inline void setAngularDamping(float angularDamping) {
		rigidBody->setAngularDamping(angularDamping);
	}

	/**
	 * @return transform
	 */
	inline const Transform& getTransform() {
		return transform;
	}

	/**
	 * Set transform
	 * @param transform transform
	 */
	inline void setTransform(const Transform& transform) {
		// store engine transform
		this->transform.setTransform(transform);

		// reset proxy shapes if bounding volumes do not match proxy shapes or if scaling has changed
		if (colliders.size() != boundingVolumes.size() || transformScale.equals(transform.getScale()) == false) {
			resetColliders();
			transformScale.set(transform.getScale());
		}

		/*
		// TODO: center of mass ~ pivot
		// set center of mass which is basically center of bv for now
		body->setCenterOfMassLocal(boundingVolume->collisionShapeLocalTransform.getPosition());
		// find final position, not sure yet if its working 100%, but still works with some tests
		auto centerOfMassWorld = transform * boundingVolume->collisionShapeLocalTransform.getPosition();
		transform.setPosition(
			transform.getPosition() +
			transform.getPosition() -
			centerOfMassWorld +
			(
				reactphysics3d::Vector3(
					boundingVolume->collisionShapeLocalTranslation.getX(),
					boundingVolume->collisionShapeLocalTranslation.getY(),
					boundingVolume->collisionShapeLocalTranslation.getZ()
				) * scaleVectorTransformed
			)
		);
		*/

		// set transform
		rigidBody->setTransform(
			reactphysics3d::Transform(
				reactphysics3d::Vector3(
					this->transform.getTranslation().getX(),
					this->transform.getTranslation().getY(),
					this->transform.getTranslation().getZ()
				),
				reactphysics3d::Quaternion(
					this->transform.getRotationsQuaternion().getX(),
					this->transform.getRotationsQuaternion().getY(),
					this->transform.getRotationsQuaternion().getZ(),
					this->transform.getRotationsQuaternion().getW()
				)
			)
		);
	}

	/**
	 * Add force
	 * @param forceOrigin position of world force
	 * @param force force
	 */
	inline void addForce(const Vector3& forceOrigin, const Vector3& force) {
		rigidBody->applyWorldForceAtWorldPosition(
			reactphysics3d::Vector3(force.getX(), force.getY(), force.getZ()),
			reactphysics3d::Vector3(forceOrigin.getX(), forceOrigin.getY(), forceOrigin.getZ())
		);
	}

	/**
	 * Add force to center of mass
	 * @param force force
	 */
	inline void addForce(const Vector3& force) {
		rigidBody->applyWorldForceAtCenterOfMass(
			reactphysics3d::Vector3(force.getX(), force.getY(), force.getZ())
		);
	}

	/**
	 * Add torque
	 * @param torque torque
	 */
	inline void addTorque(const Vector3& torque) {
		rigidBody->applyWorldTorque(
			reactphysics3d::Vector3(torque.getX(), torque.getY(), torque.getZ())
		);
	}

	/**
	 * Add a collision listener to this rigid body
	 * @param listener listener
	 */
	void addCollisionListener(CollisionListener* listener);

	/**
	 * Remove a collision listener to this rigid body
	 * @param listener listener
	 */
	void removeCollisionListener(CollisionListener* listener);

};
