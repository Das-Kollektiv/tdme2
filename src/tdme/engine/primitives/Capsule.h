#pragma once

#include <ext/reactphysics3d/src/collision/shapes/ConvexMeshShape.h>

#include <tdme/math/Vector3.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/ConvexMeshBoundingVolume.h>
#include <tdme/engine/primitives/ConvexMesh.h>

using tdme::engine::primitives::ConvexMeshBoundingVolume;
using tdme::math::Vector3;

/** 
 * Capsule primitive
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::Capsule final
	: public ConvexMeshBoundingVolume
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
	/**
	 * Create convex mesh
	 */
	void createConvexMesh();

	//
	Vector3 a {  };
	Vector3 b {  };
	float radius {  };

};
