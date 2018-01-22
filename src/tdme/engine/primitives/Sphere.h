#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/ConvexMeshBoundingVolume.h>
#include <tdme/math/Vector3.h>

using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;

/** 
 * Sphere
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::Sphere final
	: public ConvexMeshBoundingVolume
{
private:
	Vector3 center {  };
	float radius {  };

	/**
	 * Create convex mesh
	 */
	void createConvexMesh();

public:

	/**
	 * @return center
	 */
	const Vector3& getCenter() const;

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
