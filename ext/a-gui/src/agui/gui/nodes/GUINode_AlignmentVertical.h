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
 * GUI node vertical alignment enum
 */
class agui::gui::nodes::GUINode_AlignmentVertical final: public Enum
{
public:
	AGUI_STATIC_DLL_IMPEXT static GUINode_AlignmentVertical* NONE;
	AGUI_STATIC_DLL_IMPEXT static GUINode_AlignmentVertical* TOP;
	AGUI_STATIC_DLL_IMPEXT static GUINode_AlignmentVertical* CENTER;
	AGUI_STATIC_DLL_IMPEXT static GUINode_AlignmentVertical* BOTTOM;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	GUINode_AlignmentVertical(const string& name, int ordinal);

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @returns enum object
	 */
	static GUINode_AlignmentVertical* valueOf(const string& name);
};
