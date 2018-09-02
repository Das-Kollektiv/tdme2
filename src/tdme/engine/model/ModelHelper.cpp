#include <tdme/engine/model/ModelHelper.h>

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/engine/Transformations.h>
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
#include <tdme/tools/shared/model/LevelEditorObject.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/StringUtils.h>

using std::array;
using std::map;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::Transformations;
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
using tdme::tools::shared::model::LevelEditorObject;
using tdme::utils::Console;
using tdme::utils::StringUtils;

ModelHelper_VertexOrder* ModelHelper::determineVertexOrder(const vector<Vector3>& vertices)
{
	auto edgeSum = 0;
	for (auto i = 0; i < vertices.size(); i++) {
		auto& currentVertexXYZ = vertices[i].getArray();
		auto& nextVertexXYZ = vertices[(i + 1) % vertices.size()].getArray();
		edgeSum +=
			(nextVertexXYZ[0] - currentVertexXYZ[0]) * (nextVertexXYZ[1] - currentVertexXYZ[1]) * (nextVertexXYZ[2] - currentVertexXYZ[2]);
	}
	if (edgeSum >= 0) {
		return ModelHelper_VertexOrder::CLOCKWISE;
	} else {
		return ModelHelper_VertexOrder::COUNTERCLOCKWISE;
	}
}

void ModelHelper::computeNormal(const array<Vector3,3>& vertices, Vector3& normal)
{
	// face normal
	Vector3::computeCrossProduct(
		(vertices)[1].clone().sub((vertices)[0]),
		(vertices)[2].clone().sub((vertices)[0]),
		normal
	).normalize();
}

void ModelHelper::computeNormals(const array<Vector3,3>& vertices, array<Vector3,3>& normals)
{
	// face normal
	Vector3 normal;
	computeNormal(vertices, normal);

	// compute vertex normal
	for (auto i = 0; i < vertices.size(); i++) {
		(normals)[i].set(normal);
	}
}

void ModelHelper::createNormalTangentsAndBitangents(Group* group)
{
	// what we need
	vector<Vector3> tangentsArrayList;
	vector<Vector3> bitangentsArrayList;
	// temporary variables
	Vector2 uv0;
	Vector2 uv1;
	Vector2 uv2;
	Vector3 deltaPos1;
	Vector3 deltaPos2;
	Vector2 deltaUV1;
	Vector2 deltaUV2;
	Vector3 tmpVector3;
	// create it
	auto vertices = group->getVertices();
	auto normals = group->getNormals();
	auto textureCoordinates = group->getTextureCoordinates();
	for (auto& faceEntity : *group->getFacesEntities())
	if (faceEntity.getMaterial() != nullptr && faceEntity.getMaterial()->hasNormalTexture() == true) {
		for (auto& face : *faceEntity.getFaces()) {
			// Shortcuts for vertices
			auto verticesIndexes = face.getVertexIndices();
			auto v0 = &(*vertices)[(*verticesIndexes)[0]];
			auto v1 = &(*vertices)[(*verticesIndexes)[1]];
			auto v2 = &(*vertices)[(*verticesIndexes)[2]];
			// shortcuts for UVs
			auto textureCoordinatesIndexes = face.getTextureCoordinateIndices();
			uv0.set((*textureCoordinates)[(*textureCoordinatesIndexes)[0]].getArray());
			uv0.setY(1.0f - uv0.getY());
			uv1.set((*textureCoordinates)[(*textureCoordinatesIndexes)[1]].getArray());
			uv1.setY(1.0f - uv1.getY());
			uv2.set((*textureCoordinates)[(*textureCoordinatesIndexes)[2]].getArray());
			uv2.setY(1.0f - uv2.getY());
			// edges of the triangle : position delta
			deltaPos1.set(*v1).sub(*v0);
			deltaPos2.set(*v2).sub(*v0);
			// UV delta
			deltaUV1.set(uv1).sub(uv0);
			deltaUV2.set(uv2).sub(uv0);
			// compute tangent and bitangent
			auto r = 1.0f / (deltaUV1.getX() * deltaUV2.getY() - deltaUV1.getY() * deltaUV2.getX());
			auto tangent = deltaPos1.clone().scale(deltaUV2.getY()).sub(tmpVector3.set(deltaPos2).scale(deltaUV1.getY())).scale(r);
			auto bitangent = deltaPos2.clone().scale(deltaUV1.getX()).sub(tmpVector3.set(deltaPos1).scale(deltaUV2.getX())).scale(r);
			// set up tangent face indices
			face.setTangentIndices(tangentsArrayList.size() + 0, tangentsArrayList.size() + 1, tangentsArrayList.size() + 2);
			// set up bitangent face indices
			face.setBitangentIndices(bitangentsArrayList.size() + 0, bitangentsArrayList.size() + 1, bitangentsArrayList.size() + 2);
			// add to group tangents, bitangents
			tangentsArrayList.push_back(tangent);
			tangentsArrayList.push_back(tangent);
			tangentsArrayList.push_back(tangent);
			bitangentsArrayList.push_back(bitangent);
			bitangentsArrayList.push_back(bitangent);
			bitangentsArrayList.push_back(bitangent);
		}
	}

	// set up tangents and bitangents if we have any
	if (tangentsArrayList.size() > 0 && bitangentsArrayList.size() > 0) {
		group->setTangents(tangentsArrayList);
		group->setBitangents(bitangentsArrayList);
		// going further
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
	// we need to prepare the group for indexed rendering
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
		// construct indexed vertex data suitable for GL
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
				face.setIndexedRenderingIndices(indexedFaceVertexIndices);
			}
		}
		// remap skinning
		auto skinning = group->getSkinning();
		if (skinning != nullptr) {
			prepareForIndexedRendering(skinning, vertexMapping, preparedIndices);
		}
		group->setVertices(indexedVertices);
		group->setNormals(indexedNormals);
		if (groupTextureCoordinates->size() > 0) {
			group->setTextureCoordinates(indexedTextureCoordinates);
		}
		if (groupTangents != nullptr && groupBitangents != nullptr) {
			group->setTangents(indexedTangents);
			group->setBitangents(indexedBitangents);
		}
		// process sub groups
		prepareForIndexedRendering(group->getSubGroups());
	}
}

void ModelHelper::prepareForIndexedRendering(Skinning* skinning, const vector<int32_t>& vertexMapping, int32_t vertices)
{
	auto originalVerticesJointsWeights = skinning->getVerticesJointsWeights();
	vector<vector<JointWeight>> verticesJointsWeights;
	verticesJointsWeights.resize(vertices);
	for (auto i = 0; i < vertices; i++) {
		auto vertexOriginalMappedToIdx = vertexMapping[i];
		verticesJointsWeights[i].resize((*originalVerticesJointsWeights)[vertexOriginalMappedToIdx].size());
		for (auto j = 0; j < verticesJointsWeights[i].size(); j++) {
			verticesJointsWeights[i][j] = (*originalVerticesJointsWeights)[vertexOriginalMappedToIdx][j];
		}
	}
	skinning->setVerticesJointsWeights(verticesJointsWeights);
}

void ModelHelper::setDiffuseMaskedTransparency(Model* model, bool maskedTransparency) {
	auto materials = model->getMaterials();
	for (auto it = materials->begin(); it != materials->end(); ++it) {
		auto material = it->second;
		if (material->hasDiffuseTextureTransparency() == true) {
			material->setDiffuseTextureMaskedTransparency(maskedTransparency);
		}
	}
}

void ModelHelper::setupJoints(Model* model)
{
	// determine joints and mark them as joints
	auto groups = model->getGroups();
	for (auto it: *model->getSubGroups()) {
		Group* group = it.second;
		auto skinning = group->getSkinning();
		// do we have a skinning
		if (skinning != nullptr) {
			// yep
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
	// fix animation length
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

bool ModelHelper::hasDefaultAnimation(Model* model) {
	return model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT) != nullptr;
}

void ModelHelper::createDefaultAnimation(Model* model, int32_t frames)
{
	// add default model animation setup if not yet done
	auto defaultAnimation = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);
	if (defaultAnimation == nullptr) {
		model->addAnimationSetup(Model::ANIMATIONSETUP_DEFAULT, 0, frames - 1, true);
	} else {
		// check default animation setup
		if (defaultAnimation->getStartFrame() != 0 || defaultAnimation->getEndFrame() != frames - 1) {
			Console::println(string("Warning: default animation mismatch"));
		}
		if (frames - 1 > defaultAnimation->getEndFrame()) {
			Console::println(string("Warning: default animation mismatch, will be fixed"));
			model->addAnimationSetup(Model::ANIMATIONSETUP_DEFAULT, 0, frames - 1, true);
		}
	}
}

Material* ModelHelper::cloneMaterial(Material* material) {
	auto clonedMaterial = new Material(material->getId());
	clonedMaterial->setAmbientColor(material->getAmbientColor());
	clonedMaterial->setDiffuseColor(material->getDiffuseColor());
	clonedMaterial->setEmissionColor(material->getEmissionColor());
	clonedMaterial->setSpecularColor(material->getSpecularColor());
	clonedMaterial->setShininess(material->getShininess());
	clonedMaterial->setDiffuseTextureMaskedTransparency(material->hasDiffuseTextureTransparency());
	clonedMaterial->setDiffuseTextureMaskedTransparencyThreshold(material->getDiffuseTextureMaskedTransparencyThreshold());
	if (material->getDiffuseTextureFileName().length() != 0) {
		clonedMaterial->setDiffuseTexture(
			material->getDiffuseTexturePathName(),
			material->getDiffuseTextureFileName(),
			material->getDiffuseTransparencyTexturePathName(),
			material->getDiffuseTransparencyTextureFileName()
		);
	}
	if (material->getNormalTextureFileName().length() != 0) {
		clonedMaterial->setNormalTexture(
			material->getNormalTexturePathName(),
			material->getNormalTextureFileName()
		);
	}
	if (material->getSpecularTextureFileName().length() != 0) {
		clonedMaterial->setSpecularTexture(
			material->getSpecularTexturePathName(),
			material->getSpecularTextureFileName()
		);
	}
	if (material->getDisplacementTextureFileName().length() != 0) {
		clonedMaterial->setDisplacementTexture(
			material->getDisplacementTexturePathName(),
			material->getDisplacementTextureFileName()
		);
	}
	return clonedMaterial;
}

void ModelHelper::cloneGroup(Group* sourceGroup, Model* targetModel, Group* targetParentGroup) {
	auto clonedGroup = new Group(targetModel, targetParentGroup, sourceGroup->getId(), sourceGroup->getName());
	clonedGroup->setVertices(*(sourceGroup->getVertices()));
	clonedGroup->setNormals(*(sourceGroup->getNormals()));
	clonedGroup->setTextureCoordinates(*(sourceGroup->getTextureCoordinates()));
	clonedGroup->setTangents(*(sourceGroup->getTangents()));
	clonedGroup->setBitangents(*(sourceGroup->getBitangents()));
	clonedGroup->setFacesEntities(*(sourceGroup->getFacesEntities()));
	clonedGroup->setJoint(false);
	clonedGroup->getTransformationsMatrix().set(sourceGroup->getTransformationsMatrix());
	for (auto& facesEntity: *clonedGroup->getFacesEntities()) {
		if (facesEntity.getMaterial() == nullptr) continue;
		Material* material = nullptr;
		auto materialIt = (*targetModel->getMaterials()).find(facesEntity.getMaterial()->getId());
		if (materialIt == (*targetModel->getMaterials()).end()) {
			material = cloneMaterial(facesEntity.getMaterial());
			(*targetModel->getMaterials())[material->getId()] = material;
		} else {
			material = materialIt->second;
		}
		facesEntity.setMaterial(material);
	}
	clonedGroup->determineFeatures();
	(*targetModel->getGroups())[clonedGroup->getId()] = clonedGroup;
	if (targetParentGroup == nullptr) {
		(*targetModel->getSubGroups())[clonedGroup->getId()] = clonedGroup;
	} else {
		(*targetParentGroup->getSubGroups())[clonedGroup->getId()] = clonedGroup;
	}
	for (auto sourceSubGroupIt: *sourceGroup->getSubGroups()) {
		auto subGroup = sourceSubGroupIt.second;
		cloneGroup(subGroup, targetModel, clonedGroup);
	}
}

void ModelHelper::partitionGroup(Group* sourceGroup, map<string, Model*>& modelsByPartition, map<string, Vector3>& modelsPosition, const Matrix4x4& parentTransformationsMatrix) {
	Vector3 faceCenter;

	Matrix4x4 transformationsMatrix;
	transformationsMatrix.set(sourceGroup->getTransformationsMatrix());
	transformationsMatrix.multiply(parentTransformationsMatrix);

	Vector3 vertex0;
	Vector3 vertex1;
	Vector3 vertex2;
	Vector3 normal0;
	Vector3 normal1;
	Vector3 normal2;
	TextureCoordinate textureCoordinate0;
	TextureCoordinate textureCoordinate1;
	TextureCoordinate textureCoordinate2;
	Vector3 tangent0;
	Vector3 tangent1;
	Vector3 tangent2;
	Vector3 bitangent0;
	Vector3 bitangent1;
	Vector3 bitangent2;

	Vector3 vertex0Transformed;
	Vector3 vertex1Transformed;
	Vector3 vertex2Transformed;

	auto sourceGroupId = sourceGroup->getModel()->getId();
	auto sourceGroupName = sourceGroup->getModel()->getName();

	// TODO: maybe check if id and group do have real file endings like .tm, .dae, .fbx or something
	if (StringUtils::lastIndexOf(sourceGroupId, '.') != -1) {
		sourceGroupId = StringUtils::substring(sourceGroupId, 0, StringUtils::lastIndexOf(sourceGroupId, '.') - 1);
	}
	if (StringUtils::lastIndexOf(sourceGroupName, '.') != -1) {
		sourceGroupName = StringUtils::substring(sourceGroupName, 0, StringUtils::lastIndexOf(sourceGroupName, '.') - 1);
	}

	for (auto& facesEntity: *sourceGroup->getFacesEntities()) {
		bool haveTextureCoordinates = facesEntity.isTextureCoordinatesAvailable();
		bool haveTangentsBitangents = facesEntity.isTangentBitangentAvailable();
		for (auto& face: *facesEntity.getFaces()) {
			// get face vertices and such
			auto& vertexIndices = *face.getVertexIndices();
			auto& normalIndices = *face.getNormalIndices();
			auto& textureCoordinatesIndices = *face.getTextureCoordinateIndices();
			auto& tangentIndices = *face.getTangentIndices();
			auto& bitangentIndices = *face.getBitangentIndices();
			vertex0.set((*sourceGroup->getVertices())[vertexIndices[0]]);
			vertex1.set((*sourceGroup->getVertices())[vertexIndices[1]]);
			vertex2.set((*sourceGroup->getVertices())[vertexIndices[2]]);
			normal0.set((*sourceGroup->getNormals())[normalIndices[0]]);
			normal1.set((*sourceGroup->getNormals())[normalIndices[1]]);
			normal2.set((*sourceGroup->getNormals())[normalIndices[2]]);
			if (haveTextureCoordinates == true) {
				textureCoordinate0.set((*sourceGroup->getTextureCoordinates())[textureCoordinatesIndices[0]]);
				textureCoordinate1.set((*sourceGroup->getTextureCoordinates())[textureCoordinatesIndices[1]]);
				textureCoordinate2.set((*sourceGroup->getTextureCoordinates())[textureCoordinatesIndices[2]]);
			}
			if (haveTangentsBitangents == true) {
				tangent0.set((*sourceGroup->getTangents())[tangentIndices[0]]);
				tangent1.set((*sourceGroup->getTangents())[tangentIndices[1]]);
				tangent2.set((*sourceGroup->getTangents())[tangentIndices[2]]);
				bitangent0.set((*sourceGroup->getBitangents())[bitangentIndices[0]]);
				bitangent1.set((*sourceGroup->getBitangents())[bitangentIndices[1]]);
				bitangent2.set((*sourceGroup->getBitangents())[bitangentIndices[2]]);
			}

			// find out partition by transforming vertices into world coordinates
			transformationsMatrix.multiply(vertex0, vertex0Transformed);
			transformationsMatrix.multiply(vertex1, vertex1Transformed);
			transformationsMatrix.multiply(vertex2, vertex2Transformed);
			faceCenter.set(vertex0Transformed);
			faceCenter.add(vertex1Transformed);
			faceCenter.add(vertex2Transformed);
			faceCenter.scale(1.0f / 3.0f);
			auto minX = Math::min(Math::min(vertex0Transformed.getX(), vertex1Transformed.getX()), vertex2Transformed.getX());
			auto minY = Math::min(Math::min(vertex0Transformed.getY(), vertex1Transformed.getY()), vertex2Transformed.getY());
			auto minZ = Math::min(Math::min(vertex0Transformed.getZ(), vertex1Transformed.getZ()), vertex2Transformed.getZ());
			int partitionX = (int)(minX / 64.0f);
			int partitionY = (int)(minY / 64.0f);
			int partitionZ = (int)(minZ / 64.0f);

			// key
			string partitionModelKey =
				to_string(partitionX) + "," +
				to_string(partitionY) + "," +
				to_string(partitionZ);

			// get model
			auto partitionModel = modelsByPartition[partitionModelKey];
			if (partitionModel == nullptr) {
				partitionModel = new Model(
					sourceGroupId + "." + partitionModelKey,
					sourceGroupName + "." + partitionModelKey,
					sourceGroup->getModel()->getUpVector(),
					sourceGroup->getModel()->getRotationOrder(),
					nullptr
				);
				modelsByPartition[partitionModelKey] = partitionModel;
				modelsPosition[partitionModelKey].set(partitionX * 64.0f, partitionY * 64.0f, partitionZ * 64.0f);
			}

			// get group
			auto partitionModelGroup = partitionModel->getGroupById(sourceGroup->getId());
			if (partitionModelGroup == nullptr) {
				// TODO: create sub groups if they do not yet exist
				partitionModelGroup = new Group(
					partitionModel,
					sourceGroup->getParentGroup() == nullptr?nullptr:partitionModel->getGroupById(sourceGroup->getParentGroup()->getId()),
					sourceGroup->getId(),
					sourceGroup->getName()
				);
				partitionModelGroup->getTransformationsMatrix().set(sourceGroup->getTransformationsMatrix());
				if (sourceGroup->getParentGroup() == nullptr) {
					(*partitionModel->getSubGroups())[partitionModelGroup->getId()] = partitionModelGroup;
				} else {
					(*partitionModelGroup->getParentGroup()->getSubGroups())[partitionModelGroup->getId()] = partitionModelGroup;
				}
				(*partitionModel->getGroups())[partitionModelGroup->getId()] = partitionModelGroup;
			}

			// get faces entity
			FacesEntity* partitionModelGroupFacesEntity = nullptr;
			for (auto& partitionModelGroupFacesEntityExisting: *partitionModelGroup->getFacesEntities()) {
				if (partitionModelGroupFacesEntityExisting.getId() == facesEntity.getId()) {
					partitionModelGroupFacesEntity = &partitionModelGroupFacesEntityExisting;
				}
			}
			if (partitionModelGroupFacesEntity == nullptr) {
				partitionModelGroup->getFacesEntities()->push_back(
					FacesEntity(
						partitionModelGroup,
						facesEntity.getId()
					)
				);
				partitionModelGroupFacesEntity = &(*partitionModelGroup->getFacesEntities())[partitionModelGroup->getFacesEntities()->size() - 1];
				auto partitionModelGroupFacesEntityMaterial = (*partitionModel->getMaterials())[facesEntity.getMaterial()->getId()];
				if (partitionModelGroupFacesEntityMaterial == nullptr) {
					partitionModelGroupFacesEntityMaterial = cloneMaterial(facesEntity.getMaterial());
					(*partitionModel->getMaterials())[facesEntity.getMaterial()->getId()] = partitionModelGroupFacesEntityMaterial;
				}
				(*partitionModelGroup->getFacesEntities())[partitionModelGroup->getFacesEntities()->size() - 1].setMaterial(partitionModelGroupFacesEntityMaterial);
			}

			// add vertices and such
			auto verticesIdx = partitionModelGroup->getVertices()->size();
			partitionModelGroup->getVertices()->push_back(vertex0);
			partitionModelGroup->getVertices()->push_back(vertex1);
			partitionModelGroup->getVertices()->push_back(vertex2);
			partitionModelGroup->getNormals()->push_back(normal0);
			partitionModelGroup->getNormals()->push_back(normal1);
			partitionModelGroup->getNormals()->push_back(normal2);
			if (haveTextureCoordinates == true) {
				partitionModelGroup->getTextureCoordinates()->push_back(textureCoordinate0);
				partitionModelGroup->getTextureCoordinates()->push_back(textureCoordinate1);
				partitionModelGroup->getTextureCoordinates()->push_back(textureCoordinate2);
			}
			if (haveTangentsBitangents == true) {
				partitionModelGroup->getTangents()->push_back(tangent0);
				partitionModelGroup->getTangents()->push_back(tangent1);
				partitionModelGroup->getTangents()->push_back(tangent2);
				partitionModelGroup->getBitangents()->push_back(bitangent0);
				partitionModelGroup->getBitangents()->push_back(bitangent1);
				partitionModelGroup->getBitangents()->push_back(bitangent2);
			}
			partitionModelGroupFacesEntity->getFaces()->push_back(
				Face(
					partitionModelGroup,
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2,
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2
				)
			);
			if (haveTextureCoordinates == true) {
				(*partitionModelGroupFacesEntity->getFaces())[partitionModelGroupFacesEntity->getFaces()->size() - 1].setTextureCoordinateIndices(
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2
				);
			}
			if (haveTangentsBitangents == true) {
				(*partitionModelGroupFacesEntity->getFaces())[partitionModelGroupFacesEntity->getFaces()->size() - 1].setTangentIndices(
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2
				);
				(*partitionModelGroupFacesEntity->getFaces())[partitionModelGroupFacesEntity->getFaces()->size() - 1].setBitangentIndices(
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2
				);
			}
		}
	}

	for (auto modelByPartitionIt: modelsByPartition) {
		auto modelByPartitionGroup = modelByPartitionIt.second->getGroupById(sourceGroup->getId());
		if (modelByPartitionGroup != nullptr) modelByPartitionGroup->determineFeatures();
	}

	for (auto groupIt: *sourceGroup->getSubGroups()) {
		partitionGroup(groupIt.second, modelsByPartition, modelsPosition, transformationsMatrix);
	}
}

void ModelHelper::partition(Model* model, const Transformations& transformations, map<string, Model*>& modelsByPartition, map<string, Vector3>& modelsPosition) {
	Matrix4x4 transformationsMatrix;
	transformationsMatrix.set(model->getImportTransformationsMatrix());
	transformationsMatrix.multiply(transformations.getTransformationsMatrix());
	for (auto groupIt: *model->getSubGroups()) {
		partitionGroup(groupIt.second, modelsByPartition, modelsPosition, transformationsMatrix);
	}
	for (auto modelsByPartitionIt: modelsByPartition) {
		auto partitionKey = modelsByPartitionIt.first;
		auto partitionModel = modelsByPartitionIt.second;
		partitionModel->getImportTransformationsMatrix().set(model->getImportTransformationsMatrix());
		ModelHelper::createDefaultAnimation(partitionModel, 0);
		ModelHelper::setupJoints(partitionModel);
		ModelHelper::fixAnimationLength(partitionModel);
		ModelHelper::prepareForIndexedRendering(partitionModel);
	}
}

void ModelHelper::shrinkToFit(Group* group) {
	for (auto& facesEntity: *group->getFacesEntities()) {
		facesEntity.getFaces()->shrink_to_fit();
	}

	group->getFacesEntities()->shrink_to_fit();
	group->getVertices()->shrink_to_fit();
	group->getNormals()->shrink_to_fit();
	group->getTextureCoordinates()->shrink_to_fit();
	group->getTangents()->shrink_to_fit();
	group->getBitangents()->shrink_to_fit();

	// do child groups
	for (auto groupIt: *group->getSubGroups()) {
		shrinkToFit(groupIt.second);
	}

}

void ModelHelper::shrinkToFit(Model* model) {
	for (auto groupIt: *model->getSubGroups()) {
		shrinkToFit(groupIt.second);
	}
}
