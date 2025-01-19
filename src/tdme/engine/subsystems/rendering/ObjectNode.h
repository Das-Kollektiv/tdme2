#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/skinning/fwd-tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/utilities/fwd-tdme.h>

using std::make_unique;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

using tdme::engine::model::Node;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::engine::subsystems::rendering::ObjectNodeRenderer;
using tdme::engine::Engine;
using tdme::engine::Object;
using tdme::math::Matrix3x3;
using tdme::math::Matrix4x4;

/**
 * Object node specifically for rendering
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::ObjectNode final
{
	friend class tdme::engine::Object;
	friend class ModelUtilitiesInternal;
	friend class ObjectBase;
	friend class ObjectBase_TransformedFacesIterator;
	friend class ObjectNodeMesh;
	friend class ObjectNodeRenderer;
	friend class ObjectInternal;
	friend class EntityRenderer;
	friend class TransparentRenderFacesPool;
	friend class TransparentRenderFacesGroup;
	friend class tdme::engine::subsystems::skinning::SkinningShader;

private:
	STATIC_DLL_IMPEXT static int64_t counter;

	static constexpr int32_t TEXTUREID_NONE { -1 };
	static constexpr int32_t TEXTUREID_NOTUSED { 0 };

	string id;
	ObjectBase* object { nullptr };
	Node* node { nullptr };
	bool animated { false };
	vector<Matrix3x3> textureMatricesByEntities;
	vector<int32_t> specularMaterialDiffuseTextureIdsByEntities;
	vector<int32_t> specularMaterialDynamicDiffuseTextureIdsByEntities;
	vector<int32_t> specularMaterialSpecularTextureIdsByEntities;
	vector<int32_t> specularMaterialNormalTextureIdsByEntities;
	vector<int32_t> pbrMaterialBaseColorTextureIdsByEntities;
	vector<int32_t> pbrMaterialMetallicRoughnessTextureIdsByEntities;
	vector<int32_t> pbrMaterialNormalTextureIdsByEntities;
	vector<int32_t> pbrMaterialEmissiveTextureIdsByEntities;
	unique_ptr<ObjectNodeRenderer> rendererBackend;
	ObjectNodeMesh* mesh { nullptr };
	Matrix4x4* nodeTransformMatrix { nullptr };

	/**
	 * Creates object nodes from given object base object
	 * @param object object base
	 * @param useManagers use mesh manager
	 * @param animationProcessingTarget animation processing target
	 * @param objectNodes object nodes array
	 * @returns object node
	 */
	static void createNodes(ObjectBase* object, bool useManagers, Engine::AnimationProcessingTarget animationProcessingTarget, vector<ObjectNode*>& objectNodes);

	/**
	 * Computes animation for given object nodes
	 * @param contextIdx context index
	 * @param objectNodes node render data list
	 */
	static void computeAnimation(int contextIdx, vector<ObjectNode*>& objectNodes);

	/**
	 * Set up textures for given object node and faces entity
	 * @param rendererBackend renderer backend
	 * @param contextIdx context index
	 * @param objectNode object node
	 * @param facesEntityIdx faces entity idx
	 */
	static void setupTextures(RendererBackend* rendererBackend, int contextIdx, ObjectNode* objectNode, int32_t facesEntityIdx);

	/**
	 * Creates a object nodes recursively for given node and it sub nodes
	 * @param object object base
	 * @param nodes nodes
	 * @param animated animated
	 * @param useManagers use mesh manager
	 * @param animationProcessingTarget animation processing target
	 * @param objectNodes object nodes
	 */
	static void createNodes(ObjectBase* object, const unordered_map<string, Node*>& nodes, bool animated, bool useManagers, Engine::AnimationProcessingTarget animationProcessingTarget, vector<ObjectNode*>& objectNodes);

	/**
	 * Dispose
	 */
	void dispose();

public:
	// forbid class copy
	FORBID_CLASS_COPY(ObjectNode)

	/**
	 * Public constructor
	 */
	ObjectNode();

	/**
	 * Destructor
	 */
	~ObjectNode();

	/**
	 * Update node transformations matrix
	 */
	void updateNodeTransformationsMatrix();

};
