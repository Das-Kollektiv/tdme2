#pragma once

#include <array>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using std::array;
using std::vector;

using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::math::Vector3;

/** 
 * Axis aligned bounding box used for frustum, this is not directly connectable with physics engine
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::BoundingBox
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
	Vector3 min {  };
	Vector3 max {  };
	vector<Vector3> vertices {  };
	Vector3 center;
	Vector3 dimensions;

public:

	/** 
	 * @return min x,y,z vertex
	 */
	inline Vector3& getMin() {
		return min;
	}

	/** 
	 * @return max x,y,z vertex
	 */
	inline Vector3& getMax() {
		return max;
	}

	/** 
	 * Returns bounding box vertices
	 * @return vertices
	 */
	const vector<Vector3>* getVertices() const {
		return &vertices;
	}

	/**
	 * @return faces vertices indexes
	 */
	inline static const array<array<int32_t,3>,12>* getFacesVerticesIndexes() {
		return &facesVerticesIndexes;
	}

	/**
	 * @return center
	 */
	inline const Vector3& getCenter() const {
		return center;
	}

	/**
	 * @return half extension
	 */
	inline const Vector3& getDimensions() const {
		return dimensions;
	}

	/**
	 * Set up this bounding volume from given bounding volume
	 * @param original original bounding box
	 */
	void fromBoundingVolume(BoundingBox* original);

	/**
	 * Create bounding volume from given original(of same type) with applied transformations
	 * @param original original bounding box
	 * @param transformations transformations
	 */
	void fromBoundingVolumeWithTransformations(BoundingBox* original, const Transformations& transformations);

	/**
	 * Updates this bounding box
	 */
	void update();

	/**
	 * Public constructor
	 */
	BoundingBox();

	/**
	 * Public constructor
	 * @param boundingBox bounding box
	 */
	BoundingBox(BoundingBox* boundingBox);

	/**
	 * Public constructor
	 * @param min min
	 * @param max max
	 */
	BoundingBox(const Vector3& min, const Vector3& max);

};
