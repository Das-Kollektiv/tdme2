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
	 * Event fired when body was added
	 * @param id body id
	 * @param type body type
	 * @param collisionTypeId collision type id
	 * @param enabled enabled
	 * @param transform transform
	 * @param restitution restitution
	 * @param friction friction
	 * @param mass mass
	 * @param inertiaTensor inertia tensor
	 * @param boundingVolumes bounding volumes
	 * @param hierarchy hierarchy
	 */
	virtual void onAddedBody(const string& id, Body::BodyType type, uint16_t collisionTypeId, bool enabled, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*>& boundingVolumes, bool hierarchy = false) = 0;

	/**
	 * Event fired when body was removed
	 * @param id body id
	 * @param type body type
	 * @param collisionTypeId collision type id
	 */
	virtual void onRemovedBody(const string& id, Body::BodyType type, uint16_t collisionTypeId) = 0;

	/**
	 * Event fired when child body was added to a body hierarchy
	 * @param id body id
	 * @param type body type
	 * @param collisionTypeId collision type id
	 * @param subBodyParentId sub body parent id
	 * @param subBodyId sub body id
	 * @param transform transform
	 * @param boundingVolumes bounding volumes
	 */
	virtual void onAddedSubBody(const string& id, Body::BodyType type, uint16_t collisionTypeId, const string& subBodyParentId, const string& subBodyId, const Transform& transform, const vector<BoundingVolume*>& boundingVolumes) = 0;

	/**
	 * Event fired when body was removed
	 * @param id body id
	 * @param type body type
	 * @param collisionTypeId collision type id
	 * @param subBodyParentId sub body parent id
	 * @param subBodyId sub body id
	 */
	virtual void onRemovedSubBody(const string& id, Body::BodyType type, uint16_t collisionTypeId, const string& subBodyParentId, const string& subBodyId) = 0;

};
