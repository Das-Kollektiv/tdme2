#include <agui/gui/renderer/ApplicationGL3Renderer.h>

#if defined(_MSC_VER)
	// this suppresses a warning redefinition of APIENTRY macro
	#define NOMINMAX
	#include <windows.h>
#endif
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#if !defined(__APPLE__)
	#define GLEW_NO_GLU
	#include <GL/glew.h>
	#if defined(_WIN32)
		#include <GL/wglew.h>
	#endif
#endif

#include <array>
#include <string>

#include <agui/agui.h>
#include <agui/gui/renderer/GUIShader.h>
#include <agui/gui/GUI.h>

using agui::gui::renderer::ApplicationGL3Renderer;

using std::array;
using std::string;

using agui::gui::renderer::GUIShader;
using agui::gui::GUI;

ApplicationGL3Renderer::ApplicationGL3Renderer()
{
}

bool ApplicationGL3Renderer::prepareWindowSystemRendererContext(int tryIdx) {
	array<array<int, 3>, 2> glVersions = {{ {{1, 4, 3}}, {{1, 3, 2}} }};
	if (tryIdx >= glVersions.size()) return false;
	#if defined(__APPLE__)
		glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
	#endif
	const auto& glVersion = glVersions[tryIdx];
	#if !defined(__HAIKU__)
		// does not work for now with Haiku OS
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, glVersion[0] == 1?GLFW_TRUE:GLFW_FALSE);
	#endif
	glfwWindowHint(GLFW_OPENGL_PROFILE, glVersion[0] == 1?GLFW_OPENGL_CORE_PROFILE:GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glVersion[1]);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glVersion[2]);
	return true;
}

bool ApplicationGL3Renderer::initializeWindowSystemRendererContext(GLFWwindow* glfwWindow) {
	glfwMakeContextCurrent(glfwWindow);
	if (glfwGetCurrentContext() == nullptr) {
		Console::printLine("EngineGL3Renderer::initializeWindowSystemRendererContext(): glfwMakeContextCurrent(): Error: No window attached to context");
		return false;
	}
	#if !defined(__APPLE__)
		//glewExperimental = true;
		GLenum glewInitStatus = glewInit();
		if (glewInitStatus != GLEW_OK) {
			Console::printLine("EngineGL3Renderer::initializeWindowSystemRendererContext(): glewInit(): Error: " + (string((char*)glewGetErrorString(glewInitStatus))));
			return false;
		}
	#endif
	return true;
}

void ApplicationGL3Renderer::onBindTexture(int contextIdx, int32_t textureId)
{
	GUI::getShader()->bindTexture(textureId);
}

void ApplicationGL3Renderer::onUpdateTextureMatrix(int contextIdx)
{
	GUI::getShader()->updateTextureMatrix();
}

void ApplicationGL3Renderer::onUpdateEffect(int contextIdx)
{
	GUI::getShader()->updateEffect();
}
