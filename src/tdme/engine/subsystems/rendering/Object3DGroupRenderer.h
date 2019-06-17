#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/Object3DGroup.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/skinning/fwd-tdme.h>

using std::vector;

using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;
using tdme::engine::subsystems::rendering::Object3DRenderer;
using tdme::engine::subsystems::skinning::SkinningShader;

/** 
 * Object 3D group VBO renderer
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::Object3DGroupRenderer final
{
	friend class Object3DRenderer;
	friend class tdme::engine::Object3D;
	friend class tdme::engine::subsystems::skinning::SkinningShader;

private:
	Object3DGroup* object3DGroup {  };
	vector<int32_t>* vboBaseIds {  };
	vector<int32_t>* vboTangentBitangentIds {  };
	bool haveVBOs { false };
public:

	/**
	 * @return if preRender call is required
	 */
	inline bool needsPreRender() {
		return haveVBOs == false || object3DGroup->mesh->hasRecreatedBuffers() == true;
	}

	/**
	 * Pre render step like uploading VBOs and such
	 * @param context context
	 */
	void preRender(void* context);

	/** 
	 * Disposes the object 3d group
	 */
	void dispose();

	/**
	 * Constructor
	 * @param object3DGroup object 3D group
	 */
	Object3DGroupRenderer(Object3DGroup* object3DGroup);
};
