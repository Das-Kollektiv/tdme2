#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>

using tdme::engine::subsystems::object::Object3DGroup;

/** 
 * Transparent face to be rendered
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::subsystems::object::TransparentRenderFace final
{
	Object3DGroup* object3DGroup {  };
	int32_t facesEntityIdx {  };
	int32_t faceIdx {  };
	float distanceFromCamera {  };

	/**
	 * Compare
	 * @param face 1
	 * @param face 2
	 */
	inline static bool compare(TransparentRenderFace* face1, TransparentRenderFace* face2) {
		return face1->distanceFromCamera > face2->distanceFromCamera;
	}

};
