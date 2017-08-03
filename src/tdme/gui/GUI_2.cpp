// Generated from /tdme/src/tdme/gui/GUI.java
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
	ctor();
}

GUIKeyboardEvent* GUI_2::instantiate()
{
	return new GUIKeyboardEvent();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUI_2::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* GUI_2::getClass0()
{
	return class_();
}

