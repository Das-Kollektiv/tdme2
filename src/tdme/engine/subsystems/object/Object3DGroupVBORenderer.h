#pragma once

#include <vector>

#include <tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>

using std::vector;

using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DVBORenderer;

/** 
 * Object 3D group render 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::Object3DGroupVBORenderer final
{
	friend class Object3DVBORenderer;

private:
	Object3DGroup* object3DGroup {  };
	vector<int32_t>* vboBaseIds {  };
	vector<int32_t>* vboTangentBitangentIds {  };
	vector<int32_t>* vboSkinningIds {  };
public:
	void preRender(Object3DVBORenderer* object3DVBORenderer);

	/** 
	 * Disposes the object 3d group
	 * @param gl
	 */
	void dispose();

	/**
	 * Constructor
	 * @param object 3D group
	 */
	Object3DGroupVBORenderer(Object3DGroup* object3DGroup);
};
