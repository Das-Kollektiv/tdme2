#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>

using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode;

/** 
 * GUI node requested constraints entity
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::gui::nodes::GUINode_RequestedConstraints
{
	GUINode_RequestedConstraints_RequestedConstraintsType* leftType {  };
	int32_t left {  };
	GUINode_RequestedConstraints_RequestedConstraintsType* topType {  };
	int32_t top {  };
	GUINode_RequestedConstraints_RequestedConstraintsType* widthType {  };
	int32_t width {  };
	GUINode_RequestedConstraints_RequestedConstraintsType* heightType {  };
	int32_t height {  };
};
