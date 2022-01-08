#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/GL2Renderer.h>

using tdme::engine::subsystems::renderer::GL2Renderer;
using tdme::engine::Engine;

/**
 * Engine connector of GL2 renderer to other engine functionality
 * @author Andreas Drewke
 */
class tdme::engine::EngineGL2Renderer: public GL2Renderer
{

public:
	/**
	 * Public constructor
	 */
	EngineGL2Renderer();

	// overridden methods
	bool initializeWindowSystemRendererContext(int tryIdx) override;
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
