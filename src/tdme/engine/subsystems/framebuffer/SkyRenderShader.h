#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>

using std::string;

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

	int32_t vertexShaderId { -1 };
	int32_t fragmentShaderId { -1 };
	int32_t programId { -1 };
	int32_t uniformTime { -1 };
	int32_t uniformAspectRatio { -1 };
	int32_t uniformForwardVector { -1 };
	int32_t uniformSideVector { -1 };
	int32_t uniformUpVector { -1 };
	int32_t uniformLIGHT0_DIRECTION { -1 };
	int32_t uniformLIGHT0_ENABLED { -1 };
	int32_t uniformLIGHT1_DIRECTION { -1 };
	int32_t uniformLIGHT1_ENABLED { -1 };
	int32_t uniformStarsTexture { -1 };

	Texture* starsTexture { nullptr };
	int32_t starsTextureId { 0 };

	bool initialized { false };

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
	 * Render
	 * @param engine engine
	 */
	void render(Engine* engine);

};
