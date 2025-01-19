#pragma once

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>

/**
 * GUI input event handler interface
 * @author Andreas Drewke
 */
struct agui::gui::events::GUIInputEventHandler
{
	/**
	 * Destructor
	 */
	virtual ~GUIInputEventHandler() {}

	/**
	 * Handle input events that have not yet been processed
	 */
	virtual void handleInputEvents() = 0;

};
