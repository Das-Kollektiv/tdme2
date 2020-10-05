#pragma once

#include <string>

#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using tdme::math::Matrix4x4;

using std::string;

/**
 * Joint / Bone
 * @author andreas.drewke
 */
class tdme::engine::model::Joint final
{
private:
	string groupId;
	Matrix4x4 bindMatrix;
public:
	/**
	 * Public constructor
	 */
	Joint();

	/**
	 * Public constructor
	 * @param groupId group id
	 */
	Joint(const string& groupId);

	/**
	 * Associated group or bone id
	 * @return group id
	 */
	inline const string& getGroupId() const {
		return groupId;
	}

	/**
	 * Bind matrix
	 * @return matrix
	 */
	inline const Matrix4x4& getBindMatrix() const {
		return bindMatrix;
	}

	/**
	 * Bind matrix
	 * @return matrix
	 */
	inline void setBindMatrix(const Matrix4x4& bindMatrix) {
		this->bindMatrix = bindMatrix;
	}

};
