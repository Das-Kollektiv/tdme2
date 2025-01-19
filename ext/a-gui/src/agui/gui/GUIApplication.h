#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/fwd-agui.h>

using std::string;

/**
 * GUI application link
 * @author Andreas Drewke
 */
class agui::gui::GUIApplication
{
public:
	/**
	 * Destructor
	 */
	virtual ~GUIApplication() {}

	/**
	 * @return mouse cursor
	 */
	virtual int getMouseCursor() = 0;

	/**
	 * Set mouse cursor
	 * @param mouseCursor mouse cursor, see MOUSE_CURSOR_*
	 */
	virtual void setMouseCursor(int mouseCursor) = 0;

	/**
	 * @return get mouse X position
	 */
	virtual int getMousePositionX() = 0;

	/**
	 * @return get mouse Y position
	 */
	virtual int getMousePositionY() = 0;

	/**
	 * Set mouse position
	 * @param x x
	 * @param y y
	 */
	virtual void setMousePosition(int x, int y) = 0;

	/**
	 * @return clipboard content as utf8 string
	 */
	virtual string getClipboardContent() = 0;

	/**
	 * Set clipboard content
	 * @param content content
	 */
	virtual void setClipboardContent(const string& content) = 0;

	/**
	 * Open browser with given url
	 * @param url url
	 */
	virtual void openBrowser(const string& url) = 0;

};
