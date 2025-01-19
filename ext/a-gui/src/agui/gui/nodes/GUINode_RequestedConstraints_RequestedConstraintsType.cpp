#include <agui/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>

#include <string>

#include <agui/agui.h>
#include <agui/utilities/Enum.h>

using std::string;

using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using agui::utilities::Enum;

GUINode_RequestedConstraints_RequestedConstraintsType::GUINode_RequestedConstraints_RequestedConstraintsType(const string& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUINode_RequestedConstraints_RequestedConstraintsType* agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType::NONE = new GUINode_RequestedConstraints_RequestedConstraintsType("NONE", 0);
GUINode_RequestedConstraints_RequestedConstraintsType* agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL = new GUINode_RequestedConstraints_RequestedConstraintsType("PIXEL", 1);
GUINode_RequestedConstraints_RequestedConstraintsType* agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType::PERCENT = new GUINode_RequestedConstraints_RequestedConstraintsType("PERCENT", 2);
GUINode_RequestedConstraints_RequestedConstraintsType* agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType::STAR = new GUINode_RequestedConstraints_RequestedConstraintsType("STAR", 3);
GUINode_RequestedConstraints_RequestedConstraintsType* agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType::AUTO = new GUINode_RequestedConstraints_RequestedConstraintsType("AUTO", 4);
GUINode_RequestedConstraints_RequestedConstraintsType* agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType::TABLECELL = new GUINode_RequestedConstraints_RequestedConstraintsType("TABLECELL", 5);

GUINode_RequestedConstraints_RequestedConstraintsType* GUINode_RequestedConstraints_RequestedConstraintsType::valueOf(const string& name)
{
	if (NONE->getName() == name) return NONE;
	if (AUTO->getName() == name) return AUTO;
	if (PERCENT->getName() == name) return PERCENT;
	if (PIXEL->getName() == name) return PIXEL;
	if (STAR->getName() == name) return STAR;
	if (TABLECELL->getName() == name) return TABLECELL;
	// TODO: throw exception here maybe
	return nullptr;
}
