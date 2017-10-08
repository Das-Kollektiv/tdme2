#pragma once

#include <tdme.h>
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


struct default_init_tag;

/** 
 * Computed constraints for this node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUINode_ComputedConstraints
{

public:
	int32_t left {  };
	int32_t top {  };
	int32_t width {  };
	int32_t height {  };
	int32_t alignmentLeft {  };
	int32_t alignmentTop {  };
	int32_t contentAlignmentLeft {  };
	int32_t contentAlignmentTop {  };

	// Generated
	GUINode_ComputedConstraints();
protected:
	GUINode_ComputedConstraints(const ::default_init_tag&);

private:
	friend class GUINode;
	friend class GUINode_Flow;
	friend class GUINode_AlignmentHorizontal;
	friend class GUINode_AlignmentVertical;
	friend class GUINode_Alignments;
	friend class GUINode_RequestedConstraints;
	friend class GUINode_RequestedConstraints_RequestedConstraintsType;
	friend class GUINode_Padding;
	friend class GUINode_Border;
};
