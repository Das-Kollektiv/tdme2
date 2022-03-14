#include <tdme/gui/nodes/GUIMultilineTextNode.h>

#include <list>
#include <string>
#include <string_view>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>
#include <tdme/gui/nodes/GUINode_AlignmentVertical.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUICharacter.h>
#include <tdme/gui/renderer/GUIFont.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::list;
using std::string;
using std::string_view;
using std::to_string;

using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUICharacter;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::GUI;
using tdme::math::Math;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
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
	bool preformatted,
	const string& font,
	const string& color,
	const MutableString& text
):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn)
{
	this->font = font.empty() == true?nullptr:GUI::getFont(screenNode->getApplicationRootPathName(), font);
	this->color = color.empty() == true || color.length() == 0?GUIColor():GUIColor(color);
	this->autoWidth = 0;
	this->autoHeight = 0;
	this->parentOffsetsChanged = true;
	this->parentXOffsetLast = 0.0f;
	this->parentYOffsetLast = 0.0f;
	this->startRenderY = 0;
	this->charStartIdx = 0;
	this->charEndIdx = text.size() - 1;
	this->widthLast = -1;
	this->heightLast = -1;
	this->startTextStyleIdx = -1;
	this->preformatted = preformatted;
	if (this->font != nullptr) this->font->initialize();
	setText(text);
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
	auto maxLineWidth = getAutoWidth();

	//
	autoWidth = 0;
	autoHeight = 0;

	//
	auto textStyleIdx = 0;
	for (auto i = 0; i < text.size(); ) {
		//
		determineNextLineConstraints(i, text.size(), textStyleIdx);

		/*
		{
			auto l = 0;
			for (auto k = 0; k < lineConstraints.size(); k++) {
				string linePart;
				for (auto j = l; j < lineConstraints[k].idx; j++) {
					if (line[j] == 0) {
						linePart += "[image]";
					} else {
						linePart += line[j];
					}
				}
				Console::println(
					"auto line@" + to_string(k) + ": '" + line + "': '" + linePart
							+ "': " + to_string(lineConstraints[k].idx) + "; width = "
							+ to_string(lineConstraints[k].width) + " / "
							+ to_string(maxLineWidth) + ", line height = "
							+ to_string(lineConstraints[k].lineHeight) + ", height "
							+ to_string(lineConstraints[k].height) + ", base line: "
							+ to_string(lineConstraints[k].baseLine) + ": Y = " + to_string(autoHeight));
				l = lineConstraints[k].idx;
			}
		}
		*/

		//
		for (auto& lineConstraintsEntity: lineConstraints) {
			if (lineConstraintsEntity.width > autoWidth) autoWidth = lineConstraintsEntity.width;
			autoHeight+= lineConstraintsEntity.height;
		}

		//
		line.clear();
		lineCharIdxs.clear();
		lineConstraints.clear();
	}

	//
	this->parentOffsetsChanged = true;
	this->widthLast = computedConstraints.width;
	this->heightLast = computedConstraints.height;
}

void GUIMultilineTextNode::setText(const MutableString& text) {
	this->parentOffsetsChanged = true;
	this->parentXOffsetLast = 0.0f;
	this->parentYOffsetLast = 0.0f;
	this->charStartIdx = 0;
	this->charEndIdx = text.size() - 1;
	this->startRenderY = 0;
	this->widthLast = -1;
	this->heightLast = -1;
	this->startTextStyleIdx = -1;
	screenNode->invalidateLayout(this);
	disposeStyles();
	this->text.reset();
	/*
	// Currently supported BBCode like tags
	[font=schriftart]Text[/font]
	[color=farbe]farbiger Text[/color]
	[url=http://example.com/]Linktext[/url]
	[image]example.com/bild.jpg[/image] (Bearbeitet)
	*/
	string styleFont;
	string styleColor;
	string styleUrl;
	string styleImage;
	//
	auto parseStyle = false;
	auto parseImage = false;
	string currentStyle;
	int styleStartIdx = -1;
	char lc = 0;
	for (auto i = 0; i < text.size(); i++) {
		auto c = text.charAt(i);
		if (parseStyle == true) {
			// end of style
			if (c == ']') {
				if (lc != '\\') {
					auto styleTokenized = StringTools::tokenize(currentStyle, "=");
					// apply style until current text size
					if (styleStartIdx != -1 &&
						(styleFont.empty() == false ||
						styleColor.empty() == false ||
						styleUrl.empty() == false)) {
						if (styleColor.empty() == false) {
							setTextStyle(styleStartIdx, this->text.size() - 1, GUIColor(styleColor), styleFont, styleUrl);
						} else {
							setTextStyle(styleStartIdx, this->text.size() - 1, styleFont, styleUrl);
						}
					}
					if (styleTokenized.size() == 2) {
						auto command = StringTools::toLowerCase(StringTools::trim(styleTokenized[0]));
						auto argument = StringTools::trim(styleTokenized[1]);
						if (command == "font") {
							styleFont = argument;
							styleStartIdx = this->text.size();
						} else
						if (command == "color") {
							styleColor = argument;
							styleStartIdx = this->text.size();
						} else
						if (command == "url") {
							styleUrl = argument;
							styleStartIdx = this->text.size();
						} else {
							Console::println("GUIMultilineTextNode::setText(): unknown style command: " + currentStyle);
						}
					} else
					if (styleTokenized.size() == 1) {
						auto command = StringTools::toLowerCase(StringTools::trim(styleTokenized[0]));
						if (command == "/font") {
							styleFont.clear();
						} else
						if (command == "/color") {
							styleColor.clear();
						} else
						if (command == "/url") {
							styleUrl.clear();
						} else
						if (command == "image") {
							parseImage = true;
						} else
						if (command == "/image") {
							parseImage = false;
							this->text.append(static_cast<char>(0));
							setImage(this->text.size() - 1, styleImage, styleUrl, -1, -1);
							styleImage.clear();
						} else {
							Console::println("GUIMultilineTextNode::setText(): unknown style command: " + currentStyle);
						}
					} else {
						Console::println("GUIMultilineTextNode::setText(): unknown style command: " + currentStyle);
					}
					//
					currentStyle.clear();
					parseStyle = false;
					if (styleFont.empty() == false ||
						styleColor.empty() == false ||
						styleUrl.empty() == false) {
						styleStartIdx = this->text.size();
					}
				} else {
					this->text.remove(this->text.size() - 1, 1);
					currentStyle+= c;
				}
			} else {
				// style command
				currentStyle+= c;
			}
		} else
		// start of style
		if (c == '[') {
			if (lc != '\\') {
				parseStyle = true;
			} else {
				this->text.remove(this->text.size() - 1, 1);
				this->text.append(c);
			}
		} else {
			if (c == ']' && lc == '\\') {
				this->text.remove(this->text.size() - 1, 1);
			}
			if (parseImage == true) {
				// image
				styleImage+= c;
			} else {
				// ordinary text
				this->text.append(c);
			}
		}
		//
		lc = c;
	}
	// apply style until current text size
	if (styleStartIdx != -1 &&
		(styleFont.empty() == false ||
		styleColor.empty() == false ||
		styleUrl.empty() == false)) {
		if (styleColor.empty() == false) {
			setTextStyle(styleStartIdx, this->text.size() - 1, GUIColor(styleColor), styleFont, styleUrl);
		} else {
			setTextStyle(styleStartIdx, this->text.size() - 1, styleFont, styleUrl);
		}
	}
	//
}

void GUIMultilineTextNode::dispose()
{
	disposeStyles();
	if (font != nullptr) font->dispose();
	GUINode::dispose();
}

void GUIMultilineTextNode::determineNextLineConstraints(int& i, int charEndIdx, int textStyleIdx) {
	//
	auto maxLineWidth = requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO?Float::MAX_VALUE:computedConstraints.width - (border.left + border.right + padding.left + padding.right);

	// determine line to render
	if (preformatted == true) {
		line.clear();
		lineCharIdxs.clear();
		auto k = i;
		for (; k < charEndIdx; k++) {
			auto c = text.charAt(k);
			// line finished?
			if (c == '\n') {
				break;
			} else
			if (c == '\t') {
				// extend tab to 4 spaces if line is not empty
				line+= tabString3;
				lineCharIdxs.push_back(k);
				lineCharIdxs.push_back(k);
				lineCharIdxs.push_back(k);
				lineCharIdxs.push_back(k);
			} else {
				line+= c;
				lineCharIdxs.push_back(k);
			}
		}
		i = k + 1;
	} else {
		line.clear();
		lineCharIdxs.clear();
		auto k = i;
		for (; k < charEndIdx; k++) {
			auto c = text.charAt(k);
			// line finished?
			if (c == '\n') {
				break;
			} else
			if (line.empty() == false && c == ' ' && StringTools::endsWith(line, spaceString) == true) {
				// no op as we have a line which already has a space at the end
			} else
			if (line.empty() == true && (c == ' ' || c == '\t')) {
				// no op
			} else
			if (c == '\t') {
				// extend tab to 4 spaces if line is not empty
				if (line.empty() == false) {
					if (StringTools::endsWith(line, spaceString) == true) {
						line+= tabString3;
					} else {
						line+= tabString4;
					}
					lineCharIdxs.push_back(k);
					lineCharIdxs.push_back(k);
					lineCharIdxs.push_back(k);
					lineCharIdxs.push_back(k);
				}
			} else {
				line+= c;
				lineCharIdxs.push_back(k);
			}
		}
		i = k + 1;
	}
	// remove trailing space
	while (StringTools::endsWith(line, spaceString) == true) line.erase(line.begin() + line.size() - 1);

	if (line.empty() == true) {
		//
		lineConstraints.push_back(
			{
				idx: 0,
				width: 0.0f,
				height: font->getLineHeight(),
				lineHeight: font->getLineHeight(),
				baseLine: font->getBaseLine(),
				spaceWrap: true
			}
		);
	} else {
		// determine baseline and part of line to render
		auto baseLine = 0.0f;
		auto lineHeight = 0.0f;
		auto lineWidth = 0.0f;
		auto lineWidthSpaceWrap = 0.0f;
		auto lineHeightSpaceWrap = 0.0f;
		auto baseLineSpaceWrap = 0.0f;
		auto imageHeight = 0.0f;

		//
		lineConstraints.clear();
		lineConstraints.push_back(
			{
				idx: -1,
				width: 0.0f,
				height: 0.0f,
				lineHeight: 0.0f,
				baseLine: 0.0f,
				spaceWrap: false
			}
		);
		{
			auto currentTextStyleIdx = textStyleIdx;
			for (auto k = 0; k < line.size(); k++) {
				auto textStyle = getTextStyle(lineCharIdxs, k, currentTextStyleIdx);
				auto currentFont = textStyle != nullptr && textStyle->font != nullptr?textStyle->font:font;
				baseLine = Math::max(baseLine, currentFont->getBaseLine());
				baseLineSpaceWrap = Math::max(baseLineSpaceWrap, currentFont->getBaseLine());
				lineHeight = Math::max(lineHeight, currentFont->getLineHeight());
				lineHeightSpaceWrap = Math::max(lineHeightSpaceWrap, currentFont->getLineHeight());
				// render a image
				if (textStyle != nullptr && textStyle->image != nullptr) {
					if (lineConstraints[lineConstraints.size() - 1].spaceWrap == false) {
						lineConstraints[lineConstraints.size() - 1] = {
							idx: k,
							width: lineWidth,
							height: Math::max(lineHeight, baseLine + imageHeight),
							lineHeight: lineHeight,
							baseLine: baseLine,
							spaceWrap: false
						};
						lineWidthSpaceWrap = 0.0f;
						lineHeightSpaceWrap = 0.0f;
						baseLineSpaceWrap = 0.0f;
					}
					if (lineWidth > maxLineWidth) {
						imageHeight = 0.0f;
						lineWidth = lineWidthSpaceWrap;
						lineHeight = lineHeightSpaceWrap;
						baseLine = baseLineSpaceWrap;
						lineConstraints.push_back(
							{
								idx: -1,
								width: 0.0f,
								height: 0.0f,
								lineHeight: 0.0f,
								baseLine: 0.0f,
								spaceWrap: false
							}
						);
					}
					lineWidth+= textStyle->width;
					lineWidthSpaceWrap+= textStyle->width;
					imageHeight = Math::max(imageHeight, static_cast<float>(textStyle->height));
				} else {
					// render text
					if (line[k] == ' ') {
						lineConstraints[lineConstraints.size() - 1] = {
							idx: k,
							width: lineWidth,
							height: Math::max(lineHeight, baseLine + imageHeight),
							lineHeight: lineHeight,
							baseLine: baseLine,
							spaceWrap: true
						};
						lineWidthSpaceWrap = 0.0f;
						lineHeightSpaceWrap = 0.0f;
						baseLineSpaceWrap = 0.0f;
					}
					auto character = currentFont->getCharacter(line[k]);
					if (character != nullptr) {
						if (lineConstraints[lineConstraints.size() - 1].spaceWrap == false) {
							lineConstraints[lineConstraints.size() - 1] = {
								idx: k,
								width: lineWidth,
								height: Math::max(lineHeight, baseLine + imageHeight),
								lineHeight: lineHeight,
								baseLine: baseLine,
								spaceWrap: false
							};
							lineWidthSpaceWrap = 0.0f;
							lineHeightSpaceWrap = 0.0f;
							baseLineSpaceWrap = 0.0f;
						}
						if (lineWidth > maxLineWidth) {
							lineWidth = lineWidthSpaceWrap;
							if (k != line.size() - 1) {
								imageHeight = 0.0f;
								lineHeight = lineHeightSpaceWrap;
								baseLine = baseLineSpaceWrap;
							}
							lineConstraints.push_back(
								{
									idx: -1,
									width: 0.0f,
									height: 0.0f,
									lineHeight: 0.0f,
									baseLine: 0.0f,
									spaceWrap: false
								}
							);
						}
						lineWidth+= character->getXAdvance();
						lineWidthSpaceWrap+= lineWidthSpaceWrap < Math::EPSILON && line[k] == ' '?0.0f:character->getXAdvance();
					}
				}
			}
		}

		//
		lineConstraints[lineConstraints.size() - 1] = {
			idx: static_cast<int>(line.size()),
			width: lineWidth,
			height: Math::max(lineHeight, baseLine + imageHeight),
			lineHeight: lineHeight,
			baseLine: baseLine,
			spaceWrap: false
		};
	}
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
	auto parentXOffset = computeParentChildrenRenderOffsetXTotal();
	auto parentYOffset = computeParentChildrenRenderOffsetYTotal();
	bool visible = false;

	// did a scrolling appear, then reset bounds to work with
	if (parentOffsetsChanged == true ||
		Math::abs(parentXOffset - parentXOffsetLast) > Math::EPSILON ||
		Math::abs(parentYOffset - parentYOffsetLast) > Math::EPSILON) {
		parentXOffsetLast = parentXOffset;
		parentYOffsetLast = parentYOffset;
		charStartIdx = 0;
		charEndIdx = text.size();
		startTextStyleIdx = -1;
		parentOffsetsChanged = false;
		startRenderY = 0;
	} else {
		y = startRenderY;
		visible = true;
	}

	// Console::println("char start idx: " + to_string(charStartIdx) + ", char end idx: " + to_string(charEndIdx) + ", chars: " + to_string(text.size()) + ", start text style idx: " + to_string(startTextStyleIdx) + ", start render y: " + to_string(startRenderY) + ", auto width: " + to_string(autoWidth) + ", auto height = " + to_string(autoHeight))

	//
	auto maxLineWidth = getAutoWidth();
	auto textStyleIdx = startTextStyleIdx;
	auto currentCharStartIdx = charStartIdx;
	auto j = charStartIdx;
	auto boundTexture = -1;
	GUIColor lastColor = color;
	for (auto i = charStartIdx; i < charEndIdx;) {
		//
		currentCharStartIdx = i;
		determineNextLineConstraints(i, charEndIdx, textStyleIdx);

		// empty lines are cheap, handle them immediatly
		if (line.empty() == true) {
			for (auto& lineConstraint: lineConstraints) {
				y+= lineConstraint.height;
			}
			//
			line.clear();
			lineCharIdxs.clear();
			lineConstraints.clear();
			//
			continue;
		}

		//
		/*
		{
			auto l = 0;
			for (auto k = 0; k < lineConstraints.size(); k++) {
				string linePart;
				for (auto j = l; j < lineConstraints[k].idx; j++) {
					if (line[j] == 0) {
						linePart += "[image]";
					} else {
						linePart += line[j];
					}
				}
			Console::println(
					"render line@" + to_string(k) + ": '" + line + "': '" + linePart
							+ "': " + to_string(lineConstraints[k].idx) + "; width = "
							+ to_string(lineConstraints[k].width) + " / "
							+ to_string(maxLineWidth) + ", line height = "
							+ to_string(lineConstraints[k].lineHeight) + ", height "
							+ to_string(lineConstraints[k].height) + ", base line: "
							+ to_string(lineConstraints[k].baseLine) + ": Y = " + to_string(y));
				l = lineConstraints[k].idx;
			}
		}
		*/

		// render
		auto lineIdx = 0;
		{
			//
			auto skipSpaces = false;
			auto& currentTextStyleIdx = textStyleIdx;
			auto x = 0;
			// determine visibility of (sub) lines
			for (lineIdx = 0; lineIdx < lineConstraints.size(); lineIdx++) {
				// x alignment
				if (alignments.horizontal == GUINode_AlignmentHorizontal::LEFT) {
					x = 0;
				} else
				if (alignments.horizontal == GUINode_AlignmentHorizontal::CENTER) {
					x = (maxLineWidth - lineConstraints[lineIdx].width) / 2;
				} else
				if (alignments.horizontal == GUINode_AlignmentHorizontal::RIGHT) {
					x = maxLineWidth - lineConstraints[lineIdx].width;
				}
				//
				float left = x + xIndentLeft;
				float top = y + yIndentTop;
				float width = lineConstraints[lineIdx].width;
				float height = lineConstraints[lineIdx].height;
				if (guiRenderer->isQuadVisible(
						((left) / (screenWidth / 2.0f)) - 1.0f,
						((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
						((left + width) / (screenWidth / 2.0f)) - 1.0f,
						((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
						((left + width) / (screenWidth / 2.0f)) - 1.0f,
						((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
						((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f) == true) {
					// break if visible
					break;
				}
				// increment y by line height
				y+= lineConstraints[lineIdx].height;
				// iterate text style
				for (auto k = lineIdx == 0?0:lineConstraints[lineIdx - 1].idx; k < lineConstraints[lineIdx].idx; k++)
					getTextStyle(lineCharIdxs, k, currentTextStyleIdx);
			}
			// render
			if (lineIdx == lineConstraints.size()) {
				// was visible, then store text render end values
				if (visible == true) {
					visible = false;
					charEndIdx = lineCharIdxs[0];
					break;
				}
			} else {
				// if text was not visible before store text render start values
				if (visible == false) {
					visible = true;
					charStartIdx = lineCharIdxs[lineIdx == 0?0:lineConstraints[lineIdx - 1].idx];
					startTextStyleIdx = currentTextStyleIdx;
					startRenderY = y;
				}
				// x alignment
				if (alignments.horizontal == GUINode_AlignmentHorizontal::LEFT) {
					// no op
					x = 0;
				} else
				if (alignments.horizontal == GUINode_AlignmentHorizontal::CENTER) {
					x = (maxLineWidth - lineConstraints[lineIdx].width) / 2;
				} else
				if (alignments.horizontal == GUINode_AlignmentHorizontal::RIGHT) {
					x = maxLineWidth - lineConstraints[lineIdx].width;
				}
				// render
				for (auto k = lineIdx == 0?0:lineConstraints[lineIdx - 1].idx; k < line.size(); k++) {
					auto textStyle = getTextStyle(lineCharIdxs, k, currentTextStyleIdx);
					Color4 currentColor = color;
					GUIFont* currentFont = font;
					// apply text style or defaults
					if (textStyle != nullptr) {
						currentFont = textStyle->font != nullptr?textStyle->font:font;
						currentColor = textStyle->color;
					}
					if (textStyle != nullptr && textStyle->image != nullptr) {
						guiRenderer->render();
						guiRenderer->bindTexture(textStyle->textureId);
						float left = x + xIndentLeft;
						float top = y + yIndentTop + (lineConstraints[lineIdx].baseLine - textStyle->height) + (lineConstraints[lineIdx].height - lineConstraints[lineIdx].lineHeight);
						float width = textStyle->width;
						float height = textStyle->height;
						guiRenderer->addQuad(
							((left) / (screenWidth / 2.0f)) - 1.0f,
							((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
							1.0f, 1.0f, 1.0f, 1.0f,
							0.0f,
							0.0f,
							((left + width) / (screenWidth / 2.0f)) - 1.0f,
							((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
							1.0f, 1.0f, 1.0f, 1.0f,
							1.0f,
							0.0f,
							((left + width) / (screenWidth / 2.0f)) - 1.0f,
							((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
							1.0f, 1.0f, 1.0f, 1.0f,
							1.0f,
							1.0f,
							((left) / (screenWidth / 2.0f)) - 1.0f,
							((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
							1.0f, 1.0f, 1.0f, 1.0f,
							0.0f,
							1.0f
						);
						guiRenderer->render();
						guiRenderer->bindTexture(boundTexture);
						x+= textStyle->width;
					} else {
						// do line break
						if (k == lineConstraints[lineIdx].idx) {
							y+= lineConstraints[lineIdx].height;
							lineIdx++;
							if (lineIdx == lineConstraints.size()) break;
							//
							x = 0;
							if (alignments.horizontal == GUINode_AlignmentHorizontal::LEFT) {
								// no op
							} else
							if (alignments.horizontal == GUINode_AlignmentHorizontal::CENTER) {
								x = (maxLineWidth - lineConstraints[lineIdx].width) / 2;
							} else
							if (alignments.horizontal == GUINode_AlignmentHorizontal::RIGHT) {
								x = maxLineWidth - lineConstraints[lineIdx].width;
							}
							if (lineConstraints[lineIdx - 1].spaceWrap == true) {
								skipSpaces = true;
							}
							//
							{
								float left = x + xIndentLeft;
								float top = y + yIndentTop;
								float width = lineConstraints[lineIdx].width;
								float height = lineConstraints[lineIdx].height;
								if (guiRenderer->isQuadVisible(
										((left) / (screenWidth / 2.0f)) - 1.0f,
										((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
										((left + width) / (screenWidth / 2.0f)) - 1.0f,
										((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
										((left + width) / (screenWidth / 2.0f)) - 1.0f,
										((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
										((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f) == false) {
									//
									if (visible == true) {
										visible = false;
										charEndIdx = lineCharIdxs[lineIdx == 0?0:lineConstraints[lineIdx - 1].idx];
										break;
									}
								}
							}
						}
						// skip spaces if requested
						if (skipSpaces == true) {
							if (line[k] == ' ') {
								continue;
							} else {
								skipSpaces = false;
							}
						}
						// otherwise draw
						auto character = currentFont->getCharacter(line[k]);
						if (character != nullptr) {
							float left = x + xIndentLeft;
							float top = y + yIndentTop + (lineConstraints[lineIdx].baseLine - currentFont->getBaseLine()) + (lineConstraints[lineIdx].height - lineConstraints[lineIdx].lineHeight);
							if (boundTexture == -1) {
								boundTexture = currentFont->getTextureId();
								guiRenderer->bindTexture(boundTexture);
								lastColor = currentColor;
							} else
							if (boundTexture != currentFont->getTextureId()) {
								boundTexture = currentFont->getTextureId();
								guiRenderer->render();
								guiRenderer->bindTexture(boundTexture);
								lastColor = currentColor;
							} else
							if (currentColor.equals(lastColor) == false) {
								guiRenderer->render();
								lastColor = currentColor;
							}
							currentFont->drawCharacter(guiRenderer, character, left, top, currentColor);
							x+= character->getXAdvance();
						}
					}
				}
				//
				if (lineConstraints[lineConstraints.size() - 1].idx == line.size()) {
					y+= lineConstraints[lineConstraints.size() - 1].height;
				}
			}
		}

		//
		guiRenderer->render();

		//
		line.clear();
		lineCharIdxs.clear();
		lineConstraints.clear();
	}

	//
	// Console::println("y: " + to_string(y) + " / " + to_string(autoHeight));

	//
	guiRenderer->bindTexture(0);
}

void GUIMultilineTextNode::unsetTextStyle(int startIdx, int endIdx) {
	// TODO: a.drewke
}

void GUIMultilineTextNode::setTextStyle(int startIdx, int endIdx, const GUIColor& color, const string& font, const string& url) {
	Console::print("GUIMultilineTextNode::setTextStyle(): " + to_string(startIdx) + " ... " + to_string(endIdx) + ": '");
	for (auto i = startIdx; i <= endIdx; i++) Console::print(string() + text.charAt(i));
	Console::print("'");
	Console::print(", color = " + to_string(color.getRed()) + ", " + to_string(color.getGreen()) + ", " + to_string(color.getBlue()) + ", " + to_string(color.getAlpha()));
	Console::print(", url = '" + url + "'");
	Console::println();
	unsetTextStyle(startIdx, endIdx);
	// TODO: a.drewke
	auto _font = font.empty() == true?nullptr:GUI::getFont(screenNode->getApplicationRootPathName(), font);;
	if (_font != nullptr) _font->initialize();
	styles.insert(
		styles.end(),
		{
			.startIdx = startIdx,
			.endIdx = endIdx,
			.color = color,
			.font = _font,
			.url = url,
			.image = nullptr,
			.textureId = -1,
			.width = -1,
			.height = -1
		}
	);
}

void GUIMultilineTextNode::setTextStyle(int startIdx, int endIdx, const string& font, const string& url) {
	Console::print("GUIMultilineTextNode::setTextStyle(): " + to_string(startIdx) + " ... " + to_string(endIdx) + ": '");
	for (auto i = startIdx; i <= endIdx; i++) Console::print(string() + text.charAt(i));
	Console::print("'");
	Console::print(", url = '" + url + "'");
	Console::println();
	unsetTextStyle(startIdx, endIdx);
	// TODO: a.drewke
	auto _font = font.empty() == true?nullptr:GUI::getFont(screenNode->getApplicationRootPathName(), font);;
	if (_font != nullptr) _font->initialize();
	styles.insert(
		styles.end(),
		{
			.startIdx = startIdx,
			.endIdx = endIdx,
			.color = color,
			.font = _font,
			.url = url,
			.image = nullptr,
			.textureId = -1,
			.width = -1,
			.height = -1
		}
	);
}

void GUIMultilineTextNode::setImage(int idx, const string& image, const string& url, int width, int height) {
	Console::println("GUIMultilineTextNode::setImage(): " + to_string(idx) + ": " + image + ", url = '" + url + "', width = " + to_string(width) + ", height = " + to_string(height));
	unsetTextStyle(idx,idx);
	// TODO: a.drewke
	auto _image = image.empty() == true?nullptr:GUI::getImage(screenNode->getApplicationRootPathName(), image);
	styles.insert(
		styles.end(),
		{
			.startIdx = idx,
			.endIdx = idx,
			.color = color,
			.font = nullptr,
			.url = url,
			.image = _image,
			.textureId = Engine::getInstance()->getTextureManager()->addTexture(_image, 0),
			.width = width == -1?_image->getWidth():width,
			.height = height == -1?_image->getHeight():height,
		}
	);
}

void GUIMultilineTextNode::disposeStyles() {
	for (auto& style: styles) {
		if (style.font != nullptr) font->dispose();
		if (style.image != nullptr) Engine::getInstance()->getTextureManager()->removeTexture(style.image->getId());
	}
	styles.clear();
}
