#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINode.h>

using std::string;

using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIRenderer;

/** 
 * GUI vertical scrollbar internal node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIVerticalScrollbarInternalNode
	: public GUINode
{

private:
	GUIColor barColorNone {  };
	GUIColor barColorMouseOver {  };
	GUIColor barColorDragging {  };

protected:
	const string getNodeType() override;
	bool isContentNode() override;

public:
	int32_t getContentWidth() override;
	int32_t getContentHeight() override;

	/** 
	 * Render
	 * @param gui renderer
	 * @param floating nodes
	 */
	void render(GUIRenderer* guiRenderer, vector<GUINode*>& floatingNodes) override;

	GUIVerticalScrollbarInternalNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const string& id, GUINode_Flow* flow, const GUINode_Alignments& alignments, const GUINode_RequestedConstraints& requestedConstraints, const GUIColor& backgroundColor, const GUINode_Border& border, const GUINode_Padding& padding, const GUINodeConditions& showOn, const GUINodeConditions& hideOn, const GUIColor& barColorNone, const GUIColor& barColorMouseOver, const GUIColor& barColorDragging);
};
