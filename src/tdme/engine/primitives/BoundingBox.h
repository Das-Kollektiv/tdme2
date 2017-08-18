// Generated from /tdme/src/tdme/engine/primitives/BoundingBox.java

#pragma once

#include <array>
#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/engine/primitives/BoundingVolume.h>

using std::array;
using std::vector;

using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::math::Vector3;

/** 
 * Axis Aligned Bounding Box
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::BoundingBox final :
	public BoundingVolume
{
private:
	static array<int32_t, 3> FACE0_INDICES;
	static array<int32_t, 3> FACE1_INDICES;
	static array<int32_t, 3> FACE2_INDICES;
	static array<int32_t, 3> FACE3_INDICES;
	static array<int32_t, 3> FACE4_INDICES;
	static array<int32_t, 3> FACE5_INDICES;
	static array<int32_t, 3> FACE6_INDICES;
	static array<int32_t, 3> FACE7_INDICES;
	static array<int32_t, 3> FACE8_INDICES;
	static array<int32_t, 3> FACE9_INDICES;
	static array<int32_t, 3> FACE10_INDICES;
	static array<int32_t, 3> FACE11_INDICES;
	static array<array<int32_t,3>,12> facesVerticesIndexes;
	Vector3 min {  };
	Vector3 max {  };
	Vector3 center {  };
	float sphereRadius {  };
	vector<Vector3> vertices {  };

public:

	/** 
	 * @return min x,y,z vertex
	 */
	Vector3* getMin();

	/** 
	 * @return max x,y,z vertex
	 */
	Vector3* getMax();

	/** 
	 * Returns bounding box vertices
	 * @param bounding box
	 * @return vertices
	 */
	vector<Vector3>* getVertices();

	/** 
	 * @return faces vertices indexes
	 */
	static array<array<int32_t,3>,12>* getFacesVerticesIndexes();
	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations) override;
	void computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint) override;
	bool containsPoint(Vector3* point) override;
	bool doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision) override;
	Vector3* getCenter() override;
	float getSphereRadius() override;
	float computeDimensionOnAxis(Vector3* axis) override;
	void update() override;
	BoundingVolume* clone() override;

	/**
	 * Public constructor
	 */
	BoundingBox();

	/**
	 * Public constructor
	 * @param bounding box
	 */
	BoundingBox(BoundingBox* boundingBox);

	/**
	 * Public constructor
	 * @param min
	 * @param max
	 */
	BoundingBox(Vector3* min, Vector3* max);
};
