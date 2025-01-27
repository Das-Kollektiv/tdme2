#pragma once

#include <agui/agui.h>
#include <agui/gui/fwd-agui.h>
#include <agui/gui/GUIInputDefinitions.h>

/**
 * Application event handler interface
 * @author Andreas Drewke
 */
class agui::gui::GUIEventHandler
{
public:
	/**
	 * Destructor
	 */
	virtual ~GUIEventHandler() {}

	/**
	 * On char
	 * @param key key
	 * @param x x
	 * @param y y
	 */
	virtual void onChar(int key, int x, int y) = 0;

	/**
	 * On key down
	 * @param key key
	 * @param keyCode key code
	 * @param x x
	 * @param y y
	 * @param repeat event
	 * @param modifiers modifiers
	 */
	virtual void onKeyDown(int key, int keyCode, int x, int y, bool repeat, int modifiers) = 0;

	/**
	 * On key up
	 * @param key key
	 * @param keyCode key code
	 * @param x x
	 * @param y y
	 */
	virtual void onKeyUp(int key, int keyCode, int x, int y) = 0;

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
