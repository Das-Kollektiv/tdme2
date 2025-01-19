#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/skinning/fwd-tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/fwd-tdme.h>

using std::map;
using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::model::Node;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectNodeRenderer;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::utilities::FloatBuffer;
using tdme::utilities::ShortBuffer;

/**
 * Object node mesh specifically for rendering
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::ObjectNodeMesh final
{
	friend class ModelUtilitiesInternal;
	friend class ObjectBase;
	friend class ObjectBase_TransformedFacesIterator;
	friend class ObjectNode;
	friend class ObjectNodeRenderer;
	friend class EntityRenderer;
	friend class TransparentRenderFacesPool;
	friend class tdme::engine::subsystems::skinning::SkinningShader;

private:
	int instances;
	ObjectNodeRenderer* objectNodeRenderer { nullptr };
	Node* node { nullptr };
	int faceCount;
	const vector<Vector3>* vertices { nullptr };
	const vector<Vector3>* normals { nullptr };
	const vector<Vector3>* tangents { nullptr };
	const vector<Vector3>* bitangents { nullptr };
	const vector<Vector2>* textureCoordinates { nullptr };
	vector<int32_t> indices;
	vector<Vector3> transformedVertices;
	vector<Vector3> transformedNormals;
	vector<Vector3> transformedTangents;
	vector<Vector3> transformedBitangents;
	vector<Vector2> transformedTextureCoordinates;
	vector<unordered_map<string, Matrix4x4*>*> skinningMatrices;
	vector<vector<Matrix4x4*>> jointsSkinningMatrices;
	Engine::AnimationProcessingTarget animationProcessingTarget;

	int skinningMaxVertexWeights;
	vector<vector<float>> skinningJointWeight;

	Matrix4x4* nodeTransformMatrix { nullptr };

	vector<vector<vector<Matrix4x4*>>> skinningJointTransformMatrices;

	bool skinning;
	int skinningJoints;

	bool recreatedBuffers;

	// forbid class copy
	FORBID_CLASS_COPY(ObjectNodeMesh)

	/**
	 * Creates a object node mesh from node
	 * @param objectNodeRenderer object node renderer
	 * @param animationProcessingTarget animation processing target
	 * @param node node
	 * @param transformMatrices instances transformm matrices
	 * @param skinningMatrices instances skinning matrices
	 * @param instances instances
	 */
	ObjectNodeMesh(ObjectNodeRenderer* objectNodeRenderer, Engine::AnimationProcessingTarget animationProcessingTarget, Node* node, const vector<unordered_map<string, Matrix4x4*>*>& transformMatrices, const vector<unordered_map<string, Matrix4x4*>*>& skinningMatrices, int instances);

	/**
	 * Computes skinning
	 * @param contextIdx context index
	 * @param objectBase object base
	 */
	void computeSkinning(int contextIdx, ObjectBase* objectBase);

	/**
	 * Recreates node float buffers
	 */
	void recreateBuffers();

	/**
	 * @return has recreated buffers
	 */
	bool hasRecreatedBuffers() {
		return recreatedBuffers == true;
	}

	/**
	 * @return if buffers has been recreated and unsets state
	 */
	bool getRecreatedBuffers();

	/**
	 * Set up vertex indices buffer
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 * @param vboId vbo id
	 */
	void setupVertexIndicesBuffer(RendererBackend* rendererBackend, int contextIdx, int32_t vboId);

	/**
	 * Set up texture coordinates buffer
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 * @param vboId vbo id
	 */
	void setupTextureCoordinatesBuffer(RendererBackend* rendererBackend, int contextIdx, int32_t vboId);

	/**
	 * Set up vertices buffer
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 * @param vboId vbo id
	 */
	void setupVerticesBuffer(RendererBackend* rendererBackend, int contextIdx, int32_t vboId);

	/**
	 * Set up normals buffer
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 * @param vboId vbo id
	 */
	void setupNormalsBuffer(RendererBackend* rendererBackend, int contextIdx, int32_t vboId);

	/**
	 * Set up tangents buffer
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 * @param vboId vbo id
	 */
	void setupTangentsBuffer(RendererBackend* rendererBackend, int contextIdx, int32_t vboId);

	/**
	 * Set up bitangents buffer
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 * @param vboId vbo id
	 */
	void setupBitangentsBuffer(RendererBackend* rendererBackend, int contextIdx, int32_t vboId);

	/**
	 * Set up render node object origins data buffer
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 * @param vboId vbo id
	 */
	void setupOriginsBuffer(RendererBackend* rendererBackend, int contextIdx, int32_t vboId);

	/**
	 * Set up render node object lod data buffer
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 * @param vboId vbo id
	 * @param lodLevel LOD level
	 */
	void setupLodBuffer(RendererBackend* rendererBackend, int contextIdx, int32_t vboId, int lodLevel);

};
