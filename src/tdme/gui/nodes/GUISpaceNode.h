#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
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
 * GUI space node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUISpaceNode final
	: public GUINode
{
	friend class tdme::gui::GUIParser;

protected:

	/** 
	 * @return node type
	 */
	const string getNodeType() override;
	bool isContentNode() override;
	GUISpaceNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const string& id, GUINode_Flow* flow, const GUINode_Alignments& alignments, const GUINode_RequestedConstraints& requestedConstraints, const GUIColor& backgroundColor, const GUINode_Border& border, const GUINode_Padding& padding, const GUINodeConditions& showOn, const GUINodeConditions& hideOn);

public:
	int32_t getContentWidth() override;
	int32_t getContentHeight() override;

	/** 
	 * Create requested constraints
	 * @param left
	 * @param top
	 * @param width
	 * @param height
	 * @return requested constraints
	 */
	static GUINode_RequestedConstraints createRequestedConstraints(const string& left, const string& top, const string& width, const string& height);
	void dispose() override;
	void render(GUIRenderer* guiRenderer, vector<GUINode*>& floatingNodes) override;

};
