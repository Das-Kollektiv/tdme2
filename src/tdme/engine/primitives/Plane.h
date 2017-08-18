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
	float getDistance();

	/** 
	 * Set up distance from origin
	 * @param distance
	 */
	void setDistance(float distance);

	/** 
	 * @return normal
	 */
	Vector3* getNormal();

	/**
	 * Public constructor
	 */
	Plane();

	/**
	 * Public constructor
	 * @param normal
	 * @param distance
	 */
	Plane(Vector3* normal, float distance);
};
