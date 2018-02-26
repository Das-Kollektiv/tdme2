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
	 * Event fired when rigid body was added
	 */
	virtual void onAddedRigidBody(const string& id, bool enabled, int32_t typeId, const Transformations& transformations, BoundingVolume* obv, float restitution, float friction, float mass, const RigidBody::InertiaMatrixSettings& inertiaMatrix) = 0;

	/** 
	 * Event fired when rigid body was removed
	 */
	virtual void onRemovedRigidBody(const string& id) = 0;

};
