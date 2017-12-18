#pragma once

#include <vector>

#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/physics/PhysicsPartition.h>
#include <tdme/engine/physics/RigidBody.h>

using std::vector;

using tdme::engine::physics::PhysicsPartition;
using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::VectorIteratorMultiple;

/** 
 * Partition none implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::PhysicsPartitionNone final
	: public PhysicsPartition
{
private:
	vector<RigidBody*> bodies {  };
	VectorIteratorMultiple<RigidBody*> arrayListIteratorMultiple {  };

public: /* protected */

	/** 
	 * Reset
	 */
	void reset() override;

	/** 
	 * Adds a object
	 * @param rigidBody
	 */
	void addRigidBody(RigidBody* rigidBody) override;

	/** 
	 * Updates a object
	 * @param rigidBody
	 */
	void updateRigidBody(RigidBody* rigidBody) override;

	/** 
	 * Removes a rigidBody
	 * @param rigidBody
	 */
	void removeRigidBody(RigidBody* rigidBody) override;

public:

	/** 
	 * Get objects near to rigid body
	 * @param cbv
	 * @return objects near to cbv
	 */
	virtual VectorIteratorMultiple<RigidBody*>* getObjectsNearTo(RigidBody* rigidBody) override;

	/**
	 * Get objects near to
	 * @param cbv
	 * @return objects near to cbv
	 */
	VectorIteratorMultiple<RigidBody*>* getObjectsNearTo(BoundingVolume* cbv) override;

	/** 
	 * Get objects near to
	 * @param cbv
	 * @return objects near to cbv
	 */
	VectorIteratorMultiple<RigidBody*>* getObjectsNearTo(const Vector3& center) override;

	// Generated

	/**
	 * Constructor
	 */
	PhysicsPartitionNone();
};
