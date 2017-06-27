// Generated from /tdme/src/tdme/engine/physics/PhysicsPartition.java

#pragma once

#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::ArrayListIteratorMultiple;


struct default_init_tag;

/** 
 * Physics partition interface
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::PhysicsPartition
	: public virtual Object
{

public:
	typedef Object super;

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
	virtual ArrayListIteratorMultiple* getObjectsNearTo(BoundingVolume* cbv) = 0;

	/** 
	 * Get objects near to
	 * @param cbv
	 * @return objects near to cbv
	 */
	virtual ArrayListIteratorMultiple* getObjectsNearTo(Vector3* center) = 0;

	// Generated
	PhysicsPartition();
protected:
	PhysicsPartition(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
