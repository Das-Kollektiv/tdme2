#include <tdme/engine/subsystems/rendering/Object3DGroupMesh.h>

#include <map>
#include <string>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/utils/ShortBuffer.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupRenderer.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/skinning/SkinningShader.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>

using std::map;
using std::string;

using tdme::engine::subsystems::rendering::Object3DGroupMesh;
using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::utils::ShortBuffer;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::rendering::Object3DGroupRenderer;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::skinning::SkinningShader;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::Console;

Object3DGroupMesh::Object3DGroupMesh()
{
	vertices = nullptr;
	normals = nullptr;
	textureCoordinates = nullptr;
	tangents = nullptr;
	bitangents = nullptr;
	cSkinningMaxVertexWeights = -1;
	cGroupTransformationsMatrix = nullptr;
	skinning = false;
	skinningJoints = -1;
	object3DGroupRenderer = nullptr;
	skinningMatrices = nullptr;
}

Object3DGroupMesh* Object3DGroupMesh::createMesh(Object3DGroupRenderer* object3DGroupRenderer, Engine::AnimationProcessingTarget animationProcessingTarget, Group* group, map<string, Matrix4x4*>* transformationMatrices, map<string, Matrix4x4*>* skinningMatrices)
{
	auto mesh = new Object3DGroupMesh();
	//
	mesh->object3DGroupRenderer = object3DGroupRenderer;
	mesh->group = group;
	// group data
	auto groupVertices = group->getVertices();
	auto groupNormals = group->getNormals();
	auto groupTextureCoordinates = group->getTextureCoordinates();
	auto groupTangents = group->getTangents();
	auto groupBitangents = group->getBitangents();
	// determine face count
	mesh->faceCount = group->getFaceCount();
	// animation processing target
	mesh->animationProcessingTarget = animationProcessingTarget;
	// transformations for skinned meshes
	auto skinning = group->getSkinning();
	mesh->skinning = skinning != nullptr;
	mesh->skinningMatrices = skinningMatrices;
	// set up transformed vertices, normals and friends
	if ((skinning != nullptr && animationProcessingTarget == Engine::AnimationProcessingTarget::CPU) ||
		animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
		// transformed mesh vertices
		mesh->transformedVertices.resize(groupVertices->size());
		mesh->vertices = &mesh->transformedVertices;
		for (auto j = 0; j < mesh->vertices->size(); j++) {
			(*mesh->vertices)[j].set((*groupVertices)[j]);
		}
		// transformed mesh normals
		mesh->transformedNormals.resize(groupNormals->size());
		mesh->normals = &mesh->transformedNormals;
		for (auto j = 0; j < mesh->normals->size(); j++) {
			(*mesh->normals)[j].set((*groupNormals)[j]);
		}
		// transformed mesh tangents
		if (groupTangents->size() > 0) {
			mesh->transformedTangents.resize(groupTangents->size());
			mesh->tangents = &mesh->transformedTangents;
			for (auto j = 0; j < mesh->tangents->size(); j++) {
				(*mesh->tangents)[j].set((*groupTangents)[j]);
			}
		}
		// transformed mesh bitangents
		if (groupBitangents->size() > 0) {
			mesh->transformedBitangents.resize(groupBitangents->size());
			mesh->bitangents = &mesh->transformedBitangents;
			for (auto j = 0; j < mesh->bitangents->size(); j++) {
				(*mesh->bitangents)[j].set((*groupBitangents)[j]);
			}
		}
	} else {
		// no transformations on CPU, we can use model data
		mesh->vertices = groupVertices;
		mesh->normals = groupNormals;
		if (groupTangents->size() > 0) {
			mesh->tangents = groupTangents;
		}
		if (groupBitangents->size() > 0) {
			mesh->bitangents = groupBitangents;
		}
	}
	// indices
	auto indicesCount = 0;
	for (auto& facesEntity : *group->getFacesEntities()) {
		indicesCount += 3 * facesEntity.getFaces()->size();
	}
	// create face vertex indices
	mesh->indices.resize(indicesCount);
	{
		auto j = 0;
		for (auto& facesEntity : *group->getFacesEntities())
		for (auto& face : *facesEntity.getFaces())
		for (auto& vertexIndex : *face.getVertexIndices()) {
			mesh->indices[j++] = vertexIndex;
		}
	}
	// texture coordinates
	mesh->textureCoordinates = groupTextureCoordinates;
	//
	mesh->recreatedBuffers = false;
	// group transformations matrix
	if (mesh->animationProcessingTarget == Engine::AnimationProcessingTarget::CPU ||
		mesh->animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING ||
		mesh->animationProcessingTarget == Engine::AnimationProcessingTarget::GPU) {
		auto transformationMatrixIt = transformationMatrices->find(group->getId());
		// group transformations matrix
		mesh->cGroupTransformationsMatrix = transformationMatrixIt != transformationMatrices->end()?transformationMatrixIt->second:nullptr;
	}
	// skinning
	if ((skinning != nullptr &&
		(animationProcessingTarget == Engine::AnimationProcessingTarget::CPU || animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING))) {
		// skinning computation caches if computing skinning on CPU
		if (mesh->animationProcessingTarget == Engine::AnimationProcessingTarget::CPU || mesh->animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
			mesh->cSkinningJointWeight.resize(groupVertices->size());
			mesh->cSkinningJointTransformationsMatrices.resize(groupVertices->size());
			// compute joint weight caches
			auto joints = skinning->getJoints();
			auto weights = skinning->getWeights();
			auto jointsWeights = skinning->getVerticesJointsWeights();
			for (auto vertexIndex = 0; vertexIndex < groupVertices->size(); vertexIndex++) {
				auto vertexJointWeights = (*jointsWeights)[vertexIndex].size();
				if (vertexJointWeights > mesh->cSkinningMaxVertexWeights)
					mesh->cSkinningMaxVertexWeights = vertexJointWeights;

				mesh->cSkinningJointWeight[vertexIndex].resize(vertexJointWeights);
				mesh->cSkinningJointTransformationsMatrices[vertexIndex].resize(vertexJointWeights);
				auto jointWeightIdx = 0;
				for (auto& jointWeight : (*jointsWeights)[vertexIndex]) {
					auto& joint = (*joints)[jointWeight.getJointIndex()];
					mesh->cSkinningJointWeight[vertexIndex][jointWeightIdx] = (*weights)[jointWeight.getWeightIndex()];
					auto skinningMatrixIt = skinningMatrices->find(joint.getGroupId());
					mesh->cSkinningJointTransformationsMatrices[vertexIndex][jointWeightIdx] = skinningMatrixIt != skinningMatrices->end()?skinningMatrixIt->second:nullptr;
					// next
					jointWeightIdx++;
				}
			}
		}
	}
	mesh->recreateBuffers();
	return mesh;
}

void Object3DGroupMesh::computeTransformations(void* context)
{
	Vector3 tmpVector3;
	auto groupVertices = group->getVertices();
	auto groupNormals = group->getNormals();
	auto groupTangent = group->getTangents();
	auto groupBitangent = group->getBitangents();
	// transformations for skinned meshes
	auto skinning = group->getSkinning();
	if (skinning != nullptr) {
		// compute skinning on CPU if required
		if (animationProcessingTarget == Engine::AnimationProcessingTarget::GPU) {
			Engine::getSkinningShader()->computeSkinning(context, this);
		} else
		if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU || animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
			auto jointsWeights = skinning->getVerticesJointsWeights();
			Vector3* vertex;
			Vector3* transformedVertex;
			Vector3* normal;
			Vector3* transformedNormal;
			Vector3* tangent;
			Vector3* transformedTangent;
			Vector3* bitangent;
			Vector3* transformedBitangent;
			float totalWeights;
			float weightNormalized;
			for (auto vertexIndex = 0; vertexIndex < groupVertices->size(); vertexIndex++) {
				// do vertices
				vertex = &(*groupVertices)[vertexIndex];
				transformedVertex = &(*vertices)[vertexIndex].set(0.0f, 0.0f, 0.0f);
				normal = &(*groupNormals)[vertexIndex];
				transformedNormal = &(*normals)[vertexIndex].set(0.0f, 0.0f, 0.0f);
				tangent = groupTangent->size() > 0 ? &(*groupTangent)[vertexIndex] : static_cast< Vector3* >(nullptr);
				transformedTangent = tangents != nullptr ? &(*tangents)[vertexIndex].set(0.0f, 0.0f, 0.0f) : static_cast< Vector3* >(nullptr);
				bitangent = groupTangent->size() > 0 ? &(*groupBitangent)[vertexIndex] : static_cast< Vector3* >(nullptr);
				transformedBitangent = bitangents != nullptr ? &(*bitangents)[vertexIndex].set(0.0f, 0.0f, 0.0f) : static_cast< Vector3* >(nullptr);
				// compute every influence on vertex and vertex normals
				totalWeights = 0.0f;
				for (auto vertexJointWeightIdx = 0; vertexJointWeightIdx < (*jointsWeights)[vertexIndex].size(); vertexJointWeightIdx++) {
					auto weight = cSkinningJointWeight[vertexIndex][vertexJointWeightIdx];
					// skinning transformation matrix
					auto cTransformationsMatrix = cSkinningJointTransformationsMatrices[vertexIndex][vertexJointWeightIdx];
					// vertex
					transformedVertex->add(cTransformationsMatrix->multiply(*vertex, tmpVector3).scale(weight));
					// normals
					transformedNormal->add(cTransformationsMatrix->multiplyNoTranslation(*normal, tmpVector3).scale(weight));
					// tangent
					if (tangent != nullptr) {
						transformedTangent->add(cTransformationsMatrix->multiplyNoTranslation(*tangent, tmpVector3).scale(weight));
					}
					// bitangent
					if (bitangent != nullptr) {
						transformedBitangent->add(cTransformationsMatrix->multiplyNoTranslation(*bitangent, tmpVector3).scale(weight));
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
			// recreate buffers
			recreateBuffers();
		}
	} else
	if (animationProcessingTarget == Engine::AnimationProcessingTarget::CPU_NORENDERING) {
		// transformations for non skinned rendering
		//	vertices
		for (auto vertexIndex = 0; vertexIndex < groupVertices->size(); vertexIndex++) {
			(*vertices)[vertexIndex].set(cGroupTransformationsMatrix->multiply((*groupVertices)[vertexIndex], tmpVector3));
		}
		//	normals
		for (auto normalIndex = 0; normalIndex < groupNormals->size(); normalIndex++) {
			(*normals)[normalIndex].set(cGroupTransformationsMatrix->multiplyNoTranslation((*groupNormals)[normalIndex], tmpVector3).normalize());
		}
		//	TODO: tangents, bitangents, but actually it is only in use for computing bounding volumes, so I am not in a hurry
		// recreate buffers
		recreateBuffers();
	}
}

void Object3DGroupMesh::recreateBuffers()
{
	recreatedBuffers = true;
}

bool Object3DGroupMesh::getRecreatedBuffers()
{
	if (recreatedBuffers == true) {
		recreatedBuffers = false;
		return true;
	} else {
		return false;
	}
}

void Object3DGroupMesh::setupVertexIndicesBuffer(Renderer* renderer, void* context, int32_t vboId)
{
	if (renderer->isUsingShortIndices() == true) {
		if (indices.size() > 65535) {
			Console::println(
				"Object3DGroupMesh::setupVertexIndicesBuffer(): " +
				group->getModel()->getName() + ":" +
				group->getName() + ":" +
				"more than 2^16-1 indices"
			);
		}
		auto sbIndices = ObjectBuffer::getByteBuffer(context, faceCount * 3 * sizeof(uint16_t))->asShortBuffer();
		// create face vertex indices, will never be changed in engine
		for (auto index : indices) {
			sbIndices.put(index);
		}
		// done, upload
		renderer->uploadIndicesBufferObject(context, vboId, sbIndices.getPosition() * sizeof(uint16_t), &sbIndices);
	} else {
		auto ibIndices = ObjectBuffer::getByteBuffer(context, faceCount * 3 * sizeof(uint32_t))->asIntBuffer();
		// create face vertex indices, will never be changed in engine
		for (auto index : indices) {
			ibIndices.put(index);
		}
		// done, upload
		renderer->uploadIndicesBufferObject(context, vboId, ibIndices.getPosition() * sizeof(uint32_t), &ibIndices);
	}
}

void Object3DGroupMesh::setupTextureCoordinatesBuffer(Renderer* renderer, void* context, int32_t vboId)
{
	// check if we have texture coordinates
	auto groupTextureCoordinates = group->getTextureCoordinates();
	if (groupTextureCoordinates == nullptr) return;
	// create texture coordinates buffer, will never be changed in engine
	auto fbTextureCoordinates = ObjectBuffer::getByteBuffer(context, groupTextureCoordinates->size() * 2 * sizeof(float))->asFloatBuffer();
	// construct texture coordinates byte buffer as this will not change usually
	for (auto& textureCoordinate : *groupTextureCoordinates) {
		fbTextureCoordinates.put(textureCoordinate.getArray());
	}
	// done, upload
	renderer->uploadBufferObject(context, vboId, fbTextureCoordinates.getPosition() * sizeof(float), &fbTextureCoordinates);
}

void Object3DGroupMesh::setupVerticesBuffer(Renderer* renderer, void* context, int32_t vboId)
{
	auto fbVertices = ObjectBuffer::getByteBuffer(context, vertices->size() * 3 * sizeof(float))->asFloatBuffer();
	// create vertices buffers
	for (auto& vertex : *vertices) {
		fbVertices.put(vertex.getArray());
	}
	// done, upload
	renderer->uploadBufferObject(context, vboId, fbVertices.getPosition() * sizeof(float), &fbVertices);
}

void Object3DGroupMesh::setupNormalsBuffer(Renderer* renderer, void* context, int32_t vboId)
{
	auto fbNormals = ObjectBuffer::getByteBuffer(context, normals->size() * 3 * sizeof(float))->asFloatBuffer();
	// create normals buffers
	for (auto& normal : *normals) {
		fbNormals.put(normal.getArray());
	}
	// done, upload
	renderer->uploadBufferObject(context, vboId, fbNormals.getPosition() * sizeof(float), &fbNormals);
}

void Object3DGroupMesh::setupTangentsBuffer(Renderer* renderer, void* context, int32_t vboId)
{
	// check if we have tangents
	if (tangents == nullptr) return;
	auto fbTangents = ObjectBuffer::getByteBuffer(context, tangents->size() * 3 * sizeof(float))->asFloatBuffer();
	// create tangents buffers
	for (auto& tangent : *tangents) {
		fbTangents.put(tangent.getArray());
	}
	// done, upload
	renderer->uploadBufferObject(context, vboId, fbTangents.getPosition() * sizeof(float), &fbTangents);
}

void Object3DGroupMesh::setupBitangentsBuffer(Renderer* renderer, void* context, int32_t vboId)
{
	// check if we have bitangents
	if (bitangents == nullptr) return;
	auto fbBitangents = ObjectBuffer::getByteBuffer(context, bitangents->size() * 3 * sizeof(float))->asFloatBuffer();
	// create bitangents buffers
	for (auto& bitangent : *bitangents) {
		fbBitangents.put(bitangent.getArray());
	}
	// done, upload
	renderer->uploadBufferObject(context, vboId, fbBitangents.getPosition() * sizeof(float), &fbBitangents);
}

