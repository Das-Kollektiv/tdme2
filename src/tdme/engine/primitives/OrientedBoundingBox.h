#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Vector3.h>

using std::array;

using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;

/**
 * Oriented bounding box physics primitive
 * @author Andreas Drewke
 */
class tdme::engine::primitives::OrientedBoundingBox final
	: public BoundingVolume
{
private:
	STATIC_DLL_IMPEXT static const array<int32_t, 3> FACE0_INDICES;
	STATIC_DLL_IMPEXT static const array<int32_t, 3> FACE1_INDICES;
	STATIC_DLL_IMPEXT static const array<int32_t, 3> FACE2_INDICES;
	STATIC_DLL_IMPEXT static const array<int32_t, 3> FACE3_INDICES;
	STATIC_DLL_IMPEXT static const array<int32_t, 3> FACE4_INDICES;
	STATIC_DLL_IMPEXT static const array<int32_t, 3> FACE5_INDICES;
	STATIC_DLL_IMPEXT static const array<int32_t, 3> FACE6_INDICES;
	STATIC_DLL_IMPEXT static const array<int32_t, 3> FACE7_INDICES;
	STATIC_DLL_IMPEXT static const array<int32_t, 3> FACE8_INDICES;
	STATIC_DLL_IMPEXT static const array<int32_t, 3> FACE9_INDICES;
	STATIC_DLL_IMPEXT static const array<int32_t, 3> FACE10_INDICES;
	STATIC_DLL_IMPEXT static const array<int32_t, 3> FACE11_INDICES;
	STATIC_DLL_IMPEXT static const array<array<int32_t,3>,12> facesVerticesIndexes;

	// overriden methods
	void destroyCollisionShape() override;
	void createCollisionShape(World* world) override;

public:
	STATIC_DLL_IMPEXT static const Vector3 AABB_AXIS_X;
	STATIC_DLL_IMPEXT static const Vector3 AABB_AXIS_Y;
	STATIC_DLL_IMPEXT static const Vector3 AABB_AXIS_Z;

	/**
	 * Public constructor
	 * @param center center
	 * @param axis0 axis0
	 * @param axis1 axis1
	 * @param axis2 axis2
	 * @param halfExtension half extension
	 * @param scale scale
	 */
	OrientedBoundingBox(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension, const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f));

	/**
	 * Public constructor
	 * @param bb bounding box
	 * @param scale scale
	 */
	OrientedBoundingBox(BoundingBox* bb, const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f));

	/**
	 * Public constructor
	 */
	OrientedBoundingBox();

	/**
	 * Public destructor
	 */
	~OrientedBoundingBox();

	/**
	 * @return 3 axes
	 */
	const array<Vector3, 3>& getAxes() const;

	/**
	 * @return half extension
	 */
	const Vector3& getHalfExtension() const;

	/**
	 * Set up oriented bounding box from oriented bounding box
	 * @param scale bb
	 */

	// overrides
	void setScale(const Vector3& scale) override;
	BoundingVolume* clone() const override;

	/**
	 * @return oriented bounding box vertices
	 */
	const array<Vector3, 8> getVertices() const;

	/**
	 * @return faces vertices indexes
	 */
	static const array<array<int32_t,3>,12>& getFacesVerticesIndexes();

private:
	array<Vector3, 3> axes;
	Vector3 halfExtension;
};
