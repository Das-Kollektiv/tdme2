#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::utils::Enum;

GUINode_AlignmentHorizontal::GUINode_AlignmentHorizontal(const wstring& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUINode_AlignmentHorizontal* tdme::gui::nodes::GUINode_AlignmentHorizontal::LEFT = new GUINode_AlignmentHorizontal(L"LEFT", 0);
GUINode_AlignmentHorizontal* tdme::gui::nodes::GUINode_AlignmentHorizontal::CENTER = new GUINode_AlignmentHorizontal(L"CENTER", 1);
GUINode_AlignmentHorizontal* tdme::gui::nodes::GUINode_AlignmentHorizontal::RIGHT = new GUINode_AlignmentHorizontal(L"RIGHT", 2);

GUINode_AlignmentHorizontal* GUINode_AlignmentHorizontal::valueOf(const wstring& a0)
{
	if (CENTER->getName() == a0) return CENTER;
	if (LEFT->getName() == a0) return LEFT;
	if (RIGHT->getName() == a0) return RIGHT;
	// TODO: throw exception here maybe
	return nullptr;
}
