// Generated from /tdme/src/tdme/gui/events/GUIMouseEvent.java

#pragma once

#include <string>

#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::utils::Enum;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::events::GUIMouseEvent_Type;

class tdme::gui::events::GUIMouseEvent_Type final
	: public Enum
{
	friend class GUIMouseEvent;

public:
	static GUIMouseEvent_Type *NONE;
	static GUIMouseEvent_Type *MOUSE_WHEEL_MOVED;
	static GUIMouseEvent_Type *MOUSE_PRESSED;
	static GUIMouseEvent_Type *MOUSE_RELEASED;
	static GUIMouseEvent_Type *MOUSE_MOVED;
	static GUIMouseEvent_Type *MOUSE_DRAGGED;
	GUIMouseEvent_Type(const wstring& name, int ordinal);
	static GUIMouseEvent_Type* valueOf(const wstring& a0);

};
