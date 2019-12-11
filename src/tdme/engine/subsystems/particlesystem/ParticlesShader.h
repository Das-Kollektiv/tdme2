#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::Engine;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;

/** 
 * Particles shader program
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::particlesystem::ParticlesShader final
{
private:
	int32_t renderProgramId { -1 };
	int32_t renderFragmentShaderId { -1 };
	int32_t renderVertexShaderId { -1 };
	int32_t uniformMVPMatrix { -1 };
	int32_t uniformMVMatrix { -1 };
	int32_t uniformPointSize { -1 };
	int32_t uniformDiffuseTextureUnit { -1 };
	int32_t uniformEffectColorMul { -1 };
	int32_t uniformEffectColorAdd { -1 };
	Matrix4x4 mvpMatrix;
	bool isRunning;
	bool initialized;
	Engine* engine { nullptr };
	Renderer* renderer { nullptr };

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
	 * Use lighting program
	 * @param context context
	 */
	void useProgram(void* context);

	/** 
	 * Update effect to program
	 * @param context context
	 */
	void updateEffect(void* context);

	/** 
	 * Unuse particles shader program
	 * @param context context
	 */
	void unUseProgram(void* context);

	/** 
	 * Update matrices to program
	 * @param context context
	 */
	void updateMatrices(void* context);

	/**
	 * Set parameters
	 * @param context context
	 * @param textureId texture id
	 * @param pointSize point size
	 */
	void setParameters(void* context, int32_t textureId, float pointSize);

	/**
	 * Public constructor
	 * @param engine engine
	 * @param renderer renderer
	 */
	ParticlesShader(Engine* engine, Renderer* renderer);
};
