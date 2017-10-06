// Generated from /tdme/src/tdme/gui/nodes/GUINode.java
#include <tdme/gui/nodes/GUINode_AlignmentVertical.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::utils::Enum;

GUINode_AlignmentVertical::GUINode_AlignmentVertical(const wstring& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUINode_AlignmentVertical* tdme::gui::nodes::GUINode_AlignmentVertical::TOP = new GUINode_AlignmentVertical(L"TOP", 0);
GUINode_AlignmentVertical* tdme::gui::nodes::GUINode_AlignmentVertical::CENTER = new GUINode_AlignmentVertical(L"CENTER", 1);
GUINode_AlignmentVertical* tdme::gui::nodes::GUINode_AlignmentVertical::BOTTOM = new GUINode_AlignmentVertical(L"BOTTOM", 2);

GUINode_AlignmentVertical* GUINode_AlignmentVertical::valueOf(const wstring& a0)
{
	if (BOTTOM->getName() == a0) return BOTTOM;
	if (CENTER->getName() == a0) return CENTER;
	if (TOP->getName() == a0) return TOP;
	// TODO: throw exception here maybe
	return nullptr;
}
