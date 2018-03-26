#pragma once

#include <string>

#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/fwd-tdme.h>

using std::string;

using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingVolume;

/** 
 * World listener
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::physics::WorldListener
{

	/**
	 * Destructor
	 */
	virtual ~WorldListener() {}

	/** 
	 * Event fired when rigid body was added
	 * @param id
	 * @param type id
	 * @param transformations
	 * @param obv
	 * @param cbv
	 * @oaram restitution
	 * @param friction
	 * @param mass
	 * @param inertia matrix
	 */
	virtual void onAddedRigidBody(const string& id, bool enabled, int32_t typeId, const Transformations& transformations, BoundingVolume* obv, BoundingVolume* cbv, float restitution, float friction, float mass, const RigidBody::InertiaMatrixSettings& inertiaMatrix) = 0;

	/** 
	 * Event fired when rigid body was removed
	 * @param id
	 * @param type id
	 * @param obv
	 * @param cbv
	 */
	virtual void onRemovedRigidBody(const string& id, int32_t typeId, BoundingVolume* obv, BoundingVolume* cbv) = 0;

};
