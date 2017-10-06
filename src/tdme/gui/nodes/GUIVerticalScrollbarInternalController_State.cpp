// Generated from /tdme/src/tdme/gui/nodes/GUIVerticalScrollbarInternalController.java
#include <tdme/gui/nodes/GUIVerticalScrollbarInternalController_State.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::gui::nodes::GUIVerticalScrollbarInternalController_State;
using tdme::utils::Enum;

GUIVerticalScrollbarInternalController_State::GUIVerticalScrollbarInternalController_State(const wstring& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUIVerticalScrollbarInternalController_State* tdme::gui::nodes::GUIVerticalScrollbarInternalController_State::NONE = new GUIVerticalScrollbarInternalController_State(L"NONE", 0);
GUIVerticalScrollbarInternalController_State* tdme::gui::nodes::GUIVerticalScrollbarInternalController_State::MOUSEOVER = new GUIVerticalScrollbarInternalController_State(L"MOUSEOVER", 1);
GUIVerticalScrollbarInternalController_State* tdme::gui::nodes::GUIVerticalScrollbarInternalController_State::DRAGGING = new GUIVerticalScrollbarInternalController_State(L"DRAGGING", 2);

GUIVerticalScrollbarInternalController_State* GUIVerticalScrollbarInternalController_State::valueOf(const wstring& a0)
{
	if (DRAGGING->getName() == a0) return DRAGGING;
	if (MOUSEOVER->getName() == a0) return MOUSEOVER;
	if (NONE->getName() == a0) return NONE;
	// TODO: throw exception here maybe
	return nullptr;
}
