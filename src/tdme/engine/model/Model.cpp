#include <tdme/engine/model/Model.h>

#include <algorithm>
#include <map>
#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/ShaderModel.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/rendering/ObjectModelInternal.h>
#include <tdme/engine/ModelUtilities.h>
#include <tdme/engine/ObjectModel.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/threading/AtomicOperations.h>

using std::make_unique;
using std::map;
using std::sort;
using std::string;
using std::unique_ptr;

using tdme::engine::model::Animation;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::ShaderModel;
using tdme::engine::model::UpVector;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::rendering::ObjectModelInternal;
using tdme::engine::ModelUtilities;
using tdme::engine::ObjectModel;
using tdme::math::Matrix4x4;
using tdme::os::threading::AtomicOperations;

string Model::ANIMATIONSETUP_DEFAULT = "tdme.default";
uint32_t Model::uidCounter = 0;

constexpr float Model::FPS_DEFAULT;

Model::Model(const string& id, const string& name, UpVector* upVector, RotationOrder* rotationOrder, BoundingBox* boundingBox, AuthoringTool authoringTool)
{
	this->uniqueId = AtomicOperations::increment(uidCounter);
	this->id = id + ":uid=" + to_string(this->uniqueId);
	this->name = name;
	this->upVector = upVector;
	this->rotationOrder = rotationOrder;
	this->shaderModel = ShaderModel::SPECULAR;
	skinning = false;
	fps = FPS_DEFAULT;
	importTransformMatrix.identity();
	this->boundingBox = unique_ptr<BoundingBox>(boundingBox);
	this->authoringTool = authoringTool;
	this->boundingBoxUpdated = false;
	this->embedSpecularTextures = false;
	this->embedPBRTextures = false;
}

Model::~Model() {
	deleteSubNodes(subNodes);
	for (const auto& [materialId, material]: materials) delete material;
	for (const auto& [animationSetupId, animationSetup]: animationSetups) delete animationSetup;
}

void Model::deleteSubNodes(const unordered_map<string, Node*>& subNodes) {
	for (const auto& [subNodeId, subNode]: subNodes) {
		deleteSubNodes(subNode->getSubNodes());
		delete subNode;
	}
}

const vector<string> Model::getMaterialIds() {
	vector<string> result;
	for (const auto& [materialId, material]: materials) result.push_back(material->getId());
	sort(result.begin(), result.end());
	return result;
}

const vector<string> Model::getNodeIds() {
	vector<string> result;
	for (const auto& [nodeId, node]: nodes) result.push_back(node->getId());
	sort(result.begin(), result.end());
	return result;
}

const vector<string> Model::getAnimationSetupIds() {
	vector<string> result;
	for (const auto& [animationSetupId, animationSetup]: animationSetups) result.push_back(animationSetup->getId());
	sort(result.begin(), result.end());
	return result;
}

AnimationSetup* Model::addAnimationSetup(const string& id, int32_t startFrame, int32_t endFrame, bool loop, float speed)
{
	auto animationSetupIt = animationSetups.find(id);
	if (animationSetupIt != animationSetups.end()) {
		delete animationSetupIt->second;
		animationSetups.erase(animationSetupIt);
	}
	auto animationSetup = make_unique<AnimationSetup>(this, id, startFrame, endFrame, loop, string(), speed);
	animationSetups[id] = animationSetup.get();
	return animationSetup.release();
}

AnimationSetup* Model::addOverlayAnimationSetup(const string& id, const string& overlayFromNodeId, int32_t startFrame, int32_t endFrame, bool loop, float speed)
{
	auto animationSetupIt = animationSetups.find(id);
	if (animationSetupIt != animationSetups.end()) {
		delete animationSetupIt->second;
		animationSetups.erase(animationSetupIt);
	}
	auto animationSetup = make_unique<AnimationSetup>(this, id, startFrame, endFrame, loop, overlayFromNodeId, speed);
	animationSetups[id] = animationSetup.get();
	return animationSetup.release();
}

bool Model::renameAnimationSetup(const string& id, const string& newId) {
	auto animationSetupIt = animationSetups.find(id);
	if (animationSetupIt == animationSetups.end()) return false;
	auto animationSetup = animationSetupIt->second;
	animationSetups.erase(animationSetupIt);
	animationSetup->setId(newId);
	animationSetups[newId] = animationSetup;
	return true;
}

bool Model::removeAnimationSetup(const string& id) {
	auto animationSetupIt = animationSetups.find(id);
	if (animationSetupIt == animationSetups.end()) return false;
	delete animationSetupIt->second;
	animationSetups.erase(animationSetupIt);
	return true;
}

void Model::clearAnimationSetups() {
	for (const auto& [animationSetupId, animationSetup]: animationSetups) {
		delete animationSetup;
	}
	animationSetups.clear();
}

BoundingBox* Model::getBoundingBox()
{
	// TODO: return const bb
	if (boundingBox == nullptr) {
		boundingBox = unique_ptr<BoundingBox>(ModelUtilities::createBoundingBox(this));
	}
	return boundingBox.get();
}

bool Model::computeTransformMatrix(const unordered_map<string, Node*>& nodes, const Matrix4x4& parentTransformMatrix, int32_t frame, const string& nodeId, Matrix4x4& transformMatrix)
{
	// TODO: this should be computed from sub nodes to root node, not the other way around, also it looks broken to me right now, but works for our cases so far
	// iterate through nodes
	for (const auto& [subNodeId, subNode]: nodes) {
		// compute animation matrix if animation setups exist
		auto animation = subNode->getAnimation();
		if (animation != nullptr && frame != -1) {
			const auto& animationMatrices = animation->getTransformMatrices();
			transformMatrix.set(animationMatrices[frame % animationMatrices.size()]);
		} else {
			// no animation matrix, set up local transform matrix up as node matrix
			transformMatrix.set(subNode->getTransformMatrix());
		}

		// apply parent transform matrix
		transformMatrix.multiply(parentTransformMatrix);

		// return matrix if node matches
		if (subNode->getId() == nodeId) return true;

		// calculate sub nodes
		const auto& subNodes = subNode->getSubNodes();
		if (subNodes.size() > 0) {
			auto haveTransformMatrix = computeTransformMatrix(subNodes, transformMatrix.clone(), frame, nodeId, transformMatrix);
			if (haveTransformMatrix == true) return true;
		}
	}

	//
	return false;
}

void Model::invalidateBoundingBox() {
	boundingBox = nullptr;
	boundingBoxUpdated = true;
}
