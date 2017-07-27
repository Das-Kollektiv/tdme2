// Generated from /tdme/src/tdme/engine/model/Joint.java
#include <tdme/engine/model/Joint.h>

#include <tdme/math/Matrix4x4.h>

using tdme::engine::model::Joint;
using tdme::math::Matrix4x4;

Joint::Joint(const wstring& groupId)
{
	this->groupId = groupId;
	this->bindMatrix = (new Matrix4x4())->identity();
}

const wstring& Joint::getGroupId()
{
	return groupId;
}

Matrix4x4* Joint::getBindMatrix()
{
	return bindMatrix;
}

