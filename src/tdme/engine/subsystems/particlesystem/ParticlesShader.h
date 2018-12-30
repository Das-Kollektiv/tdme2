
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::Engine;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

/** 
 * Interface to particles shader program
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::particlesystem::ParticlesShader final
{
private:
	int32_t renderProgramId {  };
	int32_t renderFragmentShaderId {  };
	int32_t renderVertexShaderId {  };
	int32_t uniformMVPMatrix {  };
	int32_t uniformMVMatrix {  };
	int32_t uniformPointSize {  };
	int32_t uniformDiffuseTextureUnit {  };
	int32_t uniformEffectColorMul {  };
	int32_t uniformEffectColorAdd {  };
	Matrix4x4 mvpMatrix {  };
	bool isRunning {  };
	bool initialized {  };
	Engine* engine {  };
	GLRenderer* renderer {  };

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
	 */
	void useProgram();

	/** 
	 * Update effect to program
	 * @param renderer renderer
	 */
	void updateEffect(GLRenderer* renderer);

	/** 
	 * Unuse lighting program
	 */
	void unUseProgram();

	/** 
	 * Update matrices to program
	 * @param renderer renderer
	 */
	void updateMatrices(GLRenderer* renderer);

	/**
	 * Set parameters
	 * @param textureId texture id
	 * @param pointSize point size
	 */
	void setParameters(int32_t textureId, float pointSize);

	/**
	 * Public constructor
	 * @param engine engine
	 * @param renderer renderer
	 */
	ParticlesShader(Engine* engine, GLRenderer* renderer);
};
