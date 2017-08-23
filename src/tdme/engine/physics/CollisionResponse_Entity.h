// Generated from /tdme/src/tdme/engine/physics/CollisionResponse.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;

using tdme::engine::physics::CollisionResponse;
using tdme::math::Vector3;

/** 
 * Collision Response Entity
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::CollisionResponse_Entity final
{
	friend class CollisionResponse;

public: /* protected */
	float distance {  };
	Vector3 normal {  };
	vector<Vector3> hitPoints {  };

public:

	/** 
	 * @return distance
	 */
	float getDistance();

	/** 
	 * Set distance
	 * @param distance
	 */
	void setDistance(float distance);

	/** 
	 * @return penetration
	 */
	float getPenetration();

	/** 
	 * @return normal
	 */
	Vector3* getNormal();

	/** 
	 * Adds a hit point
	 * @param hit point
	 */
	void addHitPoint(Vector3* hitPoint);

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

	/**
	 * Public constructor
	 */
	CollisionResponse_Entity();
};
