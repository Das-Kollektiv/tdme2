#pragma once

#ifdef __linux__
	#include <GL/freeglut.h>
#elif
	#include <GLUT/glut.h>
#endif

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

struct default_init_tag;

using java::lang::Object;

#define KEYBOARD_MODIFIER_SHIFT	GLUT_ACTIVE_SHIFT
#define KEYBOARD_MODIFIER_CTRL GLUT_ACTIVE_CTRL
#define KEYBOARD_MODIFIER_ALT GLUT_ACTIVE_ALT

#define MOUSE_BUTTON_DOWN GLUT_DOWN
#define MOUSE_BUTTON_UP GLUT_UP

/** 
 * Application input events handler
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::ApplicationInputEventsHandler:
	public virtual Object
{
public:
	/**
	 * Get keyboard modifiers
	 * @return modifiers (one of KEYBOARD_MODIFIER_*)
	 */
	static int getKeyboardModifiers();

	/**
	 * On key down
	 * @param key
	 * @param x
	 * @param y
	 */
	virtual void onKeyDown (unsigned char key, int x, int y) = 0;

	/**
	 * On key up
	 * @param key
	 * @param x
	 * @param y
	 */
	virtual void onKeyUp(unsigned char key, int x, int y) = 0;

	/**
	 * On special key up
	 * @param key
	 * @param x
	 * @param y
	 */
	virtual void onSpecialKeyDown (int key, int x, int y) = 0;

	/**
	 * On special key up
	 * @param key
	 * @param x
	 * @param y
	 */
	virtual void onSpecialKeyUp(int key, int x, int y) = 0;

	/**
	 * On mouse dragged
	 * @param x
	 * @param y
	 */
	virtual void onMouseDragged(int x, int y) = 0;

	/**
	 * On mouse moved
	 * @param x
	 * @param y
	 */
	virtual void onMouseMoved(int x, int y) = 0;

	/**
	 * On mouse moved
	 * @param button
	 * @param state
	 * @param x
	 * @param y
	 */
	virtual void onMouseButton(int button, int state, int x, int y) = 0;

};
