// Generated from /tdme/src/tdme/gui/nodes/GUINode.java
#include <tdme/gui/nodes/GUINode_Flow.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::gui::nodes::GUINode_Flow;
using tdme::utils::Enum;

GUINode_Flow::GUINode_Flow(const wstring& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUINode_Flow* tdme::gui::nodes::GUINode_Flow::INTEGRATED = new GUINode_Flow(L"INTEGRATED", 0);
GUINode_Flow* tdme::gui::nodes::GUINode_Flow::FLOATING = new GUINode_Flow(L"FLOATING", 1);

GUINode_Flow* GUINode_Flow::valueOf(const wstring& a0)
{
	if (FLOATING->getName() == a0) return FLOATING;
	if (INTEGRATED->getName() == a0) return INTEGRATED;
	// TODO: throw exception here maybe
	return nullptr;
}

