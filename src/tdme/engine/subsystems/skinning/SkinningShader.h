#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/skinning/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/threading/Mutex.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::math::Matrix4x4;
using tdme::os::threading::Mutex;

/**
 * Interface to compute shader skinning shader program
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::skinning::SkinningShader final
{
private:
	struct SkinningContext {
		volatile bool running { false };
	};

	struct ModelSkinningCache {
		string id;
		vector<int32_t>* vboIds;
		vector<vector<int32_t>*> matricesVboIds;
	};

	int32_t programId { -1 };
	int32_t shaderId { -1 };
	int32_t uniformVertexCount { -1 };
	int32_t uniformMatrixCount { -1 };
	int32_t uniformInstanceCount { -1 };
	bool isRunning;
	bool initialized;
	RendererBackend* rendererBackend { nullptr };
	vector<SkinningContext> contexts;
	map<string, ModelSkinningCache> cache;
	Mutex mutex;

public:
	// forbid class copy
	FORBID_CLASS_COPY(SkinningShader)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	SkinningShader(RendererBackend* rendererBackend);

	/**
	 * @returns initialized and ready to be used
	 */
	bool isInitialized();

	/**
	 * Initialize
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
	 * @param contextIdx context index
	 * @param objectBase object base
	 * @param objectNodeMesh object node mesh
	 */
	void computeSkinning(int contextIdx, ObjectBase* objectBase, ObjectNodeMesh* objectNodeMesh);

	/**
	 * Reset
	 */
	void reset();

};
