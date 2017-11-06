#include <tdme/engine/model/ModelHelper.h>

#include <array>
#include <vector>

#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper_VertexOrder.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>

using std::array;
using std::vector;

using tdme::engine::model::ModelHelper;
using tdme::engine::model::Animation;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper_VertexOrder;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::utils::Console;

ModelHelper_VertexOrder* ModelHelper::determineVertexOrder(array<Vector3,3>* vertices)
{
	auto edgeSum = 0;
	for (auto i = 0; i < vertices->size(); i++) {
		auto currentVertexXYZ = (*vertices)[i].getArray();
		auto nextVertexXYZ = (*vertices)[(i + 1) % vertices->size()].getArray();
		edgeSum +=
			(nextVertexXYZ[0] - currentVertexXYZ[0]) * (nextVertexXYZ[1] - currentVertexXYZ[1]) * (nextVertexXYZ[2] - currentVertexXYZ[0]);
	}
	if (edgeSum >= 0) {
		return ModelHelper_VertexOrder::CLOCKWISE;
	} else {
		return ModelHelper_VertexOrder::COUNTERCLOCKWISE;
	}
}

void ModelHelper::computeNormal(array<Vector3,3>* vertices, Vector3& normal)
{
	Vector3::computeCrossProduct(
		(*vertices)[1].clone().sub((*vertices)[0]),
		(*vertices)[2].clone().sub((*vertices)[0]),
		normal
	).normalize();
}

void ModelHelper::computeNormals(array<Vector3,3> *vertices, array<Vector3,3>* normals)
{
	Vector3 normal;
	computeNormal(vertices, normal);
	for (auto i = 0; i < vertices->size(); i++) {
		(*normals)[i].set(normal);
	}
}

void ModelHelper::createNormalTangentsAndBitangents(Group* group)
{
	vector<Vector3> tangentsArrayList;
	vector<Vector3> bitangentsArrayList;
	Vector2 uv0;
	Vector2 uv1;
	Vector2 uv2;
	Vector3 deltaPos1;
	Vector3 deltaPos2;
	Vector2 deltaUV1;
	Vector2 deltaUV2;
	Vector3 tmpVector3;
	auto vertices = group->getVertices();
	auto normals = group->getNormals();
	auto textureCoordinates = group->getTextureCoordinates();
	for (auto& faceEntity : *group->getFacesEntities())
		if (faceEntity.getMaterial() != nullptr && faceEntity.getMaterial()->hasNormalTexture() == true) {
			for (auto& face : *faceEntity.getFaces()) {
				auto verticesIndexes = face.getVertexIndices();
				auto v0 = &(*vertices)[(*verticesIndexes)[0]];
				auto v1 = &(*vertices)[(*verticesIndexes)[1]];
				auto v2 = &(*vertices)[(*verticesIndexes)[2]];
				auto textureCoordinatesIndexes = face.getTextureCoordinateIndices();
				uv0.set((*textureCoordinates)[(*textureCoordinatesIndexes)[0]].getArray());
				uv0.setY(1.0f - uv0.getY());
				uv1.set((*textureCoordinates)[(*textureCoordinatesIndexes)[1]].getArray());
				uv1.setY(1.0f - uv1.getY());
				uv2.set((*textureCoordinates)[(*textureCoordinatesIndexes)[2]].getArray());
				uv2.setY(1.0f - uv2.getY());
				deltaPos1.set(*v1).sub(*v0);
				deltaPos2.set(*v2).sub(*v0);
				deltaUV1.set(uv1).sub(uv0);
				deltaUV2.set(uv2).sub(uv0);
				auto r = 1.0f / (deltaUV1.getX() * deltaUV2.getY() - deltaUV1.getY() * deltaUV2.getX());
				auto tangent = deltaPos1.clone().scale(deltaUV2.getY()).sub(tmpVector3.set(deltaPos2).scale(deltaUV1.getY())).scale(r);
				auto bitangent = deltaPos2.clone().scale(deltaUV1.getX()).sub(tmpVector3.set(deltaPos1).scale(deltaUV2.getX())).scale(r);
				face.setTangentIndices(tangentsArrayList.size() + 0, tangentsArrayList.size() + 1, tangentsArrayList.size() + 2);
				face.setBitangentIndices(bitangentsArrayList.size() + 0, bitangentsArrayList.size() + 1, bitangentsArrayList.size() + 2);
				tangentsArrayList.push_back(tangent);
				tangentsArrayList.push_back(tangent);
				tangentsArrayList.push_back(tangent);
				bitangentsArrayList.push_back(bitangent);
				bitangentsArrayList.push_back(bitangent);
				bitangentsArrayList.push_back(bitangent);
			}
		}

	if (tangentsArrayList.size() > 0 && bitangentsArrayList.size() > 0) {
		group->setTangents(&tangentsArrayList);
		group->setBitangents(&bitangentsArrayList);
		auto tangents = group->getTangents();
		auto bitangents = group->getBitangents();
		for (auto& faceEntity : *group->getFacesEntities())
		if (faceEntity.getMaterial() != nullptr && faceEntity.getMaterial()->hasNormalTexture() == true) {
			for (auto& face : *faceEntity.getFaces())
			for (auto i = 0; i < 3; i++) {
				auto normal = &(*normals)[(*face.getNormalIndices())[i]];
				auto tangent = &(*tangents)[(*face.getTangentIndices())[i]];
				auto bitangent = &(*bitangents)[(*face.getBitangentIndices())[i]];
				tangent->sub(tmpVector3.set(*normal).scale(Vector3::computeDotProduct(*normal, *tangent))).normalize();
				if (Vector3::computeDotProduct(Vector3::computeCrossProduct(*normal, *tangent, tmpVector3), *bitangent) < 0.0f) {
					tangent->scale(-1.0f);
				}
				bitangent->normalize();
			}
		}
	}
}

void ModelHelper::prepareForIndexedRendering(Model* model)
{
	prepareForIndexedRendering(model->getSubGroups());
}

void ModelHelper::prepareForIndexedRendering(map<string, Group*>* groups)
{
	for (auto it: *groups) {
		Group* group = it.second;
		auto groupVertices = group->getVertices();
		auto groupNormals = group->getNormals();
		auto groupTextureCoordinates = group->getTextureCoordinates();
		auto groupTangents = group->getTangents();
		auto groupBitangents = group->getBitangents();
		auto groupFaceCount = group->getFaceCount();
		vector<int32_t> vertexMapping;
		vector<Vector3> indexedVertices;
		vector<Vector3> indexedNormals;
		vector<TextureCoordinate> indexedTextureCoordinates;
		vector<Vector3> indexedTangents;
		vector<Vector3> indexedBitangents;
		auto preparedIndices = 0;
		for (auto& facesEntity : *group->getFacesEntities()) {
			for (auto& face : *facesEntity.getFaces()) {
				auto faceVertexIndices = face.getVertexIndices();
				auto faceNormalIndices = face.getNormalIndices();
				auto faceTextureIndices = face.getTextureCoordinateIndices();
				auto faceTangentIndices = face.getTangentIndices();
				auto faceBitangentIndices = face.getBitangentIndices();
				array<int32_t, 3> indexedFaceVertexIndices;
				for (int16_t idx = 0; idx < 3; idx++) {
					auto groupVertexIndex = (*faceVertexIndices)[idx];
					auto groupNormalIndex = (*faceNormalIndices)[idx];
					auto groupTextureCoordinateIndex = faceTextureIndices != nullptr ? (*faceTextureIndices)[idx] : 0;
					auto groupTangentIndex = faceTangentIndices != nullptr ? (*faceTangentIndices)[idx] : 0;
					auto groupBitangentIndex = faceBitangentIndices != nullptr ? (*faceBitangentIndices)[idx] : 0;
					auto vertex = &(*groupVertices)[groupVertexIndex];
					auto normal = &(*groupNormals)[groupNormalIndex];
					auto textureCoordinate = groupTextureCoordinates->size() > 0 ? &(*groupTextureCoordinates)[groupTextureCoordinateIndex] : static_cast< TextureCoordinate* >(nullptr);
					auto tangent = groupTangents->size() > 0 ? &(*groupTangents)[groupTangentIndex] : static_cast< Vector3* >(nullptr);
					auto bitangent = groupBitangents->size() > 0 ? &(*groupBitangents)[groupBitangentIndex] : static_cast< Vector3* >(nullptr);
					auto newIndex = preparedIndices;
					for (auto i = 0; i < preparedIndices; i++)
					if (indexedVertices[i].equals(*vertex) &&
						indexedNormals[i].equals(*normal) &&
					    (textureCoordinate == nullptr || indexedTextureCoordinates[i].equals(*textureCoordinate)) &&
					    (tangent == nullptr || indexedTangents[i].equals(*tangent)) &&
						(bitangent == nullptr || indexedBitangents[i].equals(*bitangent))) {
						newIndex = i;
						break;
					}
					if (newIndex == preparedIndices) {
						vertexMapping.push_back(groupVertexIndex);
						indexedVertices.push_back(*vertex);;
						indexedNormals.push_back(*normal);;
						if (textureCoordinate != nullptr) indexedTextureCoordinates.push_back(*textureCoordinate);
						if (tangent != nullptr) indexedTangents.push_back(*tangent);
						if (bitangent != nullptr) indexedBitangents.push_back(*bitangent);
						preparedIndices++;
					}
					indexedFaceVertexIndices[idx] = newIndex;
				}
				face.setIndexedRenderingIndices(&indexedFaceVertexIndices);
			}
		}
		auto skinning = group->getSkinning();
		if (skinning != nullptr) {
			prepareForIndexedRendering(skinning, &vertexMapping, preparedIndices);
		}
		group->setVertices(&indexedVertices);
		group->setNormals(&indexedNormals);
		if (groupTextureCoordinates->size() > 0) {
			group->setTextureCoordinates(&indexedTextureCoordinates);
		}
		if (groupTangents != nullptr && groupBitangents != nullptr) {
			group->setTangents(&indexedTangents);
			group->setBitangents(&indexedBitangents);
		}
		prepareForIndexedRendering(group->getSubGroups());
	}
}

void ModelHelper::prepareForIndexedRendering(Skinning* skinning, vector<int32_t>* vertexMapping, int32_t vertices)
{
	auto originalVerticesJointsWeights = skinning->getVerticesJointsWeights();
	vector<vector<JointWeight>> verticesJointsWeights;
	verticesJointsWeights.resize(vertices);
	for (auto i = 0; i < vertices; i++) {
		auto vertexOriginalMappedToIdx = (*vertexMapping)[i];
		verticesJointsWeights[i].resize((*originalVerticesJointsWeights)[vertexOriginalMappedToIdx].size());
		for (auto j = 0; j < verticesJointsWeights[i].size(); j++) {
			verticesJointsWeights[i][j] = (*originalVerticesJointsWeights)[vertexOriginalMappedToIdx][j];
		}
	}
	skinning->setVerticesJointsWeights(&verticesJointsWeights);
}

void ModelHelper::setDiffuseMaskedTransparency(Model* model) {
	auto materials = model->getMaterials();
	for (auto it = materials->begin(); it != materials->end(); ++it) {
		auto material = it->second;
		if (material->hasDiffuseTextureTransparency() == true) {
			material->setDiffuseTextureMaskedTransparency(true);
		}
	}
}

void ModelHelper::setupJoints(Model* model)
{
	auto groups = model->getGroups();
	for (auto it: *model->getSubGroups()) {
		Group* group = it.second;
		auto skinning = group->getSkinning();
		if (skinning != nullptr) {
			for (auto& joint : *skinning->getJoints()) {
				auto jointGroupIt = groups->find(joint.getGroupId());
				if (jointGroupIt != groups->end()) {
					setJoint(jointGroupIt->second);
				}
			}
		}
	}
}

void ModelHelper::setJoint(Group* root)
{
	root->setJoint(true);
	for (auto it: *root->getSubGroups()) {
		Group* group = it.second;
		setJoint(group);
	}
}

void ModelHelper::fixAnimationLength(Model* model)
{
	auto defaultAnimation = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);
	if (defaultAnimation != nullptr) {
		for (auto it: *model->getSubGroups()) {
			Group* group = it.second;
			fixAnimationLength(group, defaultAnimation->getFrames());
		}
	}
}

void ModelHelper::fixAnimationLength(Group* root, int32_t frames)
{
	auto animation = root->getAnimation();
	vector<Matrix4x4>* transformationsMatrices;
	if (animation != nullptr) {
		transformationsMatrices = root->getAnimation()->getTransformationsMatrices();
		animation = root->createAnimation(frames);
		for (auto i = 0; i < transformationsMatrices->size(); i++) {
			(*animation->getTransformationsMatrices())[i].set((*transformationsMatrices)[i]);
		}
	}
	for (auto it: *root->getSubGroups()) {
		Group* group = it.second;
		fixAnimationLength(group, frames);
	}
}

void ModelHelper::createDefaultAnimation(Model* model, int32_t frames)
{
	auto defaultAnimation = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);
	if (defaultAnimation == nullptr) {
		model->addAnimationSetup(Model::ANIMATIONSETUP_DEFAULT, 0, frames - 1, true);
	} else {
		if (defaultAnimation->getStartFrame() != 0 || defaultAnimation->getEndFrame() != frames - 1) {
			Console::println(string("Warning: default animation mismatch"));
		}
		if (frames - 1 > defaultAnimation->getEndFrame()) {
			Console::println(string("Warning: default animation mismatch, will be fixed"));
			model->addAnimationSetup(Model::ANIMATIONSETUP_DEFAULT, 0, frames - 1, true);
		}
	}
}

