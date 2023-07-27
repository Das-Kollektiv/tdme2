#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/subsystems/rendering/ObjectBase.h>
#include <tdme/engine/subsystems/rendering/ObjectNode.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::array;

using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Node;
using tdme::engine::model::Skinning;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectBase_TransformedFacesIterator;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Console;

/**
 * Transformed faces iterator
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::ObjectBase_TransformedFacesIterator
{
private:
	ObjectBase* objectBase { nullptr };
	Node* node { nullptr };
	array<Vector3, 3> vertices;
	Matrix4x4 matrix;
	int instances;
	int instanceIdx;
	int faceCount;
	int faceIdxTotal;
	int faceIdx;
	int objectNodeIdx;
	int facesEntityIdx;

private:

	/**
	 * Reset
	 */
	inline void reset() {
		instances = objectBase->instances;
		instanceIdx = 0;
		while (instanceIdx < instances && objectBase->instanceEnabled[instanceIdx] == false) instanceIdx++;
		//
		faceCount = 0;
		for (auto objectNode: objectBase->objectNodes) {
			for (auto& facesEntity: objectNode->node->getFacesEntities()) {
				faceCount += facesEntity.getFaces().size();
			}
		}
		faceIdx = 0;
		faceIdxTotal = 0;
		objectNodeIdx = 0;
		facesEntityIdx = 0;
		node = nullptr;
		matrix.identity();
		//
		if (instanceIdx < instances) {
			auto objectNode = objectBase->objectNodes[objectNodeIdx];
			node = objectNode->node;
			if (objectNode->mesh->skinning == true) {
				matrix.identity();
			} else {
				matrix.set(*objectNode->nodeTransformMatrix);
			}
			auto currentInstanceIdx = objectBase->getCurrentInstance();
			objectBase->setCurrentInstance(instanceIdx);
			matrix.multiply(objectBase->getTransformMatrix());
			objectBase->setCurrentInstance(currentInstanceIdx);
		}
	}

public:
	// forbid class copy
	CLASS_FORBID_COPY(ObjectBase_TransformedFacesIterator)

	/**
	 * Public constructor
	 */
	inline ObjectBase_TransformedFacesIterator(ObjectBase* objectBase) {
		this->objectBase = objectBase;
		reset();
	}

	/**
	 * Return iterator ready to iterate
	 */
	inline ObjectBase_TransformedFacesIterator* iterator() {
		reset();
		return this;
	}

	/**
	 * Has next
	 */
	inline bool hasNext() {
		return instanceIdx < instances && faceIdxTotal < faceCount;
	}

	/**
	 * Retrieve next triangle
	 * @return next 3 triangle vectors
	 */
	inline const array<Vector3, 3>& next() {
		auto objectNode = objectBase->objectNodes[objectNodeIdx];
		auto& facesEntities = objectNode->node->getFacesEntities();
		auto& facesEntity = facesEntities[facesEntityIdx];
		auto& faces = facesEntity.getFaces();
		auto& face = faces[faceIdx];
		// compute vertices
		auto& faceVertexIndices = face.getVertexIndices();
		// skinning
		if (objectNode->mesh->skinning == true) {
			//
			auto& nodeVertices = node->getVertices();
			auto& jointsWeights = node->getSkinning()->getVerticesJointsWeights();

			//
			const Vector3* vertex;
			float totalWeights;
			float weightNormalized;
			Matrix4x4 transformMatrix;

			//
			for (auto faceVertexIndex = 0; faceVertexIndex < 3; faceVertexIndex++) {
				// do vertices
				auto vertexIndex = faceVertexIndices[faceVertexIndex];
				vertex = &nodeVertices[vertexIndex];
				vertices[faceVertexIndex].set(0.0f, 0.0f, 0.0f);
				// compute every influence on vertex
				totalWeights = 0.0f;
				for (auto vertexJointWeightIdx = 0; vertexJointWeightIdx < jointsWeights[vertexIndex].size(); vertexJointWeightIdx++) {
					// skip on missing matrix
					auto skinningJointTransformMatrix = objectNode->mesh->skinningJointTransformMatrices[instanceIdx][vertexIndex][vertexJointWeightIdx];
					if (skinningJointTransformMatrix == nullptr) continue;
					// assemble vertex
					auto weight = objectNode->mesh->skinningJointWeight[vertexIndex][vertexJointWeightIdx];
					transformMatrix.set(*skinningJointTransformMatrix).multiply(objectBase->getTransformMatrix());
					vertices[faceVertexIndex].add(transformMatrix.multiply(*vertex).scale(weight));
					totalWeights += weight;
				}
				// scale to full weight
				if (Math::abs(totalWeights - 1.0f) > Math::EPSILON) {
					vertices[faceVertexIndex].scale(1.0f / totalWeights);
				}
			}
		} else {
			auto nodeVerticesTransformed = objectNode->mesh->vertices;
			vertices[0] = matrix.multiply((*nodeVerticesTransformed)[faceVertexIndices[0]]);
			vertices[1] = matrix.multiply((*nodeVerticesTransformed)[faceVertexIndices[1]]);
			vertices[2] = matrix.multiply((*nodeVerticesTransformed)[faceVertexIndices[2]]);
		}
		// set up current node
		node = objectNode->node;
		// increment to next face
		faceIdxTotal++;
		faceIdx++;
		// check if idxes over flow, if not yet finished
		if (faceIdxTotal < faceCount) {
			if (faceIdx == faces.size()) {
				faceIdx = 0;
				facesEntityIdx++;
				if (facesEntityIdx == facesEntities.size()) {
					facesEntityIdx = 0;
					objectNodeIdx++;
					objectNode = objectBase->objectNodes[objectNodeIdx];
					if (objectNode->mesh->skinning == true) {
						matrix.identity();
					} else {
						matrix.set(*objectNode->nodeTransformMatrix);
					}
					auto currentInstanceIdx = objectBase->getCurrentInstance();
					objectBase->setCurrentInstance(instanceIdx);
					matrix.multiply(objectBase->getTransformMatrix());
					objectBase->setCurrentInstance(currentInstanceIdx);
				}
			}
		} else
		if (instanceIdx < instances) {
			instanceIdx++;
			while (instanceIdx < instances && objectBase->instanceEnabled[instanceIdx] == false) instanceIdx++;
			//
			faceIdx = 0;
			faceIdxTotal = 0;
			objectNodeIdx = 0;
			facesEntityIdx = 0;
			node = nullptr;
			matrix.identity();
			if (instanceIdx < instances) {
				objectNode = objectBase->objectNodes[objectNodeIdx];
				if (objectNode->mesh->skinning == true) {
					matrix.identity();
				} else {
					matrix.set(*objectNode->nodeTransformMatrix);
				}
				auto currentInstanceIdx = objectBase->getCurrentInstance();
				objectBase->setCurrentInstance(instanceIdx);
				matrix.multiply(objectBase->getTransformMatrix());
				objectBase->setCurrentInstance(currentInstanceIdx);
			}
		}
		//
		return vertices;
	}

	/**
	 * @return current node
	 */
	inline Node* getNode() {
		return node;
	}

};
