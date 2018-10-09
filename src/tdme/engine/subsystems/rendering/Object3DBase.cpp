#include <tdme/engine/subsystems/rendering/Object3DBase.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/math/Math.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/engine/subsystems/manager/MeshManager.h>
#include <tdme/engine/subsystems/rendering/AnimationState.h>
#include <tdme/engine/subsystems/rendering/Object3DBase_TransformedFacesIterator.h>
#include <tdme/engine/subsystems/rendering/Object3DGroup.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupVBORenderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>

using std::map;
using std::vector;
using std::string;
using std::to_string;

using tdme::engine::subsystems::rendering::Object3DBase;
using tdme::math::Math;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::engine::model::Animation;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::Model;
using tdme::engine::model::Skinning;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Triangle;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::rendering::AnimationState;
using tdme::engine::subsystems::rendering::Object3DBase_TransformedFacesIterator;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;
using tdme::engine::subsystems::rendering::Object3DGroupVBORenderer;
using tdme::utils::Console;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Object3DBase::Object3DBase(Model* model, bool useMeshManager, Engine::AnimationProcessingTarget animationProcessingTarget)
{
	this->model = model;
	this->animationProcessingTarget = animationProcessingTarget;
	this->usesMeshManager = useMeshManager;
	transformedFacesIterator = nullptr;
	// skinning
	hasSkinning = false;
	if (model->hasSkinning() == true) {
		hasSkinning = true;
		skinningGroups.resize(determineSkinnedGroupCount(model->getSubGroups()));
		determineSkinnedGroups(model->getSubGroups(), skinningGroups, 0);
		skinningGroupsMatrices.resize(skinningGroups.size());
		for (auto i = 0; i < skinningGroups.size(); i++) {
			createTransformationsMatrices(&skinningGroupsMatrices[i], model->getSubGroups());
		}
	}
	//
	baseAnimationIdx = 0;
	// animation
	setAnimation(Model::ANIMATIONSETUP_DEFAULT);
	// create transformations matrices
	transformationsMatrices.push_back(new map<string, Matrix4x4*>());
	createTransformationsMatrices(transformationsMatrices[0], model->getSubGroups());
	// calculate transformations matrices
	computeTransformationsMatrices(model->getSubGroups(), model->getImportTransformationsMatrix(), &baseAnimations[0], transformationsMatrices[0], 0);
	if (hasSkinning == true) updateSkinningTransformationsMatrices(transformationsMatrices[0]);
	// object 3d groups
	Object3DGroup::createGroups(this, useMeshManager, animationProcessingTarget, object3dGroups);
	// do initial transformations if doing CPU no rendering for deriving bounding boxes and such
	if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) Object3DGroup::computeTransformations(object3dGroups);
	// reset animation
	if (baseAnimations.size() == 0) baseAnimations.push_back(AnimationState());
	baseAnimations[baseAnimationIdx].endAtTime = -1LL;
	baseAnimations[baseAnimationIdx].lastAtTime = Timing::UNDEFINED;
	baseAnimations[baseAnimationIdx].currentAtTime = 0LL;
	baseAnimations[baseAnimationIdx].time = 0.0f;
	baseAnimations[baseAnimationIdx].finished = false;
}

Object3DBase::~Object3DBase() {
	for (auto i = 0; i < object3dGroups.size(); i++) {
		delete object3dGroups[i];
	}
	for (auto baseAnimationTransformationsMatrices: transformationsMatrices) {
		for (auto it: *baseAnimationTransformationsMatrices) {
			delete it.second;
		}
		delete baseAnimationTransformationsMatrices;
	}
	for (auto skinningGroupMatricies: skinningGroupsMatrices) {
		for (auto it: skinningGroupMatricies) {
			delete it.second;
		}
	}
	if (transformedFacesIterator != nullptr) delete transformedFacesIterator;
}

void Object3DBase::setAnimation(const string& id)
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
		baseAnimation.finished = false;
		if (baseAnimations.size() == 0) {
			baseAnimations.push_back(baseAnimation);
			baseAnimationIdx = 0;
		} else
		if (baseAnimations.size() == 1) {
			baseAnimations.push_back(baseAnimation);
			baseAnimationIdx = 1;
			transformationsMatrices.push_back(new map<string, Matrix4x4*>());
			for (auto transformationMatrixIt: *transformationsMatrices[0]) (*transformationsMatrices[1])[transformationMatrixIt.first] = new Matrix4x4(*transformationMatrixIt.second);
			transformationsMatrices.push_back(new map<string, Matrix4x4*>());
			for (auto transformationMatrixIt: *transformationsMatrices[0]) (*transformationsMatrices[2])[transformationMatrixIt.first] = new Matrix4x4(*transformationMatrixIt.second);
		} else {
			baseAnimationIdx = (baseAnimationIdx + 1) % 2;
			baseAnimations[baseAnimationIdx] = baseAnimation;
		}
		if (baseAnimations.size() > 1) {
			auto baseAnimationIdxLast = (baseAnimationIdx + 1) % 2;
			auto& baseAnimationLast = baseAnimations[baseAnimationIdxLast];
			baseAnimationLast.endAtTime = baseAnimationLast.currentAtTime;
		}
	}
}

void Object3DBase::addOverlayAnimation(const string& id)
{
	// remove active overlay animation with given ids
	removeOverlayAnimation(id);
	// check overlay animation
	auto animationSetup = model->getAnimationSetup(id);
	if (animationSetup == nullptr)
		return;
	if (animationSetup->getOverlayFromGroupId().size() == 0)
		return;
	// create animation state
	auto animationState = new AnimationState();
	animationState->setup = animationSetup;
	animationState->lastAtTime = Timing::UNDEFINED;
	animationState->currentAtTime = 0LL;
	animationState->time = 0.0f;
	animationState->finished = false;
	// register overlay animation
	overlayAnimationsById[id] = animationState;
	overlayAnimationsByJointId[animationSetup->getOverlayFromGroupId()] = animationState;
}

void Object3DBase::removeOverlayAnimation(const string& id)
{
	auto animationStateIt = overlayAnimationsById.find(id);
	if (animationStateIt == overlayAnimationsById.end()) return;
	AnimationState* animationState = animationStateIt->second;
	overlayAnimationsById.erase(animationStateIt);
	auto overlayAnimationsByJointIdIt = overlayAnimationsByJointId.find(animationState->setup->getOverlayFromGroupId());
	if (overlayAnimationsByJointIdIt == overlayAnimationsByJointId.end()) return;
	overlayAnimationsByJointId.erase(overlayAnimationsByJointIdIt);
}

void Object3DBase::removeOverlayAnimationsFinished()
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

void Object3DBase::removeOverlayAnimations()
{
	// remove them
	vector<string> overlayAnimationsToRemove;
	for (auto it: overlayAnimationsById) {
		const string& id = it.first;
		AnimationState* animationState = it.second;
		overlayAnimationsToRemove.push_back(id);
	}
	for (auto animationState: overlayAnimationsToRemove) {
		removeOverlayAnimation(animationState);
	}
}

const string Object3DBase::getAnimation()
{
	return baseAnimations[baseAnimationIdx].setup == nullptr ? "none" : baseAnimations[baseAnimationIdx].setup->getId();
}

float Object3DBase::getAnimationTime()
{
	return baseAnimations[baseAnimationIdx].time;
}

bool Object3DBase::hasOverlayAnimation(const string& id)
{
	return overlayAnimationsById.find(id) != overlayAnimationsById.end();
}

float Object3DBase::getOverlayAnimationTime(const string& id)
{
	AnimationState* animationState = nullptr;
	auto animationStateIt = overlayAnimationsById.find(id);
	if (animationStateIt != overlayAnimationsById.end()) {
		animationState = animationStateIt->second;
	}
	return animationState == nullptr ? 1.0f : animationState->time;
}

Matrix4x4* Object3DBase::getTransformationsMatrix(const string& id)
{
	auto transformationMatrixIt = transformationsMatrices[0]->find(id);
	if (transformationMatrixIt != transformationsMatrices[0]->end()) {
		return transformationMatrixIt->second;
	}
	return nullptr;
}

void Object3DBase::createTransformationsMatrices(map<string, Matrix4x4*>* matrices, map<string, Group*>* groups)
{
	// iterate through groups
	for (auto it: *groups) {
		// put and associate transformation matrices with group
		Group* group = it.second;
		Matrix4x4* matrix = new Matrix4x4();
		matrix->identity();
		(*matrices)[group->getId()] = matrix;
		// do sub groups
		auto subGroups = group->getSubGroups();
		if (subGroups->size() > 0) {
			createTransformationsMatrices(matrices, subGroups);
		}
	}
}

void Object3DBase::computeTransformationsMatrices(map<string, Group*>* groups, Matrix4x4& parentTransformationsMatrix, AnimationState* animationState, map<string, Matrix4x4*>* transformationsMatrices, int32_t depth)
{
	// iterate through groups
	for (auto it: *groups) {
		Group* group = it.second;
		// check for overlay animation
		AnimationState* overlayAnimation = nullptr;
		auto overlayAnimationIt = overlayAnimationsByJointId.find(group->getId());
		if (overlayAnimationIt != overlayAnimationsByJointId.end()) {
			overlayAnimation = overlayAnimationIt->second;
		}
		if (overlayAnimation != nullptr) animationState = overlayAnimation;
		// group transformation matrix
		Matrix4x4 transformationsMatrix;
		// compute animation matrix if animation setups exist
		auto animation = group->getAnimation();
		// TODO: check if its better to not compute animation matrix if finished
		if (animation != nullptr) {
			auto animationMatrices = animation->getTransformationsMatrices();
			auto frames = animationState->setup->getFrames();
			auto fps = model->getFPS();
			// determine current and last matrix
			auto frameAtLast = (animationState->lastAtTime / 1000.0f) * fps;
			auto frameAtCurrent = (animationState->currentAtTime / 1000.0f) * fps;
			// check if looping is disabled
			if (animationState->setup->isLoop() == false && frameAtCurrent >= frames) {
				frameAtLast = frames - 1;
				frameAtCurrent = frames - 1;
				animationState->finished = true;
			}
			auto matrixAtLast = (static_cast< int32_t >(frameAtLast) % frames);
			auto matrixAtCurrent = (static_cast< int32_t >(frameAtCurrent) % frames);
			animationState->time = frames <= 1 ? 0.0f : static_cast< float >(matrixAtCurrent) / static_cast< float >((frames - 1));
			// compute animation transformations matrix
			auto t = frameAtCurrent - static_cast< float >(Math::floor(frameAtLast));
			if (t < 1.0f) {
				if (matrixAtLast == matrixAtCurrent) {
					matrixAtCurrent+= 1;
					if (matrixAtCurrent >= frames) {
						if (animationState->setup->isLoop() == true) {
							matrixAtCurrent = matrixAtCurrent % frames;
						} else {
							matrixAtCurrent = frames - 1;
						}
					}
				}
				Matrix4x4::interpolateLinear(
					(*animationMatrices)[matrixAtLast + animationState->setup->getStartFrame()],
					(*animationMatrices)[matrixAtCurrent + animationState->setup->getStartFrame()],
					t,
					transformationsMatrix
				);
			} else {
				transformationsMatrix.set((*animationMatrices)[matrixAtCurrent + animationState->setup->getStartFrame()]);
			}
		} else {
			// no animation matrix, set up local transformation matrix up as group matrix
			transformationsMatrix.set(group->getTransformationsMatrix());
		}
		// apply parent transformation matrix
		transformationsMatrix.multiply(parentTransformationsMatrix);
		// put and associate transformation matrices with group
		auto transformationMatrixIt = transformationsMatrices->find(group->getId());
		if (transformationMatrixIt != transformationsMatrices->end()) {
			transformationMatrixIt->second->set(transformationsMatrix);
		}
		// calculate for sub groups
		auto subGroups = group->getSubGroups();
		if (subGroups->size() > 0) {
			Matrix4x4 parentTransformationsMatrix;
			parentTransformationsMatrix.set(transformationsMatrix);
			computeTransformationsMatrices(subGroups, parentTransformationsMatrix, animationState, transformationsMatrices, depth + 1);
		}
	}
}

void Object3DBase::updateSkinningTransformationsMatrices(map<string, Matrix4x4*>* transformationsMatrices) {
	// TODO: Maybe optimize regarding map look ups
	for (auto i = 0; i < skinningGroups.size(); i++) {
		for (auto& skinningJoint: *skinningGroups[i]->getSkinning()->getJoints()) {
			auto transformationsMatrixIt = transformationsMatrices->find(skinningJoint.getGroupId());
			auto transformationsMatrix = transformationsMatrixIt != transformationsMatrices->end()?transformationsMatrixIt->second:nullptr;
			if (transformationsMatrix == nullptr) continue;
			auto skinningGroupMatrixIt = skinningGroupsMatrices[i].find(skinningJoint.getGroupId());
			if (skinningGroupMatrixIt != skinningGroupsMatrices[i].end()) {
				skinningGroupMatrixIt->second->set(skinningJoint.getBindMatrix()).multiply(*transformationsMatrix);
			}
		}
	}
}

void Object3DBase::computeTransformations(AnimationState& baseAnimation, map<string, Matrix4x4*>* transformationsMatrices, Timing* timing)
{
	// do transformations if we have a animation
	if (baseAnimation.setup != nullptr) {
		// animation timing
		baseAnimation.lastAtTime = baseAnimation.currentAtTime;
		auto currentFrameAtTime = timing->getCurrentFrameAtTime();
		auto lastFrameAtTime = timing->getLastFrameAtTime();
		// do progress of base animation
		baseAnimation.lastAtTime = baseAnimation.currentAtTime;
		if (lastFrameAtTime != Timing::UNDEFINED) {
			baseAnimation.currentAtTime += currentFrameAtTime - lastFrameAtTime;
		}
		// do progress of overlay animations
		for (auto it: overlayAnimationsById) {
			AnimationState* overlayAnimationState = it.second;
			overlayAnimationState->lastAtTime = overlayAnimationState->currentAtTime;
			if (lastFrameAtTime != Timing::UNDEFINED) {
				overlayAnimationState->currentAtTime += currentFrameAtTime - lastFrameAtTime;
			}
		}
		// set up parent transformations matrix
		Matrix4x4 parentTransformationsMatrix;
		parentTransformationsMatrix.set(model->getImportTransformationsMatrix());
		if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
			parentTransformationsMatrix.multiply(getTransformationsMatrix());
		}
		// calculate transformations matrices
		computeTransformationsMatrices(model->getSubGroups(), parentTransformationsMatrix, &baseAnimation, transformationsMatrices, 0);
		// do transformations in group render data
		Object3DGroup::computeTransformations(object3dGroups);
	} else
	if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
		// set up parent transformations matrix
		Matrix4x4 parentTransformationsMatrix;
		parentTransformationsMatrix.set(model->getImportTransformationsMatrix());
		if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
			parentTransformationsMatrix.multiply(getTransformationsMatrix());
		}
		// calculate transformations matrices
		computeTransformationsMatrices(model->getSubGroups(), parentTransformationsMatrix, &baseAnimation, transformationsMatrices, 0);
		// do transformations in group render data
		Object3DGroup::computeTransformations(object3dGroups);
	}
}

void Object3DBase::computeTransformations(Timing* timing) {
	// compute last animation matrices if required
	auto baseAnimationIdxLast = transformationsMatrices.size() > 1?(baseAnimationIdx + 1) % 2:-1;
	if (baseAnimationIdxLast != -1 &&
		baseAnimations[baseAnimationIdxLast].lastAtTime != -1LL) {
		computeTransformations(baseAnimations[baseAnimationIdxLast], transformationsMatrices[1 + baseAnimationIdxLast], timing);
	} else {
		baseAnimationIdxLast = -1;
	}

	// compute current animation matrices
	computeTransformations(baseAnimations[baseAnimationIdx], transformationsMatrices[transformationsMatrices.size() > 1?1 + baseAnimationIdx:baseAnimationIdx], timing);

	// blend if required
	if (transformationsMatrices.size() > 1) {
		for (auto transformationsMatrixIt: *transformationsMatrices[0]) {
			if (baseAnimationIdxLast != -1 &&
				baseAnimations[baseAnimationIdxLast].endAtTime != -1LL) {
				auto blendingAnimationDuration = static_cast<float>(baseAnimations[baseAnimationIdxLast].currentAtTime - baseAnimations[baseAnimationIdxLast].endAtTime) / 258.0f;
				Matrix4x4::interpolateLinear(
					*transformationsMatrices[1 + baseAnimationIdxLast]->find(transformationsMatrixIt.first)->second,
					*transformationsMatrices[1 + baseAnimationIdx]->find(transformationsMatrixIt.first)->second,
					Math::min(
						blendingAnimationDuration,
						1.0f
					),
					*transformationsMatrixIt.second
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
				transformationsMatrixIt.second->set(*transformationsMatrices[1 + baseAnimationIdx]->find(transformationsMatrixIt.first)->second);
			}
		}
	}
	if (hasSkinning == true) updateSkinningTransformationsMatrices(transformationsMatrices[0]);
}

int Object3DBase::getGroupCount() const {
	return object3dGroups.size();
}

void Object3DBase::getTriangles(vector<Triangle>& triangles, int groupIdx)
{
	if (groupIdx == -1) {
		for (auto object3DGroup : object3dGroups) {
			auto groupVerticesTransformed = &object3DGroup->mesh->transformedVertices;
			for (auto& facesEntity : *object3DGroup->group->getFacesEntities())
			for (auto& face : *facesEntity.getFaces()) {
				auto faceVertexIndices = face.getVertexIndices();
				triangles.push_back(
					Triangle(
						(*groupVerticesTransformed)[(*faceVertexIndices)[0]],
						(*groupVerticesTransformed)[(*faceVertexIndices)[1]],
						(*groupVerticesTransformed)[(*faceVertexIndices)[2]]
					)
				);
			}
		}
	} else {
		auto object3DGroup = object3dGroups[groupIdx];
		auto groupVerticesTransformed = &object3DGroup->mesh->transformedVertices;
		for (auto& facesEntity : *object3DGroup->group->getFacesEntities())
		for (auto& face : *facesEntity.getFaces()) {
			auto faceVertexIndices = face.getVertexIndices();
			triangles.push_back(
				Triangle(
					(*groupVerticesTransformed)[(*faceVertexIndices)[0]],
					(*groupVerticesTransformed)[(*faceVertexIndices)[1]],
					(*groupVerticesTransformed)[(*faceVertexIndices)[2]]
				)
			);
		}
	}
}

Object3DBase_TransformedFacesIterator* Object3DBase::getTransformedFacesIterator()
{
	if (transformedFacesIterator == nullptr) {
		transformedFacesIterator = new Object3DBase_TransformedFacesIterator(this);
	}
	return transformedFacesIterator;
}

Object3DGroupMesh* Object3DBase::getMesh(const string& groupId)
{
	// TODO: maybe rather use a hash map than an array to have a faster access
	for (auto object3DGroup : object3dGroups) {
		if (object3DGroup->group->getId() == groupId) {
			return object3DGroup->mesh;
		}
	}
	return nullptr;
}

int32_t Object3DBase::determineSkinnedGroupCount(map<string, Group*>* groups)
{
	return determineSkinnedGroupCount(groups, 0);
}

int32_t Object3DBase::determineSkinnedGroupCount(map<string, Group*>* groups, int32_t count)
{
	// iterate through groups
	for (auto it: *groups) {
		Group* group = it.second;
		//
		if (group->getSkinning() != nullptr)
			count++;
		// calculate sub groups
		auto subGroups = group->getSubGroups();
		if (subGroups->size() > 0) {
			count = determineSkinnedGroupCount(subGroups, count);
		}
	}
	return count;
}

int32_t Object3DBase::determineSkinnedGroups(map<string, Group*>* groups, vector<Group*>& skinningGroups, int32_t idx)
{
	// iterate through groups
	for (auto it: *groups) {
		Group* group = it.second;
		// fetch skinning groups
		if (group->getSkinning() != nullptr) {
			skinningGroups[idx++] = group;
		}
		// calculate sub groups
		auto subGroups = group->getSubGroups();
		if (subGroups->size() > 0) {
			idx = determineSkinnedGroups(subGroups, skinningGroups, idx);
		}
	}
	return idx;
}

map<string, Matrix4x4*>* Object3DBase::getSkinningGroupsMatrices(Group* group)
{
	if (hasSkinning == false)
		return nullptr;

	for (auto i = 0; i < skinningGroups.size(); i++) {
		if (skinningGroups[i] == group) {
			return &skinningGroupsMatrices[i];
		}
	}
	return nullptr;
}

void Object3DBase::initialize()
{
	auto meshManager = Engine::getInstance()->getMeshManager();
	// init mesh
	for (auto i = 0; i < object3dGroups.size(); i++) {
		auto object3DGroup = object3dGroups[i];
		// initiate mesh if not yet done, happens usually after disposing from engine and readding to engine
		if (object3DGroup->mesh == nullptr) {
			if (usesMeshManager == true) {
				object3DGroup->mesh = meshManager->getMesh(object3DGroup->id);
				if (object3DGroup->mesh == nullptr) {
					object3DGroup->mesh = Object3DGroupMesh::createMesh(
						object3DGroup->renderer,
						animationProcessingTarget,
						object3DGroup->group,
						object3DGroup->object->transformationsMatrices[0],
						getSkinningGroupsMatrices(object3DGroup->group)
					);
				}
			} else {
				object3DGroup->mesh = Object3DGroupMesh::createMesh(
					object3DGroup->renderer,
					animationProcessingTarget,
					object3DGroup->group,
					object3DGroup->object->transformationsMatrices[0],
					getSkinningGroupsMatrices(object3DGroup->group)
				);
			}
		}
	}
}

void Object3DBase::dispose()
{
	auto meshManager = Engine::getInstance()->getMeshManager();
	// dispose mesh
	for (auto i = 0; i < object3dGroups.size(); i++) {
		auto object3DGroup = object3dGroups[i];
		// dispose renderer
		object3DGroup->renderer->dispose();
		// dispose object3d group
		object3DGroup->dispose();
		// dispose mesh
		if (usesMeshManager == true) {
			meshManager->removeMesh(object3DGroup->id);
		} else {
			delete object3DGroup->mesh;
		}
		object3DGroup->mesh = nullptr;
	}
}

const Matrix4x4& Object3DBase::getTransformationsMatrix() const
{
	return Transformations::getTransformationsMatrix();
}

