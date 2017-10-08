
#pragma once

#include <tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

/** 
 * Pre shadow mapping shader for render shadow map pass 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre
{
private:
	GLRenderer* renderer {  };
	int32_t preVertexShaderGlId {  };
	int32_t preFragmentShaderGlId {  };
	int32_t preUniformMVPMatrix {  };
	int32_t preProgramGlId {  };
	bool initialized {  };

public:

	/** 
	 * @return if initialized and ready to use
	 */
	virtual bool isInitialized();

	/** 
	 * Init shadow mapping
	 */
	virtual void initialize();

	/** 
	 * Use pre render shadow mapping program
	 */
	virtual void useProgram();

	/** 
	 * Un use pre render shadow mapping program
	 */
	virtual void unUseProgram();

	/** 
	 * Set up pre program mvp matrix
	 * @param mvp matrix
	 */
	virtual void setProgramMVPMatrix(Matrix4x4* mvpMatrix);

	/**
	 * Constructor
	 * @param renderer
	 */
	ShadowMappingShaderPre(GLRenderer* renderer);
};
