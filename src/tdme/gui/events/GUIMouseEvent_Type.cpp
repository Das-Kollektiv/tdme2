// Generated from /tdme/src/tdme/gui/events/GUIMouseEvent.java
#include <tdme/gui/events/GUIMouseEvent_Type.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::gui::events::GUIMouseEvent_Type;
using tdme::utils::Enum;

GUIMouseEvent_Type::GUIMouseEvent_Type(const wstring& name, int ordinal) : Enum(name, ordinal)
{
}

GUIMouseEvent_Type* tdme::gui::events::GUIMouseEvent_Type::NONE = new GUIMouseEvent_Type(L"NONE", 0);
GUIMouseEvent_Type* tdme::gui::events::GUIMouseEvent_Type::MOUSE_WHEEL_MOVED = new GUIMouseEvent_Type(L"MOUSE_WHEEL_MOVED", 1);
GUIMouseEvent_Type* tdme::gui::events::GUIMouseEvent_Type::MOUSE_PRESSED = new GUIMouseEvent_Type(L"MOUSE_PRESSED", 2);
GUIMouseEvent_Type* tdme::gui::events::GUIMouseEvent_Type::MOUSE_RELEASED = new GUIMouseEvent_Type(L"MOUSE_RELEASED", 3);
GUIMouseEvent_Type* tdme::gui::events::GUIMouseEvent_Type::MOUSE_MOVED = new GUIMouseEvent_Type(L"MOUSE_MOVED", 4);
GUIMouseEvent_Type* tdme::gui::events::GUIMouseEvent_Type::MOUSE_DRAGGED = new GUIMouseEvent_Type(L"MOUSE_DRAGGED", 5);

GUIMouseEvent_Type* GUIMouseEvent_Type::valueOf(const wstring& a0)
{
	if (MOUSE_DRAGGED->getName() == a0) return MOUSE_DRAGGED;
	if (MOUSE_MOVED->getName() == a0) return MOUSE_MOVED;
	if (MOUSE_PRESSED->getName() == a0) return MOUSE_PRESSED;
	if (MOUSE_RELEASED->getName() == a0) return MOUSE_RELEASED;
	if (MOUSE_WHEEL_MOVED->getName() == a0) return MOUSE_WHEEL_MOVED;
	if (NONE->getName() == a0) return NONE;
	// TODO: throw exception here maybe
	return nullptr;
}
