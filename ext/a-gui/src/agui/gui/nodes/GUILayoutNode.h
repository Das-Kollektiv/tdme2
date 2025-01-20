#pragma once

#include <agui/agui.h>
#include <agui/gui/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIParentNode.h>

/**
 * GUI layout node
 */
class agui::gui::nodes::GUILayoutNode: public GUIParentNode
{
	friend class agui::gui::GUIParser;

private:
	GUILayoutNode_Alignment* alignment { nullptr };

protected:
	// forbid class copy
	FORBID_CLASS_COPY(GUILayoutNode)

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
	 * @param tooltip tooltip
	 * @param alignment alignment
	 * @throws agui::gui::GUIParserException
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
		const GUIColor& backgroundImageEffectColorMul,
		const GUIColor& backgroundImageEffectColorAdd,
		const GUINode_Border& border,
		const GUINode_Padding& padding,
		const GUINodeConditions& showOn,
		const GUINodeConditions& hideOn,
		const string& tooltip,
		GUILayoutNode_Alignment* alignment
	);

	// overridden methods
	const string getNodeType() override;
	bool isContentNode() override;
	void layoutSubNodes() override;
	void setTop(int top) override;
	void setLeft(int left) override;

public:
	// overridden methods
	int getContentWidth() override;
	int getContentHeight() override;

	/**
	 * Create alignment
	 * @param alignment alignment
	 * @returns alignment
	 */
	static GUILayoutNode_Alignment* createAlignment(const string& alignment);

};
