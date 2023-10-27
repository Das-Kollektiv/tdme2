#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>

using std::vector;

using tdme::engine::model::RotationOrder;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;

/**
 * Animation entity
 * @author andreas.drewke
 */
class tdme::engine::model::Animation final
{
private:
	vector<Transform> transforms;

public:
	// forbid class copy
	FORBID_CLASS_COPY(Animation)

	/**
	 * Public constructor
	 * @param frames frames
	 */
	Animation();

	/**
	 * @return number of frames
	 */
	inline int getFrames() const {
		return transforms.size();
	}

	/**
	 * Returns transform matrices
	 * @return transform matrices
	 */
	inline const vector<Transform>& getTransforms() const {
		return transforms;
	}

	/**
	 * Set transforms
	 * @param transforms transforms
	 */
	inline void setTransforms(const vector<Transform>& transforms) {
		this->transforms.resize(transforms.size());
		auto i = 0;
		for (const auto& transform: transforms) {
			this->transforms[i++] = transform;
		}
	}

	/**
	 * Set transform matrices
	 * @param transformMatrices transform matrices
	 */
	inline void setTransformMatrices(const vector<Matrix4x4>& transformMatrices) {
		transforms.resize(transformMatrices.size());
		auto i = 0;
		for (const auto& matrix: transformMatrices) {
			transforms[i++].fromMatrix(matrix, RotationOrder::ZYX);
		}
	}

	/**
	 * Get transform matrices
	 * @return transformMatrices transform matrices
	 */
	inline const vector<Matrix4x4> getTransformMatrices() const {
		vector<Matrix4x4> transformMatrices(transforms.size());
		auto i = 0;
		for (const auto& matrix: transformMatrices) {
			transformMatrices[i] = transforms[i++].getTransformMatrix();
		}
		return transformMatrices;
	}

};
