#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/ColorTexture.h>

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::ColorTexture;

/**
 * BRDFLUT render shader
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::framebuffer::BRDFLUTShader final: public ColorTexture
{

private:
	static constexpr int BRDFLUT_WIDTH { 1024 };
	static constexpr int BRDFLUT_HEIGHT { 1024 };

	RendererBackend* rendererBackend { nullptr };
	int32_t vertexShaderId { -1 };
	int32_t fragmentShaderId { -1 };
	int32_t programId { -1 };
	int32_t colorBufferTextureId { 0 };
	int32_t frameBufferId { -1 };
	bool initialized { false };

public:
	// forbid class copy
	FORBID_CLASS_COPY(BRDFLUTShader)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	BRDFLUTShader(RendererBackend* rendererBackend);

	/**
	 * Public destructor
	 */
	~BRDFLUTShader();

	/**
	 * @returns if initialized and ready to use
	 */
	bool isInitialized();

	/**
	 * Initialize
	 */
	void initialize();

	/**
	 * Generate
	 */
	void generate();

	/**
	 * @returns color texture id
	 */
	inline int32_t getColorTextureId() override {
		return colorBufferTextureId;
	}
};
