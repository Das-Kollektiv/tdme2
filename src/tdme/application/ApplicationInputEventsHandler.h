#pragma once

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__linux__) || defined(_WIN32)
	#include <GL/freeglut.h>
#elif defined(__APPLE__)
	#include <GLUT/glut.h>
#elif defined(__HAIKU__)
	#include <GL/glut.h>
#endif

#include <tdme/tdme.h>
#include <tdme/application/fwd-tdme.h>

#define KEYBOARD_MODIFIER_SHIFT	GLUT_ACTIVE_SHIFT
#define KEYBOARD_MODIFIER_CTRL GLUT_ACTIVE_CTRL
#define KEYBOARD_MODIFIER_ALT GLUT_ACTIVE_ALT

#define MOUSE_BUTTON_DOWN GLUT_DOWN
#define MOUSE_BUTTON_UP GLUT_UP

#define KEYBOARD_KEYCODE_LEFT GLUT_KEY_LEFT
#define KEYBOARD_KEYCODE_UP GLUT_KEY_UP
#define KEYBOARD_KEYCODE_RIGHT GLUT_KEY_RIGHT
#define KEYBOARD_KEYCODE_DOWN GLUT_KEY_DOWN

/** 
 * Application input events handler
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::application::ApplicationInputEventsHandler
{
public:
	/**
	 * Get keyboard modifiers
	 * @return modifiers (one of KEYBOARD_MODIFIER_*)
	 */
	static int getKeyboardModifiers();

	/**
	 * On key down
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	virtual void onKeyDown (unsigned char key, int x, int y) = 0;

	/**
	 * On key up
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	virtual void onKeyUp(unsigned char key, int x, int y) = 0;

	/**
	 * On special key up
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	virtual void onSpecialKeyDown (int key, int x, int y) = 0;

	/**
	 * On special key up
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	virtual void onSpecialKeyUp(int key, int x, int y) = 0;

	/**
	 * On mouse dragged
	 * @param x x
	 * @param y y
	 */
	virtual void onMouseDragged(int x, int y) = 0;

	/**
	 * On mouse moved
	 * @param x x
	 * @param y y
	 */
	virtual void onMouseMoved(int x, int y) = 0;

	/**
	 * On mouse moved
	 * @param button button
	 * @param state state
	 * @param x x
	 * @param y y
	 */
	virtual void onMouseButton(int button, int state, int x, int y) = 0;

	/**
	 * On mouse wheen
	 * @param button button
	 * @param direction direction
	 * @param x x
	 * @param y y
	 */
	virtual void onMouseWheel(int button, int direction, int x, int y) = 0;

};
