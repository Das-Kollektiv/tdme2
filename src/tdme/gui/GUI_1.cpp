#include <tdme/gui/GUI_1.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIMouseEvent.h>

using tdme::gui::GUI_1;
using tdme::gui::GUI;
using tdme::gui::events::GUIMouseEvent;

GUI_1::GUI_1(GUI *GUI_this)
	: super()
	, GUI_this(GUI_this)
{
}

GUIMouseEvent* GUI_1::instantiate()
{
	return new GUIMouseEvent();
}

