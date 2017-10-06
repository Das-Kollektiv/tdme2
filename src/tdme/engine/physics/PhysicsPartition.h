
#pragma once

#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/engine/physics/RigidBody.h>
#include <tdme/utils/ArrayListIteratorMultiple.h>

using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::ArrayListIteratorMultiple;

/** 
 * Physics partition interface
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::PhysicsPartition
{
public: /* protected */

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

public:

	/** 
	 * Get objects near to
	 * @param cbv
	 * @return objects near to cbv
	 */
	virtual ArrayListIteratorMultiple<RigidBody*>* getObjectsNearTo(BoundingVolume* cbv) = 0;

	/** 
	 * Get objects near to
	 * @param cbv
	 * @return objects near to cbv
	 */
	virtual ArrayListIteratorMultiple<RigidBody*>* getObjectsNearTo(const Vector3& center) = 0;
};
