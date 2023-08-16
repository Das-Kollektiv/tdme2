#include <tdme/engine/subsystems/rendering/ObjectNode.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
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
#include <tdme/math/Matrix3x3.h>
#include <tdme/math/Matrix4x4.h>

using std::make_unique;
using std::map;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::vector;

using tdme::engine::Texture;
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
using tdme::math::Matrix3x3;
using tdme::math::Matrix4x4;

int64_t ObjectNode::counter = 0;

ObjectNode::ObjectNode()
{
}

ObjectNode::~ObjectNode()
{
}

void ObjectNode::updateNodeTransformationsMatrix() {
	nodeTransformMatrix = nullptr;
	auto overriddenTransformationsMatricesIt = object->instanceAnimations[0]->overriddenTransformMatrices.find(node->getId());
	if (overriddenTransformationsMatricesIt != object->instanceAnimations[0]->overriddenTransformMatrices.end()) {
		nodeTransformMatrix = overriddenTransformationsMatricesIt->second;
	} else {
		auto transformationsMatricesIt = object->instanceAnimations[0]->transformMatrices[0].find(node->getId());
		if (transformationsMatricesIt != object->instanceAnimations[0]->transformMatrices[0].end()) {
			nodeTransformMatrix = transformationsMatricesIt->second;
		}
	}
}

void ObjectNode::createNodes(ObjectBase* object, bool useManagers, Engine::AnimationProcessingTarget animationProcessingTarget, vector<ObjectNode*>& objectNodes)
{
	auto model = object->getModel();
	createNodes(object, model->getSubNodes(), model->hasAnimations(), useManagers, animationProcessingTarget, objectNodes);
}

void ObjectNode::createNodes(ObjectBase* object, const map<string, Node*>& nodes, bool animated, bool useManagers, Engine::AnimationProcessingTarget animationProcessingTarget, vector<ObjectNode*>& objectNodes)
{
	for (const auto& [nodeId, node]: nodes) {
		// skip on joints
		if (node->isJoint() == true) {
			continue;
		}
		// determine face count
		auto faceCount = node->getFaceCount();
		// skip on nodes without faces
		if (faceCount > 0) {
			// create node render data
			auto objectNode = new ObjectNode();
			// add it to node render data list
			objectNodes.push_back(objectNode);
			// determine mesh id
			objectNode->id =
				node->getModel()->getId() +
				":" +
				node->getId() +
				":" +
				to_string(animationProcessingTarget) +
				":" +
				to_string(object->instances);
			if (node->getSkinning() != nullptr || (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING)) {
				objectNode->id =
					objectNode->id +
					":" +
					to_string(counter++);
			}
			objectNode->object = object;
			objectNode->node = node;
			objectNode->animated = animated;
			objectNode->renderer = make_unique<ObjectNodeRenderer>(objectNode);
			vector<unordered_map<string, Matrix4x4*>*> instancesTransformMatrices;
			vector<unordered_map<string, Matrix4x4*>*> instancesSkinningNodesMatrices;
			for (auto animation: object->instanceAnimations) {
				instancesTransformMatrices.push_back(&animation->transformMatrices[0]);
				instancesSkinningNodesMatrices.push_back(animation->getSkinningNodesTransformMatrices(objectNode->node));
			}
			if (useManagers == true) {
				auto meshManager = Engine::getInstance()->getMeshManager();
				objectNode->mesh = meshManager->getMesh(objectNode->id);
				if (objectNode->mesh == nullptr) {
					objectNode->mesh = new ObjectNodeMesh(
						objectNode->renderer.get(),
						animationProcessingTarget,
						node,
						instancesTransformMatrices,
						instancesSkinningNodesMatrices,
						object->instances
					);
					meshManager->addMesh(objectNode->id, objectNode->mesh);
				}
			} else {
				objectNode->mesh = new ObjectNodeMesh(
					objectNode->renderer.get(),
					animationProcessingTarget,
					node,
					instancesTransformMatrices,
					instancesSkinningNodesMatrices,
					object->instances
				);
			}
			objectNode->textureMatricesByEntities.resize(node->getFacesEntities().size());
			for (auto j = 0; j < node->getFacesEntities().size(); j++) {
				auto material = node->getFacesEntities()[j].getMaterial();
				if (material != nullptr) {
					objectNode->textureMatricesByEntities[j].set(material->getTextureMatrix());
				} else {
					objectNode->textureMatricesByEntities[j].identity();
				}
			}
			objectNode->specularMaterialDiffuseTextureIdsByEntities.resize(node->getFacesEntities().size());
			objectNode->specularMaterialDynamicDiffuseTextureIdsByEntities.resize(node->getFacesEntities().size());
			objectNode->specularMaterialSpecularTextureIdsByEntities.resize(node->getFacesEntities().size());
			objectNode->specularMaterialNormalTextureIdsByEntities.resize(node->getFacesEntities().size());
			objectNode->pbrMaterialBaseColorTextureIdsByEntities.resize(node->getFacesEntities().size());
			objectNode->pbrMaterialMetallicRoughnessTextureIdsByEntities.resize(node->getFacesEntities().size());
			objectNode->pbrMaterialNormalTextureIdsByEntities.resize(node->getFacesEntities().size());
			objectNode->pbrMaterialEmissiveTextureIdsByEntities.resize(node->getFacesEntities().size());
			for (auto j = 0; j < node->getFacesEntities().size(); j++) {
				objectNode->specularMaterialDiffuseTextureIdsByEntities[j] = TEXTUREID_NONE;
				objectNode->specularMaterialDynamicDiffuseTextureIdsByEntities[j] = TEXTUREID_NONE;
				objectNode->specularMaterialSpecularTextureIdsByEntities[j] = TEXTUREID_NONE;
				objectNode->specularMaterialNormalTextureIdsByEntities[j] = TEXTUREID_NONE;
				objectNode->pbrMaterialBaseColorTextureIdsByEntities[j] = TEXTUREID_NONE;
				objectNode->pbrMaterialMetallicRoughnessTextureIdsByEntities[j] = TEXTUREID_NONE;
				objectNode->pbrMaterialNormalTextureIdsByEntities[j] = TEXTUREID_NONE;
				objectNode->pbrMaterialEmissiveTextureIdsByEntities[j] = TEXTUREID_NONE;
			}
			// update node transformations matrix
			objectNode->updateNodeTransformationsMatrix();
		}
		// but still check sub nodes
		createNodes(object, node->getSubNodes(), animated, useManagers, animationProcessingTarget, objectNodes);
	}
}

void ObjectNode::computeAnimation(int contextIdx, vector<ObjectNode*>& objectNodes)
{
	for (auto objectNode : objectNodes) {
		objectNode->mesh->computeSkinning(contextIdx, objectNode->object);
	}
}

void ObjectNode::setupTextures(Renderer* renderer, int contextIdx, ObjectNode* objectNode, int32_t facesEntityIdx)
{
	const auto& facesEntities = objectNode->node->getFacesEntities();
	auto material = facesEntities[facesEntityIdx].getMaterial();
	// get material or use default
	if (material == nullptr) material = Material::getDefaultMaterial();
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties != nullptr) {
		// load specular diffuse texture
		if (objectNode->specularMaterialDiffuseTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (specularMaterialProperties->getDiffuseTexture() != nullptr) {
				objectNode->specularMaterialDiffuseTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(specularMaterialProperties->getDiffuseTexture(), contextIdx);
			} else {
				objectNode->specularMaterialDiffuseTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
		// load specular specular texture
		if (renderer->isSpecularMappingAvailable() == true && objectNode->specularMaterialSpecularTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (specularMaterialProperties->getSpecularTexture() != nullptr) {
				objectNode->specularMaterialSpecularTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(specularMaterialProperties->getSpecularTexture(), contextIdx);
			} else {
				objectNode->specularMaterialSpecularTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
		// load specular normal texture
		if (renderer->isNormalMappingAvailable() == true && objectNode->specularMaterialNormalTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (specularMaterialProperties->getNormalTexture() != nullptr) {
				objectNode->specularMaterialNormalTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(specularMaterialProperties->getNormalTexture(), contextIdx);
			} else {
				objectNode->specularMaterialNormalTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
	}
	// load PBR textures
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties != nullptr && renderer->isPBRAvailable() == true) {
		// load PBR base color texture
		if (objectNode->pbrMaterialBaseColorTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (pbrMaterialProperties->getBaseColorTexture() != nullptr) {
				objectNode->pbrMaterialBaseColorTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(pbrMaterialProperties->getBaseColorTexture(), contextIdx);
			} else {
				objectNode->pbrMaterialBaseColorTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
		// load PBR metallic roughness texture
		if (objectNode->pbrMaterialMetallicRoughnessTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (pbrMaterialProperties->getMetallicRoughnessTexture() != nullptr) {
				objectNode->pbrMaterialMetallicRoughnessTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(pbrMaterialProperties->getMetallicRoughnessTexture(), contextIdx);
			} else {
				objectNode->pbrMaterialMetallicRoughnessTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
		// load PBR normal texture
		if (objectNode->pbrMaterialNormalTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (pbrMaterialProperties->getNormalTexture() != nullptr) {
				objectNode->pbrMaterialNormalTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(pbrMaterialProperties->getNormalTexture(), contextIdx);
			} else {
				objectNode->pbrMaterialNormalTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
		// load PBR emissive texture
		if (objectNode->pbrMaterialEmissiveTextureIdsByEntities[facesEntityIdx] == TEXTUREID_NONE) {
			if (pbrMaterialProperties->getEmissiveTexture() != nullptr) {
				objectNode->pbrMaterialEmissiveTextureIdsByEntities[facesEntityIdx] = Engine::getInstance()->getTextureManager()->addTexture(pbrMaterialProperties->getEmissiveTexture(), contextIdx);
			} else {
				objectNode->pbrMaterialEmissiveTextureIdsByEntities[facesEntityIdx] = TEXTUREID_NOTUSED;
			}
		}
	}
}

void ObjectNode::dispose()
{
	auto engine = Engine::getInstance();
	auto textureManager = engine->getTextureManager();
	const auto& facesEntities = node->getFacesEntities();
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
			// PBR emissive texture
			auto pbrEmissiveTextureId = pbrMaterialEmissiveTextureIdsByEntities[j];
			if (pbrEmissiveTextureId != ObjectNode::TEXTUREID_NONE && pbrEmissiveTextureId != ObjectNode::TEXTUREID_NOTUSED) {
				// remove texture from texture manager
				if (pbrMaterialProperties->getEmissiveTexture() != nullptr)
					textureManager->removeTexture(pbrMaterialProperties->getEmissiveTexture()->getId());
				// mark as removed
				pbrMaterialEmissiveTextureIdsByEntities[j] = ObjectNode::TEXTUREID_NONE;
			}
		}
	}
}
