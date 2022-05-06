#include <tdme/engine/subsystems/rendering/ObjectBase.h>

#include <map>
#include <string>
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
	instanceTransformations.resize(instances);
	for (auto i = 0; i < instances; i++) {
		instanceEnabled[i] = true;
		instanceAnimations[i] = new ObjectAnimation(model, animationProcessingTarget);
	}
	transformedFacesIterator = nullptr;
	// object 3d nodes
	ObjectNode::createNodes(this, useManagers, animationProcessingTarget, object3dNodes);
	// do initial transformations if doing CPU no rendering for deriving bounding boxes and such
	if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) ObjectNode::computeTransformations(0, object3dNodes);
}

ObjectBase::~ObjectBase() {
	for (auto i = 0; i < instances; i++) {
		delete instanceAnimations[i];
	}
	for (auto i = 0; i < object3dNodes.size(); i++) {
		delete object3dNodes[i];
	}
	if (transformedFacesIterator != nullptr) delete transformedFacesIterator;
}

int ObjectBase::getNodeCount() const {
	return object3dNodes.size();
}

void ObjectBase::getTriangles(vector<Triangle>& triangles, int nodeIdx)
{
	if (nodeIdx == -1) {
		for (auto object3DNode : object3dNodes) {
			auto nodeVerticesTransformed = &object3DNode->mesh->transformedVertices;
			for (auto& facesEntity : object3DNode->node->getFacesEntities())
			for (auto& face : facesEntity.getFaces()) {
				auto faceVertexIndices = face.getVertexIndices();
				triangles.push_back(
					Triangle(
						(*nodeVerticesTransformed)[faceVertexIndices[0]],
						(*nodeVerticesTransformed)[faceVertexIndices[1]],
						(*nodeVerticesTransformed)[faceVertexIndices[2]]
					)
				);
			}
		}
	} else {
		auto object3DNode = object3dNodes[nodeIdx];
		auto nodeVerticesTransformed = &object3DNode->mesh->transformedVertices;
		for (auto& facesEntity : object3DNode->node->getFacesEntities())
		for (auto& face : facesEntity.getFaces()) {
			auto faceVertexIndices = face.getVertexIndices();
			triangles.push_back(
				Triangle(
					(*nodeVerticesTransformed)[faceVertexIndices[0]],
					(*nodeVerticesTransformed)[faceVertexIndices[1]],
					(*nodeVerticesTransformed)[faceVertexIndices[2]]
				)
			);
		}
	}
}

ObjectBase_TransformedFacesIterator* ObjectBase::getTransformedFacesIterator()
{
	if (transformedFacesIterator == nullptr) {
		transformedFacesIterator = new ObjectBase_TransformedFacesIterator(this);
	}
	return transformedFacesIterator;
}

ObjectNodeMesh* ObjectBase::getMesh(const string& nodeId)
{
	// TODO: maybe rather use a hash map than an array to have a faster access
	for (auto object3DNode : object3dNodes) {
		if (object3DNode->node->getId() == nodeId) {
			return object3DNode->mesh;
		}
	}
	return nullptr;
}

void ObjectBase::initialize()
{
	auto meshManager = Engine::getInstance()->getMeshManager();
	//
	// init mesh
	for (auto i = 0; i < object3dNodes.size(); i++) {
		auto object3DNode = object3dNodes[i];
		// initiate mesh if not yet done, happens usually after disposing from engine and readding to engine
		if (object3DNode->mesh == nullptr) {
			vector<map<string, Matrix4x4*>*> instancesTransformationsMatrices;
			vector<map<string, Matrix4x4*>*> instancesSkinningNodesMatrices;
			for (auto animation: object3DNode->object->instanceAnimations) {
				instancesTransformationsMatrices.push_back(&animation->transformationsMatrices[0]);
				instancesSkinningNodesMatrices.push_back(animation->getSkinningNodesMatrices(object3DNode->node));
			}
			if (usesManagers == true) {
				object3DNode->mesh = meshManager->getMesh(object3DNode->id);
				if (object3DNode->mesh == nullptr) {
					object3DNode->mesh = new ObjectNodeMesh(
						object3DNode->renderer,
						animationProcessingTarget,
						object3DNode->node,
						instancesTransformationsMatrices,
						instancesSkinningNodesMatrices,
						instances
					);
				}
			} else {
				object3DNode->mesh = new ObjectNodeMesh(
					object3DNode->renderer,
					animationProcessingTarget,
					object3DNode->node,
					instancesTransformationsMatrices,
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
	for (auto i = 0; i < object3dNodes.size(); i++) {
		auto object3DNode = object3dNodes[i];
		// dispose renderer
		object3DNode->renderer->dispose();
		// dispose object3d node
		object3DNode->dispose();
		// dispose mesh
		if (usesManagers == true) {
			meshManager->removeMesh(object3DNode->id);
		} else {
			delete object3DNode->mesh;
		}
		object3DNode->mesh = nullptr;
	}
	//
}
