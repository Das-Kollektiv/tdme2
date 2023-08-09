#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>

#include <map>
#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/ObjectBase.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeRenderer.h>
#include <tdme/engine/subsystems/skinning/SkinningShader.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/ShortBuffer.h>

using std::map;
using std::string;
using std::unordered_map;

using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Node;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::engine::subsystems::rendering::ObjectNodeRenderer;
using tdme::engine::subsystems::skinning::SkinningShader;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::FloatBuffer;
using tdme::utilities::ShortBuffer;

ObjectNodeMesh::ObjectNodeMesh(ObjectNodeRenderer* objectNodeRenderer, Engine::AnimationProcessingTarget animationProcessingTarget, Node* node, const vector<unordered_map<string, Matrix4x4*>*>& transformMatrices, const vector<unordered_map<string, Matrix4x4*>*>& skinningMatrices, int instances)
{
	//
	this->instances = instances;
	this->objectNodeRenderer = objectNodeRenderer;
	this->node = node;
	// node data
	const auto& nodeVertices = node->getVertices();
	const auto& nodeNormals = node->getNormals();
	const auto& nodeTextureCoordinates = node->getTextureCoordinates();
	const auto& nodeTangents = node->getTangents();
	const auto& nodeBitangents = node->getBitangents();
	// determine face count
	faceCount = node->getFaceCount();
	// animation processing target
	this->animationProcessingTarget = animationProcessingTarget;
	// transform for skinned meshes
	auto skinning = node->getSkinning();
	this->skinning = skinning != nullptr;
	this->skinningMatrices = skinningMatrices;
	if (skinning != nullptr) {
		jointsSkinningMatrices.resize(instances);
		for (auto i = 0; i < instances; i++) {
			for (const auto& joint: skinning->getJoints()) {
				jointsSkinningMatrices[i].push_back(skinningMatrices[i]->find(joint.getNodeId())->second);
			}
		}
	}
	// set up transformed vertices, normals and friends
	if (instances > 1 || (skinning != nullptr && animationProcessingTarget == Engine::AnimationProcessingTarget::CPU) ||
		animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
		// transformed mesh vertices
		transformedVertices.resize(nodeVertices.size() * instances);
		vertices = &transformedVertices;
		{
			auto idx = 0;
			for (auto i = 0; i < instances; i++)
			for (auto j = 0; j < nodeVertices.size(); j++) {
				transformedVertices[idx++].set(nodeVertices[j]);
			}
		}
		// transformed mesh normals
		transformedNormals.resize(nodeNormals.size() * instances);
		normals = &transformedNormals;
		{
			auto idx = 0;
			for (auto i = 0; i < instances; i++)
			for (auto j = 0; j < nodeNormals.size(); j++) {
				transformedNormals[idx++].set(nodeNormals[j]);
			}
		}
		if (instances > 1) {
			// transformed mesh texture coordinates
			transformedTextureCoordinates.resize(nodeTextureCoordinates.size() * instances);
			textureCoordinates = &transformedTextureCoordinates;
			{
				auto idx = 0;
				for (auto i = 0; i < instances; i++)
				for (auto j = 0; j < nodeTextureCoordinates.size(); j++) {
					transformedTextureCoordinates[idx++].set(nodeTextureCoordinates[j]);
				}
			}
		} else {
			textureCoordinates = &nodeTextureCoordinates;
		}
		// transformed mesh tangents
		if (nodeTangents.size() > 0) {
			transformedTangents.resize(nodeTangents.size() * instances);
			tangents = &transformedTangents;
			{
				auto idx = 0;
				for (auto i = 0; i < instances; i++)
				for (auto j = 0; j < nodeTangents.size(); j++) {
					transformedTangents[idx++].set(nodeTangents[j]);
				}
			}
		}
		// transformed mesh bitangents
		if (nodeBitangents.size() > 0) {
			transformedBitangents.resize(nodeBitangents.size() * instances);
			bitangents = &transformedBitangents;
			{
				auto idx = 0;
				for (auto i = 0; i < instances; i++)
				for (auto j = 0; j < nodeBitangents.size(); j++) {
					transformedBitangents[idx++].set(nodeBitangents[j]);
				}
			}
		}
	} else {
		// no transform on CPU, we can use model data
		vertices = &nodeVertices;
		normals = &nodeNormals;
		textureCoordinates = &nodeTextureCoordinates;
		if (nodeTangents.size() > 0) {
			tangents = &nodeTangents;
		}
		if (nodeBitangents.size() > 0) {
			bitangents = &nodeBitangents;
		}
	}

	// indices
	auto indicesCount = 0;
	for (const auto& facesEntity: node->getFacesEntities()) {
		indicesCount += 3 * facesEntity.getFaces().size();
	}
	indices.resize(instances * indicesCount);
	{
		auto j = 0;
		for (const auto& facesEntity: node->getFacesEntities()) {
			for (auto i = 0; i < instances; i++) {
				for (const auto& face: facesEntity.getFaces())
				for (auto vertexIndex: face.getVertexIndices()) {
					indices[j++] = nodeVertices.size() * i + vertexIndex;
				}
			}
		}
	}

	//
	recreatedBuffers = false;
	// node transform matrix
	if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU ||
		animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING ||
		animationProcessingTarget == Engine::AnimationProcessingTarget::GPU) {
		// node transform matrix
		nodeTransformMatrix = transformMatrices[0]->find(node->getId())->second;
	}
	// skinning
	if (skinning != nullptr) {
		skinningMaxVertexWeights = 0;
		skinningJointWeight.resize(nodeVertices.size());
		skinningJointTransformMatrices.resize(instances);
		for (auto i = 0; i < instances; i++) skinningJointTransformMatrices[i].resize(nodeVertices.size());
		// compute joint weight caches
		const auto& joints = skinning->getJoints();
		const auto& weights = skinning->getWeights();
		const auto& jointsWeights = skinning->getVerticesJointsWeights();
		for (auto vertexIndex = 0; vertexIndex < nodeVertices.size(); vertexIndex++) {
			auto vertexJointWeights = jointsWeights[vertexIndex].size();
			if (vertexJointWeights > skinningMaxVertexWeights) skinningMaxVertexWeights = vertexJointWeights;
			skinningJointWeight[vertexIndex].resize(vertexJointWeights);
			for (auto i = 0; i < instances; i++) skinningJointTransformMatrices[i][vertexIndex].resize(vertexJointWeights);
			{
				auto jointWeightIdx = 0;
				for (const auto& jointWeight : jointsWeights[vertexIndex]) {
					const auto& joint = joints[jointWeight.getJointIndex()];
					skinningJointWeight[vertexIndex][jointWeightIdx] = weights[jointWeight.getWeightIndex()];
					// next
					jointWeightIdx++;
				}
			}
			for (auto i = 0; i < instances; i++) {
				auto jointWeightIdx = 0;
				for (const auto& jointWeight : jointsWeights[vertexIndex]) {
					auto& joint = joints[jointWeight.getJointIndex()];
					auto skinningMatrixIt = skinningMatrices[i]->find(joint.getNodeId());
					skinningJointTransformMatrices[i][vertexIndex][jointWeightIdx] = skinningMatrixIt != skinningMatrices[i]->end()?skinningMatrixIt->second:nullptr;
					// next
					jointWeightIdx++;
				}
			}
		}
	}
	recreateBuffers();
}

void ObjectNodeMesh::computeSkinning(int contextIdx, ObjectBase* objectBase)
{
	// transform for skinned meshes
	auto skinning = node->getSkinning();
	if (skinning != nullptr) {
		// compute skinning on CPU if required
		if (animationProcessingTarget == Engine::AnimationProcessingTarget::GPU) {
			Engine::getSkinningShader()->computeSkinning(contextIdx, objectBase, this);
		} else
		if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU || animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
			const auto& nodeVertices = node->getVertices();
			const auto& nodeNormals = node->getNormals();
			const auto& nodeTangent = node->getTangents();
			const auto& nodeBitangent = node->getBitangents();
			const auto& jointsWeights = skinning->getVerticesJointsWeights();
			const Vector3* vertex;
			Vector3* transformedVertex;
			const Vector3* normal;
			Vector3* transformedNormal;
			const Vector3* tangent;
			Vector3* transformedTangent;
			const Vector3* bitangent;
			Vector3* transformedBitangent;
			float totalWeights;
			float weightNormalized;
			auto j = 0;
			Matrix4x4 transformMatrix;
			auto currentInstance = objectBase->getCurrentInstance();
			for (auto i = 0; i < instances; i++) {
				if (objectBase->instanceEnabled[i] == false) continue;
				objectBase->setCurrentInstance(i);
				for (auto vertexIndex = 0; vertexIndex < nodeVertices.size(); vertexIndex++) {
					// do vertices, normals, tangents and bitangents
					vertex = &nodeVertices[vertexIndex];
					transformedVertex = &transformedVertices[nodeVertices.size() * j + vertexIndex].set(0.0f, 0.0f, 0.0f);
					normal = &nodeNormals[vertexIndex];
					transformedNormal = &transformedNormals[nodeVertices.size() * j + vertexIndex].set(0.0f, 0.0f, 0.0f);
					tangent = tangents != nullptr?&nodeTangent[vertexIndex]:nullptr;
					transformedTangent = tangents != nullptr?&transformedTangents[nodeVertices.size() * j + vertexIndex].set(0.0f, 0.0f, 0.0f):nullptr;
					bitangent = bitangents != nullptr?&nodeBitangent[vertexIndex]:nullptr;
					transformedBitangent = bitangents != nullptr?&transformedBitangents[nodeVertices.size() * j + vertexIndex].set(0.0f, 0.0f, 0.0f):nullptr;
					// compute every influence on vertex and ...
					totalWeights = 0.0f;
					for (auto vertexJointWeightIdx = 0; vertexJointWeightIdx < jointsWeights[vertexIndex].size(); vertexJointWeightIdx++) {
						// skip on missing matrix
						auto skinningJointTransformMatrix = skinningJointTransformMatrices[i][vertexIndex][vertexJointWeightIdx];
						if (skinningJointTransformMatrix == nullptr) continue;
						//
						auto weight = skinningJointWeight[vertexIndex][vertexJointWeightIdx];
						//
						transformMatrix.set(*skinningJointTransformMatrix).multiply(objectBase->getTransformMatrix());
						// vertex
						transformedVertex->add(transformMatrix.multiply(*vertex).scale(weight));
						// normals
						transformedNormal->add(transformMatrix.multiplyNoTranslation(*normal).scale(weight));
						// tangent
						if (tangent != nullptr && transformedTangent != nullptr) {
							transformedTangent->add(transformMatrix.multiplyNoTranslation(*tangent).scale(weight));
						}
						// bitangent
						if (bitangent != nullptr && transformedBitangent != nullptr) {
							transformedBitangent->add(transformMatrix.multiplyNoTranslation(*bitangent).scale(weight));
						}
						//
						totalWeights += weight;
					}
					// scale to full weight
					if (Math::abs(totalWeights - 1.0f) > Math::EPSILON) {
						weightNormalized = 1.0f / totalWeights;
						// vertex
						transformedVertex->scale(weightNormalized);
						// normals
						transformedNormal->scale(weightNormalized);
						// tangent
						if (transformedTangent != nullptr) {
							transformedTangent->scale(weightNormalized);
						}
						// bitangent
						if (transformedBitangent != nullptr) {
							transformedBitangent->scale(weightNormalized);
						}
					}
					// normalize normal
					transformedNormal->normalize();
				}
				j++;
			}
			objectBase->setCurrentInstance(currentInstance);
			// recreate buffers
			recreateBuffers();
		}
	} else
	if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
		const auto& nodeVertices = node->getVertices();
		const auto& nodeNormals = node->getNormals();
		// transform for non skinned rendering
		//	vertices
		for (auto vertexIndex = 0; vertexIndex < nodeVertices.size(); vertexIndex++) {
			transformedVertices[vertexIndex].set(nodeTransformMatrix->multiply(nodeVertices[vertexIndex]));
		}
		//	normals
		for (auto normalIndex = 0; normalIndex < nodeNormals.size(); normalIndex++) {
			transformedNormals[normalIndex].set(nodeTransformMatrix->multiplyNoTranslation(nodeNormals[normalIndex]).normalize());
		}
		//	TODO: tangents, bitangents, but actually it is only in use for computing bounding volumes, so I am not in a hurry
		// recreate buffers
		recreateBuffers();
	}
}

void ObjectNodeMesh::recreateBuffers()
{
	recreatedBuffers = true;
}

bool ObjectNodeMesh::getRecreatedBuffers()
{
	if (recreatedBuffers == true) {
		recreatedBuffers = false;
		return true;
	} else {
		return false;
	}
}

void ObjectNodeMesh::setupVertexIndicesBuffer(Renderer *renderer, int contextIdx, int32_t vboId) {
	// upload
	if (renderer->isUsingShortIndices() == true) {
		if (instances * indices.size() > 65535) {
			Console::println(
				"ObjectNodeMesh::setupVertexIndicesBuffer(): " +
				node->getModel()->getName() + ":" +
				node->getName() + ":" +
				"more than 2^16-1 indices: " +
				to_string(indices.size())
			);
		}
		auto sbIndices = ObjectBuffer::getByteBuffer(contextIdx, instances * faceCount * 3 * sizeof(uint16_t))->asShortBuffer();
		// create face vertex indices, will never be changed in engine
		for (auto i = 0; i < instances; i++)
		for (auto index: indices) {
			sbIndices.put(index);
		}
		// done, upload
		renderer->uploadIndicesBufferObject(contextIdx, vboId, sbIndices.getPosition() * sizeof(uint16_t), &sbIndices);
	} else {
		auto ibIndices = ObjectBuffer::getByteBuffer(contextIdx, instances * faceCount * 3 * sizeof(uint32_t))->asIntBuffer();
		// create face vertex indices, will never be changed in engine
		for (auto i = 0; i < instances; i++)
		for (auto index: indices) {
			ibIndices.put(index);
		}
		// done, upload
		renderer->uploadIndicesBufferObject(contextIdx, vboId, ibIndices.getPosition() * sizeof(uint32_t), &ibIndices);
	}
}


void ObjectNodeMesh::setupTextureCoordinatesBuffer(Renderer* renderer, int contextIdx, int32_t vboId)
{
	if (textureCoordinates->size() == 0) return;
	// create texture coordinates buffer, will never be changed in engine
	auto fbTextureCoordinates = ObjectBuffer::getByteBuffer(contextIdx, textureCoordinates->size() * 2 * sizeof(float))->asFloatBuffer();
	// construct texture coordinates byte buffer as this will not change usually
	for (const auto& textureCoordinate: *textureCoordinates) {
		fbTextureCoordinates.put(textureCoordinate.getArray());
	}
	// done, upload
	renderer->uploadBufferObject(contextIdx, vboId, fbTextureCoordinates.getPosition() * sizeof(float), &fbTextureCoordinates);
}

void ObjectNodeMesh::setupVerticesBuffer(Renderer* renderer, int contextIdx, int32_t vboId)
{
	auto fbVertices = ObjectBuffer::getByteBuffer(contextIdx, vertices->size() * 3 * sizeof(float))->asFloatBuffer();
	// create vertices buffers
	for (const auto& vertex: *vertices) {
		fbVertices.put(vertex.getArray());
	}
	// done, upload
	renderer->uploadBufferObject(contextIdx, vboId, fbVertices.getPosition() * sizeof(float), &fbVertices);
}

void ObjectNodeMesh::setupNormalsBuffer(Renderer* renderer, int contextIdx, int32_t vboId)
{
	auto fbNormals = ObjectBuffer::getByteBuffer(contextIdx, normals->size() * 3 * sizeof(float))->asFloatBuffer();
	// create normals buffers
	for (const auto& normal: *normals) {
		fbNormals.put(normal.getArray());
	}
	// done, upload
	renderer->uploadBufferObject(contextIdx, vboId, fbNormals.getPosition() * sizeof(float), &fbNormals);
}

void ObjectNodeMesh::setupTangentsBuffer(Renderer* renderer, int contextIdx, int32_t vboId)
{
	// check if we have tangents
	if (tangents == nullptr) return;
	auto fbTangents = ObjectBuffer::getByteBuffer(contextIdx, tangents->size() * 3 * sizeof(float))->asFloatBuffer();
	// create tangents buffers
	for (const auto& tangent: *tangents) {
		fbTangents.put(tangent.getArray());
	}
	// done, upload
	renderer->uploadBufferObject(contextIdx, vboId, fbTangents.getPosition() * sizeof(float), &fbTangents);
}

void ObjectNodeMesh::setupBitangentsBuffer(Renderer* renderer, int contextIdx, int32_t vboId)
{
	// check if we have bitangents
	if (bitangents == nullptr) return;
	auto fbBitangents = ObjectBuffer::getByteBuffer(contextIdx, bitangents->size() * 3 * sizeof(float))->asFloatBuffer();
	// create bitangents buffers
	for (const auto& bitangent: *bitangents) {
		fbBitangents.put(bitangent.getArray());
	}
	// done, upload
	renderer->uploadBufferObject(contextIdx, vboId, fbBitangents.getPosition() * sizeof(float), &fbBitangents);
}

void ObjectNodeMesh::setupOriginsBuffer(Renderer* renderer, int contextIdx, int32_t vboId) {
	// check if we have origins
	const auto& origins = node->getOrigins();
	if (origins.size() == 0) return;
	// create origins buffer, will never be changed in engine
	auto fbOrigins = ObjectBuffer::getByteBuffer(contextIdx, origins.size() * 3 * sizeof(float))->asFloatBuffer();
	// construct origins buffer
	for (const auto& origin: origins) {
		fbOrigins.put(origin.getArray());
	}
	// done, upload
	renderer->uploadBufferObject(contextIdx, vboId, fbOrigins.getPosition() * sizeof(float), &fbOrigins);
}

void ObjectNodeMesh::setupLodBuffer(Renderer* renderer, int contextIdx, int32_t vboId, int lodLevel) {
	// TODO: we only support faces entities 0 lod indices for terrain now
	const vector<int32_t>* indices { nullptr };
	switch (lodLevel) {
		case 1: indices = &node->getFacesEntities()[0].getLOD1Indices(); break;
		case 2: indices = &node->getFacesEntities()[0].getLOD2Indices(); break;
		case 3: indices = &node->getFacesEntities()[0].getLOD3Indices(); break;
		default:
			Console::println(
				"ObjectNodeMesh::setupLodBuffer(): " +
				node->getModel()->getName() + ":" +
				node->getName() + ":" +
				"no valid lod level: " + to_string(lodLevel)
			);
			return;
	}
	if (indices->empty() == true) {
		Console::println(
			"ObjectNodeMesh::setupLodBuffer(): " +
			node->getModel()->getName() + ":" +
			node->getName() + ":" +
			"no indices"
		);
		return;
	}
	if (renderer->isUsingShortIndices() == true) {
		if (instances * indices->size() > 65535) {
			Console::println(
				"ObjectNodeMesh::setupLodBuffer(): " +
				node->getModel()->getName() + ":" +
				node->getName() + ":" +
				"more than 2^16-1 indices: " +
				to_string(indices->size())
			);
		}
		// create indices buffer, will never be changed in engine
		auto sbIndices = ObjectBuffer::getByteBuffer(contextIdx, indices->size() * sizeof(uint16_t))->asShortBuffer();
		// construct indices buffer
		for (const auto index: *indices) {
			sbIndices.put(index);
		}
		renderer->uploadIndicesBufferObject(contextIdx, vboId, sbIndices.getPosition() * sizeof(uint16_t), &sbIndices);
	} else {
		// create indices buffer, will never be changed in engine
		auto ibIndices = ObjectBuffer::getByteBuffer(contextIdx, indices->size() * sizeof(uint32_t))->asIntBuffer();
		// construct indices buffer
		for (const auto index: *indices) {
			ibIndices.put(index);
		}
		renderer->uploadIndicesBufferObject(contextIdx, vboId, ibIndices.getPosition() * sizeof(uint32_t), &ibIndices);
	}
}
