#pragma once

#if defined(__linux__) or defined(_WIN32)
	#include <GL/freeglut.h>
#elif defined(__APPLE__)
	#include <GLUT/glut.h>
#endif

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/fwd-tdme.h>
#include <tdme/application/ApplicationInputEventsHandler.h>

using std::string;

using tdme::application::ApplicationInputEventsHandler;

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
	 * @param input event handler
	 */
	void setInputEventHandler(ApplicationInputEventsHandler* inputEventHandler);

	/**
	 * Run this application
	 * @param argument count
	 * @param argument values
	 * @param title
	 * @param application input event handler
	 */
	void run(int argc, char** argv, const string& title, ApplicationInputEventsHandler* inputEventHandler = nullptr);

	/** 
	 * Init
	 */
	virtual void initialize() = 0;

	/** 
	 * Resize
	 * @param width
	 * @param height
	 */
	virtual void reshape(int32_t width, int32_t height) = 0;

	/** 
	 * Display
	 */
	virtual void display() = 0;

	/**
	 * Disposes this frame buffer
	 */
	virtual void dispose() = 0;

private:
	static Application* application;
	static ApplicationInputEventsHandler* inputEventHandler;
	bool initialized { false };
	static int64_t timeLast;

	/**
	 * GLUT display function
	 */
	static void glutDisplay();

	/**
	 * GLUT reshape function
	 * @param width
	 * @param height
	 */
	static void glutReshape(int32_t width, int32_t height);

	/**
	 * GLUT on key down
	 * @param key
	 * @param x
	 * @param y
	 */
	static void glutOnKeyDown (unsigned char key, int x, int y);

	/**
	 * GLUT on key up
	 * @param key
	 * @param x
	 * @param y
	 */
	static void glutOnKeyUp(unsigned char key, int x, int y);

	/**
	 * GLUT on special key down
	 * @param key
	 * @param x
	 * @param y
	 */
	static void glutOnSpecialKeyDown (int key, int x, int y);

	/**
	 * GLUT on special key up
	 * @param key
	 * @param x
	 * @param y
	 */
	static void glutOnSpecialKeyUp(int, int x, int y);

	/**
	 * GLUT on mouse dragged
	 * @param x
	 * @param y
	 */
	static void glutOnMouseDragged(int x, int y) ;

	/**
	 * GLUT on mouse moved
	 * @param x
	 * @param y
	 */
	static void glutOnMouseMoved(int x, int y);

	/**
	 * On mouse button
	 * @param button
	 * @param state
	 * @param x
	 * @param y
	 */
	static void glutOnMouseButton(int button, int state, int x, int y);

	/**
	 * On mouse wheel
	 * @param button
	 * @param direction
	 * @param x
	 * @param y
	 */
	static void glutOnMouseWheel(int button, int direction, int x, int y);

};
