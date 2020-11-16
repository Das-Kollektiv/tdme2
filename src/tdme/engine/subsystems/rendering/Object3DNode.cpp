#include <tdme/engine/subsystems/rendering/Object3DNode.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/subsystems/manager/MeshManager.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/rendering/Object3DBase.h>
#include <tdme/engine/subsystems/rendering/Object3DNodeMesh.h>
#include <tdme/engine/subsystems/rendering/Object3DNodeRenderer.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
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
using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::Skinning;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::rendering::Object3DBase;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;
using tdme::engine::subsystems::rendering::Object3DGroupRenderer;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;

int64_t Object3DGroup::counter = 0;

Object3DGroup::Object3DGroup()
{
}

Object3DGroup::~Object3DGroup()
{
	delete renderer;
}

void Object3DGroup::createGroups(Object3DBase* object, bool useManagers, Engine::AnimationProcessingTarget animationProcessingTarget, vector<Object3DGroup*>& object3DGroups)
{
	auto model = object->getModel();
	createGroups(object, model->getSubGroups(), model->hasAnimations(), useManagers, animationProcessingTarget, object3DGroups);
}

void Object3DGroup::createGroups(Object3DBase* object3D, const map<string, Group*>& groups, bool animated, bool useManagers, Engine::AnimationProcessingTarget animationProcessingTarget, vector<Object3DGroup*>& object3DGroups)
{
	for (auto it: groups) {
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
				to_string(animationProcessingTarget) +
				":" +
				to_string(object3D->instances);
			if (group->getSkinning() != nullptr || (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING)) {
				object3DGroup->id =
					object3DGroup->id +
					":" +
					to_string(counter++);
			}
			object3DGroup->object = object3D;
			object3DGroup->group = group;
			object3DGroup->animated = animated;
			object3DGroup->renderer = new Object3DGroupRenderer(object3DGroup);
			vector<map<string, Matrix4x4*>*> instancesTransformationsMatrices;
			vector<map<string, Matrix4x4*>*> instancesSkinningGroupsMatrices;
			for (auto animation: object3D->instanceAnimations) {
				instancesTransformationsMatrices.push_back(&animation->transformationsMatrices[0]);
				instancesSkinningGroupsMatrices.push_back(animation->getSkinningGroupsMatrices(object3DGroup->group));
			}
			if (useManagers == true) {
				auto meshManager = Engine::getInstance()->getMeshManager();
				object3DGroup->mesh = meshManager->getMesh(object3DGroup->id);
				if (object3DGroup->mesh == nullptr) {
					object3DGroup->mesh = new Object3DGroupMesh(
						object3DGroup->renderer,
						animationProcessingTarget,
						group,
						instancesTransformationsMatrices,
						instancesSkinningGroupsMatrices,
						object3D->instances
					);
					meshManager->addMesh(object3DGroup->id, object3DGroup->mesh);
				}
			} else {
				object3DGroup->mesh = new Object3DGroupMesh(
					object3DGroup->renderer,
					animationProcessingTarget,
					group,
					instancesTransformationsMatrices,
					instancesSkinningGroupsMatrices,
					object3D->instances
				);
			}
			object3DGroup->textureMatricesByEntities.resize(group->getFacesEntities().size());
			for (auto j = 0; j < group->getFacesEntities().size(); j++) {
				auto material = group->getFacesEntities()[j].getMaterial();
				if (material != nullptr) {
					object3DGroup->textureMatricesByEntities[j].set(material->getTextureMatrix());
				} else {
					object3DGroup->textureMatricesByEntities[j].identity();
				}
			}
			object3DGroup->specularMaterialDiffuseTextureIdsByEntities.resize(group->getFacesEntities().size());
			object3DGroup->specularMaterialDynamicDiffuseTextureIdsByEntities.resize(group->getFacesEntities().size());
			object3DGroup->specularMaterialSpecularTextureIdsByEntities.resize(group->getFacesEntities().size());
			object3DGroup->specularMaterialNormalTextureIdsByEntities.resize(group->getFacesEntities().size());
			object3DGroup->pbrMaterialBaseColorTextureIdsByEntities.resize(group->getFacesEntities().size());
			object3DGroup->pbrMaterialMetallicRoughnessTextureIdsByEntities.resize(group->getFacesEntities().size());
			object3DGroup->pbrMaterialNormalTextureIdsByEntities.resize(group->getFacesEntities().size());
			for (auto j = 0; j < group->getFacesEntities().size(); j++) {
				object3DGroup->specularMaterialDiffuseTextureIdsByEntities[j] = TEXTUREID_NONE;
				object3DGroup->specularMaterialDynamicDiffuseTextureIdsByEntities[j] = TEXTUREID_NONE;
				object3DGroup->specularMaterialSpecularTextureIdsByEntities[j] = TEXTUREID_NONE;
				object3DGroup->specularMaterialNormalTextureIdsByEntities[j] = TEXTUREID_NONE;
				object3DGroup->pbrMaterialBaseColorTextureIdsByEntities[j] = TEXTUREID_NONE;
				object3DGroup->pbrMaterialMetallicRoughnessTextureIdsByEntities[j] = TEXTUREID_NONE;
				object3DGroup->pbrMaterialNormalTextureIdsByEntities[j] = TEXTUREID_NONE;
			}
			// determine group transformations matrix
			object3DGroup->groupTransformationsMatrix = object3D->instanceAnimations[0]->transformationsMatrices[0].find(group->getId())->second;
		}
		// but still check sub groups
		createGroups(object3D, group->getSubGroups(), animated, useManagers, animationProcessingTarget, object3DGroups);
	}
}

void Object3DGroup::computeTransformations(void* context, vector<Object3DGroup*>& object3DGroups)
{
	for (auto object3DGroup : object3DGroups) {
		object3DGroup->mesh->computeTransformations(context, object3DGroup->object);
	}
}

void Object3DGroup::setupTextures(Renderer* renderer, void* context, Object3DGroup* object3DGroup, int32_t facesEntityIdx)
{
	auto& facesEntities = object3DGroup->group->getFacesEntities();
	auto material = facesEntities[facesEntityIdx].getMaterial();
	// get material or use default
	if (material == nullptr) material = Material::getDefaultMaterial();
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties != nullptr) {
		// load specular diffuse texture
		if (object3DGroup->specularMaterialDiffuseTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (specularMaterialProperties->getDiffuseTexture() != nullptr) {
				object3DGroup->specularMaterialDiffuseTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(specularMaterialProperties->getDiffuseTexture(), context);
			} else {
				object3DGroup->specularMaterialDiffuseTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
		// load specular specular texture
		if (renderer->isSpecularMappingAvailable() == true && object3DGroup->specularMaterialSpecularTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (specularMaterialProperties->getSpecularTexture() != nullptr) {
				object3DGroup->specularMaterialSpecularTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(specularMaterialProperties->getSpecularTexture(), context);
			} else {
				object3DGroup->specularMaterialSpecularTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
		// load specular normal texture
		if (renderer->isNormalMappingAvailable() == true && object3DGroup->specularMaterialNormalTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (specularMaterialProperties->getNormalTexture() != nullptr) {
				object3DGroup->specularMaterialNormalTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(specularMaterialProperties->getNormalTexture(), context);
			} else {
				object3DGroup->specularMaterialNormalTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
	}
	// load PBR textures
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties != nullptr && renderer->isPBRAvailable() == true) {
		// load PBR base color texture
		if (object3DGroup->pbrMaterialBaseColorTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (pbrMaterialProperties->getBaseColorTexture() != nullptr) {
				object3DGroup->pbrMaterialBaseColorTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(pbrMaterialProperties->getBaseColorTexture(), context);
			} else {
				object3DGroup->pbrMaterialBaseColorTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
		// load PBR metallic roughness texture
		if (object3DGroup->pbrMaterialMetallicRoughnessTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (pbrMaterialProperties->getMetallicRoughnessTexture() != nullptr) {
				object3DGroup->pbrMaterialMetallicRoughnessTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(pbrMaterialProperties->getMetallicRoughnessTexture(), context);
			} else {
				object3DGroup->pbrMaterialMetallicRoughnessTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
		// load PBR normal texture
		if (object3DGroup->pbrMaterialNormalTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (pbrMaterialProperties->getNormalTexture() != nullptr) {
				object3DGroup->pbrMaterialNormalTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(pbrMaterialProperties->getNormalTexture(), context);
			} else {
				object3DGroup->pbrMaterialNormalTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
	}
}

void Object3DGroup::dispose()
{
	auto engine = Engine::getInstance();
	auto textureManager = engine->getTextureManager();
	auto& facesEntities = group->getFacesEntities();
	// dispose textures
	for (auto j = 0; j < facesEntities.size(); j++) {
		// get entity's material
		auto material = facesEntities[j].getMaterial();
		//	skip if no material was set up
		auto specularMaterialProperties = material != nullptr?material->getSpecularMaterialProperties():nullptr;
		if (specularMaterialProperties != nullptr) {
			// specular diffuse texture
			auto specularDiffuseTextureId = specularMaterialDiffuseTextureIdsByEntities[j];
			if (specularDiffuseTextureId != Object3DGroup::TEXTUREID_NONE && specularDiffuseTextureId != Object3DGroup::TEXTUREID_NOTUSED) {
				// remove texture from texture manager
				if (specularMaterialProperties->getDiffuseTexture() != nullptr)
					textureManager->removeTexture(specularMaterialProperties->getDiffuseTexture()->getId());
				// mark as removed
				specularMaterialDiffuseTextureIdsByEntities[j] = Object3DGroup::TEXTUREID_NONE;
			}
			// specular specular texture
			auto specularSpecularTextureId = specularMaterialSpecularTextureIdsByEntities[j];
			if (specularSpecularTextureId != Object3DGroup::TEXTUREID_NONE && specularSpecularTextureId != Object3DGroup::TEXTUREID_NOTUSED) {
				// remove texture from texture manager
				if (specularMaterialProperties->getSpecularTexture() != nullptr)
					textureManager->removeTexture(specularMaterialProperties->getSpecularTexture()->getId());
				// mark as removed
				specularMaterialSpecularTextureIdsByEntities[j] = Object3DGroup::TEXTUREID_NONE;
			}
			// specular normal texture
			auto specularNormalTextureId = specularMaterialNormalTextureIdsByEntities[j];
			if (specularNormalTextureId != Object3DGroup::TEXTUREID_NONE && specularNormalTextureId != Object3DGroup::TEXTUREID_NOTUSED) {
				// remove texture from texture manager
				if (specularMaterialProperties->getNormalTexture() != nullptr)
					textureManager->removeTexture(specularMaterialProperties->getNormalTexture()->getId());
				// mark as removed
				specularMaterialNormalTextureIdsByEntities[j] = Object3DGroup::TEXTUREID_NONE;
			}
		}
		// PBR textures
		auto pbrMaterialProperties = material != nullptr?material->getPBRMaterialProperties():nullptr;
		if (pbrMaterialProperties != nullptr) {
			// PBR base color texture
			auto pbrBaseColorTextureId = pbrMaterialBaseColorTextureIdsByEntities[j];
			if (pbrBaseColorTextureId != Object3DGroup::TEXTUREID_NONE && pbrBaseColorTextureId != Object3DGroup::TEXTUREID_NOTUSED) {
				// remove texture from texture manager
				if (pbrMaterialProperties->getBaseColorTexture() != nullptr)
					textureManager->removeTexture(pbrMaterialProperties->getBaseColorTexture()->getId());
				// mark as removed
				pbrMaterialBaseColorTextureIdsByEntities[j] = Object3DGroup::TEXTUREID_NONE;
			}
			auto pbrMetallicRoughnessTextureId = pbrMaterialMetallicRoughnessTextureIdsByEntities[j];
			if (pbrMetallicRoughnessTextureId != Object3DGroup::TEXTUREID_NONE && pbrMetallicRoughnessTextureId != Object3DGroup::TEXTUREID_NOTUSED) {
				// remove texture from texture manager
				if (pbrMaterialProperties->getMetallicRoughnessTexture() != nullptr)
					textureManager->removeTexture(pbrMaterialProperties->getMetallicRoughnessTexture()->getId());
				// mark as removed
				pbrMaterialMetallicRoughnessTextureIdsByEntities[j] = Object3DGroup::TEXTUREID_NONE;
			}
			// PBR normal texture
			auto pbrNormalTextureId = pbrMaterialNormalTextureIdsByEntities[j];
			if (pbrNormalTextureId != Object3DGroup::TEXTUREID_NONE && pbrNormalTextureId != Object3DGroup::TEXTUREID_NOTUSED) {
				// remove texture from texture manager
				if (pbrMaterialProperties->getNormalTexture() != nullptr)
					textureManager->removeTexture(pbrMaterialProperties->getNormalTexture()->getId());
				// mark as removed
				pbrMaterialNormalTextureIdsByEntities[j] = Object3DGroup::TEXTUREID_NONE;
			}
		}
	}
}
