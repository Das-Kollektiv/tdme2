#pragma once

#include <string>

#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::string;

using tdme::utils::Enum;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::events::GUIMouseEvent_Type;

class tdme::gui::events::GUIMouseEvent_Type final
	: public Enum
{
	friend class GUIMouseEvent;

public:
	static GUIMouseEvent_Type* MOUSEEVENT_NONE;
	static GUIMouseEvent_Type* MOUSEEVENT_WHEEL_MOVED;
	static GUIMouseEvent_Type* MOUSEEVENT_PRESSED;
	static GUIMouseEvent_Type* MOUSEEVENT_RELEASED;
	static GUIMouseEvent_Type* MOUSEEVENT_MOVED;
	static GUIMouseEvent_Type* MOUSEEVENT_DRAGGED;
	GUIMouseEvent_Type(const string& name, int ordinal);
	static GUIMouseEvent_Type* valueOf(const string& a0);

};
