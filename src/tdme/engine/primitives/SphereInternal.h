#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using tdme::math::Vector3;

/** 
 * Sphere
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::SphereInternal final
{
private:
	Vector3 center {  };
	float radius {  };
public:
	inline Vector3& getCenter() {
		return center;
	}

	/** 
	 * @return float radius
	 */
	float getRadius() const;

	/** 
	 * Set up radius
	 * @param radius
	 */
	void setRadius(float radius);

	/**
	 * Public constructor
	 * @param center
	 * @param radius
	 */
	SphereInternal(const Vector3& center, float radius);
};
