#include <tdme/engine/subsystems/rendering/ObjectNode.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/subsystems/manager/MeshManager.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/ObjectBase.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeRenderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>

using std::map;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Joint;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::Skinning;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::engine::subsystems::rendering::ObjectNodeRenderer;
using tdme::engine::Engine;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;

int64_t ObjectNode::counter = 0;

ObjectNode::ObjectNode()
{
}

ObjectNode::~ObjectNode()
{
	delete renderer;
}

void ObjectNode::createNodes(ObjectBase* object, bool useManagers, Engine::AnimationProcessingTarget animationProcessingTarget, vector<ObjectNode*>& object3DNodes)
{
	auto model = object->getModel();
	createNodes(object, model->getSubNodes(), model->hasAnimations(), useManagers, animationProcessingTarget, object3DNodes);
}

void ObjectNode::createNodes(ObjectBase* object3D, const map<string, Node*>& nodes, bool animated, bool useManagers, Engine::AnimationProcessingTarget animationProcessingTarget, vector<ObjectNode*>& object3DNodes)
{
	for (auto it: nodes) {
		Node* node = it.second;
		// skip on joints
		if (node->isJoint() == true) {
			continue;
		}
		// determine face count
		auto faceCount = node->getFaceCount();
		// skip on nodes without faces
		if (faceCount > 0) {
			// create node render data
			auto object3DNode = new ObjectNode();
			// add it to node render data list
			object3DNodes.push_back(object3DNode);
			// determine mesh id
			object3DNode->id =
				node->getModel()->getId() +
				":" +
				node->getId() +
				":" +
				to_string(animationProcessingTarget) +
				":" +
				to_string(object3D->instances);
			if (node->getSkinning() != nullptr || (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING)) {
				object3DNode->id =
					object3DNode->id +
					":" +
					to_string(counter++);
			}
			object3DNode->object = object3D;
			object3DNode->node = node;
			object3DNode->animated = animated;
			object3DNode->renderer = new ObjectNodeRenderer(object3DNode);
			vector<map<string, Matrix4x4*>*> instancesTransformationsMatrices;
			vector<map<string, Matrix4x4*>*> instancesSkinningNodesMatrices;
			for (auto animation: object3D->instanceAnimations) {
				instancesTransformationsMatrices.push_back(&animation->transformationsMatrices[0]);
				instancesSkinningNodesMatrices.push_back(animation->getSkinningNodesMatrices(object3DNode->node));
			}
			if (useManagers == true) {
				auto meshManager = Engine::getInstance()->getMeshManager();
				object3DNode->mesh = meshManager->getMesh(object3DNode->id);
				if (object3DNode->mesh == nullptr) {
					object3DNode->mesh = new ObjectNodeMesh(
						object3DNode->renderer,
						animationProcessingTarget,
						node,
						instancesTransformationsMatrices,
						instancesSkinningNodesMatrices,
						object3D->instances
					);
					meshManager->addMesh(object3DNode->id, object3DNode->mesh);
				}
			} else {
				object3DNode->mesh = new ObjectNodeMesh(
					object3DNode->renderer,
					animationProcessingTarget,
					node,
					instancesTransformationsMatrices,
					instancesSkinningNodesMatrices,
					object3D->instances
				);
			}
			object3DNode->textureMatricesByEntities.resize(node->getFacesEntities().size());
			for (auto j = 0; j < node->getFacesEntities().size(); j++) {
				auto material = node->getFacesEntities()[j].getMaterial();
				if (material != nullptr) {
					object3DNode->textureMatricesByEntities[j].set(material->getTextureMatrix());
				} else {
					object3DNode->textureMatricesByEntities[j].identity();
				}
			}
			object3DNode->specularMaterialDiffuseTextureIdsByEntities.resize(node->getFacesEntities().size());
			object3DNode->specularMaterialDynamicDiffuseTextureIdsByEntities.resize(node->getFacesEntities().size());
			object3DNode->specularMaterialSpecularTextureIdsByEntities.resize(node->getFacesEntities().size());
			object3DNode->specularMaterialNormalTextureIdsByEntities.resize(node->getFacesEntities().size());
			object3DNode->pbrMaterialBaseColorTextureIdsByEntities.resize(node->getFacesEntities().size());
			object3DNode->pbrMaterialMetallicRoughnessTextureIdsByEntities.resize(node->getFacesEntities().size());
			object3DNode->pbrMaterialNormalTextureIdsByEntities.resize(node->getFacesEntities().size());
			for (auto j = 0; j < node->getFacesEntities().size(); j++) {
				object3DNode->specularMaterialDiffuseTextureIdsByEntities[j] = TEXTUREID_NONE;
				object3DNode->specularMaterialDynamicDiffuseTextureIdsByEntities[j] = TEXTUREID_NONE;
				object3DNode->specularMaterialSpecularTextureIdsByEntities[j] = TEXTUREID_NONE;
				object3DNode->specularMaterialNormalTextureIdsByEntities[j] = TEXTUREID_NONE;
				object3DNode->pbrMaterialBaseColorTextureIdsByEntities[j] = TEXTUREID_NONE;
				object3DNode->pbrMaterialMetallicRoughnessTextureIdsByEntities[j] = TEXTUREID_NONE;
				object3DNode->pbrMaterialNormalTextureIdsByEntities[j] = TEXTUREID_NONE;
			}
			// determine node transformations matrix
			object3DNode->nodeTransformationsMatrix = object3D->instanceAnimations[0]->transformationsMatrices[0].find(node->getId())->second;
		}
		// but still check sub nodes
		createNodes(object3D, node->getSubNodes(), animated, useManagers, animationProcessingTarget, object3DNodes);
	}
}

void ObjectNode::computeTransformations(int contextIdx, vector<ObjectNode*>& object3DNodes)
{
	for (auto object3DNode : object3DNodes) {
		object3DNode->mesh->computeTransformations(contextIdx, object3DNode->object);
	}
}

void ObjectNode::setupTextures(Renderer* renderer, int contextIdx, ObjectNode* object3DNode, int32_t facesEntityIdx)
{
	auto& facesEntities = object3DNode->node->getFacesEntities();
	auto material = facesEntities[facesEntityIdx].getMaterial();
	// get material or use default
	if (material == nullptr) material = Material::getDefaultMaterial();
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties != nullptr) {
		// load specular diffuse texture
		if (object3DNode->specularMaterialDiffuseTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (specularMaterialProperties->getDiffuseTexture() != nullptr) {
				object3DNode->specularMaterialDiffuseTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(specularMaterialProperties->getDiffuseTexture(), contextIdx);
			} else {
				object3DNode->specularMaterialDiffuseTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
		// load specular specular texture
		if (renderer->isSpecularMappingAvailable() == true && object3DNode->specularMaterialSpecularTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (specularMaterialProperties->getSpecularTexture() != nullptr) {
				object3DNode->specularMaterialSpecularTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(specularMaterialProperties->getSpecularTexture(), contextIdx);
			} else {
				object3DNode->specularMaterialSpecularTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
		// load specular normal texture
		if (renderer->isNormalMappingAvailable() == true && object3DNode->specularMaterialNormalTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (specularMaterialProperties->getNormalTexture() != nullptr) {
				object3DNode->specularMaterialNormalTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(specularMaterialProperties->getNormalTexture(), contextIdx);
			} else {
				object3DNode->specularMaterialNormalTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
	}
	// load PBR textures
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties != nullptr && renderer->isPBRAvailable() == true) {
		// load PBR base color texture
		if (object3DNode->pbrMaterialBaseColorTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (pbrMaterialProperties->getBaseColorTexture() != nullptr) {
				object3DNode->pbrMaterialBaseColorTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(pbrMaterialProperties->getBaseColorTexture(), contextIdx);
			} else {
				object3DNode->pbrMaterialBaseColorTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
		// load PBR metallic roughness texture
		if (object3DNode->pbrMaterialMetallicRoughnessTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (pbrMaterialProperties->getMetallicRoughnessTexture() != nullptr) {
				object3DNode->pbrMaterialMetallicRoughnessTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(pbrMaterialProperties->getMetallicRoughnessTexture(), contextIdx);
			} else {
				object3DNode->pbrMaterialMetallicRoughnessTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
		// load PBR normal texture
		if (object3DNode->pbrMaterialNormalTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (pbrMaterialProperties->getNormalTexture() != nullptr) {
				object3DNode->pbrMaterialNormalTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(pbrMaterialProperties->getNormalTexture(), contextIdx);
			} else {
				object3DNode->pbrMaterialNormalTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
	}
}

void ObjectNode::dispose()
{
	auto engine = Engine::getInstance();
	auto textureManager = engine->getTextureManager();
	auto& facesEntities = node->getFacesEntities();
	// dispose textures
	for (auto j = 0; j < facesEntities.size(); j++) {
		// get entity's material
		auto material = facesEntities[j].getMaterial();
		//	skip if no material was set up
		auto specularMaterialProperties = material != nullptr?material->getSpecularMaterialProperties():nullptr;
		if (specularMaterialProperties != nullptr) {
			// specular diffuse texture
			auto specularDiffuseTextureId = specularMaterialDiffuseTextureIdsByEntities[j];
			if (specularDiffuseTextureId != ObjectNode::TEXTUREID_NONE && specularDiffuseTextureId != ObjectNode::TEXTUREID_NOTUSED) {
				// remove texture from texture manager
				if (specularMaterialProperties->getDiffuseTexture() != nullptr)
					textureManager->removeTexture(specularMaterialProperties->getDiffuseTexture()->getId());
				// mark as removed
				specularMaterialDiffuseTextureIdsByEntities[j] = ObjectNode::TEXTUREID_NONE;
			}
			// specular specular texture
			auto specularSpecularTextureId = specularMaterialSpecularTextureIdsByEntities[j];
			if (specularSpecularTextureId != ObjectNode::TEXTUREID_NONE && specularSpecularTextureId != ObjectNode::TEXTUREID_NOTUSED) {
				// remove texture from texture manager
				if (specularMaterialProperties->getSpecularTexture() != nullptr)
					textureManager->removeTexture(specularMaterialProperties->getSpecularTexture()->getId());
				// mark as removed
				specularMaterialSpecularTextureIdsByEntities[j] = ObjectNode::TEXTUREID_NONE;
			}
			// specular normal texture
			auto specularNormalTextureId = specularMaterialNormalTextureIdsByEntities[j];
			if (specularNormalTextureId != ObjectNode::TEXTUREID_NONE && specularNormalTextureId != ObjectNode::TEXTUREID_NOTUSED) {
				// remove texture from texture manager
				if (specularMaterialProperties->getNormalTexture() != nullptr)
					textureManager->removeTexture(specularMaterialProperties->getNormalTexture()->getId());
				// mark as removed
				specularMaterialNormalTextureIdsByEntities[j] = ObjectNode::TEXTUREID_NONE;
			}
		}
		// PBR textures
		auto pbrMaterialProperties = material != nullptr?material->getPBRMaterialProperties():nullptr;
		if (pbrMaterialProperties != nullptr) {
			// PBR base color texture
			auto pbrBaseColorTextureId = pbrMaterialBaseColorTextureIdsByEntities[j];
			if (pbrBaseColorTextureId != ObjectNode::TEXTUREID_NONE && pbrBaseColorTextureId != ObjectNode::TEXTUREID_NOTUSED) {
				// remove texture from texture manager
				if (pbrMaterialProperties->getBaseColorTexture() != nullptr)
					textureManager->removeTexture(pbrMaterialProperties->getBaseColorTexture()->getId());
				// mark as removed
				pbrMaterialBaseColorTextureIdsByEntities[j] = ObjectNode::TEXTUREID_NONE;
			}
			auto pbrMetallicRoughnessTextureId = pbrMaterialMetallicRoughnessTextureIdsByEntities[j];
			if (pbrMetallicRoughnessTextureId != ObjectNode::TEXTUREID_NONE && pbrMetallicRoughnessTextureId != ObjectNode::TEXTUREID_NOTUSED) {
				// remove texture from texture manager
				if (pbrMaterialProperties->getMetallicRoughnessTexture() != nullptr)
					textureManager->removeTexture(pbrMaterialProperties->getMetallicRoughnessTexture()->getId());
				// mark as removed
				pbrMaterialMetallicRoughnessTextureIdsByEntities[j] = ObjectNode::TEXTUREID_NONE;
			}
			// PBR normal texture
			auto pbrNormalTextureId = pbrMaterialNormalTextureIdsByEntities[j];
			if (pbrNormalTextureId != ObjectNode::TEXTUREID_NONE && pbrNormalTextureId != ObjectNode::TEXTUREID_NOTUSED) {
				// remove texture from texture manager
				if (pbrMaterialProperties->getNormalTexture() != nullptr)
					textureManager->removeTexture(pbrMaterialProperties->getNormalTexture()->getId());
				// mark as removed
				pbrMaterialNormalTextureIdsByEntities[j] = ObjectNode::TEXTUREID_NONE;
			}
		}
	}
}
