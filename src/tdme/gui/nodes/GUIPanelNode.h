#pragma once

#include <set>
#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUILayoutNode.h>

using std::set;
using std::string;

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
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;

/** 
 * GUI panel node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIPanelNode
	: public GUILayoutNode
{
	friend class tdme::gui::GUIParser;

protected:
	const string getNodeType() override;

	/**
	 * Constructor
	 * @param screenNode screen node
	 * @param parentNode parent node
	 * @param id id
	 * @param flow flow
	 * @param overflowX overflow x
	 * @param overflowY overflow y
	 * @param alignments alignments
	 * @param requestedConstraints requested constraints
	 * @param backgroundColor background color
	 * @param backgroundImage background image
	 * @param backgroundImageScale9Grid background image scale 9 grid
	 * @param backgroundImageEffectColorMul background image effect color mul
	 * @param backgroundImageEffectColorAdd background image effect color add
	 * @param border border
	 * @param padding padding
	 * @param showOn show on
	 * @param hideOn hide on
	 * @param alignment alignment
	 */
	GUIPanelNode(
		GUIScreenNode* screenNode,
		GUIParentNode* parentNode,
		const string& id,
		GUINode_Flow* flow,
		GUIParentNode_Overflow* overflowX,
		GUIParentNode_Overflow* overflowY,
		const GUINode_Alignments& alignments,
		const GUINode_RequestedConstraints& requestedConstraints,
		const GUIColor& backgroundColor,
		const string& backgroundImage,
		const GUINode_Scale9Grid& backgroundImageScale9Grid,
		const GUIColor& backgroundImageEffectColorMul,
		const GUIColor& backgroundImageEffectColorAdd,
		const GUINode_Border& border,
		const GUINode_Padding& padding,
		const GUINodeConditions& showOn,
		const GUINodeConditions& hideOn,
		GUILayoutNode_Alignment* alignment
	) throw (GUIParserException);

public:
	// overriden methods
	void determineMouseEventNodes(GUIMouseEvent* event, bool floatingNode, set<string>& eventNodeIds, set<string>& eventFloatingNodeIds) override;
	void handleKeyboardEvent(GUIKeyboardEvent* event) override;

};
