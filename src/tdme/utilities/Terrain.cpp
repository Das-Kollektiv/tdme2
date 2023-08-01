#include <tdme/utilities/Terrain.h>

#include <array>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/ModelTools.h>

using std::array;
using std::map;
using std::set;
using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::utilities::Terrain;

using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::model::UpVector;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::LineSegment;
using tdme::engine::Rotation;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Matrix2D3x3;
using tdme::math::Vector2;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::ModelTools;

Texture* Terrain::createTerrainNavigationMap(float width, float depth, vector<float>& terrainHeightVector, float maxNavigationSlope) {
	auto terrainHeightVectorVerticesPerX = static_cast<int>(Math::ceil(width / STEP_SIZE));
	auto terreinHeightVectorVerticesPerZ = static_cast<int>(Math::ceil(depth / STEP_SIZE));
	//
	auto navigationMapTextureByteBuffer = ByteBuffer(terrainHeightVectorVerticesPerX * 2 * terreinHeightVectorVerticesPerZ * 2 * 3);
	for (auto z = 0; z < terreinHeightVectorVerticesPerZ * 2; z++) {
		for (auto x = 0; x < terrainHeightVectorVerticesPerX * 2; x++) {
			navigationMapTextureByteBuffer.put(0);
			navigationMapTextureByteBuffer.put(0);
			navigationMapTextureByteBuffer.put(0);
		}
	}
	//
	for (float z = 0.0f; z < depth; z+= STEP_SIZE) {
		for (float x = 0.0f; x < width; x+= STEP_SIZE) {

			auto terrainHeightVectorX = static_cast<int>(x / STEP_SIZE);
			auto terrainHeightVectorZ = static_cast<int>(z / STEP_SIZE);

			auto topNormal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX, terrainHeightVectorZ - 1);
			auto topLeftNormal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX - 1, terrainHeightVectorZ - 1);
			auto leftNormal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX - 1, terrainHeightVectorZ);
			auto normal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX, terrainHeightVectorZ);

			//
			{
				auto terrainSlopeTop = Math::abs(180.0f / 3.14f * Math::acos(Math::clamp(Vector3::computeDotProduct(topNormal, Vector3(0.0f, 1.0f, 0.0f)), -1.0f, 1.0f)));
				navigationMapTextureByteBuffer.setPosition((terrainHeightVectorZ * 2 * terrainHeightVectorVerticesPerX * 2) * 3 + (terrainHeightVectorX * 2 + 1) * 3);
				if (terrainSlopeTop > maxNavigationSlope) {
					navigationMapTextureByteBuffer.put(255);
					navigationMapTextureByteBuffer.put(0);
					navigationMapTextureByteBuffer.put(0);
				} else {
					navigationMapTextureByteBuffer.put(0);
					navigationMapTextureByteBuffer.put(255);
					navigationMapTextureByteBuffer.put(0);
				}
			}
			//
			{
				auto terrainSlopeTopLeft = Math::abs(180.0f / 3.14f * Math::acos(Math::clamp(Vector3::computeDotProduct(topLeftNormal, Vector3(0.0f, 1.0f, 0.0f)), -1.0f, 1.0f)));
				navigationMapTextureByteBuffer.setPosition((terrainHeightVectorZ * 2 * terrainHeightVectorVerticesPerX * 2) * 3 + terrainHeightVectorX * 2 * 3);
				if (terrainSlopeTopLeft > maxNavigationSlope) {
					navigationMapTextureByteBuffer.put(255);
					navigationMapTextureByteBuffer.put(0);
					navigationMapTextureByteBuffer.put(0);
				} else {
					navigationMapTextureByteBuffer.put(0);
					navigationMapTextureByteBuffer.put(255);
					navigationMapTextureByteBuffer.put(0);
				}
			}
			//
			{
				auto terrainSlopeLeft = Math::abs(180.0f / 3.14f * Math::acos(Math::clamp(Vector3::computeDotProduct(leftNormal, Vector3(0.0f, 1.0f, 0.0f)), -1.0f, 1.0f)));
				navigationMapTextureByteBuffer.setPosition(((terrainHeightVectorZ * 2 + 1) * terrainHeightVectorVerticesPerX * 2) * 3 + terrainHeightVectorX * 2 * 3);
				if (terrainSlopeLeft > maxNavigationSlope) {
					navigationMapTextureByteBuffer.put(255);
					navigationMapTextureByteBuffer.put(0);
					navigationMapTextureByteBuffer.put(0);
				} else {
					navigationMapTextureByteBuffer.put(0);
					navigationMapTextureByteBuffer.put(255);
					navigationMapTextureByteBuffer.put(0);
				}
			}
			//
			{
				auto terrainSlope = Math::abs(180.0f / 3.14f * Math::acos(Math::clamp(Vector3::computeDotProduct(normal, Vector3(0.0f, 1.0f, 0.0f)), -1.0f, 1.0f)));
				navigationMapTextureByteBuffer.setPosition(((terrainHeightVectorZ * 2 + 1) * terrainHeightVectorVerticesPerX * 2) * 3 + (terrainHeightVectorX * 2 + 1) * 3);
				if (terrainSlope > maxNavigationSlope) {
					navigationMapTextureByteBuffer.put(255);
					navigationMapTextureByteBuffer.put(0);
					navigationMapTextureByteBuffer.put(0);
				} else {
					navigationMapTextureByteBuffer.put(0);
					navigationMapTextureByteBuffer.put(255);
					navigationMapTextureByteBuffer.put(0);
				}
			}
		}
	}
	//
	auto navigationMapTexture = new Texture(
		"terrain-navigationmaptexture",
		Texture::TEXTUREDEPTH_RGB,
		Texture::TEXTUREFORMAT_RGB,
		terrainHeightVectorVerticesPerX * 2,
		terreinHeightVectorVerticesPerZ * 2,
		terrainHeightVectorVerticesPerX * 2,
		terreinHeightVectorVerticesPerZ * 2,
		Texture::TEXTUREFORMAT_RGB,
		navigationMapTextureByteBuffer
	);
	navigationMapTexture->acquireReference();
	//
	return navigationMapTexture;
}

void Terrain::createTerrainModels(float width, float depth, float y, vector<float>& terrainHeightVector, BoundingBox& terrainBoundingBox, vector<Model*>& terrainModels, bool createLODLevels)
{
	vector<unordered_map<int, int>> partitionTerrainTriangles;
	vector<vector<Vector3>> partitionTerrainVertices;
	vector<vector<Vector3>> partitionTerrainNormals;
	vector<vector<array<int, 6>>> partitionTerrainFaces;
	vector<vector<int32_t>> partitionLod1Indices;
	vector<vector<int32_t>> partitionLod2Indices;
	vector<vector<int32_t>> partitionLod3Indices;
	auto partitionsX = static_cast<int>(Math::ceil(width / PARTITION_SIZE));
	auto partitionsZ = static_cast<int>(Math::ceil(depth / PARTITION_SIZE));
	auto partitionCount = partitionsX * partitionsZ;
	partitionTerrainTriangles.resize(partitionCount);
	partitionTerrainVertices.resize(partitionCount);
	partitionTerrainNormals.resize(partitionCount);
	partitionTerrainFaces.resize(partitionCount);
	if (terrainHeightVector.empty() == true) {
		for (float z = 0.0f; z < depth; z+= STEP_SIZE) {
			for (float x = 0.0f; x < width; x+= STEP_SIZE) {
				terrainHeightVector.push_back(y);
			}
		}
	}
	auto terrainHeightVectorVerticesPerX = static_cast<int>(Math::ceil(width / STEP_SIZE));
	auto terreinHeightVectorVerticesPerZ = static_cast<int>(Math::ceil(depth / STEP_SIZE));
	for (float z = 0.0f; z < depth; z+= STEP_SIZE) {
		for (float x = 0.0f; x < width; x+= STEP_SIZE) {

			auto partitionX = static_cast<int>(x / PARTITION_SIZE);
			auto partitionZ = static_cast<int>(z / PARTITION_SIZE);
			auto partitionIdx = partitionZ * partitionsX + partitionX;

			auto& terrainVertices = partitionTerrainVertices[partitionIdx];
			auto& terrainNormals = partitionTerrainNormals[partitionIdx];
			auto& terrainFaces = partitionTerrainFaces[partitionIdx];
			auto& terrainTriangles = partitionTerrainTriangles[partitionIdx];

			int normalIdx = terrainNormals.size();
			int vertexIdx = terrainVertices.size();

			auto terrainHeightVectorX = static_cast<int>(x / STEP_SIZE);
			auto terrainHeightVectorZ = static_cast<int>(z / STEP_SIZE);

			Vector3 topVertex;
			Vector3 topLeftVertex;
			Vector3 leftVertex;
			Vector3 vertex;

			getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX, terrainHeightVectorZ - 1, topVertex);
			getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX - 1, terrainHeightVectorZ - 1, topLeftVertex);
			getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX - 1, terrainHeightVectorZ, leftVertex);
			getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX, terrainHeightVectorZ, vertex);

			terrainVertices.push_back(topVertex);
			terrainVertices.push_back(topLeftVertex);
			terrainVertices.push_back(leftVertex);
			terrainVertices.push_back(vertex);

			auto topNormal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX, terrainHeightVectorZ - 1);
			auto topLeftNormal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX - 1, terrainHeightVectorZ - 1);
			auto leftNormal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX - 1, terrainHeightVectorZ);
			auto normal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX, terrainHeightVectorZ);

			terrainNormals.push_back(topNormal);
			terrainNormals.push_back(topLeftNormal);
			terrainNormals.push_back(leftNormal);
			terrainNormals.push_back(normal);

			terrainFaces.push_back(
				{
					vertexIdx + 0,
					vertexIdx + 1,
					vertexIdx + 2,
					normalIdx + 0,
					normalIdx + 1,
					normalIdx + 2
				}
			);
			terrainFaces.push_back(
				{
					vertexIdx + 2,
					vertexIdx + 3,
					vertexIdx + 0,
					normalIdx + 2,
					normalIdx + 3,
					normalIdx + 0
				}
			);
			terrainTriangles[terrainHeightVectorZ]+= 2;
		}
	}
	auto partitionIdx = 0;
	for (auto partitionIdx = 0; partitionIdx < partitionCount; partitionIdx++) {
		if (partitionTerrainFaces[partitionIdx].empty() == true) continue;
		auto modelId = "terrain." + to_string(partitionIdx);
		auto terrainModel = new Model(modelId, modelId, UpVector::Y_UP, RotationOrder::ZYX, nullptr);
		auto terrainMaterial = new Material("terrain");
		terrainMaterial->setSpecularMaterialProperties(new SpecularMaterialProperties());
		// TODO: Fix me! The textures seem to be much too dark
		terrainMaterial->getSpecularMaterialProperties()->setAmbientColor(Color4(2.0f, 2.0f, 2.0f, 0.0f));
		terrainMaterial->getSpecularMaterialProperties()->setDiffuseColor(Color4(1.0f, 1.0f, 1.0f, 1.0f));
		terrainMaterial->getSpecularMaterialProperties()->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 0.0f));
		terrainModel->getMaterials()[terrainMaterial->getId()] = terrainMaterial;
		auto terrainNode = new Node(terrainModel, nullptr, "terrain", "terrain");
		FacesEntity nodeFacesEntityTerrain(terrainNode, "terrain.facesentity");
		nodeFacesEntityTerrain.setMaterial(terrainMaterial);
		vector<FacesEntity> nodeFacesEntities;
		vector<Face> nodeFaces;
		auto trianglesPerX = partitionTerrainTriangles[partitionIdx].begin()->second;
		auto trianglesPerZ = partitionTerrainTriangles[partitionIdx].size();
		for (auto& faceIndices: partitionTerrainFaces[partitionIdx]) {
			nodeFaces.emplace_back(
				terrainNode,
				faceIndices[0],
				faceIndices[1],
				faceIndices[2],
				faceIndices[3],
				faceIndices[4],
				faceIndices[5]
			);
		};

		// create LOD levels?
		if (createLODLevels == true) {
			// lod1
			{
				vector<int32_t> lod1Indices;
				const auto& facesIndices = partitionTerrainFaces[partitionIdx];
				auto finishedZ = false;
				for (auto z = 0; finishedZ == false && z < trianglesPerZ; z+= 4) {
					if (z > trianglesPerZ - 4) {
						z = trianglesPerZ - 4;
						finishedZ = true;
					}
					auto finishedX = false;
					for (auto x = 0; finishedX == false && x < trianglesPerX; x+= 8) {
						if (x > trianglesPerX - 8) {
							x = trianglesPerX - 8;
							finishedX = true;
						}
						lod1Indices.push_back(facesIndices[z * trianglesPerX + x + 6][0]); 			// top
						lod1Indices.push_back(facesIndices[z * trianglesPerX + x][1]);				// top left
						lod1Indices.push_back(facesIndices[(z + 3) * trianglesPerX + x][2]);		// left
						lod1Indices.push_back(facesIndices[(z + 3) * trianglesPerX + x][2]);		// left
						lod1Indices.push_back(facesIndices[(z + 3) * trianglesPerX + x + 7][1]);	// vertex
						lod1Indices.push_back(facesIndices[z * trianglesPerX + x + 6][0]); 			// top
					}
				}
				nodeFacesEntityTerrain.setLOD1Indices(lod1Indices);
				nodeFacesEntityTerrain.setLOD1Distance(64.0f);
			}

			// lod2
			{
				vector<int32_t> lod2Indices;
				const auto& facesIndices = partitionTerrainFaces[partitionIdx];
				auto finishedZ = false;
				for (auto z = 0; finishedZ == false && z < trianglesPerZ; z+= 8) {
					if (z > trianglesPerZ - 8) {
						z = trianglesPerZ - 8;
						finishedZ = true;
					}
					auto finishedX = false;
					for (auto x = 0; finishedX == false && x < trianglesPerX; x+= 16) {
						if (x > trianglesPerX - 16) {
							x = trianglesPerX - 16;
							finishedX = true;
						}
						lod2Indices.push_back(facesIndices[z * trianglesPerX + x + 14][0]);			// top
						lod2Indices.push_back(facesIndices[z * trianglesPerX + x][1]);				// top left
						lod2Indices.push_back(facesIndices[(z + 7) * trianglesPerX + x][2]);		// left
						lod2Indices.push_back(facesIndices[(z + 7) * trianglesPerX + x][2]);		// left
						lod2Indices.push_back(facesIndices[(z + 7) * trianglesPerX + x + 15][1]);	// vertex
						lod2Indices.push_back(facesIndices[z * trianglesPerX + x + 14][0]); 		// top
					}
				}
				nodeFacesEntityTerrain.setLOD2Indices(lod2Indices);
				nodeFacesEntityTerrain.setLOD2Distance(128.0f);
			}

			// lod3
			{
				vector<int32_t> lod3Indices;
				const auto& facesIndices = partitionTerrainFaces[partitionIdx];
				auto finishedZ = false;
				for (auto z = 0; finishedZ == false && z < trianglesPerZ; z+= 16) {
					if (z > trianglesPerZ - 16) {
						z = trianglesPerZ - 16;
						finishedZ = true;
					}
					auto finishedX = false;
					for (auto x = 0; finishedX == false && x < trianglesPerX; x+= 32) {
						if (x > trianglesPerX - 32) {
							x = trianglesPerX - 32;
							finishedX = true;
						}
						lod3Indices.push_back(facesIndices[z * trianglesPerX + x + 30][0]); 		// top
						lod3Indices.push_back(facesIndices[z * trianglesPerX + x][1]);				// top left
						lod3Indices.push_back(facesIndices[(z + 15) * trianglesPerX + x][2]);		// left
						lod3Indices.push_back(facesIndices[(z + 15) * trianglesPerX + x][2]);		// left
						lod3Indices.push_back(facesIndices[(z + 15) * trianglesPerX + x + 31][1]);	// vertex
						lod3Indices.push_back(facesIndices[z * trianglesPerX + x + 30][0]); 		// top
					}
				}
				nodeFacesEntityTerrain.setLOD3Indices(lod3Indices);
				nodeFacesEntityTerrain.setLOD3Distance(192.0f);
			}
		}

		nodeFacesEntityTerrain.setFaces(nodeFaces);
		nodeFacesEntities.push_back(nodeFacesEntityTerrain);
		terrainNode->setVertices(partitionTerrainVertices[partitionIdx]);
		terrainNode->setNormals(partitionTerrainNormals[partitionIdx]);
		terrainNode->setFacesEntities(nodeFacesEntities);
		terrainModel->getNodes()[terrainNode->getId()] = terrainNode;
		terrainModel->getSubNodes()[terrainNode->getId()] = terrainNode;
		terrainModel->invalidateBoundingBox();
		if (partitionIdx == 0) {
			terrainBoundingBox = *terrainModel->getBoundingBox();
		} else {
			terrainBoundingBox.extend(terrainModel->getBoundingBox());
		}
		ModelTools::createDefaultAnimation(terrainModel, 1);
		terrainModels.push_back(terrainModel);
	}
}

inline const Vector3 Terrain::computeTerrainVertexNormal(const vector<float>& terrainHeightVector, int verticesPerX, int verticesPerZ, int x, int z) {
	Vector3 vertexNormal;

	Vector3 vertex;
	auto haveVertex = getTerrainVertex(terrainHeightVector, verticesPerX, verticesPerZ, x, z - 1, vertex);
	if (haveVertex == false) return Vector3(0.0f, 1.0f, 0.0f);

	Vector3 topVertex;
	Vector3 topLeftVertex;
	Vector3 leftVertex;
	Vector3 bottomVertex;
	Vector3 rightVertex;
	Vector3 bottomRightVertex;

	auto haveTopVertex = getTerrainVertex(terrainHeightVector, verticesPerX, verticesPerZ, x, z - 1, topVertex);
	auto haveTopLeftVertex = getTerrainVertex(terrainHeightVector, verticesPerX, verticesPerZ, x - 1, z - 1, topLeftVertex);
	auto haveLeftVertex = getTerrainVertex(terrainHeightVector, verticesPerX, verticesPerZ, x - 1, z, leftVertex);
	auto haveBottomVertex = getTerrainVertex(terrainHeightVector, verticesPerX, verticesPerZ, x, z + 1, bottomVertex);
	auto haveRightVertex = getTerrainVertex(terrainHeightVector, verticesPerX, verticesPerZ, x + 1, z, rightVertex);
	auto haveBottomRightVertex = getTerrainVertex(terrainHeightVector, verticesPerX, verticesPerZ, x + 1, z + 1, bottomRightVertex);

	Vector3 triangleNormal;
	int normalCount = 0;
	if (haveTopVertex == true && haveTopLeftVertex == true) {
		triangleNormal = ModelTools::computeNormal(
			{
				topVertex,
				topLeftVertex,
				vertex
			}
		);
		vertexNormal.add(triangleNormal);
		normalCount++;
	}
	if (haveTopLeftVertex == true && haveLeftVertex == true) {
		triangleNormal = ModelTools::computeNormal(
			{
				topLeftVertex,
				leftVertex,
				vertex
			}
		);
		vertexNormal.add(triangleNormal);
		normalCount++;
	}
	if (haveLeftVertex == true && haveBottomVertex == true) {
		triangleNormal = ModelTools::computeNormal(
			{
				leftVertex,
				bottomVertex,
				vertex
			}
		);
		vertexNormal.add(triangleNormal);
		normalCount++;
	}
	if (haveBottomVertex == true && haveBottomRightVertex == true) {
		triangleNormal = ModelTools::computeNormal(
			{
				bottomVertex,
				bottomRightVertex,
				vertex
			}
		);
		vertexNormal.add(triangleNormal);
		normalCount++;
	}
	if (haveBottomRightVertex == true && haveRightVertex == true) {
		triangleNormal = ModelTools::computeNormal(
			{
				bottomRightVertex,
				rightVertex,
				vertex
			}
		);
		vertexNormal.add(triangleNormal);
		normalCount++;
	}
	if (haveRightVertex == true && haveTopVertex == true) {
		triangleNormal = ModelTools::computeNormal(
			{
				rightVertex,
				topVertex,
				vertex
			}
		);
		vertexNormal.add(triangleNormal);
		normalCount++;
	}
	if (normalCount > 0) {
		return vertexNormal.normalize();
	}
	Console::println("Terrain::computeTerrainVertexNormal(): no vertex normal available: normal count == 0");
	return vertexNormal.set(0.0f, 1.0f, 0.0f);
}

void Terrain::applyBrushToTerrainModels(
	BoundingBox& terrainBoundingBox,
	vector<Model*>& terrainModels,
	vector<float>& terrainHeightVector,
	const Vector3& brushCenterPosition,
	Texture* brushTexture,
	float brushScale,
	float brushStrength,
	BrushOperation brushOperation,
	float brushHeight
) {
	// check if we have a texture
	if (brushTexture == nullptr) return;
	// check if we have a model
	if (terrainModels.empty() == true) return;

	// apply brush
	vector<vector<Vector3>> partitionTerrainVertices;
	vector<vector<Vector3>> partitionTerrainNormals;
	partitionTerrainVertices.resize(terrainModels.size());
	partitionTerrainNormals.resize(terrainModels.size());
	auto partitionsX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / PARTITION_SIZE));
	auto terrainHeightVectorVerticesPerX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / STEP_SIZE));
	auto terreinHeightVectorVerticesPerZ = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getZ() / STEP_SIZE));

	// water
	if (brushOperation == BRUSHOPERATION_WATER_ADD) return;

	// other operations
	auto textureData = brushTexture->getRGBTextureData();
	auto textureWidth = brushTexture->getTextureWidth();
	auto textureHeight = brushTexture->getTextureHeight();
	auto textureBytePerPixel = brushTexture->getRGBDepthBitsPerPixel() == 32?4:3;
	for (auto z = 0.0f; z < textureHeight * brushScale; z+= STEP_SIZE) {
		auto brushPosition =
			brushCenterPosition.
			clone().
			sub(
				Vector3(
					(static_cast<float>(textureWidth) * brushScale) / 2.0f,
					0.0f,
					(static_cast<float>(textureHeight) * brushScale) / 2.0f
				)
			).
			add(
				Vector3(
					0.0f,
					0.0f,
					z
				)
			);
		for (auto x = 0.0f; x < textureWidth * brushScale; x+= STEP_SIZE) {
			auto textureX = static_cast<int>(x / brushScale);
			auto textureY = static_cast<int>(z / brushScale);
			auto red = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 0);
			auto green = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 1);
			auto blue = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 2);
			auto alpha = textureBytePerPixel == 3?255:textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 3);
			auto appliedStrength = (static_cast<float>(red) + static_cast<float>(green) + static_cast<float>(blue)) / (255.0f * 3.0f) * brushStrength;
			auto terrainHeightVectorX = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / STEP_SIZE);
			auto terrainHeightVectorZ = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / STEP_SIZE);
			if (terrainHeightVectorX < 0 || terrainHeightVectorX >= terrainHeightVectorVerticesPerX ||
				terrainHeightVectorZ < 0 || terrainHeightVectorZ >= terreinHeightVectorVerticesPerZ) {
				brushPosition.add(
					Vector3(
						STEP_SIZE,
						0.0f,
						0.0f
					)
				);
				continue;
			}
			auto vertexIdx = terrainHeightVectorZ * terrainHeightVectorVerticesPerX + terrainHeightVectorX;
			auto terrainVertexHeight = terrainHeightVector[vertexIdx];
			switch(brushOperation) {
				case BRUSHOPERATION_ADD:
					terrainVertexHeight+= appliedStrength;
					break;
				case BRUSHOPERATION_SUBTRACT:
					terrainVertexHeight-= appliedStrength;
					break;
				case BRUSHOPERATION_FLATTEN:
					terrainVertexHeight = terrainVertexHeight * (1.0f - Math::clamp(appliedStrength, 0.0f, 1.0f)) + brushHeight * Math::clamp(appliedStrength, 0.0f, 1.0f);
					break;
				case BRUSHOPERATION_DELETE:
					terrainVertexHeight = terrainVertexHeight * (1.0f - Math::clamp(appliedStrength, 0.0f, 1.0f)) + 0.0f * Math::clamp(appliedStrength, 0.0f, 1.0f);
					break;
				case BRUSHOPERATION_SMOOTH:
					auto terrainVertexHeightNeighbours = 0.0f;
					auto terrainVertexHeightNeighbourCount = 0;
					Vector3 topVertex;
					Vector3 leftVertex;
					Vector3 bottomVertex;
					Vector3 rightVertex;
					auto haveTopVertex = getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX, terrainHeightVectorZ - 1, topVertex);
					auto haveLeftVertex = getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX - 1, terrainHeightVectorZ, leftVertex);
					auto haveBottomVertex = getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX, terrainHeightVectorZ + 1, bottomVertex);
					auto haveRightVertex = getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX + 1, terrainHeightVectorZ, rightVertex);
					if (haveTopVertex == true) {
						terrainVertexHeightNeighbourCount++;
						terrainVertexHeightNeighbours+= topVertex[1];
					}
					if (haveLeftVertex == true) {
						terrainVertexHeightNeighbourCount++;
						terrainVertexHeightNeighbours+= leftVertex[1];
					}
					if (haveBottomVertex == true) {
						terrainVertexHeightNeighbourCount++;
						terrainVertexHeightNeighbours+= bottomVertex[1];
					}
					if (haveRightVertex == true) {
						terrainVertexHeightNeighbourCount++;
						terrainVertexHeightNeighbours+= rightVertex[1];
					}
					if (terrainVertexHeightNeighbourCount > 0) {
						auto terrainVertexHeightSmoothed = terrainVertexHeightNeighbours / static_cast<float>(terrainVertexHeightNeighbourCount);
						terrainVertexHeight = terrainVertexHeight * (1.0f - Math::clamp(appliedStrength, 0.0f, 1.0f)) + terrainVertexHeightSmoothed * Math::clamp(appliedStrength, 0.0f, 1.0f);
					}
					break;
			}
			terrainHeightVector[vertexIdx] = terrainVertexHeight;

			// original
			{
				auto _brushPosition = brushPosition;
				auto partitionX = static_cast<int>((_brushPosition.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
				auto partitionZ = static_cast<int>((_brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
				auto partitionIdx = partitionZ * partitionsX + partitionX;
				auto terrainModel = partitionIdx < terrainModels.size()?terrainModels[partitionIdx]:nullptr;
				auto terrainNode = terrainModel != nullptr?terrainModel->getNodeById("terrain"):nullptr;

				auto terrainModelX = terrainNode != nullptr?static_cast<int>((_brushPosition.getX() - terrainModel->getBoundingBox()->getMin().getX()) / STEP_SIZE):-1;
				auto terrainModelZ = terrainNode != nullptr?static_cast<int>((_brushPosition.getZ() - terrainModel->getBoundingBox()->getMin().getZ()) / STEP_SIZE):-1;
				auto terrainModelVerticesPerZ = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getZ() / STEP_SIZE)):-1;
				auto terrainModelVerticesPerX = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getX() / STEP_SIZE)):-1;

				if (terrainNode != nullptr &&
					terrainModelX >= 0 &&
					terrainModelX < terrainModelVerticesPerX &&
					terrainModelZ >= 0 &&
					terrainModelZ < terrainModelVerticesPerZ) {
					if (partitionTerrainVertices[partitionIdx].empty() == true) {
						partitionTerrainVertices[partitionIdx] = terrainNode->getVertices();
					}
					auto& terrainVertices = partitionTerrainVertices[partitionIdx];
					auto vertexIdx = (terrainModelZ * terrainModelVerticesPerX * 4) + (terrainModelX * 4);
					terrainVertices[vertexIdx + 3][1] = terrainVertexHeight;
				}
			}

			// top
			{
				auto _brushPosition = brushPosition.clone().sub(Vector3(0.0f, 0.0f, -STEP_SIZE));
				auto partitionX = static_cast<int>((_brushPosition.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
				auto partitionZ = static_cast<int>((_brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
				auto partitionIdx = partitionZ * partitionsX + partitionX;
				auto terrainModel = partitionIdx < terrainModels.size()?terrainModels[partitionIdx]:nullptr;
				auto terrainNode = terrainModel != nullptr?terrainModel->getNodeById("terrain"):nullptr;

				auto terrainModelX = terrainNode != nullptr?static_cast<int>((_brushPosition.getX() - terrainModel->getBoundingBox()->getMin().getX()) / STEP_SIZE):-1;
				auto terrainModelZ = terrainNode != nullptr?static_cast<int>((_brushPosition.getZ() - terrainModel->getBoundingBox()->getMin().getZ()) / STEP_SIZE):-1;
				auto terrainModelVerticesPerZ = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getZ() / STEP_SIZE)):-1;
				auto terrainModelVerticesPerX = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getX() / STEP_SIZE)):-1;

				if (terrainNode != nullptr &&
					terrainModelX >= 0 &&
					terrainModelX < terrainModelVerticesPerX &&
					terrainModelZ >= 0 &&
					terrainModelZ < terrainModelVerticesPerZ) {
					if (partitionTerrainVertices[partitionIdx].empty() == true) {
						partitionTerrainVertices[partitionIdx] = terrainNode->getVertices();
					}
					auto& terrainVertices = partitionTerrainVertices[partitionIdx];
					auto vertexIdx = (terrainModelZ * terrainModelVerticesPerX * 4) + (terrainModelX * 4);
					terrainVertices[vertexIdx + 0][1] = terrainVertexHeight;
				}
			}

			// top, left
			{
				auto _brushPosition = brushPosition.clone().sub(Vector3(-STEP_SIZE, 0.0f, -STEP_SIZE));
				auto partitionX = static_cast<int>((_brushPosition.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
				auto partitionZ = static_cast<int>((_brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
				auto partitionIdx = partitionZ * partitionsX + partitionX;
				auto terrainModel = partitionIdx < terrainModels.size()?terrainModels[partitionIdx]:nullptr;
				auto terrainNode = terrainModel != nullptr?terrainModel->getNodeById("terrain"):nullptr;

				auto terrainModelX = terrainNode != nullptr?static_cast<int>((_brushPosition.getX() - terrainModel->getBoundingBox()->getMin().getX()) / STEP_SIZE):-1;
				auto terrainModelZ = terrainNode != nullptr?static_cast<int>((_brushPosition.getZ() - terrainModel->getBoundingBox()->getMin().getZ()) / STEP_SIZE):-1;
				auto terrainModelVerticesPerZ = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getZ() / STEP_SIZE)):-1;
				auto terrainModelVerticesPerX = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getX() / STEP_SIZE)):-1;

				if (terrainNode != nullptr &&
					terrainModelX >= 0 &&
					terrainModelX < terrainModelVerticesPerX &&
					terrainModelZ >= 0 &&
					terrainModelZ < terrainModelVerticesPerZ) {
					if (partitionTerrainVertices[partitionIdx].empty() == true) {
						partitionTerrainVertices[partitionIdx] = terrainNode->getVertices();
					}
					auto& terrainVertices = partitionTerrainVertices[partitionIdx];
					auto vertexIdx = (terrainModelZ * terrainModelVerticesPerX * 4) + (terrainModelX * 4);
					terrainVertices[vertexIdx + 1][1] = terrainVertexHeight;
				}
			}

			// left
			{
				auto _brushPosition = brushPosition.clone().sub(Vector3(-STEP_SIZE, 0.0f, 0.0f));
				auto partitionX = static_cast<int>((_brushPosition.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
				auto partitionZ = static_cast<int>((_brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
				auto partitionIdx = partitionZ * partitionsX + partitionX;
				auto terrainModel = partitionIdx < terrainModels.size()?terrainModels[partitionIdx]:nullptr;
				auto terrainNode = terrainModel != nullptr?terrainModel->getNodeById("terrain"):nullptr;

				auto terrainModelX = terrainNode != nullptr?static_cast<int>((_brushPosition.getX() - terrainModel->getBoundingBox()->getMin().getX()) / STEP_SIZE):-1;
				auto terrainModelZ = terrainNode != nullptr?static_cast<int>((_brushPosition.getZ() - terrainModel->getBoundingBox()->getMin().getZ()) / STEP_SIZE):-1;
				auto terrainModelVerticesPerZ = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getZ() / STEP_SIZE)):-1;
				auto terrainModelVerticesPerX = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getX() / STEP_SIZE)):-1;

				if (terrainNode != nullptr &&
					terrainModelX >= 0 &&
					terrainModelX < terrainModelVerticesPerX &&
					terrainModelZ >= 0 &&
					terrainModelZ < terrainModelVerticesPerZ) {
					if (partitionTerrainVertices[partitionIdx].empty() == true) {
						partitionTerrainVertices[partitionIdx] = terrainNode->getVertices();
					}
					auto& terrainVertices = partitionTerrainVertices[partitionIdx];
					auto vertexIdx = (terrainModelZ * terrainModelVerticesPerX * 4) + (terrainModelX * 4);
					terrainVertices[vertexIdx + 2][1] = terrainVertexHeight;
				}
			}

			//
			brushPosition.add(
				Vector3(
					STEP_SIZE,
					0.0f,
					0.0f
				)
			);
		}
	}

	// normals
	for (auto z = -STEP_SIZE * 8.0f; z < textureHeight * brushScale + STEP_SIZE * 16.0f; z+= STEP_SIZE) {
		auto brushPosition =
			brushCenterPosition.
			clone().
			sub(
				Vector3(
					(static_cast<float>(textureWidth) * brushScale) / 2.0f,
					0.0f,
					(static_cast<float>(textureHeight) * brushScale) / 2.0f
				)
			).
			add(
				Vector3(
					-STEP_SIZE * 8.0f,
					0.0f,
					z
				)
			);
		for (auto x = -STEP_SIZE * 8.0f; x < textureWidth * brushScale + STEP_SIZE * 16.0f; x+= STEP_SIZE) {
			auto partitionX = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
			auto partitionZ = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
			auto partitionIdx = partitionZ * partitionsX + partitionX;
			auto terrainModel = partitionIdx < terrainModels.size()?terrainModels[partitionIdx]:nullptr;
			auto terrainNode = terrainModel != nullptr?terrainModel->getNodeById("terrain"):nullptr;

			auto terrainHeightVectorX = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / STEP_SIZE) + 1;
			auto terrainHeightVectorZ = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / STEP_SIZE) + 1;
			auto terrainModelX = terrainNode != nullptr?static_cast<int>((brushPosition.getX() - terrainModel->getBoundingBox()->getMin().getX()) / STEP_SIZE):-1;
			auto terrainModelZ = terrainNode != nullptr?static_cast<int>((brushPosition.getZ() - terrainModel->getBoundingBox()->getMin().getZ()) / STEP_SIZE):-1;
			auto terrainModelVerticesPerZ = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getZ() / STEP_SIZE)):-1;
			auto terrainModelVerticesPerX = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getX() / STEP_SIZE)):-1;

			if (terrainNode != nullptr &&
				terrainModelX >= 0 &&
				terrainModelX < terrainModelVerticesPerX &&
				terrainModelZ >= 0 &&
				terrainModelZ < terrainModelVerticesPerZ) {
				if (partitionTerrainNormals[partitionIdx].empty() == true) {
					partitionTerrainNormals[partitionIdx] = terrainNode->getNormals();
				}
				auto& terrainNormals = partitionTerrainNormals[partitionIdx];

				auto topNormal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX, terrainHeightVectorZ - 1);
				auto topLeftNormal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX - 1, terrainHeightVectorZ - 1);
				auto leftNormal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX - 1, terrainHeightVectorZ);
				auto normal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX, terrainHeightVectorZ);
				auto normalIdx = (terrainModelZ * terrainModelVerticesPerX * 4) + (terrainModelX * 4);

				terrainNormals[normalIdx + 0] = topNormal;
				terrainNormals[normalIdx + 1] = topLeftNormal;
				terrainNormals[normalIdx + 2] = leftNormal;
				terrainNormals[normalIdx + 3] = normal;
			}

			//
			brushPosition.add(
				Vector3(
					STEP_SIZE,
					0.0f,
					0.0f
				)
			);
		}
	}

	// set terrain model vertices
	{
		auto partitionIdx = 0;
		for (const auto& terrainVertices: partitionTerrainVertices) {
			if (terrainVertices.empty() == false) {
				auto terrainNode = terrainModels[partitionIdx]->getNodeById("terrain");
				if (terrainNode != nullptr) {
					terrainNode->setVertices(terrainVertices);
					terrainModels[partitionIdx]->invalidateBoundingBox();
				}
			}
			partitionIdx++;
		}
	}
	// set terrain model normals
	{
		auto partitionIdx = 0;
		for (const auto& terrainNormals: partitionTerrainNormals) {
			if (terrainNormals.empty() == false) {
				auto terrainNode = terrainModels[partitionIdx]->getNodeById("terrain");
				if (terrainNode != nullptr) {
					terrainNode->setNormals(terrainNormals);
					terrainModels[partitionIdx]->invalidateBoundingBox();
				}
			}
			partitionIdx++;
		}
	}
}

void Terrain::applyRampBrushToTerrainModels(
	BoundingBox& terrainBoundingBox, // TODO: constness
	vector<Model*>& terrainModels,
	vector<float>& terrainHeightVector,
	const Vector3& brushCenterPosition,
	Texture* brushTexture,
	float brushRotation,
	const Vector2& brushScale,
	float heightMin,
	float heightMax
) {
	// check if we have a texture
	if (brushTexture == nullptr) return;
	// check if we have a model
	if (terrainModels.empty() == true) return;

	// apply brush
	vector<vector<Vector3>> partitionTerrainVertices;
	vector<vector<Vector3>> partitionTerrainNormals;
	partitionTerrainVertices.resize(terrainModels.size());
	partitionTerrainNormals.resize(terrainModels.size());
	auto partitionsX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / PARTITION_SIZE));
	auto terrainHeightVectorVerticesPerX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / STEP_SIZE));
	auto terreinHeightVectorVerticesPerZ = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getZ() / STEP_SIZE));

	// texture
	auto textureData = brushTexture->getRGBTextureData();
	auto textureWidth = brushTexture->getTextureWidth();
	auto textureHeight = brushTexture->getTextureHeight();
	auto textureBytePerPixel = brushTexture->getRGBDepthBitsPerPixel() == 32?4:3;

	// brush texture matrix
	Matrix2D3x3 brushTextureMatrix;
	brushTextureMatrix.identity();
	brushTextureMatrix.translate(Vector2(static_cast<float>(textureWidth) / 2.0f, static_cast<float>(textureHeight) / 2.0f));
	brushTextureMatrix.multiply((Matrix2D3x3()).identity().scale(Vector2(1.0f / brushScale.getX(), 1.0f / brushScale.getY())));
	brushTextureMatrix.multiply((Matrix2D3x3()).identity().rotate(brushRotation));
	auto brushScaleMax = Math::max(brushScale.getX(), brushScale.getY());

	//
	for (auto z = -textureHeight * brushScaleMax * 2.0f; z < textureHeight * brushScaleMax * 2.0f; z+= STEP_SIZE) {
		auto brushPosition =
			brushCenterPosition.
			clone().
			sub(
				Vector3(
					static_cast<float>(textureWidth) * brushScaleMax * 2.0f,
					0.0f,
					0.0f
				)
			).
			add(
				Vector3(
					0.0f,
					0.0f,
					z
				)
			);
		for (auto x = -textureWidth * brushScaleMax * 2.0f; x < textureWidth * brushScaleMax * 2.0f; x+= STEP_SIZE) {
			auto texturePositionUntransformed = Vector2(x, z);
			auto texturePosition = brushTextureMatrix.multiply(texturePositionUntransformed);
			auto textureX = static_cast<int>(texturePosition.getX());
			auto textureY = static_cast<int>(texturePosition.getY());
			if (textureX < 0 || textureX >= textureWidth ||
				textureY < 0 || textureY >= textureHeight) {
				brushPosition.add(
					Vector3(
						STEP_SIZE,
						0.0f,
						0.0f
					)
				);
				continue;
			}
			auto red = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 0);
			auto green = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 1);
			auto blue = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 2);
			auto alpha = textureBytePerPixel == 3?255:textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 3);
			auto height = ((static_cast<float>(red) + static_cast<float>(green) + static_cast<float>(blue)) / (255.0f * 3.0f) * (heightMax - heightMin)) + heightMin;
			auto terrainHeightVectorX = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / STEP_SIZE);
			auto terrainHeightVectorZ = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / STEP_SIZE);
			if (terrainHeightVectorX < 0 || terrainHeightVectorX >= terrainHeightVectorVerticesPerX ||
				terrainHeightVectorZ < 0 || terrainHeightVectorZ >= terreinHeightVectorVerticesPerZ) {
				brushPosition.add(
					Vector3(
						STEP_SIZE,
						0.0f,
						0.0f
					)
				);
				continue;
			}
			auto terrainVertexHeight = 0.0f;
			{
				auto vertexIdx = terrainHeightVectorZ * terrainHeightVectorVerticesPerX + terrainHeightVectorX;
				terrainVertexHeight = terrainHeightVector[vertexIdx];
				terrainVertexHeight = height > terrainVertexHeight?height:terrainVertexHeight;
				terrainHeightVector[vertexIdx] = terrainVertexHeight;
			}

			// original
			{
				auto _brushPosition = brushPosition;
				auto partitionX = static_cast<int>((_brushPosition.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
				auto partitionZ = static_cast<int>((_brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
				auto partitionIdx = partitionZ * partitionsX + partitionX;
				auto terrainModel = partitionIdx < terrainModels.size()?terrainModels[partitionIdx]:nullptr;
				auto terrainNode = terrainModel != nullptr?terrainModel->getNodeById("terrain"):nullptr;

				auto terrainModelX = terrainNode != nullptr?static_cast<int>((_brushPosition.getX() - terrainModel->getBoundingBox()->getMin().getX()) / STEP_SIZE):-1;
				auto terrainModelZ = terrainNode != nullptr?static_cast<int>((_brushPosition.getZ() - terrainModel->getBoundingBox()->getMin().getZ()) / STEP_SIZE):-1;
				auto terrainModelVerticesPerZ = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getZ() / STEP_SIZE)):-1;
				auto terrainModelVerticesPerX = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getX() / STEP_SIZE)):-1;

				if (terrainNode != nullptr &&
					terrainModelX >= 0 &&
					terrainModelX < terrainModelVerticesPerX &&
					terrainModelZ >= 0 &&
					terrainModelZ < terrainModelVerticesPerZ) {
					if (partitionTerrainVertices[partitionIdx].empty() == true) {
						partitionTerrainVertices[partitionIdx] = terrainNode->getVertices();
					}
					auto& terrainVertices = partitionTerrainVertices[partitionIdx];
					auto vertexIdx = (terrainModelZ * terrainModelVerticesPerX * 4) + (terrainModelX * 4);
					terrainVertices[vertexIdx + 3][1] = terrainVertexHeight;
				}
			}

			// top
			{
				auto _brushPosition = brushPosition.clone().sub(Vector3(0.0f, 0.0f, -STEP_SIZE));
				auto partitionX = static_cast<int>((_brushPosition.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
				auto partitionZ = static_cast<int>((_brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
				auto partitionIdx = partitionZ * partitionsX + partitionX;
				auto terrainModel = partitionIdx < terrainModels.size()?terrainModels[partitionIdx]:nullptr;
				auto terrainNode = terrainModel != nullptr?terrainModel->getNodeById("terrain"):nullptr;

				auto terrainModelX = terrainNode != nullptr?static_cast<int>((_brushPosition.getX() - terrainModel->getBoundingBox()->getMin().getX()) / STEP_SIZE):-1;
				auto terrainModelZ = terrainNode != nullptr?static_cast<int>((_brushPosition.getZ() - terrainModel->getBoundingBox()->getMin().getZ()) / STEP_SIZE):-1;
				auto terrainModelVerticesPerZ = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getZ() / STEP_SIZE)):-1;
				auto terrainModelVerticesPerX = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getX() / STEP_SIZE)):-1;

				if (terrainNode != nullptr &&
					terrainModelX >= 0 &&
					terrainModelX < terrainModelVerticesPerX &&
					terrainModelZ >= 0 &&
					terrainModelZ < terrainModelVerticesPerZ) {
					if (partitionTerrainVertices[partitionIdx].empty() == true) {
						partitionTerrainVertices[partitionIdx] = terrainNode->getVertices();
					}
					auto& terrainVertices = partitionTerrainVertices[partitionIdx];
					auto vertexIdx = (terrainModelZ * terrainModelVerticesPerX * 4) + (terrainModelX * 4);
					terrainVertices[vertexIdx + 0][1] = terrainVertexHeight;
				}
			}

			// top, left
			{
				auto _brushPosition = brushPosition.clone().sub(Vector3(-STEP_SIZE, 0.0f, -STEP_SIZE));
				auto partitionX = static_cast<int>((_brushPosition.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
				auto partitionZ = static_cast<int>((_brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
				auto partitionIdx = partitionZ * partitionsX + partitionX;
				auto terrainModel = partitionIdx < terrainModels.size()?terrainModels[partitionIdx]:nullptr;
				auto terrainNode = terrainModel != nullptr?terrainModel->getNodeById("terrain"):nullptr;

				auto terrainModelX = terrainNode != nullptr?static_cast<int>((_brushPosition.getX() - terrainModel->getBoundingBox()->getMin().getX()) / STEP_SIZE):-1;
				auto terrainModelZ = terrainNode != nullptr?static_cast<int>((_brushPosition.getZ() - terrainModel->getBoundingBox()->getMin().getZ()) / STEP_SIZE):-1;
				auto terrainModelVerticesPerZ = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getZ() / STEP_SIZE)):-1;
				auto terrainModelVerticesPerX = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getX() / STEP_SIZE)):-1;

				if (terrainNode != nullptr &&
					terrainModelX >= 0 &&
					terrainModelX < terrainModelVerticesPerX &&
					terrainModelZ >= 0 &&
					terrainModelZ < terrainModelVerticesPerZ) {
					if (partitionTerrainVertices[partitionIdx].empty() == true) {
						partitionTerrainVertices[partitionIdx] = terrainNode->getVertices();
					}
					auto& terrainVertices = partitionTerrainVertices[partitionIdx];
					auto vertexIdx = (terrainModelZ * terrainModelVerticesPerX * 4) + (terrainModelX * 4);
					terrainVertices[vertexIdx + 1][1] = terrainVertexHeight;
				}
			}

			// left
			{
				auto _brushPosition = brushPosition.clone().sub(Vector3(-STEP_SIZE, 0.0f, 0.0f));
				auto partitionX = static_cast<int>((_brushPosition.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
				auto partitionZ = static_cast<int>((_brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
				auto partitionIdx = partitionZ * partitionsX + partitionX;
				auto terrainModel = partitionIdx < terrainModels.size()?terrainModels[partitionIdx]:nullptr;
				auto terrainNode = terrainModel != nullptr?terrainModel->getNodeById("terrain"):nullptr;

				auto terrainModelX = terrainNode != nullptr?static_cast<int>((_brushPosition.getX() - terrainModel->getBoundingBox()->getMin().getX()) / STEP_SIZE):-1;
				auto terrainModelZ = terrainNode != nullptr?static_cast<int>((_brushPosition.getZ() - terrainModel->getBoundingBox()->getMin().getZ()) / STEP_SIZE):-1;
				auto terrainModelVerticesPerZ = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getZ() / STEP_SIZE)):-1;
				auto terrainModelVerticesPerX = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getX() / STEP_SIZE)):-1;

				if (terrainNode != nullptr &&
					terrainModelX >= 0 &&
					terrainModelX < terrainModelVerticesPerX &&
					terrainModelZ >= 0 &&
					terrainModelZ < terrainModelVerticesPerZ) {
					if (partitionTerrainVertices[partitionIdx].empty() == true) {
						partitionTerrainVertices[partitionIdx] = terrainNode->getVertices();
					}
					auto& terrainVertices = partitionTerrainVertices[partitionIdx];
					auto vertexIdx = (terrainModelZ * terrainModelVerticesPerX * 4) + (terrainModelX * 4);
					terrainVertices[vertexIdx + 2][1] = terrainVertexHeight;
				}
			}

			//
			brushPosition.add(
				Vector3(
					STEP_SIZE,
					0.0f,
					0.0f
				)
			);
		}
	}

	// normals
	for (auto z = -textureHeight * brushScaleMax * 2.0f; z < textureHeight * brushScaleMax * 2.0f; z+= STEP_SIZE) {
		auto brushPosition =
			brushCenterPosition.
			clone().
			sub(
				Vector3(
					static_cast<float>(textureWidth) * brushScaleMax * 2.0f,
					0.0f,
					0.0f
				)
			).
			add(
				Vector3(
					0.0f,
					0.0f,
					z
				)
			);
		for (auto x = -textureWidth * brushScaleMax * 2.0f; x < textureWidth * brushScaleMax * 2.0f; x+= STEP_SIZE) {
			auto partitionX = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
			auto partitionZ = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
			auto partitionIdx = partitionZ * partitionsX + partitionX;
			auto terrainModel = partitionIdx < terrainModels.size()?terrainModels[partitionIdx]:nullptr;
			auto terrainNode = terrainModel != nullptr?terrainModel->getNodeById("terrain"):nullptr;

			auto terrainHeightVectorX = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / STEP_SIZE) + 1;
			auto terrainHeightVectorZ = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / STEP_SIZE) + 1;
			auto terrainModelX = terrainNode != nullptr?static_cast<int>((brushPosition.getX() - terrainModel->getBoundingBox()->getMin().getX()) / STEP_SIZE):-1;
			auto terrainModelZ = terrainNode != nullptr?static_cast<int>((brushPosition.getZ() - terrainModel->getBoundingBox()->getMin().getZ()) / STEP_SIZE):-1;
			auto terrainModelVerticesPerZ = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getZ() / STEP_SIZE)):-1;
			auto terrainModelVerticesPerX = terrainNode != nullptr?static_cast<int>(Math::ceil(terrainModel->getBoundingBox()->getDimensions().getX() / STEP_SIZE)):-1;

			if (terrainNode != nullptr &&
				terrainModelX >= 0 &&
				terrainModelX < terrainModelVerticesPerX &&
				terrainModelZ >= 0 &&
				terrainModelZ < terrainModelVerticesPerZ) {
				if (partitionTerrainNormals[partitionIdx].empty() == true) {
					partitionTerrainNormals[partitionIdx] = terrainNode->getNormals();
				}
				auto& terrainNormals = partitionTerrainNormals[partitionIdx];

				auto topNormal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX, terrainHeightVectorZ - 1);
				auto topLeftNormal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX - 1, terrainHeightVectorZ - 1);
				auto leftNormal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX - 1, terrainHeightVectorZ);
				auto normal = computeTerrainVertexNormal(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorX, terrainHeightVectorZ);
				auto normalIdx = (terrainModelZ * terrainModelVerticesPerX * 4) + (terrainModelX * 4);

				terrainNormals[normalIdx + 0] = topNormal;
				terrainNormals[normalIdx + 1] = topLeftNormal;
				terrainNormals[normalIdx + 2] = leftNormal;
				terrainNormals[normalIdx + 3] = normal;
			}

			//
			brushPosition.add(
				Vector3(
					STEP_SIZE,
					0.0f,
					0.0f
				)
			);
		}
	}

	// set terrain model vertices
	{
		auto partitionIdx = 0;
		for (const auto& terrainVertices: partitionTerrainVertices) {
			if (terrainVertices.empty() == false) {
				auto terrainNode = terrainModels[partitionIdx]->getNodeById("terrain");
				if (terrainNode != nullptr) {
					terrainNode->setVertices(terrainVertices);
					terrainModels[partitionIdx]->invalidateBoundingBox();
				}
			}
			partitionIdx++;
		}
	}
	// set terrain model normals
	{
		auto partitionIdx = 0;
		for (const auto& terrainNormals: partitionTerrainNormals) {
			if (terrainNormals.empty() == false) {
				auto terrainNode = terrainModels[partitionIdx]->getNodeById("terrain");
				if (terrainNode != nullptr) {
					terrainNode->setNormals(terrainNormals);
					terrainModels[partitionIdx]->invalidateBoundingBox();
				}
			}
			partitionIdx++;
		}
	}
}

bool Terrain::computeWaterPositionMap(BoundingBox& terrainBoundingBox, const vector<float>& terrainHeightVector, const Vector3& brushCenterPosition, float waterHeight, unordered_map<int, unordered_set<int>>& waterPositionMap) {
	auto terrainHeightVectorVerticesPerX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / STEP_SIZE));
	auto terreinHeightVectorVerticesPerZ = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getZ() / STEP_SIZE));

	auto brushPosition = brushCenterPosition;
	auto terrainHeightVectorXCenter = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / STEP_SIZE);
	auto terrainHeightVectorZCenter = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / STEP_SIZE);

	//
	waterPositionMap[terrainHeightVectorZCenter].insert(terrainHeightVectorXCenter);

	//
	Console::println("Terrain::determineWaterPositionSet: " + to_string(terrainHeightVectorXCenter) + " / " + to_string(terrainHeightVectorZCenter) + " @ " + to_string(waterHeight));

	//
	determineWaterXPositionSet(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, terrainHeightVectorXCenter, terrainHeightVectorZCenter, waterHeight, waterPositionMap[terrainHeightVectorZCenter]);

	//
	{
		auto zLast = 0;
		auto zMin = -1;
		while (true == true) {
			auto terrainHeightVectorZLast = terrainHeightVectorZCenter + zLast;
			auto terrainHeightVectorZ = terrainHeightVectorZCenter + zMin;
			for (auto zLastWaterXPosition: waterPositionMap[terrainHeightVectorZLast]) {
				if (determineWater(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, zLastWaterXPosition, terrainHeightVectorZ, waterHeight) == true) {
					determineWaterXPositionSet(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, zLastWaterXPosition, terrainHeightVectorZ, waterHeight, waterPositionMap[terrainHeightVectorZ]);
				}
			}
			if (waterPositionMap[terrainHeightVectorZ].empty() == true) break;
			zLast = zMin;
			zMin--;
		}
	}

	//
	{
		auto zLast = 0;
		auto zMax = 1;
		while (true == true) {
			auto terrainHeightVectorZLast = terrainHeightVectorZCenter + zLast;
			auto terrainHeightVectorZ = terrainHeightVectorZCenter + zMax;
			for (auto zLastWaterXPosition: waterPositionMap[terrainHeightVectorZLast]) {
				if (determineWater(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, zLastWaterXPosition, terrainHeightVectorZ, waterHeight) == true) {
					determineWaterXPositionSet(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, zLastWaterXPosition, terrainHeightVectorZ, waterHeight, waterPositionMap[terrainHeightVectorZ]);
				}
			}
			if (waterPositionMap[terrainHeightVectorZ].empty() == true) break;
			zLast = zMax;
			zMax++;
		}
	}

	{
		auto waterPositionMapCopy = waterPositionMap;
		auto zMin = waterPositionMap.begin()->first;
		auto zMax = waterPositionMap.begin()->first;
		do {
			waterPositionMapCopy = waterPositionMap;
			for (const auto& [z, xValues]: waterPositionMap) {
				for (auto x: xValues) {
					if (hasWaterPosition(waterPositionMap, x, z - 1) == false &&
						determineWater(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, x, z - 1, waterHeight) == true) {
						computeWaterPositionMap(
							terrainBoundingBox,
							terrainHeightVector,
							Vector3(
								terrainBoundingBox.getMin().getX() + x * STEP_SIZE,
								waterHeight,
								terrainBoundingBox.getMin().getZ() + ((z - 1) * STEP_SIZE)
							),
							waterHeight,
							waterPositionMap
						);
					} else
					if (hasWaterPosition(waterPositionMap, x, z + 1) == false &&
						determineWater(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, x, z + 1, waterHeight) == true) {
						computeWaterPositionMap(
							terrainBoundingBox,
							terrainHeightVector,
							Vector3(
								terrainBoundingBox.getMin().getX() + x * STEP_SIZE,
								waterHeight,
								terrainBoundingBox.getMin().getZ() + ((z + 1) * STEP_SIZE)
							),
							waterHeight,
							waterPositionMap
						);
					}
				}
			}
		} while (waterPositionMapCopy.size() != waterPositionMap.size());
		waterPositionMap[zMax] = waterPositionMap[zMax - 1];
	}

	//
	auto haveWaterPositionSet = waterPositionMap.empty() == false;
	Console::println("Terrain::determineWaterPositionSet: Have water position set: " + to_string(haveWaterPositionSet));
	return haveWaterPositionSet;
}

Vector3 Terrain::computeWaterReflectionEnvironmentMappingPosition(const unordered_map<int, unordered_set<int>>& waterPositionMap, float waterHeight) {
	// determine reflection environment mapping position
	auto zMin = Integer::MAX_VALUE;
	auto zMax = Integer::MIN_VALUE;
	auto xMin = Integer::MAX_VALUE;
	auto xMax = Integer::MIN_VALUE;
	for (const auto& [z, xValues]: waterPositionMap) {
		if (z < zMin) zMin = z;
		if (z > zMax) zMax = z;
		for (auto x: xValues) {
			if (x < xMin) xMin = x;
			if (x > xMax) xMax = x;
		}
	}

	return Vector3(
		(static_cast<float>(xMin + xMax) / 2.0f) * STEP_SIZE,
		waterHeight + 2.0f,
		(static_cast<float>(zMin + zMax) / 2.0f) * STEP_SIZE
	);
}

void Terrain::createWaterModels(
	BoundingBox& terrainBoundingBox,
	const unordered_map<int, unordered_set<int>>& waterPositionMap,
	float waterHeight,
	int waterModelIdx,
	vector<Model*>& waterModels
) {
	auto width = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX()));
	auto depth = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getZ()));
	auto partitionsX = static_cast<int>(Math::ceil(width / PARTITION_SIZE));
	auto partitionsZ = static_cast<int>(Math::ceil(depth / PARTITION_SIZE));
	auto partitionCount = partitionsX * partitionsZ;
	vector<vector<Vector3>> partitionTerrainVertices;
	vector<vector<Vector3>> partitionTerrainNormals;
	vector<vector<array<int, 6>>> partitionWaterFaces;
	partitionTerrainVertices.resize(partitionCount);
	partitionTerrainNormals.resize(partitionCount);
	partitionWaterFaces.resize(partitionCount);
	for (float z = 0.0f; z < depth; z+= STEP_SIZE) {
		for (float x = 0.0f; x < width; x+= STEP_SIZE) {
			auto terrainHeightVectorX = static_cast<int>(x / STEP_SIZE);
			auto terrainHeightVectorZ = static_cast<int>(z / STEP_SIZE);

			Vector3 topVertex;
			Vector3 topLeftVertex;
			Vector3 leftVertex;
			Vector3 vertex;

			auto hasTopLeft = hasWaterPosition(waterPositionMap, terrainHeightVectorX - 1, terrainHeightVectorZ - 1);
			auto hasTop = hasWaterPosition(waterPositionMap, terrainHeightVectorX, terrainHeightVectorZ - 1);
			auto hasLeft = hasWaterPosition(waterPositionMap, terrainHeightVectorX - 1, terrainHeightVectorZ);
			auto hasOrigin = hasWaterPosition(waterPositionMap, terrainHeightVectorX, terrainHeightVectorZ);

			auto haveVertexCount = 0;
			if (hasTop == true) haveVertexCount++;
			if (hasTopLeft == true) haveVertexCount++;
			if (hasLeft == true) haveVertexCount++;
			if (hasOrigin == true) haveVertexCount++;
			if (haveVertexCount < 3) continue;

			auto partitionX = static_cast<int>(x / PARTITION_SIZE);
			auto partitionZ = static_cast<int>(z / PARTITION_SIZE);
			auto partitionIdx = partitionZ * partitionsX + partitionX;

			auto& terrainVertices = partitionTerrainVertices[partitionIdx];
			auto& terrainNormals = partitionTerrainNormals[partitionIdx];
			auto& terrainFaces = partitionWaterFaces[partitionIdx];

			int normalIdx = terrainNormals.size();
			int vertexIdx = terrainVertices.size();

			getWaterVertex(terrainHeightVectorX, terrainHeightVectorZ - 1, waterHeight, topVertex);
			getWaterVertex(terrainHeightVectorX - 1, terrainHeightVectorZ - 1, waterHeight, topLeftVertex);
			getWaterVertex(terrainHeightVectorX - 1, terrainHeightVectorZ, waterHeight, leftVertex);
			getWaterVertex(terrainHeightVectorX, terrainHeightVectorZ, waterHeight, vertex);

			if (hasTop == true) terrainVertices.push_back(topVertex);
			if (hasTopLeft == true) terrainVertices.push_back(topLeftVertex);
			if (hasLeft == true) terrainVertices.push_back(leftVertex);
			if (hasOrigin == true) terrainVertices.push_back(vertex);

			auto normal = Vector3(0.0f, 1.0f, 0.0f);
			auto topNormal = Vector3(0.0f, 1.0f, 0.0f);
			auto topLeftNormal = Vector3(0.0f, 1.0f, 0.0f);
			auto leftNormal = Vector3(0.0f, 1.0f, 0.0f);

			if (hasTop == true) terrainNormals.push_back(topNormal);
			if (hasTopLeft == true) terrainNormals.push_back(topLeftNormal);
			if (hasLeft == true) terrainNormals.push_back(leftNormal);
			if (hasOrigin == true) terrainNormals.push_back(normal);

			if (hasTopLeft == false ||
				hasTop == false ||
				hasLeft == false ||
				hasOrigin == false) {
				terrainFaces.push_back(
					{
						vertexIdx + 0,
						vertexIdx + 1,
						vertexIdx + 2,
						normalIdx + 0,
						normalIdx + 1,
						normalIdx + 2
					}
				);
			} else {
				terrainFaces.push_back(
					{
						vertexIdx + 0,
						vertexIdx + 1,
						vertexIdx + 2,
						normalIdx + 0,
						normalIdx + 1,
						normalIdx + 2
					}
				);
				terrainFaces.push_back(
					{
						vertexIdx + 2,
						vertexIdx + 3,
						vertexIdx + 0,
						normalIdx + 2,
						normalIdx + 3,
						normalIdx + 0
					}
				);
			}
		}
	}
	for (auto partitionIdx = 0; partitionIdx < partitionCount; partitionIdx++) {
		if (partitionWaterFaces[partitionIdx].empty() == true) continue;
		auto modelId = "water." + to_string(waterModelIdx) + "." + to_string(partitionIdx);
		auto waterModel = new Model(modelId, modelId, UpVector::Y_UP, RotationOrder::ZYX, nullptr);
		auto waterMaterial = new Material("water");
		waterMaterial->setDoubleSided(true);
		waterMaterial->setSpecularMaterialProperties(new SpecularMaterialProperties());
		waterMaterial->getSpecularMaterialProperties()->setAmbientColor(Color4(0.022f, 0.13f, 0.56f, 1.0f));
		waterMaterial->getSpecularMaterialProperties()->setDiffuseColor(Color4(0.026f, 0.15f, 0.64f, 1.0f));
		waterMaterial->getSpecularMaterialProperties()->setSpecularColor(Color4(1.0f, 1.0f, 1.0f, 1.0f));
		waterMaterial->getSpecularMaterialProperties()->setShininess(100.0f);
		waterModel->getMaterials()[waterMaterial->getId()] = waterMaterial;
		auto waterNode = new Node(waterModel, nullptr, "water", "water");
		FacesEntity nodeFacesEntityWater(waterNode, "water.facesentity");
		nodeFacesEntityWater.setMaterial(waterMaterial);
		vector<FacesEntity> nodeFacesEntities;
		vector<Face> nodeFaces;
		for (auto& faceIndices: partitionWaterFaces[partitionIdx]) {
			nodeFaces.emplace_back(
				waterNode,
				faceIndices[0],
				faceIndices[1],
				faceIndices[2],
				faceIndices[3],
				faceIndices[4],
				faceIndices[5]
			);
		};
		nodeFacesEntityWater.setFaces(nodeFaces);
		nodeFacesEntities.push_back(nodeFacesEntityWater);
		waterNode->setVertices(partitionTerrainVertices[partitionIdx]);
		waterNode->setNormals(partitionTerrainNormals[partitionIdx]);
		waterNode->setFacesEntities(nodeFacesEntities);
		waterModel->getNodes()[waterNode->getId()] = waterNode;
		waterModel->getSubNodes()[waterNode->getId()] = waterNode;
		ModelTools::prepareForIndexedRendering(waterModel);
		ModelTools::createDefaultAnimation(waterModel, 1);
		waterModels.push_back(waterModel);
	}
}

bool Terrain::getTerrainModelsHeight(
	BoundingBox& terrainBoundingBox,
	vector<Model*>& terrainModels,
	vector<float>& terrainHeightVector,
	const Vector3& brushCenterPosition,
	float& brushHeight
) {
	// check if we have a model
	if (terrainModels.empty() == true) return false;

	// get height at brush position
	auto terrainHeightVectorVerticesPerX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / STEP_SIZE));
	auto terreinHeightVectorVerticesPerZ = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getZ() / STEP_SIZE));
	auto terrainHeightVectorX = static_cast<int>((brushCenterPosition.getX() - terrainBoundingBox.getMin().getX()) / STEP_SIZE);
	auto terrainHeightVectorZ = static_cast<int>((brushCenterPosition.getZ() - terrainBoundingBox.getMin().getZ()) / STEP_SIZE);
	if (terrainHeightVectorX < 0 || terrainHeightVectorX >= terreinHeightVectorVerticesPerZ ||
			terrainHeightVectorZ < 0 || terrainHeightVectorZ >= terreinHeightVectorVerticesPerZ) return false;
	brushHeight = terrainHeightVector[terrainHeightVectorZ * terrainHeightVectorVerticesPerX + terrainHeightVectorX];

	//
	return true;
}

void Terrain::createFoliageMaps(
	BoundingBox& terrainBoundingBox,
	vector<unordered_map<int, vector<Transform>>>& foliageMaps
) {
	//
	auto width = terrainBoundingBox.getDimensions().getX();
	auto depth = terrainBoundingBox.getDimensions().getZ();
	createFoliageMaps(width, depth, foliageMaps);
}

void Terrain::createFoliageMaps(
	float terrainWidth,
	float terrainDepth,
	vector<unordered_map<int, vector<Transform>>>& foliageMaps
) {
	//
	auto partitionsX = static_cast<int>(Math::ceil(terrainWidth / PARTITION_SIZE));
	auto partitionsZ = static_cast<int>(Math::ceil(terrainDepth / PARTITION_SIZE));
	auto partitionCount = partitionsX * partitionsZ;
	foliageMaps.resize(partitionCount);
	for (auto& foliageMap: foliageMaps) foliageMap.clear();
}

void Terrain::emptyFoliageMaps(
	vector<unordered_map<int, vector<Transform>>>& foliageMaps
) {
	//
	for (auto& foliageMap: foliageMaps) foliageMap.clear();
}

void Terrain::applyFoliageBrush(
	BoundingBox& terrainBoundingBox,
	vector<float>& terrainHeightVector,
	const Vector3& brushCenterPosition,
	const FoliageBrush& foliageBrush,
	const vector<FoliageBrushPrototype>& foliageBrushPrototypes,
	BrushOperation brushOperation,
	vector<unordered_map<int, vector<Transform>>>& foliageMaps,
	vector<unordered_map<int, vector<Transform>>>& newFoliageMaps
) {
	// check if we have a texture
	if (foliageBrush.brushTexture == nullptr) return;

	// apply brush
	auto partitionsX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / PARTITION_SIZE));
	auto terrainHeightVectorVerticesPerX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / STEP_SIZE));
	auto terreinHeightVectorVerticesPerZ = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getZ() / STEP_SIZE));

	// other operations
	auto textureData = foliageBrush.brushTexture->getRGBTextureData();
	auto textureWidth = foliageBrush.brushTexture->getTextureWidth();
	auto textureHeight = foliageBrush.brushTexture->getTextureHeight();
	auto textureBytePerPixel = foliageBrush.brushTexture->getRGBDepthBitsPerPixel() == 32?4:3;

	//
	vector<unordered_map<int, float>> brushMapCountMapTemplate;
	auto brushMapCountMapWidth = static_cast<int>(textureWidth * foliageBrush.brushScale);
	auto brushMapCountMapDepth = static_cast<int>(textureHeight * foliageBrush.brushScale);
	for (auto z = 0.0f; z < textureHeight * foliageBrush.brushScale; z+= 1.0f) {
		for (auto x = 0.0f; x < textureWidth * foliageBrush.brushScale; x+= 1.0f) {
			auto textureX = static_cast<int>(x / foliageBrush.brushScale);
			auto textureY = static_cast<int>(z / foliageBrush.brushScale);
			auto red = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 0);
			auto green = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 1);
			auto blue = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 2);
			auto alpha = textureBytePerPixel == 3?255:textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 3);
			auto appliedDensity = (static_cast<float>(red) + static_cast<float>(green) + static_cast<float>(blue)) / (255.0f * 3.0f) * foliageBrush.brushDensity;
			unordered_map<int, float> brushMapCountMapEntity;
			for (auto& foliageBrushPrototype: foliageBrushPrototypes) {
				if (foliageBrushPrototype.prototypeId == -1) continue;
				auto foliageCount = foliageBrushPrototype.count;
				brushMapCountMapEntity[foliageBrushPrototype.prototypeId] = foliageCount * appliedDensity;
			}
			brushMapCountMapTemplate.push_back(brushMapCountMapEntity);
		}
	}

	//
	auto brushMapCountMap = brushMapCountMapTemplate;
	for (auto& foliageBrushPrototype: foliageBrushPrototypes) {
		if (foliageBrushPrototype.prototypeId == -1) continue;
		float totalCount = 0.0f;
		for (auto i = 0; i < brushMapCountMap.size(); i++) {
			auto& brushMapCountMapEntity = brushMapCountMap[i];
			auto count = brushMapCountMapEntity[foliageBrushPrototype.prototypeId];
			auto countFloor = Math::floor(count);
			totalCount+= count - countFloor;
			brushMapCountMapEntity[foliageBrushPrototype.prototypeId] = countFloor;
			auto totalCountFloor = Math::floor(totalCount);
			if (totalCount >= 1.0f) brushMapCountMapEntity[foliageBrushPrototype.prototypeId]+= totalCountFloor;
			totalCount-= totalCountFloor;
		}
	}

	// randomize
	unordered_map<int, unordered_map<int, vector<int>>> brushMapIdxPerDensityPerPrototype;
	for (const auto& foliageBrushPrototype: foliageBrushPrototypes) {
		for (auto i = 0; i < brushMapCountMapTemplate.size(); i++) {
			auto brushMapPrototypeCount = brushMapCountMapTemplate[i][foliageBrushPrototype.prototypeId];
			brushMapIdxPerDensityPerPrototype[foliageBrushPrototype.prototypeId][static_cast<int>(brushMapPrototypeCount * 1000.0f)].push_back(i);
		}
	}
	for (const auto& foliageBrushPrototype: foliageBrushPrototypes) {
		for (auto i = 0; i < brushMapCountMap.size(); i++) {
			auto brushMapPrototypeCountMapEntityITemplate = brushMapCountMapTemplate[i][foliageBrushPrototype.prototypeId];
			auto brushMapPrototypeCountMapEntityI = brushMapCountMap[i][foliageBrushPrototype.prototypeId];
			const auto& brushMapIdxPerDensityPerPrototypeVector = brushMapIdxPerDensityPerPrototype[foliageBrushPrototype.prototypeId][static_cast<int>(brushMapPrototypeCountMapEntityITemplate * 1000.0f)];
			auto j = brushMapIdxPerDensityPerPrototypeVector[static_cast<int>(brushMapIdxPerDensityPerPrototypeVector.size() - 1) * Math::random()];
			auto brushMapPrototypeCountMapEntityJ = brushMapCountMap[j][foliageBrushPrototype.prototypeId];
			brushMapCountMap[j][foliageBrushPrototype.prototypeId] = brushMapPrototypeCountMapEntityI;
			brushMapCountMap[i][foliageBrushPrototype.prototypeId] = brushMapPrototypeCountMapEntityJ;
		}
	}

	//
	for (auto z = 0.0f; z < textureHeight * foliageBrush.brushScale; z+= 1.0f) {
		auto brushPosition =
			brushCenterPosition.
			clone().
			sub(
				Vector3(
					(static_cast<float>(textureWidth) * foliageBrush.brushScale) / 2.0f,
					0.0f,
					((static_cast<float>(textureHeight) * foliageBrush.brushScale) / 2.0f)
				)
			).
			add(
				Vector3(
					0.0f,
					0.0f,
					z
				)
			);
		for (auto x = 0.0f; x < textureWidth * foliageBrush.brushScale; x+= 1.0f) {
			auto brushMapCountMapX = static_cast<int>(x);
			auto brushMapCountMapZ = static_cast<int>(z);
			auto brushMapCountMapEntity = brushMapCountMap[brushMapCountMapZ * brushMapCountMapWidth + brushMapCountMapX];
			auto terrainHeightVectorX = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / STEP_SIZE);
			auto terrainHeightVectorZ = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / STEP_SIZE);
			if (brushPosition.getX() < 0.0f || brushPosition.getZ() < 0.0f ||
				terrainHeightVectorX < 0 || terrainHeightVectorX >= terrainHeightVectorVerticesPerX ||
				terrainHeightVectorZ < 0 || terrainHeightVectorZ >= terreinHeightVectorVerticesPerZ) {
				//
				brushPosition.add(
					Vector3(
						STEP_SIZE,
						0.0f,
						0.0f
					)
				);
				continue;
			}

			//
			switch(brushOperation) {
				case BRUSHOPERATION_ADD:
					for (const auto& [prototypeId, prototypeCount]: brushMapCountMapEntity) {
						if (prototypeId == -1) continue;

						//
						auto prototypeIdx = -1;
						for (auto i = 0; i < foliageBrushPrototypes.size(); i++) {
							if (foliageBrushPrototypes[i].prototypeId == prototypeId) prototypeIdx = i;
						}
						if (prototypeIdx == -1) continue;

						//
						for (auto i = 0; i < static_cast<int>(prototypeCount); i++) {
							auto prototypeScale = foliageBrushPrototypes[prototypeIdx].scaleMin + ((foliageBrushPrototypes[prototypeIdx].scaleMax - foliageBrushPrototypes[prototypeIdx].scaleMin) * Math::random());

							//
							Vector3 translation(
								Math::floor(brushPosition.getX()) + Math::random(),
								0.0f,
								Math::floor(brushPosition.getZ()) + Math::random()
							);

							//
							auto partitionX = static_cast<int>((translation.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
							auto partitionZ = static_cast<int>((translation.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
							auto partitionIdx = partitionZ * partitionsX + partitionX;

							//
							auto haveContact = false;
							Vector3 contact;
							Vector3 normal;
							float height;
							for (int _z = -1; _z < 2; _z++)
							for (int _x = -1; _x < 2; _x++) {
								Vector3 topVertex;
								Vector3 topLeftVertex;
								Vector3 leftVertex;
								Vector3 vertex;

								getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, _x + terrainHeightVectorX, _z + terrainHeightVectorZ - 1, topVertex);
								getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, _x + terrainHeightVectorX - 1, _z + terrainHeightVectorZ - 1, topLeftVertex);
								getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, _x + terrainHeightVectorX - 1, _z + terrainHeightVectorZ, leftVertex);
								getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, _x + terrainHeightVectorX, _z + terrainHeightVectorZ, vertex);

								if (LineSegment::doesLineSegmentCollideWithTriangle(topVertex, topLeftVertex, leftVertex, translation.clone().setY(-10000.0f), translation.clone().setY(+10000.0f), contact) == true) {
									haveContact = true;
									normal = ModelTools::computeNormal({topVertex, topLeftVertex, leftVertex});
									height = (topVertex.getY() + topLeftVertex.getY() + leftVertex.getY()) / 3.0f;
									break;
								} else
								if (LineSegment::doesLineSegmentCollideWithTriangle(leftVertex, vertex, topVertex, translation.clone().setY(-10000.0f), translation.clone().setY(+10000.0f), contact) == true) {
									haveContact = true;
									normal = ModelTools::computeNormal({leftVertex, vertex, topVertex});
									height = (leftVertex.getY() + vertex.getY() + topVertex.getY()) / 3.0f;
									break;
								}
							}

							// check height
							if (height < foliageBrushPrototypes[prototypeIdx].heightMin || height > foliageBrushPrototypes[prototypeIdx].heightMax) continue;

							//
							if (haveContact == false) {
								Console::println(
									"Terrain::applyFoliageBrush(): no contact@" +
									to_string(translation.getX()) + ", " +
									to_string(translation.getZ())
								);
								contact = translation;
								continue;
							}

							// slope
							auto slope = Math::abs(180.0f / 3.14f * Math::acos(Math::clamp(Vector3::computeDotProduct(normal, Vector3(0.0, 1.0, 0.0)), -1.0, 1.0)));
							if (slope < foliageBrushPrototypes[prototypeIdx].slopeMin || slope > foliageBrushPrototypes[prototypeIdx].slopeMax) continue;

							//
							Transform transform;
							transform.setTranslation(translation);
							auto xAxisRotation = foliageBrushPrototypes[prototypeIdx].rotationXMin + ((foliageBrushPrototypes[prototypeIdx].rotationXMax - foliageBrushPrototypes[prototypeIdx].rotationXMin) * Math::random());
							auto yAxisRotation = foliageBrushPrototypes[prototypeIdx].rotationYMin + ((foliageBrushPrototypes[prototypeIdx].rotationYMax - foliageBrushPrototypes[prototypeIdx].rotationYMin) * Math::random());
							auto zAxisRotation = foliageBrushPrototypes[prototypeIdx].rotationZMin + ((foliageBrushPrototypes[prototypeIdx].rotationZMax - foliageBrushPrototypes[prototypeIdx].rotationZMin) * Math::random());
							if (foliageBrushPrototypes[prototypeIdx].normalAlign == true) {
								xAxisRotation = Vector3::computeAngle(normal, Vector3(0.0f, 1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f));
								zAxisRotation = Vector3::computeAngle(normal, Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f));
								Transform _transform;
								_transform.addRotation(Rotation::Z_AXIS, zAxisRotation);
								_transform.addRotation(Rotation::X_AXIS, xAxisRotation);
								_transform.addRotation(Rotation::Y_AXIS, yAxisRotation);
								_transform.update();
								auto euler = _transform.getTransformMatrix().computeEulerAngles();
								zAxisRotation = euler.getZ();
								yAxisRotation = euler.getY();
								xAxisRotation = euler.getX();
							}
							transform.addRotation(Rotation::Z_AXIS, zAxisRotation);
							transform.addRotation(Rotation::Y_AXIS, yAxisRotation);
							transform.addRotation(Rotation::X_AXIS, xAxisRotation);
							transform.setScale(Vector3(prototypeScale, prototypeScale, prototypeScale));

							transform.setTranslation(translation.clone().setY(contact.getY()));
							transform.update();

							//
							foliageMaps[partitionIdx][prototypeId].push_back(transform);
							newFoliageMaps[partitionIdx][prototypeId].push_back(transform);
						}
					}
					break;
			}

			//
			brushPosition.add(
				Vector3(
					STEP_SIZE,
					0.0f,
					0.0f
				)
			);
		}
	}
}

void Terrain::applyFoliageDeleteBrush(
	BoundingBox& terrainBoundingBox, // TODO: constness
	const Vector3& brushCenterPosition,
	const FoliageBrush& foliageBrush,
	const vector<FoliageBrushPrototype>& foliageBrushPrototypes,
	BrushOperation brushOperation,
	vector<unordered_map<int, vector<Transform>>>& foliageMaps,
	unordered_set<int>& recreateFoliagePartitions
) {
	// check if we have a texture
	if (foliageBrush.brushTexture == nullptr) return;

	// apply brush
	auto partitionsX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / PARTITION_SIZE));
	auto terrainHeightVectorVerticesPerX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / STEP_SIZE));
	auto terreinHeightVectorVerticesPerZ = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getZ() / STEP_SIZE));

	// other operations
	auto textureData = foliageBrush.brushTexture->getRGBTextureData();
	auto textureWidth = foliageBrush.brushTexture->getTextureWidth();
	auto textureHeight = foliageBrush.brushTexture->getTextureHeight();
	auto textureBytePerPixel = foliageBrush.brushTexture->getRGBDepthBitsPerPixel() == 32?4:3;

	auto heightMin = Float::MAX_VALUE;
	auto heightMax = Float::MIN_VALUE;
	auto prototypeCount = 0;
	for (const auto& foliageBrushPrototype: foliageBrushPrototypes) {
		if (foliageBrushPrototype.prototypeId == -1) continue;
		heightMin = Math::min(heightMin, foliageBrushPrototype.heightMin);
		heightMax = Math::max(heightMax, foliageBrushPrototype.heightMax);
		prototypeCount++;
	}
	//
	for (auto z = 0.0f; z < textureHeight * foliageBrush.brushScale; z+= 1.0f) {
		auto brushPosition =
			brushCenterPosition.
			clone().
			sub(
				Vector3(
					(static_cast<float>(textureWidth) * foliageBrush.brushScale) / 2.0f,
					0.0f,
					((static_cast<float>(textureHeight) * foliageBrush.brushScale) / 2.0f)
				)
			).
			add(
				Vector3(
					0.0f,
					0.0f,
					z
				)
			);
		for (auto x = 0.0f; x < textureWidth * foliageBrush.brushScale; x+= 1.0f) {
			auto textureX = static_cast<int>(x / foliageBrush.brushScale);
			auto textureY = static_cast<int>(z / foliageBrush.brushScale);
			auto red = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 0);
			auto green = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 1);
			auto blue = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 2);
			auto alpha = textureBytePerPixel == 3?255:textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 3);
			auto appliedDensity = (static_cast<float>(red) + static_cast<float>(green) + static_cast<float>(blue)) / (255.0f * 3.0f);

			//
			auto terrainHeightVectorX = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / STEP_SIZE);
			auto terrainHeightVectorZ = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / STEP_SIZE);

			//
			if (terrainHeightVectorX < 0 || terrainHeightVectorX >= terrainHeightVectorVerticesPerX ||
				terrainHeightVectorZ < 0 || terrainHeightVectorZ >= terreinHeightVectorVerticesPerZ) {
				//
				brushPosition.add(
					Vector3(
						STEP_SIZE,
						0.0f,
						0.0f
					)
				);
				continue;
			}

			//
			auto partitionX = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
			auto partitionZ = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
			auto partitionIdx = partitionZ * partitionsX + partitionX;

			//
			switch(brushOperation) {
				case BRUSHOPERATION_DELETE:
					{
						Vector3 topVertex;
						Vector3 topLeftVertex;
						Vector3 leftVertex;
						Vector3 vertex;

						getTerrainVertex(terrainHeightVectorX, terrainHeightVectorZ - 1, topVertex);
						getTerrainVertex(terrainHeightVectorX - 1, terrainHeightVectorZ - 1, topLeftVertex);
						getTerrainVertex(terrainHeightVectorX - 1, terrainHeightVectorZ, leftVertex);
						getTerrainVertex(terrainHeightVectorX, terrainHeightVectorZ, vertex);

						for (auto& [prototypeId, transformVector]: foliageMaps[partitionIdx]) {
							for (auto i = 0; i < transformVector.size(); i++) {
								const auto& translation = transformVector[i].getTranslation();
								if (appliedDensity > 0.0f &&
									translation.getX() >= leftVertex.getX() - 0.01f &&
									translation.getX() <= vertex.getX() + 0.01f &&
									translation.getZ() >= topVertex.getZ() - 0.01f &&
									translation.getZ() <= vertex.getZ() + 0.01f &&
									(prototypeCount == 0 ||
									(translation.getY() >= heightMin &&
									translation.getY() <= heightMax))) {
									//
									transformVector.erase(transformVector.begin() + i);
									recreateFoliagePartitions.insert(partitionIdx);
									i--;
								}
							}
						}
					}
					break;
			}

			//
			brushPosition.add(
				Vector3(
					STEP_SIZE,
					0.0f,
					0.0f
				)
			);
		}
	}
}

void Terrain::updateFoliageTerrainBrush(
	BoundingBox& terrainBoundingBox, // TODO: constness
	vector<float>& terrainHeightVector,
	const Vector3& brushCenterPosition,
	const FoliageBrush& foliageBrush,
	vector<unordered_map<int, vector<Transform>>>& foliageMaps,
	unordered_set<int>& updateFoliagePartitions
) {
	// check if we have a texture
	if (foliageBrush.brushTexture == nullptr) return;

	// apply brush
	auto partitionsX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / PARTITION_SIZE));
	auto terrainHeightVectorVerticesPerX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / STEP_SIZE));
	auto terreinHeightVectorVerticesPerZ = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getZ() / STEP_SIZE));

	// other operations
	auto textureData = foliageBrush.brushTexture->getRGBTextureData();
	auto textureWidth = foliageBrush.brushTexture->getTextureWidth();
	auto textureHeight = foliageBrush.brushTexture->getTextureHeight();
	auto textureBytePerPixel = foliageBrush.brushTexture->getRGBDepthBitsPerPixel() == 32?4:3;

	//
	for (auto z = 0.0f; z < textureHeight * foliageBrush.brushScale; z+= 1.0f) {
		auto brushPosition =
			brushCenterPosition.
			clone().
			sub(
				Vector3(
					(static_cast<float>(textureWidth) * foliageBrush.brushScale) / 2.0f,
					0.0f,
					((static_cast<float>(textureHeight) * foliageBrush.brushScale) / 2.0f)
				)
			).
			add(
				Vector3(
					0.0f,
					0.0f,
					z
				)
			);
		for (auto x = 0.0f; x < textureWidth * foliageBrush.brushScale; x+= 1.0f) {
			auto brushMapCountMapX = static_cast<int>(x);
			auto brushMapCountMapZ = static_cast<int>(z);
			auto terrainHeightVectorX = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / STEP_SIZE);
			auto terrainHeightVectorZ = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / STEP_SIZE);
			if (terrainHeightVectorX < 0 || terrainHeightVectorX >= terrainHeightVectorVerticesPerX ||
				terrainHeightVectorZ < 0 || terrainHeightVectorZ >= terreinHeightVectorVerticesPerZ) {
				//
				brushPosition.add(
					Vector3(
						STEP_SIZE,
						0.0f,
						0.0f
					)
				);
				continue;
			}

			//
			auto textureX = static_cast<int>(x / foliageBrush.brushScale);
			auto textureY = static_cast<int>(z / foliageBrush.brushScale);
			auto red = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 0);
			auto green = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 1);
			auto blue = textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 2);
			auto alpha = textureBytePerPixel == 3?255:textureData.get(textureY * textureWidth * textureBytePerPixel + textureX * textureBytePerPixel + 3);
			auto brushTextureDensity = (static_cast<float>(red) + static_cast<float>(green) + static_cast<float>(blue)) / (255.0f * 3.0f);

			//
			auto partitionX = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
			auto partitionZ = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
			auto partitionIdx = partitionZ * partitionsX + partitionX;

			//
			updateFoliagePartitions.insert(partitionIdx);

			//
			Vector3 topVertex;
			Vector3 topLeftVertex;
			Vector3 leftVertex;
			Vector3 vertex;

			//
			getTerrainVertex(terrainHeightVectorX, terrainHeightVectorZ - 1, topVertex);
			getTerrainVertex(terrainHeightVectorX - 1, terrainHeightVectorZ - 1, topLeftVertex);
			getTerrainVertex(terrainHeightVectorX - 1, terrainHeightVectorZ, leftVertex);
			getTerrainVertex(terrainHeightVectorX, terrainHeightVectorZ, vertex);

			//
			for (auto& [prototypeId, transformVector]: foliageMaps[partitionIdx]) {
				if (prototypeId == -1) continue;
				for (auto& transform: transformVector) {
					const auto& translation = transform.getTranslation();
					if (brushTextureDensity > 0.0f &&
						translation.getX() >= leftVertex.getX() &&
						translation.getX() <= vertex.getX() &&
						translation.getZ() >= topVertex.getZ() &&
						translation.getZ() <= vertex.getZ()) {
						//
						auto haveContact = false;
						Vector3 contact;
						for (int _z = -1; _z < 2; _z++)
						for (int _x = -1; _x < 2; _x++) {
							Vector3 topVertex;
							Vector3 topLeftVertex;
							Vector3 leftVertex;
							Vector3 vertex;

							getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, _x + terrainHeightVectorX, _z + terrainHeightVectorZ - 1, topVertex);
							getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, _x + terrainHeightVectorX - 1, _z + terrainHeightVectorZ - 1, topLeftVertex);
							getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, _x + terrainHeightVectorX - 1, _z + terrainHeightVectorZ, leftVertex);
							getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, _x + terrainHeightVectorX, _z + terrainHeightVectorZ, vertex);

							if (LineSegment::doesLineSegmentCollideWithTriangle(topVertex, topLeftVertex, leftVertex, transform.getTranslation().clone().setY(-10000.0f), transform.getTranslation().clone().setY(+10000.0f), contact) == true) {
								haveContact = true;
								break;
							} else
							if (LineSegment::doesLineSegmentCollideWithTriangle(leftVertex, vertex, topVertex, transform.getTranslation().clone().setY(-10000.0f), transform.getTranslation().clone().setY(+10000.0f), contact) == true) {
								haveContact = true;
								break;
							}
						}

						//
						if (haveContact == false) {
							Console::println(
								"Terrain::applyFoliageBrush(): no contact@" +
								to_string(transform.getTranslation().getX()) + ", " +
								to_string(transform.getTranslation().getZ())
							);
							contact = transform.getTranslation();
						}

						//
						transform.setTranslation(transform.getTranslation().clone().setY(contact.getY()));
						transform.update();
					}
				}
			}

			//
			brushPosition.add(
				Vector3(
					STEP_SIZE,
					0.0f,
					0.0f
				)
			);
		}
	}
}

void Terrain::updateFoliageTerrainRampBrush(
	BoundingBox& terrainBoundingBox, // TODO: constness
	vector<float>& terrainHeightVector,
	const Vector3& brushCenterPosition,
	Texture* brushTexture,
	float brushRotation,
	const Vector2& brushScale,
	vector<unordered_map<int, vector<Transform>>>& foliageMaps,
	unordered_set<int>& updateFoliagePartitions
) {
	// check if we have a texture
	if (brushTexture == nullptr) return;

	// apply brush
	vector<vector<Vector3>> partitionTerrainVertices;
	vector<vector<Vector3>> partitionTerrainNormals;
	auto partitionsX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / PARTITION_SIZE));
	auto terrainHeightVectorVerticesPerX = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getX() / STEP_SIZE));
	auto terreinHeightVectorVerticesPerZ = static_cast<int>(Math::ceil(terrainBoundingBox.getDimensions().getZ() / STEP_SIZE));

	// texture
	auto textureData = brushTexture->getRGBTextureData();
	auto textureWidth = brushTexture->getTextureWidth();
	auto textureHeight = brushTexture->getTextureHeight();
	auto textureBytePerPixel = brushTexture->getRGBDepthBitsPerPixel() == 32?4:3;

	// brush texture matrix
	Matrix2D3x3 brushTextureMatrix;
	brushTextureMatrix.identity();
	brushTextureMatrix.translate(Vector2(static_cast<float>(textureWidth) / 2.0f, static_cast<float>(textureHeight) / 2.0f));
	brushTextureMatrix.multiply((Matrix2D3x3()).identity().scale(Vector2(1.0f / brushScale.getX(), 1.0f / brushScale.getY())));
	brushTextureMatrix.multiply((Matrix2D3x3()).identity().rotate(brushRotation));
	auto brushScaleMax = Math::max(brushScale.getX(), brushScale.getY());

	//
	for (auto z = -textureHeight * brushScaleMax * 2.0f; z < textureHeight * brushScaleMax * 2.0f; z+= STEP_SIZE) {
		auto brushPosition =
			brushCenterPosition.
			clone().
			sub(
				Vector3(
					static_cast<float>(textureWidth) * brushScaleMax * 2.0f,
					0.0f,
					0.0f
				)
			).
			add(
				Vector3(
					0.0f,
					0.0f,
					z
				)
			);
		for (auto x = -textureWidth * brushScaleMax * 2.0f; x < textureWidth * brushScaleMax * 2.0f; x+= STEP_SIZE) {
			auto texturePositionUntransformed = Vector2(x, z);
			auto texturePosition = brushTextureMatrix.multiply(texturePositionUntransformed);
			auto textureX = static_cast<int>(texturePosition.getX());
			auto textureY = static_cast<int>(texturePosition.getY());
			if (textureX < 0 || textureX >= textureWidth ||
				textureY < 0 || textureY >= textureHeight) {
				brushPosition.add(
					Vector3(
						STEP_SIZE,
						0.0f,
						0.0f
					)
				);
				continue;
			}
			auto terrainHeightVectorX = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / STEP_SIZE);
			auto terrainHeightVectorZ = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / STEP_SIZE);
			if (terrainHeightVectorX < 0 || terrainHeightVectorX >= terrainHeightVectorVerticesPerX ||
				terrainHeightVectorZ < 0 || terrainHeightVectorZ >= terreinHeightVectorVerticesPerZ) {
				brushPosition.add(
					Vector3(
						STEP_SIZE,
						0.0f,
						0.0f
					)
				);
				continue;
			}

			//
			auto partitionX = static_cast<int>((brushPosition.getX() - terrainBoundingBox.getMin().getX()) / PARTITION_SIZE);
			auto partitionZ = static_cast<int>((brushPosition.getZ() - terrainBoundingBox.getMin().getZ()) / PARTITION_SIZE);
			auto partitionIdx = partitionZ * partitionsX + partitionX;

			//
			updateFoliagePartitions.insert(partitionIdx);

			//
			Vector3 topVertex;
			Vector3 topLeftVertex;
			Vector3 leftVertex;
			Vector3 vertex;

			//
			getTerrainVertex(terrainHeightVectorX, terrainHeightVectorZ - 1, topVertex);
			getTerrainVertex(terrainHeightVectorX - 1, terrainHeightVectorZ - 1, topLeftVertex);
			getTerrainVertex(terrainHeightVectorX - 1, terrainHeightVectorZ, leftVertex);
			getTerrainVertex(terrainHeightVectorX, terrainHeightVectorZ, vertex);

			//
			for (auto& [prototypeId, transformVector]: foliageMaps[partitionIdx]) {
				if (prototypeId == -1) continue;
				for (auto& transform: transformVector) {
					const auto& translation = transform.getTranslation();
					if (translation.getX() >= leftVertex.getX() &&
						translation.getX() <= vertex.getX() &&
						translation.getZ() >= topVertex.getZ() &&
						translation.getZ() <= vertex.getZ()) {
						//
						auto haveContact = false;
						Vector3 contact;
						for (int _z = -1; _z < 2; _z++)
						for (int _x = -1; _x < 2; _x++) {
							Vector3 topVertex;
							Vector3 topLeftVertex;
							Vector3 leftVertex;
							Vector3 vertex;

							getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, _x + terrainHeightVectorX, _z + terrainHeightVectorZ - 1, topVertex);
							getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, _x + terrainHeightVectorX - 1, _z + terrainHeightVectorZ - 1, topLeftVertex);
							getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, _x + terrainHeightVectorX - 1, _z + terrainHeightVectorZ, leftVertex);
							getTerrainVertex(terrainHeightVector, terrainHeightVectorVerticesPerX, terreinHeightVectorVerticesPerZ, _x + terrainHeightVectorX, _z + terrainHeightVectorZ, vertex);

							if (LineSegment::doesLineSegmentCollideWithTriangle(topVertex, topLeftVertex, leftVertex, transform.getTranslation().clone().setY(-10000.0f), transform.getTranslation().clone().setY(+10000.0f), contact) == true) {
								haveContact = true;
								break;
							} else
							if (LineSegment::doesLineSegmentCollideWithTriangle(leftVertex, vertex, topVertex, transform.getTranslation().clone().setY(-10000.0f), transform.getTranslation().clone().setY(+10000.0f), contact) == true) {
								haveContact = true;
								break;
							}
						}

						//
						if (haveContact == false) {
							Console::println(
								"Terrain::applyFoliageBrush(): no contact@" +
								to_string(transform.getTranslation().getX()) + ", " +
								to_string(transform.getTranslation().getZ())
							);
							contact = transform.getTranslation();
						}

						//
						transform.setTranslation(transform.getTranslation().clone().setY(contact.getY()));
						transform.update();
					}
				}
			}

			//
			brushPosition.add(
				Vector3(
					STEP_SIZE,
					0.0f,
					0.0f
				)
			);
		}
	}
}


void Terrain::mirrorXAxis(
	bool flipZ,
	float width,
	float depth,
	vector<float>& terrainHeightVector,
	unordered_map<int, float>& waterPositionMapsHeight,
	unordered_map<int, unordered_map<int, unordered_set<int>>>& waterPositionMaps,
	vector<unordered_map<int, vector<Transform>>>& foliageMaps
) {
	auto terrainHeightVectorVerticesPerX = static_cast<int>(Math::ceil(width / STEP_SIZE));
	auto terreinHeightVectorVerticesPerZ = static_cast<int>(Math::ceil(depth / STEP_SIZE));

	// terrain
	vector<float> terrainHeightVectorMirrored;
	terrainHeightVectorMirrored.resize(terrainHeightVectorVerticesPerX * 2 * terreinHeightVectorVerticesPerZ);
	for (auto z = 0; z < terreinHeightVectorVerticesPerZ; z++) {
		for (auto x = 0; x < terrainHeightVectorVerticesPerX; x++) {
			auto _z = flipZ == true?terreinHeightVectorVerticesPerZ - z - 1:z;
			terrainHeightVectorMirrored[z * terrainHeightVectorVerticesPerX * 2 + x] = terrainHeightVector[z * terrainHeightVectorVerticesPerX + x];
			terrainHeightVectorMirrored[_z * terrainHeightVectorVerticesPerX * 2 + (terrainHeightVectorVerticesPerX * 2 - x - 1)] = terrainHeightVector[z * terrainHeightVectorVerticesPerX + x];
		}
	}
	terrainHeightVector = terrainHeightVectorMirrored;

	// water
	unordered_map<int, unordered_map<int, unordered_set<int>>> waterPositionMapsMirrored;
	unordered_map<int, float> waterPositionMapsHeightMirrored;
	auto idxMax = 0;
	for (const auto& [idx, waterPositionMap]: waterPositionMaps) {
		if (idx > idxMax) idxMax = idx;
	}
	idxMax++;
	for (const auto& [idx, waterPositionMap]: waterPositionMaps) {
		waterPositionMapsHeightMirrored[idx] = waterPositionMapsHeight[idx];
		waterPositionMapsHeightMirrored[idxMax + idx] = waterPositionMapsHeight[idx];
		for (const auto& [z, xValues]: waterPositionMap) {
			auto _z = flipZ == true?terreinHeightVectorVerticesPerZ - z - 1:z;
			for (const auto x: xValues) {
				waterPositionMapsMirrored[idx][z].insert(x);
				waterPositionMapsMirrored[idxMax + idx][_z].insert(terrainHeightVectorVerticesPerX * 2 - x - 1);
			}
		}
	}
	waterPositionMapsHeight = waterPositionMapsHeightMirrored;
	waterPositionMaps = waterPositionMapsMirrored;

	// foliage
	auto partitionsX = static_cast<int>(Math::ceil(width * 2.0f / PARTITION_SIZE));
	auto partitionsZ = static_cast<int>(Math::ceil(depth / PARTITION_SIZE));
	vector<unordered_map<int, vector<Transform>>> foliageMapsMirrored;
	createFoliageMaps(width * 2.0f, depth, foliageMapsMirrored);
	for (const auto& foliageMapPartition: foliageMaps) {
		for (const auto& [foliagePrototypeId, foliagePrototypeTransformVector]: foliageMapPartition) {
			for (const auto& transform: foliagePrototypeTransformVector) {
				{
					//
					auto partitionX = static_cast<int>((transform.getTranslation().getX()) / PARTITION_SIZE);
					auto partitionZ = static_cast<int>((transform.getTranslation().getZ()) / PARTITION_SIZE);
					auto partitionIdx = partitionZ * partitionsX + partitionX;
					foliageMapsMirrored[partitionIdx][foliagePrototypeId].push_back(transform);
				}
				{
					auto transformMirrored = transform;
					transformMirrored.setTranslation(
						Vector3(
							width * 2.0f - transformMirrored.getTranslation().getX(),
							transformMirrored.getTranslation().getY(),
							flipZ == true?depth - transformMirrored.getTranslation().getZ():transformMirrored.getTranslation().getZ()
						)
					);
					transformMirrored.addRotation(transformMirrored.getRotationAxis(0), -transformMirrored.getRotationAngle(0));
					transformMirrored.update();
					auto eulerAngles = transformMirrored.getTransformMatrix().computeEulerAngles();
					transformMirrored.removeRotation(3);
					transformMirrored.setRotationAngle(0, eulerAngles.getZ());
					transformMirrored.setRotationAngle(1, eulerAngles.getY());
					transformMirrored.setRotationAngle(2, eulerAngles.getX());
					transformMirrored.update();
					//
					auto partitionX = static_cast<int>((transformMirrored.getTranslation().getX()) / PARTITION_SIZE);
					auto partitionZ = static_cast<int>((transformMirrored.getTranslation().getZ()) / PARTITION_SIZE);
					if (partitionZ >= partitionsZ) partitionZ = partitionsZ - 1; // special case if translation = x, y, 0.0
					if (partitionX >= partitionsX) partitionX = partitionsX - 1; // special case if translation = 0.0, y, z
					auto partitionIdx = partitionZ * partitionsX + partitionX;
					foliageMapsMirrored[partitionIdx][foliagePrototypeId].push_back(transformMirrored);
				}
			}
		}
	}
	foliageMaps = foliageMapsMirrored;
}

void Terrain::mirrorZAxis(
	bool flipX,
	float width,
	float depth,
	vector<float>& terrainHeightVector,
	unordered_map<int, float>& waterPositionMapsHeight,
	unordered_map<int, unordered_map<int, unordered_set<int>>>& waterPositionMaps,
	vector<unordered_map<int, vector<Transform>>>& foliageMaps
) {
	auto terrainHeightVectorVerticesPerX = static_cast<int>(Math::ceil(width / STEP_SIZE));
	auto terreinHeightVectorVerticesPerZ = static_cast<int>(Math::ceil(depth / STEP_SIZE));

	// terrain
	vector<float> terrainHeightVectorMirrored;
	terrainHeightVectorMirrored.resize(terrainHeightVectorVerticesPerX * terreinHeightVectorVerticesPerZ * 2);
	for (auto z = 0; z < terreinHeightVectorVerticesPerZ; z++) {
		for (auto x = 0; x < terrainHeightVectorVerticesPerX; x++) {
			auto _x = flipX == true?terrainHeightVectorVerticesPerX - x - 1:x;
			terrainHeightVectorMirrored[z * terrainHeightVectorVerticesPerX + x] = terrainHeightVector[z * terrainHeightVectorVerticesPerX + x];
			terrainHeightVectorMirrored[(terreinHeightVectorVerticesPerZ * 2 - z - 1) * terrainHeightVectorVerticesPerX + _x] = terrainHeightVector[z * terrainHeightVectorVerticesPerX + x];
		}
	}
	terrainHeightVector = terrainHeightVectorMirrored;

	// water
	unordered_map<int, unordered_map<int, unordered_set<int>>> waterPositionMapsMirrored;
	unordered_map<int, float> waterPositionMapsHeightMirrored;
	auto idxMax = 0;
	for (const auto& [idx, waterPositionMap]: waterPositionMaps) {
		if (idx > idxMax) idxMax = idx;
	}
	idxMax++;
	for (const auto& [idx, waterPositionMap]: waterPositionMaps) {
		waterPositionMapsHeightMirrored[idx] = waterPositionMapsHeight[idx];
		waterPositionMapsHeightMirrored[idxMax + idx] = waterPositionMapsHeight[idx];
		for (const auto& [z, xValues]: waterPositionMap) {
			for (const auto x: xValues) {
				auto _x = flipX == true?terrainHeightVectorVerticesPerX - x - 1:x;
				waterPositionMapsMirrored[idx][z].insert(x);
				waterPositionMapsMirrored[idxMax + idx][terreinHeightVectorVerticesPerZ * 2 - z - 1].insert(_x);
			}
		}
	}
	waterPositionMapsHeight = waterPositionMapsHeightMirrored;
	waterPositionMaps = waterPositionMapsMirrored;

	// foliage
	auto partitionsX = static_cast<int>(Math::ceil(width / PARTITION_SIZE));
	auto partitionsZ = static_cast<int>(Math::ceil(depth * 2.0f / PARTITION_SIZE));
	vector<unordered_map<int, vector<Transform>>> foliageMapsMirrored;
	createFoliageMaps(width, depth * 2.0f, foliageMapsMirrored);
	for (const auto& foliageMapPartition: foliageMaps) {
		for (const auto& [foliagePrototypeId, foliageMapPartitionTransformVector]: foliageMapPartition) {
			for (const auto& transform: foliageMapPartitionTransformVector) {
				{
					//
					auto partitionX = static_cast<int>((transform.getTranslation().getX()) / PARTITION_SIZE);
					auto partitionZ = static_cast<int>((transform.getTranslation().getZ()) / PARTITION_SIZE);
					auto partitionIdx = partitionZ * partitionsX + partitionX;
					foliageMapsMirrored[partitionIdx][foliagePrototypeId].push_back(transform);
				}
				{
					auto transformMirrored = transform;
					transformMirrored.setTranslation(
						Vector3(
							flipX == true?width - transformMirrored.getTranslation().getX():transformMirrored.getTranslation().getX(),
							transformMirrored.getTranslation().getY(),
							depth * 2.0f - transformMirrored.getTranslation().getZ()
						)
					);
					transformMirrored.addRotation(transformMirrored.getRotationAxis(2), -transformMirrored.getRotationAngle(2));
					transformMirrored.update();
					auto eulerAngles = transformMirrored.getTransformMatrix().computeEulerAngles();
					transformMirrored.removeRotation(3);
					transformMirrored.setRotationAngle(0, eulerAngles.getZ());
					transformMirrored.setRotationAngle(1, eulerAngles.getY());
					transformMirrored.setRotationAngle(2, eulerAngles.getX());
					transformMirrored.update();
					//
					auto partitionX = static_cast<int>((transformMirrored.getTranslation().getX()) / PARTITION_SIZE);
					auto partitionZ = static_cast<int>((transformMirrored.getTranslation().getZ()) / PARTITION_SIZE);
					if (partitionX >= partitionsX) partitionX = partitionsX - 1; // special case if translation = 0.0, y, z
					if (partitionZ >= partitionsZ) partitionZ = partitionsZ - 1; // special case if translation = x, y, 0.0
					auto partitionIdx = partitionZ * partitionsX + partitionX;
					foliageMapsMirrored[partitionIdx][foliagePrototypeId].push_back(transformMirrored);
				}
			}
		}
	}
	foliageMaps = foliageMapsMirrored;
}
