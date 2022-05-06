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
			createTransformationsMatrices(skinningNodesMatrices[i], nodeListIgnored, model->getSubNodes());
		}
	}
	hasAnimations = model->hasAnimations();
	//
	baseAnimationIdx = 0;
	// animation
	setAnimation(Model::ANIMATIONSETUP_DEFAULT);
	// create transformations matrices
	transformationsMatrices.push_back(map<string, Matrix4x4*>());
	nodeLists.push_back(vector<FlattenedNode>());
	createTransformationsMatrices(transformationsMatrices[0], nodeLists[0], model->getSubNodes());
	// calculate transformations matrices
	computeTransformationsMatrices(nodeLists[0], model->getImportTransformationsMatrix(), baseAnimations.size() == 0?nullptr:&baseAnimations[0]);
	// skinning ...
	if (hasSkinning == true) {
		for (auto i = 0; i < skinningNodes.size(); i++) {
			skinningNodesNodeSkinningJoints.push_back(vector<NodeSkinningJoint>());
			for (auto& skinningJoint: skinningNodes[i]->getSkinning()->getJoints()) {
				auto transformationsMatrixIt = transformationsMatrices[0].find(skinningJoint.getNodeId());
				if (transformationsMatrixIt == transformationsMatrices[0].end()) continue;
				auto skinningNodeMatrixIt = skinningNodesMatrices[i].find(skinningJoint.getNodeId());
				if (skinningNodeMatrixIt == skinningNodesMatrices[i].end()) continue;
				skinningNodesNodeSkinningJoints[i].push_back({
					.joint = &skinningJoint,
					.nodeTransformationsMatrix = transformationsMatrixIt->second,
					.skinningNodeTransformationsMatrix = skinningNodeMatrixIt->second
				});
			}
		}
		updateSkinningTransformationsMatrices();
	}
	// reset animation
	if (baseAnimations.size() == 0) baseAnimations.push_back(AnimationState());
	baseAnimations[baseAnimationIdx].endAtTime = -1LL;
	baseAnimations[baseAnimationIdx].lastAtTime = Timing::UNDEFINED;
	baseAnimations[baseAnimationIdx].currentAtTime = 0LL;
	baseAnimations[baseAnimationIdx].time = 0.0f;
	baseAnimations[baseAnimationIdx].finished = false;
}

ObjectAnimation::~ObjectAnimation() {
	for (auto baseAnimationTransformationsMatrices: transformationsMatrices) {
		for (auto it: baseAnimationTransformationsMatrices) {
			delete it.second;
		}
	}
	for (auto skinningNodeMatricies: skinningNodesMatrices) {
		for (auto it: skinningNodeMatricies) {
			delete it.second;
		}
	}
	for (auto overriddenTransformationsMatrixIt: overriddenTransformationsMatrices) {
		delete overriddenTransformationsMatrixIt.second;
	}
}

void ObjectAnimation::setAnimation(const string& id, float speed)
{
	auto _animationActiveSetup = model->getAnimationSetup(id);

	// only switch animation if we have one
	if (_animationActiveSetup != nullptr) {
		AnimationState baseAnimation;
		baseAnimation.setup = _animationActiveSetup;
		baseAnimation.endAtTime = -1LL;
		baseAnimation.lastAtTime = Timing::UNDEFINED;
		baseAnimation.currentAtTime = 0LL;
		baseAnimation.time = 0.0f;
		baseAnimation.speed = speed;
		baseAnimation.finished = false;
		if (baseAnimations.size() == 0) {
			baseAnimations.push_back(baseAnimation);
			baseAnimationIdx = 0;
		} else
		if (baseAnimations.size() == 1) {
			baseAnimations.push_back(baseAnimation);
			baseAnimationIdx = 1;
			transformationsMatrices.push_back(map<string, Matrix4x4*>());
			nodeLists.push_back(vector<FlattenedNode>());
			createTransformationsMatrices(transformationsMatrices[1], nodeLists[1], model->getSubNodes());
			transformationsMatrices.push_back(map<string, Matrix4x4*>());
			nodeLists.push_back(vector<FlattenedNode>());
			createTransformationsMatrices(transformationsMatrices[2], nodeLists[2], model->getSubNodes());
		} else {
			baseAnimationIdx = (baseAnimationIdx + 1) % 2;
			baseAnimations[baseAnimationIdx] = baseAnimation;
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

void ObjectAnimation::removeOverlayAnimationsFinished()
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

const Matrix4x4 ObjectAnimation::getNodeTransformationsMatrix(const string& id)
{
	auto overriddenTransformationsMatrixIt = overriddenTransformationsMatrices.find(id);
	if (overriddenTransformationsMatrixIt != overriddenTransformationsMatrices.end()) {
		return *overriddenTransformationsMatrixIt->second;
	} else {
		auto transformationMatrixIt = transformationsMatrices[0].find(id);
		if (transformationMatrixIt != transformationsMatrices[0].end()) {
			return *transformationMatrixIt->second;
		}
		Console::println("ObjectAnimation::getTransformationsMatrix(): " + id + ": node not found");
	}
	return Matrix4x4().identity();
}

void ObjectAnimation::setNodeTransformationsMatrix(const string& id, const Matrix4x4& matrix)
{
	auto overriddenTransformationsMatrixIt = overriddenTransformationsMatrices.find(id);
	if (overriddenTransformationsMatrixIt != overriddenTransformationsMatrices.end()) {
		*overriddenTransformationsMatrixIt->second = matrix;
	} else {
		overriddenTransformationsMatrices[id] = new Matrix4x4(matrix);
	}
	//
	updateNodeLists();
}

void ObjectAnimation::unsetNodeTransformationsMatrix(const string& id)
{
	auto overriddenTransformationsMatrixIt = overriddenTransformationsMatrices.find(id);
	if (overriddenTransformationsMatrixIt != overriddenTransformationsMatrices.end()) {
		delete overriddenTransformationsMatrixIt->second;
		overriddenTransformationsMatrices.erase(overriddenTransformationsMatrixIt);
	}
	//
	updateNodeLists();
}

void ObjectAnimation::createTransformationsMatrices(map<string, Matrix4x4*>& matrices, vector<FlattenedNode>& nodeList, const map<string, Node*>& nodes, Matrix4x4* parentTransformationsMatrix, AnimationState* animationState)
{
	// iterate through nodes
	for (auto it: nodes) {
		//
		auto nodeAnimationState = animationState;
		// put and associate transformation matrices with node
		auto node = it.second;
		auto matrix = new Matrix4x4();
		matrix->identity();
		matrices[node->getId()] = matrix;
		// overridden matrix
		Matrix4x4* overriddenTransformationsMatrix = nullptr;
		auto overriddenTransformationsMatrixIt = overriddenTransformationsMatrices.find(node->getId());
		if (overriddenTransformationsMatrixIt != overriddenTransformationsMatrices.end()) overriddenTransformationsMatrix = overriddenTransformationsMatrixIt->second;
		// overlay animation
		auto overlayAnimationIt = overlayAnimationsByJointId.find(node->getId());
		if (overlayAnimationIt != overlayAnimationsByJointId.end()) {
			nodeAnimationState = overlayAnimationIt->second;
		}
		nodeList.push_back({
			.nodeId = node->getId(),
			.nodeTransformationsMatrix = &node->getTransformationsMatrix(),
			.nodeOverriddenTransformationsMatrix = overriddenTransformationsMatrix,
			.nodeAnimation = node->getAnimation(),
			.nodeAnimationState = animationState,
			.parentTransformationsMatrix = parentTransformationsMatrix,
			.transformationsMatrix = matrix
		});
		// do sub nodes
		auto& subNodes = node->getSubNodes();
		if (subNodes.size() > 0) {
			createTransformationsMatrices(matrices, nodeList, subNodes, matrix, nodeAnimationState);
		}
	}
}

void ObjectAnimation::updateNodeList(vector<FlattenedNode>& nodeList, int& nodeIdx, const map<string, Node*>& nodes, AnimationState* animationState) {
	// iterate through nodes
	for (auto it: nodes) {
		//
		auto nodeAnimationState = animationState;
		// put and associate transformation matrices with node
		auto node = it.second;
		// overridden matrix
		Matrix4x4* overriddenTransformationsMatrix = nullptr;
		auto overriddenTransformationsMatrixIt = overriddenTransformationsMatrices.find(node->getId());
		if (overriddenTransformationsMatrixIt != overriddenTransformationsMatrices.end()) overriddenTransformationsMatrix = overriddenTransformationsMatrixIt->second;
		// overlay animation
		auto overlayAnimationIt = overlayAnimationsByJointId.find(node->getId());
		if (overlayAnimationIt != overlayAnimationsByJointId.end()) {
			nodeAnimationState = overlayAnimationIt->second;
		}
		// update node list
		nodeList[nodeIdx].nodeOverriddenTransformationsMatrix = overriddenTransformationsMatrix;
		nodeList[nodeIdx].nodeAnimationState = nodeAnimationState;
		nodeIdx++;
		// do sub nodes
		auto& subNodes = node->getSubNodes();
		if (subNodes.size() > 0) {
			updateNodeList(nodeList, nodeIdx, subNodes, nodeAnimationState);
		}
	}
}

void ObjectAnimation::computeTransformationsMatrices(vector<FlattenedNode>& nodeList, const Matrix4x4 parentTransformationsMatrix, AnimationState* animationState)
{
	// iterate through flattened nodes
	Matrix4x4 transformationsMatrix;
	for (auto& flattenedNode: nodeList) {
		auto nodeAnimationState = flattenedNode.nodeAnimationState != nullptr?flattenedNode.nodeAnimationState:animationState;
		// compute animation matrix if animation setups exist
		auto animation = flattenedNode.nodeAnimation;
		// TODO: check if its better to not compute animation matrix if finished
		if (animation != nullptr && nodeAnimationState != nullptr && nodeAnimationState->setup != nullptr) {
			auto& animationMatrices = animation->getTransformationsMatrices();
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
			// compute animation transformations matrix
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
				transformationsMatrix = Matrix4x4::interpolateLinear(
					animationMatrices[matrixAtLast + nodeAnimationState->setup->getStartFrame()],
					animationMatrices[matrixAtCurrent + nodeAnimationState->setup->getStartFrame()],
					t
				);
			} else {
				transformationsMatrix.set(animationMatrices[matrixAtCurrent + nodeAnimationState->setup->getStartFrame()]);
			}
		} else {
			if (flattenedNode.nodeOverriddenTransformationsMatrix != nullptr) {
				transformationsMatrix.set(*flattenedNode.nodeOverriddenTransformationsMatrix);
			} else {
				// no animation matrix, set up local transformation matrix up as node matrix
				transformationsMatrix.set(*flattenedNode.nodeTransformationsMatrix);
			}
		}
		// apply parent transformation matrix
		transformationsMatrix.multiply(flattenedNode.parentTransformationsMatrix != nullptr?*flattenedNode.parentTransformationsMatrix:parentTransformationsMatrix);
		// put and associate transformation matrices with node
		flattenedNode.transformationsMatrix->set(transformationsMatrix);
	}
}

inline void ObjectAnimation::updateSkinningTransformationsMatrices() {
	for (auto& skinningNodeNodeSkinningJoints: skinningNodesNodeSkinningJoints)
	for (auto& skinningNodeNodeSkinningJoint: skinningNodeNodeSkinningJoints) {
		skinningNodeNodeSkinningJoint.skinningNodeTransformationsMatrix->set(skinningNodeNodeSkinningJoint.joint->getBindMatrix()).multiply(*skinningNodeNodeSkinningJoint.nodeTransformationsMatrix);
	}
}

void ObjectAnimation::computeTransformations(vector<FlattenedNode>& nodeList, const Matrix4x4& instanceTransformationsMatrix, AnimationState& baseAnimation, int contextIdx, int64_t lastFrameAtTime, int64_t currentFrameAtTime)
{
	// do transformations if we have a animation
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
		// set up parent transformations matrix
		Matrix4x4 parentTransformationsMatrix;
		parentTransformationsMatrix.set(model->getImportTransformationsMatrix());
		if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
			parentTransformationsMatrix.multiply(instanceTransformationsMatrix);
		}
		// calculate transformations matrices
		computeTransformationsMatrices(nodeList, parentTransformationsMatrix, &baseAnimation);
		//
		baseAnimation.lastAtTime = baseAnimation.currentAtTime;
	} else
	if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
		// set up parent transformations matrix
		Matrix4x4 parentTransformationsMatrix;
		parentTransformationsMatrix.set(model->getImportTransformationsMatrix());
		if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
			parentTransformationsMatrix.multiply(instanceTransformationsMatrix);
		}
		// calculate transformations matrices
		computeTransformationsMatrices(nodeList, parentTransformationsMatrix, &baseAnimation);
	}
}

void ObjectAnimation::computeTransformations(int contextIdx, const Matrix4x4& instanceTransformationsMatrix, int64_t lastFrameAtTime, int64_t currentFrameAtTime) {
	// compute last animation matrices if required
	auto baseAnimationIdxLast = transformationsMatrices.size() > 1?(baseAnimationIdx + 1) % 2:-1;
	if (baseAnimationIdxLast != -1 &&
		baseAnimations[baseAnimationIdxLast].lastAtTime != -1LL) {
		computeTransformations(nodeLists[1 + baseAnimationIdxLast], instanceTransformationsMatrix, baseAnimations[baseAnimationIdxLast], contextIdx, lastFrameAtTime, currentFrameAtTime);
	} else {
		baseAnimationIdxLast = -1;
	}

	// compute current animation matrices
	computeTransformations(nodeLists[nodeLists.size() > 1?1 + baseAnimationIdx:baseAnimationIdx], instanceTransformationsMatrix, baseAnimations[baseAnimationIdx], contextIdx, lastFrameAtTime, currentFrameAtTime);

	// blend if required
	if (transformationsMatrices.size() > 1) {
		for (auto i = 0; i < nodeLists[0].size(); i++) {
			if (baseAnimationIdxLast != -1 &&
				baseAnimations[baseAnimationIdxLast].endAtTime != -1LL) {
				auto blendingAnimationDuration = static_cast<float>(baseAnimations[baseAnimationIdxLast].currentAtTime - baseAnimations[baseAnimationIdxLast].endAtTime) / Engine::getAnimationBlendingTime();
				*nodeLists[0][i].transformationsMatrix = Matrix4x4::interpolateLinear(
					*nodeLists[1 + baseAnimationIdxLast][i].transformationsMatrix,
					*nodeLists[1 + baseAnimationIdx][i].transformationsMatrix,
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
				nodeLists[0][i].transformationsMatrix->set(*nodeLists[1 + baseAnimationIdx][i].transformationsMatrix);
			}
		}
	}
	if (hasSkinning == true) updateSkinningTransformationsMatrices();
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

map<string, Matrix4x4*>* ObjectAnimation::getSkinningNodesMatrices(Node* node)
{
	if (hasSkinning == false) return nullptr;
	for (auto i = 0; i < skinningNodes.size(); i++) {
		if (skinningNodes[i] == node) {
			return &skinningNodesMatrices[i];
		}
	}
	return nullptr;
}
