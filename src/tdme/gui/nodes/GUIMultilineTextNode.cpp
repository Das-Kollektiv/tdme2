#include <tdme/gui/nodes/GUIMultilineTextNode.h>

#include <string>
#include <vector>

#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>
#include <tdme/gui/nodes/GUINode_AlignmentVertical.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/renderer/GUIFont.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/MutableString.h>

using std::vector;
using std::string;

using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::renderer::GUIFont;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::MutableString;

GUIMultilineTextNode::GUIMultilineTextNode(
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

const string GUIMultilineTextNode::getNodeType()
{
	return "multiline-text";
}

bool GUIMultilineTextNode::isContentNode()
{
	return true;
}

int32_t GUIMultilineTextNode::getContentWidth()
{
	if (requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return autoWidth + border.left + border.right + padding.left + padding.right;
	} else {
		return computedConstraints.width;
	}
}

int32_t GUIMultilineTextNode::getContentHeight()
{	if (requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return autoHeight + border.top + border.bottom + padding.top + padding.bottom;
	} else {
		return computedConstraints.height;
	}
}

void GUIMultilineTextNode::computeContentAlignment() {
	// TODO: this is beeing called very often and thus makes layouting slow, please FIXME
	autoWidth = 0;
	autoHeight = 0;
	{
		string line;
		string word;
		bool hadBreak = false;
		for (auto i = 0; i < text.length(); i++) {
			auto c = text.charAt(i);
			auto lastChar = i == text.length() - 1;
			if (c == '\n' || c == ' ' || c == '\t' || lastChar == true) {
				// determine current line width + word width
				auto lineWidth = font->getTextWidth(MutableString(line)) + font->getTextWidth(MutableString(word));
				// check if too long
				auto tooLong =
					requestedConstraints.widthType != GUINode_RequestedConstraints_RequestedConstraintsType::AUTO &&
					lineWidth >= computedConstraints.width - (border.left + border.right + padding.left + padding.right);
				// if not auto and too long then draw current line and do a new line or flush last text
				if (tooLong == true ||
					c == '\n' ||
					lastChar == true) {
					if (tooLong == false || hadBreak == false) line+= word;
					// determine current line width
					lineWidth = font->getTextWidth(MutableString(line));
					// alignment
					if (hadBreak == false) {
						// no op
						line.clear();
					} else
					if (tooLong == true) {
						line = word;
						if (c != '\n') line+= c;
					} else {
						line.clear();
					}
					word.clear();
					hadBreak = false;
					if (lineWidth > autoWidth) autoWidth = lineWidth;
					autoHeight+= font->getLineHeight();
				} else
				if (c != '\n') {
					line+= word + c;
					word.clear();
					hadBreak = true;
				}
			} else {
				word+= c;
			}
		}
	}
}

void GUIMultilineTextNode::dispose()
{
	this->font->dispose();
	GUINode::dispose();
}

void GUIMultilineTextNode::render(GUIRenderer* guiRenderer, vector<GUINode*>& floatingNodes)
{
	if (conditionsMet == false)
		return;

	GUINode::render(guiRenderer, floatingNodes);

	{
		auto xIndentLeft = computedConstraints.left + border.left + padding.left;
		auto yIndentTop = computedConstraints.top + border.top + padding.top;
		auto y = 0;
		if (alignments.vertical == GUINode_AlignmentVertical::TOP) {
			// no op
		} else
		if (alignments.vertical == GUINode_AlignmentVertical::CENTER) {
			y = (computedConstraints.height - (border.top + border.bottom + padding.top + padding.bottom) - autoHeight) / 2;
		} else
		if (alignments.vertical == GUINode_AlignmentVertical::BOTTOM) {
			y = (computedConstraints.height - (border.top + border.bottom + padding.top + padding.bottom) - autoHeight);
		}
		string line;
		string word;
		bool hadBreak = false;
		for (auto i = 0; i < text.length(); i++) {
			auto c = text.charAt(i);
			auto lastChar = i == text.length() - 1;
			if (c == '\n' || c == ' ' || c == '\t' || lastChar == true) {
				// determine current line width + word width
				auto lineWidth = font->getTextWidth(MutableString(line)) + font->getTextWidth(MutableString(word));
				// check if too long
				auto tooLong =
					requestedConstraints.widthType != GUINode_RequestedConstraints_RequestedConstraintsType::AUTO &&
					lineWidth >= computedConstraints.width - (border.left + border.right + padding.left + padding.right);
				// if not auto and too long then draw current line and do a new line or flush last text
				if (tooLong == true ||
					c == '\n' ||
					lastChar == true) {
					if (tooLong == false || hadBreak == false) line+= word;
					// determine current line width
					lineWidth = font->getTextWidth(MutableString(line));
					// alignment
					auto x = 0;
					if (alignments.horizontal == GUINode_AlignmentHorizontal::LEFT) {
						// no op
					} else
					if (alignments.horizontal == GUINode_AlignmentHorizontal::CENTER) {
						x = (computedConstraints.width - (border.left + border.right + padding.left + padding.right) - lineWidth) / 2;
					} else
					if (alignments.horizontal == GUINode_AlignmentHorizontal::RIGHT) {
						x = (computedConstraints.width - (border.left + border.right + padding.left + padding.right) - lineWidth);
					}
					font->drawString(
						guiRenderer,
						x + xIndentLeft,
						y + yIndentTop,
						line,
						0,
						0,
						color
					);
					if (hadBreak == false) {
						// no op
						line.clear();
					} else
					if (tooLong == true) {
						line = word;
						if (c != '\n') line+= c;
					} else {
						line.clear();
					}
					word.clear();
					hadBreak = false;
					y+= font->getLineHeight();
				} else
				if (c != '\n') {
					line+= word + c;
					word.clear();
					hadBreak = true;
				}
			} else {
				word+= c;
			}
		}
	}
}
