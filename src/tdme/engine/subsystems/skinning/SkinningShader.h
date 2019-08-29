#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/skinning/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/threading/Mutex.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;
using tdme::math::Matrix4x4;
using tdme::os::threading::Mutex;

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
		vector<vector<int32_t>*> matricesVboIds;
	};

	int32_t programId {  };
	int32_t shaderId {  };
	int32_t uniformSkinningCount { -1 };
	bool isRunning {  };
	bool initialized {  };
	Renderer* renderer {  };
	map<string, ModelSkinningCache> cache;
	Mutex mutex;

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
	 * @param context context
	 * @param object3DGroupMesh object 3d group mesh
	 */
	void computeSkinning(void* context, Object3DGroupMesh* object3DGroupMesh);

	/**
	 * Reset
	 */
	void reset();

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	SkinningShader(Renderer* renderer);
};
