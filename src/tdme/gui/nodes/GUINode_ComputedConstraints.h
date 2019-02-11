#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>

using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode;

/** 
 * GUI node computed constraints
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::gui::nodes::GUINode_ComputedConstraints
{
	int32_t left {  };
	int32_t top {  };
	int32_t width {  };
	int32_t height {  };
	int32_t alignmentLeft {  };
	int32_t alignmentTop {  };
	int32_t contentAlignmentLeft {  };
	int32_t contentAlignmentTop {  };
};
