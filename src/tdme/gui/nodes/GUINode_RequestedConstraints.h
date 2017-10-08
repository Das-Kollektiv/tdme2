#pragma once

#include <fwd-tdme.h>
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
 * Requested constraints for this node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUINode_RequestedConstraints
{

public: /* protected */
	GUINode_RequestedConstraints_RequestedConstraintsType* leftType {  };
	int32_t left {  };
	GUINode_RequestedConstraints_RequestedConstraintsType* topType {  };
	int32_t top {  };
	GUINode_RequestedConstraints_RequestedConstraintsType* widthType {  };
	int32_t width {  };
	GUINode_RequestedConstraints_RequestedConstraintsType* heightType {  };
	int32_t height {  };

public:
	GUINode_RequestedConstraints();

private:
	friend class GUINode;
	friend class GUINode_Flow;
	friend class GUINode_AlignmentHorizontal;
	friend class GUINode_AlignmentVertical;
	friend class GUINode_Alignments;
	friend class GUINode_RequestedConstraints_RequestedConstraintsType;
	friend class GUINode_ComputedConstraints;
	friend class GUINode_Padding;
	friend class GUINode_Border;
};
