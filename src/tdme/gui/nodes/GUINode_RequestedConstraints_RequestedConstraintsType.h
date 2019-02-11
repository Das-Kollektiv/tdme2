#pragma once

#include <string>

#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::string;

using tdme::utils::Enum;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;

/**
 * GUI node requested constraints requested constraints type enum
 * @author Andreas Drewke
 */
class tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType final: public Enum
{
	friend class GUINode;
	friend class GUINode_Flow;
	friend class GUINode_AlignmentHorizontal;
	friend class GUINode_AlignmentVertical;
	friend class GUINode_Alignments;
	friend class GUINode_RequestedConstraints;
	friend class GUINode_ComputedConstraints;
	friend class GUINode_Padding;
	friend class GUINode_Border;

public:
	static GUINode_RequestedConstraints_RequestedConstraintsType *PIXEL;
	static GUINode_RequestedConstraints_RequestedConstraintsType *PERCENT;
	static GUINode_RequestedConstraints_RequestedConstraintsType *STAR;
	static GUINode_RequestedConstraints_RequestedConstraintsType *AUTO;
	GUINode_RequestedConstraints_RequestedConstraintsType(const string& name, int ordinal);
	static GUINode_RequestedConstraints_RequestedConstraintsType* valueOf(const string& a0);
};
