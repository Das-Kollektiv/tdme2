#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using std::vector;

using tdme::math::Matrix4x4;

/**
 * Animation entity
 * @author andreas.drewke
 */
class tdme::engine::model::Animation final
{
private:
	vector<Matrix4x4> transformMatrices;

public:
	// forbid class copy
	CLASS_FORBID_COPY(Animation)

	/**
	 * Public constructor
	 * @param frames frames
	 */
	Animation();

	/**
	 * @return number of frames
	 */
	inline int getFrames() const {
		return transformMatrices.size();
	}

	/**
	 * Returns transform matrices
	 * @return transform matrices
	 */
	inline const vector<Matrix4x4>& getTransformMatrices() const {
		return transformMatrices;
	}

	/**
	 * Set transform matrices
	 * @return transformMatrices transform matrices
	 */
	inline void setTransformMatrices(const vector<Matrix4x4>& transformMatrices) {
		this->transformMatrices = transformMatrices;
	}

};
