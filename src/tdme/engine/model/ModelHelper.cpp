#include <tdme/engine/model/ModelHelper.h>

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/engine/Transformations.h>
#include <tdme/engine/fileio/textures/Texture.h>
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
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/files/ProgressCallback.h>
#include <tdme/tools/shared/model/LevelEditorObject.h>
#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/StringUtils.h>

using std::array;
using std::map;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::Transformations;
using tdme::engine::fileio::textures::Texture;
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
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::model::UpVector;
using tdme::engine::primitives::BoundingBox;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::tools::shared::files::ProgressCallback;
using tdme::tools::shared::model::LevelEditorObject;
using tdme::utils::ByteBuffer;
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
		if (material->getSpecularMaterialProperties() != nullptr &&
			material->getSpecularMaterialProperties()->hasDiffuseTextureTransparency() == true) {
			material->getSpecularMaterialProperties()->setDiffuseTextureMaskedTransparency(maskedTransparency);
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
		auto animation = new Animation();
		newTransformationsMatrices.resize(frames);
		for (auto i = 0; i < frames; i++) {
			if (i < oldTransformationsMatrices.size()) {
				newTransformationsMatrices[i] = oldTransformationsMatrices[i];
			} else {
				newTransformationsMatrices[i].identity();
			}
		}
		animation->setTransformationsMatrices(newTransformationsMatrices);
		root->setAnimation(animation);
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

Material* ModelHelper::cloneMaterial(const Material* material, const string& id) {
	auto clonedMaterial = new Material(id.empty()?material->getId():id);
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties != nullptr) {
		auto clonedSpecularMaterialProperties = new SpecularMaterialProperties();
		clonedSpecularMaterialProperties->setAmbientColor(specularMaterialProperties->getAmbientColor());
		clonedSpecularMaterialProperties->setDiffuseColor(specularMaterialProperties->getDiffuseColor());
		clonedSpecularMaterialProperties->setEmissionColor(specularMaterialProperties->getEmissionColor());
		clonedSpecularMaterialProperties->setSpecularColor(specularMaterialProperties->getSpecularColor());
		clonedSpecularMaterialProperties->setShininess(specularMaterialProperties->getShininess());
		clonedSpecularMaterialProperties->setTextureAtlasSize(specularMaterialProperties->getTextureAtlasSize());
		if (specularMaterialProperties->getDiffuseTexture() != nullptr) {
			specularMaterialProperties->getDiffuseTexture()->acquireReference();
			clonedSpecularMaterialProperties->setDiffuseTexture(specularMaterialProperties->getDiffuseTexture());
		}
		clonedSpecularMaterialProperties->setDiffuseTextureMaskedTransparency(specularMaterialProperties->hasDiffuseTextureMaskedTransparency());
		clonedSpecularMaterialProperties->setDiffuseTextureMaskedTransparencyThreshold(specularMaterialProperties->getDiffuseTextureMaskedTransparencyThreshold());
		// TODO: a.drewke: clone textures like diffuse texture
		if (specularMaterialProperties->getNormalTextureFileName().length() != 0) {
			clonedSpecularMaterialProperties->setNormalTexture(
				specularMaterialProperties->getNormalTexturePathName(),
				specularMaterialProperties->getNormalTextureFileName()
			);
		}
		if (specularMaterialProperties->getSpecularTextureFileName().length() != 0) {
			clonedSpecularMaterialProperties->setSpecularTexture(
				specularMaterialProperties->getSpecularTexturePathName(),
				specularMaterialProperties->getSpecularTextureFileName()
			);
		}
		clonedMaterial->setSpecularMaterialProperties(clonedSpecularMaterialProperties);
	}
	return clonedMaterial;
}

void ModelHelper::cloneGroup(Group* sourceGroup, Model* targetModel, Group* targetParentGroup, bool cloneMesh) {
	Console::println("ModelHelper::cloneGroup(): " + sourceGroup->getId());
	auto clonedGroup = new Group(targetModel, targetParentGroup, sourceGroup->getId(), sourceGroup->getName());
	clonedGroup->setTransformationsMatrix(sourceGroup->getTransformationsMatrix());
	clonedGroup->setJoint(sourceGroup->isJoint());
	if (cloneMesh == true) {
		clonedGroup->setVertices(sourceGroup->getVertices());
		clonedGroup->setNormals(sourceGroup->getNormals());
		clonedGroup->setTextureCoordinates(sourceGroup->getTextureCoordinates());
		clonedGroup->setTangents(sourceGroup->getTangents());
		clonedGroup->setBitangents(sourceGroup->getBitangents());
		auto facesEntities = clonedGroup->getFacesEntities();
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
	}
	if (sourceGroup->getAnimation() != nullptr) {
		auto clonedAnimation = new Animation();
		clonedAnimation->setTransformationsMatrices(sourceGroup->getAnimation()->getTransformationsMatrices());
		clonedGroup->setAnimation(clonedAnimation);
	}
	targetModel->getGroups()[clonedGroup->getId()] = clonedGroup;
	if (targetParentGroup == nullptr) {
		targetModel->getSubGroups()[clonedGroup->getId()] = clonedGroup;
	} else {
		targetParentGroup->getSubGroups()[clonedGroup->getId()] = clonedGroup;
	}
	for (auto sourceSubGroupIt: sourceGroup->getSubGroups()) {
		auto subGroup = sourceSubGroupIt.second;
		cloneGroup(subGroup, targetModel, clonedGroup, cloneMesh);
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
			auto partitionX = (int)(minX / 64.0f);
			auto partitionY = (int)(minY / 64.0f);
			auto partitionZ = (int)(minZ / 64.0f);

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
	if (shader == "foliage" || shader == "tree") {
		for (auto groupIt: model->getSubGroups()) prepareForFoliageTreeShader(groupIt.second, model->getImportTransformationsMatrix(), shader);
		model->setImportTransformationsMatrix(Matrix4x4().identity());
		model->setUpVector(UpVector::Y_UP);
	} else {
		for (auto groupIt: model->getSubGroups()) prepareForDefaultShader(groupIt.second);
	}
}

void ModelHelper::prepareForDefaultShader(Group* group) {
	vector<Vector3> objectOrigins;
	group->setOrigins(objectOrigins);
	for (auto groupIt: group->getSubGroups()) {
		prepareForDefaultShader(groupIt.second);
	}
}

void ModelHelper::prepareForFoliageTreeShader(Group* group, const Matrix4x4& parentTransformationsMatrix, const string& shader) {
	vector<Vector3> objectOrigins;
	objectOrigins.resize(group->getVertices().size());
	Console::println("ModelHelper::prepareForShader(): " + group->getModel()->getName() + ": " + group->getId() + ": applying import and group matrices");
	if (group->getAnimation() != nullptr) Console::println("ModelHelper::prepareForFoliageShader(): animation available, this is not yet supported!");
	if (group->getSkinning() != nullptr) Console::println("ModelHelper::prepareForFoliageShader(): skinning available, this is not yet supported!");
	auto transformationsMatrix = group->getTransformationsMatrix().clone().multiply(parentTransformationsMatrix);
	{
		auto vertices = group->getVertices();
		auto vertexIdx = 0;
		for (auto& vertex: vertices) {
			transformationsMatrix.multiply(vertex, vertex);
			if (shader == "tree") objectOrigins[vertexIdx].set(0.0f, vertex.getY(), 0.0f);
			vertexIdx++;
		}
		group->setVertices(vertices);
	}
	{
		auto normals = group->getNormals();
		for (auto& normal: normals) {
			transformationsMatrix.multiplyNoTranslation(normal, normal);
			normal.normalize();
		}
		group->setNormals(normals);
	}
	{
		auto tangents = group->getTangents();
		for (auto& tangent: tangents) {
			transformationsMatrix.multiplyNoTranslation(tangent, tangent);
			tangent.normalize();
		}
		group->setTangents(tangents);
	}
	{
		auto bitangents = group->getBitangents();
		for (auto& bitangent: bitangents) {
			transformationsMatrix.multiplyNoTranslation(bitangent, bitangent);
			bitangent.normalize();
		}
		group->setBitangents(bitangents);
	}
	group->setTransformationsMatrix(Matrix4x4().identity());
	group->setOrigins(objectOrigins);
	for (auto groupIt: group->getSubGroups()) {
		prepareForFoliageTreeShader(groupIt.second, transformationsMatrix, shader);
	}
}

void ModelHelper::checkForOptimization(Group* group, map<string, int>& materialUseCount) {
	// skip on joints as they do not have textures to display and no vertex data
	if (group->isJoint() == true) return;

	// track material usage
	for (auto& facesEntity: group->getFacesEntities()) {
		if (facesEntity.getMaterial() == nullptr) continue;
		materialUseCount[facesEntity.getMaterial()->getId()]++;
	}

	// do not transform skinning vertices and such
	if (group->getSkinning() != nullptr) return;

	//
	for (auto groupIt: group->getSubGroups()) {
		checkForOptimization(groupIt.second, materialUseCount);
	}
}

void ModelHelper::prepareForOptimization(Group* group, const Matrix4x4& parentTransformationsMatrix) {
	// skip on joints as they do not have textures to display and no vertex data
	if (group->isJoint() == true) return;

	// do not transform skinning vertices and such
	if (group->getSkinning() != nullptr) return;

	// static group, apply group transformations matrix
	auto transformationsMatrix = group->getTransformationsMatrix().clone().multiply(parentTransformationsMatrix);
	{
		auto vertices = group->getVertices();
		for (auto& vertex: vertices) {
			transformationsMatrix.multiply(vertex, vertex);
		}
		group->setVertices(vertices);
	}
	{
		auto normals = group->getNormals();
		for (auto& normal: normals) {
			transformationsMatrix.multiplyNoTranslation(normal, normal);
			normal.normalize();
		}
		group->setNormals(normals);
	}
	{
		auto tangents = group->getTangents();
		for (auto& tangent: tangents) {
			transformationsMatrix.multiplyNoTranslation(tangent, tangent);
			tangent.normalize();
		}
		group->setTangents(tangents);
	}
	{
		auto bitangents = group->getBitangents();
		for (auto& bitangent: bitangents) {
			transformationsMatrix.multiplyNoTranslation(bitangent, bitangent);
			bitangent.normalize();
		}
		group->setBitangents(bitangents);
	}

	// we do not set group transformations matrix as we need it later
	// group->setTransformationsMatrix(Matrix4x4().identity());

	//
	for (auto groupIt: group->getSubGroups()) {
		prepareForOptimization(groupIt.second, transformationsMatrix);
	}
}

void ModelHelper::optimizeGroup(Group* sourceGroup, Model* targetModel, int diffuseTextureAtlasSize, const map<string, int>& diffuseTextureAtlasIndices) {
	Console::println("ModelHelper::optimizeGroup(): " + sourceGroup->getId());
	if (sourceGroup->getFacesEntities().size() > 0) {
		auto& sourceVertices = sourceGroup->getVertices();
		auto& sourceNormals = sourceGroup->getNormals();
		auto& sourceTangents = sourceGroup->getTangents();
		auto& sourceBitangents = sourceGroup->getBitangents();
		auto& sourceTextureCoordinates = sourceGroup->getTextureCoordinates();
		auto targetGroup = targetModel->getGroups()["group.optimized"];
		auto targetVertices = targetGroup->getVertices();
		auto targetNormals = targetGroup->getNormals();
		auto targetTangents = targetGroup->getTangents();
		auto targetBitangents = targetGroup->getBitangents();
		auto targetTextureCoordinates = targetGroup->getTextureCoordinates();
		auto targetOffset = targetVertices.size();
		auto targetTextureCoordinatesOffset = targetTextureCoordinates.size();
		for (auto& v: sourceVertices) targetVertices.push_back(v);
		for (auto& v: sourceNormals) targetNormals.push_back(v);
		for (auto& v: sourceTangents) targetTangents.push_back(v);
		for (auto& v: sourceBitangents) targetBitangents.push_back(v);
		targetGroup->setVertices(targetVertices);
		targetGroup->setNormals(targetNormals);
		targetGroup->setTangents(targetTangents);
		targetGroup->setBitangents(targetBitangents);
		auto targetFacesEntities = targetGroup->getFacesEntities();
		FacesEntity* tmpFacesEntity = nullptr;
		auto targetFaces = (tmpFacesEntity = targetGroup->getFacesEntity("facesentity.optimized")) != nullptr?tmpFacesEntity->getFaces():vector<Face>();
		auto targetFacesMaskedTransparency = (tmpFacesEntity = targetGroup->getFacesEntity("facesentity.optimized.maskedtransparency")) != nullptr?tmpFacesEntity->getFaces():vector<Face>();
		auto targetFacesTransparency = (tmpFacesEntity = targetGroup->getFacesEntity("facesentity.optimized.transparency")) != nullptr?tmpFacesEntity->getFaces():vector<Face>();
		for (auto& facesEntity: sourceGroup->getFacesEntities()) {
			auto material = facesEntity.getMaterial();
			auto diffuseTextureAtlasIndex = diffuseTextureAtlasIndices.find(material->getId())->second;
			auto textureXOffset = diffuseTextureAtlasSize == 0?0.0f:static_cast<float>(diffuseTextureAtlasIndex % diffuseTextureAtlasSize) * 1000.0f + 500.0f;
			auto textureYOffset = diffuseTextureAtlasSize == 0?0.0f:static_cast<float>(diffuseTextureAtlasIndex / diffuseTextureAtlasSize) * 1000.0f + 500.0f;
			auto textureXScale = diffuseTextureAtlasSize == 0?1.0f:1.0f;
			auto textureYScale = diffuseTextureAtlasSize == 0?1.0f:1.0f;
			for (auto& face: facesEntity.getFaces()) {
				auto sourceVertexIndices = face.getVertexIndices();
				auto sourceNormalIndices = face.getNormalIndices();
				auto sourceTangentIndices = face.getTangentIndices();
				auto sourceBitangentIndices = face.getBitangentIndices();
				auto sourceTextureCoordinateIndices = face.getTextureCoordinateIndices();
				{
					auto textureCoordinateArray = sourceTextureCoordinateIndices[0] == -1 || sourceTextureCoordinates.size() == 0?array<float, 2>():sourceTextureCoordinates[sourceTextureCoordinateIndices[0]].getArray();
					textureCoordinateArray[0]*= textureXScale;
					textureCoordinateArray[0]+= textureXOffset;
					textureCoordinateArray[1]*= textureYScale;
					textureCoordinateArray[1]+= textureYOffset;
					targetTextureCoordinates.push_back(TextureCoordinate(textureCoordinateArray));
				}
				{
					auto textureCoordinateArray = sourceTextureCoordinateIndices[1] == -1 || sourceTextureCoordinates.size() == 0?array<float, 2>():sourceTextureCoordinates[sourceTextureCoordinateIndices[1]].getArray();
					textureCoordinateArray[0]*= textureXScale;
					textureCoordinateArray[0]+= textureXOffset;
					textureCoordinateArray[1]*= textureYScale;
					textureCoordinateArray[1]+= textureYOffset;
					targetTextureCoordinates.push_back(TextureCoordinate(textureCoordinateArray));
				}
				{
					auto textureCoordinateArray = sourceTextureCoordinateIndices[2] == -1 || sourceTextureCoordinates.size() == 0?array<float, 2>():sourceTextureCoordinates[sourceTextureCoordinateIndices[2]].getArray();
					textureCoordinateArray[0]*= textureXScale;
					textureCoordinateArray[0]+= textureXOffset;
					textureCoordinateArray[1]*= textureYScale;
					textureCoordinateArray[1]+= textureYOffset;
					targetTextureCoordinates.push_back(TextureCoordinate(textureCoordinateArray));
				}
				if (material->getSpecularMaterialProperties()->hasDiffuseTextureTransparency() == true) {
					if (material->getSpecularMaterialProperties()->hasDiffuseTextureMaskedTransparency() == true) {
						targetFacesMaskedTransparency.push_back(
							Face(
								targetGroup,
								sourceVertexIndices[0] + targetOffset,
								sourceVertexIndices[1] + targetOffset,
								sourceVertexIndices[2] + targetOffset,
								sourceNormalIndices[0] + targetOffset,
								sourceNormalIndices[1] + targetOffset,
								sourceNormalIndices[2] + targetOffset,
								targetTextureCoordinatesOffset + 0,
								targetTextureCoordinatesOffset + 1,
								targetTextureCoordinatesOffset + 2
							)
						);
					} else {
						targetFacesTransparency.push_back(
							Face(
								targetGroup,
								sourceVertexIndices[0] + targetOffset,
								sourceVertexIndices[1] + targetOffset,
								sourceVertexIndices[2] + targetOffset,
								sourceNormalIndices[0] + targetOffset,
								sourceNormalIndices[1] + targetOffset,
								sourceNormalIndices[2] + targetOffset,
								targetTextureCoordinatesOffset + 0,
								targetTextureCoordinatesOffset + 1,
								targetTextureCoordinatesOffset + 2
							)
						);
					}
				} else {
					targetFaces.push_back(
						Face(
							targetGroup,
							sourceVertexIndices[0] + targetOffset,
							sourceVertexIndices[1] + targetOffset,
							sourceVertexIndices[2] + targetOffset,
							sourceNormalIndices[0] + targetOffset,
							sourceNormalIndices[1] + targetOffset,
							sourceNormalIndices[2] + targetOffset,
							targetTextureCoordinatesOffset + 0,
							targetTextureCoordinatesOffset + 1,
							targetTextureCoordinatesOffset + 2
						)
					);
				}
				targetTextureCoordinatesOffset+= 3;
			}
		}
		targetGroup->setTextureCoordinates(targetTextureCoordinates);
		Console::println(targetModel->getId() + ": a: " + to_string(targetFaces.size()));
		Console::println(targetModel->getId() + ": b: " + to_string(targetFacesMaskedTransparency.size()));
		Console::println(targetModel->getId() + ": c: " + to_string(targetFacesTransparency.size()));
		if (targetFaces.size() > 0) {
			auto facesEntity = targetGroup->getFacesEntity("facesentity.optimized");
			if (targetGroup->getFacesEntity("facesentity.optimized") == nullptr) {
				targetFacesEntities.push_back(FacesEntity(targetGroup, "facesentity.optimized"));
				facesEntity = &targetFacesEntities[targetFacesEntities.size() - 1];
			}
			facesEntity->setFaces(targetFaces);
		}
		if (targetFacesMaskedTransparency.size() > 0) {
			auto facesEntity = targetGroup->getFacesEntity("facesentity.optimized.maskedtransparency");
			if (targetGroup->getFacesEntity("facesentity.optimized.maskedtransparency") == nullptr) {
				targetFacesEntities.push_back(FacesEntity(targetGroup, "facesentity.optimized.maskedtransparency"));
				facesEntity = &targetFacesEntities[targetFacesEntities.size() - 1];
			}
			facesEntity->setFaces(targetFacesMaskedTransparency);
		}
		if (targetFacesTransparency.size() > 0) {
			auto facesEntity = targetGroup->getFacesEntity("facesentity.optimized.transparency");
			if (targetGroup->getFacesEntity("facesentity.optimized.transparency") == nullptr) {
				targetFacesEntities.push_back(FacesEntity(targetGroup, "facesentity.optimized.transparency"));
				facesEntity = &targetFacesEntities[targetFacesEntities.size() - 1];
			}
			facesEntity->setFaces(targetFacesMaskedTransparency);
		}
		targetGroup->setFacesEntities(targetFacesEntities);
	}
	for (auto& subGroupIt: sourceGroup->getSubGroups()) {
		optimizeGroup(subGroupIt.second, targetModel, diffuseTextureAtlasSize, diffuseTextureAtlasIndices);
	}
}

Texture* ModelHelper::createAtlasTexture(map<int, Texture*>& textureAtlasTextures) {
	// create atlas
	// TODO: looks like we need 2 groups, damn: one with masked transparency and one without for models that have both :(
	int textureAtlasSize = static_cast<int>(Math::ceil(sqrt(textureAtlasTextures.size())));
	Console::println("\tTexture atlas size: " + to_string(textureAtlasSize) + " x " + to_string(textureAtlasSize));
	Texture* atlasTexture = nullptr;
	static auto globalAtlasTextureIdx = 0;
	#define ATLAS_TEXTURE_SIZE	512
	auto textureWidth = textureAtlasSize * ATLAS_TEXTURE_SIZE;
	auto textureHeight = textureAtlasSize * ATLAS_TEXTURE_SIZE;
	auto textureByteBuffer = ByteBuffer::allocate(textureWidth * textureHeight * 4);
	for (auto y = 0; y < textureHeight; y++)
	for (auto x = 0; x < textureWidth; x++) {
		auto atlasTextureIdxX = x / ATLAS_TEXTURE_SIZE;
		auto atlasTextureIdxY = y / ATLAS_TEXTURE_SIZE;
		auto materialTextureX = x - (atlasTextureIdxX * ATLAS_TEXTURE_SIZE);
		auto materialTextureY = y - (atlasTextureIdxY * ATLAS_TEXTURE_SIZE);
		auto materialTextureXFloat = static_cast<float>(materialTextureX) / static_cast<float>(ATLAS_TEXTURE_SIZE);
		auto materialTextureYFloat = static_cast<float>(materialTextureY) / static_cast<float>(ATLAS_TEXTURE_SIZE);
		auto atlasTextureIdx = atlasTextureIdxY * textureAtlasSize + atlasTextureIdxX;
		auto materialTexture = textureAtlasTextures[atlasTextureIdx];
		if (materialTexture != nullptr) {
			auto materialTextureWidth = materialTexture->getTextureWidth();
			auto materialTextureHeight = materialTexture->getTextureHeight();
			auto materialTextureBytesPerPixel = materialTexture->getDepth() / 8;
			auto materialTextureXInt = static_cast<int>(materialTextureXFloat * static_cast<float>(materialTextureWidth));
			auto materialTextureYInt = static_cast<int>(materialTextureYFloat * static_cast<float>(materialTextureHeight));
			if (materialTextureXInt < 8) materialTextureXInt = 0; else
			if (materialTextureXInt > materialTextureWidth - 8) materialTextureXInt = materialTextureWidth - 1; else
				materialTextureXInt = static_cast<int>((static_cast<float>(materialTextureXInt) - 8.0f) * (static_cast<float>(materialTextureWidth) + 16.0f) / static_cast<float>(materialTextureWidth));
			if (materialTextureYInt < 8) materialTextureYInt = 0; else
			if (materialTextureYInt > materialTextureHeight - 8) materialTextureYInt = materialTextureHeight - 1; else
				materialTextureYInt = static_cast<int>((static_cast<float>(materialTextureYInt) - 8.0f) * (static_cast<float>(materialTextureHeight) + 16.0f) / static_cast<float>(materialTextureHeight));
			auto materialTexturePixelOffset =
				materialTextureYInt * materialTextureWidth * materialTextureBytesPerPixel +
				materialTextureXInt * materialTextureBytesPerPixel;
			auto materialPixelR = materialTexture->getTextureData()->get(materialTexturePixelOffset + 0);
			auto materialPixelG = materialTexture->getTextureData()->get(materialTexturePixelOffset + 1);
			auto materialPixelB = materialTexture->getTextureData()->get(materialTexturePixelOffset + 2);
			auto materialPixelA = materialTextureBytesPerPixel == 4?materialTexture->getTextureData()->get(materialTexturePixelOffset + 3):0xff;
			textureByteBuffer->put(materialPixelR);
			textureByteBuffer->put(materialPixelG);
			textureByteBuffer->put(materialPixelB);
			textureByteBuffer->put(materialPixelA);
		} else {
			auto materialPixelR = 0xff;
			auto materialPixelG = 0x00;
			auto materialPixelB = 0x00;
			auto materialPixelA = 0xff;
			textureByteBuffer->put(materialPixelR);
			textureByteBuffer->put(materialPixelG);
			textureByteBuffer->put(materialPixelB);
			textureByteBuffer->put(materialPixelA);
		}
	}
	atlasTexture = new Texture(
		"tdme.texture.atlas." + to_string(globalAtlasTextureIdx++),
		32,
		textureWidth, textureHeight,
		textureWidth, textureHeight,
		textureByteBuffer
	);
	atlasTexture->setAtlasSize(textureAtlasSize);
	atlasTexture->acquireReference();
	return atlasTexture;
}

Model* ModelHelper::optimizeModel(Model* model) {
	Console::println(model->getName());
	Console::println("\tSource material count: " + to_string(model->getMaterials().size()));
	Console::println("\tSource group count: " + to_string(model->getGroups().size()));

	// TODO: 2 mas could have the same texture
	// prepare for optimizations
	map<string, int> materialUseCount;
	for (auto& groupIt: model->getSubGroups()) {
		checkForOptimization(
			groupIt.second,
			materialUseCount
		);
	}

	// check materials and diffuse textures
	auto diffuseTextureCount = 0;
	map<string, int> diffuseTextureAtlasIndices;
	map<int, Texture*> diffuseTextureAtlasTextures;
	map<string, Material*> atlasMaterials;
	for (auto& materialUseCountIt: materialUseCount) {
		auto material = model->getMaterials().find(materialUseCountIt.first)->second;
		Console::println("\tMaterial usage: " + materialUseCountIt.first + ": " + to_string(materialUseCountIt.second));
		Console::print("\t\tEmission: ");
		for (auto colorComponent: material->getSpecularMaterialProperties()->getEmissionColor().getArray()) {
			Console::print(to_string(colorComponent) + " ");
		}
		Console::println();
		Console::print("\t\tAmbient: ");
		for (auto colorComponent: material->getSpecularMaterialProperties()->getAmbientColor().getArray()) {
			Console::print(to_string(colorComponent) + " ");
		}
		Console::println();
		Console::print("\t\tDiffuse: ");
		for (auto colorComponent: material->getSpecularMaterialProperties()->getDiffuseColor().getArray()) {
			Console::print(to_string(colorComponent) + " ");
		}
		auto diffuseTexture = material->getSpecularMaterialProperties()->getDiffuseTexture();
		if (diffuseTexture != nullptr) {
			diffuseTextureAtlasIndices[material->getId()] = diffuseTextureCount;
			diffuseTextureAtlasTextures[diffuseTextureCount] = diffuseTexture;
			diffuseTextureCount++;
			atlasMaterials[material->getId()] = material;
		}
		Console::print("\t\tDiffuse texture: " + (diffuseTexture == nullptr?"none":to_string(diffuseTexture->getTextureWidth()) + " x " + to_string(diffuseTexture->getTextureHeight())));
		Console::println();
		Console::print("\t\tSpecular: ");
		for (auto colorComponent: material->getSpecularMaterialProperties()->getSpecularColor().getArray()) {
			Console::print(to_string(colorComponent) + " ");
		}
		Console::println();
		Console::print("\t\tShininess: ");
		Console::print(to_string(material->getSpecularMaterialProperties()->getShininess()) + " ");
		Console::println();
	}

	// do we need to optimize?
	if (diffuseTextureCount < 2) return model;

	// prepare for optimizations
	for (auto& groupIt: model->getSubGroups()) {
		prepareForOptimization(
			groupIt.second,
			Matrix4x4().identity()
		);
	}

	// create diffuse atlas texture
	auto diffuseAtlasTexture = createAtlasTexture(diffuseTextureAtlasTextures);

	// create model with optimizations applied
	auto optimizedModel = new Model(model->getId() + ".optimized", model->getName() + ".optimized", model->getUpVector(), model->getRotationOrder(), new BoundingBox(model->getBoundingBox()), model->getAuthoringTool());
	optimizedModel->setImportTransformationsMatrix(model->getImportTransformationsMatrix());
	auto optimizedGroup = new Group(optimizedModel, nullptr, "group.optimized", "group.optimized");
	optimizedModel->getGroups()["group.optimized"] = optimizedGroup;
	optimizedModel->getSubGroups()["group.optimized"] = optimizedGroup;

	// create optimized material
	auto optimizedMaterial = new Material("material.optimized");
	{
		optimizedMaterial->getSpecularMaterialProperties()->setDiffuseTexture(diffuseAtlasTexture);
		optimizedMaterial->getSpecularMaterialProperties()->setTextureAtlasSize(diffuseAtlasTexture->getAtlasSize());
		optimizedMaterial->getSpecularMaterialProperties()->setDiffuseTextureTransparency(false);
		optimizedMaterial->getSpecularMaterialProperties()->setDiffuseTextureMaskedTransparency(false);
		Vector4 optimizedMaterialEmission(0.0f, 0.0f, 0.0f, 0.0f);
		Vector4 optimizedMaterialAmbient(0.0f, 0.0f, 0.0f, 0.0f);
		Vector4 optimizedMaterialDiffuse(0.0f, 0.0f, 0.0f, 0.0f);
		Vector4 optimizedMaterialSpecular(0.0f, 0.0f, 0.0f, 0.0f);
		float optimizedMaterialShininess;
		for (auto& atlasMaterialsIt: atlasMaterials) {
			auto material = atlasMaterialsIt.second;
			optimizedMaterialEmission+= Vector4(material->getSpecularMaterialProperties()->getEmissionColor().getArray());
			optimizedMaterialAmbient+= Vector4(material->getSpecularMaterialProperties()->getAmbientColor().getArray());
			optimizedMaterialDiffuse+= Vector4(material->getSpecularMaterialProperties()->getDiffuseColor().getArray());
			optimizedMaterialSpecular+= Vector4(material->getSpecularMaterialProperties()->getSpecularColor().getArray());
			optimizedMaterialShininess+= material->getSpecularMaterialProperties()->getShininess();
		}
		optimizedMaterialEmission/= static_cast<float>(atlasMaterials.size());
		optimizedMaterialAmbient/= static_cast<float>(atlasMaterials.size());
		optimizedMaterialDiffuse/= static_cast<float>(atlasMaterials.size());
		optimizedMaterialSpecular/= static_cast<float>(atlasMaterials.size());
		optimizedMaterialShininess/= static_cast<float>(atlasMaterials.size());
		optimizedMaterial->getSpecularMaterialProperties()->setEmissionColor(Color4(optimizedMaterialEmission.getArray()));
		optimizedMaterial->getSpecularMaterialProperties()->setAmbientColor(Color4(optimizedMaterialAmbient.getArray()));
		optimizedMaterial->getSpecularMaterialProperties()->setDiffuseColor(Color4(optimizedMaterialDiffuse.getArray()));
		optimizedMaterial->getSpecularMaterialProperties()->setSpecularColor(Color4(optimizedMaterialSpecular.getArray()));
		optimizedMaterial->getSpecularMaterialProperties()->setShininess(optimizedMaterialShininess);
		Console::println("\tOptimized Material");
		Console::print("\t\tEmission: ");
		for (auto colorComponent: optimizedMaterial->getSpecularMaterialProperties()->getEmissionColor().getArray()) {
			Console::print(to_string(colorComponent) + " ");
		}
		Console::println();
		Console::print("\t\tAmbient: ");
		for (auto colorComponent: optimizedMaterial->getSpecularMaterialProperties()->getAmbientColor().getArray()) {
			Console::print(to_string(colorComponent) + " ");
		}
		Console::println();
		Console::print("\t\tDiffuse: ");
		for (auto colorComponent: optimizedMaterial->getSpecularMaterialProperties()->getDiffuseColor().getArray()) {
			Console::print(to_string(colorComponent) + " ");
		}
		auto diffuseTexture = optimizedMaterial->getSpecularMaterialProperties()->getDiffuseTexture();
		Console::print("\t\tDiffuse texture: " + (diffuseTexture == nullptr?"none":to_string(diffuseTexture->getTextureWidth()) + " x " + to_string(diffuseTexture->getTextureHeight())));
		Console::println();
		Console::print("\t\tSpecular: ");
		for (auto colorComponent: optimizedMaterial->getSpecularMaterialProperties()->getSpecularColor().getArray()) {
			Console::print(to_string(colorComponent) + " ");
		}
		Console::println();
		Console::print("\t\tShininess: ");
		Console::print(to_string(optimizedMaterial->getSpecularMaterialProperties()->getShininess()) + " ");
		Console::println();
	}

	// also have a material with masked transparency
	auto optimizedMaterialMaskedTransparency = cloneMaterial(optimizedMaterial, "material.optimized.maskedtransparency");
	optimizedMaterialMaskedTransparency->getSpecularMaterialProperties()->setDiffuseTextureMaskedTransparency(true);

	// also have a material with transparency
	auto optimizedMaterialTransparency = cloneMaterial(optimizedMaterial, "material.optimized.transparency");
	optimizedMaterialTransparency->getSpecularMaterialProperties()->setDiffuseTextureTransparency(true);

	// now optimize into our optimized model
	for (auto& subGroupIt: model->getSubGroups()) {
		auto group = subGroupIt.second;
		if ((model->hasSkinning() == true && group->getSkinning() != nullptr) ||
			(model->hasSkinning() == false && group->isJoint() == false)) {
			optimizeGroup(group, optimizedModel, diffuseAtlasTexture->getAtlasSize(), diffuseTextureAtlasIndices);
			if (model->hasSkinning() == true) {
				auto skinning = group->getSkinning();
				auto optimizedSkinning = new Skinning();
				optimizedSkinning->setWeights(skinning->getWeights());
				optimizedSkinning->setJoints(skinning->getJoints());
				optimizedSkinning->setVerticesJointsWeights(skinning->getVerticesJointsWeights());
				optimizedModel->getGroups()["group.optimized"]->setSkinning(optimizedSkinning);
			}
		}
		cloneGroup(group, optimizedModel, nullptr, false);
	}

	// set up materials
	{
		auto optimizedFacesEntity = optimizedModel->getGroups()["group.optimized"]->getFacesEntity("facesentity.optimized");
		if (optimizedFacesEntity != nullptr) {
			optimizedModel->getMaterials()[optimizedMaterial->getId()] = optimizedMaterial;
			optimizedFacesEntity->setMaterial(optimizedMaterial);
		} else {
			delete optimizedMaterial;
		}
	}
	{
		auto optimizedFacesEntityMaskedTransparency = optimizedModel->getGroups()["group.optimized"]->getFacesEntity("facesentity.optimized.maskedtransparency");
		if (optimizedFacesEntityMaskedTransparency != nullptr) {
			optimizedModel->getMaterials()[optimizedMaterialMaskedTransparency->getId()] = optimizedMaterialMaskedTransparency;
			optimizedFacesEntityMaskedTransparency->setMaterial(optimizedMaterialMaskedTransparency);
		} else {
			delete optimizedMaterialMaskedTransparency;
		}
	}
	{
		auto optimizedFacesEntityTransparency = optimizedModel->getGroups()["group.optimized"]->getFacesEntity("facesentity.optimized.transparency");
		if (optimizedFacesEntityTransparency != nullptr) {
			optimizedModel->getMaterials()[optimizedMaterialTransparency->getId()] = optimizedMaterialTransparency;
			optimizedFacesEntityTransparency->setMaterial(optimizedMaterialTransparency);
		} else {
			delete optimizedMaterialTransparency;
		}
	}

	// copy animation set up
	for (auto animationSetupIt: model->getAnimationSetups()) {
		auto animationSetup = animationSetupIt.second;
		if (animationSetup->getOverlayFromGroupId().empty() == false) {
			optimizedModel->addOverlayAnimationSetup(
				animationSetup->getId(),
				animationSetup->getOverlayFromGroupId(),
				animationSetup->getStartFrame(),
				animationSetup->getEndFrame(),
				animationSetup->isLoop(),
				animationSetup->getSpeed()
			);
		} else {
			optimizedModel->addAnimationSetup(
				animationSetup->getId(),
				animationSetup->getStartFrame(),
				animationSetup->getEndFrame(),
				animationSetup->isLoop(),
				animationSetup->getSpeed()
			);
		}
	}

	//
	delete model;

	Console::println();
	Console::println(optimizedModel->getName());
	Console::println("\tOptimized material count: " + to_string(optimizedModel->getMaterials().size()));
	Console::println("\tOptimized group count: " + to_string(optimizedModel->getGroups().size()));

	Console::println();

	// prepare for indexed rendering
	ModelHelper::prepareForIndexedRendering(optimizedModel);

	// done
	return optimizedModel;
}