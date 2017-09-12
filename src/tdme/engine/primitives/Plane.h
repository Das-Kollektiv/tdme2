// Generated from /tdme/src/tdme/engine/primitives/Plane.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using tdme::math::Vector3;

/** 
 * Plane
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::Plane final
{
private:
	Vector3 normal {  };
	float distance {  };
public:
	/** 
	 * @return float distance from origin
	 */
	inline float getDistance() {
		return distance;
	}

	/** 
	 * Set up distance from origin
	 * @param distance
	 */
	inline void setDistance(float distance) {
		this->distance = distance;
	}

	/** 
	 * @return normal
	 */
	inline Vector3* getNormal() {
		return &normal;
	}

	/**
	 * Public constructor
	 */
	inline Plane() {
		normal.set(0.0f, 0.0f, 0.0f);
		distance = 0.0f;
	}

	/**
	 * Public constructor
	 * @param normal
	 * @param distance
	 */
	inline Plane(Vector3* normal, float distance) {
		this->normal.set(normal);
		this->distance = distance;
	}
};
