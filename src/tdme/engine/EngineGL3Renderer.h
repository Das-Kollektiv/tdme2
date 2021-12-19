#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/GL3Renderer.h>

using tdme::engine::subsystems::renderer::GL3Renderer;
using tdme::engine::Engine;

/**
 * Engine connector of GL3 renderer to other engine functionality
 * @author Andreas Drewke
 */

class tdme::engine::EngineGL3Renderer: public GL3Renderer
{
public:
	/**
	 * Public constructor
	 * @param engine engine
	 */
	EngineGL3Renderer(Engine* engine);

	// overridden methods
	void onUpdateProjectionMatrix(int contextIdx) override;
	void onUpdateCameraMatrix(int contextIdx) override;
	void onUpdateModelViewMatrix(int contextIdx) override;
	void onBindTexture(int contextIdx, int32_t textureId) override;
	void onUpdateTextureMatrix(int contextIdx) override;
	void onUpdateEffect(int contextIdx) override;
	void onUpdateLight(int contextIdx, int32_t lightId) override;
	void onUpdateMaterial(int contextIdx) override;
	void onUpdateShader(int contextIdx) override;
	void onUpdateShaderParameters(int contextIdx) override;

private:
	Engine* engine { nullptr };
};
