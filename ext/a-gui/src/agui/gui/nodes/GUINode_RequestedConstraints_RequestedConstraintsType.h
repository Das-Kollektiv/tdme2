#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/utilities/Enum.h>

using std::string;

// namespaces
namespace agui {
namespace gui {
namespace nodes {
	using ::agui::utilities::Enum;
}
}
}

/**
 * GUI node requested constraints requested constraints type enum
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType final: public Enum
{
public:
	AGUI_STATIC_DLL_IMPEXT static GUINode_RequestedConstraints_RequestedConstraintsType* NONE;
	AGUI_STATIC_DLL_IMPEXT static GUINode_RequestedConstraints_RequestedConstraintsType* PIXEL;
	AGUI_STATIC_DLL_IMPEXT static GUINode_RequestedConstraints_RequestedConstraintsType* PERCENT;
	AGUI_STATIC_DLL_IMPEXT static GUINode_RequestedConstraints_RequestedConstraintsType* STAR;
	AGUI_STATIC_DLL_IMPEXT static GUINode_RequestedConstraints_RequestedConstraintsType* AUTO;
	AGUI_STATIC_DLL_IMPEXT static GUINode_RequestedConstraints_RequestedConstraintsType* TABLECELL;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	GUINode_RequestedConstraints_RequestedConstraintsType(const string& name, int ordinal);

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @return enum object
	 */
	static GUINode_RequestedConstraints_RequestedConstraintsType* valueOf(const string& name);

};
