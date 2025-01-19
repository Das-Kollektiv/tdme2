#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/ObjectNode.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>
#include <tdme/engine/subsystems/skinning/fwd-tdme.h>

using std::vector;

using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::engine::subsystems::skinning::SkinningShader;

/**
 * Object node VBO rendererBackend
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::rendering::ObjectNodeRenderer final
{
	friend class EntityRenderer;
	friend class tdme::engine::Object;
	friend class tdme::engine::subsystems::rendering::ObjectNodeMesh;
	friend class tdme::engine::subsystems::skinning::SkinningShader;

private:
	ObjectNode* objectNode { nullptr };
	VBOManager::ManagedVBO* vboManagedBase { nullptr };
	VBOManager::ManagedVBO* vboManagedNormalMapping { nullptr };
	VBOManager::ManagedVBO* vboManagedOrigins { nullptr };
	VBOManager::ManagedVBO* vboManagedLods { nullptr };
	vector<int32_t>* vboBaseIds { nullptr };
	vector<int32_t>* vboNormalMappingIds { nullptr  };
	vector<int32_t>* vboOrigins { nullptr };
	vector<int32_t>* vboLods { nullptr };
	bool haveVBOs { false };

public:
	// forbid class copy
	FORBID_CLASS_COPY(ObjectNodeRenderer)

	/**
	 * Constructor
	 * @param objectNode object node
	 */
	ObjectNodeRenderer(ObjectNode* objectNode);

	/**
	 * @returns if preRender call is required
	 */
	inline bool needsPreRender() {
		return haveVBOs == false || objectNode->mesh->hasRecreatedBuffers() == true || objectNode->mesh->node->hasUpdate();
	}

	/**
	 * Pre render step like uploading VBOs and such
	 * @param contextIdx context index
	 */
	void preRender(int contextIdx);

	/**
	 * Disposes the object node
	 */
	void dispose();

};
