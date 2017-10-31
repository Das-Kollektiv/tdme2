
#pragma once

#include <array>
#include <vector>

#include <tdme/tdme.h>
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
	static const array<int32_t, 3> FACE0_INDICES;
	static const array<int32_t, 3> FACE1_INDICES;
	static const array<int32_t, 3> FACE2_INDICES;
	static const array<int32_t, 3> FACE3_INDICES;
	static const array<int32_t, 3> FACE4_INDICES;
	static const array<int32_t, 3> FACE5_INDICES;
	static const array<int32_t, 3> FACE6_INDICES;
	static const array<int32_t, 3> FACE7_INDICES;
	static const array<int32_t, 3> FACE8_INDICES;
	static const array<int32_t, 3> FACE9_INDICES;
	static const array<int32_t, 3> FACE10_INDICES;
	static const array<int32_t, 3> FACE11_INDICES;
	static const array<array<int32_t,3>,12> facesVerticesIndexes;

public:
	static const Vector3 AABB_AXIS_X;
	static const Vector3 AABB_AXIS_Y;
	static const Vector3 AABB_AXIS_Z;

public:
	inline Vector3& getCenter() override {
		return center;
	}

	inline float getSphereRadius() const override {
		return sphereRadius;
	}

	/** 
	 * @return 3 axes
	 */
	const array<Vector3, 3>* getAxes() const;

	/** 
	 * @return half extension
	 */
	Vector3& getHalfExtension();

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
	inline const vector<Vector3>* getVertices() const {
		return &vertices;
	}

	/** 
	 * @return faces vertices indexes
	 */
	inline static const array<array<int32_t,3>,12>* getFacesVerticesIndexes() {
		return &facesVerticesIndexes;
	}

	void computeClosestPointOnBoundingVolume(const Vector3& point, Vector3& closestPoint) const override;

	/** 
	 * Computes nearest point on obb face from point in obb
	 * @param point in obb
	 * @param point on face
	 */
	void computeNearestPointOnFaceBoundingVolume(const Vector3& pointInObb, Vector3& pointOnFace) const;

	/** 
	 * Computes nearest point on obb face from point in obb on given axis
	 * @param axis idx
	 * @param point in obb
	 * @param point on face
	 */
	void computeNearestPointOnFaceBoundingVolumeAxis(int32_t axisIdx, const Vector3& pointInObb, Vector3& pointOnFace) const;

	/** 
	 * Computes nearest point on obb face from point in obb
	 * @param point in obb
	 * @param point on face
	 */
	void computeOppositePointOnFaceBoundingVolume(const Vector3& pointInObb, Vector3& pointOnFace) const;

	/** 
	 * Computes nearest point on obb face from point in obb on given axis
	 * @param axis idx
	 * @param point in obb
	 * @param point on face
	 */
	void computeOppositePointOnFaceBoundingVolumeAxis(int32_t axisIdx, const Vector3& pointInObb, Vector3& pointOnFace) const;
	bool containsPoint(const Vector3& point) const override;
	bool doesCollideWith(BoundingVolume* bv2, const Vector3& movement, CollisionResponse* collision) override;
	float computeDimensionOnAxis(const Vector3& axis) const override;
	BoundingVolume* clone() const override;

	/**
	 * Public constructor
	 * @param center
	 * @param axis0
	 * @param axis1
	 * @param axis2
	 * @param half extension
	 */
	OrientedBoundingBox(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension);

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
