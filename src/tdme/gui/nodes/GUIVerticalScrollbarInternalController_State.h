#pragma once

#include <string>

#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::string;

using tdme::utils::Enum;
using tdme::gui::nodes::GUIVerticalScrollbarInternalController;
using tdme::gui::nodes::GUIVerticalScrollbarInternalController_State;

class tdme::gui::nodes::GUIVerticalScrollbarInternalController_State final
	: public Enum
{
	friend class GUIVerticalScrollbarInternalController;

public:
	static GUIVerticalScrollbarInternalController_State *NONE;
	static GUIVerticalScrollbarInternalController_State *MOUSEOVER;
	static GUIVerticalScrollbarInternalController_State *DRAGGING;
	GUIVerticalScrollbarInternalController_State(const string& name, int ordinal);
	static GUIVerticalScrollbarInternalController_State* valueOf(const string& a0);
};
