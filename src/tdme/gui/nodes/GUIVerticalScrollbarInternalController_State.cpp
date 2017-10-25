#include <tdme/gui/nodes/GUIVerticalScrollbarInternalController_State.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::string;

using tdme::gui::nodes::GUIVerticalScrollbarInternalController_State;
using tdme::utils::Enum;

GUIVerticalScrollbarInternalController_State::GUIVerticalScrollbarInternalController_State(const string& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUIVerticalScrollbarInternalController_State* tdme::gui::nodes::GUIVerticalScrollbarInternalController_State::NONE = new GUIVerticalScrollbarInternalController_State("NONE", 0);
GUIVerticalScrollbarInternalController_State* tdme::gui::nodes::GUIVerticalScrollbarInternalController_State::MOUSEOVER = new GUIVerticalScrollbarInternalController_State("MOUSEOVER", 1);
GUIVerticalScrollbarInternalController_State* tdme::gui::nodes::GUIVerticalScrollbarInternalController_State::DRAGGING = new GUIVerticalScrollbarInternalController_State("DRAGGING", 2);

GUIVerticalScrollbarInternalController_State* GUIVerticalScrollbarInternalController_State::valueOf(const string& a0)
{
	if (DRAGGING->getName() == a0) return DRAGGING;
	if (MOUSEOVER->getName() == a0) return MOUSEOVER;
	if (NONE->getName() == a0) return NONE;
	// TODO: throw exception here maybe
	return nullptr;
}
