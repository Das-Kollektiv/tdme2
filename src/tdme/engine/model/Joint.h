#pragma once

#include <string>

#include <tdme/tdme.h>
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
	string nodeId;
	Matrix4x4 bindMatrix;

public:
	/**
	 * Public constructor
	 */
	Joint();

	/**
	 * Public constructor
	 * @param nodeId node id
	 */
	Joint(const string& nodeId);

	/**
	 * Associated node or bone id
	 * @returns node id
	 */
	inline const string& getNodeId() const {
		return nodeId;
	}

	/**
	 * Bind matrix
	 * @returns matrix
	 */
	inline const Matrix4x4& getBindMatrix() const {
		return bindMatrix;
	}

	/**
	 * Bind matrix
	 * @returns matrix
	 */
	inline void setBindMatrix(const Matrix4x4& bindMatrix) {
		this->bindMatrix = bindMatrix;
	}

};
