// Generated from /tdme/src/tdme/engine/model/Skinning.java
#include <tdme/engine/model/Skinning.h>

#include <map>
#include <string>
#include <vector>

#include <java/io/Serializable.h>
#include <java/lang/Cloneable.h>
#include <java/lang/Float.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::map;
using std::wstring;
using std::vector;

using tdme::engine::model::Skinning;
using java::lang::Float;
using java::util::Arrays;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;

Skinning::Skinning() 
{
}

vector<float>* Skinning::getWeights()
{
	return &weights;
}

void Skinning::setWeights(const vector<float>& weights)
{
	this->weights.resize(weights.size());
	int i = 0;
	for (float weight: weights) {
		this->weights[i++] = weight;
	}
}

vector<Joint*>* Skinning::getJoints()
{
	return &joints;
}

void Skinning::setJoints(const vector<Joint*>& joints)
{
	this->joints.resize(joints.size());
	int i = 0;
	for (auto joint: joints) {
		this->joints[i++] = joint;
	}
	setupJointsByName();
}

vector<vector<JointWeight*>>* Skinning::getVerticesJointsWeights()
{
	return &verticesJointsWeights;
}

void Skinning::setVerticesJointsWeights(const vector<vector<JointWeight*>>* verticesJointsWeights)
{
	this->verticesJointsWeights.resize(verticesJointsWeights->size());
	for (auto i = 0; i < verticesJointsWeights->size(); i++) {
		this->verticesJointsWeights[i].resize(verticesJointsWeights->at(i).size());
		for (auto j = 0; j < verticesJointsWeights->at(i).size(); j++) {
			this->verticesJointsWeights[i][j] = verticesJointsWeights->at(i).at(j);
		}
	}
}

void Skinning::setupJointsByName()
{
	for (auto i = 0; i < joints.size(); i++) {
		auto joint = joints[i];
		jointsByName[joint->getGroupId()] = joint;
	}
}

Joint* Skinning::getJointByName(const wstring& name)
{
	auto jointIt = jointsByName.find(name);
	if (jointIt != jointsByName.end()) {
		return jointIt->second;
	}
	return nullptr;
}
