#include <tdme/utilities/ModelTools.h>

#include <array>
#include <map>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/ProgressCallback.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Matrix4x4Negative.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/SimpleTextureAtlas.h>
#include <tdme/utilities/StringTools.h>

using std::array;
using std::make_unique;
using std::map;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::unordered_set;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::fileio::ProgressCallback;
using tdme::engine::model::Animation;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::Skinning;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::model::UpVector;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::scene::SceneEntity;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Matrix4x4Negative;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::ModelTools;
using tdme::utilities::SimpleTextureAtlas;
using tdme::utilities::StringTools;

ModelTools::VertexOrder ModelTools::determineVertexOrder(const vector<Vector3>& vertices)
{
	auto edgeSum = 0;
	for (auto i = 0; i < vertices.size(); i++) {
		const auto& currentVertex = vertices[i];
		const auto& nextVertex = vertices[(i + 1) % vertices.size()];
		edgeSum += (nextVertex[0] - currentVertex[0]) * (nextVertex[1] - currentVertex[1]) * (nextVertex[2] - currentVertex[2]);
	}
	if (edgeSum >= 0) {
		return VERTEXORDER_CLOCKWISE;
	} else {
		return VERTEXORDER_COUNTERCLOCKWISE;
	}
}

void ModelTools::prepareForIndexedRendering(Model* model)
{
	prepareForIndexedRendering(model->getSubNodes());
}

void ModelTools::prepareForIndexedRendering(const map<string, Node*>& nodes)
{
	// we need to prepare the node for indexed rendering
	for (const auto& [nodeId, node]: nodes) {
		const auto& nodeVertices = node->getVertices();
		const auto& nodeNormals = node->getNormals();
		const auto& nodeTextureCoordinates = node->getTextureCoordinates();
		const auto& nodeTangents = node->getTangents();
		const auto& nodeBitangents = node->getBitangents();
		const auto& nodeOrigins = node->getOrigins();
		vector<int32_t> vertexMapping;
		vector<Vector3> indexedVertices;
		vector<Vector3> indexedNormals;
		vector<Vector2> indexedTextureCoordinates;
		vector<Vector3> indexedTangents;
		vector<Vector3> indexedBitangents;
		vector<Vector3> indexedOrigins;
		// construct indexed vertex data suitable for indexed rendering
		auto preparedIndices = 0;
		auto newFacesEntities = node->getFacesEntities();
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
					auto nodeVertexIndex = faceVertexIndices[idx];
					auto nodeNormalIndex = faceNormalIndices[idx];
					auto nodeTextureCoordinateIndex = faceTextureIndices[idx];
					auto nodeTangentIndex = faceTangentIndices[idx];
					auto nodeBitangentIndex = faceBitangentIndices[idx];
					auto vertex = &nodeVertices[nodeVertexIndex];
					auto normal = &nodeNormals[nodeNormalIndex];
					auto textureCoordinate = nodeTextureCoordinates.size() > 0?&nodeTextureCoordinates[nodeTextureCoordinateIndex]:static_cast<Vector2*>(nullptr);
					auto tangent = nodeTangents.size() > 0 ? &nodeTangents[nodeTangentIndex] : static_cast<Vector3*>(nullptr);
					auto bitangent = nodeBitangents.size() > 0 ? &nodeBitangents[nodeBitangentIndex] : static_cast<Vector3*>(nullptr);
					auto origin = nodeOrigins.size() > 0 ? &nodeOrigins[nodeVertexIndex] : static_cast<Vector3*>(nullptr);
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
						vertexMapping.push_back(nodeVertexIndex);
						indexedVertices.push_back(*vertex);
						indexedNormals.push_back(*normal);
						if (textureCoordinate != nullptr) indexedTextureCoordinates.push_back(*textureCoordinate);
						if (tangent != nullptr) indexedTangents.push_back(*tangent);
						if (bitangent != nullptr) indexedBitangents.push_back(*bitangent);
						if (origin != nullptr) indexedOrigins.push_back(*origin);
						preparedIndices++;
					}
					indexedFaceVertexIndices[idx] = newIndex;
				}
				face.setIndexedRenderingIndices(indexedFaceVertexIndices);
			}
			newFacesEntity.setFaces(newFaces);
		}
		node->setFacesEntities(newFacesEntities);
		// remap skinning
		auto skinning = node->getSkinning();
		if (skinning != nullptr) {
			prepareForIndexedRendering(skinning, vertexMapping, preparedIndices);
		}
		node->setVertices(indexedVertices);
		node->setNormals(indexedNormals);
		if (nodeTextureCoordinates.size() > 0) {
			node->setTextureCoordinates(indexedTextureCoordinates);
		}
		node->setTangents(indexedTangents);
		node->setBitangents(indexedBitangents);
		if (nodeOrigins.size() > 0) {
			node->setOrigins(indexedOrigins);
		}
		// process sub nodes
		prepareForIndexedRendering(node->getSubNodes());
	}
}

void ModelTools::prepareForIndexedRendering(Skinning* skinning, const vector<int32_t>& vertexMapping, int32_t vertices)
{
	const auto& originalVerticesJointsWeights = skinning->getVerticesJointsWeights();
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

void ModelTools::setupJoints(Model* model)
{
	// determine joints and mark them as joints
	auto nodes = model->getNodes();
	for (const auto& [nodeId, node]: nodes) {
		auto skinning = node->getSkinning();
		// do we have a skinning
		if (skinning != nullptr) {
			// yep
			for (const auto& joint : skinning->getJoints()) {
				auto jointNodeIt = nodes.find(joint.getNodeId());
				if (jointNodeIt != nodes.end()) {
					setJoint(jointNodeIt->second);
				}
			}
		}
	}
}

void ModelTools::setJoint(Node* root)
{
	root->setJoint(true);
	for (const auto& [subNodeId, subNode]: root->getSubNodes()) {
		setJoint(subNode);
	}
}

void ModelTools::fixAnimationLength(Model* model)
{
	// fix animation length
	auto defaultAnimation = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);
	if (defaultAnimation != nullptr) {
		for (const auto& [subNodeId, subNode]: model->getSubNodes()) {
			fixAnimationLength(subNode, defaultAnimation->getFrames());
		}
	}
}

void ModelTools::fixAnimationLength(Node* root, int32_t frames)
{
	auto animation = root->getAnimation();
	if (animation != nullptr) {
		vector<Matrix4x4> newTransformMatrices;
		auto oldTransformMatrices = root->getAnimation()->getTransformMatrices();
		auto animation = new Animation();
		newTransformMatrices.resize(frames);
		for (auto i = 0; i < frames; i++) {
			if (i < oldTransformMatrices.size()) {
				newTransformMatrices[i] = oldTransformMatrices[i];
			} else {
				newTransformMatrices[i].identity();
			}
		}
		animation->setTransformMatrices(newTransformMatrices);
		root->setAnimation(animation);
	}
	for (const auto& [subNodeId, subNode]: root->getSubNodes()) {
		fixAnimationLength(subNode, frames);
	}
}

bool ModelTools::hasDefaultAnimation(Model* model) {
	return model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT) != nullptr;
}

void ModelTools::createDefaultAnimation(Model* model, int32_t frames)
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

Material* ModelTools::cloneMaterial(const Material* material, const string& id) {
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
			clonedSpecularMaterialProperties->setDiffuseTexture(specularMaterialProperties->getDiffuseTexture());
			clonedSpecularMaterialProperties->setDiffuseTexturePathName(specularMaterialProperties->getDiffuseTexturePathName());
			clonedSpecularMaterialProperties->setDiffuseTextureFileName(specularMaterialProperties->getDiffuseTextureFileName());
		}
		clonedSpecularMaterialProperties->setDiffuseTextureTransparency(specularMaterialProperties->hasDiffuseTextureTransparency());
		clonedSpecularMaterialProperties->setDiffuseTextureMaskedTransparency(specularMaterialProperties->hasDiffuseTextureMaskedTransparency());
		clonedSpecularMaterialProperties->setDiffuseTextureMaskedTransparencyThreshold(specularMaterialProperties->getDiffuseTextureMaskedTransparencyThreshold());
		if (specularMaterialProperties->getSpecularTexture() != nullptr) {
			clonedSpecularMaterialProperties->setSpecularTexture(specularMaterialProperties->getSpecularTexture());
			clonedSpecularMaterialProperties->setSpecularTexturePathName(specularMaterialProperties->getSpecularTexturePathName());
			clonedSpecularMaterialProperties->setSpecularTextureFileName(specularMaterialProperties->getSpecularTextureFileName());
		}
		if (specularMaterialProperties->getNormalTexture() != nullptr) {
			clonedSpecularMaterialProperties->setNormalTexture(specularMaterialProperties->getNormalTexture());
			clonedSpecularMaterialProperties->setNormalTexturePathName(specularMaterialProperties->getNormalTexturePathName());
			clonedSpecularMaterialProperties->setNormalTextureFileName(specularMaterialProperties->getNormalTextureFileName());
		}
		clonedMaterial->setSpecularMaterialProperties(clonedSpecularMaterialProperties);
	}
	return clonedMaterial;
}

void ModelTools::cloneNode(Node* sourceNode, Model* targetModel, Node* targetParentNode, bool cloneMesh) {
	auto clonedNode = new Node(targetModel, targetParentNode, sourceNode->getId(), sourceNode->getName());
	clonedNode->setTransformMatrix(sourceNode->getTransformMatrix());
	clonedNode->setJoint(sourceNode->isJoint());
	if (cloneMesh == true) {
		clonedNode->setVertices(sourceNode->getVertices());
		clonedNode->setNormals(sourceNode->getNormals());
		clonedNode->setTextureCoordinates(sourceNode->getTextureCoordinates());
		clonedNode->setTangents(sourceNode->getTangents());
		clonedNode->setBitangents(sourceNode->getBitangents());
		clonedNode->setOrigins(sourceNode->getOrigins());
		auto facesEntities = clonedNode->getFacesEntities();
		for (const auto& facesEntity: sourceNode->getFacesEntities()) {
			if (facesEntity.getMaterial() == nullptr) continue;
			Material* material = nullptr;
			auto materialIt = targetModel->getMaterials().find(facesEntity.getMaterial()->getId());
			if (materialIt == targetModel->getMaterials().end()) {
				material = cloneMaterial(facesEntity.getMaterial());
				targetModel->getMaterials()[material->getId()] = material;
			} else {
				material = materialIt->second;
			}
			auto clonedFacesEntity = FacesEntity(clonedNode, facesEntity.getId());
			clonedFacesEntity.setMaterial(material);
			clonedFacesEntity.setFaces(facesEntity.getFaces());
			facesEntities.push_back(clonedFacesEntity);
		}
		clonedNode->setFacesEntities(facesEntities);
	}
	if (sourceNode->getAnimation() != nullptr) {
		auto clonedAnimation = new Animation();
		clonedAnimation->setTransformMatrices(sourceNode->getAnimation()->getTransformMatrices());
		clonedNode->setAnimation(clonedAnimation);
	}
	targetModel->getNodes()[clonedNode->getId()] = clonedNode;
	if (targetParentNode == nullptr) {
		targetModel->getSubNodes()[clonedNode->getId()] = clonedNode;
	} else {
		targetParentNode->getSubNodes()[clonedNode->getId()] = clonedNode;
	}
	for (const auto& [sourceSubNodeId, sourceSubNode]: sourceNode->getSubNodes()) {
		cloneNode(sourceSubNode, targetModel, clonedNode, cloneMesh);
	}
}

void ModelTools::partitionNode(Node* sourceNode, map<string, Model*>& modelsByPartition, map<string, Vector3>& modelsPosition, const Matrix4x4& parentTransformMatrix) {
	// TODO: performance: faces handling is very suboptimal currently, however this is only executed in SceneEditor if doing partitioning
	Vector3 faceCenter;

	Matrix4x4 transformMatrix;
	transformMatrix.set(sourceNode->getTransformMatrix());
	transformMatrix.multiply(parentTransformMatrix);

	Vector3 vertex0;
	Vector3 vertex1;
	Vector3 vertex2;
	Vector3 normal0;
	Vector3 normal1;
	Vector3 normal2;
	Vector2 textureCoordinate0;
	Vector2 textureCoordinate1;
	Vector2 textureCoordinate2;
	Vector3 tangent0;
	Vector3 tangent1;
	Vector3 tangent2;
	Vector3 bitangent0;
	Vector3 bitangent1;
	Vector3 bitangent2;

	Vector3 vertex0Transformed;
	Vector3 vertex1Transformed;
	Vector3 vertex2Transformed;

	auto sourceNodeId = sourceNode->getModel()->getId();
	auto sourceNodeName = sourceNode->getModel()->getName();

	// TODO: maybe check if id and node do have real file endings like .tm, .dae, .fbx or something
	if (StringTools::lastIndexOf(sourceNodeId, '.') != -1) {
		sourceNodeId = StringTools::substring(sourceNodeId, 0, StringTools::lastIndexOf(sourceNodeId, '.') - 1);
	}
	if (StringTools::lastIndexOf(sourceNodeName, '.') != -1) {
		sourceNodeName = StringTools::substring(sourceNodeName, 0, StringTools::lastIndexOf(sourceNodeName, '.') - 1);
	}

	//
	map<string, Node*> partitionModelNodes;

	// partition model node vertices and such
	map<string, vector<Vector3>> partitionModelNodesVertices;
	map<string, vector<Vector3>> partitionModelNodesNormals;
	map<string, vector<Vector2>> partitionModelNodesTextureCoordinates;
	map<string, vector<Vector3>> partitionModelNodesTangents;
	map<string, vector<Vector3>> partitionModelNodesBitangents;
	map<string, vector<FacesEntity>> partitionModelNodesFacesEntities;

	for (const auto& facesEntity: sourceNode->getFacesEntities()) {
		bool haveTextureCoordinates = facesEntity.isTextureCoordinatesAvailable();
		bool haveTangentsBitangents = facesEntity.isTangentBitangentAvailable();
		for (const auto& face: facesEntity.getFaces()) {
			// get face vertices and such
			const auto& vertexIndices = face.getVertexIndices();
			const auto& normalIndices = face.getNormalIndices();
			const auto& textureCoordinatesIndices = face.getTextureCoordinateIndices();
			const auto& tangentIndices = face.getTangentIndices();
			const auto& bitangentIndices = face.getBitangentIndices();
			vertex0.set(sourceNode->getVertices()[vertexIndices[0]]);
			vertex1.set(sourceNode->getVertices()[vertexIndices[1]]);
			vertex2.set(sourceNode->getVertices()[vertexIndices[2]]);
			normal0.set(sourceNode->getNormals()[normalIndices[0]]);
			normal1.set(sourceNode->getNormals()[normalIndices[1]]);
			normal2.set(sourceNode->getNormals()[normalIndices[2]]);
			if (haveTextureCoordinates == true) {
				textureCoordinate0.set(sourceNode->getTextureCoordinates()[textureCoordinatesIndices[0]]);
				textureCoordinate1.set(sourceNode->getTextureCoordinates()[textureCoordinatesIndices[1]]);
				textureCoordinate2.set(sourceNode->getTextureCoordinates()[textureCoordinatesIndices[2]]);
			}
			if (haveTangentsBitangents == true) {
				tangent0.set(sourceNode->getTangents()[tangentIndices[0]]);
				tangent1.set(sourceNode->getTangents()[tangentIndices[1]]);
				tangent2.set(sourceNode->getTangents()[tangentIndices[2]]);
				bitangent0.set(sourceNode->getBitangents()[bitangentIndices[0]]);
				bitangent1.set(sourceNode->getBitangents()[bitangentIndices[1]]);
				bitangent2.set(sourceNode->getBitangents()[bitangentIndices[2]]);
			}

			// find out partition by transforming vertices into world coordinates
			vertex0Transformed = transformMatrix.multiply(vertex0);
			vertex1Transformed = transformMatrix.multiply(vertex1);
			vertex2Transformed = transformMatrix.multiply(vertex2);
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
					sourceNodeId + "." + partitionModelKey,
					sourceNodeName + "." + partitionModelKey,
					sourceNode->getModel()->getUpVector(),
					sourceNode->getModel()->getRotationOrder(),
					nullptr
				);
				modelsByPartition[partitionModelKey] = partitionModel;
				modelsPosition[partitionModelKey].set(partitionX * 64.0f, partitionY * 64.0f, partitionZ * 64.0f);
			}

			// get node
			auto partitionModelNode = partitionModelNodes[partitionModelKey];
			partitionModelNode = partitionModel->getNodeById(sourceNode->getId());
			if (partitionModelNode == nullptr) {
				// TODO: create sub nodes if they do not yet exist
				partitionModelNode = new Node(
					partitionModel,
					sourceNode->getParentNode() == nullptr?nullptr:partitionModel->getNodeById(sourceNode->getParentNode()->getId()),
					sourceNode->getId(),
					sourceNode->getName()
				);
				partitionModelNode->setTransformMatrix(sourceNode->getTransformMatrix());
				if (sourceNode->getParentNode() == nullptr) {
					partitionModel->getSubNodes()[partitionModelNode->getId()] = partitionModelNode;
				} else {
					partitionModelNode->getParentNode()->getSubNodes()[partitionModelNode->getId()] = partitionModelNode;
				}
				partitionModel->getNodes()[partitionModelNode->getId()] = partitionModelNode;
				partitionModelNodes[partitionModelKey] = partitionModelNode;
			}

			// get faces entity
			FacesEntity* partitionModelNodeFacesEntity = nullptr;
			for (auto& partitionModelNodeFacesEntityExisting: partitionModelNodesFacesEntities[partitionModelKey]) {
				if (partitionModelNodeFacesEntityExisting.getId() == facesEntity.getId()) {
					partitionModelNodeFacesEntity = &partitionModelNodeFacesEntityExisting;
				}
			}
			if (partitionModelNodeFacesEntity == nullptr) {
				auto newFacesEntity = FacesEntity(
					partitionModelNode,
					facesEntity.getId()
				);
				partitionModelNodesFacesEntities[partitionModelKey].push_back(newFacesEntity);
				partitionModelNodeFacesEntity = &newFacesEntity;
				auto partitionModelNodeFacesEntityMaterial = partitionModel->getMaterials()[facesEntity.getMaterial()->getId()];
				if (partitionModelNodeFacesEntityMaterial == nullptr) {
					partitionModelNodeFacesEntityMaterial = cloneMaterial(facesEntity.getMaterial());
					partitionModel->getMaterials()[facesEntity.getMaterial()->getId()] = partitionModelNodeFacesEntityMaterial;
				}
				partitionModelNodeFacesEntity->setMaterial(partitionModelNodeFacesEntityMaterial);
			}

			auto faces = partitionModelNodeFacesEntity->getFaces();

			// add vertices and such
			auto verticesIdx = partitionModelNodesVertices[partitionModelKey].size();
			partitionModelNodesVertices[partitionModelKey].push_back(vertex0);
			partitionModelNodesVertices[partitionModelKey].push_back(vertex1);
			partitionModelNodesVertices[partitionModelKey].push_back(vertex2);
			partitionModelNodesNormals[partitionModelKey].push_back(normal0);
			partitionModelNodesNormals[partitionModelKey].push_back(normal1);
			partitionModelNodesNormals[partitionModelKey].push_back(normal2);
			if (haveTextureCoordinates == true) {
				partitionModelNodesTextureCoordinates[partitionModelKey].push_back(textureCoordinate0);
				partitionModelNodesTextureCoordinates[partitionModelKey].push_back(textureCoordinate1);
				partitionModelNodesTextureCoordinates[partitionModelKey].push_back(textureCoordinate2);
			}
			if (haveTangentsBitangents == true) {
				partitionModelNodesTangents[partitionModelKey].push_back(tangent0);
				partitionModelNodesTangents[partitionModelKey].push_back(tangent1);
				partitionModelNodesTangents[partitionModelKey].push_back(tangent2);
				partitionModelNodesBitangents[partitionModelKey].push_back(bitangent0);
				partitionModelNodesBitangents[partitionModelKey].push_back(bitangent1);
				partitionModelNodesBitangents[partitionModelKey].push_back(bitangent2);
			}
			Face newFace =
				Face(
					partitionModelNode,
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
			partitionModelNodeFacesEntity->setFaces(faces);
		}
	}

	// set vertices and such
	for (const auto& [partitionModelKey, model]: modelsByPartition) {
		if (partitionModelNodes[partitionModelKey] == nullptr) continue;
		partitionModelNodes[partitionModelKey]->setVertices(partitionModelNodesVertices[partitionModelKey]);
		partitionModelNodes[partitionModelKey]->setNormals(partitionModelNodesNormals[partitionModelKey]);
		partitionModelNodes[partitionModelKey]->setTextureCoordinates(partitionModelNodesTextureCoordinates[partitionModelKey]);
		partitionModelNodes[partitionModelKey]->setTangents(partitionModelNodesTangents[partitionModelKey]);
		partitionModelNodes[partitionModelKey]->setBitangents(partitionModelNodesBitangents[partitionModelKey]);
		partitionModelNodes[partitionModelKey]->setFacesEntities(partitionModelNodesFacesEntities[partitionModelKey]);
	}

	// partition sub nodes
	for (const auto& [sourceNodeId, sourceNode]: sourceNode->getSubNodes()) {
		partitionNode(sourceNode, modelsByPartition, modelsPosition, transformMatrix);
	}
}

void ModelTools::partition(Model* model, const Transform& transform, map<string, Model*>& modelsByPartition, map<string, Vector3>& modelsPosition) {
	Matrix4x4 transformMatrix;
	transformMatrix.set(model->getImportTransformMatrix());
	transformMatrix.multiply(transform.getTransformMatrix());
	for (const auto& [subNodeId, subNode]: model->getSubNodes()) {
		partitionNode(subNode, modelsByPartition, modelsPosition, transformMatrix);
	}
	for (const auto& [partitionKey, partitionModel]: modelsByPartition) {
		partitionModel->setImportTransformMatrix(model->getImportTransformMatrix());
		ModelTools::createDefaultAnimation(partitionModel, 0);
		ModelTools::setupJoints(partitionModel);
		ModelTools::fixAnimationLength(partitionModel);
		ModelTools::prepareForIndexedRendering(partitionModel);
	}
}

void ModelTools::shrinkToFit(Node* node) {
	// TODO: a.drewke
	/*
	for (auto& facesEntity: node->getFacesEntities()) {
		facesEntity.getFaces().shrink_to_fit();
	}

	node->getFacesEntities().shrink_to_fit();
	node->getVertices().shrink_to_fit();
	node->getNormals().shrink_to_fit();
	node->getTextureCoordinates().shrink_to_fit();
	node->getTangents().shrink_to_fit();
	node->getBitangents().shrink_to_fit();

	// do child nodes
	for (const auto& [subNodeId, subNode]: node->getSubNodes()) {
		shrinkToFit(subNode);
	}
	*/
}

void ModelTools::shrinkToFit(Model* model) {
	for (const auto& [subNodeId, subNode]: model->getSubNodes()) {
		shrinkToFit(subNode);
	}
}

float ModelTools::computeNormals(Node* node, ProgressCallback* progressCallback, float incrementPerFace, float progress) {
	node->setNormals(vector<Vector3>());
	array<Vector3, 3> vertices;
	Vector3 normal;
	auto facesEntityProcessed = 0;
	vector<Vector3> normals;
	auto facesEntities = node->getFacesEntities();
	for (auto& facesEntity: facesEntities) {
		auto faces = facesEntity.getFaces();
		for (auto& face: faces) {
			for (auto i = 0; i < vertices.size(); i++) {
				vertices[i] = node->getVertices()[face.getVertexIndices()[i]];
			}
			normal = computeNormal(vertices);
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
	node->setFacesEntities(facesEntities);
	facesEntityProcessed = 0;
	for (const auto& facesEntity: node->getFacesEntities()) {
		for (const auto& face: facesEntity.getFaces()) {
			for (auto i = 0; i < vertices.size(); i++) {
				if (interpolateNormal(node, node->getVertices()[face.getVertexIndices()[i]], normals, normal) == true) {
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
	node->setNormals(normals);
	for (const auto& [subNodeId, subNode]: node->getSubNodes()) {
		progress = computeNormals(subNode, progressCallback, incrementPerFace, progress);
	}
	return progress;
}

void ModelTools::computeNormals(Model* model, ProgressCallback* progressCallback) {
	auto progessCallbackPtr = unique_ptr<ProgressCallback>(progressCallback);
	auto faceCount = 0;
	for (const auto& [subNodeId, subNode]: model->getSubNodes()) {
		faceCount+= determineFaceCount(subNode);
	}
	for (const auto& [subNodeId, subNode]: model->getSubNodes()) {
		computeNormals(subNode, progessCallbackPtr.get(), 1.0f / static_cast<float>(faceCount), 0.0f);
	}
	prepareForIndexedRendering(model);
	if (progessCallbackPtr != nullptr) {
		progessCallbackPtr->progress(1.0f);
	}
}

int ModelTools::determineFaceCount(Node* node) {
	auto faceCount = 0;
	faceCount+= node->getFaceCount();
	for (const auto& [subNodeId, subNode]: node->getSubNodes()) {
		faceCount+= determineFaceCount(subNode);
	}
	return faceCount;
}

void ModelTools::prepareForShader(Model* model, const string& shader) {
	if (shader == "foliage" || shader == "pbr-foliage" || shader == "tree" || shader == "pbr-tree") {
		model->getAnimationSetups().clear();
		for (const auto& [subNodeId, subNode]: model->getSubNodes()) prepareForFoliageTreeShader(subNode, model->getImportTransformMatrix(), shader);
		model->setImportTransformMatrix(Matrix4x4().identity());
		model->setUpVector(UpVector::Y_UP);
		createDefaultAnimation(model, 0);
	}
}

void ModelTools::prepareForDefaultShader(Node* node, const Matrix4x4& parentTransformaMatrix) {
	auto transformMatrix = node->getTransformMatrix().clone().multiply(parentTransformaMatrix);
	// do not continue on non mesh datas
	if (node->isEmpty() == true || node->isJoint() == true) {
		node->setTransformMatrix(transformMatrix);
		//
		for (const auto& [subNodeId, subNode]: node->getSubNodes()) {
			prepareForDefaultShader(subNode, transformMatrix);
		}
		//
		return;
	}
	// apply transformations matrix to vertices, ...
	{
		auto vertices = node->getVertices();
		auto vertexIdx = 0;
		for (auto& vertex: vertices) {
			vertex = transformMatrix.multiply(vertex);
		}
		node->setVertices(vertices);
	}
	{
		auto normals = node->getNormals();
		for (auto& normal: normals) {
			normal = transformMatrix.multiplyNoTranslation(normal);
			normal.normalize();
		}
		node->setNormals(normals);
	}
	{
		auto tangents = node->getTangents();
		for (auto& tangent: tangents) {
			tangent = transformMatrix.multiplyNoTranslation(tangent);
			tangent.normalize();
		}
		node->setTangents(tangents);
	}
	{
		auto bitangents = node->getBitangents();
		for (auto& bitangent: bitangents) {
			bitangent = transformMatrix.multiplyNoTranslation(bitangent);
			bitangent.normalize();
		}
		node->setBitangents(bitangents);
	}
	node->setTransformMatrix(Matrix4x4().identity());
	// check if we need to change front face
	Matrix4x4Negative matrix4x4Negative;
	if (matrix4x4Negative.isNegative(transformMatrix) == true) changeFrontFace(node, false);
	//
	for (const auto& [subNodeId, subNode]: node->getSubNodes()) {
		prepareForDefaultShader(subNode, transformMatrix);
	}
}

void ModelTools::prepareForFoliageTreeShader(Node* node, const Matrix4x4& parentTransformMatrix, const string& shader) {
	//
	node->setAnimation(nullptr);
	//
	auto transformMatrix = node->getTransformMatrix().clone().multiply(parentTransformMatrix);
	// do not continue on non mesh datas
	if (node->isEmpty() == true || node->isJoint() == true) {
		node->setTransformMatrix(transformMatrix);
		//
		for (const auto& [subNodeId, subNode]: node->getSubNodes()) {
			prepareForFoliageTreeShader(subNode, transformMatrix, shader);
		}
		//
		return;
	}
	//
	vector<Vector3> objectOrigins;
	objectOrigins.resize(node->getVertices().size());
	{
		auto vertices = node->getVertices();
		auto vertexIdx = 0;
		for (auto& vertex: vertices) {
			vertex = transformMatrix.multiply(vertex);
			if (shader == "tree" || shader == "pbr-tree") objectOrigins[vertexIdx].set(0.0f, vertex.getY(), 0.0f);
			vertexIdx++;
		}
		node->setVertices(vertices);
	}
	{
		auto normals = node->getNormals();
		for (auto& normal: normals) {
			normal = transformMatrix.multiplyNoTranslation(normal);
			normal.normalize();
		}
		node->setNormals(normals);
	}
	{
		auto tangents = node->getTangents();
		for (auto& tangent: tangents) {
			tangent = transformMatrix.multiplyNoTranslation(tangent);
			tangent.normalize();
		}
		node->setTangents(tangents);
	}
	{
		auto bitangents = node->getBitangents();
		for (auto& bitangent: bitangents) {
			bitangent = transformMatrix.multiplyNoTranslation(bitangent);
			bitangent.normalize();
		}
		node->setBitangents(bitangents);
	}
	node->setTransformMatrix(Matrix4x4().identity());
	node->setOrigins(objectOrigins);
	// check if we need to change front face
	Matrix4x4Negative matrix4x4Negative;
	if (matrix4x4Negative.isNegative(transformMatrix) == true) changeFrontFace(node, false);
	//
	for (const auto& [subNodeId, subNode]: node->getSubNodes()) {
		prepareForFoliageTreeShader(subNode, transformMatrix, shader);
	}
}

void ModelTools::checkForOptimization(Node* node, map<string, int>& materialUseCount, const vector<string>& excludeDiffuseTextureFileNamePatterns) {
	// skip on joints as they do not have textures to display and no vertex data
	if (node->isJoint() == true) return;

	// track material usage
	for (const auto& facesEntity: node->getFacesEntities()) {
		if (facesEntity.getMaterial() == nullptr) continue;
		bool excludeDiffuseTexture = false;
		for (const auto& excludeDiffuseTextureFileNamePattern: excludeDiffuseTextureFileNamePatterns) {
			if (StringTools::startsWith(facesEntity.getMaterial()->getSpecularMaterialProperties()->getDiffuseTextureFileName(), excludeDiffuseTextureFileNamePattern) == true) {
				excludeDiffuseTexture = true;
				break;
			}
		}
		if (excludeDiffuseTexture == true) {
			continue;
		}
		materialUseCount[facesEntity.getMaterial()->getId()]++;
	}

	// do not transform skinning vertices and such
	if (node->getSkinning() != nullptr) return;

	//
	for (const auto& [subNodeId, subNode]: node->getSubNodes()) {
		checkForOptimization(subNode, materialUseCount, excludeDiffuseTextureFileNamePatterns);
	}
}

void ModelTools::prepareForOptimization(Node* node, const Matrix4x4& parentTransformMatrix) {
	// skip on joints as they do not have textures to display and no vertex data
	if (node->isJoint() == true) return;

	// do not transform skinning vertices and such
	if (node->getSkinning() != nullptr) return;

	// static node, apply node transform matrix
	auto transformMatrix = node->getTransformMatrix().clone().multiply(parentTransformMatrix);
	{
		auto vertices = node->getVertices();
		for (auto& vertex: vertices) {
			vertex = transformMatrix.multiply(vertex);
		}
		node->setVertices(vertices);
	}
	{
		auto normals = node->getNormals();
		for (auto& normal: normals) {
			normal = transformMatrix.multiplyNoTranslation(normal);
			normal.normalize();
		}
		node->setNormals(normals);
	}
	{
		auto tangents = node->getTangents();
		for (auto& tangent: tangents) {
			tangent = transformMatrix.multiplyNoTranslation(tangent);
			tangent.normalize();
		}
		node->setTangents(tangents);
	}
	{
		auto bitangents = node->getBitangents();
		for (auto& bitangent: bitangents) {
			bitangent = transformMatrix.multiplyNoTranslation(bitangent);
			bitangent.normalize();
		}
		node->setBitangents(bitangents);
	}

	// we do not set node transform matrix as we need it later
	// node->setTransformMatrix(Matrix4x4().identity());

	//
	for (const auto& [subNodeId, subNode]: node->getSubNodes()) {
		prepareForOptimization(subNode, transformMatrix);
	}
}

void ModelTools::optimizeNode(Node* sourceNode, Model* targetModel, int diffuseTextureAtlasSize, const map<string, int>& diffuseTextureAtlasIndices, const vector<string>& excludeDiffuseTextureFileNamePatterns) {
	if (sourceNode->getFacesEntities().size() > 0) {
		unordered_set<int> processedTextureCoordinates;
		const auto& sourceVertices = sourceNode->getVertices();
		const auto& sourceNormals = sourceNode->getNormals();
		const auto& sourceTangents = sourceNode->getTangents();
		const auto& sourceBitangents = sourceNode->getBitangents();
		const auto& sourceTextureCoordinates = sourceNode->getTextureCoordinates();
		const auto& sourceOrigins = sourceNode->getOrigins();
		auto targetNode = targetModel->getNodes()["tdme.node.optimized"];
		auto targetVertices = targetNode->getVertices();
		auto targetNormals = targetNode->getNormals();
		auto targetTangents = targetNode->getTangents();
		auto targetBitangents = targetNode->getBitangents();
		auto targetTextureCoordinates = targetNode->getTextureCoordinates();
		auto targetOrigins = targetNode->getOrigins();
		auto targetOffset = targetVertices.size();
		for (const auto& v: sourceVertices) targetVertices.push_back(v);
		for (const auto& v: sourceNormals) targetNormals.push_back(v);
		for (const auto& v: sourceTangents) targetTangents.push_back(v);
		for (const auto& v: sourceBitangents) targetBitangents.push_back(v);
		for (const auto& v: sourceTextureCoordinates) targetTextureCoordinates.push_back(v);
		for (const auto& v: sourceOrigins) targetOrigins.push_back(v);
		targetNode->setVertices(targetVertices);
		targetNode->setNormals(targetNormals);
		targetNode->setTangents(targetTangents);
		targetNode->setBitangents(targetBitangents);
		targetNode->setOrigins(targetOrigins);
		vector<FacesEntity> targetFacesEntitiesKeptMaterials;
		for (auto& targetFacesEntity: targetNode->getFacesEntities()) {
			if (StringTools::startsWith(targetFacesEntity.getId(), "tdme.facesentity.kept.") == false) continue;
			targetFacesEntitiesKeptMaterials.push_back(targetFacesEntity);
		}
		FacesEntity* tmpFacesEntity = nullptr;
		auto targetFaces = (tmpFacesEntity = targetNode->getFacesEntity("tdme.facesentity.optimized")) != nullptr?tmpFacesEntity->getFaces():vector<Face>();
		auto targetFacesMaskedTransparency = (tmpFacesEntity = targetNode->getFacesEntity("tdme.facesentity.optimized.maskedtransparency")) != nullptr?tmpFacesEntity->getFaces():vector<Face>();
		auto targetFacesTransparency = (tmpFacesEntity = targetNode->getFacesEntity("tdme.facesentity.optimized.transparency")) != nullptr?tmpFacesEntity->getFaces():vector<Face>();
		for (const auto& sourceFacesEntity: sourceNode->getFacesEntities()) {
			auto material = sourceFacesEntity.getMaterial();

			//
			string keptMaterialId;
			for (const auto& excludeDiffuseTextureFileNamePattern: excludeDiffuseTextureFileNamePatterns) {
				if (StringTools::startsWith(sourceFacesEntity.getMaterial()->getSpecularMaterialProperties()->getDiffuseTextureFileName(), excludeDiffuseTextureFileNamePattern) == true) {
					keptMaterialId = sourceFacesEntity.getMaterial()->getId();
					break;
				}
			}
			auto targetFacesKeptMaterial = (tmpFacesEntity = targetNode->getFacesEntity("tdme.facesentity.kept." + keptMaterialId)) != nullptr?tmpFacesEntity->getFaces():vector<Face>();

			auto diffuseTextureAtlasIndexIt = diffuseTextureAtlasIndices.find(material->getId());
			auto diffuseTextureAtlasIndex = -1;
			if (diffuseTextureAtlasIndexIt != diffuseTextureAtlasIndices.end()) {
				diffuseTextureAtlasIndex = diffuseTextureAtlasIndices.find(material->getId())->second;
			}
			auto textureXOffset = 0.0f;
			auto textureYOffset = 0.0f;
			auto textureXScale = 1.0f;
			auto textureYScale = 1.0f;
			if (diffuseTextureAtlasIndex != -1) {
				textureXOffset = diffuseTextureAtlasSize == 0?0.0f:static_cast<float>(diffuseTextureAtlasIndex % diffuseTextureAtlasSize) * 1000.0f + 500.0f;
				textureYOffset = diffuseTextureAtlasSize == 0?0.0f:static_cast<float>(diffuseTextureAtlasIndex / diffuseTextureAtlasSize) * 1000.0f + 500.0f;
				textureXScale = diffuseTextureAtlasSize == 0?1.0f:1.0f;
				textureYScale = diffuseTextureAtlasSize == 0?1.0f:1.0f;
			}
			for (const auto& face: sourceFacesEntity.getFaces()) {
				auto sourceVertexIndices = face.getVertexIndices();
				auto sourceNormalIndices = face.getNormalIndices();
				auto sourceTangentIndices = face.getTangentIndices();
				auto sourceBitangentIndices = face.getBitangentIndices();
				auto sourceTextureCoordinateIndices = face.getTextureCoordinateIndices();
				// TODO: could happen that in one node are two faces entities with different textures that reference the same texture coordinate, in this case the following breaks the texture coordinates
				for (auto i = 0; i < sourceTextureCoordinateIndices.size(); i++) {
					if (sourceTextureCoordinateIndices[i] != -1 &&
						sourceTextureCoordinates.size() > 0 &&
						processedTextureCoordinates.find(sourceTextureCoordinateIndices[i]) == processedTextureCoordinates.end()) {
						auto textureCoordinateArray = sourceTextureCoordinates[sourceTextureCoordinateIndices[i]].getArray();
						textureCoordinateArray[0]*= textureXScale;
						textureCoordinateArray[0]+= textureXOffset;
						textureCoordinateArray[1]*= textureYScale;
						textureCoordinateArray[1]+= textureYOffset;
						targetTextureCoordinates[sourceTextureCoordinateIndices[i] + targetOffset] = Vector2(textureCoordinateArray);
						processedTextureCoordinates.insert(sourceTextureCoordinateIndices[i]);
					}
				}
				if (keptMaterialId.empty() == false) {
					targetFacesKeptMaterial.push_back(
						Face(
							targetNode,
							sourceVertexIndices[0] + targetOffset,
							sourceVertexIndices[1] + targetOffset,
							sourceVertexIndices[2] + targetOffset,
							sourceNormalIndices[0] + targetOffset,
							sourceNormalIndices[1] + targetOffset,
							sourceNormalIndices[2] + targetOffset,
							sourceTextureCoordinateIndices[0] + targetOffset,
							sourceTextureCoordinateIndices[1] + targetOffset,
							sourceTextureCoordinateIndices[2] + targetOffset
						)
					);
				} else
				if (material->getSpecularMaterialProperties()->hasDiffuseTextureTransparency() == true) {
					if (material->getSpecularMaterialProperties()->hasDiffuseTextureMaskedTransparency() == true) {
						targetFacesMaskedTransparency.push_back(
							Face(
								targetNode,
								sourceVertexIndices[0] + targetOffset,
								sourceVertexIndices[1] + targetOffset,
								sourceVertexIndices[2] + targetOffset,
								sourceNormalIndices[0] + targetOffset,
								sourceNormalIndices[1] + targetOffset,
								sourceNormalIndices[2] + targetOffset,
								sourceTextureCoordinateIndices[0] + targetOffset,
								sourceTextureCoordinateIndices[1] + targetOffset,
								sourceTextureCoordinateIndices[2] + targetOffset
							)
						);
					} else {
						targetFacesTransparency.push_back(
							Face(
								targetNode,
								sourceVertexIndices[0] + targetOffset,
								sourceVertexIndices[1] + targetOffset,
								sourceVertexIndices[2] + targetOffset,
								sourceNormalIndices[0] + targetOffset,
								sourceNormalIndices[1] + targetOffset,
								sourceNormalIndices[2] + targetOffset,
								sourceTextureCoordinateIndices[0] + targetOffset,
								sourceTextureCoordinateIndices[1] + targetOffset,
								sourceTextureCoordinateIndices[2] + targetOffset
							)
						);
					}
				} else {
					targetFaces.push_back(
						Face(
							targetNode,
							sourceVertexIndices[0] + targetOffset,
							sourceVertexIndices[1] + targetOffset,
							sourceVertexIndices[2] + targetOffset,
							sourceNormalIndices[0] + targetOffset,
							sourceNormalIndices[1] + targetOffset,
							sourceNormalIndices[2] + targetOffset,
							sourceTextureCoordinateIndices[0] + targetOffset,
							sourceTextureCoordinateIndices[1] + targetOffset,
							sourceTextureCoordinateIndices[2] + targetOffset
						)
					);
				}
			}
			if (targetFacesKeptMaterial.size() > 0) {
				FacesEntity* facesEntity = nullptr;
				for (auto& targetFacesEntityKeptMaterial: targetFacesEntitiesKeptMaterials) {
					if (targetFacesEntityKeptMaterial.getId() == "tdme.facesentity.kept." + keptMaterialId) {
						facesEntity = &targetFacesEntityKeptMaterial;
						break;
					}
				}
				if (facesEntity == nullptr) {
					targetFacesEntitiesKeptMaterials.push_back(FacesEntity(targetNode, "tdme.facesentity.kept." + keptMaterialId));
					facesEntity = &targetFacesEntitiesKeptMaterials[targetFacesEntitiesKeptMaterials.size() - 1];
				}
				facesEntity->setFaces(targetFacesKeptMaterial);
				facesEntity->setMaterial(targetModel->getMaterials()[keptMaterialId]);
			}
		}
		targetNode->setTextureCoordinates(targetTextureCoordinates);
		vector<FacesEntity> targetFacesEntities;
		if (targetFaces.size() > 0) {
			targetFacesEntities.push_back(FacesEntity(targetNode, "tdme.facesentity.optimized"));
			targetFacesEntities[targetFacesEntities.size() - 1].setFaces(targetFaces);
		}
		if (targetFacesMaskedTransparency.size() > 0) {
			targetFacesEntities.push_back(FacesEntity(targetNode, "tdme.facesentity.optimized.maskedtransparency"));
			targetFacesEntities[targetFacesEntities.size() - 1].setFaces(targetFacesMaskedTransparency);
		}
		if (targetFacesTransparency.size() > 0) {
			targetFacesEntities.push_back(FacesEntity(targetNode, "tdme.facesentity.optimized.transparency"));
			targetFacesEntities[targetFacesEntities.size() - 1].setFaces(targetFacesTransparency);
		}
		for (const auto& targetFacesEntityKeptMaterial: targetFacesEntitiesKeptMaterials) {
			targetFacesEntities.push_back(targetFacesEntityKeptMaterial);
		}
		targetNode->setFacesEntities(targetFacesEntities);
	}
	for (const auto& [subNodeId, subNode]: sourceNode->getSubNodes()) {
		optimizeNode(subNode, targetModel, diffuseTextureAtlasSize, diffuseTextureAtlasIndices, excludeDiffuseTextureFileNamePatterns);
	}
}

bool ModelTools::isOptimizedModel(Model* model) {
	return model->getNodes()["tdme.node.optimized"] != nullptr;
}

Model* ModelTools::optimizeModel(Model* model, const string& texturePathName, const vector<string>& excludeDiffuseTextureFileNamePatterns) {
	auto modelPtr = unique_ptr<Model>(model);
	// exit early if modelPtr has been optimized already
	if (isOptimizedModel(modelPtr.get()) == true) return modelPtr.release();

	// TODO: 2 mats could have the same texture
	// prepare for optimizations
	map<string, int> materialUseCount;
	for (const auto& [subNodeId, subNode]: modelPtr->getSubNodes()) {
		checkForOptimization(
			subNode,
			materialUseCount,
			excludeDiffuseTextureFileNamePatterns
		);
	}

	// create diffuse atlas texture
	SimpleTextureAtlas diffuseAtlas(modelPtr->getName() + ".diffuse.atlas");

	// check materials and diffuse textures
	auto diffuseTextureCount = 0;
	map<string, int> diffuseTextureAtlasIndices;
	map<string, Material*> atlasMaterials;
	for (const auto& [materialName, materialCount]: materialUseCount) {
		auto material = modelPtr->getMaterials().find(materialName)->second;
		auto diffuseTexture = material->getSpecularMaterialProperties()->getDiffuseTexture();
		if (diffuseTexture != nullptr) {
			diffuseTextureAtlasIndices[material->getId()] = diffuseAtlas.addTexture(diffuseTexture);
			diffuseTextureCount++;
			atlasMaterials[material->getId()] = material;
		}
	}

	// do we need to optimize?
	if (diffuseTextureCount < 2) return modelPtr.release();

	// prepare for optimizations
	for (const auto& [subNodeId, subNode]: modelPtr->getSubNodes()) {
		prepareForOptimization(
			subNode,
			Matrix4x4().identity()
		);
	}

	// update diffuse atlas texture
	diffuseAtlas.update();

	// create modelPtr with optimizations applied
	auto optimizedModelPtr = make_unique<Model>(modelPtr->getId() + ".optimized", modelPtr->getName() + ".optimized", modelPtr->getUpVector(), modelPtr->getRotationOrder(), new BoundingBox(modelPtr->getBoundingBox()), modelPtr->getAuthoringTool());
	optimizedModelPtr->setImportTransformMatrix(modelPtr->getImportTransformMatrix());
	optimizedModelPtr->setEmbedSpecularTextures(true);
	optimizedModelPtr->setEmbedPBRTextures(true);
	auto optimizedNode = new Node(optimizedModelPtr.get(), nullptr, "tdme.node.optimized", "tdme.node.optimized");
	optimizedModelPtr->getNodes()["tdme.node.optimized"] = optimizedNode;
	optimizedModelPtr->getSubNodes()["tdme.node.optimized"] = optimizedNode;

	// clone materials with diffuse textures that we like to keep
	for (const auto& [materialId, material]: modelPtr->getMaterials()) {
		bool keepDiffuseTexture = false;
		for (const auto& excludeDiffuseTextureFileNamePattern: excludeDiffuseTextureFileNamePatterns) {
			if (StringTools::startsWith(material->getSpecularMaterialProperties()->getDiffuseTextureFileName(), excludeDiffuseTextureFileNamePattern) == true) {
				keepDiffuseTexture = true;
				break;
			}
		}
		if (keepDiffuseTexture == false) continue;
		optimizedModelPtr->getMaterials()[material->getId()] = cloneMaterial(material);
	}

	// create optimized material
	auto optimizedMaterial = make_unique<Material>("tdme.material.optimized");
	{
		optimizedMaterial->getSpecularMaterialProperties()->setDiffuseTexture(diffuseAtlas.getAtlasTexture());
		optimizedMaterial->getSpecularMaterialProperties()->setTextureAtlasSize(diffuseAtlas.getAtlasTexture()->getAtlasSize());
		optimizedMaterial->getSpecularMaterialProperties()->setDiffuseTextureTransparency(false);
		optimizedMaterial->getSpecularMaterialProperties()->setDiffuseTextureMaskedTransparency(false);
		Vector4 optimizedMaterialEmission(0.0f, 0.0f, 0.0f, 0.0f);
		Vector4 optimizedMaterialAmbient(0.0f, 0.0f, 0.0f, 0.0f);
		Vector4 optimizedMaterialDiffuse(0.0f, 0.0f, 0.0f, 0.0f);
		Vector4 optimizedMaterialSpecular(0.0f, 0.0f, 0.0f, 0.0f);
		float optimizedMaterialShininess = 0.0f;
		for (const auto& [atlasMaterialsId, material]: atlasMaterials) {
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
	}

	// also have a material with masked transparency
	auto optimizedMaterialMaskedTransparency = unique_ptr<Material>(cloneMaterial(optimizedMaterial.get(), "tdme.material.optimized.maskedtransparency"));
	optimizedMaterialMaskedTransparency->getSpecularMaterialProperties()->setDiffuseTextureTransparency(true);
	optimizedMaterialMaskedTransparency->getSpecularMaterialProperties()->setDiffuseTextureMaskedTransparency(true);

	// also have a material with transparency
	auto optimizedMaterialTransparency = unique_ptr<Material>(cloneMaterial(optimizedMaterial.get(), "tdme.material.optimized.transparency"));
	optimizedMaterialTransparency->getSpecularMaterialProperties()->setDiffuseTextureTransparency(true);

	// now optimize into our optimized modelPtr
	for (const auto& [subNodeId, subNode]: modelPtr->getSubNodes()) {
		if ((modelPtr->hasSkinning() == true && subNode->getSkinning() != nullptr) ||
			(modelPtr->hasSkinning() == false && subNode->isJoint() == false)) {
			optimizeNode(subNode, optimizedModelPtr.get(), diffuseAtlas.getAtlasTexture()->getAtlasSize(), diffuseTextureAtlasIndices, excludeDiffuseTextureFileNamePatterns);
			if (modelPtr->hasSkinning() == true) {
				auto skinning = subNode->getSkinning();
				auto optimizedSkinning = new Skinning();
				optimizedSkinning->setWeights(skinning->getWeights());
				optimizedSkinning->setJoints(skinning->getJoints());
				optimizedSkinning->setVerticesJointsWeights(skinning->getVerticesJointsWeights());
				optimizedModelPtr->getNodes()["tdme.node.optimized"]->setSkinning(optimizedSkinning);
			}
		}
		cloneNode(subNode, optimizedModelPtr.get(), nullptr, false);
	}

	// set up materials
	{
		auto optimizedFacesEntity = optimizedModelPtr->getNodes()["tdme.node.optimized"]->getFacesEntity("tdme.facesentity.optimized");
		if (optimizedFacesEntity != nullptr) {
			optimizedModelPtr->getMaterials()[optimizedMaterial->getId()] = optimizedMaterial.get();
			optimizedFacesEntity->setMaterial(optimizedMaterial.release());
		}
	}
	{
		auto optimizedFacesEntityMaskedTransparency = optimizedModelPtr->getNodes()["tdme.node.optimized"]->getFacesEntity("tdme.facesentity.optimized.maskedtransparency");
		if (optimizedFacesEntityMaskedTransparency != nullptr) {
			optimizedModelPtr->getMaterials()[optimizedMaterialMaskedTransparency->getId()] = optimizedMaterialMaskedTransparency.get();
			optimizedFacesEntityMaskedTransparency->setMaterial(optimizedMaterialMaskedTransparency.release());
		}
	}
	{
		auto optimizedFacesEntityTransparency = optimizedModelPtr->getNodes()["tdme.node.optimized"]->getFacesEntity("tdme.facesentity.optimized.transparency");
		if (optimizedFacesEntityTransparency != nullptr) {
			optimizedModelPtr->getMaterials()[optimizedMaterialTransparency->getId()] = optimizedMaterialTransparency.get();
			optimizedFacesEntityTransparency->setMaterial(optimizedMaterialTransparency.release());
		}
	}

	// copy animation set up
	for (const auto& [animationSetupId, animationSetup]: modelPtr->getAnimationSetups()) {
		if (animationSetup->getOverlayFromNodeId().empty() == false) {
			optimizedModelPtr->addOverlayAnimationSetup(
				animationSetup->getId(),
				animationSetup->getOverlayFromNodeId(),
				animationSetup->getStartFrame(),
				animationSetup->getEndFrame(),
				animationSetup->isLoop(),
				animationSetup->getSpeed()
			);
		} else {
			optimizedModelPtr->addAnimationSetup(
				animationSetup->getId(),
				animationSetup->getStartFrame(),
				animationSetup->getEndFrame(),
				animationSetup->isLoop(),
				animationSetup->getSpeed()
			);
		}
	}

	// done
	return optimizedModelPtr.release();
}

void ModelTools::computeTangentsAndBitangents(Node* node)
{
	// without texture coordinates we cant compute tangents and bitangents
	if (node->getTextureCoordinates().empty() == true) {
		Console::println("ModelTools::computeTangentsAndBitangents(): " + node->getId() + ": No texture coordinates");
		return;
	}
	// see: https://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
	// what we need
	vector<Vector3> tangents;
	vector<Vector3> bitangents;
	// temporary variables
	Vector2 uv0;
	Vector2 uv1;
	Vector2 uv2;
	Vector3 deltaPos1;
	Vector3 deltaPos2;
	Vector2 deltaUV1;
	Vector2 deltaUV2;
	// create it
	auto facesEntities = node->getFacesEntities();
	const auto& vertices = node->getVertices();
	const auto& normals = node->getNormals();
	auto textureCoordinates = node->getTextureCoordinates();
	for (auto& faceEntity: facesEntities) {
		auto faces = faceEntity.getFaces();
		for (auto& face: faces) {
			// shortcuts for vertices
			auto verticesIndexes = face.getVertexIndices();
			auto v0 = vertices[verticesIndexes[0]];
			auto v1 = vertices[verticesIndexes[1]];
			auto v2 = vertices[verticesIndexes[2]];
			// shortcuts for UVs
			auto textureCoordinatesIndexes = face.getTextureCoordinateIndices();
			uv0.set(textureCoordinates[textureCoordinatesIndexes[0]].getArray());
			uv0.setY(1.0f - uv0.getY());
			uv1.set(textureCoordinates[textureCoordinatesIndexes[1]].getArray());
			uv1.setY(1.0f - uv1.getY());
			uv2.set(textureCoordinates[textureCoordinatesIndexes[2]].getArray());
			uv2.setY(1.0f - uv2.getY());
			// edges of the triangle : position delta
			deltaPos1.set(v1).sub(v0);
			deltaPos2.set(v2).sub(v0);
			// UV delta
			deltaUV1.set(uv1).sub(uv0);
			deltaUV2.set(uv2).sub(uv0);
			// compute tangent and bitangent
			auto r = 1.0f / (deltaUV1.getX() * deltaUV2.getY() - deltaUV1.getY() * deltaUV2.getX());
			auto tangent = deltaPos1.clone().scale(deltaUV2.getY()).sub(deltaPos2.clone().scale(deltaUV1.getY())).scale(r);
			auto bitangent = deltaPos2.clone().scale(deltaUV1.getX()).sub(deltaPos1.clone().scale(deltaUV2.getX())).scale(r);
			// set up tangent face indices
			face.setTangentIndices(tangents.size() + 0, tangents.size() + 1, tangents.size() + 2);
			// set up bitangent face indices
			face.setBitangentIndices(bitangents.size() + 0, bitangents.size() + 1, bitangents.size() + 2);
			// add to group tangents, bitangents
			tangents.push_back(tangent);
			tangents.push_back(tangent);
			tangents.push_back(tangent);
			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);
		}
		faceEntity.setFaces(faces);
	}
	node->setFacesEntities(facesEntities);

	// set up tangents and bitangents if we have any
	if (tangents.size() > 0 && bitangents.size() > 0) {
		// going further
		auto facesEntities = node->getFacesEntities();
		for (auto& faceEntity: facesEntities) {
			auto faces = faceEntity.getFaces();
			for (auto& face: faces) {
				for (auto i = 0; i < 3; i++) {
					auto normal = normals[face.getNormalIndices()[i]];
					auto& tangent = tangents[face.getTangentIndices()[i]];
					auto& bitangent = bitangents[face.getBitangentIndices()[i]];
					tangent.sub(normal.clone().scale(Vector3::computeDotProduct(normal, tangent))).normalize();
					if (Vector3::computeDotProduct(Vector3::computeCrossProduct(normal, tangent), bitangent) < 0.0f) {
						tangent.scale(-1.0f);
					}
					bitangent.normalize();
				}
			}
			faceEntity.setFaces(faces);
		}
		node->setFacesEntities(facesEntities);
		//
		node->setTangents(tangents);
		node->setBitangents(bitangents);
	}
}

void ModelTools::changeFrontFace(Node* node, bool applyToSubNodes) {
	auto facesEntities = node->getFacesEntities();
	for (auto& facesEntity: facesEntities) {
		auto faces = facesEntity.getFaces();
		for (auto& face: faces) face.changeFrontFace();
		facesEntity.setFaces(faces);
	}
	node->setFacesEntities(facesEntities);
	if (applyToSubNodes == true) {
		for (const auto& [subNodeId, subNode]: node->getSubNodes()) {
			changeFrontFace(subNode, true);
		}
	}
}

void ModelTools::changeFrontFace(Model* model) {
	for (const auto& [subNodeId, subNode]: model->getSubNodes()) {
		changeFrontFace(subNode, true);
	}
}
