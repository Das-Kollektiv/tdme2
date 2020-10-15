#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/subsystems/rendering/Object3DBase.h>
#include <tdme/engine/subsystems/rendering/Object3DGroup.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Matrix4x4.h>

using std::array;

using tdme::engine::model::Group;
using tdme::engine::subsystems::rendering::Object3DBase;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Transformed faces iterator
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::Object3DBase_TransformedFacesIterator
{
private:
	Object3DBase* object3DBase { nullptr };
	Group* group { nullptr };
	array<Vector3, 3> vertices;
	Matrix4x4 matrix;
	int32_t faceCount;
	int32_t faceIdxTotal;
	int32_t faceIdx;
	int32_t object3DGroupIdx;
	int32_t facesEntityIdx;

private:

	/**
	 * Reset
	 */
	void reset();
public:
	/**
	 * Public constructor
	 */
	Object3DBase_TransformedFacesIterator(Object3DBase* object3DBase);

	/**
	 * Return iterator ready to iterate
	 */
	Object3DBase_TransformedFacesIterator* iterator();

	/**
	 * Has next
	 */
	inline bool hasNext() {
		return faceIdxTotal < faceCount;
	}

	/**
	 * Retrieve next triangle
	 * @return next 3 triangle vectors
	 */
	const array<Vector3, 3>& next();

	/**
	 * @return current group
	 */
	inline Group* getGroup() {
		return group;
	}

};
