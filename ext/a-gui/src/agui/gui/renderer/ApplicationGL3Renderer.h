#pragma once

#if defined(_MSC_VER)
	// this suppresses a warning redefinition of APIENTRY macro
	#define NOMINMAX
	#include <windows.h>
#endif
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/renderer/fwd-agui.h>
#include <agui/gui/renderer/GL3Renderer.h>

using std::string;

/**
 * Application GL3 renderer
 * @author Andreas Drewke
 */
class agui::gui::renderer::ApplicationGL3Renderer: public GL3Renderer
{
public:
	// forbid class copy
	FORBID_CLASS_COPY(ApplicationGL3Renderer)

	/**
	 * Public constructor
	 */
	ApplicationGL3Renderer();

	// overridden methods
	bool prepareWindowSystemRendererContext(int tryIdx) override;
	bool initializeWindowSystemRendererContext(GLFWwindow* glfwWindow) override;
	void onBindTexture(int contextIdx, int32_t textureId) override;
	void onUpdateTextureMatrix(int contextIdx) override;
	void onUpdateEffect(int contextIdx) override;
};
