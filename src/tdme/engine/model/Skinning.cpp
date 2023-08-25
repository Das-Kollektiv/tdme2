#include <tdme/engine/model/Skinning.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Skinning;

Skinning::Skinning()
{
}

void Skinning::setWeights(const vector<float>& weights)
{
	this->weights.resize(weights.size());
	auto i = 0;
	for (float weight: weights) {
		this->weights[i++] = weight;
	}
}

void Skinning::setJoints(const vector<Joint>& joints)
{
	this->joints.resize(joints.size());
	auto i = 0;
	for (const auto& joint: joints) {
		this->joints[i++] = joint;
	}
	setupJointsByNodeIds();
}

void Skinning::setVerticesJointsWeights(const vector<vector<JointWeight>>& verticesJointsWeights)
{
	this->verticesJointsWeights.resize(verticesJointsWeights.size());
	for (auto i = 0; i < verticesJointsWeights.size(); i++) {
		this->verticesJointsWeights[i].resize(verticesJointsWeights[i].size());
		for (auto j = 0; j < verticesJointsWeights[i].size(); j++) {
			this->verticesJointsWeights[i][j] = verticesJointsWeights[i][j];
		}
	}
}

void Skinning::setupJointsByNodeIds()
{
	jointsByNodeIds.clear();
	for (auto& joint: joints) {
		jointsByNodeIds[joint.getNodeId()] = &joint;
	}
}
