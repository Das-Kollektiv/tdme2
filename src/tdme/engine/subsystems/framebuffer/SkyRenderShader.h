#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>

using std::string;

using tdme::engine::subsystems::renderer::RendererBackend;
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
	RendererBackend* rendererBackend { nullptr };

	int32_t vertexShaderId { -1 };
	int32_t fragmentShaderId { -1 };
	int32_t programId { -1 };
	int32_t uniformLightScatteringPass { -1 };
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
	int32_t uniformCloudsTopTexture { -1 };
	int32_t uniformCloudsMiddleTexture { -1 };
	int32_t uniformCloudsBottomTexture { -1 };

	// sky
	int32_t uniformDayTopColor { -1 };
	int32_t uniformDayBottomColor { -1 };
	int32_t uniformSunsetTopColor { -1 };
	int32_t uniformSunsetBottomColor { -1 };
	int32_t uniformNightTopColor { -1 };
	int32_t uniformNightBottomColor { -1 };
	// horizon
	int32_t uniformHorizonColor { -1 };
	int32_t uniformHorizonBlur { -1 };
	// sun
	int32_t uniformSunColorFactor { -1 };
	int32_t uniformSunColor { -1 };
	int32_t uniformSunSunsetColor { -1 };
	int32_t uniformSunSize { -1 };
	int32_t uniformSunBlur { -1 };
	// moon
	int32_t uniformMoonColorFactor { -1 };
	int32_t uniformMoonColor { -1 };
	int32_t uniformMoonSize { -1 };
	int32_t uniformMoonBlur { -1 };
	// clouds
	int32_t uniformCloudsEdgeColor { -1 };
	int32_t uniformCloudsTopColor { -1 };
	int32_t uniformCloudsMiddleColor { -1 };
	int32_t uniformCloudsBottomColor { -1 };
	int32_t uniformCloudsSpeed { -1 };
	int32_t uniformCloudsDirection { -1 };
	int32_t uniformCloudsScale { -1 };
	int32_t uniformCloudsCutoff { -1 };
	int32_t uniformCloudsFuzziness { -1 };
	int32_t uniformCloudsWeight { -1 };
	int32_t uniformCloudsBlur { -1 };
	int32_t uniformStarsSpeed { -1 };

	Texture* starsTexture { nullptr };
	int32_t starsTextureId { 0 };
	Texture* cloudsTopTexture { nullptr };
	int32_t cloudsTopTextureId { 0 };
	Texture* cloudsMiddleTexture { nullptr };
	int32_t cloudsMiddleTextureId { 0 };
	Texture* cloudsBottomTexture { nullptr };
	int32_t cloudsBottomTextureId { 0 };

	bool initialized { false };

public:
	// forbid class copy
	FORBID_CLASS_COPY(SkyRenderShader)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	SkyRenderShader(RendererBackend* rendererBackend);

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
	 * @param lightScatteringPass light scattering pass
	 * @param camera camera
	 */
	void render(Engine* engine, bool lightScatteringPass, Camera* camera = nullptr);

};
