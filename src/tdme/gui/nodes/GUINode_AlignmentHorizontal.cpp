#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::string;

using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::utils::Enum;

GUINode_AlignmentHorizontal::GUINode_AlignmentHorizontal(const string& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUINode_AlignmentHorizontal* tdme::gui::nodes::GUINode_AlignmentHorizontal::LEFT = new GUINode_AlignmentHorizontal("LEFT", 0);
GUINode_AlignmentHorizontal* tdme::gui::nodes::GUINode_AlignmentHorizontal::CENTER = new GUINode_AlignmentHorizontal("CENTER", 1);
GUINode_AlignmentHorizontal* tdme::gui::nodes::GUINode_AlignmentHorizontal::RIGHT = new GUINode_AlignmentHorizontal("RIGHT", 2);

GUINode_AlignmentHorizontal* GUINode_AlignmentHorizontal::valueOf(const string& a0)
{
	if (CENTER->getName() == a0) return CENTER;
	if (LEFT->getName() == a0) return LEFT;
	if (RIGHT->getName() == a0) return RIGHT;
	// TODO: throw exception here maybe
	return nullptr;
}
