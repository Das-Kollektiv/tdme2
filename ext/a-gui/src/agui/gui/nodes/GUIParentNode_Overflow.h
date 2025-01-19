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
 * GUI parent node overflow enum
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUIParentNode_Overflow final: public Enum
{
public:
	AGUI_STATIC_DLL_IMPEXT static GUIParentNode_Overflow* HIDDEN;
	AGUI_STATIC_DLL_IMPEXT static GUIParentNode_Overflow* DOWNSIZE_CHILDREN;
	AGUI_STATIC_DLL_IMPEXT static GUIParentNode_Overflow* SCROLL;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	GUIParentNode_Overflow(const string& name, int ordinal);

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @return enum object
	 */
	static GUIParentNode_Overflow* valueOf(const string& name);
};
