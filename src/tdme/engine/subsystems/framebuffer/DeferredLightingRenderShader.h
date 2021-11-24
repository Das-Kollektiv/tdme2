#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>

using std::array;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Camera;
using tdme::engine::Engine;

/**
 * Deferred lighint render shader
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::framebuffer::DeferredLightingRenderShader final
{

private:
	Renderer* renderer { nullptr };
	int32_t vertexShaderId { -1 };
	int32_t fragmentShaderId { -1 };
	int32_t programId { -1 };
	int32_t uniformGeometryBufferTextureId1 { -1 };
	int32_t uniformGeometryBufferTextureId2 { -1 };
	int32_t uniformGeometryBufferTextureId3 { -1 };
	int32_t uniformColorBufferTextureUnit1 { -1 };
	int32_t uniformColorBufferTextureUnit2 { -1 };
	int32_t uniformColorBufferTextureUnit3 { -1 };
	int32_t uniformColorBufferTextureUnit4 { -1 };
	int32_t uniformColorBufferTextureUnit5 { -1 };
	int32_t uniformDepthBufferTextureUnit { -1 };

	array<int32_t, Engine::LIGHTS_MAX> uniformSpecularLightEnabled;
	array<int32_t, Engine::LIGHTS_MAX> uniformSpecularLightAmbient;
	array<int32_t, Engine::LIGHTS_MAX> uniformSpecularLightDiffuse;
	array<int32_t, Engine::LIGHTS_MAX> uniformSpecularLightSpecular;
	array<int32_t, Engine::LIGHTS_MAX> uniformSpecularLightPosition;
	array<int32_t, Engine::LIGHTS_MAX> uniformSpecularLightSpotDirection;
	array<int32_t, Engine::LIGHTS_MAX> uniformSpecularLightSpotExponent;
	array<int32_t, Engine::LIGHTS_MAX> uniformSpecularLightSpotCosCutoff;
	array<int32_t, Engine::LIGHTS_MAX> uniformSpecularLightConstantAttenuation;
	array<int32_t, Engine::LIGHTS_MAX> uniformSpecularLightLinearAttenuation;
	array<int32_t, Engine::LIGHTS_MAX> uniformSpecularLightQuadraticAttenuation;
	array<int32_t, Engine::LIGHTS_MAX> uniformSpecularLightRadius;
	int32_t uniformCameraMatrix { -1 };

	bool initialized;
	bool isRunning;

public:
	/**
	 * Public constructor
	 * @param renderer renderer
	 */
	DeferredLightingRenderShader(Renderer* renderer);

	/**
	 * Public destructor
	 */
	~DeferredLightingRenderShader();

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
	 * @param engine engine
	 */
	void useProgram(Engine* engine);

	/**
	 * Un use render program
	 */
	void unUseProgram();

};
