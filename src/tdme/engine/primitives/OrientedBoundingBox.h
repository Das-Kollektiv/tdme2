// Generated from /tdme/src/tdme/engine/primitives/OrientedBoundingBox.java

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
using tdme::engine::primitives::BoundingBox;
using tdme::math::Vector3;

/** 
 * Oriented Bounding Box
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::OrientedBoundingBox final
	: public BoundingVolume
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

public:
	static Vector3 AABB_AXIS_X;
	static Vector3 AABB_AXIS_Y;
	static Vector3 AABB_AXIS_Z;

public:
	Vector3* getCenter() override;
	float getSphereRadius() override;

	/** 
	 * @return 3 axes
	 */
	array<Vector3, 3>* getAxes();

	/** 
	 * @return half extension
	 */
	Vector3* getHalfExtension();

	/** 
	 * Set up oriented bounding box from bounding box
	 * @param bb
	 */
	void fromBoundingBox(BoundingBox* bb);

	/** 
	 * Set up oriented bounding box from oriented bounding box
	 * @param bb
	 */
	void fromOrientedBoundingBox(OrientedBoundingBox* obb);
	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations) override;
	void update() override;

	/** 
	 * @return oriented bounding box vertices
	 */
	vector<Vector3>* getVertices();

	/** 
	 * @return faces vertices indexes
	 */
	static array<array<int32_t,3>,12>* getFacesVerticesIndexes();
	void computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint) override;

	/** 
	 * Computes nearest point on obb face from point in obb
	 * @param point in obb
	 * @param point on face
	 */
	void computeNearestPointOnFaceBoundingVolume(Vector3* pointInObb, Vector3* pointOnFace);

	/** 
	 * Computes nearest point on obb face from point in obb on given axis
	 * @param axis idx
	 * @param point in obb
	 * @param point on face
	 */
	void computeNearestPointOnFaceBoundingVolumeAxis(int32_t axisIdx, Vector3* pointInObb, Vector3* pointOnFace);

	/** 
	 * Computes nearest point on obb face from point in obb
	 * @param point in obb
	 * @param point on face
	 */
	void computeOppositePointOnFaceBoundingVolume(Vector3* pointInObb, Vector3* pointOnFace);

	/** 
	 * Computes nearest point on obb face from point in obb on given axis
	 * @param axis idx
	 * @param point in obb
	 * @param point on face
	 */
	void computeOppositePointOnFaceBoundingVolumeAxis(int32_t axisIdx, Vector3* pointInObb, Vector3* pointOnFace);
	bool containsPoint(Vector3* point) override;
	bool doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision) override;
	float computeDimensionOnAxis(Vector3* axis) override;
	BoundingVolume* clone() override;

	/**
	 * Public constructor
	 * @param center
	 * @param axis0
	 * @param axis1
	 * @param axis2
	 * @param half extension
	 */
	OrientedBoundingBox(Vector3* center, Vector3* axis0, Vector3* axis1, Vector3* axis2, Vector3* halfExtension);

	/**
	 * Public constructor
	 * @param bounding box
	 */
	OrientedBoundingBox(BoundingBox* bb);

	/**
	 * Public constructor
	 */
	OrientedBoundingBox();

private:
	Vector3 center {  };
	array<Vector3, 3> axes {  };
	Vector3 halfExtension {  };
	vector<Vector3> vertices {  };
	float sphereRadius {  };

};
