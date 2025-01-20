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
 * GUI node flow enum
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUINode_Flow final: public Enum
{
public:
	AGUI_STATIC_DLL_IMPEXT static GUINode_Flow* INTEGRATED;
	AGUI_STATIC_DLL_IMPEXT static GUINode_Flow* FLOATING;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	GUINode_Flow(const string& name, int ordinal);

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @returns enum object
	 */
	static GUINode_Flow* valueOf(const string& name);

};
