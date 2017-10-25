#pragma once

#include <string>

#include <tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIParentNode.h>

using std::string;

using tdme::gui::nodes::GUIParentNode;
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

/** 
 * GUI element node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIElementNode final
	: public GUIParentNode
{

public: /* protected */
	static string CONDITION_ALWAYS;
	static string CONDITION_ONMOUSEOVER;
	static string CONDITION_CLICK;

public:
	static string CONDITION_FOCUS;

public: /* protected */
	string name {  };
	string value {  };
	bool selected {  };
	bool disabled {  };
	GUINodeConditions* activeConditions {  };
	bool focusable {  };
	bool ignoreEvents {  };

public: /* protected */

	/** 
	 * @return node type
	 */
	const string getNodeType() override;
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
	const string& getName();

	/** 
	 * @return value
	 */
	const string& getValue();

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

	GUIElementNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const string& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, const string& name, const string& value, bool selected, bool disabled, bool focusable, bool ignoreEvents);

private:
	void init();
};
