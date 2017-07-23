// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DGroup.java
#include <tdme/engine/subsystems/object/Object3DGroup.h>

#include <map>
#include <string>
#include <vector>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <tdme/engine/Engine_AnimationProcessingTarget.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/subsystems/manager/MeshManager.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/object/Object3DBase.h>
#include <tdme/engine/subsystems/object/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/object/Object3DGroupVBORenderer.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::engine::subsystems::object::Object3DGroup;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using tdme::engine::Engine_AnimationProcessingTarget;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Skinning;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::object::Object3DBase;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::engine::subsystems::object::Object3DGroupVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::FacesEntity, ::java::lang::ObjectArray > FacesEntityArray;
typedef ::SubArray< ::tdme::engine::model::Joint, ::java::lang::ObjectArray > JointArray;
}  // namespace model

namespace subsystems {
namespace object {
typedef ::SubArray< ::tdme::engine::subsystems::object::Object3DGroup, ::java::lang::ObjectArray > Object3DGroupArray;
}  // namespace object
}  // namespace subsystems
}  // namespace engine
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

Object3DGroup::Object3DGroup(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Object3DGroup::Object3DGroup()
	: Object3DGroup(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void Object3DGroup::ctor()
{
	super::ctor();
	init();
}

void Object3DGroup::init()
{
	materialDiffuseTextureIdsByEntities = nullptr;
	dynamicDiffuseTextureIdsByEntities = nullptr;
	materialSpecularTextureIdsByEntities = nullptr;
	materialDisplacementTextureIdsByEntities = nullptr;
	materialNormalTextureIdsByEntities = nullptr;
	groupTransformationsMatrix = nullptr;
}

int64_t Object3DGroup::counter;

constexpr int32_t Object3DGroup::GLTEXTUREID_NONE;

constexpr int32_t Object3DGroup::GLTEXTUREID_NOTUSED;

Object3DGroupArray* Object3DGroup::createGroups(Object3DBase* object, bool useMeshManager, Engine_AnimationProcessingTarget* animationProcessingTarget)
{
	clinit();
	vector<Object3DGroup*> object3DGroups;
	auto model = object->getModel();
	createGroups(object, object3DGroups, model->getSubGroups(), model->hasAnimations(), useMeshManager, animationProcessingTarget);
	auto object3DGroupArray = new Object3DGroupArray(object3DGroups.size());
	int i = 0;
	for (auto object3DGroup: object3DGroups) {
		object3DGroupArray->set(i++, object3DGroup);
	}
	return object3DGroupArray;
}

void Object3DGroup::createGroups(Object3DBase* object3D, vector<Object3DGroup*>& object3DGroups, map<wstring, Group*>* groups, bool animated, bool useMeshManager, Engine_AnimationProcessingTarget* animationProcessingTarget)
{
	clinit();
	for (auto it: *groups) {
		Group* group = it.second;
		if (group->isJoint() == true) {
			continue;
		}
		auto faceCount = group->getFaceCount();
		if (faceCount > 0) {
			auto object3DGroup = new Object3DGroup();
			object3DGroups.push_back(object3DGroup);
			object3DGroup->id = ::java::lang::StringBuilder().append(group->getModel()->getId())->append(u":"_j)
				->append(group->getId())
				->append(u":"_j)
				->append(animationProcessingTarget->toString()->toLowerCase())->toString();
			if (animated == true && (animationProcessingTarget == Engine_AnimationProcessingTarget::CPU || animationProcessingTarget == Engine_AnimationProcessingTarget::CPU_NORENDERING)) {
				object3DGroup->id = ::java::lang::StringBuilder(object3DGroup->id).append(::java::lang::StringBuilder().append(u":"_j)->append((counter++))->toString())->toString();
			}
			object3DGroup->object = object3D;
			object3DGroup->group = group;
			object3DGroup->animated = animated;
			if (useMeshManager == true) {
				auto meshManager = Engine::getInstance()->getMeshManager();
				object3DGroup->mesh = meshManager->getMesh(object3DGroup->id);
				if (object3DGroup->mesh == nullptr) {
					object3DGroup->mesh = Object3DGroupMesh::createMesh(animationProcessingTarget, group, &object3D->transformationsMatrices, object3D->getSkinningGroupsMatrices(group));
					meshManager->addMesh(object3DGroup->id, object3DGroup->mesh);
				}
			} else {
				object3DGroup->mesh = Object3DGroupMesh::createMesh(animationProcessingTarget, group, &object3D->transformationsMatrices, object3D->getSkinningGroupsMatrices(group));
			}
			object3DGroup->materialDiffuseTextureIdsByEntities = new int32_tArray(group->getFacesEntities()->length);
			object3DGroup->dynamicDiffuseTextureIdsByEntities = new int32_tArray(group->getFacesEntities()->length);
			object3DGroup->materialSpecularTextureIdsByEntities = new int32_tArray(group->getFacesEntities()->length);
			object3DGroup->materialDisplacementTextureIdsByEntities = new int32_tArray(group->getFacesEntities()->length);
			object3DGroup->materialNormalTextureIdsByEntities = new int32_tArray(group->getFacesEntities()->length);
			for (auto j = 0; j < group->getFacesEntities()->length; j++) {
				(*object3DGroup->materialDiffuseTextureIdsByEntities)[j] = GLTEXTUREID_NONE;
				(*object3DGroup->dynamicDiffuseTextureIdsByEntities)[j] = GLTEXTUREID_NONE;
				(*object3DGroup->materialSpecularTextureIdsByEntities)[j] = GLTEXTUREID_NONE;
				(*object3DGroup->materialDisplacementTextureIdsByEntities)[j] = GLTEXTUREID_NONE;
				(*object3DGroup->materialNormalTextureIdsByEntities)[j] = GLTEXTUREID_NONE;
			}
			object3DGroup->renderer = new Object3DGroupVBORenderer(object3DGroup);
			auto groupTransformationsMatrixIt = object3D->transformationsMatrices.find(group->getId());
			object3DGroup->groupTransformationsMatrix = groupTransformationsMatrixIt != object3D->transformationsMatrices.end()?groupTransformationsMatrixIt->second:nullptr;
		}
		createGroups(object3D, object3DGroups, group->getSubGroups(), animated, useMeshManager, animationProcessingTarget);
	}
}

void Object3DGroup::computeTransformations(Object3DGroupArray* object3DGroups)
{
	clinit();
	for (auto object3DGroup : *object3DGroups) {
		object3DGroup->mesh->computeTransformations(object3DGroup->group);
	}
}

void Object3DGroup::setupTextures(GLRenderer* renderer, Object3DGroup* object3DGroup, int32_t facesEntityIdx)
{
	clinit();
	auto facesEntities = object3DGroup->group->getFacesEntities();
	auto material = (*facesEntities)[facesEntityIdx]->getMaterial();
	if (material == nullptr)
		material = Material::getDefaultMaterial();

	if ((*object3DGroup->materialDiffuseTextureIdsByEntities)[facesEntityIdx] == GLTEXTUREID_NONE) {
		if (material->getDiffuseTexture() != nullptr) {
			(*object3DGroup->materialDiffuseTextureIdsByEntities)[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(material->getDiffuseTexture());
		} else {
			(*object3DGroup->materialDiffuseTextureIdsByEntities)[facesEntityIdx] = GLTEXTUREID_NOTUSED;
		}
	}
	if (renderer->isSpecularMappingAvailable() == true && (*object3DGroup->materialSpecularTextureIdsByEntities)[facesEntityIdx] == GLTEXTUREID_NONE) {
		if (material->getSpecularTexture() != nullptr) {
			(*object3DGroup->materialSpecularTextureIdsByEntities)[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(material->getSpecularTexture());
		} else {
			(*object3DGroup->materialSpecularTextureIdsByEntities)[facesEntityIdx] = GLTEXTUREID_NOTUSED;
		}
	}
	if (renderer->isDisplacementMappingAvailable() == true && (*object3DGroup->materialDisplacementTextureIdsByEntities)[facesEntityIdx] == GLTEXTUREID_NONE) {
		if (material->getDisplacementTexture() != nullptr) {
			(*object3DGroup->materialDisplacementTextureIdsByEntities)[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(material->getDisplacementTexture());
		} else {
			(*object3DGroup->materialDisplacementTextureIdsByEntities)[facesEntityIdx] = GLTEXTUREID_NOTUSED;
		}
	}
	if (renderer->isNormalMappingAvailable() == true && (*object3DGroup->materialNormalTextureIdsByEntities)[facesEntityIdx] == GLTEXTUREID_NONE) {
		if (material->getNormalTexture() != nullptr) {
			(*object3DGroup->materialNormalTextureIdsByEntities)[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(material->getNormalTexture());
		} else {
			(*object3DGroup->materialNormalTextureIdsByEntities)[facesEntityIdx] = GLTEXTUREID_NOTUSED;
		}
	}
}

void Object3DGroup::dispose()
{
	auto engine = Engine::getInstance();
	auto textureManager = engine->getTextureManager();
	auto facesEntities = group->getFacesEntities();
	for (auto j = 0; j < facesEntities->length; j++) {
		auto material = (*facesEntities)[j]->getMaterial();
		if (material == nullptr)
			continue;

		auto glDiffuseTextureId = (*materialDiffuseTextureIdsByEntities)[j];
		if (glDiffuseTextureId != Object3DGroup::GLTEXTUREID_NONE && glDiffuseTextureId != Object3DGroup::GLTEXTUREID_NOTUSED) {
			if (material->getDiffuseTexture() != nullptr)
				textureManager->removeTexture(material->getDiffuseTexture()->getId());

			(*materialDiffuseTextureIdsByEntities)[j] = Object3DGroup::GLTEXTUREID_NONE;
		}
		auto glSpecularTextureId = (*materialSpecularTextureIdsByEntities)[j];
		if (glSpecularTextureId != Object3DGroup::GLTEXTUREID_NONE && glSpecularTextureId != Object3DGroup::GLTEXTUREID_NOTUSED) {
			if (material->getDiffuseTexture() != nullptr)
				textureManager->removeTexture(material->getSpecularTexture()->getId());

			(*materialSpecularTextureIdsByEntities)[j] = Object3DGroup::GLTEXTUREID_NONE;
		}
		auto glDisplacementTextureId = (*materialDisplacementTextureIdsByEntities)[j];
		if (glDisplacementTextureId != Object3DGroup::GLTEXTUREID_NONE && glDisplacementTextureId != Object3DGroup::GLTEXTUREID_NOTUSED) {
			if (material->getDisplacementTexture() != nullptr)
				textureManager->removeTexture(material->getDisplacementTexture()->getId());

			(*materialDisplacementTextureIdsByEntities)[j] = Object3DGroup::GLTEXTUREID_NONE;
		}
		auto glNormalTextureId = (*materialNormalTextureIdsByEntities)[j];
		if (glNormalTextureId != Object3DGroup::GLTEXTUREID_NONE && glNormalTextureId != Object3DGroup::GLTEXTUREID_NOTUSED) {
			if (material->getNormalTexture() != nullptr)
				textureManager->removeTexture(material->getNormalTexture()->getId());

			(*materialNormalTextureIdsByEntities)[j] = Object3DGroup::GLTEXTUREID_NONE;
		}
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Object3DGroup::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.Object3DGroup", 43);
    return c;
}

void Object3DGroup::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		counter = 0;
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* Object3DGroup::getClass0()
{
	return class_();
}

