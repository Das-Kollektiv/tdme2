#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Vector3.h>

using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;

/** 
 * Sphere
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::Sphere final
	: public BoundingVolume
{
private:
	float radius {  };

public:
	/** 
	 * @return float radius
	 */
	float getRadius() const;

	// overrides
	BoundingVolume* clone() const override;

	/**
	 * Public constructor
	 */
	Sphere();

	/**
	 * Public constructor
	 * @param center
	 * @param radius
	 */
	Sphere(const Vector3& center, float radius);

};
