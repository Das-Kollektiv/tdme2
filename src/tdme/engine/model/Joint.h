#pragma once

#include <string>

#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using tdme::math::Matrix4x4;

using std::wstring;

/** 
 * Joint / Bone
 * @author andreas.drewke
 */
class tdme::engine::model::Joint final
{
private:
	wstring groupId {  };
	Matrix4x4 bindMatrix {  };
public:
	/** 
	 * Associated group or bone id
	 * @return group id
	 */
	const wstring& getGroupId();

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
	Joint(const wstring& groupId);
};
