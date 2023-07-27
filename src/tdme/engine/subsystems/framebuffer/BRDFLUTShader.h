#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/ColorTexture.h>

using tdme::engine::subsystems::renderer::Renderer;
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

	Renderer* renderer { nullptr };
	int32_t vertexShaderId { -1 };
	int32_t fragmentShaderId { -1 };
	int32_t programId { -1 };
	int32_t colorBufferTextureId { 0 };
	int32_t frameBufferId { -1 };
	bool initialized { false };

public:
	// forbid class copy
	CLASS_FORBID_COPY(BRDFLUTShader)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	BRDFLUTShader(Renderer* renderer);

	/**
	 * Public destructor
	 */
	~BRDFLUTShader();

	/**
	 * @return if initialized and ready to use
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
	 * @return color texture id
	 */
	inline int32_t getColorTextureId() override {
		return colorBufferTextureId;
	}
};
