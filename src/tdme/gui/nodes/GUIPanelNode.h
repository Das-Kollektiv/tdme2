#pragma once

#include <string>

#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUILayoutNode.h>

using std::wstring;

using tdme::gui::nodes::GUILayoutNode;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUILayoutNode_Alignment;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;


struct default_init_tag;

/** 
 * GUI panel node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIPanelNode
	: public GUILayoutNode
{

public:
	typedef GUILayoutNode super;

protected:

	/** 
	 * Public constructor
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
	 * @param alignment
	 * @throws GUIParserException
	 */
	void ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, GUILayoutNode_Alignment* alignment) /* throws(GUIParserException) */;

public: /* protected */
	const wstring getNodeType() override;

public:
	void handleMouseEvent(GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUIKeyboardEvent* event) override;

	// Generated
	GUIPanelNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, GUILayoutNode_Alignment* alignment);
protected:
	GUIPanelNode(const ::default_init_tag&);
};
