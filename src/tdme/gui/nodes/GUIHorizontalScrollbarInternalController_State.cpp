#include <tdme/gui/nodes/GUIHorizontalScrollbarInternalController_State.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::string;

using tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State;
using tdme::utils::Enum;

GUIHorizontalScrollbarInternalController_State::GUIHorizontalScrollbarInternalController_State(const string& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUIHorizontalScrollbarInternalController_State* tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State::NONE = new GUIHorizontalScrollbarInternalController_State("NONE", 0);
GUIHorizontalScrollbarInternalController_State* tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State::MOUSEOVER = new GUIHorizontalScrollbarInternalController_State("MOUSEOVER", 1);
GUIHorizontalScrollbarInternalController_State* tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State::DRAGGING = new GUIHorizontalScrollbarInternalController_State("DRAGGING", 2);

GUIHorizontalScrollbarInternalController_State* GUIHorizontalScrollbarInternalController_State::valueOf(const string& a0)
{
	if (DRAGGING->getName() == a0) return DRAGGING;
	if (MOUSEOVER->getName() == a0) return MOUSEOVER;
	if (NONE->getName() == a0) return NONE;
	// TODO: throw exception here maybe
	return nullptr;
}
