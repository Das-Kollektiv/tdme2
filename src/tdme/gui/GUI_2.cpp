#include <tdme/gui/GUI_2.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>

using tdme::gui::GUI_2;
using tdme::gui::GUI;
using tdme::gui::events::GUIKeyboardEvent;

GUI_2::GUI_2(GUI *GUI_this)
	: super()
	, GUI_this(GUI_this)
{
}

GUIKeyboardEvent* GUI_2::instantiate()
{
	return new GUIKeyboardEvent();
}

