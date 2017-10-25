#include <tdme/engine/model/Joint.h>

#include <tdme/math/Matrix4x4.h>

using tdme::engine::model::Joint;
using tdme::math::Matrix4x4;

Joint::Joint()
{
	this->groupId = "";
	this->bindMatrix.identity();
}

Joint::Joint(const string& groupId)
{
	this->groupId = groupId;
	this->bindMatrix.identity();
}

const string& Joint::getGroupId()
{
	return groupId;
}

Matrix4x4& Joint::getBindMatrix()
{
	return bindMatrix;
}

