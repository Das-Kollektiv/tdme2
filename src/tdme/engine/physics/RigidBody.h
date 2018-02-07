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
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/engine/physics/CollisionListener.h>

using std::remove;
using std::vector;
using std::string;

using tdme::engine::Transformations;
using tdme::engine::physics::CollisionListener;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Rigid Body class
 * ported from "game physics - a practical introduction/ben kenwright"
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::RigidBody final
{
	friend class World;

public:
	static constexpr int32_t TYPE_STATIC { 0 };
	static constexpr int32_t TYPE_DYNAMIC { 2 };
	static constexpr int32_t TYPE_KINEMATIC { 1 };

	static constexpr uint16_t TYPEID_STATIC { 1 };
	static constexpr uint16_t TYPEID_DYNAMIC { 2 };
	static constexpr uint16_t TYPEIDS_ALL { 65535 };

private:
	World* world {  };
	reactphysics3d::RigidBody* rigidBody;
	reactphysics3d::ProxyShape* proxyShape;
	string id {  };
	string rootId {  };
	bool enabled {  };
	int32_t typeId {  };
	Matrix4x4 inverseInertiaMatrix;
	Vector3 linearVelocity;
	Vector3 angularVelocity;
	Transformations transformations {  };
	BoundingVolume* boundingVolume {  };
	vector<CollisionListener*> collisionListener {  };

	/**
	 * Fire on collision
	 * @param other
	 * @param collision response
	 */
	void fireOnCollision(RigidBody* other, CollisionResponse* collisionResponse);

	/**
	 * Fire on collision begin
	 * @param other
	 * @param collision response
	 */
	void fireOnCollisionBegin(RigidBody* other, CollisionResponse* collisionResponse);

	/**
	 * Fire on collision end
	 * @param other
	 * @param collision response
	 */
	void fireOnCollisionEnd(RigidBody* other);

	/**
	 * Protected constructor
	 * @param partition
	 * @param id
	 * @param type
	 * @param enabled
	 * @param type id
	 * @param bounding volume
	 * @param transformations
	 * @param restitution
	 * @param mass in kg
	 */
	RigidBody(World* world, const string& id, int type, bool enabled, uint16_t typeId, BoundingVolume* boundingVolume, Transformations* transformations, float restitution, float friction, float mass, const Matrix4x4& inertiaMatrix);

	/**
	 * Destructor
	 */
	~RigidBody();

public:

	/** 
	 * No rotation inertia matrix
	 * @param bv
	 * @param mass
	 * @return inertia matrix
	 */
	static Matrix4x4 getNoRotationInertiaMatrix();

	/** 
	 * Computes the inertia matrix
	 * @param bv
	 * @param mass
	 * @return inertia matrix
	 */
	static Matrix4x4 computeInertiaMatrix(BoundingVolume* bv, float mass, float scaleXAxis, float scaleYAxis, float scaleZAxis);

	/** 
	 * @return id
	 */
	const string& getId();

	/** 
	 * @return root id
	 */
	const string& getRootId();

	/**
	 * Set root id
	 * @param root id
	 */
	void setRootId(const string& rootId);

	/**
	 * @return type id
	 */
	uint16_t getTypeId();

	/** 
	 * @return collision type ids bitmask
	 */
	uint16_t getCollisionTypeIds();

	/** 
	 * Set up collision type ids
	 * @param collisionTypeIds
	 */
	void setCollisionTypeIds(uint16_t collisionTypeIds);

	/** 
	 * @return if enabled
	 */
	bool isEnabled();

	/** 
	 * Set up if rigid body is enabled
	 * @param enabled
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
	 * @return original bounding volume
	 */
	BoundingVolume* getBoundingVolume();

	/**
	 * Compute bounding box transformed
	 */
	BoundingBox computeBoundingBoxTransformed();

	/**
	 * @return position
	 */
	Vector3& getPosition();

	/** 
	 * @return friction
	 */
	float getFriction();

	/** 
	 * Set up friction
	 * @param friction
	 */
	void setFriction(float friction);

	/** 
	 * @return restitution / bouncyness
	 */
	float getRestitution();

	/** 
	 * Set up restitution
	 * @param restitution
	 */
	void setRestitution(float restitution);

	/** 
	 * @return mass
	 */
	float getMass();

	/** 
	 * Set up mass
	 * @param mass
	 */
	void setMass(float mass);

	/** 
	 * @return linear velocity
	 */
	Vector3& getLinearVelocity();

	/** 
	 * @return angular velocity
	 */
	Vector3& getAngularVelocity();

	/**
	 * @return transformations
	 */
	Transformations* getTransformations();

	/** 
	 * Synchronizes this rigid body with transformations
	 * @param transformations
	 */
	void fromTransformations(Transformations* transformations);

	/** 
	 * Add force
	 * @param position of world force
	 * @param force
	 */
	void addForce(const Vector3& forceOrigin, const Vector3& force);

	/**
	 * Add force to center of mass
	 * @param force
	 */
	void addForce(const Vector3& forceOrigin);

	/**
	 * Add torque
	 * @param torque
	 */
	void addTorque(const Vector3& torque);

	/**
	 * Checks if this rigid body does collide with given bounding volume
	 * @deprecated this method is deprecated, please try to avoid it
	 * @param bounding volume
	 * @param collision
	 */
	bool doesCollideWith(BoundingVolume* boundingVolume, CollisionResponse* collision);

	/**
	 * Checks if this rigid body does collide with another rigid body
	 * @param rigid body
	 * @param bounding volume
	 * @param collision
	 */
	bool doesCollideWith(RigidBody* rigidBody, CollisionResponse* collision);

	/** 
	 * Add a collision listener to this rigid body
	 * @param listener
	 */
	void addCollisionListener(CollisionListener* listener);

	/** 
	 * Remove a collision listener to this rigid body
	 * @param listener
	 */
	void removeCollisionListener(CollisionListener* listener);

};
