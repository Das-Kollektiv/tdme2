#include <tdme/engine/subsystems/rendering/ObjectBase.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/engine/subsystems/manager/MeshManager.h>
#include <tdme/engine/subsystems/rendering/AnimationState.h>
#include <tdme/engine/subsystems/rendering/ObjectAnimation.h>
#include <tdme/engine/subsystems/rendering/ObjectBase_TransformedFacesIterator.h>
#include <tdme/engine/subsystems/rendering/ObjectNode.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeRenderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::make_unique;
using std::map;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::model::Animation;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Joint;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::Skinning;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Triangle;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::rendering::AnimationState;
using tdme::engine::subsystems::rendering::ObjectAnimation;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectBase_TransformedFacesIterator;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::engine::subsystems::rendering::ObjectNodeRenderer;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Console;

ObjectBase::ObjectBase(Model* model, bool useManagers, Engine::AnimationProcessingTarget animationProcessingTarget, int instances)
{
	this->model = model;
	this->animationProcessingTarget = animationProcessingTarget;
	this->usesManagers = useManagers;
	this->instances = instances;
	this->enabledInstances = instances;
	this->currentInstance = 0;
	instanceAnimations.resize(instances);
	instanceEnabled.resize(instances);
	instanceTransform.resize(instances);
	for (auto i = 0; i < instances; i++) {
		instanceEnabled[i] = true;
		instanceAnimations[i] = new ObjectAnimation(model, animationProcessingTarget);
	}
	transformedFacesIterator = nullptr;
	// object nodes
	ObjectNode::createNodes(this, useManagers, animationProcessingTarget, objectNodes);
	// do initial transform if doing CPU no rendering for deriving bounding boxes and such
	if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) ObjectNode::computeAnimation(0, objectNodes);
}

ObjectBase::~ObjectBase() {
	for (auto i = 0; i < instances; i++) {
		delete instanceAnimations[i];
	}
	for (auto i = 0; i < objectNodes.size(); i++) {
		delete objectNodes[i];
	}
}

int ObjectBase::getNodeCount() const {
	return objectNodes.size();
}

void ObjectBase::getTriangles(vector<Triangle>& triangles, int nodeIdx)
{
	if (nodeIdx == -1) {
		for (auto objectNode : objectNodes) {
			auto nodeVerticesTransformed = &objectNode->mesh->transformedVertices;
			for (const auto& facesEntity: objectNode->node->getFacesEntities())
			for (const auto& face: facesEntity.getFaces()) {
				const auto& faceVertexIndices = face.getVertexIndices();
				triangles.emplace_back(
					(*nodeVerticesTransformed)[faceVertexIndices[0]],
					(*nodeVerticesTransformed)[faceVertexIndices[1]],
					(*nodeVerticesTransformed)[faceVertexIndices[2]]
				);
			}
		}
	} else {
		auto objectNode = objectNodes[nodeIdx];
		auto nodeVerticesTransformed = &objectNode->mesh->transformedVertices;
		for (const auto& facesEntity: objectNode->node->getFacesEntities())
		for (const auto& face: facesEntity.getFaces()) {
			const auto& faceVertexIndices = face.getVertexIndices();
			triangles.emplace_back(
				(*nodeVerticesTransformed)[faceVertexIndices[0]],
				(*nodeVerticesTransformed)[faceVertexIndices[1]],
				(*nodeVerticesTransformed)[faceVertexIndices[2]]
			);
		}
	}
}

ObjectBase_TransformedFacesIterator* ObjectBase::getTransformedFacesIterator()
{
	if (transformedFacesIterator == nullptr) {
		transformedFacesIterator = make_unique<ObjectBase_TransformedFacesIterator>(this);
	}
	return transformedFacesIterator.get();
}

ObjectNodeMesh* ObjectBase::getMesh(const string& nodeId)
{
	// TODO: maybe rather use a hash map than an array to have a faster access
	for (auto objectNode :objectNodes) {
		if (objectNode->node->getId() == nodeId) {
			return objectNode->mesh;
		}
	}
	return nullptr;
}

void ObjectBase::initialize()
{
	auto meshManager = Engine::getInstance()->getMeshManager();
	//
	// init mesh
	for (auto i = 0; i < objectNodes.size(); i++) {
		auto objectNode = objectNodes[i];
		// initiate mesh if not yet done, happens usually after disposing from engine and readding to engine
		if (objectNode->mesh == nullptr) {
			vector<unordered_map<string, Matrix4x4*>*> instancesTransformMatrices;
			vector<unordered_map<string, Matrix4x4*>*> instancesSkinningNodesMatrices;
			for (auto animation: objectNode->object->instanceAnimations) {
				instancesTransformMatrices.push_back(&animation->transformMatrices[0]);
				instancesSkinningNodesMatrices.push_back(animation->getSkinningNodesTransformMatrices(objectNode->node));
			}
			if (usesManagers == true) {
				objectNode->mesh = meshManager->getMesh(objectNode->id);
				if (objectNode->mesh == nullptr) {
					objectNode->mesh = new ObjectNodeMesh(
						objectNode->rendererBackend.get(),
						animationProcessingTarget,
						objectNode->node,
						instancesTransformMatrices,
						instancesSkinningNodesMatrices,
						instances
					);
				}
			} else {
				objectNode->mesh = new ObjectNodeMesh(
					objectNode->rendererBackend.get(),
					animationProcessingTarget,
					objectNode->node,
					instancesTransformMatrices,
					instancesSkinningNodesMatrices,
					instances
				);
			}
		}
	}
}

void ObjectBase::dispose()
{
	auto meshManager = Engine::getInstance()->getMeshManager();
	// dispose mesh
	for (auto i = 0; i < objectNodes.size(); i++) {
		auto objectNode = objectNodes[i];
		// dispose renderer
		objectNode->rendererBackend->dispose();
		// dispose object node
		objectNode->dispose();
		// dispose mesh
		if (usesManagers == true) {
			meshManager->removeMesh(objectNode->id);
		} else {
			delete objectNode->mesh;
		}
		objectNode->mesh = nullptr;
	}
	//
}
