#pragma once

#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/renderer/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>

using std::string;
using std::vector;

// namespaces
namespace agui {
namespace gui {
namespace nodes {
	using ::agui::gui::renderer::GUIRenderer;
}
}
}

/**
 * GUI horizontal scroll bar internal node
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUIHorizontalScrollbarInternalNode
	: public GUINode
{

private:
	GUIColor barColorNone;
	GUIColor barColorMouseOver;
	GUIColor barColorDragging;

protected:
	// overridden methods
	const string getNodeType() override;
	bool isContentNode() override;

public:
	// forbid class copy
	FORBID_CLASS_COPY(GUIHorizontalScrollbarInternalNode)

	/**
	 * Constructor
	 * @param screenNode screen node
	 * @param parentNode parent node
	 * @param id id
	 * @param flow flow
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
	 * @param barColorNone bar color none
	 * @param barColorMouseOver bar color mouse over
	 * @param barColorDragging bar color dragging
	 *
	 */
	GUIHorizontalScrollbarInternalNode(
		GUIScreenNode* screenNode,
		GUIParentNode* parentNode,
		const string& id,
		GUINode_Flow* flow,
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
		const GUIColor& barColorNone,
		const GUIColor& barColorMouseOver,
		const GUIColor& barColorDragging
	);

	// overridden methods
	int getContentWidth() override;
	int getContentHeight() override;
	void render(GUIRenderer* guiRenderer) override;

};
