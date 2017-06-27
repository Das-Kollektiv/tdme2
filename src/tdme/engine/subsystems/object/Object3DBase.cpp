// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DBase.java
#include <tdme/engine/subsystems/object/Object3DBase.h>

#include <java/lang/ArrayStoreException.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Math.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/util/Iterator.h>
#include <tdme/engine/Engine_AnimationProcessingTarget.h>
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
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_HashMap_KeysIterator.h>
#include <tdme/utils/_HashMap_ValuesIterator.h>
#include <tdme/utils/_HashMap.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using tdme::engine::subsystems::object::Object3DBase;
using java::lang::ArrayStoreException;
using java::lang::ClassCastException;
using java::lang::Math;
using java::lang::NullPointerException;
using java::lang::Object;
using java::lang::String;
using java::util::Iterator;
using tdme::engine::Engine_AnimationProcessingTarget;
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
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap_KeysIterator;
using tdme::utils::_HashMap_ValuesIterator;
using tdme::utils::_HashMap;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::Face, ::java::lang::ObjectArray > FaceArray;
typedef ::SubArray< ::tdme::engine::model::FacesEntity, ::java::lang::ObjectArray > FacesEntityArray;
typedef ::SubArray< ::tdme::engine::model::Group, ::java::lang::ObjectArray > GroupArray;
}  // namespace model

namespace primitives {
typedef ::SubArray< ::tdme::engine::primitives::BoundingVolume, ::java::lang::ObjectArray > BoundingVolumeArray;
typedef ::SubArray< ::tdme::engine::primitives::Triangle, ::java::lang::ObjectArray, BoundingVolumeArray > TriangleArray;
}  // namespace primitives

namespace subsystems {
namespace object {
typedef ::SubArray< ::tdme::engine::subsystems::object::Object3DGroup, ::java::lang::ObjectArray > Object3DGroupArray;
}  // namespace object
}  // namespace subsystems
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Matrix4x4, ::java::lang::ObjectArray > Matrix4x4Array;
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math

namespace utils {
typedef ::SubArray< ::tdme::utils::_HashMap, ::java::lang::ObjectArray > _HashMapArray;
}  // namespace utils
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

Object3DBase::Object3DBase(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Object3DBase::Object3DBase(Model* model, bool useMeshManager, Engine_AnimationProcessingTarget* animationProcessingTarget) 
	: Object3DBase(*static_cast< ::default_init_tag* >(0))
{
	ctor(model,useMeshManager,animationProcessingTarget);
}

void Object3DBase::init()
{
	object3dGroups = nullptr;
}

void Object3DBase::ctor(Model* model, bool useMeshManager, Engine_AnimationProcessingTarget* animationProcessingTarget)
{
	super::ctor();
	init();
	this->model = model;
	this->animationProcessingTarget = animationProcessingTarget;
	this->baseAnimation = new AnimationState();
	this->overlayAnimationsById = new _HashMap();
	this->overlayAnimationsByJointId = new _HashMap();
	this->usesMeshManager = useMeshManager;
	this->overlayAnimationsToRemove = new _ArrayList();
	transformationsMatrices = new _HashMap();
	parentTransformationsMatrix = new Matrix4x4();
	transformationsMatrix = super::getTransformationsMatrix();
	tmpMatrix1 = new Matrix4x4();
	transformedFacesIterator = nullptr;
	hasSkinning = false;
	skinningGroupsMatrices = nullptr;
	skinningGroups = nullptr;
	if (model->hasSkinning() == true) {
		hasSkinning = true;
		skinningGroups = new GroupArray(determineSkinnedGroupCount(model->getSubGroups()));
		determineSkinnedGroups(model->getSubGroups(), skinningGroups, 0);
		skinningGroupsMatrices = new _HashMapArray(skinningGroups->length);
		for (auto i = 0; i < skinningGroups->length; i++) {
			skinningGroupsMatrices->set(i, new _HashMap());
			createTransformationsMatrices((*skinningGroupsMatrices)[i], model->getSubGroups());
		}
	}
	setAnimation(Model::ANIMATIONSETUP_DEFAULT);
	createTransformationsMatrices(transformationsMatrices, model->getSubGroups());
	object3dGroups = Object3DGroup::createGroups(this, useMeshManager, animationProcessingTarget);
	auto transformationsMatricesStackDepth = determineTransformationsMatricesStackDepth(model->getSubGroups(), 0);
	transformationsMatricesStack = new Matrix4x4Array(transformationsMatricesStackDepth);
	for (auto i = 0; i < transformationsMatricesStack->length; i++) {
		transformationsMatricesStack->set(i, new Matrix4x4());
	}
	computeTransformationsMatrices(model->getSubGroups(), model->getImportTransformationsMatrix(), baseAnimation, 0);
	Object3DGroup::computeTransformations(object3dGroups, transformationsMatrices);
	setAnimation(Model::ANIMATIONSETUP_DEFAULT);
}

Model* Object3DBase::getModel()
{
	return model;
}

void Object3DBase::setAnimation(String* id)
{
	auto _animationActiveSetup = model->getAnimationSetup(id);
	if (_animationActiveSetup != nullptr) {
		baseAnimation->setup = _animationActiveSetup;
		baseAnimation->lastAtTime = Timing::UNDEFINED;
		baseAnimation->currentAtTime = 0LL;
		baseAnimation->time = 0.0f;
		baseAnimation->finished = false;
	}
}

void Object3DBase::addOverlayAnimation(String* id)
{
	removeOverlayAnimation(id);
	auto animationSetup = model->getAnimationSetup(id);
	if (animationSetup == nullptr)
		return;

	if (animationSetup->getOverlayFromGroupId() == nullptr)
		return;

	auto animationState = new AnimationState();
	animationState->setup = animationSetup;
	animationState->lastAtTime = Timing::UNDEFINED;
	animationState->currentAtTime = 0LL;
	animationState->time = 0.0f;
	animationState->finished = false;
	overlayAnimationsById->put(id, animationState);
	overlayAnimationsByJointId->put(animationSetup->getOverlayFromGroupId(), animationState);
}

void Object3DBase::removeOverlayAnimation(String* id)
{
	auto animationState = java_cast< AnimationState* >(overlayAnimationsById->remove(id));
	if (animationState != nullptr)
		overlayAnimationsByJointId->remove(animationState->setup->getOverlayFromGroupId());

}

void Object3DBase::removeOverlayAnimation(AnimationState* animationState)
{
	auto _animationState = java_cast< AnimationState* >(overlayAnimationsById->remove(animationState->setup->getId()));
	if (_animationState != nullptr)
		overlayAnimationsByJointId->remove(_animationState->setup->getOverlayFromGroupId());

}

void Object3DBase::removeOverlayAnimationsFinished()
{
	overlayAnimationsToRemove->clear();
	for (auto _i = overlayAnimationsById->getValuesIterator()->iterator(); _i->hasNext(); ) {
		AnimationState* animationState = java_cast< AnimationState* >(_i->next());
		{
			if (animationState->finished == true) {
				overlayAnimationsToRemove->add(animationState);
			}
		}
	}
	for (auto i = 0; i < overlayAnimationsToRemove->size(); i++) {
		removeOverlayAnimation(java_cast< AnimationState* >(overlayAnimationsToRemove->get(i)));
	}
}

void Object3DBase::removeOverlayAnimations()
{
	for (auto _i = overlayAnimationsById->getKeysIterator()->iterator(); _i->hasNext(); ) {
		String* overlayAnimationId = java_cast< String* >(_i->next());
		{
			removeOverlayAnimation(overlayAnimationId);
		}
	}
}

String* Object3DBase::getAnimation()
{
	return baseAnimation->setup == nullptr ? u"none"_j : baseAnimation->setup->getId();
}

float Object3DBase::getAnimationTime()
{
	return baseAnimation->time;
}

bool Object3DBase::hasOverlayAnimation(String* id)
{
	return java_cast< AnimationState* >(overlayAnimationsById->get(id)) != nullptr;
}

float Object3DBase::getOverlayAnimationTime(String* id)
{
	auto animationState = java_cast< AnimationState* >(overlayAnimationsById->get(id));
	return animationState == nullptr ? 1.0f : animationState->time;
}

Matrix4x4* Object3DBase::getTransformationsMatrix(String* id)
{
	return java_cast< Matrix4x4* >(transformationsMatrices->get(id));
}

void Object3DBase::createTransformationsMatrices(_HashMap* matrices, _HashMap* groups)
{
	for (auto _i = groups->getValuesIterator()->iterator(); _i->hasNext(); ) {
		Group* group = java_cast< Group* >(_i->next());
		{
			matrices->put(group->getId(), (new Matrix4x4())->identity());
			auto subGroups = group->getSubGroups();
			if (subGroups->size() > 0) {
				createTransformationsMatrices(matrices, subGroups);
			}
		}
	}
}

void Object3DBase::computeTransformationsMatrices(_HashMap* groups, Matrix4x4* parentTransformationsMatrix, AnimationState* animationState, int32_t depth)
{
	for (auto _i = groups->getValuesIterator()->iterator(); _i->hasNext(); ) {
		Group* group = java_cast< Group* >(_i->next());
		{
			auto overlayAnimation = java_cast< AnimationState* >(overlayAnimationsByJointId->get(group->getId()));
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
					transformationsMatrix = Matrix4x4::interpolateLinear((*animationMatrices)[matrixAtLast + animationState->setup->getStartFrame()], (*animationMatrices)[matrixAtCurrent + animationState->setup->getStartFrame()], t, tmpMatrix1);
				} else {
					transformationsMatrix = tmpMatrix1->set((*animationMatrices)[matrixAtCurrent + animationState->setup->getStartFrame()]);
				}
			}
			if (transformationsMatrix == nullptr) {
				transformationsMatrix = tmpMatrix1->set(group->getTransformationsMatrix());
			}
			if (parentTransformationsMatrix != nullptr) {
				transformationsMatrix->multiply(parentTransformationsMatrix);
			}
			java_cast< Matrix4x4* >(transformationsMatrices->get(group->getId()))->set(transformationsMatrix);
			if (hasSkinning == true) {
				for (auto i = 0; i < skinningGroups->length; i++) {
					auto skinningJoint = (*skinningGroups)[i]->getSkinning()->getJointByName(group->getId());
					if (skinningJoint == nullptr) {
						java_cast< Matrix4x4* >((*skinningGroupsMatrices)[i]->get(group->getId()))->set(transformationsMatrix);
					} else {
						java_cast< Matrix4x4* >((*skinningGroupsMatrices)[i]->get(group->getId()))->set(skinningJoint->getBindMatrix())->multiply(transformationsMatrix);
					}
				}
			}
			auto subGroups = group->getSubGroups();
			if (subGroups->size() > 0) {
				(*transformationsMatricesStack)[depth]->set(transformationsMatrix);
				computeTransformationsMatrices(subGroups, (*transformationsMatricesStack)[depth], animationState, depth + 1);
			}
		}
	}
}

int32_t Object3DBase::determineTransformationsMatricesStackDepth(_HashMap* groups, int32_t depth)
{
	auto depthMax = depth;
	for (auto _i = groups->getValuesIterator()->iterator(); _i->hasNext(); ) {
		Group* group = java_cast< Group* >(_i->next());
		{
			auto subGroups = group->getSubGroups();
			if (subGroups->size() > 0) {
				auto _depth = determineTransformationsMatricesStackDepth(subGroups, depth + 1);
				if (_depth > depthMax)
					depthMax = _depth;

			}
		}
	}
	return depthMax;
}

void Object3DBase::computeTransformations()
{
	if (baseAnimation->setup != nullptr) {
		auto engine = Engine::getInstance();
		auto timing = engine->getTiming();
		baseAnimation->lastAtTime = baseAnimation->currentAtTime;
		auto currentFrameAtTime = timing->getCurrentFrameAtTime();
		auto lastFrameAtTime = timing->getLastFrameAtTime();
		baseAnimation->lastAtTime = baseAnimation->currentAtTime;
		if (lastFrameAtTime != Timing::UNDEFINED) {
			baseAnimation->currentAtTime += currentFrameAtTime - lastFrameAtTime;
		}
		for (auto _i = overlayAnimationsById->getValuesIterator()->iterator(); _i->hasNext(); ) {
			AnimationState* overlayAnimationState = java_cast< AnimationState* >(_i->next());
			{
				overlayAnimationState->lastAtTime = overlayAnimationState->currentAtTime;
				if (lastFrameAtTime != Timing::UNDEFINED) {
					overlayAnimationState->currentAtTime += currentFrameAtTime - lastFrameAtTime;
				}
			}
		}
		parentTransformationsMatrix->set(model->getImportTransformationsMatrix());
		if (animationProcessingTarget == Engine_AnimationProcessingTarget::CPU_NORENDERING) {
			parentTransformationsMatrix->multiply(transformationsMatrix);
		}
		computeTransformationsMatrices(model->getSubGroups(), parentTransformationsMatrix, baseAnimation, 0);
		Object3DGroup::computeTransformations(object3dGroups, transformationsMatrices);
	} else if (animationProcessingTarget == Engine_AnimationProcessingTarget::CPU_NORENDERING) {
		parentTransformationsMatrix->set(model->getImportTransformationsMatrix());
		if (animationProcessingTarget == Engine_AnimationProcessingTarget::CPU_NORENDERING) {
			parentTransformationsMatrix->multiply(transformationsMatrix);
		}
		computeTransformationsMatrices(model->getSubGroups(), parentTransformationsMatrix, baseAnimation, 0);
		Object3DGroup::computeTransformations(object3dGroups, transformationsMatrices);
	}
}

TriangleArray* Object3DBase::getFaceTriangles()
{
	auto triangles = new _ArrayList();
	for (auto object3DGroup : *object3dGroups) {
		auto groupVerticesTransformed = object3DGroup->mesh->vertices;
		for (auto facesEntity : *object3DGroup->group->getFacesEntities()) 
						for (auto face : *facesEntity->getFaces()) {
				auto faceVertexIndices = face->getVertexIndices();
				triangles->add(new Triangle((*groupVerticesTransformed)[(*faceVertexIndices)[0]]->clone(), (*groupVerticesTransformed)[(*faceVertexIndices)[1]]->clone(), (*groupVerticesTransformed)[(*faceVertexIndices)[2]]->clone()));
			}

	}
	auto triangleArray = new TriangleArray(triangles->size());
	triangles->toArray(triangleArray);
	return triangleArray;
}

Object3DBase_TransformedFacesIterator* Object3DBase::getTransformedFacesIterator()
{
	if (transformedFacesIterator == nullptr) {
		transformedFacesIterator = new Object3DBase_TransformedFacesIterator(this);
	}
	return transformedFacesIterator;
}

Object3DGroupMesh* Object3DBase::getMesh(String* groupId)
{
	for (auto object3DGroup : *object3dGroups) {
		if (object3DGroup->group->getId()->equals(groupId)) {
			return object3DGroup->mesh;
		}
	}
	return nullptr;
}

int32_t Object3DBase::determineSkinnedGroupCount(_HashMap* groups)
{
	return determineSkinnedGroupCount(groups, 0);
}

int32_t Object3DBase::determineSkinnedGroupCount(_HashMap* groups, int32_t count)
{
	for (auto _i = groups->getValuesIterator()->iterator(); _i->hasNext(); ) {
		Group* group = java_cast< Group* >(_i->next());
		{
			if (group->getSkinning() != nullptr)
				count++;

			auto subGroups = group->getSubGroups();
			if (subGroups->size() > 0) {
				count = determineSkinnedGroupCount(subGroups, count);
			}
		}
	}
	return count;
}

int32_t Object3DBase::determineSkinnedGroups(_HashMap* groups, GroupArray* skinningGroups, int32_t idx)
{
	for (auto _i = groups->getValuesIterator()->iterator(); _i->hasNext(); ) {
		Group* group = java_cast< Group* >(_i->next());
		{
			if (group->getSkinning() != nullptr) {
				skinningGroups->set(idx++, group);
			}
			auto subGroups = group->getSubGroups();
			if (subGroups->size() > 0) {
				idx = determineSkinnedGroups(subGroups, skinningGroups, idx);
			}
		}
	}
	return idx;
}

_HashMap* Object3DBase::getSkinningGroupsMatrices(Group* group)
{
	if (hasSkinning == false)
		return nullptr;

	for (auto i = 0; i < skinningGroups->length; i++) {
		if ((*skinningGroups)[i] == group) {
			return (*skinningGroupsMatrices)[i];
		}
	}
	return nullptr;
}

void Object3DBase::initialize()
{
	auto meshManager = Engine::getInstance()->getMeshManager();
	for (auto i = 0; i < object3dGroups->length; i++) {
		auto object3DGroup = (*object3dGroups)[i];
		if (object3DGroup->mesh == nullptr) {
			if (usesMeshManager == true) {
				object3DGroup->mesh = meshManager->getMesh(object3DGroup->id);
				if (object3DGroup->mesh == nullptr) {
					object3DGroup->mesh = Object3DGroupMesh::createMesh(animationProcessingTarget, object3DGroup->group, object3DGroup->object->transformationsMatrices, getSkinningGroupsMatrices(object3DGroup->group));
				}
			} else {
				object3DGroup->mesh = Object3DGroupMesh::createMesh(animationProcessingTarget, object3DGroup->group, object3DGroup->object->transformationsMatrices, getSkinningGroupsMatrices(object3DGroup->group));
			}
		}
	}
}

void Object3DBase::dispose()
{
	auto meshManager = Engine::getInstance()->getMeshManager();
	for (auto i = 0; i < object3dGroups->length; i++) {
		auto object3DGroup = (*object3dGroups)[i];
		meshManager->removeMesh(object3DGroup->id);
		object3DGroup->mesh = nullptr;
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Object3DBase::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.Object3DBase", 42);
    return c;
}

Matrix4x4* Object3DBase::getTransformationsMatrix()
{
	return super::getTransformationsMatrix();
}

java::lang::Class* Object3DBase::getClass0()
{
	return class_();
}

