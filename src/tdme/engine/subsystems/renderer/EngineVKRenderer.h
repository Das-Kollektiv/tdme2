#pragma once

#if defined(_MSC_VER)
	// this suppresses a warning redefinition of APIENTRY macro
	#define NOMINMAX
	#include <windows.h>
#endif
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackendPlugin.h>
#include <tdme/engine/subsystems/renderer/VKRenderer.h>

using std::string;

using tdme::engine::subsystems::renderer::RendererBackendPlugin;
using tdme::engine::subsystems::renderer::VKRenderer;
using tdme::engine::Engine;

/**
 * Engine connector of VK renderer backend to other engine functionality
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::renderer::EngineVKRenderer: public VKRenderer, public RendererBackendPlugin
{
public:
	// forbid class copy
	FORBID_CLASS_COPY(EngineVKRenderer)

	/**
	 * Public constructor
	 */
	EngineVKRenderer();

	// overridden methods
	bool prepareWindowSystemRendererContext(int tryIdx) override;
	bool initializeWindowSystemRendererContext(GLFWwindow* glfwWindow) override;
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

};
