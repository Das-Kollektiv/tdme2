#include <tdme/engine/subsystems/object/Object3DBase.h>

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
#include <tdme/engine/subsystems/object/AnimationState.h>
#include <tdme/engine/subsystems/object/Object3DBase_TransformedFacesIterator.h>
#include <tdme/engine/subsystems/object/Object3DGroup.h>
#include <tdme/engine/subsystems/object/Object3DGroupMesh.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::engine::subsystems::object::Object3DBase;
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
using tdme::engine::subsystems::object::AnimationState;
using tdme::engine::subsystems::object::Object3DBase_TransformedFacesIterator;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Object3DBase::Object3DBase(Model* model, bool useMeshManager, Engine::AnimationProcessingTarget animationProcessingTarget)
{
	this->model = model;
	this->animationProcessingTarget = animationProcessingTarget;
	this->usesMeshManager = useMeshManager;
	tmpMatrix1 = new Matrix4x4();
	transformedFacesIterator = nullptr;
	hasSkinning = false;
	if (model->hasSkinning() == true) {
		hasSkinning = true;
		skinningGroups.resize(determineSkinnedGroupCount(model->getSubGroups()));
		determineSkinnedGroups(model->getSubGroups(), &skinningGroups, 0);
		skinningGroupsMatrices.resize(skinningGroups.size());
		for (auto i = 0; i < skinningGroups.size(); i++) {
			createTransformationsMatrices(&skinningGroupsMatrices[i], model->getSubGroups());
		}
	}
	setAnimation(Model::ANIMATIONSETUP_DEFAULT);
	createTransformationsMatrices(&transformationsMatrices, model->getSubGroups());
	Object3DGroup::createGroups(this, useMeshManager, animationProcessingTarget, &object3dGroups);
	computeTransformationsMatrices(model->getSubGroups(), model->getImportTransformationsMatrix(), &baseAnimation, 0);
	Object3DGroup::computeTransformations(&object3dGroups);
	setAnimation(Model::ANIMATIONSETUP_DEFAULT);
}

Model* Object3DBase::getModel()
{
	return model;
}

void Object3DBase::setAnimation(const wstring& id)
{
	auto _animationActiveSetup = model->getAnimationSetup(id);
	if (_animationActiveSetup != nullptr) {
		baseAnimation.setup = _animationActiveSetup;
		baseAnimation.lastAtTime = Timing::UNDEFINED;
		baseAnimation.currentAtTime = 0LL;
		baseAnimation.time = 0.0f;
		baseAnimation.finished = false;
	}
}

void Object3DBase::addOverlayAnimation(const wstring& id)
{
	removeOverlayAnimation(id);
	auto animationSetup = model->getAnimationSetup(id);
	if (animationSetup == nullptr)
		return;

	if (animationSetup->getOverlayFromGroupId().size() == 0)
		return;

	auto animationState = new AnimationState();
	animationState->setup = animationSetup;
	animationState->lastAtTime = Timing::UNDEFINED;
	animationState->currentAtTime = 0LL;
	animationState->time = 0.0f;
	animationState->finished = false;
	overlayAnimationsById[id] = animationState;
	overlayAnimationsByJointId[animationSetup->getOverlayFromGroupId()] = animationState;
}

void Object3DBase::removeOverlayAnimation(const wstring& id)
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
	vector<wstring> overlayAnimationsToRemove;
	for (auto it: overlayAnimationsById) {
		const wstring& id = it.first;
		AnimationState* animationState = it.second;
		{
			if (animationState->finished == true) {
				overlayAnimationsToRemove.push_back(id);
			}
		}
	}
	for (auto animationState: overlayAnimationsToRemove) {
		removeOverlayAnimation(animationState);
	}
}

void Object3DBase::removeOverlayAnimations()
{
	vector<wstring> overlayAnimationsToRemove;
	for (auto it: overlayAnimationsById) {
		const wstring& id = it.first;
		AnimationState* animationState = it.second;
		overlayAnimationsToRemove.push_back(id);
	}
	for (auto animationState: overlayAnimationsToRemove) {
		removeOverlayAnimation(animationState);
	}
}

const wstring Object3DBase::getAnimation()
{
	return baseAnimation.setup == nullptr ? L"none" : baseAnimation.setup->getId();
}

float Object3DBase::getAnimationTime()
{
	return baseAnimation.time;
}

bool Object3DBase::hasOverlayAnimation(const wstring& id)
{
	return overlayAnimationsById.find(id) != overlayAnimationsById.end();
}

float Object3DBase::getOverlayAnimationTime(const wstring& id)
{
	AnimationState* animationState = nullptr;
	auto animationStateIt = overlayAnimationsById.find(id);
	if (animationStateIt != overlayAnimationsById.end()) {
		animationState = animationStateIt->second;
	}
	return animationState == nullptr ? 1.0f : animationState->time;
}

Matrix4x4* Object3DBase::getTransformationsMatrix(const wstring& id)
{
	auto transformationMatrixIt = transformationsMatrices.find(id);
	if (transformationMatrixIt != transformationsMatrices.end()) {
		return transformationMatrixIt->second;
	}
	return nullptr;
}

void Object3DBase::createTransformationsMatrices(map<wstring, Matrix4x4*>* matrices, map<wstring, Group*>* groups)
{
	for (auto it: *groups) {
		Group* group = it.second;
		Matrix4x4* matrix = new Matrix4x4();
		matrix->identity();
		(*matrices)[group->getId()] = matrix;
		auto subGroups = group->getSubGroups();
		if (subGroups->size() > 0) {
			createTransformationsMatrices(matrices, subGroups);
		}
	}
}

void Object3DBase::computeTransformationsMatrices(map<wstring, Group*>* groups, Matrix4x4* parentTransformationsMatrix, AnimationState* animationState, int32_t depth)
{
	for (auto it: *groups) {
		Group* group = it.second;
		AnimationState* overlayAnimation = nullptr;
		auto overlayAnimationIt = overlayAnimationsByJointId.find(group->getId());
		if (overlayAnimationIt != overlayAnimationsByJointId.end()) {
			overlayAnimation = overlayAnimationIt->second;
		}
		if (overlayAnimation != nullptr)
			animationState = overlayAnimation;

		Matrix4x4* transformationsMatrix = nullptr;
		auto animation = group->getAnimation();
		if (animation != nullptr && animationState->finished == false) {
			auto animationMatrices = animation->getTransformationsMatrices();
			auto frames = animationState->setup->getFrames();
			auto fps = model->getFPS();
			auto frameAtLast = (animationState->lastAtTime / 1000.0f) * fps;
			auto frameAtCurrent = (animationState->currentAtTime / 1000.0f) * fps;
			if (animationState->setup->isLoop() == false && frameAtCurrent >= frames) {
				frameAtLast = frames - 1;
				frameAtCurrent = frames - 1;
				animationState->finished = true;
			}
			auto matrixAtLast = (static_cast< int32_t >(frameAtLast) % frames);
			auto matrixAtCurrent = (static_cast< int32_t >(frameAtCurrent) % frames);
			animationState->time = frames <= 1 ? 0.0f : static_cast< float >(matrixAtCurrent) / static_cast< float >((frames - 1));
			auto t = frameAtCurrent - static_cast< float >(Math::floor(frameAtLast));
			if (t < 1.0f) {
				if (matrixAtLast == matrixAtCurrent) {
					matrixAtCurrent = ((matrixAtCurrent + 1) % frames);
				}
				transformationsMatrix = Matrix4x4::interpolateLinear(
					&(*animationMatrices)[matrixAtLast + animationState->setup->getStartFrame()],
					&(*animationMatrices)[matrixAtCurrent + animationState->setup->getStartFrame()],
					t,
					tmpMatrix1
				);
			} else {
				transformationsMatrix = tmpMatrix1->set(&(*animationMatrices)[matrixAtCurrent + animationState->setup->getStartFrame()]);
			}
		}
		if (transformationsMatrix == nullptr) {
			transformationsMatrix = tmpMatrix1->set(group->getTransformationsMatrix());
		}
		if (parentTransformationsMatrix != nullptr) {
			transformationsMatrix->multiply(parentTransformationsMatrix);
		}
		auto transformationMatrixIt = transformationsMatrices.find(group->getId());
		if (transformationMatrixIt != transformationsMatrices.end()) {
			transformationMatrixIt->second->set(transformationsMatrix);
		}
		if (hasSkinning == true) {
			for (auto i = 0; i < skinningGroups.size(); i++) {
				auto skinningJoint = skinningGroups[i]->getSkinning()->getJointByName(group->getId());
				if (skinningJoint == nullptr) {
					auto skinningGroupMatrixIt = skinningGroupsMatrices.at(i).find(group->getId());
					if (skinningGroupMatrixIt != skinningGroupsMatrices.at(i).end()) {
						skinningGroupMatrixIt->second->set(transformationsMatrix);
					}
				} else {
					auto skinningGroupMatrixIt = skinningGroupsMatrices.at(i).find(group->getId());
					if (skinningGroupMatrixIt != skinningGroupsMatrices.at(i).end()) {
						skinningGroupMatrixIt->second->set(skinningJoint->getBindMatrix())->multiply(transformationsMatrix);
					}
				}
			}
		}
		auto subGroups = group->getSubGroups();
		if (subGroups->size() > 0) {
			Matrix4x4 parentTransformationsMatrix;
			parentTransformationsMatrix.set(transformationsMatrix);
			computeTransformationsMatrices(subGroups, &parentTransformationsMatrix, animationState, depth + 1);
		}
	}
}

void Object3DBase::computeTransformations()
{
	if (baseAnimation.setup != nullptr) {
		auto engine = Engine::getInstance();
		auto timing = engine->getTiming();
		baseAnimation.lastAtTime = baseAnimation.currentAtTime;
		auto currentFrameAtTime = timing->getCurrentFrameAtTime();
		auto lastFrameAtTime = timing->getLastFrameAtTime();
		baseAnimation.lastAtTime = baseAnimation.currentAtTime;
		if (lastFrameAtTime != Timing::UNDEFINED) {
			baseAnimation.currentAtTime += currentFrameAtTime - lastFrameAtTime;
		}
		for (auto it: overlayAnimationsById) {
			AnimationState* overlayAnimationState = it.second;
			overlayAnimationState->lastAtTime = overlayAnimationState->currentAtTime;
			if (lastFrameAtTime != Timing::UNDEFINED) {
				overlayAnimationState->currentAtTime += currentFrameAtTime - lastFrameAtTime;
			}
		}
		Matrix4x4 parentTransformationsMatrix;
		parentTransformationsMatrix.set(model->getImportTransformationsMatrix());
		if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
			parentTransformationsMatrix.multiply(getTransformationsMatrix());
		}
		computeTransformationsMatrices(model->getSubGroups(), &parentTransformationsMatrix, &baseAnimation, 0);
		Object3DGroup::computeTransformations(&object3dGroups);
	} else
	if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
		Matrix4x4 parentTransformationsMatrix;
		parentTransformationsMatrix.set(model->getImportTransformationsMatrix());
		if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
			parentTransformationsMatrix.multiply(getTransformationsMatrix());
		}
		computeTransformationsMatrices(model->getSubGroups(), &parentTransformationsMatrix, &baseAnimation, 0);
		Object3DGroup::computeTransformations(&object3dGroups);
	}
}

void Object3DBase::getFaceTriangles(vector<Triangle>* faceTriangles)
{
	for (auto object3DGroup : object3dGroups) {
		auto groupVerticesTransformed = object3DGroup->mesh->vertices;
		for (auto facesEntity : *object3DGroup->group->getFacesEntities()) 
		for (auto& face : *facesEntity.getFaces()) {
			auto faceVertexIndices = face.getVertexIndices();
			faceTriangles->push_back(
				Triangle(
					(*groupVerticesTransformed)[(*faceVertexIndices)[0]].clone(),
					(*groupVerticesTransformed)[(*faceVertexIndices)[1]].clone(),
					(*groupVerticesTransformed)[(*faceVertexIndices)[2]].clone()
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

Object3DGroupMesh* Object3DBase::getMesh(const wstring& groupId)
{
	for (auto object3DGroup : object3dGroups) {
		if (object3DGroup->group->getId() == groupId) {
			return object3DGroup->mesh;
		}
	}
	return nullptr;
}

int32_t Object3DBase::determineSkinnedGroupCount(map<wstring, Group*>* groups)
{
	return determineSkinnedGroupCount(groups, 0);
}

int32_t Object3DBase::determineSkinnedGroupCount(map<wstring, Group*>* groups, int32_t count)
{
	for (auto it: *groups) {
		Group* group = it.second;
		if (group->getSkinning() != nullptr)
			count++;

		auto subGroups = group->getSubGroups();
		if (subGroups->size() > 0) {
			count = determineSkinnedGroupCount(subGroups, count);
		}
	}
	return count;
}

int32_t Object3DBase::determineSkinnedGroups(map<wstring, Group*>* groups, vector<Group*>* skinningGroups, int32_t idx)
{
	for (auto it: *groups) {
		Group* group = it.second;
		if (group->getSkinning() != nullptr) {
			(*skinningGroups)[idx++] = group;
		}
		auto subGroups = group->getSubGroups();
		if (subGroups->size() > 0) {
			idx = determineSkinnedGroups(subGroups, skinningGroups, idx);
		}
	}
	return idx;
}

map<wstring, Matrix4x4*>* Object3DBase::getSkinningGroupsMatrices(Group* group)
{
	if (hasSkinning == false)
		return nullptr;

	for (auto i = 0; i < skinningGroups.size(); i++) {
		if (skinningGroups.at(i) == group) {
			return &skinningGroupsMatrices.at(i);
		}
	}
	return nullptr;
}

void Object3DBase::initialize()
{
	auto meshManager = Engine::getInstance()->getMeshManager();
	for (auto i = 0; i < object3dGroups.size(); i++) {
		auto object3DGroup = object3dGroups[i];
		if (object3DGroup->mesh == nullptr) {
			if (usesMeshManager == true) {
				object3DGroup->mesh = meshManager->getMesh(object3DGroup->id);
				if (object3DGroup->mesh == nullptr) {
					object3DGroup->mesh = Object3DGroupMesh::createMesh(animationProcessingTarget, object3DGroup->group, &object3DGroup->object->transformationsMatrices, getSkinningGroupsMatrices(object3DGroup->group));
				}
			} else {
				object3DGroup->mesh = Object3DGroupMesh::createMesh(animationProcessingTarget, object3DGroup->group, &object3DGroup->object->transformationsMatrices, getSkinningGroupsMatrices(object3DGroup->group));
			}
		}
	}
}

void Object3DBase::dispose()
{
	auto meshManager = Engine::getInstance()->getMeshManager();
	for (auto i = 0; i < object3dGroups.size(); i++) {
		auto object3DGroup = object3dGroups[i];
		meshManager->removeMesh(object3DGroup->id);
		object3DGroup->mesh = nullptr;
	}
}

Matrix4x4* Object3DBase::getTransformationsMatrix()
{
	return Transformations::getTransformationsMatrix();
}

