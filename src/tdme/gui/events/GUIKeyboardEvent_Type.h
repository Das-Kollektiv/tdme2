// Generated from /tdme/src/tdme/gui/events/GUIKeyboardEvent.java

#pragma once

#include <string>

#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::utils::Enum;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIKeyboardEvent_Type;

class tdme::gui::events::GUIKeyboardEvent_Type final
	: public Enum
{
	friend class GUIKeyboardEvent;

public:
	static GUIKeyboardEvent_Type *NONE;
	static GUIKeyboardEvent_Type *KEY_PRESSED;
	static GUIKeyboardEvent_Type *KEY_RELEASED;
	GUIKeyboardEvent_Type(const wstring& name, int ordinal);
	static GUIKeyboardEvent_Type* valueOf(const wstring& a0);
};
