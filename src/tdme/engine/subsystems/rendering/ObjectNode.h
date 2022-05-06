#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/skinning/fwd-tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/utilities/fwd-tdme.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::model::Node;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::engine::subsystems::rendering::ObjectNodeRenderer;
using tdme::engine::Engine;
using tdme::engine::Object;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;

/**
 * Object 3d node specifically for rendering
 * @author Andreas Drewke
 * @version $Id$
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
	vector<Matrix2D3x3> textureMatricesByEntities;
	vector<int32_t> specularMaterialDiffuseTextureIdsByEntities;
	vector<int32_t> specularMaterialDynamicDiffuseTextureIdsByEntities;
	vector<int32_t> specularMaterialSpecularTextureIdsByEntities;
	vector<int32_t> specularMaterialNormalTextureIdsByEntities;
	vector<int32_t> pbrMaterialBaseColorTextureIdsByEntities;
	vector<int32_t> pbrMaterialMetallicRoughnessTextureIdsByEntities;
	vector<int32_t> pbrMaterialNormalTextureIdsByEntities;
	ObjectNodeRenderer* renderer { nullptr };
	ObjectNodeMesh* mesh { nullptr };
	Matrix4x4* nodeTransformationsMatrix { nullptr };

	/**
	 * Creates object 3d nodes from given object3d base object
	 * @param object object 3d base
	 * @param useManagers use mesh and object 3d renderer node managers
	 * @param animationProcessingTarget animation processing target
	 * @param object3DNodes object 3d nodes array
	 * @return object 3d node
	 */
	static void createNodes(ObjectBase* object, bool useManagers, Engine::AnimationProcessingTarget animationProcessingTarget, vector<ObjectNode*>& object3DNodes);

	/**
	 * Applies transformations to meshes for given object 3d nodes
	 * @param contextIdx context index
	 * @param object3DNodes node render data list
	 */
	static void computeTransformations(int contextIdx, vector<ObjectNode*>& object3DNodes);

	/**
	 * Set up textures for given object3d node and faces entity
	 * @param renderer renderer
	 * @param contextIdx context index
	 * @param object3DNode object 3D node
	 * @param facesEntityIdx faces entity idx
	 */
	static void setupTextures(Renderer* renderer, int contextIdx, ObjectNode* object3DNode, int32_t facesEntityIdx);

	/**
	 * Creates a object 3d nodes recursively for given node and it sub nodes
	 * @param object3D object 3D base
	 * @param nodes nodes
	 * @param animated animated
	 * @param useManagers use mesh and object 3d render node managers
	 * @param animationProcessingTarget animation processing target
	 * @param object3DNodes object 3D nodes
	 */
	static void createNodes(ObjectBase* object3D, const map<string, Node*>& nodes, bool animated, bool useManagers, Engine::AnimationProcessingTarget animationProcessingTarget, vector<ObjectNode*>& object3DNodes);

	/**
	 * Dispose
	 */
	void dispose();

public:
	/**
	 * Public constructor
	 */
	ObjectNode();

	/**
	 * Destructor
	 */
	~ObjectNode();
};
