#pragma once

#if defined(_MSC_VER)
	// this suppresses a warning redefinition of APIENTRY macro
	#define NOMINMAX
	#include <windows.h>
#endif
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define MOUSE_CURSOR_DISABLED 0
#define MOUSE_CURSOR_ENABLED 1
#define MOUSE_CURSOR_NORMAL 1
#define MOUSE_CURSOR_HAND 2

#include <array>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/fwd-tdme.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::array;
using std::string;
using std::vector;

using tdme::application::InputEventHandler;
using tdme::engine::subsystems::renderer::Renderer;

/**
 * Application base class, please make sure to allocate application on heap to have correct application shutdown working
 * @author Andreas Drewke
 */
class tdme::application::Application
{
	friend class InputEventHandler;
	friend class tdme::engine::subsystems::renderer::VKRenderer;

public:
	// forbid class copy
	FORBID_CLASS_COPY(Application)

	static constexpr int WINDOW_HINT_NONE { 0 };
	static constexpr int WINDOW_HINT_NOTRESIZEABLE { 1 };
	static constexpr int WINDOW_HINT_NOTDECORATED { 2 };
	static constexpr int WINDOW_HINT_INVISIBLE { 4 };
	static constexpr int WINDOW_HINT_MAXIMIZED { 8 };

	static constexpr int FPS { 60 };

	static constexpr int EXITCODE_SUCCESS { 0 };
	static constexpr int EXITCODE_FAILURE { 1 };

	/**
	 * @return renderer
	 */
	inline static Renderer* getRenderer() {
		return renderer;
	}

	/**
	 * @return if having a GL/Vulkan window and context
	 */
	inline static bool hasApplication() {
		return application != nullptr;
	}

	/**
	 * @return application
	 */
	inline static Application* getApplication() {
		return application;
	}

	/**
	 * @return if FPS should be limited to 60 frames per seconds
	 */
	inline static bool isLimitFPS() {
		return limitFPS;
	}

	/**
	 * Set frames per seconds limit
	 * @param limitFPS set up if FPS should be limited to 60 frames per seconds
	 */
	inline static void setLimitFPS(bool limitFPS) {
		Application::limitFPS = limitFPS;
	}

	/**
	 * Set vsync enabled
	 * @param vSync vertical sync
	 */
	static void setVSyncEnabled(bool vSync);

	/**
	 * @return Operating system the application is running on
	 */
	static string getOSName();

	/**
	 * @return CPU the application is running on
	 */
	static string getCPUName();

	/**
	 * Set locale
	 * @param locale locale
	 */
	static void setLocale(const string& locale);

	/**
	 * Public constructor
	 */
	Application();

	/**
	 * Destructor
	 */
	virtual ~Application();

	/**
	 * @return title
	 */
	inline const string& getTitle() {
		return title;
	}

	/**
	 * @return executable file name
	 */
	inline const string& getExecutableFileName() {
		return executableFileName;
	}

	/**
	 * @return debugging enabled
	 */
	inline bool isDebuggingEnabled() {
		return debuggingEnabled;
	}

	/**
	 * Set input event handler
	 * @param inputEventHandler input event handler
	 */
	void setInputEventHandler(InputEventHandler* inputEventHandler);

	/**
	 * Execute a command and wait until it finished running
	 * @param command command to execute
	 * @throws std::runtime_error
	 * @return application output
	 */
	static string execute(const string& command);

	/**
	 * Execute a command in background
	 * @param command command to execute
	 */
	static void executeBackground(const string& command);

	/**
	 * Open browser with given url
	 * @param url url
	 */
	static void openBrowser(const string& url);

	/**
	 * Cancels a users requested exit (ALT-F4 or X button)
	 */
	static void cancelExit();

	/**
	 * Exits this application with given exit code
	 * @param exitCode exit code
	 */
	static void exit(int exitCode);

	/**
	 * @return If window is active on Win32, on other platforms it currently always return true
	 */
	static bool isActive();

	/**
	 * @return window X position
	 */
	int getWindowXPosition();

	/**
	 * Set window X position when initializing
	 * @param windowXPosition window X position
	 */
	void setWindowXPosition(int windowXPosition);

	/**
	 * @return window Y position
	 */
	int getWindowYPosition();

	/**
	 * Set window Y position when initializing
	 * @param windowYPosition window Y position
	 */
	void setWindowYPosition(int windowYPosition);

	/**
	 * @return window width
	 */
	int getWindowWidth() const;

	/**
	 * Set window width
	 * @param windowWidth window width
	 */
	void setWindowWidth(int windowWidth);

	/**
	 * @return window height
	 */
	int getWindowHeight() const;

	/**
	 * Set window height
	 * @param windowHeight window height
	 */
	void setWindowHeight(int windowHeight);

	/**
	 * @return is full screen
	 */
	bool isFullScreen() const;

	/**
	 * Set full screen mode
	 * @param fullScreen full screen
	 */
	void setFullScreen(bool fullScreen);

	/**
	 * Windows only: Install exception handler that will print a stack trace if crashing
	 */
	static void installExceptionHandler();

	/**
	 * @return mouse cursor
	 */
	inline static int getMouseCursor() {
		return mouseCursor;
	}

	/**
	 * Set mouse cursor
	 * @param mouseCursor mouse cursor, see MOUSE_CURSOR_*
	 */
	static void setMouseCursor(int mouseCursor);

	/**
	 * @return get mouse X position
	 */
	static int getMousePositionX();

	/**
	 * @return get mouse Y position
	 */
	static int getMousePositionY();

	/**
	 * Set mouse position
	 * @param x x
	 * @param y y
	 */
	static void setMousePosition(int x, int y);

	/**
	 * Swap rendering buffers
	 */
	static void swapBuffers();

	/**
	 * @return clipboard content as utf8 string
	 */
	string getClipboardContent();

	/**
	 * Set clipboard content
	 * @param content content
	 */
	void setClipboardContent(const string& content);

	/**
	 * Run this application
	 * @param argc argument count
	 * @param argv argument values
	 * @param title title
	 * @param inputEventHandler application input event handler
	 * @param windowHints window hints
	 * @return exit code
	 */
	int run(int argc, char** argv, const string& title, InputEventHandler* inputEventHandler = nullptr, int windowHints = WINDOW_HINT_NONE);

	/**
	 * Init
	 */
	virtual void initialize() = 0;

	/**
	 * Resize
	 * @param width width
	 * @param height height
	 */
	virtual void reshape(int width, int height) = 0;

	/**
	 * Display
	 */
	virtual void display() = 0;

	/**
	 * Disposes
	 */
	virtual void dispose() = 0;

	/**
	 * On close
	 */
	virtual void onClose();

	/**
	 * On drop
	 * @param paths paths of items that were dropped
	 */
	virtual void onDrop(const vector<string>& paths);

private:
	STATIC_DLL_IMPEXT static Renderer* renderer;
	STATIC_DLL_IMPEXT static Application* application;
	STATIC_DLL_IMPEXT static InputEventHandler* inputEventHandler;
	int windowHints { WINDOW_HINT_NONE };
	string executableFileName;
	bool debuggingEnabled { false };
	bool initialized { false };
	int windowWidth { 1024 };
	int windowHeight { 768 };
	int windowXPosition { -1 };
	int windowYPosition { -1 };
	bool fullScreen { false };
	STATIC_DLL_IMPEXT static int64_t timeLast;
	STATIC_DLL_IMPEXT static bool limitFPS;
	string title;
	int exitCode { EXITCODE_SUCCESS };

	STATIC_DLL_IMPEXT static GLFWwindow* glfwWindow;
	STATIC_DLL_IMPEXT static array<unsigned int, 10> glfwMouseButtonDownFrames;
	STATIC_DLL_IMPEXT static int glfwMouseButtonLast;
	STATIC_DLL_IMPEXT static bool glfwCapsLockEnabled;
	STATIC_DLL_IMPEXT static GLFWcursor* glfwHandCursor;

	STATIC_DLL_IMPEXT static int mouseCursor;

	/**
	 * Set application icon
	 */
	void setIcon();

	/**
	 * Display function
	 */
	static void displayInternal();

	/**
	 * Reshape function
	 * @param width width
	 * @param height height
	 */
	static void reshapeInternal(int width, int height);

	/**
	 * GLFW on char
	 * @param window window
	 * @param key key
	 */
	static void glfwOnChar(GLFWwindow* window, unsigned int key);

	/**
	 * GLFW on key
	 * @param window window
	 * @param key key
	 * @param scanCode scan code
	 * @param action action
	 * @param mods modifier keys
	 */
	static void glfwOnKey(GLFWwindow* window, int key, int scanCode, int action, int mods);

	/**
	 * GLFW on mouse moved
	 * @param window window
	 * @param x x
	 * @param y y
	 */
	static void glfwOnMouseMoved(GLFWwindow* window, double x, double y);

	/**
	 * GLFW on key
	 * @param window window
	 * @param button button
	 * @param action action
	 * @param mods modifier keys
	 */
	static void glfwOnMouseButton(GLFWwindow* window, int button, int action, int mods);

	/**
	 * GLFW on key
	 * @param window window
	 * @param x x
	 * @param y y
	 */
	static void glfwOnMouseWheel(GLFWwindow* window, double x, double y);

	/**
	 * GLFW on window resize
	 * @param window window
	 * @param width width
	 * @param height height
	 */
	static void glfwOnWindowResize(GLFWwindow* window, int width, int height);

	/**
	 * GLFW on close
	 */
	static void glfwOnClose(GLFWwindow* window);

	/**
	 * GLFW on drop
	 * @param window window
	 * @param count count
	 * @param paths paths
	 */
	static void glfwOnDrop(GLFWwindow* window, int count, const char** paths);

};
