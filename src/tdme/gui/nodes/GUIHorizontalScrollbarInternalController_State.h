#pragma once

#include <string>

#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::string;

using tdme::utils::Enum;
using tdme::gui::nodes::GUIHorizontalScrollbarInternalController;
using tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State;

class tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State final
	: public Enum
{
	friend class GUIHorizontalScrollbarInternalController;
public:
	static GUIHorizontalScrollbarInternalController_State *NONE;
	static GUIHorizontalScrollbarInternalController_State *MOUSEOVER;
	static GUIHorizontalScrollbarInternalController_State *DRAGGING;
	GUIHorizontalScrollbarInternalController_State(const string& name, int ordinal);
	static GUIHorizontalScrollbarInternalController_State* valueOf(const string& a0);
};
