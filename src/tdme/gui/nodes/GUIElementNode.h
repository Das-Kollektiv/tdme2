// Generated from /tdme/src/tdme/gui/nodes/GUIElementNode.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIParentNode.h>

using tdme::gui::nodes::GUIParentNode;
using java::lang::String;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::nodes::GUIScreenNode;


struct default_init_tag;

/** 
 * GUI element node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIElementNode final
	: public GUIParentNode
{

public:
	typedef GUIParentNode super;

public: /* protected */
	static String* CONDITION_ALWAYS;
	static String* CONDITION_ONMOUSEOVER;
	static String* CONDITION_CLICK;

public:
	static String* CONDITION_FOCUS;

public: /* protected */
	String* name {  };
	String* value {  };
	bool selected {  };
	bool disabled {  };
	GUINodeConditions* activeConditions {  };
	bool focusable {  };
	bool ignoreEvents {  };
protected:

	/** 
	 * Constructor
	 * @param screen node
	 * @param parent node
	 * @param id
	 * @param flow
	 * @param overflow x
	 * @param overflow y
	 * @param alignments
	 * @param requested constraints
	 * @param background color
	 * @param border
	 * @param padding
	 * @param show on
	 * @param hide on
	 * @param name
	 * @param value
	 * @param selected
	 * @param disabled
	 * @param focusable
	 * @param ignore events
	 * @throws GUIParserException
	 */
	void ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, String* name, String* value, bool selected, bool disabled, bool focusable, bool ignoreEvents) /* throws(GUIParserException) */;

public: /* protected */

	/** 
	 * @return node type
	 */
	String* getNodeType() override;
	bool isContentNode() override;

public:
	int32_t getContentWidth() override;
	int32_t getContentHeight() override;

	/** 
	 * @return focusable
	 */
	bool isFocusable();

public: /* protected */

	/** 
	 * Set computed top
	 * @param top
	 */
	void setTop(int32_t top) override;

	/** 
	 * Set computed left
	 * @param left
	 */
	void setLeft(int32_t left) override;
	void layoutSubNodes() override;
	void layout() override;

public:

	/** 
	 * @return name
	 */
	String* getName();

	/** 
	 * @return value
	 */
	String* getValue();

	/** 
	 * @return is selected
	 */
	bool isSelected();

	/** 
	 * @return is disabled
	 */
	bool isDisabled();

	/** 
	 * @return active conditions
	 */
	GUINodeConditions* getActiveConditions();
	void handleMouseEvent(GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUIKeyboardEvent* event) override;

	// Generated
	GUIElementNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, String* name, String* value, bool selected, bool disabled, bool focusable, bool ignoreEvents);
protected:
	GUIElementNode(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
