#pragma once

#include <tdme/tdme.h>
#include <tdme/application/fwd-tdme.h>
#include <tdme/application/InputDefinitions.h>

/**
 * Application input event handler interface
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::application::InputEventHandler
{
public:
	/**
	 * Destructor
	 */
	virtual ~InputEventHandler();

	/**
	 * On char
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	virtual void onChar(unsigned int key, int x, int y) = 0;

	/**
	 * On key down
	 * @param key key
	 * @param keyCode key code
	 * @param x x
	 * @param y y
	 */
	virtual void onKeyDown (unsigned char key, int keyCode, int x, int y) = 0;

	/**
	 * On key up
	 * @param key key
	 * @param keyCode key code
	 * @param x x
	 * @param y y
	 */
	virtual void onKeyUp(unsigned char key, int keyCode, int x, int y) = 0;

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
