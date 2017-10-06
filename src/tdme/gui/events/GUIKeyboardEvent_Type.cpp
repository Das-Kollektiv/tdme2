// Generated from /tdme/src/tdme/gui/events/GUIKeyboardEvent.java
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>

#include <tdme/utils/Enum.h>

using tdme::gui::events::GUIKeyboardEvent_Type;
using tdme::utils::Enum;

GUIKeyboardEvent_Type::GUIKeyboardEvent_Type(const wstring& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUIKeyboardEvent_Type* tdme::gui::events::GUIKeyboardEvent_Type::NONE = new GUIKeyboardEvent_Type(L"NONE", 0);
GUIKeyboardEvent_Type* tdme::gui::events::GUIKeyboardEvent_Type::KEY_PRESSED = new GUIKeyboardEvent_Type(L"KEY_PRESSED", 1);
GUIKeyboardEvent_Type* tdme::gui::events::GUIKeyboardEvent_Type::KEY_RELEASED = new GUIKeyboardEvent_Type(L"KEY_RELEASED", 2);

GUIKeyboardEvent_Type* GUIKeyboardEvent_Type::valueOf(const wstring& a0)
{
	if (KEY_PRESSED->getName() == a0) return KEY_PRESSED;
	if (KEY_RELEASED->getName() == a0) return KEY_RELEASED;
	if (NONE->getName() == a0) return NONE;
	// TODO: throw exception here maybe
	return nullptr;
}
