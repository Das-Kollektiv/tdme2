#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <reactphysics3d/body/RigidBody.h>
#include <reactphysics3d/collision/shapes/CollisionShape.h>
#include <reactphysics3d/collision/Collider.h>

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
 * Rigid body class
 * @author Andreas Drewke
 */
class tdme::engine::physics::Body
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
	static constexpr uint16_t COLLISION_TYPEID_RESERVED { 32768 };
	static constexpr uint16_t COLLISION_TYPEID_ALL { 65535 };

	/**
	 * @returns no rotation inertia tensor
	 */
	inline static const Vector3 getNoRotationInertiaTensor() {
		return Vector3(0.0f, 0.0f, 0.0f);
	}

protected:
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
	bool initiation;

	// forbid class copy
	FORBID_CLASS_COPY(Body)

	/**
	 * Protected constructor
	 * @param world world
	 * @param id id
	 * @param type type
	 * @param collisionTypeId collision type id
	 * @param enabled enabled
	 * @param transform transform
	 * @param restitution restitution
	 * @param friction friction
	 * @param mass mass in kg
	 * @param inertiaTensor inertia tensor vector
	 * @param boundingVolumes bounding volumes
	 */
	Body(World* world, const string& id, BodyType type, uint16_t collisionTypeId, bool enabled, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*>& boundingVolumes);

	/**
	 * Destructor
	 */
	virtual ~Body();

	/**
	 * Remove colliders
	 * @param colliders colliders
	 * @param boundingVolumes bounding volumes
	 */
	void removeColliders(vector<reactphysics3d::Collider*>& colliders, vector<BoundingVolume*>& boundingVolumes);

	/**
	 * Reset given colliders with given bounding volumes and local transform
	 * @param colliders colliders
	 * @param boundingVolumes bounding volumes
	 * @param transform transform
	 */
	void resetColliders(vector<reactphysics3d::Collider*>& colliders, vector<BoundingVolume*>& boundingVolumes, const Transform& transform);

	/**
	 * Reset body colliders
	 */
	virtual void resetColliders();

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
	 * @returns id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * Return type, see TYPE_*
	 * @returns type
	 */
	inline BodyType getType() {
		return type;
	}

	/**
	 * @returns type id
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
	 * @returns collision type ids bitmask
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
	 * @returns if enabled
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
	 * @returns if sleeping
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
	 * @returns bounding volumes
	 */
	inline vector<BoundingVolume*>& getBoundingVolumes() {
		return boundingVolumes;
	}

	/**
	 * Compute world bounding box
	 */
	inline BoundingBox computeWorldBoundingBox() {
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
	 * @returns friction
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
	 * @returns restitution / bouncyness
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
	 * @returns mass
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
	 * @returns linear velocity
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
	 * @returns angular velocity
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
	 * @returns return linear damping
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
	 * @returns return angular damping
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
	 * @returns transform
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
		this->transform = transform;

		// reset colliders if bounding volumes do not match proxy shapes or if scaling has changed
		if (initiation == true || colliders.size() != boundingVolumes.size() || transformScale.equals(transform.getScale()) == false) {
			initiation = false;
			resetColliders();
			transformScale.set(transform.getScale());
		}

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
	 * Set angular lock axis factor
	 * @param factor factor
	 */
	inline void setAngularLockAxisFactor(const Vector3& factor) {
		rigidBody->setAngularLockAxisFactor(reactphysics3d::Vector3(factor.getX(), factor.getY(), factor.getZ()));
	}

	/**
	 * Set linear lock axis factor
	 * @param factor factor
	 */
	inline void setLinearLockAxisFactor(const Vector3& factor) {
		rigidBody->setLinearLockAxisFactor(reactphysics3d::Vector3(factor.getX(), factor.getY(), factor.getZ()));
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
