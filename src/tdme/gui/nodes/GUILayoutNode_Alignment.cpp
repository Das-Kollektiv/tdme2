#include <tdme/gui/nodes/GUILayoutNode_Alignment.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::gui::nodes::GUILayoutNode_Alignment;
using tdme::utils::Enum;

GUILayoutNode_Alignment::GUILayoutNode_Alignment(const wstring& name, int ordinal)
	: Enum(name, ordinal)
{
}

GUILayoutNode_Alignment* tdme::gui::nodes::GUILayoutNode_Alignment::VERTICAL = new GUILayoutNode_Alignment(L"VERTICAL", 0);
GUILayoutNode_Alignment* tdme::gui::nodes::GUILayoutNode_Alignment::HORIZONTAL = new GUILayoutNode_Alignment(L"HORIZONTAL", 1);
GUILayoutNode_Alignment* tdme::gui::nodes::GUILayoutNode_Alignment::NONE = new GUILayoutNode_Alignment(L"NONE", 2);

GUILayoutNode_Alignment* GUILayoutNode_Alignment::valueOf(const wstring& a0)
{
	if (HORIZONTAL->getName() == a0) return HORIZONTAL;
	if (NONE->getName() == a0) return NONE;
	if (VERTICAL->getName() == a0) return VERTICAL;
	// TODO: throw exception here maybe
	return nullptr;
}
