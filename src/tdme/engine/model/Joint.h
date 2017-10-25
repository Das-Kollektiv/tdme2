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
	string groupId {  };
	Matrix4x4 bindMatrix {  };
public:
	/** 
	 * Associated group or bone id
	 * @return group id
	 */
	const string& getGroupId();

	/** 
	 * Bind matrix
	 * @return matrix
	 */
	Matrix4x4& getBindMatrix();

	/**
	 * Public constructor
	 */
	Joint();

	/**
	 * Public constructor
	 * @param group id
	 */
	Joint(const string& groupId);
};
