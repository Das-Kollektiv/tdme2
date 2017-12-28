#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIParentNode.h>

using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUILayoutNode_Alignment;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::nodes::GUIScreenNode;

class tdme::gui::nodes::GUILayoutNode
	: public GUIParentNode
{
	friend class tdme::gui::GUIParser;

private:
	GUILayoutNode_Alignment* alignment {  };

protected:
	/** 
	 * @return node type
	 */
	const string getNodeType() override;
	bool isContentNode() override;
	void layoutSubNodes() override;
	void setTop(int32_t top) override;
	void setLeft(int32_t left) override;
	GUILayoutNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const string& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, GUILayoutNode_Alignment* alignment);

public:
	int32_t getContentWidth() override;
	int32_t getContentHeight() override;

public:

	/** 
	 * Create alignment
	 * @param alignment
	 * @return alignment
	 */
	static GUILayoutNode_Alignment* createAlignment(const string& alignment);

private:
	friend class GUILayoutNode_Alignment;
};
