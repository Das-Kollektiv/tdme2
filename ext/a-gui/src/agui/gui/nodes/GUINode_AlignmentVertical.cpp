#include <agui/gui/nodes/GUINode_AlignmentVertical.h>

#include <string>

#include <agui/agui.h>
#include <agui/utilities/Enum.h>

using std::string;

using agui::gui::nodes::GUINode_AlignmentVertical;
using agui::utilities::Enum;

GUINode_AlignmentVertical::GUINode_AlignmentVertical(const string& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUINode_AlignmentVertical* agui::gui::nodes::GUINode_AlignmentVertical::NONE = new GUINode_AlignmentVertical("NONE", 0);
GUINode_AlignmentVertical* agui::gui::nodes::GUINode_AlignmentVertical::TOP = new GUINode_AlignmentVertical("TOP", 0);
GUINode_AlignmentVertical* agui::gui::nodes::GUINode_AlignmentVertical::CENTER = new GUINode_AlignmentVertical("CENTER", 1);
GUINode_AlignmentVertical* agui::gui::nodes::GUINode_AlignmentVertical::BOTTOM = new GUINode_AlignmentVertical("BOTTOM", 2);

GUINode_AlignmentVertical* GUINode_AlignmentVertical::valueOf(const string& name)
{
	if (NONE->getName() == name) return NONE;
	if (TOP->getName() == name) return TOP;
	if (CENTER->getName() == name) return CENTER;
	if (BOTTOM->getName() == name) return BOTTOM;
	// TODO: throw exception here maybe
	return nullptr;
}
