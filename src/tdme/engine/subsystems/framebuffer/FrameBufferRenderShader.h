#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::renderer::RendererBackend;

/**
 * Frame buffer render shader
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::framebuffer::FrameBufferRenderShader final
{

private:
	RendererBackend* rendererBackend { nullptr };
	int32_t vertexShaderId { -1 };
	int32_t fragmentShaderId { -1 };
	int32_t programId { -1 };
	int32_t uniformColorBufferTextureUnit { -1 };
	int32_t uniformDepthBufferTextureUnit { -1 };
	int32_t vboVertices { -1 };
	int32_t vboTextureCoordinates {-1  };
	bool initialized;
	bool isRunning;

public:
	// forbid class copy
	FORBID_CLASS_COPY(FrameBufferRenderShader)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	FrameBufferRenderShader(RendererBackend* rendererBackend);

	/**
	 * Public destructor
	 */
	~FrameBufferRenderShader();

	/**
	 * @returns if initialized and ready to use
	 */
	bool isInitialized();

	/**
	 * Initialize
	 */
	void initialize();

	/**
	 * Dispose
	 */
	void dispose();

	/**
	 * Use render program
	 */
	void useProgram();

	/**
	 * Un use render program
	 */
	void unUseProgram();

	/**
	 * @returns vertices VBO
	 */
	inline int32_t getVBOVertices() {
		return vboVertices;
	}

	/**
	 * @returns texture coordinates VBO
	 */
	inline int32_t getVBOTextureCoordinates() {
		return vboTextureCoordinates;
	}

};
