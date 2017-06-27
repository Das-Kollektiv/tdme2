// Generated from /tdme/src/tdme/gui/nodes/GUINode.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode;


struct default_init_tag;

/** 
 * Alignments
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUINode_Alignments
	: public virtual Object
{

public:
	typedef Object super;

public: /* protected */
	GUINode_AlignmentHorizontal* horizontal {  };
	GUINode_AlignmentVertical* vertical {  };

public:
	String* toString() override;

	// Generated
	GUINode_Alignments();
protected:
	GUINode_Alignments(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUINode;
	friend class GUINode_Flow;
	friend class GUINode_AlignmentHorizontal;
	friend class GUINode_AlignmentVertical;
	friend class GUINode_RequestedConstraints;
	friend class GUINode_RequestedConstraints_RequestedConstraintsType;
	friend class GUINode_ComputedConstraints;
	friend class GUINode_Padding;
	friend class GUINode_Border;
};
