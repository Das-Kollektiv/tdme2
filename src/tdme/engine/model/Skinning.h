#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;

/**
 * Skinning definition for nodes
 * @author andreas.drewke
 */
class tdme::engine::model::Skinning final
{
private:
	vector<float> weights;
	vector<Joint> joints;
	vector<vector<JointWeight>> verticesJointsWeights;
	unordered_map<string, Joint*> jointsByNodeIds;

public:
	// forbid class copy
	FORBID_CLASS_COPY(Skinning)

	/**
	 * Public constructor
	 */
	Skinning();

	/**
	 * @returns weights
	 */
	inline const vector<float>& getWeights() {
		return weights;
	}

	/**
	 * Set up weights
	 * @param weights weights
	 */
	void setWeights(const vector<float>& weights);

	/**
	 * @returns all joints
	 */
	inline const vector<Joint>& getJoints() {
		return joints;
	}

	/**
	 * Set up joints
	 * @param joints joints
	 */
	void setJoints(const vector<Joint>& joints);

	/**
	 * @returns all vertex joints
	 */
	inline const vector<vector<JointWeight>>& getVerticesJointsWeights() {
		return verticesJointsWeights;
	}

	/**
	 * Sets up vertices joints weights
	 * @param verticesJointsWeights verticesJointsWeights
	 */
	void setVerticesJointsWeights(const vector<vector<JointWeight>>& verticesJointsWeights);

	/**
	 * Get joint by node id
	 * @param nodeId node id
	 * @returns joint or nullptr if not found
	 */
	inline Joint* getJointByNodeId(const string& nodeId) {
		auto jointIt = jointsByNodeIds.find(nodeId);
		if (jointIt != jointsByNodeIds.end()) return jointIt->second;
		return nullptr;
	}

private:

	/**
	 * Set up joints by node ids hash map
	 */
	void setupJointsByNodeIds();
};
