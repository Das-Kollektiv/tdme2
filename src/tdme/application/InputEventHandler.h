#pragma once

#include <tdme/tdme.h>
#include <tdme/application/fwd-tdme.h>

#include <agui/agui.h>
#include <agui/gui/GUIEventHandler.h>

/**
 * GUI input event handler interface
 * @author Andreas Drewke
 */
class tdme::application::InputEventHandler: public agui::gui::GUIEventHandler
{
public:
	/**
	 * Destructor
	 */
	virtual ~InputEventHandler() {}

};
