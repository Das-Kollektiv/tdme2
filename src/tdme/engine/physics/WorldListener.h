#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/Transform.h>

using std::string;
using std::vector;

using tdme::engine::physics::Body;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Transform;

/**
 * World listener which is about notifying adding or removing bodies
 * @author Andreas Drewke
 */
struct tdme::engine::physics::WorldListener
{

	/**
	 * Destructor
	 */
	virtual ~WorldListener() {}

	/**
	 * Event fired when rigid body was added
	 * @param id id
	 * @param type body type
	 * @param enabled enabled
	 * @param collisionTypeId collision type id
	 * @param transform transform
	 * @param restitution restitution
	 * @param friction friction
	 * @param mass mass
	 * @param inertiaTensor inertia tensor
	 * @param boundingVolumes bounding volumes
	 */
	virtual void onAddedBody(const string& id, Body::BodyType type, bool enabled, uint16_t collisionTypeId, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*>& boundingVolumes) = 0;

	/**
	 * Event fired when rigid body was removed
	 * @param id id
	 * @param type rigid body type
	 * @param collisionTypeId collision type id
	 */
	virtual void onRemovedBody(const string& id, Body::BodyType type, uint16_t collisionTypeId) = 0;

};
