#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <ext/reactphysics3d/src/body/Body.h>
#include <ext/reactphysics3d/src/body/CollisionBody.h>
#include <ext/reactphysics3d/src/body/RigidBody.h>
#include <ext/reactphysics3d/src/collision/ProxyShape.h>

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
	static constexpr int32_t TYPE_STATIC { 0 };
	static constexpr int32_t TYPE_DYNAMIC { 2 };
	static constexpr int32_t TYPE_KINEMATIC { 1 };
	static constexpr int32_t TYPE_COLLISION { 3 };

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
	static const Vector3 getNoRotationInertiaTensor();

private:
	World* world { nullptr };
	reactphysics3d::RigidBody* rigidBody { nullptr };
	reactphysics3d::CollisionBody* collisionBody { nullptr };
	bool cloned { false };
	string id;
	int type;
	float mass;
	uint16_t collideTypeIds;
	uint16_t collisionTypeId;
	Vector3 inertiaTensor;
	Transform transform;
	Vector3 transformScale;
	vector<BoundingVolume*> boundingVolumes;
	vector<reactphysics3d::ProxyShape*> proxyShapes;
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
	Body(World* world, const string& id, int type, bool enabled, uint16_t collisionTypeId, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*> boundingVolumes);

	/**
	 * Destructor
	 */
	~Body();

	/**
	 * @return if rigid body has been cloned from another rigid body
	 */
	bool isCloned();

	/**
	 * Set cloned
	 * @param cloned cloned
	 */
	void setCloned(bool cloned);

	/**
	 * Reset proxy shapes
	 */
	void resetProxyShapes();

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

	/**
	 * Computes the inverse inertia matrix
	 * @param boundingBox bounding box
	 * @param mass mass
	 * @param scaleXAxis scale x axis
	 * @param scaleYAxis scale y axis
	 * @param scaleZAxis scale z axis
	 * @return inverse inertia matrix
	 */
	static Matrix4x4 computeInverseInertiaMatrix(BoundingBox* boundingBox, float mass, float scaleXAxis, float scaleYAxis, float scaleZAxis);

public:

	/**
	 * @return id
	 */
	const string& getId();

	/**
	 * Return type, see TYPE_*
	 * @return type
	 */
	int getType();

	/**
	 * @return type id
	 */
	uint16_t getCollisionTypeId();

	/**
	 * Set collision type id
	 * @param typeId type id
	 */
	void setCollisionTypeId(uint16_t typeId);

	/**
	 * @return collision type ids bitmask
	 */
	uint16_t getCollisionTypeIds();

	/**
	 * Set up collision type ids
	 * @param collisionTypeIds collisionTypeIds
	 */
	void setCollisionTypeIds(uint16_t collisionTypeIds);

	/**
	 * @return if enabled
	 */
	bool isEnabled();

	/**
	 * Set up if rigid body is enabled
	 * @param enabled enabled
	 */
	void setEnabled(bool enabled);

	/**
	 * @return object is static
	 */
	bool isStatic();

	/**
	 * @return if sleeping
	 */
	bool isSleeping();

	/**
	 * Set sleeping
	 * @param sleeping sleeping
	 */
	void setSleeping(bool sleeping);

	/**
	 * @deprecated this method should be removed
	 * @return bounding volumes
	 */
	vector<BoundingVolume*>& getBoundingVolumes();

	/**
	 * Add bounding volume
	 * @param boundingVolume bounding volume
	 */
	void addBoundingVolume(BoundingVolume* boundingVolume);

	/**
	 * Compute bounding box transformed
	 */
	BoundingBox computeBoundingBoxTransformed();

	/**
	 * @return friction
	 */
	float getFriction();

	/**
	 * Set up friction
	 * @param friction friction
	 */
	void setFriction(float friction);

	/**
	 * @return restitution / bouncyness
	 */
	float getRestitution();

	/**
	 * Set up restitution
	 * @param restitution restitution
	 */
	void setRestitution(float restitution);

	/**
	 * @return mass
	 */
	float getMass();

	/**
	 * Set up mass
	 * @param mass mass
	 */
	void setMass(float mass);

	/**
	 * @return linear velocity
	 */
	const Vector3 getLinearVelocity();

	/**
	 * Set linear velocity
	 * @param linearVelocity velocity
	 */
	void setLinearVelocity(const Vector3& linearVelocity);

	/**
	 * @return angular velocity
	 */
	const Vector3 getAngularVelocity();

	/**
	 * Set angular velocity
	 * @param angularVelocity angular velocity
	 */
	void setAngularVelocity(const Vector3& angularVelocity);

	/**
	 * @return return linear damping
	 */
	float getLinearDamping();

	/**
	 * Set linear damping
	 * @param linearDamping linear damping
	 */
	void setLinearDamping(float linearDamping);

	/**
	 * @return return angular damping
	 */
	float getAngularDamping();

	/**
	 * Set angular damping
	 * @param angularDamping anuglar damping
	 */
	void setAngularDamping(float angularDamping);

	/**
	 * @return transform
	 */
	const Transform& getTransform();

	/**
	 * Set transform
	 * @param transform transform
	 */
	void setTransform(const Transform& transform);

	/**
	 * Add force
	 * @param forceOrigin position of world force
	 * @param force force
	 */
	void addForce(const Vector3& forceOrigin, const Vector3& force);

	/**
	 * Add force to center of mass
	 * @param force force
	 */
	void addForce(const Vector3& force);

	/**
	 * Add torque
	 * @param torque torque
	 */
	void addTorque(const Vector3& torque);

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
