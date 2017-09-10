#include <tdme/engine/model/JointWeight.h>

using tdme::engine::model::JointWeight;

JointWeight::JointWeight()
{
	this->jointIndex = -1;
	this->weightIndex = -1;
}

JointWeight::JointWeight(int32_t jointIndex, int32_t weightIndex) 
{
	this->jointIndex = jointIndex;
	this->weightIndex = weightIndex;
}

int32_t JointWeight::getJointIndex()
{
	return jointIndex;
}

int32_t JointWeight::getWeightIndex()
{
	return weightIndex;
}
