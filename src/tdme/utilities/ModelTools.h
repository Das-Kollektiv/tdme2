#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/fwd-tdme.h>

using std::array;
using std::map;
using std::string;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::fileio::ProgressCallback;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::Skinning;
using tdme::engine::Transform;
using tdme::math::Vector3;

/**
 * Model tools functions class
 * @author Andreas Drewke
 */
class tdme::utilities::ModelTools final
{

public:
	enum VertexOrder { VERTEXORDER_CLOCKWISE, VERTEXORDER_COUNTERCLOCKWISE };

	/**
	 * Determines vertex order of face
	 * @param vertices vertices
	 * @return vertex order
	 */
	static VertexOrder determineVertexOrder(const vector<Vector3>& vertices);

	/**
	 * Computes face normal for given face vertices
	 * @param vertices face vertices
	 * @return computed face normal
	 */
	inline static Vector3 computeNormal(const array<Vector3,3>& vertices) {
		// face normal
		auto normal = Vector3::computeCrossProduct(
			(vertices)[1].clone().sub((vertices)[0]),
			(vertices)[2].clone().sub((vertices)[0])
		);
		// check if zero?
		if (normal.computeLengthSquared() < Math::EPSILON * Math::EPSILON) {
			// take up vector
			normal.set(0.0f, 1.0f, 0.0f);
		} else {
			// otherwise normalize
			normal.normalize();
		}
		return normal;
	}

	/**
	 * Computes face normals for given face vertices
	 * these normals will not be smooth
	 * @param vertices face vertices
	 * @return normals computed face normals
	 */
	static array<Vector3,3> computeNormals(const array<Vector3,3>& vertices) {
		// face normal
		auto normal = computeNormal(vertices);

		// compute vertex normal
		array<Vector3,3> normals;
		for (auto i = 0; i < vertices.size(); i++) {
			normals[i].set(normal);
		}

		//
		return normals;
	}

	/**
	 * Prepare for indexed rendering
	 * @param model model
	 */
	static void prepareForIndexedRendering(Model* model);

private:

	/**
	 * Prepares this node for indexed rendering
	 * @param nodes nodes
	 */
	static void prepareForIndexedRendering(const map<string, Node*>& nodes);

	/**
	 * Maps original vertices to new vertice mapping
	 * @param skinning skinning
	 * @param vertexMapping vertice mapping / new vertex index to old vertex index
	 * @param vertices vertice count
	 */
	static void prepareForIndexedRendering(Skinning* skinning, const vector<int32_t>& vertexMapping, int32_t vertices);

public:

	/**
	 * Set up joints for skinning nodes
	 * @param model model
	 */
	static void setupJoints(Model* model);

private:

	/**
	 * Sets up a node as joint taking all subnodes into account
	 * @param root node
	 */
	static void setJoint(Node* root);

public:

	/**
	 * Fix animation length
	 * @param model model
	 */
	static void fixAnimationLength(Model* model);

private:

	/**
	 * Fixes animation length as sometimes they are only given partially, which is not supported by engine
	 * @param root node
	 * @param frames frames
	 */
	static void fixAnimationLength(Node* root, int32_t frames);

public:

	/**
	 * Check default animation
	 * @param model model
	 * @return if animation exists
	 */
	static bool hasDefaultAnimation(Model* model);

	/**
	 * Create default animation
	 * @param model model
	 * @param frames frames
	 */
	static void createDefaultAnimation(Model* model, int32_t frames);

	/**
	 * Clone material
	 * @param material material
	 * @param id new id to use
	 * @return material
	 */
	static Material* cloneMaterial(const Material* material, const string& id = string());

	/**
	 * Create model from source sub nodes into target sub nodes
	 * @param sourceNode source node
	 * @param targetModel target model
	 * @param targetParentNode target parent node
	 * @param cloneMesh clone mesh
	 */
	static void cloneNode(Node* sourceNode, Model* targetModel, Node* targetParentNode = nullptr, bool cloneMesh = true);

private:

	/**
	 * Partition sub nodes
	 * @param sourceNode source node to partition
	 * @param modelsByPartition models by partition
	 * @param modelsPosition models position
	 * @param parentTransformMatrix parent transform matrix
	 */
	static void partitionNode(Node* sourceNode, map<string, Model*>& modelsByPartition, map<string, Vector3>& modelsPosition, const Matrix4x4& parentTransformMatrix);

	/**
	 * Shrink to fit node
	 * @param node node
	 */
	static void shrinkToFit(Node* node);

	/**
	 * Find all faces that include vertex and compute the avarage normal
	 * @param node node
	 * @param vertex vertex
	 * @param normals normals
	 * @param normal normal
	 */
	inline static bool interpolateNormal(Node* node, const Vector3& vertex, const vector<Vector3>& normals, Vector3& normal) {
		array<Vector3, 3> vertices;
		auto normalCount = 0;
		normal.set(0.0f, 0.0f, 0.0f);
		for (const auto& facesEntity: node->getFacesEntities()) {
			for (const auto& face: facesEntity.getFaces()) {
				for (auto i = 0; i < vertices.size(); i++) {
					if (vertex.equals(node->getVertices()[face.getVertexIndices()[i]]) == true) {
						normal.add(normals[face.getNormalIndices()[0]]);
						normalCount++;
						break;
					}
				}
				if (normalCount == 6) break;
			}
			if (normalCount == 6) break;
		}
		if (normalCount > 1) {
			normal.normalize();
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Compute normals
	 * @param node node
	 */
	static float computeNormals(Node* node, ProgressCallback* progressCallback = nullptr, float incrementPerFace = 0.0f, float progress = 0.0f);

	/**
	 * Compute face count
	 * @param node node
	 */
	static int determineFaceCount(Node* node);

public:
	/**
	 * Partition model
	 * @param model model
	 * @param transform transform
	 * @param modelsByPartition models by partition
	 * @param modelsPosition models position
	 */
	static void partition(Model* model, const Transform& transform, map<string, Model*>& modelsByPartition, map<string, Vector3>& modelsPosition);

	/**
	 * Shrink to fit
	 * @param model model
	 */
	static void shrinkToFit(Model* model);

	/**
	 * Compute normals
	 * @param node node
	 */
	static void computeNormals(Model* model, ProgressCallback* progressCallback = nullptr);

	/**
	 * Prepare model for specific shader
	 * @param model model
	 * @param shader optional shader
	 */
	static void prepareForShader(Model* model, const string& shader = string());

	/**
	 * @returns if model has been optimized
	 */
	static bool isOptimizedModel(Model* model);

	/**
	 * Optimizes model in terms of material / node reduction
	 * @param model model
	 * @param texturePathName texturePathName
	 * @param excludeDiffuseTextureFileNamePatterns exclude diffuse texture file name patterns
	 */
	static Model* optimizeModel(Model* model, const string& texturePathName = string(), const vector<string>& excludeDiffuseTextureFileNamePatterns = vector<string>());

	/**
	 * Compute tangents and bitangents for given node
	 * @param node node
	 */
	static void computeTangentsAndBitangents(Node* node);

	/**
	 * Change front face from counter clock wise to clock wise or clock wise to counter clock wise
	 * @param node node
	 * @param applyToSubNodes apply to sub nodes
	 */
	static void changeFrontFace(Node* node, bool applyToSubNodes);

	/**
	 * Change front face from counter clock wise to clock wise or clock wise to counter clock wise
	 * @param model model
	 */
	static void changeFrontFace(Model* model);

private:

	/**
	 * Prepare node for default shader
	 * @param node node
	 * @param parentTransformMatrix parent transform matrix
	 */
	static void prepareForDefaultShader(Node* node, const Matrix4x4& parentTransformMatrix);

	/**
	 * Prepare node for foliage shader
	 * @param node node
	 * @param parentTransformMatrix parent transform matrix
	 * @param shader shader
	 */
	static void prepareForFoliageTreeShader(Node* node, const Matrix4x4& parentTransformMatrix, const string& shader);

	/**
	 * Prepare node for water shader
	 * @param node node
	 * @param parentTransformMatrix parent transform matrix
	 */
	static void prepareForWaterShader(Node* node, const Matrix4x4& parentTransformMatrix);

	/**
	 * Check for optimization
	 * @param node node
	 * @param materialUseCount material use count
	 * @param excludeDiffuseTextureFileNamePatterns exclude diffuse texture file name patterns
	 */
	static void checkForOptimization(Node* node, map<string, int>& materialUseCount, const vector<string>& excludeDiffuseTextureFileNamePatterns);

	/**
	 * Prepare for optimization
	 * @param node node
	 * @param parentTransformMatrix parent transform matrix
	 * @param materialUseCount material use count
	 */
	static void prepareForOptimization(Node* node, const Matrix4x4& parentTransformMatrix);

	/**
	 * Prepare for optimization
	 * @param sourceNode source node
	 * @param targetModel target model
	 * @param diffuseTextureAtlasSize diffuse texture atlas size
	 * @param diffuseTextureAtlasIndices diffuse texture atlas indices
	 * @param excludeDiffuseTextureFileNamePatterns exclude diffuse texture file name patterns
	 */
	static void optimizeNode(Node* sourceNode, Model* targetModel, int diffuseTextureAtlasSize, const map<string, int>& diffuseTextureAtlasIndices, const vector<string>& excludeDiffuseTextureFileNamePatterns);

};
