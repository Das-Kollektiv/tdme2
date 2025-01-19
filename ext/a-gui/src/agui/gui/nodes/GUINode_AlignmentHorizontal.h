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
 * GUI node horizontal alignment enum
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUINode_AlignmentHorizontal final: public Enum
{
public:
	AGUI_STATIC_DLL_IMPEXT static GUINode_AlignmentHorizontal* NONE;
	AGUI_STATIC_DLL_IMPEXT static GUINode_AlignmentHorizontal* LEFT;
	AGUI_STATIC_DLL_IMPEXT static GUINode_AlignmentHorizontal* CENTER;
	AGUI_STATIC_DLL_IMPEXT static GUINode_AlignmentHorizontal* RIGHT;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	GUINode_AlignmentHorizontal(const string& name, int ordinal);

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @return enum object
	 */
	static GUINode_AlignmentHorizontal* valueOf(const string& name);
};
