#include <agui/gui/nodes/GUITextNode.h>

#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUINode_Border.h>
#include <agui/gui/nodes/GUINode_ComputedConstraints.h>
#include <agui/gui/nodes/GUINode_Padding.h>
#include <agui/gui/nodes/GUINode_Scale9Grid.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/renderer/GUIFont.h>
#include <agui/utilities/Exception.h>
#include <agui/utilities/MutableString.h>

using std::string;
using std::vector;

using agui::gui::nodes::GUIColor;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_ComputedConstraints;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_Scale9Grid;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextNode;
using agui::gui::renderer::GUIFont;
using agui::utilities::Exception;
using agui::utilities::MutableString;

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
	const GUIColor& backgroundImageEffectColorMul,
	const GUIColor& backgroundImageEffectColorAdd,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	const string& tooltip,
	const string& font,
	int size,
	const string& color,
	const MutableString& text
):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn, tooltip)
{
	this->font = font.empty() == true?nullptr:screenNode->getFont(font, size);
	this->color = color.empty() == true || color.length() == 0?GUIColor():GUIColor(color);
	this->text.set(text);
	if (this->font != nullptr) this->font->initialize();
}

const string GUITextNode::getNodeType()
{
	return "text";
}

bool GUITextNode::isContentNode()
{
	return true;
}

int GUITextNode::getContentWidth()
{
	return font != nullptr?font->getTextWidth(text) + border.left + border.right + padding.left + padding.right:0;
}

int GUITextNode::getContentHeight()
{
	return font != nullptr?font->getLineHeight() + border.top + border.bottom + padding.top + padding.bottom:0;
}

void GUITextNode::setText(const MutableString& text) {
	if (this->text.equals(text)) return;
	this->text = text;
	screenNode->invalidateLayout(this);
}

void GUITextNode::dispose()
{
	if (font != nullptr) font->dispose();
	GUINode::dispose();
}

void GUITextNode::render(GUIRenderer* guiRenderer)
{
	if (shouldRender() == false) return;

	GUINode::render(guiRenderer);
	if (font != nullptr) {
		font->drawString(
			guiRenderer,
			computedConstraints.left + computedConstraints.alignmentLeft + computedConstraints.contentAlignmentLeft,
			computedConstraints.top + computedConstraints.alignmentTop + computedConstraints.contentAlignmentTop,
			text,
			0,
			0,
			color
		);
	}
}

