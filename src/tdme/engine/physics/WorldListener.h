#pragma once

#include <string>
#include <vector>

#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/fwd-tdme.h>

using std::string;
using std::vector;

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
	 * @param rigid body type
	 * @param collision type id
	 * @param transformations
	 * @oaram restitution
	 * @param friction
	 * @param mass
	 * @param inertia matrix
	 * @param bounding volumes
	 */
	virtual void onAddedRigidBody(const string& id, int32_t type, bool enabled, uint16_t collisionTypeId, const Transformations& transformations, float restitution, float friction, float mass, const Matrix4x4& inertiaMatrix, vector<BoundingVolume*>& boundingVolumes) = 0;

	/** 
	 * Event fired when rigid body was removed
	 * @param id
	 * @param rigid body type
	 * @param collision type id
	 */
	virtual void onRemovedRigidBody(const string& id, int32_t type, uint16_t collisionTypeId) = 0;

};
