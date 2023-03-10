#include <tdme/engine/subsystems/rendering/ObjectAnimation.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/subsystems/rendering/AnimationState.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::map;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::model::Animation;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Joint;
using tdme::engine::model::Model;
using tdme::engine::model::Skinning;
using tdme::engine::subsystems::rendering::AnimationState;
using tdme::engine::subsystems::rendering::ObjectAnimation;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Console;

ObjectAnimation::ObjectAnimation(Model* model, Engine::AnimationProcessingTarget animationProcessingTarget)
{
	this->animationProcessingTarget = animationProcessingTarget;
	this->model = model;
	// skinning
	hasSkinning = false;
	if (model->hasSkinning() == true) {
		hasSkinning = true;
		skinningNodes.resize(determineSkinnedNodeCount(model->getSubNodes()));
		determineSkinnedNodes(model->getSubNodes(), skinningNodes, 0);
		skinningNodesMatrices.resize(skinningNodes.size());
		for (auto i = 0; i < skinningNodes.size(); i++) {
			vector<FlattenedNode> nodeListIgnored;
			createNodesTransformMatrices(skinningNodesMatrices[i], nodeListIgnored, model->getSubNodes());
		}
	}
	hasAnimations = model->hasAnimations();
	//
	baseAnimationIdx = 0;
	// animation
	setAnimation(Model::ANIMATIONSETUP_DEFAULT);
	// create transform matrices
	transformMatrices.emplace_back();
	nodeLists.emplace_back();
	createNodesTransformMatrices(transformMatrices[0], nodeLists[0], model->getSubNodes());
	// calculate transform matrices
	computeNodesTransformMatrices(nodeLists[0], model->getImportTransformMatrix(), baseAnimations.size() == 0?nullptr:&baseAnimations[0]);
	// skinning ...
	if (hasSkinning == true) {
		for (auto i = 0; i < skinningNodes.size(); i++) {
			skinningNodesNodeSkinningJoints.emplace_back();
			for (auto& skinningJoint: skinningNodes[i]->getSkinning()->getJoints()) {
				auto transformMatrixIt = transformMatrices[0].find(skinningJoint.getNodeId());
				if (transformMatrixIt == transformMatrices[0].end()) continue;
				auto skinningNodeMatrixIt = skinningNodesMatrices[i].find(skinningJoint.getNodeId());
				if (skinningNodeMatrixIt == skinningNodesMatrices[i].end()) continue;
				skinningNodesNodeSkinningJoints[i].emplace_back(
					&skinningJoint,
					transformMatrixIt->second,
					skinningNodeMatrixIt->second
				);
			}
		}
		updateSkinningJoints();
	}
	// reset animation
	if (baseAnimations.size() == 0) baseAnimations.emplace_back();
	baseAnimations[baseAnimationIdx].endAtTime = -1LL;
	baseAnimations[baseAnimationIdx].lastAtTime = Timing::UNDEFINED;
	baseAnimations[baseAnimationIdx].currentAtTime = 0LL;
	baseAnimations[baseAnimationIdx].time = 0.0f;
	baseAnimations[baseAnimationIdx].finished = false;
}

ObjectAnimation::~ObjectAnimation() {
	for (auto baseAnimationTransformMatrices: transformMatrices) {
		for (auto it: baseAnimationTransformMatrices) {
			delete it.second;
		}
	}
	for (auto skinningNodeMatricies: skinningNodesMatrices) {
		for (auto it: skinningNodeMatricies) {
			delete it.second;
		}
	}
	for (auto overriddenTransformMatrixIt: overriddenTransformMatrices) {
		delete overriddenTransformMatrixIt.second;
	}
}

void ObjectAnimation::setAnimation(const string& id, float speed)
{
	auto animationActiveSetup = model->getAnimationSetup(id);

	// only switch animation if we have one
	if (animationActiveSetup != nullptr) {
		if (baseAnimations.size() == 0) {
			baseAnimations.emplace_back(
				animationActiveSetup,
				-1LL,
				0LL,
				Timing::UNDEFINED,
				false,
				0.0f,
				speed
			);
			baseAnimationIdx = 0;
		} else
		if (baseAnimations.size() == 1) {
			baseAnimations.emplace_back(
				animationActiveSetup,
				-1LL,
				0LL,
				Timing::UNDEFINED,
				false,
				0.0f,
				speed
			);
			baseAnimationIdx = 1;
			transformMatrices.emplace_back();
			nodeLists.emplace_back();
			createNodesTransformMatrices(transformMatrices[1], nodeLists[1], model->getSubNodes());
			transformMatrices.emplace_back();
			nodeLists.emplace_back();
			createNodesTransformMatrices(transformMatrices[2], nodeLists[2], model->getSubNodes());
		} else {
			baseAnimationIdx = (baseAnimationIdx + 1) % 2;
			baseAnimations[baseAnimationIdx] = AnimationState(
				animationActiveSetup,
				-1LL,
				0LL,
				Timing::UNDEFINED,
				false,
				0.0f,
				speed
			);
		}
		if (baseAnimations.size() > 1) {
			auto baseAnimationIdxLast = (baseAnimationIdx + 1) % 2;
			auto& baseAnimationLast = baseAnimations[baseAnimationIdxLast];
			baseAnimationLast.endAtTime = baseAnimationLast.currentAtTime;
		}
	} else {
		Console::println("ObjectAnimation::setAnimation(): " + model->getId() + ": missing animation: " + id);
	}
}

void ObjectAnimation::setAnimationSpeed(float speed) {
	if (baseAnimations.size() == 0) return;
	baseAnimations[baseAnimationIdx].speed = speed;
}

void ObjectAnimation::addOverlayAnimation(const string& id)
{
	// remove active overlay animation with given ids
	removeOverlayAnimation(id);
	// check overlay animation
	auto animationSetup = model->getAnimationSetup(id);
	if (animationSetup == nullptr) return;
	if (animationSetup->getOverlayFromNodeId().size() == 0) return;
	// create animation state
	auto animationState = new AnimationState();
	animationState->setup = animationSetup;
	animationState->lastAtTime = Timing::UNDEFINED;
	animationState->currentAtTime = 0LL;
	animationState->time = 0.0f;
	animationState->speed = 1.0f;
	animationState->finished = false;
	// register overlay animation
	overlayAnimationsById[id] = animationState;
	overlayAnimationsByJointId[animationSetup->getOverlayFromNodeId()] = animationState;
	//
	updateNodeLists();
}

void ObjectAnimation::removeOverlayAnimation(const string& id)
{
	auto animationStateIt = overlayAnimationsById.find(id);
	if (animationStateIt == overlayAnimationsById.end()) return;
	auto animationState = animationStateIt->second;
	overlayAnimationsById.erase(animationStateIt);
	auto overlayAnimationsByJointIdIt = overlayAnimationsByJointId.find(animationState->setup->getOverlayFromNodeId());
	if (overlayAnimationsByJointIdIt == overlayAnimationsByJointId.end() || overlayAnimationsByJointIdIt->second->setup != animationState->setup) {
		delete animationState;
		return;
	}
	overlayAnimationsByJointId.erase(overlayAnimationsByJointIdIt);
	delete animationState;
	//
	updateNodeLists();
}

void ObjectAnimation::removeFinishedOverlayAnimations()
{
	// determine finished overlay animations
	vector<string> overlayAnimationsToRemove;
	for (auto it: overlayAnimationsById) {
		const string& id = it.first;
		AnimationState* animationState = it.second;
		{
			if (animationState->finished == true) {
				overlayAnimationsToRemove.push_back(id);
			}
		}
	}
	// remove them
	for (auto animationState: overlayAnimationsToRemove) {
		removeOverlayAnimation(animationState);
	}
}

void ObjectAnimation::removeOverlayAnimations()
{
	// remove them
	vector<string> overlayAnimationsToRemove;
	for (auto it: overlayAnimationsById) {
		overlayAnimationsToRemove.push_back(it.first);
	}
	for (auto animationState: overlayAnimationsToRemove) {
		removeOverlayAnimation(animationState);
	}
}

const string ObjectAnimation::getAnimation()
{
	return baseAnimations[baseAnimationIdx].setup == nullptr ? "none" : baseAnimations[baseAnimationIdx].setup->getId();
}

float ObjectAnimation::getAnimationTime()
{
	return baseAnimations[baseAnimationIdx].time;
}

bool ObjectAnimation::hasOverlayAnimation(const string& id)
{
	return overlayAnimationsById.find(id) != overlayAnimationsById.end();
}

float ObjectAnimation::getOverlayAnimationTime(const string& id)
{
	AnimationState* animationState = nullptr;
	auto animationStateIt = overlayAnimationsById.find(id);
	if (animationStateIt != overlayAnimationsById.end()) {
		animationState = animationStateIt->second;
	}
	return animationState == nullptr ? 1.0f : animationState->time;
}

const Matrix4x4 ObjectAnimation::getNodeTransformMatrix(const string& id)
{
	auto overriddenTransformMatrixIt = overriddenTransformMatrices.find(id);
	if (overriddenTransformMatrixIt != overriddenTransformMatrices.end()) {
		return *overriddenTransformMatrixIt->second;
	} else {
		auto transformMatrixIt = transformMatrices[0].find(id);
		if (transformMatrixIt != transformMatrices[0].end()) {
			return *transformMatrixIt->second;
		}
		Console::println("ObjectAnimation::getTransformMatrix(): " + id + ": node not found");
	}
	return Matrix4x4().identity();
}

void ObjectAnimation::setNodeTransformMatrix(const string& id, const Matrix4x4& matrix)
{
	auto overriddenTransformMatrixIt = overriddenTransformMatrices.find(id);
	if (overriddenTransformMatrixIt != overriddenTransformMatrices.end()) {
		*overriddenTransformMatrixIt->second = matrix;
	} else {
		overriddenTransformMatrices[id] = new Matrix4x4(matrix);
	}
	//
	updateNodeLists();
}

void ObjectAnimation::unsetNodeTransformMatrix(const string& id)
{
	auto overriddenTransformMatrixIt = overriddenTransformMatrices.find(id);
	if (overriddenTransformMatrixIt != overriddenTransformMatrices.end()) {
		delete overriddenTransformMatrixIt->second;
		overriddenTransformMatrices.erase(overriddenTransformMatrixIt);
	}
	//
	updateNodeLists();
}

void ObjectAnimation::createNodesTransformMatrices(map<string, Matrix4x4*>& matrices, vector<FlattenedNode>& nodeList, const map<string, Node*>& nodes, Matrix4x4* parentTransformMatrix, AnimationState* animationState)
{
	// iterate through nodes
	for (auto it: nodes) {
		//
		auto nodeAnimationState = animationState;
		// put and associate transform matrices with node
		auto node = it.second;
		auto matrix = new Matrix4x4();
		matrix->identity();
		matrices[node->getId()] = matrix;
		// overridden matrix
		Matrix4x4* overriddenTransformMatrix = nullptr;
		auto overriddenTransformMatrixIt = overriddenTransformMatrices.find(node->getId());
		if (overriddenTransformMatrixIt != overriddenTransformMatrices.end()) overriddenTransformMatrix = overriddenTransformMatrixIt->second;
		// overlay animation
		auto overlayAnimationIt = overlayAnimationsByJointId.find(node->getId());
		if (overlayAnimationIt != overlayAnimationsByJointId.end()) {
			nodeAnimationState = overlayAnimationIt->second;
		}
		nodeList.emplace_back(
			node->getId(),
			&node->getTransformMatrix(),
			overriddenTransformMatrix,
			node->getAnimation(),
			animationState,
			parentTransformMatrix,
			matrix
		);
		// do sub nodes
		auto& subNodes = node->getSubNodes();
		if (subNodes.size() > 0) {
			createNodesTransformMatrices(matrices, nodeList, subNodes, matrix, nodeAnimationState);
		}
	}
}

void ObjectAnimation::updateNodeList(vector<FlattenedNode>& nodeList, int& nodeIdx, const map<string, Node*>& nodes, AnimationState* animationState) {
	// iterate through nodes
	for (auto it: nodes) {
		//
		auto nodeAnimationState = animationState;
		// put and associate transform matrices with node
		auto node = it.second;
		// overridden matrix
		Matrix4x4* overriddenTransformMatrix = nullptr;
		auto overriddenTransformMatrixIt = overriddenTransformMatrices.find(node->getId());
		if (overriddenTransformMatrixIt != overriddenTransformMatrices.end()) overriddenTransformMatrix = overriddenTransformMatrixIt->second;
		// overlay animation
		auto overlayAnimationIt = overlayAnimationsByJointId.find(node->getId());
		if (overlayAnimationIt != overlayAnimationsByJointId.end()) {
			nodeAnimationState = overlayAnimationIt->second;
		}
		// update node list
		nodeList[nodeIdx].nodeOverriddenTransformMatrix = overriddenTransformMatrix;
		nodeList[nodeIdx].nodeAnimationState = nodeAnimationState;
		nodeIdx++;
		// do sub nodes
		auto& subNodes = node->getSubNodes();
		if (subNodes.size() > 0) {
			updateNodeList(nodeList, nodeIdx, subNodes, nodeAnimationState);
		}
	}
}

void ObjectAnimation::computeNodesTransformMatrices(vector<FlattenedNode>& nodeList, const Matrix4x4 parentTransformMatrix, AnimationState* animationState)
{
	// iterate through flattened nodes
	Matrix4x4 transformMatrix;
	for (auto& flattenedNode: nodeList) {
		auto nodeAnimationState = flattenedNode.nodeAnimationState != nullptr?flattenedNode.nodeAnimationState:animationState;
		// compute animation matrix if animation setups exist
		auto animation = flattenedNode.nodeAnimation;
		// TODO: check if its better to not compute animation matrix if finished
		if (animation != nullptr && nodeAnimationState != nullptr && nodeAnimationState->setup != nullptr) {
			auto& animationMatrices = animation->getTransformMatrices();
			auto frames = nodeAnimationState->setup->getFrames();
			auto fps = model->getFPS();
			// determine current and last matrix
			auto frameAtLast = (nodeAnimationState->lastAtTime / 1000.0f) * fps * nodeAnimationState->setup->getSpeed() * nodeAnimationState->speed;
			auto frameAtCurrent = (nodeAnimationState->currentAtTime / 1000.0f) * fps * nodeAnimationState->setup->getSpeed() * nodeAnimationState->speed;
			// check if looping is disabled
			if (nodeAnimationState->setup->isLoop() == false && frameAtCurrent >= frames) {
				frameAtLast = frames - 1;
				frameAtCurrent = frames - 1;
				nodeAnimationState->finished = true;
			}
			auto matrixAtLast = static_cast<int32_t>(frameAtLast) % frames;
			auto matrixAtCurrent = static_cast<int32_t>(frameAtCurrent) % frames;
			nodeAnimationState->time = frames <= 1?0.0f:static_cast<float>(matrixAtCurrent) / static_cast<float>((frames - 1));
			// compute animation transform matrix
			auto t = frameAtCurrent - static_cast<float>(Math::floor(frameAtLast));
			if (t < 1.0f) {
				if (matrixAtLast == matrixAtCurrent) {
					matrixAtCurrent+= 1;
					if (matrixAtCurrent >= frames) {
						if (nodeAnimationState->setup->isLoop() == true) {
							matrixAtCurrent = matrixAtCurrent % frames;
						} else {
							matrixAtCurrent = frames - 1;
						}
					}
				}
				transformMatrix = Matrix4x4::interpolateLinear(
					animationMatrices[matrixAtLast + nodeAnimationState->setup->getStartFrame()],
					animationMatrices[matrixAtCurrent + nodeAnimationState->setup->getStartFrame()],
					t
				);
			} else {
				transformMatrix.set(animationMatrices[matrixAtCurrent + nodeAnimationState->setup->getStartFrame()]);
			}
		} else {
			if (flattenedNode.nodeOverriddenTransformMatrix != nullptr) {
				transformMatrix.set(*flattenedNode.nodeOverriddenTransformMatrix);
			} else {
				// no animation matrix, set up local transform matrix up as node matrix
				transformMatrix.set(*flattenedNode.nodeTransformMatrix);
			}
		}
		// apply parent transform matrix
		transformMatrix.multiply(flattenedNode.parentTransformMatrix != nullptr?*flattenedNode.parentTransformMatrix:parentTransformMatrix);
		// put and associate transform matrices with node
		flattenedNode.transformMatrix->set(transformMatrix);
	}
}

inline void ObjectAnimation::updateSkinningJoints() {
	for (auto& skinningNodeNodeSkinningJoints: skinningNodesNodeSkinningJoints)
	for (auto& skinningNodeNodeSkinningJoint: skinningNodeNodeSkinningJoints) {
		skinningNodeNodeSkinningJoint.skinningNodeTransformMatrix->set(skinningNodeNodeSkinningJoint.joint->getBindMatrix()).multiply(*skinningNodeNodeSkinningJoint.nodeTransformMatrix);
	}
}

void ObjectAnimation::computeAnimation(vector<FlattenedNode>& nodeList, const Matrix4x4& instanceTransformMatrix, AnimationState& baseAnimation, int contextIdx, int64_t lastFrameAtTime, int64_t currentFrameAtTime)
{
	// do transform if we have a animation
	if (baseAnimation.setup != nullptr) {
		// animation timing
		// do progress of base animation
		if (lastFrameAtTime != Timing::UNDEFINED && baseAnimation.lastAtTime != -1LL) {
			baseAnimation.currentAtTime+= currentFrameAtTime - lastFrameAtTime;
		}
		// do progress of overlay animations
		for (auto it: overlayAnimationsById) {
			AnimationState* overlayAnimationState = it.second;
			if (lastFrameAtTime != Timing::UNDEFINED && overlayAnimationState->lastAtTime != -1LL) {
				overlayAnimationState->currentAtTime+= currentFrameAtTime - lastFrameAtTime;
			}
			overlayAnimationState->lastAtTime = overlayAnimationState->currentAtTime;
		}
		// set up parent transform matrix
		Matrix4x4 parentTransformMatrix;
		parentTransformMatrix.set(model->getImportTransformMatrix());
		if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
			parentTransformMatrix.multiply(instanceTransformMatrix);
		}
		// calculate transform matrices
		computeNodesTransformMatrices(nodeList, parentTransformMatrix, &baseAnimation);
		//
		baseAnimation.lastAtTime = baseAnimation.currentAtTime;
	} else
	if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
		// set up parent transform matrix
		Matrix4x4 parentTransformMatrix;
		parentTransformMatrix.set(model->getImportTransformMatrix());
		if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
			parentTransformMatrix.multiply(instanceTransformMatrix);
		}
		// calculate transform matrices
		computeNodesTransformMatrices(nodeList, parentTransformMatrix, &baseAnimation);
	}
}

void ObjectAnimation::computeAnimation(int contextIdx, const Matrix4x4& instanceTransformMatrix, int64_t lastFrameAtTime, int64_t currentFrameAtTime) {
	// compute last animation matrices if required
	auto baseAnimationIdxLast = transformMatrices.size() > 1?(baseAnimationIdx + 1) % 2:-1;
	if (baseAnimationIdxLast != -1 &&
		baseAnimations[baseAnimationIdxLast].lastAtTime != -1LL) {
		computeAnimation(nodeLists[1 + baseAnimationIdxLast], instanceTransformMatrix, baseAnimations[baseAnimationIdxLast], contextIdx, lastFrameAtTime, currentFrameAtTime);
	} else {
		baseAnimationIdxLast = -1;
	}

	// compute current animation matrices
	computeAnimation(nodeLists[nodeLists.size() > 1?1 + baseAnimationIdx:baseAnimationIdx], instanceTransformMatrix, baseAnimations[baseAnimationIdx], contextIdx, lastFrameAtTime, currentFrameAtTime);

	// blend if required
	if (transformMatrices.size() > 1) {
		for (auto i = 0; i < nodeLists[0].size(); i++) {
			if (baseAnimationIdxLast != -1 &&
				baseAnimations[baseAnimationIdxLast].endAtTime != -1LL) {
				auto blendingAnimationDuration = static_cast<float>(baseAnimations[baseAnimationIdxLast].currentAtTime - baseAnimations[baseAnimationIdxLast].endAtTime) / Engine::getAnimationBlendingTime();
				*nodeLists[0][i].transformMatrix = Matrix4x4::interpolateLinear(
					*nodeLists[1 + baseAnimationIdxLast][i].transformMatrix,
					*nodeLists[1 + baseAnimationIdx][i].transformMatrix,
					Math::min(
						blendingAnimationDuration,
						1.0f
					)
				);
				if (blendingAnimationDuration >= 1.0f) {
					auto& animationStateLast = baseAnimations[baseAnimationIdxLast];
					animationStateLast.setup = nullptr;
					animationStateLast.endAtTime = -1LL;
					animationStateLast.currentAtTime = -1LL;
					animationStateLast.lastAtTime = -1LL;
					animationStateLast.finished = true;
					animationStateLast.time = -1LL;
				}
			} else {
				nodeLists[0][i].transformMatrix->set(*nodeLists[1 + baseAnimationIdx][i].transformMatrix);
			}
		}
	}
	if (hasSkinning == true) updateSkinningJoints();
}

int32_t ObjectAnimation::determineSkinnedNodeCount(const map<string, Node*>& nodes)
{
	return determineSkinnedNodeCount(nodes, 0);
}

int32_t ObjectAnimation::determineSkinnedNodeCount(const map<string, Node*>& nodes, int32_t count)
{
	// iterate through nodes
	for (auto it: nodes) {
		Node* node = it.second;
		//
		if (node->getSkinning() != nullptr)
			count++;
		// calculate sub nodes
		auto& subNodes = node->getSubNodes();
		if (subNodes.size() > 0) {
			count = determineSkinnedNodeCount(subNodes, count);
		}
	}
	return count;
}

int32_t ObjectAnimation::determineSkinnedNodes(const map<string, Node*>& nodes, vector<Node*>& skinningNodes, int32_t idx)
{
	// iterate through nodes
	for (auto it: nodes) {
		Node* node = it.second;
		// fetch skinning nodes
		if (node->getSkinning() != nullptr) {
			skinningNodes[idx++] = node;
		}
		// calculate sub nodes
		auto& subNodes = node->getSubNodes();
		if (subNodes.size() > 0) {
			idx = determineSkinnedNodes(subNodes, skinningNodes, idx);
		}
	}
	return idx;
}

map<string, Matrix4x4*>* ObjectAnimation::getSkinningNodesTransformMatrices(Node* node)
{
	if (hasSkinning == false) return nullptr;
	for (auto i = 0; i < skinningNodes.size(); i++) {
		if (skinningNodes[i] == node) {
			return &skinningNodesMatrices[i];
		}
	}
	return nullptr;
}
