#pragma once

#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/engine/physics/RigidBody.h>
#include <tdme/utils/VectorIteratorMultiple.h>

using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::VectorIteratorMultiple;

/** 
 * Physics partition interface
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::physics::PhysicsPartition
{

	/** 
	 * Reset
	 */
	virtual void reset() = 0;

	/** 
	 * Adds a object
	 * @param rigidBody
	 */
	virtual void addRigidBody(RigidBody* rigidBody) = 0;

	/** 
	 * Updates a object
	 * @param rigidBody
	 */
	virtual void updateRigidBody(RigidBody* rigidBody) = 0;

	/** 
	 * Removes a rigidBody
	 * @param rigidBody
	 */
	virtual void removeRigidBody(RigidBody* rigidBody) = 0;

	/** 
	 * Get objects near to rigid body
	 * @param cbv
	 * @return objects near to cbv
	 */
	virtual VectorIteratorMultiple<RigidBody*>* getObjectsNearTo(RigidBody* rigidBody) = 0;

	/**
	 * Get objects near to
	 * @param cbv
	 * @return objects near to cbv
	 */
	virtual VectorIteratorMultiple<RigidBody*>* getObjectsNearTo(BoundingVolume* cbv) = 0;

	/** 
	 * Get objects near to
	 * @param cbv
	 * @return objects near to cbv
	 */
	virtual VectorIteratorMultiple<RigidBody*>* getObjectsNearTo(const Vector3& center, const Vector3& halfExtension = Vector3(0.1f, 0.1f, 0.01f)) = 0;

	/**
	 * Destructor
	 */
	virtual ~PhysicsPartition() {}

};
