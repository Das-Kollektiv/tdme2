#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/AnimationState.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/fwd-tdme.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::model::Animation;
using tdme::engine::model::Joint;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::subsystems::rendering::AnimationState;
using tdme::engine::Engine;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;

/**
 * Object animation class
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::ObjectAnimation
{
	friend class tdme::engine::subsystems::rendering::ModelUtilitiesInternal;
	friend class tdme::engine::subsystems::rendering::ObjectBase;
	friend class tdme::engine::subsystems::rendering::ObjectNode;
	friend class tdme::engine::subsystems::rendering::ObjectInternal;
private:
	/**
	 * Determine skinned node count
	 * @param nodes nodes
	 */
	int32_t determineSkinnedNodeCount(const map<string, Node*>& nodes);

	/**
	 * Determine skinned node count
	 * @param nodes nodes
	 * @param count current count
	 */
	int32_t determineSkinnedNodeCount(const map<string, Node*>& nodes, int32_t count);

	/**
	 * Determine skinned nodes
	 * @param nodes nodes
	 * @param skinningNodes skinning nodes
	 * @param idx idx
	 */
	int32_t determineSkinnedNodes(const map<string, Node*>& nodes, vector<Node*>& skinningNodes, int32_t idx);

protected:
	struct FlattenedNode {
		const string nodeId;
		const Matrix4x4* nodeTransformMatrix;
		Matrix4x4* nodeOverriddenTransformMatrix;
		const Animation* nodeAnimation;
		AnimationState* nodeAnimationState;
		const Matrix4x4* parentTransformMatrix;
		Matrix4x4* transformMatrix;
	};
	struct NodeSkinningJoint {
		const Joint* joint;
		const Matrix4x4* nodeTransformMatrix;
		Matrix4x4* skinningNodeTransformMatrix;
	};

	Model* model;
	Engine::AnimationProcessingTarget animationProcessingTarget;
	map<string, Matrix4x4*> overriddenTransformMatrices;
	vector<map<string, Matrix4x4*>> transformMatrices;
	bool hasSkinning;
	bool hasAnimations;
	vector<map<string, Matrix4x4*>> skinningNodesMatrices;
	vector<Node*> skinningNodes;
	vector<vector<NodeSkinningJoint>> skinningNodesNodeSkinningJoints;
	vector<AnimationState> baseAnimations;
	int baseAnimationIdx;
	map<string, AnimationState*> overlayAnimationsById;
	map<string, AnimationState*> overlayAnimationsByJointId;
	vector<vector<FlattenedNode>> nodeLists;

	/**
	 * Public constructor
	 * @param model model
	 * @param animationProcessingTarget animation processing target
	 */
	ObjectAnimation(Model* model, Engine::AnimationProcessingTarget animationProcessingTarget);

	/**
	 * Destructor
	 */
	virtual ~ObjectAnimation();

	/**
	 * Creates all nodes transform matrices
	 * @param matrices matrices
	 * @param nodeList flattened node list
	 * @param nodes nodes
	 * @param parentTransformMatrix parent transform matrix
	 * @param animationState animation state
	 */
	void createNodesTransformMatrices(map<string, Matrix4x4*>& matrices, vector<FlattenedNode>& nodeList, const map<string, Node*>& nodes, Matrix4x4* parentTransformMatrix = nullptr, AnimationState* animationState = nullptr);

	/**
	 * Update node list
	 * @param nodeList flattened node list
	 * @param nodeIdx node index
	 * @param nodes nodes
	 * @param animationState animation state
	 */
	void updateNodeList(vector<FlattenedNode>& nodeList, int& nodeIdx, const map<string, Node*>& nodes, AnimationState* animationState = nullptr);

	/**
	 * Update node list
	 * @param nodeList flattened node list
	 */
	inline void updateNodeList(vector<FlattenedNode>& nodeList) {
		auto nodeIdx = 0;
		updateNodeList(nodeList, nodeIdx, model->getSubNodes());
	}

	/**
	 * Update node lists
	 */
	inline void updateNodeLists() {
		for (auto& nodeList: nodeLists) updateNodeList(nodeList);
	}

	/**
	 * Comutes all nodes transform matrices
	 * @param nodeList flattened node list
	 * @param parentTransformMatrix parent transform matrix
	 * @param animationState animation state
	 */
	void computeNodesTransformMatrices(vector<FlattenedNode>& nodeList, const Matrix4x4 parentTransformMatrix, AnimationState* animationState);

	/**
	 * Compute animation for given animation state into nodes transform matrices given by flattened node list
	 * @param nodeList flattened node list
	 * @param instanceTransformMatrix object transform matrix
	 * @param baseAnimation base animation
	 * @param contextIdx context index
	 * @param lastFrameAtTime time of last animation computation
	 * @param currentFrameAtTime time of current animation computation
	 */
	void computeAnimation(vector<FlattenedNode>& nodeList, const Matrix4x4& instanceTransformMatrix, AnimationState& baseAnimation, int contextIdx, int64_t lastFrameAtTime, int64_t currentFrameAtTime);

	/**
	 * Update skinning transform matrices
	 */
	void updateSkinningJoints();

	/**
	 * Get skinning nodes transform matrices
	 * @param node node
	 * @return matrices
	 */
	map<string, Matrix4x4*>* getSkinningNodesTransformMatrices(Node* node);

public:

	/**
	 * Sets up a base animation to play
	 * @param id id
	 * @param speed speed whereas 1.0 is default speed
	 */
	void setAnimation(const string& id, float speed = 1.0f);

	/**
	 * Set up animation speed
	 * @param speed speed whereas 1.0 is default speed
	 */
	void setAnimationSpeed(float speed);

	/**
	 * Overlays a animation above the base animation
	 * @param id id
	 */
	void addOverlayAnimation(const string& id);

	/**
	 * Removes a overlay animation
	 * @param id id
	 */
	void removeOverlayAnimation(const string& id);

	/**
	 * Removes all finished overlay animations
	 */
	void removeFinishedOverlayAnimations();

	/**
	 * Removes all overlay animations
	 */
	void removeOverlayAnimations();

	/**
	 * @return active animation setup id
	 */
	const string getAnimation();

	/**
	 * Returns current base animation time
	 * @return 0.0 <= time <= 1.0
	 */
	float getAnimationTime();

	/**
	 * Returns if there is currently running a overlay animation with given id
	 * @param id id
	 * @return animation is running
	 */
	bool hasOverlayAnimation(const string& id);

	/**
	 * Returns current overlay animation time
	 * @param id id
	 * @return 0.0 <= time <= 1.0
	 */
	float getOverlayAnimationTime(const string& id);

	/**
	 * Returns transform matrix for given node
	 * @param id node id
	 * @return transform matrix or identity matrix if not found
	 */
	const Matrix4x4 getNodeTransformMatrix(const string& id);

	/**
	 * Set transform matrix for given node
	 * @param id node id
	 * @param matrix transform matrix
	 */
	void setNodeTransformMatrix(const string& id, const Matrix4x4& matrix);

	/**
	 * Unset transform matrix for given node
	 * @param id node id
	 */
	void unsetNodeTransformMatrix(const string& id);

	/**
	 * Computes animations
	 * @param contextIdx context index
	 * @param objectTransformMatrix object transform matrix
	 * @param lastFrameAtTime time of last animation computation
	 * @param currentFrameAtTime time of current animation computation
	 */
	void computeAnimation(int contextIdx, const Matrix4x4& objectTransformMatrix, int64_t lastFrameAtTime, int64_t currentFrameAtTime);

};
