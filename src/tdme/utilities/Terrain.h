#pragma once

#include <tdme/utilities/fwd-tdme.h>

#include <vector>

#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/Vector3.h>

using std::vector;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::math::Vector3;

/**
 * Terrain tool
 * @author Andreas Drewke
 */
class tdme::utilities::Terrain
{
public:
	static constexpr float STEP_SIZE { 0.5f };

private:
	/**
	 * @param terrainHeightVector terrain height vector
	 * @param verticesPerZ vertices per x
	 * @param x x
	 * @param z z
	 * @return terrain vertex
	 */
	static inline bool getTerrainVertex(const vector<float>& terrainHeightVector, int verticesPerX, int verticesPerZ, int x, int z, Vector3& vertex) {
		if (x < 0 || x >= verticesPerX) return false;
		if (z < 0 || z>= verticesPerZ) return false;
		vertex.set(
			x * STEP_SIZE,
			terrainHeightVector[z * verticesPerX + x],
			z * STEP_SIZE
		);
		return true;
	}

	/**
	 * Compute terrain vertex normal
	 * @param terrainHeightVector terrain height vector
	 * @param verticesPerX vertices per x
	 * @param verticesPerZ vertices per z
	 * @param x x
	 * @param z z
	 * @return normal for given vertex index
	 */
	static const Vector3 computeTerrainVertexNormal(const vector<float>& terrainHeightVector, int verticesPerX, int verticesPerZ, int x, int z);

public:
	enum BrushOperation {
		BRUSHOPERATION_ADD,
		BRUSHOPERATION_SUBTRACT,
		BRUSHOPERATION_FLATTEN,
		BRUSHOPERATION_DELETE,
		BRUSHOPERATION_SMOOTH
	};

	/**
	 * Creates a terrain model
	 * @param width width
	 * @param depth depth
	 * @param y float y
	 * @param terrainHeightVector terrain height vector
	 * @param terrainBoundingBox terrain bounding box
	 * @param terrainModels terrain models
	 */
	static void createTerrainModels(float width, float depth, float y, vector<float>& terrainHeightVector, BoundingBox& terrainBoundingBox, vector<Model*>& terrainModels);

	/**
	 * Apply brush to terrain model
	 * @param terrainBoundingBox terrain bounding box
	 * @param terrainModels terrain models
	 * @param terrainHeightVector terrain height vector
	 * @param brushCenterPosition brush center position
	 * @param brushTexture brush texture
	 * @param brushScale brush scale
	 * @param brushStrength brush strength
	 * @param brushOperation brush operation
	 * @param flattenHeight flatten height
	 *
	 */
	static void applyBrushToTerrainModel(
		const BoundingBox& terrainBoundingBox,
		vector<Model*> terrainModels,
		vector<float>& terrainHeightVector,
		const Vector3& brushCenterPosition,
		Texture* brushTexture,
		float brushScale,
		float brushStrength,
		BrushOperation brushOperation,
		float flattenHeight = 0.0f
	);

	/**
	 * Get terrain model flatten height
	 * @param terrainBoundingBox terrain bounding box
	 * @param terrainModels terrain models
	 * @param terrainHeightVector terrain height vector
	 * @param flattenHeight flatten height
	 *
	 */
	static bool getTerrainModelFlattenHeight(
		const BoundingBox& terrainBoundingBox,
		vector<Model*> terrainModels,
		vector<float>& terrainHeightVector,
		const Vector3& brushCenterPosition,
		float& flattenHeight
	);
};
