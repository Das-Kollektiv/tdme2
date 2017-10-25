#include <tdme/gui/nodes/GUIParentNode_Overflow.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::string;

using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::utils::Enum;

GUIParentNode_Overflow::GUIParentNode_Overflow(const string& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUIParentNode_Overflow* tdme::gui::nodes::GUIParentNode_Overflow::HIDDEN = new GUIParentNode_Overflow("HIDDEN", 0);
GUIParentNode_Overflow* tdme::gui::nodes::GUIParentNode_Overflow::DOWNSIZE_CHILDREN = new GUIParentNode_Overflow("DOWNSIZE_CHILDREN", 1);
GUIParentNode_Overflow* tdme::gui::nodes::GUIParentNode_Overflow::SCROLL = new GUIParentNode_Overflow("SCROLL", 2);

GUIParentNode_Overflow* GUIParentNode_Overflow::valueOf(const string& a0)
{
	if (DOWNSIZE_CHILDREN->getName() == a0) return DOWNSIZE_CHILDREN;
	if (HIDDEN->getName() == a0) return HIDDEN;
	if (SCROLL->getName() == a0) return SCROLL;
	// TODO: throw exception here maybe
	return nullptr;
}
