#include <tdme/engine/subsystems/rendering/Object3DGroup.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/subsystems/manager/MeshManager.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/rendering/Object3DBase.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupVBORenderer.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>

using std::map;
using std::vector;
using std::string;
using std::to_string;

using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Skinning;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::rendering::Object3DBase;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;
using tdme::engine::subsystems::rendering::Object3DGroupVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;

int64_t Object3DGroup::counter = 0;
constexpr int32_t Object3DGroup::GLTEXTUREID_NONE;
constexpr int32_t Object3DGroup::GLTEXTUREID_NOTUSED;

Object3DGroup::Object3DGroup()
{
	groupTransformationsMatrix = nullptr;
}

Object3DGroup::~Object3DGroup()
{
	delete renderer;
}

void Object3DGroup::createGroups(Object3DBase* object, bool useMeshManager, Engine::AnimationProcessingTarget animationProcessingTarget, vector<Object3DGroup*>& object3DGroups)
{
	auto model = object->getModel();
	createGroups(object, model->getSubGroups(), model->hasAnimations(), useMeshManager, animationProcessingTarget, object3DGroups);
}

void Object3DGroup::createGroups(Object3DBase* object3D, map<string, Group*>* groups, bool animated, bool useMeshManager, Engine::AnimationProcessingTarget animationProcessingTarget, vector<Object3DGroup*>& object3DGroups)
{
	for (auto it: *groups) {
		Group* group = it.second;
		// skip on joints
		if (group->isJoint() == true) {
			continue;
		}
		// determine face count
		auto faceCount = group->getFaceCount();
		// skip on groups without faces
		if (faceCount > 0) {
			// create group render data
			auto object3DGroup = new Object3DGroup();
			// add it to group render data list
			object3DGroups.push_back(object3DGroup);
			// determine mesh id
			object3DGroup->id =
				group->getModel()->getId() +
				":" +
				group->getId() +
				":" +
				to_string(animationProcessingTarget);
			if (group->getSkinning() != nullptr || (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING)) {
				object3DGroup->id =
					object3DGroup->id +
					":" +
					to_string(counter++);
			}
			object3DGroup->object = object3D;
			object3DGroup->group = group;
			object3DGroup->animated = animated;
			object3DGroup->renderer = new Object3DGroupVBORenderer(object3DGroup);
			if (useMeshManager == true) {
				auto meshManager = Engine::getInstance()->getMeshManager();
				object3DGroup->mesh = meshManager->getMesh(object3DGroup->id);
				if (object3DGroup->mesh == nullptr) {
					object3DGroup->mesh = Object3DGroupMesh::createMesh(
						object3DGroup->renderer,
						animationProcessingTarget,
						group,
						object3D->transformationsMatrices[0],
						object3D->getSkinningGroupsMatrices(group)
					);
					meshManager->addMesh(object3DGroup->id, object3DGroup->mesh);
				}
			} else {
				object3DGroup->mesh = Object3DGroupMesh::createMesh(
					object3DGroup->renderer,
					animationProcessingTarget,
					group,
					object3D->transformationsMatrices[0],
					object3D->getSkinningGroupsMatrices(group)
				);
			}
			object3DGroup->textureMatricesByEntities.resize(group->getFacesEntities()->size());
			for (auto& textureMatrix: object3DGroup->textureMatricesByEntities) textureMatrix.identity();
			object3DGroup->materialDiffuseTextureIdsByEntities.resize(group->getFacesEntities()->size());
			object3DGroup->dynamicDiffuseTextureIdsByEntities.resize(group->getFacesEntities()->size());
			object3DGroup->materialSpecularTextureIdsByEntities.resize(group->getFacesEntities()->size());
			object3DGroup->materialDisplacementTextureIdsByEntities.resize(group->getFacesEntities()->size());
			object3DGroup->materialNormalTextureIdsByEntities.resize(group->getFacesEntities()->size());
			for (auto j = 0; j < group->getFacesEntities()->size(); j++) {
				object3DGroup->materialDiffuseTextureIdsByEntities[j] = GLTEXTUREID_NONE;
				object3DGroup->dynamicDiffuseTextureIdsByEntities[j] = GLTEXTUREID_NONE;
				object3DGroup->materialSpecularTextureIdsByEntities[j] = GLTEXTUREID_NONE;
				object3DGroup->materialDisplacementTextureIdsByEntities[j] = GLTEXTUREID_NONE;
				object3DGroup->materialNormalTextureIdsByEntities[j] = GLTEXTUREID_NONE;
			}
			// determine group transformations matrix
			auto groupTransformationsMatrixIt = object3D->transformationsMatrices[0]->find(group->getId());
			object3DGroup->groupTransformationsMatrix = groupTransformationsMatrixIt != object3D->transformationsMatrices[0]->end()?groupTransformationsMatrixIt->second:nullptr;
		}
		// but still check sub groups
		createGroups(object3D, group->getSubGroups(), animated, useMeshManager, animationProcessingTarget, object3DGroups);
	}
}

void Object3DGroup::computeTransformations(vector<Object3DGroup*>& object3DGroups)
{
	for (auto object3DGroup : object3DGroups) {
		object3DGroup->mesh->computeTransformations();
	}
}

void Object3DGroup::setupTextures(GLRenderer* renderer, Object3DGroup* object3DGroup, int32_t facesEntityIdx)
{
	auto facesEntities = object3DGroup->group->getFacesEntities();
	auto material = (*facesEntities)[facesEntityIdx].getMaterial();
	// get material or use default
	if (material == nullptr)
		material = Material::getDefaultMaterial();

	// load diffuse texture
	if (object3DGroup->materialDiffuseTextureIdsByEntities[facesEntityIdx] == GLTEXTUREID_NONE) {
		if (material->getDiffuseTexture() != nullptr) {
			object3DGroup->materialDiffuseTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(material->getDiffuseTexture());
		} else {
			object3DGroup->materialDiffuseTextureIdsByEntities[facesEntityIdx] = GLTEXTUREID_NOTUSED;
		}
	}
	// load specular texture
	if (renderer->isSpecularMappingAvailable() == true && object3DGroup->materialSpecularTextureIdsByEntities[facesEntityIdx] == GLTEXTUREID_NONE) {
		if (material->getSpecularTexture() != nullptr) {
			object3DGroup->materialSpecularTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(material->getSpecularTexture());
		} else {
			object3DGroup->materialSpecularTextureIdsByEntities[facesEntityIdx] = GLTEXTUREID_NOTUSED;
		}
	}
	// load displacement texture
	if (renderer->isDisplacementMappingAvailable() == true && object3DGroup->materialDisplacementTextureIdsByEntities[facesEntityIdx] == GLTEXTUREID_NONE) {
		if (material->getDisplacementTexture() != nullptr) {
			object3DGroup->materialDisplacementTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(material->getDisplacementTexture());
		} else {
			object3DGroup->materialDisplacementTextureIdsByEntities[facesEntityIdx] = GLTEXTUREID_NOTUSED;
		}
	}
	// load normal texture
	if (renderer->isNormalMappingAvailable() == true && object3DGroup->materialNormalTextureIdsByEntities[facesEntityIdx] == GLTEXTUREID_NONE) {
		if (material->getNormalTexture() != nullptr) {
			object3DGroup->materialNormalTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(material->getNormalTexture());
		} else {
			object3DGroup->materialNormalTextureIdsByEntities[facesEntityIdx] = GLTEXTUREID_NOTUSED;
		}
	}
}

void Object3DGroup::dispose()
{
	auto engine = Engine::getInstance();
	auto textureManager = engine->getTextureManager();
	auto facesEntities = group->getFacesEntities();
	// dispose textures
	for (auto j = 0; j < facesEntities->size(); j++) {
		// get entity's material
		auto material = (*facesEntities)[j].getMaterial();
		//	skip if no material was set up
		if (material == nullptr)
			continue;
		// diffuse texture
		auto glDiffuseTextureId = materialDiffuseTextureIdsByEntities[j];
		if (glDiffuseTextureId != Object3DGroup::GLTEXTUREID_NONE && glDiffuseTextureId != Object3DGroup::GLTEXTUREID_NOTUSED) {
			// remove texture from texture manager
			if (material->getDiffuseTexture() != nullptr)
				textureManager->removeTexture(material->getDiffuseTexture()->getId());
			// mark as removed
			materialDiffuseTextureIdsByEntities[j] = Object3DGroup::GLTEXTUREID_NONE;
		}
		// specular texture
		auto glSpecularTextureId = materialSpecularTextureIdsByEntities[j];
		if (glSpecularTextureId != Object3DGroup::GLTEXTUREID_NONE && glSpecularTextureId != Object3DGroup::GLTEXTUREID_NOTUSED) {
			// remove texture from texture manager
			if (material->getSpecularTexture() != nullptr)
				textureManager->removeTexture(material->getSpecularTexture()->getId());
			// mark as removed
			materialSpecularTextureIdsByEntities[j] = Object3DGroup::GLTEXTUREID_NONE;
		}
		// displacement texture
		auto glDisplacementTextureId = materialDisplacementTextureIdsByEntities[j];
		if (glDisplacementTextureId != Object3DGroup::GLTEXTUREID_NONE && glDisplacementTextureId != Object3DGroup::GLTEXTUREID_NOTUSED) {
			// remove texture from texture manager
			if (material->getDisplacementTexture() != nullptr)
				textureManager->removeTexture(material->getDisplacementTexture()->getId());
			// mark as removed
			materialDisplacementTextureIdsByEntities[j] = Object3DGroup::GLTEXTUREID_NONE;
		}
		// normal texture
		auto glNormalTextureId = materialNormalTextureIdsByEntities[j];
		if (glNormalTextureId != Object3DGroup::GLTEXTUREID_NONE && glNormalTextureId != Object3DGroup::GLTEXTUREID_NOTUSED) {
			// remove texture from texture manager
			if (material->getNormalTexture() != nullptr)
				textureManager->removeTexture(material->getNormalTexture()->getId());
			// mark as removed
			materialNormalTextureIdsByEntities[j] = Object3DGroup::GLTEXTUREID_NONE;
		}
	}
}
