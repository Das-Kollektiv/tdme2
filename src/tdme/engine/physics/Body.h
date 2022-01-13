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
#include <tdme/engine/Transformations.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::remove;
using std::string;
using std::vector;

using tdme::engine::physics::CollisionListener;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Transformations;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Console;

/**
 * Dynamic rigid/static rigid/collision body class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::Body final
{
	friend class World;

public:
	enum BodyType {
		BODYTYPE_STATIC = 0,
		BODYTYPE_DYNAMIC = 2,
		BODYTYPE_KINEMATIC = 1,
		BODYTYPE_COLLISION = 3
	};

	static constexpr uint16_t TYPEID_STATIC { 1 };
	static constexpr uint16_t TYPEID_DYNAMIC { 2 };
	static constexpr uint16_t TYPEIDS_ALL { 65535 };

	/**
	 * @return no rotation inertia tensor
	 */
	inline static const Vector3 getNoRotationInertiaTensor() {
		return Vector3(0.0f, 0.0f, 0.0f);
	}

private:
	World* world { nullptr };
	reactphysics3d::RigidBody* rigidBody { nullptr };
	reactphysics3d::CollisionBody* collisionBody { nullptr };
	bool cloned { false };
	string id;
	BodyType bodyType;
	float mass;
	uint16_t collideTypeIds;
	uint16_t collisionTypeId;
	Vector3 inertiaTensor;
	Transformations transformations;
	Vector3 transformationsScale;
	vector<BoundingVolume*> boundingVolumes;
	vector<reactphysics3d::ProxyShape*> proxyShapes;
	vector<CollisionListener*> collisionListener;

	/**
	 * Protected constructor
	 * @param world world
	 * @param id id
	 * @param bodyType body type
	 * @param enabled enabled
	 * @param collisionTypeId collision type id
	 * @param transformations transformations
	 * @param restitution restitution
	 * @param friction friction
	 * @param mass mass in kg
	 * @param inertiaTensor inertia tensor vector
	 * @param boundingVolumes bounding volumes
	 */
	Body(World* world, const string& id, BodyType bodyType, bool enabled, uint16_t collisionTypeId, const Transformations& transformations, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*> boundingVolumes);

	/**
	 * Destructor
	 */
	~Body();

	/**
	 * Reset proxy shapes
	 */
	void resetProxyShapes();

	/**
	 * Fire on collision
	 * @param other other
	 * @param collisionResponse collision response
	 */
	inline void fireOnCollision(Body* other, CollisionResponse& collisionResponse) {
		for (auto listener: collisionListener) {
			listener->onCollision(this, other, collisionResponse);
		}
	}

	/**
	 * Fire on collision begin
	 * @param other other
	 * @param collisionResponse collision response
	 */
	inline void fireOnCollisionBegin(Body* other, CollisionResponse& collisionResponse) {
		for (auto listener: collisionListener) {
			listener->onCollisionBegin(this, other, collisionResponse);
		}
	}

	/**
	 * Fire on collision end
	 * @param other other
	 */
	inline void fireOnCollisionEnd(Body* other) {
		for (auto listener: collisionListener) {
			listener->onCollisionEnd(this, other);
		}
	}

	/**
	 * Computes the inverse inertia matrix
	 * @param boundingBox bounding box
	 * @param mass mass
	 * @param scaleXAxis scale x axis
	 * @param scaleYAxis scale y axis
	 * @param scaleZAxis scale z axis
	 * @return inverse inertia matrix
	 */
	inline static Matrix4x4 computeInverseInertiaMatrix(BoundingBox* boundingBox, float mass, float scaleXAxis, float scaleYAxis, float scaleZAxis) {
		auto width = boundingBox->getDimensions().getX();
		auto height = boundingBox->getDimensions().getY();
		auto depth = boundingBox->getDimensions().getZ();
		return
			(Matrix4x4(
				scaleXAxis > Math::EPSILON && mass > Math::EPSILON?1.0f / (scaleXAxis * 1.0f / 12.0f * mass * (height * height + depth * depth)):0.0f,
				0.0f,
				0.0f,
				0.0f,
				0.0f,
				scaleYAxis > Math::EPSILON && mass > Math::EPSILON?1.0f / (scaleYAxis * 1.0f / 12.0f * mass * (width * width + depth * depth)):0.0f,
				0.0f,
				0.0f,
				0.0f,
				0.0f,
				scaleZAxis > Math::EPSILON && mass > Math::EPSILON?1.0f / (scaleZAxis * 1.0f / 12.0f * mass * (width * width + height * height)):0.0f,
				0.0f,
				0.0f,
				0.0f,
				0.0f,
				1.0f
			));
	}

public:
	/**
	 * @return if rigid body has been cloned from another rigid body
	 */
	inline bool isCloned() {
		return cloned;
	}

	/**
	 * Set cloned
	 * @param cloned cloned
	 */
	inline void setCloned(bool cloned) {
		this->cloned = cloned;
	}

	/**
	 * @return id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * Return type, see BODYTYPE_*
	 * @return type
	 */
	inline BodyType getType() {
		return bodyType;
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
		return collideTypeIds;
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
		return collisionBody->isActive();
	}

	/**
	 * Set up if rigid body is enabled
	 * @param enabled enabled
	 */
	inline void setEnabled(bool enabled) {
		collisionBody->setIsActive(enabled);
		if (enabled == true) collisionBody->setIsSleeping(false);
	}

	/**
	 * @return object is static
	 */
	bool isStatic();

	/**
	 * @return if sleeping
	 */
	inline bool isSleeping() {
		return collisionBody->isSleeping();
	}

	/**
	 * Set sleeping
	 * @param sleeping sleeping
	 */
	inline void setSleeping(bool sleeping) {
		collisionBody->setIsSleeping(sleeping);
	}

	/**
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
	BoundingBox computeBoundingBoxTransformed();

	/**
	 * @return friction
	 */
	inline float getFriction() {
		if (rigidBody == nullptr) {
			Console::println("Body::getFriction(): no rigid body attached");
			return 0.0f;
		}
		return rigidBody->getMaterial().getFrictionCoefficient();
	}

	/**
	 * Set up friction
	 * @param friction friction
	 */
	inline void setFriction(float friction) {
		if (rigidBody == nullptr) {
			Console::println("Body::setFriction(): no rigid body attached");
			return;
		}
		rigidBody->getMaterial().setFrictionCoefficient(friction);
	}

	/**
	 * @return restitution / bouncyness
	 */
	inline float getRestitution() {
		if (rigidBody == nullptr) {
			Console::println("Body::getRestitution(): no rigid body attached");
			return 0.0f;
		}
		return rigidBody->getMaterial().getBounciness();
	}

	/**
	 * Set up restitution
	 * @param restitution restitution
	 */
	inline void setRestitution(float restitution) {
		if (rigidBody == nullptr) {
			Console::println("Body::setRestitution(): no rigid body attached");
			return;
		}
		rigidBody->getMaterial().setBounciness(restitution);
	}

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
		if (rigidBody == nullptr) {
			Console::println("Body::setMass(): no rigid body attached");
			return;
		}
		rigidBody->setMass(mass);
	}

	/**
	 * @return linear velocity
	 */
	inline const Vector3 getLinearVelocity() {
		if (rigidBody == nullptr) {
			Console::println("Body::getLinearVelocity(): no rigid body attached");
			return Vector3();
		}
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
		if (rigidBody == nullptr) {
			Console::println("Body::setLinearVelocity(): no rigid body attached");
			return;
		}
		rigidBody->setLinearVelocity(reactphysics3d::Vector3(linearVelocity.getX(), linearVelocity.getY(), linearVelocity.getZ()));
	}

	/**
	 * @return angular velocity
	 */
	inline const Vector3 getAngularVelocity() {
		if (rigidBody == nullptr) {
			Console::println("Body::getAngularVelocity(): no rigid body attached");
			return Vector3();
		}
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
		if (rigidBody == nullptr) {
			Console::println("Body::setAngularVelocity(): no rigid body attached");
			return;
		}
		rigidBody->setAngularVelocity(reactphysics3d::Vector3(angularVelocity.getX(), angularVelocity.getY(), angularVelocity.getZ()));
	}

	/**
	 * @return return linear damping
	 */
	inline float getLinearDamping() {
		if (rigidBody == nullptr) {
			Console::println("Body::getLinearDamping(): no rigid body attached");
			return 0.0f;
		}
		return rigidBody->getLinearDamping();
	}

	/**
	 * Set linear damping
	 * @param linearDamping linear damping
	 */
	inline void setLinearDamping(float linearDamping) {
		if (rigidBody == nullptr) {
			Console::println("Body::setLinearDamping(): no rigid body attached");
			return;
		}
		rigidBody->setLinearDamping(linearDamping);
	}

	/**
	 * @return return angular damping
	 */
	inline float getAngularDamping() {
		if (rigidBody == nullptr) {
			Console::println("Body::getAngularDamping(): no rigid body attached");
			return 0.0f;
		}
		return rigidBody->getAngularDamping();
	}

	/**
	 * Set angular damping
	 * @param angularDamping anuglar damping
	 */
	inline void setAngularDamping(float angularDamping) {
		if (rigidBody == nullptr) {
			Console::println("Body::setAngularDamping(): no rigid body attached");
			return;
		}
		rigidBody->setAngularDamping(angularDamping);
	}

	/**
	 * @return transformations
	 */
	inline const Transformations& getTransformations() {
		return transformations;
	}

	/**
	 * Synchronizes this rigid body with transformations
	 * @param transformations transformations
	 */
	void fromTransformations(const Transformations& transformations);

	/**
	 * Add force
	 * @param forceOrigin position of world force
	 * @param force force
	 */
	inline void addForce(const Vector3& forceOrigin, const Vector3& force) {
		if (rigidBody == nullptr) {
			Console::println("Body::addForce(): no rigid body attached");
			return;
		}
		rigidBody->applyForce(
			reactphysics3d::Vector3(force.getX(), force.getY(), force.getZ()),
			reactphysics3d::Vector3(forceOrigin.getX(), forceOrigin.getY(), forceOrigin.getZ())
		);
	}

	/**
	 * Add force to center of mass
	 * @param forceOrigin force
	 */
	inline void addForce(const Vector3& force) {
		if (rigidBody == nullptr) {
			Console::println("Body::addForce(): no rigid body attached");
			return;
		}
		rigidBody->applyForceToCenterOfMass(
			reactphysics3d::Vector3(force.getX(), force.getY(), force.getZ())
		);
	}

	/**
	 * Add torque
	 * @param torque torque
	 */
	inline void addTorque(const Vector3& torque) {
		if (rigidBody == nullptr) {
			Console::println("Body::addTorque(): no rigid body attached");
			return;
		}
		rigidBody->applyTorque(
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
