#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/VKRenderer.h>

using tdme::engine::subsystems::renderer::VKRenderer;
using tdme::engine::Engine;

/**
 * Engine connector of GL3 renderer to other engine functionality
 * @author Andreas Drewke
 */

class tdme::engine::EngineVKRenderer: public VKRenderer
{
public:
	// overriden methods
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
	 * @param engine engine
	 */
	EngineVKRenderer(Engine* engine);
private:
	Engine *engine;
};
