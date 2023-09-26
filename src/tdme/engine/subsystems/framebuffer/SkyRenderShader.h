#pragma once

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>

using std::string;
using std::unique_ptr;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::Texture;

/**
 * Sky render shader
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::framebuffer::SkyRenderShader final
{

private:
	Renderer* renderer { nullptr };

	int32_t cloudsVertexShaderId { -1 };
	int32_t cloudsFragmentShaderId { -1 };
	int32_t cloudsProgramId { -1 };
	int32_t cloudUniformSunPosition { -1 };
	int32_t cloudsUniformNoise { -1 };
	int32_t cloudsUniformWind { -1 };
	int32_t cloudsUniformSize { -1 };
	int32_t cloudsUniformSoftness { -1 };
	int32_t cloudsUniformCoverage { -1 };
	int32_t cloudsUniformHeight { -1 };
	int32_t cloudsUniformThickness { -1 };
	int32_t cloudsUniformAbsorption { -1 };
	int32_t cloudsUniformSteps { -1 };

	int32_t cloudsUniformTime { -1 };

	Texture* cloudsNoiseTexture { nullptr };
	int32_t cloudNoiseTextureId { 0 };

	int32_t renderVertexShaderId { -1 };
	int32_t renderFragmentShaderId { -1 };
	int32_t renderProgramId { -1 };
	int32_t renderUniformSampler { -1 };
	int32_t renderUniformSideVector { -1 };
	int32_t renderUniformUpVector { -1 };
	int32_t renderUniformForwardVector { -1 };

	bool initialized { false };

	unique_ptr<FrameBuffer> cloudsFrameBuffer;

public:
	// forbid class copy
	FORBID_CLASS_COPY(SkyRenderShader)

	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	SkyRenderShader(Renderer* renderer);

	/**
	 * Public destructor
	 */
	~SkyRenderShader();

	/**
	 * @return if initialized and ready to use
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
	 * Unload textures
	 */
	void unloadTextures();

	/**
	 * Load textures
	 * @param pathName path name
	 */
	void loadTextures(const string& pathName);

	/**
	 * Prepare
	 * @param engine engine
	 */
	void prepare(Engine* engine);

	/**
	 * Render
	 * @param engine engine
	 */
	void render(Engine* engine);

};
