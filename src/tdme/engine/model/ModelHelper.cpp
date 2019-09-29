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
#include <tdme/engine/model/UpVector.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/files/ProgressCallback.h>
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
using tdme::engine::model::UpVector;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::tools::shared::files::ProgressCallback;
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

void ModelHelper::prepareForIndexedRendering(Model* model)
{
	prepareForIndexedRendering(model->getSubGroups());
}

void ModelHelper::prepareForIndexedRendering(const map<string, Group*>& groups)
{
	// we need to prepare the group for indexed rendering
	for (auto it: groups) {
		Group* group = it.second;
		auto& groupVertices = group->getVertices();
		auto& groupNormals = group->getNormals();
		auto& groupTextureCoordinates = group->getTextureCoordinates();
		auto& groupTangents = group->getTangents();
		auto& groupBitangents = group->getBitangents();
		vector<int32_t> vertexMapping;
		vector<Vector3> indexedVertices;
		vector<Vector3> indexedNormals;
		vector<TextureCoordinate> indexedTextureCoordinates;
		vector<Vector3> indexedTangents;
		vector<Vector3> indexedBitangents;
		// construct indexed vertex data suitable for GL
		auto preparedIndices = 0;
		auto newFacesEntities = group->getFacesEntities();
		for (auto& newFacesEntity: newFacesEntities) {
			auto newFaces = newFacesEntity.getFaces();
			for (auto& face: newFaces) {
				auto faceVertexIndices = face.getVertexIndices();
				auto faceNormalIndices = face.getNormalIndices();
				auto faceTextureIndices = face.getTextureCoordinateIndices();
				auto faceTangentIndices = face.getTangentIndices();
				auto faceBitangentIndices = face.getBitangentIndices();
				array<int32_t, 3> indexedFaceVertexIndices;
				for (int16_t idx = 0; idx < 3; idx++) {
					auto groupVertexIndex = faceVertexIndices[idx];
					auto groupNormalIndex = faceNormalIndices[idx];
					auto groupTextureCoordinateIndex = faceTextureIndices[idx];
					auto groupTangentIndex = faceTangentIndices[idx];
					auto groupBitangentIndex = faceBitangentIndices[idx];
					auto vertex = &groupVertices[groupVertexIndex];
					auto normal = &groupNormals[groupNormalIndex];
					auto textureCoordinate = groupTextureCoordinates.size() > 0 ? &groupTextureCoordinates[groupTextureCoordinateIndex] : static_cast< TextureCoordinate* >(nullptr);
					auto tangent = groupTangents.size() > 0 ? &groupTangents[groupTangentIndex] : static_cast< Vector3* >(nullptr);
					auto bitangent = groupBitangents.size() > 0 ? &groupBitangents[groupBitangentIndex] : static_cast< Vector3* >(nullptr);
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
			newFacesEntity.setFaces(newFaces);
		}
		group->setFacesEntities(newFacesEntities);
		// remap skinning
		auto skinning = group->getSkinning();
		if (skinning != nullptr) {
			prepareForIndexedRendering(skinning, vertexMapping, preparedIndices);
		}
		group->setVertices(indexedVertices);
		group->setNormals(indexedNormals);
		if (groupTextureCoordinates.size() > 0) {
			group->setTextureCoordinates(indexedTextureCoordinates);
		}
		group->setTangents(indexedTangents);
		group->setBitangents(indexedBitangents);
		// process sub groups
		prepareForIndexedRendering(group->getSubGroups());
	}
}

void ModelHelper::prepareForIndexedRendering(Skinning* skinning, const vector<int32_t>& vertexMapping, int32_t vertices)
{
	auto& originalVerticesJointsWeights = skinning->getVerticesJointsWeights();
	vector<vector<JointWeight>> verticesJointsWeights;
	verticesJointsWeights.resize(vertices);
	for (auto i = 0; i < vertices; i++) {
		auto vertexOriginalMappedToIdx = vertexMapping[i];
		verticesJointsWeights[i].resize(originalVerticesJointsWeights[vertexOriginalMappedToIdx].size());
		for (auto j = 0; j < verticesJointsWeights[i].size(); j++) {
			verticesJointsWeights[i][j] = originalVerticesJointsWeights[vertexOriginalMappedToIdx][j];
		}
	}
	skinning->setVerticesJointsWeights(verticesJointsWeights);
}

void ModelHelper::setDiffuseMaskedTransparency(Model* model, bool maskedTransparency) {
	auto materials = model->getMaterials();
	for (auto it = materials.begin(); it != materials.end(); ++it) {
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
	for (auto it: model->getSubGroups()) {
		Group* group = it.second;
		auto skinning = group->getSkinning();
		// do we have a skinning
		if (skinning != nullptr) {
			// yep
			for (auto& joint : skinning->getJoints()) {
				auto jointGroupIt = groups.find(joint.getGroupId());
				if (jointGroupIt != groups.end()) {
					setJoint(jointGroupIt->second);
				}
			}
		}
	}
}

void ModelHelper::setJoint(Group* root)
{
	root->setJoint(true);
	for (auto it: root->getSubGroups()) {
		Group* group = it.second;
		setJoint(group);
	}
}

void ModelHelper::fixAnimationLength(Model* model)
{
	// fix animation length
	auto defaultAnimation = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);
	if (defaultAnimation != nullptr) {
		for (auto it: model->getSubGroups()) {
			Group* group = it.second;
			fixAnimationLength(group, defaultAnimation->getFrames());
		}
	}
}

void ModelHelper::fixAnimationLength(Group* root, int32_t frames)
{
	auto animation = root->getAnimation();
	if (animation != nullptr) {
		vector<Matrix4x4> newTransformationsMatrices;
		auto oldTransformationsMatrices = root->getAnimation()->getTransformationsMatrices();
		animation = root->createAnimation();
		newTransformationsMatrices.resize(frames);
		for (auto i = 0; i < frames; i++) {
			if (i < oldTransformationsMatrices.size()) {
				newTransformationsMatrices[i] = oldTransformationsMatrices[i];
			} else {
				newTransformationsMatrices[i].identity();
			}
		}
		animation->setTransformationsMatrices(newTransformationsMatrices);
	}
	for (auto it: root->getSubGroups()) {
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

Material* ModelHelper::cloneMaterial(const Material* material) {
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
	clonedGroup->setVertices(sourceGroup->getVertices());
	clonedGroup->setNormals(sourceGroup->getNormals());
	clonedGroup->setTextureCoordinates(sourceGroup->getTextureCoordinates());
	clonedGroup->setTangents(sourceGroup->getTangents());
	clonedGroup->setBitangents(sourceGroup->getBitangents());
	auto facesEntities = clonedGroup->getFacesEntities();
	clonedGroup->setJoint(false);
	clonedGroup->setTransformationsMatrix(sourceGroup->getTransformationsMatrix());
	for (auto& facesEntity: facesEntities) {
		if (facesEntity.getMaterial() == nullptr) continue;
		Material* material = nullptr;
		auto materialIt = targetModel->getMaterials().find(facesEntity.getMaterial()->getId());
		if (materialIt == targetModel->getMaterials().end()) {
			material = cloneMaterial(facesEntity.getMaterial());
			targetModel->getMaterials()[material->getId()] = material;
		} else {
			material = materialIt->second;
		}
		facesEntity.setMaterial(material);
	}
	clonedGroup->setFacesEntities(facesEntities);
	targetModel->getGroups()[clonedGroup->getId()] = clonedGroup;
	if (targetParentGroup == nullptr) {
		targetModel->getSubGroups()[clonedGroup->getId()] = clonedGroup;
	} else {
		targetParentGroup->getSubGroups()[clonedGroup->getId()] = clonedGroup;
	}
	for (auto sourceSubGroupIt: sourceGroup->getSubGroups()) {
		auto subGroup = sourceSubGroupIt.second;
		cloneGroup(subGroup, targetModel, clonedGroup);
	}
}

void ModelHelper::partitionGroup(Group* sourceGroup, map<string, Model*>& modelsByPartition, map<string, Vector3>& modelsPosition, const Matrix4x4& parentTransformationsMatrix) {
	// TODO: performance: faces handling is very suboptimal currently, however this is only executed in LevelEditor if doing partitioning
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

	//
	map<string, Group*> partitionModelGroups;

	// partition model group vertices and such
	map<string, vector<Vector3>> partitionModelGroupsVertices;
	map<string, vector<Vector3>> partitionModelGroupsNormals;
	map<string, vector<TextureCoordinate>> partitionModelGroupsTextureCoordinates;
	map<string, vector<Vector3>> partitionModelGroupsTangents;
	map<string, vector<Vector3>> partitionModelGroupsBitangents;
	map<string, vector<FacesEntity>> partitionModelGroupsFacesEntities;

	for (auto& facesEntity: sourceGroup->getFacesEntities()) {
		bool haveTextureCoordinates = facesEntity.isTextureCoordinatesAvailable();
		bool haveTangentsBitangents = facesEntity.isTangentBitangentAvailable();
		for (auto& face: facesEntity.getFaces()) {
			// get face vertices and such
			auto& vertexIndices = face.getVertexIndices();
			auto& normalIndices = face.getNormalIndices();
			auto& textureCoordinatesIndices = face.getTextureCoordinateIndices();
			auto& tangentIndices = face.getTangentIndices();
			auto& bitangentIndices = face.getBitangentIndices();
			vertex0.set(sourceGroup->getVertices()[vertexIndices[0]]);
			vertex1.set(sourceGroup->getVertices()[vertexIndices[1]]);
			vertex2.set(sourceGroup->getVertices()[vertexIndices[2]]);
			normal0.set(sourceGroup->getNormals()[normalIndices[0]]);
			normal1.set(sourceGroup->getNormals()[normalIndices[1]]);
			normal2.set(sourceGroup->getNormals()[normalIndices[2]]);
			if (haveTextureCoordinates == true) {
				textureCoordinate0.set(sourceGroup->getTextureCoordinates()[textureCoordinatesIndices[0]]);
				textureCoordinate1.set(sourceGroup->getTextureCoordinates()[textureCoordinatesIndices[1]]);
				textureCoordinate2.set(sourceGroup->getTextureCoordinates()[textureCoordinatesIndices[2]]);
			}
			if (haveTangentsBitangents == true) {
				tangent0.set(sourceGroup->getTangents()[tangentIndices[0]]);
				tangent1.set(sourceGroup->getTangents()[tangentIndices[1]]);
				tangent2.set(sourceGroup->getTangents()[tangentIndices[2]]);
				bitangent0.set(sourceGroup->getBitangents()[bitangentIndices[0]]);
				bitangent1.set(sourceGroup->getBitangents()[bitangentIndices[1]]);
				bitangent2.set(sourceGroup->getBitangents()[bitangentIndices[2]]);
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
			auto partitionModelGroup = partitionModelGroups[partitionModelKey];
			partitionModelGroup = partitionModel->getGroupById(sourceGroup->getId());
			if (partitionModelGroup == nullptr) {
				// TODO: create sub groups if they do not yet exist
				partitionModelGroup = new Group(
					partitionModel,
					sourceGroup->getParentGroup() == nullptr?nullptr:partitionModel->getGroupById(sourceGroup->getParentGroup()->getId()),
					sourceGroup->getId(),
					sourceGroup->getName()
				);
				partitionModelGroup->setTransformationsMatrix(sourceGroup->getTransformationsMatrix());
				if (sourceGroup->getParentGroup() == nullptr) {
					partitionModel->getSubGroups()[partitionModelGroup->getId()] = partitionModelGroup;
				} else {
					partitionModelGroup->getParentGroup()->getSubGroups()[partitionModelGroup->getId()] = partitionModelGroup;
				}
				partitionModel->getGroups()[partitionModelGroup->getId()] = partitionModelGroup;
				partitionModelGroups[partitionModelKey] = partitionModelGroup;
			}

			// get faces entity
			FacesEntity* partitionModelGroupFacesEntity = nullptr;
			for (auto& partitionModelGroupFacesEntityExisting: partitionModelGroupsFacesEntities[partitionModelKey]) {
				if (partitionModelGroupFacesEntityExisting.getId() == facesEntity.getId()) {
					partitionModelGroupFacesEntity = &partitionModelGroupFacesEntityExisting;
				}
			}
			if (partitionModelGroupFacesEntity == nullptr) {
				auto newFacesEntity = FacesEntity(
					partitionModelGroup,
					facesEntity.getId()
				);
				partitionModelGroupsFacesEntities[partitionModelKey].push_back(newFacesEntity);
				partitionModelGroupFacesEntity = &newFacesEntity;
				auto partitionModelGroupFacesEntityMaterial = partitionModel->getMaterials()[facesEntity.getMaterial()->getId()];
				if (partitionModelGroupFacesEntityMaterial == nullptr) {
					partitionModelGroupFacesEntityMaterial = cloneMaterial(facesEntity.getMaterial());
					partitionModel->getMaterials()[facesEntity.getMaterial()->getId()] = partitionModelGroupFacesEntityMaterial;
				}
				partitionModelGroupFacesEntity->setMaterial(partitionModelGroupFacesEntityMaterial);
			}

			auto faces = partitionModelGroupFacesEntity->getFaces();

			// add vertices and such
			auto verticesIdx = partitionModelGroupsVertices[partitionModelKey].size();
			partitionModelGroupsVertices[partitionModelKey].push_back(vertex0);
			partitionModelGroupsVertices[partitionModelKey].push_back(vertex1);
			partitionModelGroupsVertices[partitionModelKey].push_back(vertex2);
			partitionModelGroupsNormals[partitionModelKey].push_back(normal0);
			partitionModelGroupsNormals[partitionModelKey].push_back(normal1);
			partitionModelGroupsNormals[partitionModelKey].push_back(normal2);
			if (haveTextureCoordinates == true) {
				partitionModelGroupsTextureCoordinates[partitionModelKey].push_back(textureCoordinate0);
				partitionModelGroupsTextureCoordinates[partitionModelKey].push_back(textureCoordinate1);
				partitionModelGroupsTextureCoordinates[partitionModelKey].push_back(textureCoordinate2);
			}
			if (haveTangentsBitangents == true) {
				partitionModelGroupsTangents[partitionModelKey].push_back(tangent0);
				partitionModelGroupsTangents[partitionModelKey].push_back(tangent1);
				partitionModelGroupsTangents[partitionModelKey].push_back(tangent2);
				partitionModelGroupsBitangents[partitionModelKey].push_back(bitangent0);
				partitionModelGroupsBitangents[partitionModelKey].push_back(bitangent1);
				partitionModelGroupsBitangents[partitionModelKey].push_back(bitangent2);
			}
			Face newFace =
				Face(
					partitionModelGroup,
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2,
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2
				);
			if (haveTextureCoordinates == true) {
				newFace.setTextureCoordinateIndices(
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2
				);
			}
			if (haveTangentsBitangents == true) {
				newFace.setTangentIndices(
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2
				);
				newFace.setBitangentIndices(
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2
				);
			}
			faces.push_back(newFace);
			partitionModelGroupFacesEntity->setFaces(faces);
		}
	}

	// set vertices and such
	for (auto it: modelsByPartition) {
		auto partitionModelKey = it.first;
		if (partitionModelGroups[partitionModelKey] == nullptr) continue;
		partitionModelGroups[partitionModelKey]->setVertices(partitionModelGroupsVertices[partitionModelKey]);
		partitionModelGroups[partitionModelKey]->setNormals(partitionModelGroupsNormals[partitionModelKey]);
		partitionModelGroups[partitionModelKey]->setTextureCoordinates(partitionModelGroupsTextureCoordinates[partitionModelKey]);
		partitionModelGroups[partitionModelKey]->setTangents(partitionModelGroupsTangents[partitionModelKey]);
		partitionModelGroups[partitionModelKey]->setBitangents(partitionModelGroupsBitangents[partitionModelKey]);
		partitionModelGroups[partitionModelKey]->setFacesEntities(partitionModelGroupsFacesEntities[partitionModelKey]);
	}

	for (auto groupIt: sourceGroup->getSubGroups()) {
		partitionGroup(groupIt.second, modelsByPartition, modelsPosition, transformationsMatrix);
	}
}

void ModelHelper::partition(Model* model, const Transformations& transformations, map<string, Model*>& modelsByPartition, map<string, Vector3>& modelsPosition) {
	Matrix4x4 transformationsMatrix;
	transformationsMatrix.set(model->getImportTransformationsMatrix());
	transformationsMatrix.multiply(transformations.getTransformationsMatrix());
	for (auto groupIt: model->getSubGroups()) {
		partitionGroup(groupIt.second, modelsByPartition, modelsPosition, transformationsMatrix);
	}
	for (auto modelsByPartitionIt: modelsByPartition) {
		auto partitionKey = modelsByPartitionIt.first;
		auto partitionModel = modelsByPartitionIt.second;
		partitionModel->setImportTransformationsMatrix(model->getImportTransformationsMatrix());
		ModelHelper::createDefaultAnimation(partitionModel, 0);
		ModelHelper::setupJoints(partitionModel);
		ModelHelper::fixAnimationLength(partitionModel);
		ModelHelper::prepareForIndexedRendering(partitionModel);
	}
}

void ModelHelper::shrinkToFit(Group* group) {
	// TODO: a.drewke
	/*
	for (auto& facesEntity: group->getFacesEntities()) {
		facesEntity.getFaces().shrink_to_fit();
	}

	group->getFacesEntities().shrink_to_fit();
	group->getVertices().shrink_to_fit();
	group->getNormals().shrink_to_fit();
	group->getTextureCoordinates().shrink_to_fit();
	group->getTangents().shrink_to_fit();
	group->getBitangents().shrink_to_fit();

	// do child groups
	for (auto groupIt: group->getSubGroups()) {
		shrinkToFit(groupIt.second);
	}
	*/
}

void ModelHelper::shrinkToFit(Model* model) {
	for (auto groupIt: model->getSubGroups()) {
		shrinkToFit(groupIt.second);
	}
}

float ModelHelper::computeNormals(Group* group, ProgressCallback* progressCallback, float incrementPerFace, float progress) {
	group->setNormals(vector<Vector3>());
	array<Vector3, 3> vertices;
	Vector3 normal;
	auto facesEntityProcessed = 0;
	vector<Vector3> normals;
	auto facesEntities = group->getFacesEntities();
	for (auto& facesEntity: facesEntities) {
		auto faces = facesEntity.getFaces();
		for (auto& face: faces) {
			for (auto i = 0; i < vertices.size(); i++) {
				vertices[i] = group->getVertices()[face.getVertexIndices()[i]];
			}
			computeNormal(vertices, normal);
			face.setNormalIndices(normals.size(), normals.size() + 1, normals.size() + 2);
			normals.push_back(normal);
			normals.push_back(normal);
			normals.push_back(normal);
			if (progressCallback != nullptr) {
				progress+= incrementPerFace / 2.0f;
				if (facesEntityProcessed == 0 || facesEntityProcessed % 1000 == 0) progressCallback->progress(progress);
				facesEntityProcessed++;
			}
		}
		facesEntity.setFaces(faces);
	}
	group->setFacesEntities(facesEntities);
	facesEntityProcessed = 0;
	for (auto& facesEntity: group->getFacesEntities()) {
		for (auto& face: facesEntity.getFaces()) {
			for (auto i = 0; i < vertices.size(); i++) {
				if (interpolateNormal(group, group->getVertices()[face.getVertexIndices()[i]], normals, normal) == true) {
					normals[face.getNormalIndices()[i]].set(normal);
				}
			}
			if (progressCallback != nullptr) {
				progress+= incrementPerFace / 2.0f;
				if (facesEntityProcessed == 0 || facesEntityProcessed % 1000 == 0) progressCallback->progress(progress);
				facesEntityProcessed++;
			}
		}
	}
	group->setNormals(normals);
	for (auto subGroupIt: group->getSubGroups()) {
		progress = computeNormals(subGroupIt.second, progressCallback, incrementPerFace, progress);
	}
	return progress;
}

void ModelHelper::computeNormals(Model* model, ProgressCallback* progressCallback) {
	auto faceCount = 0;
	for (auto groupIt: model->getSubGroups()) {
		faceCount+= determineFaceCount(groupIt.second);
	}
	for (auto groupIt: model->getSubGroups()) {
		computeNormals(groupIt.second, progressCallback, 1.0f / static_cast<float>(faceCount), 0.0f);
	}
	prepareForIndexedRendering(model);
	if (progressCallback != nullptr) {
		progressCallback->progress(1.0f);
		delete progressCallback;
	}
}

int ModelHelper::determineFaceCount(Group* group) {
	auto faceCount = 0;
	faceCount+= group->getFaceCount();
	for (auto subGroupIt: group->getSubGroups()) {
		faceCount+= determineFaceCount(subGroupIt.second);
	}
	return faceCount;
}

void ModelHelper::prepareForShader(Model* model, const string& shader) {
	if (shader == "foliage") {
		for (auto groupIt: model->getSubGroups()) prepareForFoliageShader(groupIt.second);
		if (model->getUpVector() == UpVector::Z_UP) {
			Console::println("ModelHelper::prepareForShader(): " + model->getName() + ": fixing Z-Up to Y-Up");
			Matrix4x4 z2yUpMatrix;
			z2yUpMatrix.identity().rotate(-90.0f, Vector3(1.0f, 0.0f, 0.0f));
			model->setImportTransformationsMatrix(model->getImportTransformationsMatrix().clone().multiply(z2yUpMatrix));
			model->setUpVector(UpVector::Y_UP);
		}
	} else {
		for (auto groupIt: model->getSubGroups()) prepareForDefaultShader(groupIt.second);
	}
}

void ModelHelper::prepareForDefaultShader(Group* group) {
	vector<Vector3> objectOrigins;
	group->setOrigins(objectOrigins);
	for (auto groupIt: group->getSubGroups()) {
		prepareForFoliageShader(groupIt.second);
	}
}

void ModelHelper::prepareForFoliageShader(Group* group) {
	vector<Vector3> objectOrigins;
	objectOrigins.resize(group->getVertices().size());
	group->setOrigins(objectOrigins);
	if (group->getModel()->getUpVector() == UpVector::Z_UP) {
		if (group->getAnimation() != nullptr) Console::println("ModelHelper::prepareForFoliageShader(): animation available, this is not yet supported!");
		if (group->getSkinning() != nullptr) Console::println("ModelHelper::prepareForFoliageShader(): skinning available, this is not yet supported!");
		{
			auto vertices = group->getVertices();
			for (auto& vertex: vertices) {
				auto tmp = vertex.getY();
				vertex.setY(-vertex.getZ());
				vertex.setZ(tmp);
			}
			group->setVertices(vertices);
		}
		{
			auto normals = group->getNormals();
			for (auto& normal: normals) {
				auto tmp = normal.getY();
				normal.setY(-normal.getZ());
				normal.setZ(tmp);
			}
			group->setNormals(normals);
		}
		{
			auto tangents = group->getTangents();
			for (auto& tangent: tangents) {
				auto tmp = tangent.getY();
				tangent.setY(-tangent.getZ());
				tangent.setZ(tmp);
			}
			group->setTangents(tangents);
		}
		{
			auto bitangents = group->getBitangents();
			for (auto& bitangent: bitangents) {
				auto tmp = bitangent.getY();
				bitangent.setY(-bitangent.getZ());
				bitangent.setZ(tmp);
			}
			group->setBitangents(bitangents);
		}
	}
	for (auto groupIt: group->getSubGroups()) {
		prepareForFoliageShader(groupIt.second);
	}
}
