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
	int32_t programGlId {  };
	int32_t uniformDiffuseTextureUnit {  };
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
	 * Init shadow mapping
	 */
	void initialize();

	/** 
	 * Use render GUI program
	 */
	void useProgram();

	/** 
	 * Un use render GUI program
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
	 */
	FrameBufferRenderShader(GLRenderer* renderer);

	/**
	 * Public destructor
	 */
	~FrameBufferRenderShader();
};
