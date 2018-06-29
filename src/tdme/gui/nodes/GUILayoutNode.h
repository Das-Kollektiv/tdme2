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
using tdme::gui::nodes::GUINode_Scale9Grid;
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
	 * @param background image
	 * @param background image scale 9 grid
	 * @param border
	 * @param padding
	 * @param show on
	 * @param hide on
	 * @param alignment
	 */
	GUILayoutNode(
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
		const GUINode_Border& border,
		const GUINode_Padding& padding,
		const GUINodeConditions& showOn,
		const GUINodeConditions& hideOn,
		GUILayoutNode_Alignment* alignment
	) throw(GUIParserException);

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
