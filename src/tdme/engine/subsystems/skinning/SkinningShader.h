#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/skinning/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;
using tdme::math::Matrix4x4;

/** 
 * Interface to compute shader skinning shader program
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::skinning::SkinningShader final
{
private:
	struct ModelSkinningCache {
		string id;
		vector<int32_t>* vboIds;
	};

	int32_t programId {  };
	int32_t shaderId {  };
	int32_t uniformSkinningCount { -1 };
	bool isRunning {  };
	bool initialized {  };
	GLRenderer* renderer {  };
	map<string, ModelSkinningCache> cache;

public:

	/** 
	 * @return initialized and ready to be used
	 */
	bool isInitialized();

	/** 
	 * Initialize renderer
	 */
	void initialize();

	/** 
	 * Use skinning program
	 */
	void useProgram();

	/** 
	 * Unuse skinning program
	 */
	void unUseProgram();

	/**
	 * Compute skinning
	 * @param object3DGroupMesh object 3d group mesh
	 */
	void computeSkinning(Object3DGroupMesh* object3DGroupMesh);

	/**
	 * Reset
	 */
	void reset();

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	SkinningShader(GLRenderer* renderer);
};
