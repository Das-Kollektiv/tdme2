#include <tdme/gui/nodes/GUINode_AlignmentVertical.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::string;

using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::utils::Enum;

GUINode_AlignmentVertical::GUINode_AlignmentVertical(const string& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUINode_AlignmentVertical* tdme::gui::nodes::GUINode_AlignmentVertical::TOP = new GUINode_AlignmentVertical("TOP", 0);
GUINode_AlignmentVertical* tdme::gui::nodes::GUINode_AlignmentVertical::CENTER = new GUINode_AlignmentVertical("CENTER", 1);
GUINode_AlignmentVertical* tdme::gui::nodes::GUINode_AlignmentVertical::BOTTOM = new GUINode_AlignmentVertical("BOTTOM", 2);

GUINode_AlignmentVertical* GUINode_AlignmentVertical::valueOf(const string& a0)
{
	if (BOTTOM->getName() == a0) return BOTTOM;
	if (CENTER->getName() == a0) return CENTER;
	if (TOP->getName() == a0) return TOP;
	// TODO: throw exception here maybe
	return nullptr;
}
