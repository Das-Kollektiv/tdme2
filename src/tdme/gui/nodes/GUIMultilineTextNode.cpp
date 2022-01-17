#include <tdme/gui/nodes/GUIMultilineTextNode.h>

#include <list>
#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>
#include <tdme/gui/nodes/GUINode_AlignmentVertical.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIFont.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::list;
using std::string;
using std::to_string;

using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::GUI;
using tdme::math::Math;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

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
	const GUIColor& backgroundImageEffectColorMul,
	const GUIColor& backgroundImageEffectColorAdd,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	const string& font,
	const string& color,
	const MutableString& text
):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn)
{
	this->font = font.empty() == true?nullptr:GUI::getFont(screenNode->getApplicationRootPathName(), font);
	this->color = color.empty() == true || color.length() == 0?GUIColor():GUIColor(color);
	this->text.set(text);
	this->autoWidth = 0;
	this->autoHeight = 0;
	this->parentOffsetsChanged = true;
	this->parentXOffsetLast = 0.0f;
	this->parentYOffsetLast = 0.0f;
	this->yLast = 0.0f;
	this->charStartIdx = 0;
	this->charEndIdx = text.size() - 1;
	this->widthLast = -1;
	this->heightLast = -1;
	this->startTextStyleIdx = -1;
	if (this->font != nullptr) this->font->initialize();
}

const string GUIMultilineTextNode::getNodeType()
{
	return "multiline-text";
}

bool GUIMultilineTextNode::isContentNode()
{
	return true;
}

int GUIMultilineTextNode::getContentWidth()
{
	if (requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return font != nullptr?autoWidth + border.left + border.right + padding.left + padding.right:0;
	} else {
		return computedConstraints.width;
	}
}

int GUIMultilineTextNode::getContentHeight()
{	if (requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return font != nullptr?autoHeight + border.top + border.bottom + padding.top + padding.bottom:0;
	} else {
		return computedConstraints.height;
	}
}

void GUIMultilineTextNode::computeContentAlignment() {
	// If fixed width requested and no computed constraints yet, abort
	if (requestedConstraints.widthType != GUINode_RequestedConstraints_RequestedConstraintsType::AUTO && computedConstraints.width == -1) return;
	// width did not change, but relayout has been requested
	if (requestedConstraints.widthType != GUINode_RequestedConstraints_RequestedConstraintsType::AUTO && widthLast == computedConstraints.width) return;
	// no font, exit
	if (font == nullptr) return;

	//
	autoWidth = 0;
	autoHeight = 0;
	string line;
	string word;
	bool hadBreak = false;
	for (auto i = 0; i < text.size(); i++) {
		auto c = text.charAt(i);
		// last char
		auto lastChar = i == text.size() - 1;
		// check for separation char or last char
		if (c == '\n' || c == ' ' || c == '\t' || lastChar == true) {
			// if last char add it to current word
			if (lastChar == true) word+= c;
			// determine current line width + word width
			auto lineWidth = font->getTextWidth(MutableString(line)) + font->getTextWidth(MutableString(word));
			// check if too long
			auto tooLong =
				requestedConstraints.widthType != GUINode_RequestedConstraints_RequestedConstraintsType::AUTO && // TODO: check with <multi... width="auto" />
				lineWidth >= computedConstraints.width - (border.left + border.right + padding.left + padding.right);
			// if not auto and too long then draw current line and do a new line or flush last text
			if (tooLong == true ||
				c == '\n' ||
				lastChar == true) {
				// add word to line if required
				if ((tooLong == true && hadBreak == false) || lastChar == true || c == '\n') {
					line+= word;
					word.clear();
				}
				//
				string lineToRender = line;
				string lineLeft;
				//
				do {
					//
					auto separationAt = font->getTextIndexXAtWidth(MutableString(lineToRender), computedConstraints.width - (border.left + border.right + padding.left + padding.right));
					lineLeft = StringTools::substring(lineToRender, separationAt + 1);
					lineToRender = StringTools::substring(lineToRender, 0, separationAt + 1);
					// determine current line width
					lineWidth = font->getTextWidth(MutableString(lineToRender));
					// track dimension
					if (lineWidth > autoWidth) autoWidth = lineWidth;
					autoHeight+= font->getLineHeight();
					//
					lineToRender = lineLeft;
					lineLeft.clear();
				} while (lineToRender.empty() == false);
				// new line is current word
				line = word;
				// add white space if we have one
				if (c != '\n') line+= c;
				// empty word
				word.clear();
				// reset
				hadBreak = false;
			} else
			if (c != '\n') {
				// no flush yet, add word to line
				line+= word + c;
				// reset
				word.clear();
				hadBreak = lastChar == false;
			}
		} else {
			// regular character
			word+= c;
		}
	}

	//
	this->parentOffsetsChanged = true;
	this->widthLast = computedConstraints.width;
	this->heightLast = computedConstraints.height;
}

void GUIMultilineTextNode::setText(const MutableString& text) {
	this->text = text;
	this->parentOffsetsChanged = true;
	this->parentXOffsetLast = 0.0f;
	this->parentYOffsetLast = 0.0f;
	this->charStartIdx = 0;
	this->charEndIdx = text.size() - 1;
	this->yLast = 0.0f;
	this->widthLast = -1;
	this->heightLast = -1;
	this->startTextStyleIdx = -1;
	screenNode->invalidateLayout(this);
}

void GUIMultilineTextNode::dispose()
{
	if (font != nullptr) font->dispose();
	GUINode::dispose();
}

void GUIMultilineTextNode::render(GUIRenderer* guiRenderer)
{
	if (shouldRender() == false) return;

	//
	GUINode::render(guiRenderer);

	//
	if (font == nullptr) return;

	// screen dimensions
	auto screenWidth = screenNode->getScreenWidth();
	auto screenHeight = screenNode->getScreenHeight();

	// indents
	auto xIndentLeft = computedConstraints.left + computedConstraints.alignmentLeft + computedConstraints.contentAlignmentLeft + border.left + padding.left;
	auto yIndentTop = computedConstraints.top + computedConstraints.alignmentTop + computedConstraints.contentAlignmentTop + border.top + padding.top;

	// vertical alignment
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

	//
	string line;
	string word;
	bool hadBreak = false;
	auto parentXOffset = computeParentChildrenRenderOffsetXTotal();
	auto parentYOffset = computeParentChildrenRenderOffsetYTotal();

	// did a scrolling appear, then reset bounds to work with
	if (parentOffsetsChanged == true ||
		Math::abs(parentXOffset - parentXOffsetLast) > Math::EPSILON ||
		Math::abs(parentYOffset - parentYOffsetLast) > Math::EPSILON) {
		parentXOffsetLast = parentXOffset;
		parentYOffsetLast = parentYOffset;
		charStartIdx = 0;
		charEndIdx = text.size() - 1;
		startTextStyleIdx = -1;
		parentOffsetsChanged = false;
		yLast = 0;
	} else {
		y = yLast;
	}

	//
	auto textStyleIdx = startTextStyleIdx;
	bool visible = false;
	auto _charStartIdx = charStartIdx;
	auto _y = y;
	auto j = charStartIdx;
	for (auto i = charStartIdx; i <= charEndIdx; i++) {
		//
		auto c = text.charAt(i);
		// last char
		auto lastChar = i == charEndIdx;
		// check for separation char or last char
		if (c == '\n' || c == ' ' || c == '\t' || lastChar == true) {
			// if last char add it to current word
			if (lastChar == true) word+= c;
			// determine current line width + word width
			auto lineWidth = font->getTextWidth(MutableString(line)) + font->getTextWidth(MutableString(word));
			// check if too long
			auto tooLong =
				requestedConstraints.widthType != GUINode_RequestedConstraints_RequestedConstraintsType::AUTO && // TODO: check with <multi... width="auto" />
				lineWidth >= computedConstraints.width - (border.left + border.right + padding.left + padding.right);
			// if not auto and too long then draw current line and do a new line or flush last text
			if (tooLong == true ||
				c == '\n' ||
				lastChar == true) {

				// add word to line if required
				if ((tooLong == true && hadBreak == false) || lastChar == true || c == '\n') {
					line+= word;
					word.clear();
				}

				//
				string lineToRender = line;
				string lineLeft;

				//
				auto k = 0;

				//
				TextStyle* textStyleLast = nullptr;
				TextStyle* textStyle = nullptr;

				//
				do {
					//
					auto separationAt = font->getTextIndexXAtWidth(MutableString(lineToRender), computedConstraints.width - (border.left + border.right + padding.left + padding.right));
					lineLeft = StringTools::substring(lineToRender, separationAt + 1);
					lineToRender = StringTools::substring(lineToRender, 0, separationAt + 1);
					// determine current line width
					lineWidth = font->getTextWidth(MutableString(lineToRender));
					// horizontal alignment
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
					{
						float left = x + xIndentLeft;
						float top = y + yIndentTop;
						float width = lineWidth;
						float height = font->getLineHeight();
						if (guiRenderer->isQuadVisible(
								((left) / (screenWidth / 2.0f)) - 1.0f,
								((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
								((left + width) / (screenWidth / 2.0f)) - 1.0f,
								((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
								((left + width) / (screenWidth / 2.0f)) - 1.0f,
								((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
								((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f) == true) {

							auto styleFontColor = color;
							string textToRender;
							auto _startTextStyleIdx = textStyleIdx;
							for (auto l = 0; l < lineToRender.size(); l++) {
								TextStyle* validTextStyle = nullptr;
								if (textStyles.empty() == false) {
									// find style to start with, aligned with last line start
									if (textStyleIdx == -1) {
										textStyleIdx = 0;
										for (auto i = 0; i < textStyles.size(); i++) {
											auto textStyle = &textStyles[i];
											if (textStyle->startIdx > j) {
												textStyleIdx = i - 1;
												break;
											}
										}
										_startTextStyleIdx = textStyleIdx;
									}
									//
									textStyle = textStyleIdx < textStyles.size()?&textStyles[textStyleIdx]:nullptr;
									if (textStyle != nullptr && j + k + l >= textStyle->startIdx) {
										if (j + k + l >= textStyle->endIdx) {
											// invalid text style, check next text style
											textStyleIdx++;
											textStyle = textStyleIdx < textStyles.size()?&textStyles[textStyleIdx]:nullptr;
											if (textStyle != nullptr && j + k + l >= textStyle->startIdx) {
												if (j + k + l < textStyle->endIdx) {
													// valid text style
													validTextStyle = textStyle;
												}
											}
										} else
										if (j + k + l < textStyle->endIdx) {
											// valid text style
											validTextStyle = textStyle;
										}
									}
								}
								if (textToRender.empty() == false && textStyleLast != validTextStyle) {
									// flush/draw to screen
									font->drawString(
										guiRenderer,
										left,
										top,
										textToRender,
										0,
										0,
										textStyleLast != nullptr?textStyleLast->color:color
									);
									left+= font->getTextWidth(textToRender);
									textToRender.clear();
								}
								//
								textToRender+= lineToRender[l];
								textStyleLast = validTextStyle;
							}
							if (textToRender.empty() == false) {
								// flush/draw to screen
								font->drawString(
									guiRenderer,
									left,
									top,
									textToRender,
									0,
									0,
									textStyleLast != nullptr?textStyleLast->color:color
								);
								left+= font->getTextWidth(textToRender);
								textToRender.clear();
							}
							if (visible == false) {
								visible = true;
								charStartIdx = _charStartIdx;
								startTextStyleIdx = _startTextStyleIdx;
								yLast = _y;
							}
						} else
						if (visible == true) {
							visible = false;
							charEndIdx = i;
						}
					}
					// move y
					y+= font->getLineHeight();
					//
					k+= lineToRender.size();
					lineToRender = lineLeft;
					lineLeft.clear();
				} while (lineToRender.empty() == false);
				// new line is current word
				line = word;
				// add white space if we have one
				if (c != '\n') line+= c;
				// empty word
				word.clear();
				// reset
				hadBreak = false;
				//
				if (c == '\n') {
					_charStartIdx = i + 1;
					_y = y;
				}
				//
				j = i + 1 - line.size();
			} else
			if (c != '\n') {
				// no flush yet, add word to line
				line+= word + c;
				// reset
				word.clear();
				hadBreak = lastChar == false;
			}
		} else {
			// regular character
			word+= c;
		}
	}
}

void GUIMultilineTextNode::removeTextStyle(int startIdx, int endIdx) {
	// TODO: a.drewke
}

void GUIMultilineTextNode::addTextStyle(int startIdx, int endIdx, const GUIColor& color) {
	removeTextStyle(startIdx, endIdx);

	// TODO: a.drewke

	//
	startTextStyleIdx = -1;
	TextStyle* textStyleFirst = nullptr;
	// 0->4 6->8
	// 5
	// 2
	/*
	auto textStyleIt = textStyles.begin();
	for (auto& textStyle: textStyles) {
		if (textStyleFirst == nullptr) textStyleFirst = &textStyle;
		if (startIdx > textStyle.endIdx) {
			textStyles.insert(
				textStyleIt,
				{
					.startIdx = startIdx,
					.endIdx = endIdx,
					.color = color
				}
			);
			return;
		}
		textStyleIt++;
	}
	*/
	textStyles.insert(
		/*textStyleFirst != nullptr && startIdx < textStyleFirst->startIdx?textStyles.begin():*/textStyles.end(),
		{
			.startIdx = startIdx,
			.endIdx = endIdx,
			.color = color
		}
	);
}
