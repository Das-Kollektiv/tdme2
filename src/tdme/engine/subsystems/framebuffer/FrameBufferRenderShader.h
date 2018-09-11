#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * Frame buffer render shader
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::framebuffer::FrameBufferRenderShader final
{

private:
	GLRenderer* renderer {  };
	int32_t vertexShaderGlId {  };
	int32_t fragmentShaderGlId {  };
	int32_t programId {  };
	int32_t uniformColorBufferTextureUnit { -1 };
	int32_t uniformDepthBufferTextureUnit { -1 };
	int32_t vboVertices {  };
	int32_t vboTextureCoordinates {  };
	bool initialized {  };
	bool isRunning {  };

public:

	/** 
	 * @return if initialized and ready to use
	 */
	bool isInitialized();

	/** 
	 * Initialize
	 */
	void initialize();

	/** 
	 * Use render program
	 */
	void useProgram();

	/** 
	 * Un use render program
	 */
	void unUseProgram();

	/**
	 * @return vertices VBO
	 */
	inline int32_t getVBOVertices() {
		return vboVertices;
	}

	/**
	 * @return texture coordinates VBO
	 */
	inline int32_t getVBOTextureCoordinates() {
		return vboTextureCoordinates;
	}

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	FrameBufferRenderShader(GLRenderer* renderer);

	/**
	 * Public destructor
	 */
	~FrameBufferRenderShader();
};
