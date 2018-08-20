#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/GLES2Renderer.h>

using tdme::engine::subsystems::renderer::GLES2Renderer;
using tdme::engine::Engine;

class tdme::engine::EngineGLES2Renderer
	: public GLES2Renderer
{

public:
	void onUpdateProjectionMatrix() override;
	void onUpdateCameraMatrix() override;
	void onUpdateModelViewMatrix() override;
	void onBindTexture(int32_t textureId) override;
	void onUpdateTextureMatrix() override;
	void onUpdateEffect() override;
	void onUpdateLight(int32_t lightId) override;
	void onUpdateMaterial() override;
	void onUpdateShader() override;

	/**
	 * Public constructor
	 * @param *engine engine
	 */
	EngineGLES2Renderer(Engine *engine);
private:
	Engine* engine;
};
