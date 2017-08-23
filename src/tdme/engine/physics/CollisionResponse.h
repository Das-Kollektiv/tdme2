// Generated from /tdme/src/tdme/engine/physics/CollisionResponse.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/CollisionResponse_Entity.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;

using tdme::engine::physics::CollisionResponse_Entity;
using tdme::math::Vector3;

/** 
 * Collision response
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::CollisionResponse final
{
	friend class CollisionResponse_Entity;

public: /* protected */
	static constexpr int32_t HITPOINT_COUNT { 30 };
	vector<CollisionResponse_Entity> entities {  };
	CollisionResponse_Entity* selectedEntity {  };

public:

	/** 
	 * Reset
	 */
	void reset();

	/** 
	 * Adds a collision response entity 
	 * @param distance
	 * @return Entity or null
	 */
	CollisionResponse_Entity* addResponse(float distance);

	/** 
	 * @return entity count
	 */
	int32_t getEntityCount();

	/** 
	 * @return selected entity
	 */
	CollisionResponse_Entity* getSelectedEntity();

	/** 
	 * Selects entity at given index
	 * @param idx
	 * @return
	 */
	CollisionResponse_Entity* getEntityAt(int32_t idx);

	/** 
	 * Selects entity at given index
	 * @param idx
	 * @return
	 */
	CollisionResponse* selectEntityAt(int32_t idx);

	/** 
	 * Select entity with least penetration but exclude given axis
	 * @param axis
	 * @param respect direction
	 * @return
	 */
	CollisionResponse* selectEntityExcludeAxis(Vector3* axis, bool respectDirection);

	/** 
	 * Select entity on given axis with least penetration
	 * @param axis
	 * @param respect direction
	 * @return
	 */
	CollisionResponse* selectEntityOnAxis(Vector3* axis, bool respectDirection);
	bool hasEntitySelected();
	float getDistance();
	bool hasPenetration();
	float getPenetration();
	Vector3* getNormal();

	/** 
	 * @return hit points count
	 */
	int32_t getHitPointsCount();

	/** 
	 * Get hit point of given index 
	 * @param i
	 * @return hit point for given hit points index
	 */
	Vector3* getHitPointAt(int32_t i);

public: /* protected */

	/** 
	 * Invert normals
	 */
	void invertNormals();

public:

	/** 
	 * Set up response from given collision response
	 * @param response
	 */
	CollisionResponse* fromResponse(CollisionResponse* response);

	/** 
	 * Set up response from given collision response
	 * @param response
	 */
	CollisionResponse* mergeResponse(CollisionResponse* response);

	/**
	 * Public constructor
	 * @param distance
	 * @param normal
	 */
	CollisionResponse();
};
