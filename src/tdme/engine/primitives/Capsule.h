#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Vector3.h>

using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;

/** 
 * Capsule primitive
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::Capsule final
	: public BoundingVolume
{
public:
	/** 
	 * @return radius
	 */
	float getRadius() const;

	/** 
	 * @return line segment point a
	 */
	const Vector3& getA() const;

	/** 
	 * @return line segment point b
	 */
	const Vector3& getB() const;

	// overrides
	BoundingVolume* clone() const override;

	/**
	 * Public constructor
	 * @param a
	 * @param b
	 * @param radius
	 */
	Capsule(const Vector3& a, const Vector3& b, float radius);

private:
	//
	Vector3 a {  };
	Vector3 b {  };
	float radius {  };

};
