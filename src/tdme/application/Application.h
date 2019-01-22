#pragma once

#if defined(__linux__) || defined(_WIN32)
	#include <GL/freeglut.h>
#elif defined(__APPLE__)
	#include <GLUT/glut.h>
#endif

#define MOUSE_CURSOR_DISABLED GLUT_CURSOR_NONE
#define MOUSE_CURSOR_ENABLED GLUT_CURSOR_INHERIT

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/fwd-tdme.h>
#include <tdme/application/InputEventHandler.h>

using std::string;

using tdme::application::InputEventHandler;

/** 
 * Application
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::application::Application
{
public:
	static constexpr int32_t FPS { 60 };

	/**
	 * Public constructor
	 */
	Application();

	/**
	 * Destructor
	 */
	virtual ~Application();

	/**
	 * Set input event handler
	 * @param inputEventHandler input event handler
	 */
	void setInputEventHandler(InputEventHandler* inputEventHandler);

	/**
	 * @return window X position
	 */
	int32_t getWindowXPosition() const;

	/**
	 * Set window X position when initializing
	 * @param windowXPosition window X position
	 */
	void setWindowXPosition(int32_t windowXPosition);

	/**
	 * @return window Y position
	 */
	int32_t getWindowYPosition() const;

	/**
	 * Set window Y position when initializing
	 * @param windowYPosition window Y position
	 */
	void setWindowYPosition(int32_t windowYPosition);

	/**
	 * @return window width
	 */
	int32_t getWindowWidth() const;

	/**
	 * Set window width when initializing
	 * @param windowWidth window width
	 */
	void setWindowWidth(int32_t windowWidth);

	/**
	 * @return window height
	 */
	int32_t getWindowHeight() const;

	/**
	 * Set window height when initializing
	 * @param windowHeight window height
	 */
	void setWindowHeight(int32_t windowHeight);

	/**
	 * @return is full screen
	 */
	bool isFullScreen() const;

	/**
	 * Set full screen mode when initializing
	 * @param fullScreen full screen
	 */
	void setFullScreen(bool fullScreen);

	/**
	 * Windows only: Install exception handler that will print a stack trace if crashing
	 */
	static void installExceptionHandler();

	/**
	 * Set mouse cursor
	 * @param mouseCursor mouse cursor, see MOUSE_CURSOR_*
	 */
	static void setMouseCursor(int mouseCursor);

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
	 * Run this application
	 * @param argc argument count
	 * @param argv argument values
	 * @param title title
	 * @param inputEventHandler application input event handler
	 */
	void run(int argc, char** argv, const string& title, InputEventHandler* inputEventHandler = nullptr);

	/** 
	 * Init
	 */
	virtual void initialize() = 0;

	/** 
	 * Resize
	 * @param width width
	 * @param height height
	 */
	virtual void reshape(int32_t width, int32_t height) = 0;

	/** 
	 * Display
	 */
	virtual void display() = 0;

	/**
	 * Disposes
	 */
	virtual void dispose() = 0;

private:
	static Application* application;
	static InputEventHandler* inputEventHandler;
	bool initialized { false };
	int32_t windowWidth { 1024 };
	int32_t windowHeight { 768 };
	int32_t windowXPosition { 100 };
	int32_t windowYPosition { 100 };
	bool fullScreen { false };
	static int64_t timeLast;

	/**
	 * GLUT display function
	 */
	static void glutDisplay();

	/**
	 * GLUT reshape function
	 * @param width width
	 * @param height height
	 */
	static void glutReshape(int32_t width, int32_t height);

	/**
	 * GLUT on key down
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	static void glutOnKeyDown (unsigned char key, int x, int y);

	/**
	 * GLUT on key up
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	static void glutOnKeyUp(unsigned char key, int x, int y);

	/**
	 * GLUT on special key down
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	static void glutOnSpecialKeyDown (int key, int x, int y);

	/**
	 * GLUT on special key up
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	static void glutOnSpecialKeyUp(int key, int x, int y);

	/**
	 * GLUT on mouse dragged
	 * @param x x
	 * @param y y
	 */
	static void glutOnMouseDragged(int x, int y) ;

	/**
	 * GLUT on mouse moved
	 * @param x x
	 * @param y y
	 */
	static void glutOnMouseMoved(int x, int y);

	/**
	 * On mouse button
	 * @param button button
	 * @param state state
	 * @param x x
	 * @param y y
	 */
	static void glutOnMouseButton(int button, int state, int x, int y);

	/**
	 * On mouse wheel
	 * @param button button
	 * @param direction direction
	 * @param x x
	 * @param y y
	 */
	static void glutOnMouseWheel(int button, int direction, int x, int y);

};
