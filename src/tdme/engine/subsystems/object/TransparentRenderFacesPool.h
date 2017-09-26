// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderFacesPool.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Pool.h>

using std::vector;

using tdme::engine::subsystems::object::Object3DGroup;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::Pool;

/** 
 * Transparent render faces pool
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::TransparentRenderFacesPool final
{
private:
	static constexpr int32_t FACES_MAX { 16384 };
	vector<TransparentRenderFace*> transparentRenderFaces {  };
	Pool<TransparentRenderFace*>* transparentRenderFacesPool {  };

public: /* protected */

	/** 
	 * Creates an array of transparent render faces from
	 * @param model view matrix
	 * @param object3D group
	 * @param faces entity index
	 * @param face index
	 * @param face index for texture coordinates
	 * @return
	 */
	void createTransparentRenderFaces(Matrix4x4& modelViewMatrix, Object3DGroup* object3DGroup, int32_t facesEntityIdx, int32_t faceIdx);

public:

	/** 
	 * @return allocated faces
	 */
	int32_t size();

public: /* protected */

	/** 
	 * Reset
	 */
	void reset();

	/** 
	 * @return transparent render faces vector
	 */
	vector<TransparentRenderFace*>* getTransparentRenderFaces();

	/**
	 * Public constructor
	 */
	TransparentRenderFacesPool();
};
