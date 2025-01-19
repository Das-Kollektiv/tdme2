#include <agui/gui/nodes/GUINode_Flow.h>

#include <string>

#include <agui/agui.h>
#include <agui/utilities/Enum.h>

using std::string;

using agui::gui::nodes::GUINode_Flow;
using agui::utilities::Enum;

GUINode_Flow::GUINode_Flow(const string& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUINode_Flow* agui::gui::nodes::GUINode_Flow::INTEGRATED = new GUINode_Flow("INTEGRATED", 0);
GUINode_Flow* agui::gui::nodes::GUINode_Flow::FLOATING = new GUINode_Flow("FLOATING", 1);

GUINode_Flow* GUINode_Flow::valueOf(const string& name)
{
	if (FLOATING->getName() == name) return FLOATING;
	if (INTEGRATED->getName() == name) return INTEGRATED;
	// TODO: throw exception here maybe
	return nullptr;
}

