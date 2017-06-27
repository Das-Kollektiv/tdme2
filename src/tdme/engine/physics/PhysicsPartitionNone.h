// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionNone.java

#pragma once

#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/physics/PhysicsPartition.h>

using tdme::engine::physics::PhysicsPartition;
using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::ArrayListIteratorMultiple;
using tdme::utils::_ArrayList;


struct default_init_tag;

/** 
 * Partition none implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::PhysicsPartitionNone final
	: public PhysicsPartition
{

public:
	typedef PhysicsPartition super;

private:
	_ArrayList* bodies {  };
	ArrayListIteratorMultiple* arrayListIteratorMultiple {  };
protected:

	/** 
	 * Constructor
	 */
	void ctor();

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
	 * Get objects near to
	 * @param cbv
	 * @return objects near to cbv
	 */
	ArrayListIteratorMultiple* getObjectsNearTo(BoundingVolume* cbv) override;

	/** 
	 * Get objects near to
	 * @param cbv
	 * @return objects near to cbv
	 */
	ArrayListIteratorMultiple* getObjectsNearTo(Vector3* center) override;

	// Generated

public: /* protected */
	PhysicsPartitionNone();
protected:
	PhysicsPartitionNone(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
