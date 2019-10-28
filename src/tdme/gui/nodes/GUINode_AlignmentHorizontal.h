#pragma once

#include <string>

#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::string;

using tdme::utils::Enum;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;

/**
 * GUI node horizontal alignment enum
 * @author Andreas Drewke
 */
class tdme::gui::nodes::GUINode_AlignmentHorizontal final: public Enum
{
public:
	static GUINode_AlignmentHorizontal* LEFT;
	static GUINode_AlignmentHorizontal* CENTER;
	static GUINode_AlignmentHorizontal* RIGHT;
	GUINode_AlignmentHorizontal(const string& name, int ordinal);
	static GUINode_AlignmentHorizontal* valueOf(const string& a0);
};
