// Generated from /tdme/src/tdme/gui/GUI.java
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
	ctor();
}

GUIMouseEvent* GUI_1::instantiate()
{
	return new GUIMouseEvent();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUI_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* GUI_1::getClass0()
{
	return class_();
}

