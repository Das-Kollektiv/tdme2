#include <tdme/gui/nodes/GUITextNode.h>

#include <string>
#include <vector>

#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIFont.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/MutableString.h>

using std::vector;
using std::string;

using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIFont;
using tdme::utils::Exception;
using tdme::utils::MutableString;

GUITextNode::GUITextNode(
	GUIScreenNode* screenNode,
	GUIParentNode* parentNode,
	const string& id,
	GUINode_Flow* flow,
	const GUINode_Alignments& alignments,
	const GUINode_RequestedConstraints& requestedConstraints,
	const GUIColor& backgroundColor,
	const string& backgroundImage,
	const GUINode_Scale9Grid& backgroundImageScale9Grid,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	const string& font,
	const string& color,
	const MutableString& text
) throw(Exception):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, border, padding, showOn, hideOn)
{
	this->font = GUI::getFont(font);
	this->color = color.empty() == true || color.length() == 0 ? GUIColor() : GUIColor(color);
	this->text.set(text);
	this->font->initialize();
}

const string GUITextNode::getNodeType()
{
	return "text";
}

bool GUITextNode::isContentNode()
{
	return true;
}

int32_t GUITextNode::getContentWidth()
{
	return font->getTextWidth(text) + border.left + border.right + padding.left + padding.right;
}

int32_t GUITextNode::getContentHeight()
{
	return font->getLineHeight() + border.top + border.bottom + padding.top + padding.bottom;
}

void GUITextNode::setText(const MutableString& text) {
	this->text = text;
	screenNode->layout(parentNode);
}

void GUITextNode::dispose()
{
	this->font->dispose();
	GUINode::dispose();
}

void GUITextNode::render(GUIRenderer* guiRenderer, vector<GUINode*>& floatingNodes)
{
	if (conditionsMet == false)
		return;

	GUINode::render(guiRenderer, floatingNodes);
	font->drawString(guiRenderer, computedConstraints.left + computedConstraints.alignmentLeft + computedConstraints.contentAlignmentLeft, computedConstraints.top + computedConstraints.alignmentTop + computedConstraints.contentAlignmentTop, text, 0, 0, color);
}

