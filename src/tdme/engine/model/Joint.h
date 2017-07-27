// Generated from /tdme/src/tdme/engine/model/Joint.java

#pragma once

#include <string>

#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using java::lang::Object;
using java::lang::String;
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
	Matrix4x4* bindMatrix {  };
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
	Matrix4x4* getBindMatrix();

	/**
	 * Public constructor
	 */
	Joint(const wstring& groupId);
};
