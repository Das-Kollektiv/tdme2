#include <tdme/gui/nodes/GUIStyledTextNode.h>

#include <list>
#include <string>
#include <string_view>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>
#include <tdme/gui/nodes/GUINode_AlignmentVertical.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIStyledTextNodeController.h>
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

using tdme::gui::nodes::GUIStyledTextNode;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::Engine;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNodeController;
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

GUIStyledTextNode::GUIStyledTextNode(
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

void GUIStyledTextNode::removeText(int32_t idx, int32_t count) {
	text.remove(idx, count);
	auto adaptNextStyles = false;
	for (auto i = 0; i < styles.size(); i++) {
		auto& style = styles[i];
		// adapting styles after specific style change for all succeeding styles
		if (adaptNextStyles == true) {
			style.startIdx-= count;
			style.endIdx-= count;
			if (style.startIdx < 0 && style.endIdx < 0) {
				styles.erase(styles.begin() + i);
				i--;
				continue;
			}
			if (style.startIdx < 0) style.startIdx = 0;
			if (style.endIdx < 0) style.endIdx = 0;
		} else
		// adapting styles for all succeeding styles
		if (idx < style.startIdx) {
			style.startIdx-= count;
			style.endIdx-= count;
			if (style.startIdx < 0 && style.endIdx < 0) {
				styles.erase(styles.begin() + i);
				i--;
				continue;
			}
			if (style.startIdx < 0) style.startIdx = 0;
			if (style.endIdx < 0) style.endIdx = 0;
			adaptNextStyles = true;
		} else {
			// our index >= style start and index <= style end
			if (idx <= style.endIdx) {
				// idx < end idx
				style.endIdx-= count;
				if (style.endIdx < 0) {
					styles.erase(styles.begin() + i);
					i--;
					continue;
				}
				if (style.endIdx < 0) style.endIdx = 0;
				adaptNextStyles = true;
			}
		}
	}
	charEndIdx-= count;
	startTextStyleIdx = -1;
}

void GUIStyledTextNode::insertText(int32_t idx, char c) {
	text.insert(idx, c);
	auto count = 1;
	auto adaptNextStyles = false;
	for (auto& style: styles) {
		// adapting styles after specific style change for all succeeding styles
		if (adaptNextStyles == true) {
			style.startIdx+= count;
			style.endIdx+= count;
		} else
		// adapting styles for all succeeding styles
		if (idx < style.startIdx) {
			style.startIdx+= count;
			style.endIdx+= count;
			adaptNextStyles = true;
		} else {
			// our index >= style start and index <= style end
			if (idx <= style.endIdx) {
				// idx < end idx
				style.endIdx+= count;
				adaptNextStyles = true;
			}
		}
	}
	charEndIdx+= count;
	startTextStyleIdx = -1;
}

void GUIStyledTextNode::insertText(int32_t idx, const string& s) {
	text.insert(idx, s);
	auto count = s.size();
	auto adaptNextStyles = false;
	for (auto& style: styles) {
		// adapting styles after specific style change for all succeeding styles
		if (adaptNextStyles == true) {
			style.startIdx+= count;
			style.endIdx+= count;
		} else
		// adapting styles for all succeeding styles
		if (idx < style.startIdx) {
			style.startIdx+= count;
			style.endIdx+= count;
			adaptNextStyles = true;
		} else {
			// our index >= style start and index <= style end
			if (idx <= style.endIdx) {
				// idx < end idx
				style.endIdx+= count;
				adaptNextStyles = true;
			}
		}
	}
	charEndIdx+= count;
	startTextStyleIdx = -1;
}

void GUIStyledTextNode::scrollToIndex() {
	// no font, exit
	if (font == nullptr) return;

	//
	auto styledTextController = required_dynamic_cast<GUIStyledTextNodeController*>(controller);
	auto cursorIndex = styledTextController->getIndex();
	auto yBefore = 0.0f;
	auto y = 0.0f;
	auto textStyleIdx = 0;
	for (auto i = 0; i < text.size(); ) {
		//
		determineNextLineConstraints(i, text.size(), textStyleIdx);

		//
		for (auto& lineConstraintsEntity: lineConstraints) {
			y+= lineConstraintsEntity.height;
		}

		//
		auto reachedCursorIndex = false;
		for (auto idx: lineCharIdxs) {
			if (idx == cursorIndex) {
				reachedCursorIndex = true;
				break;
			}
		}
		if (reachedCursorIndex == true) break;

		//
		line.clear();
		lineCharIdxs.clear();
		lineConstraints.clear();

		//
		yBefore = y;
	}

	//
	auto renderOffsetY = parentNode->getChildrenRenderOffsetY();

	// scroll up if required
	if (renderOffsetY > yBefore) {
		parentOffsetsChanged = true;
		parentNode->setChildrenRenderOffsetY(yBefore);
	}

	// scroll down if required
	if (renderOffsetY + parentNode->getComputedConstraints().height < y) {
		parentOffsetsChanged = true;
		parentNode->setChildrenRenderOffsetY(y - parentNode->getComputedConstraints().height);
	}
}

int GUIStyledTextNode::doPageUp() {
	//
	scrollToIndex();

	// no font, exit
	if (font == nullptr) return -1;

	//
	auto styledTextController = required_dynamic_cast<GUIStyledTextNodeController*>(controller);
	auto cursorIndex = styledTextController->getIndex();
	auto visibleHeight = parentNode->getComputedConstraints().height;
	auto y = 0.0f;
	auto textStyleIdx = 0;
	auto reachedCursorIndex = false;
	struct LineInfo {
		int idx;
		float y;
	};
	vector<LineInfo> lines;
	for (auto i = 0; i < text.size(); ) {
		//
		determineNextLineConstraints(i, text.size(), textStyleIdx);

		// did we reach our corsor index
		if (reachedCursorIndex == false) {
			for (auto idx: lineCharIdxs) {
				if (idx == cursorIndex) {
					reachedCursorIndex = true;
					break;
				}
			}
		}

		// if reached cursor index try to find index of a page down height
		for (auto& lineConstraintsEntity: lineConstraints) {
			lines.push_back(
				{
					.idx = lineCharIdxs[0],
					.y = y
				}
			);
			y+= lineConstraintsEntity.height;
		}

		//
		line.clear();
		lineCharIdxs.clear();
		lineConstraints.clear();

		//
		if (reachedCursorIndex == true) break;
	}

	// scroll down
	auto renderOffsetY = parentNode->getChildrenRenderOffsetY();
	parentOffsetsChanged = true;
	parentNode->setChildrenRenderOffsetY(renderOffsetY - visibleHeight);

	// determine cursor index
	for (int i = lines.size() - 1; i >= 0; i--) {
		auto& line = lines[i];
		if (y - line.y >= visibleHeight) {
			return line.idx;
		}
	}

	// otherwise fallback to previous value
	return cursorIndex;
}

int GUIStyledTextNode::doPageDown() {
	//
	scrollToIndex();

	// no font, exit
	if (font == nullptr) return -1;

	//
	auto styledTextController = required_dynamic_cast<GUIStyledTextNodeController*>(controller);
	auto cursorIndex = styledTextController->getIndex();
	auto visibleHeight = parentNode->getComputedConstraints().height;
	auto y = 0.0f;
	auto textStyleIdx = 0;
	auto reachedCursorIndex = false;
	auto finished = false;
	for (auto i = 0; i < text.size(); ) {
		//
		determineNextLineConstraints(i, text.size(), textStyleIdx);

		// did we reach our corsor index
		if (reachedCursorIndex == false) {
			for (auto idx: lineCharIdxs) {
				if (idx == cursorIndex) {
					reachedCursorIndex = true;
					break;
				}
			}
			// then reset Y
			if (reachedCursorIndex == true) {
				y = 0.0f;
			}
		}

		// if reached cursor index try to find index of a page down height
		if (reachedCursorIndex == true) {
			for (auto& lineConstraintsEntity: lineConstraints) {
				y+= lineConstraintsEntity.height;
				if (y >= visibleHeight) {
					cursorIndex = lineCharIdxs[0];
					finished = true;
					break;
				}
			}
		}

		//
		line.clear();
		lineCharIdxs.clear();
		lineConstraints.clear();

		//
		if (finished == true) break;
	}

	// scroll down
	auto renderOffsetY = parentNode->getChildrenRenderOffsetY();
	parentOffsetsChanged = true;
	parentNode->setChildrenRenderOffsetY(renderOffsetY + visibleHeight);

	//
	return cursorIndex;
}

const string GUIStyledTextNode::getNodeType()
{
	return "multiline-text";
}

bool GUIStyledTextNode::isContentNode()
{
	return true;
}

int GUIStyledTextNode::getContentWidth()
{
	if (requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return font != nullptr?autoWidth + border.left + border.right + padding.left + padding.right:0;
	} else {
		return computedConstraints.width;
	}
}

int GUIStyledTextNode::getContentHeight()
{	if (requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return font != nullptr?autoHeight + border.top + border.bottom + padding.top + padding.bottom:0;
	} else {
		return computedConstraints.height;
	}
}

void GUIStyledTextNode::computeContentAlignment() {
	// If fixed width requested and no computed constraints yet, abort
	if (requestedConstraints.widthType != GUINode_RequestedConstraints_RequestedConstraintsType::AUTO && computedConstraints.width == -1) return;
	// width did not change, but relayout has been requested
	if (requestedConstraints.widthType != GUINode_RequestedConstraints_RequestedConstraintsType::AUTO && widthLast == computedConstraints.width) return;
	// no font, exit
	if (font == nullptr) return;

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

void GUIStyledTextNode::setText(const MutableString& text) {
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
	unsetStyles();
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
							if (this->text.size() > styleStartIdx) setTextStyle(styleStartIdx, this->text.size() - 1, GUIColor(styleColor), styleFont, styleUrl);
						} else {
							if (this->text.size() > styleStartIdx) setTextStyle(styleStartIdx, this->text.size() - 1, styleFont, styleUrl);
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
							Console::println("GUIStyledTextNode::setText(): unknown style command: " + currentStyle);
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
							Console::println("GUIStyledTextNode::setText(): unknown style command: " + currentStyle);
						}
					} else {
						Console::println("GUIStyledTextNode::setText(): unknown style command: " + currentStyle);
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
			if (this->text.size() > styleStartIdx) setTextStyle(styleStartIdx, this->text.size() - 1, GUIColor(styleColor), styleFont, styleUrl);
		} else {
			if (this->text.size() > styleStartIdx) setTextStyle(styleStartIdx, this->text.size() - 1, styleFont, styleUrl);
		}
	}

	// add a trailing newline
	if (StringTools::endsWith(this->text.getString(), newLine) == false) this->text.append(newLine);
}

void GUIStyledTextNode::dispose()
{
	unsetStyles();
	if (font != nullptr) font->dispose();
	GUINode::dispose();
}

void GUIStyledTextNode::determineNextLineConstraints(int& i, int charEndIdx, int textStyleIdx) {
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
				line+= c;
				lineCharIdxs.push_back(k);
				break;
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
				line+= c;
				lineCharIdxs.push_back(k);
				break;
			} else
			if (line.empty() == false && c == ' ' && StringTools::endsWith(line, spaceString) == true) {
				// no op as we have a line which already has a space at the end
			} else
			if (line.empty() == true && (c == ' ' || c == '\t')) {
				// no op
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
				.idx = 0,
				.width = 0.0f,
				.height = font->getLineHeight(),
				.lineHeight = font->getLineHeight(),
				.baseLine = font->getBaseLine(),
				.spaceWrap = true
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
				.idx = -1,
				.width = 0.0f,
				.height = 0.0f,
				.lineHeight = 0.0f,
				.baseLine = 0.0f,
				.spaceWrap = false
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
							.idx = k,
							.width = lineWidth,
							.height = Math::max(lineHeight, baseLine + imageHeight),
							.lineHeight = lineHeight,
							.baseLine = baseLine,
							.spaceWrap = false
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
								.idx = -1,
								.width = 0.0f,
								.height = 0.0f,
								.lineHeight = 0.0f,
								.baseLine = 0.0f,
								.spaceWrap = false
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
							.idx = k,
							.width = lineWidth,
							.height = Math::max(lineHeight, baseLine + imageHeight),
							.lineHeight = lineHeight,
							.baseLine = baseLine,
							.spaceWrap = true
						};
						lineWidthSpaceWrap = 0.0f;
						lineHeightSpaceWrap = 0.0f;
						baseLineSpaceWrap = 0.0f;
					}
					auto character = currentFont->getCharacter(line[k] == '\t'?' ':line[k]);
					if (character != nullptr) {
						if (lineConstraints[lineConstraints.size() - 1].spaceWrap == false) {
							lineConstraints[lineConstraints.size() - 1] = {
								.idx = k,
								.width = lineWidth,
								.height = Math::max(lineHeight, baseLine + imageHeight),
								.lineHeight = lineHeight,
								.baseLine = baseLine,
								.spaceWrap = false
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
									.idx = -1,
									.width = 0.0f,
									.height = 0.0f,
									.lineHeight = 0.0f,
									.baseLine = 0.0f,
									.spaceWrap = false
								}
							);
						}
						auto charXAdvance = line[k] == '\t'?character->getXAdvance() * tabSize:character->getXAdvance();
						lineWidth+= charXAdvance;
						lineWidthSpaceWrap+= lineWidthSpaceWrap < Math::EPSILON && (line[k] == ' ' || line[k] == '\t')?0.0f:charXAdvance;
					}
				}
			}
		}

		//
		lineConstraints[lineConstraints.size() - 1] = {
			.idx = static_cast<int>(line.size()),
			.width = lineWidth,
			.height = Math::max(lineHeight, baseLine + imageHeight),
			.lineHeight = lineHeight,
			.baseLine = baseLine,
			.spaceWrap = false
		};
	}
}

void GUIStyledTextNode::render(GUIRenderer* guiRenderer)
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
	}

	// Console::println("char start idx: " + to_string(charStartIdx) + ", char end idx: " + to_string(charEndIdx) + ", chars: " + to_string(text.size()) + ", start text style idx: " + to_string(startTextStyleIdx) + ", start render y: " + to_string(startRenderY) + ", auto width: " + to_string(autoWidth) + ", auto height = " + to_string(autoHeight))

	//
	auto cursorMode = GUIStyledTextNodeController::CURSORMODE_HIDE;
	auto cursorIndex = -1;
	auto cursorSelectionIndex = -1;
	if (editMode == true) {
		auto styledTextController = required_dynamic_cast<GUIStyledTextNodeController*>(controller);
		cursorMode = styledTextController->getCursorMode();
		cursorIndex = styledTextController->getIndex();
		cursorSelectionIndex = styledTextController->getSelectionIndex();
	}

	//
	urlAreas.clear();

	//
	auto maxLineWidth = getAutoWidth();
	auto textStyleIdx = startTextStyleIdx;
	auto boundTexture = -1;
	GUIColor lastColor = color;
	string currentURL;
	string styleURL;
	int x = 0;
	for (auto i = charStartIdx; i < charEndIdx;) {

		//
		auto nextCharStartIdx = i;
		auto nextStartTextStyleIdx = textStyleIdx;
		auto nextStartRenderY = y;

		//
		determineNextLineConstraints(i, charEndIdx, textStyleIdx);

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
					"render line@" + to_string(k) + ": '" + linePart
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
					//
					charStartIdx = nextCharStartIdx;
					startTextStyleIdx = nextStartTextStyleIdx;
					startRenderY = nextStartRenderY;
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
					styleURL.clear();
					// apply text style or defaults
					if (textStyle != nullptr) {
						currentFont = textStyle->font != nullptr?textStyle->font:font;
						currentColor = textStyle->color;
						styleURL = textStyle->url;
					}
					if (textStyle != nullptr && textStyle->image != nullptr) {
						// draw
						guiRenderer->render();
						guiRenderer->bindTexture(textStyle->textureId);
						{
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
						}
						//
						if (cursorMode == GUIStyledTextNodeController::CURSORMODE_SHOW && cursorIndex == lineCharIdxs[k]) {
							float left = x + xIndentLeft;
							float top = y + yIndentTop + (lineConstraints[lineIdx].baseLine - textStyle->height) + (lineConstraints[lineIdx].height - lineConstraints[lineIdx].lineHeight);
							float width = 2;
							float height = textStyle->height;
							auto& colorData = color.getArray();
							guiRenderer->bindTexture(0);
							guiRenderer->addQuad(
								((left) / (screenWidth / 2.0f)) - 1.0f,
								((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
								colorData[0], colorData[1], colorData[2], colorData[3],
								0.0f, 1.0f,
								((left + width) / (screenWidth / 2.0f)) - 1.0f,
								((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
								colorData[0], colorData[1], colorData[2], colorData[3],
								1.0f, 1.0f,
								((left + width) / (screenWidth / 2.0f)) - 1.0f,
								((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
								colorData[0], colorData[1], colorData[2], colorData[3],
								1.0f, 0.0f,
								((left) / (screenWidth / 2.0f)) - 1.0f,
								((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
								colorData[0], colorData[1], colorData[2], colorData[3],
								0.0f, 0.0f
							);
							guiRenderer->render();
						}
						//
						guiRenderer->bindTexture(boundTexture);
						// flush current URL
						if (currentURL.empty() == false && urlAreas.empty() == false) {
							auto& urlArea = urlAreas[urlAreas.size() - 1];
							urlArea.width = x - urlArea.left;
							urlArea.height = lineConstraints[lineIdx].lineHeight;
						}
						currentURL.clear();
						// add url area if URL is given
						if (textStyle->url.empty() == false) {
							urlAreas.push_back(
								{
									.left = static_cast<int>(x),
									.top = static_cast<int>(y),
									.width = static_cast<int>(textStyle->width),
									.height = static_cast<int>(textStyle->height),
									.url = textStyle->url
								}
							);
						}
						//
						x+= textStyle->width;
					} else {
						// do line break
						if (k == lineConstraints[lineIdx].idx) {
							// flush current URL
							if (currentURL.empty() == false && urlAreas.empty() == false) {
								auto& urlArea = urlAreas[urlAreas.size() - 1];
								urlArea.width = x - urlArea.left;
								urlArea.height = lineConstraints[lineIdx].lineHeight;
							}
							//
							currentURL.clear();
							//
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
							if (line[k] == ' ' || line[k] == '\t') {
								continue;
							} else {
								skipSpaces = false;
							}
						}
						if (line[k] == '\n') {
							// draw cursor
							if (cursorMode == GUIStyledTextNodeController::CURSORMODE_SHOW && cursorIndex == lineCharIdxs[k]) {
								float left = x + xIndentLeft;
								float top = y + yIndentTop + (lineConstraints[lineIdx].baseLine - currentFont->getBaseLine()) + (lineConstraints[lineIdx].height - lineConstraints[lineIdx].lineHeight);
								float width = 2;
								float height = lineConstraints[lineIdx].lineHeight;
								auto& colorData = color.getArray();
								guiRenderer->render();
								guiRenderer->bindTexture(0);
								guiRenderer->addQuad(
									((left) / (screenWidth / 2.0f)) - 1.0f,
									((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
									colorData[0], colorData[1], colorData[2], colorData[3],
									0.0f, 1.0f,
									((left + width) / (screenWidth / 2.0f)) - 1.0f,
									((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
									colorData[0], colorData[1], colorData[2], colorData[3],
									1.0f, 1.0f,
									((left + width) / (screenWidth / 2.0f)) - 1.0f,
									((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
									colorData[0], colorData[1], colorData[2], colorData[3],
									1.0f, 0.0f,
									((left) / (screenWidth / 2.0f)) - 1.0f,
									((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
									colorData[0], colorData[1], colorData[2], colorData[3],
									0.0f, 0.0f
								);
								guiRenderer->render();
								guiRenderer->bindTexture(boundTexture);
							}
						} else {
							// otherwise draw
							auto characterCount = line[k] == '\t'?tabSize:1;
							auto character = currentFont->getCharacter(line[k] == '\t'?' ':line[k]);
							if (character != nullptr) {
								//
								auto hasSelection = false;
								if (editMode == true && cursorSelectionIndex != -1) {
									auto selectionStartIndex = Math::min(cursorIndex, cursorSelectionIndex);
									auto selectionEndIndex = Math::max(cursorIndex, cursorSelectionIndex);
									if (lineCharIdxs[k] >= selectionStartIndex && lineCharIdxs[k] < selectionEndIndex) {
										// TODO: optimize me render wise, each character with background has now 2 rendercalls, lol
										guiRenderer->render();
										boundTexture = currentFont->getTextureId();
										if (boundTexture != 0) guiRenderer->bindTexture(0);
										for (auto l = 0; l < characterCount; l++) {
											float left = x + xIndentLeft + (l * character->getXAdvance());
											float top = y + yIndentTop + (lineConstraints[lineIdx].baseLine - currentFont->getBaseLine()) + (lineConstraints[lineIdx].height - lineConstraints[lineIdx].lineHeight);
											currentFont->drawCharacterBackground(guiRenderer, character, left, top, lineConstraints[lineIdx].lineHeight, selectionBackgroundColor);
										}
										guiRenderer->render();
										if (boundTexture != 0) guiRenderer->bindTexture(boundTexture);
										hasSelection = true;
									}
								}
								// draw character
								for (auto l = 0; l < characterCount; l++) {
									float left = x + xIndentLeft + (l * character->getXAdvance());
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
									if (hasSelection == true) {
										currentFont->drawCharacter(guiRenderer, character, left, top, selectionTextColor);
									} else {
										currentFont->drawCharacter(guiRenderer, character, left, top, currentColor);
									}
								}

								// draw cursor
								if (cursorMode == GUIStyledTextNodeController::CURSORMODE_SHOW && cursorIndex == lineCharIdxs[k]) {
									float left = x + xIndentLeft;
									float top = y + yIndentTop + (lineConstraints[lineIdx].baseLine - currentFont->getBaseLine()) + (lineConstraints[lineIdx].height - lineConstraints[lineIdx].lineHeight);
									float width = 2;
									float height = lineConstraints[lineIdx].lineHeight;
									auto& colorData = color.getArray();
									guiRenderer->render();
									guiRenderer->bindTexture(0);
									guiRenderer->addQuad(
										((left) / (screenWidth / 2.0f)) - 1.0f,
										((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
										colorData[0], colorData[1], colorData[2], colorData[3],
										0.0f, 1.0f,
										((left + width) / (screenWidth / 2.0f)) - 1.0f,
										((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
										colorData[0], colorData[1], colorData[2], colorData[3],
										1.0f, 1.0f,
										((left + width) / (screenWidth / 2.0f)) - 1.0f,
										((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
										colorData[0], colorData[1], colorData[2], colorData[3],
										1.0f, 0.0f,
										((left) / (screenWidth / 2.0f)) - 1.0f,
										((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
										colorData[0], colorData[1], colorData[2], colorData[3],
										0.0f, 0.0f
									);
									guiRenderer->render();
									guiRenderer->bindTexture(boundTexture);
								}

								// if URL did change, create URL areas
								if (styleURL != currentURL) {
									if (currentURL.empty() == false && urlAreas.empty() == false) {
										auto& urlArea = urlAreas[urlAreas.size() - 1];
										urlArea.width = x - urlArea.left;
										urlArea.height = lineConstraints[lineIdx].lineHeight;
									}
									if (styleURL.empty() == false) {
										urlAreas.push_back(
											{
												.left = static_cast<int>(x),
												.top = static_cast<int>(y),
												.width = -1,
												.height = 1,
												.url = styleURL
											}
										);
									}
									currentURL = styleURL;
								}
								// advance X
								x+= line[k] == '\t'?tabSize * character->getXAdvance():character->getXAdvance();
							}
						}
					}
				}
				//
				if (lineConstraints[lineConstraints.size() - 1].idx == line.size()) {
					y+= lineConstraints[lineConstraints.size() - 1].height;
				}

				// flush current URL
				if (currentURL.empty() == false && urlAreas.empty() == false) {
					auto& urlArea = urlAreas[urlAreas.size() - 1];
					urlArea.width = x - urlArea.left;
					urlArea.height = lineConstraints[lineIdx].lineHeight;
				}
				currentURL.clear();
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

void GUIStyledTextNode::unsetStyles() {
	for (auto& style: styles) {
		if (style.font != nullptr) font->dispose();
		if (style.image != nullptr) Engine::getInstance()->getTextureManager()->removeTexture(style.image->getId());
	}
	styles.clear();
	startTextStyleIdx = -1;
}

void GUIStyledTextNode::unsetTextStyle(int startIdx, int endIdx) {
	// Console::print("GUIStyledTextNode::unsetTextStyle(): " + to_string(startIdx) + " ... " + to_string(endIdx) + ": '");
	// for (auto i = startIdx; i <= endIdx; i++) Console::print(string() + text.charAt(i));
	// Console::println("'");
	// for (auto& style: styles) Console::println("pre: " + to_string(style.startIdx) + " ... " + to_string(style.endIdx));
	for (auto i = 0; i < styles.size(); i++) {
		auto& style = styles[i];
		if (startIdx >= style.startIdx && endIdx <= style.endIdx) {
			auto styleNext = style;
			style.endIdx = startIdx - 1;
			styleNext.startIdx = endIdx + 1;
			styles.insert(styles.begin() + i + 1, styleNext);
		} else {
			if (startIdx >= style.startIdx && startIdx <= style.endIdx) {
				style.endIdx = startIdx - 1;
			}
			if (endIdx >= style.startIdx && endIdx <= style.endIdx) {
				style.startIdx = endIdx - 1;
			}
		}
		if (style.startIdx > style.endIdx ||
			(startIdx < style.startIdx && endIdx > style.endIdx)) {
			styles.erase(styles.begin() + i);
			i--;
		}
	}
	// for (auto& style: styles) Console::println("post: " + to_string(style.startIdx) + " ... " + to_string(style.endIdx));
}

void GUIStyledTextNode::setTextStyle(int startIdx, int endIdx, const GUIColor& color, const string& font, const string& url) {
	// Console::print("GUIStyledTextNode::setTextStyle(): " + to_string(startIdx) + " ... " + to_string(endIdx) + ": '");
	// for (auto i = startIdx; i <= endIdx; i++) Console::print(string() + text.charAt(i));
	// Console::print("'");
	// Console::print(", color = " + to_string(color.getRed()) + ", " + to_string(color.getGreen()) + ", " + to_string(color.getBlue()) + ", " + to_string(color.getAlpha()));
	// Console::print(", url = '" + url + "'");
	// Console::println();
	unsetTextStyle(startIdx, endIdx);
	// TODO: a.drewke
	auto _font = font.empty() == true?nullptr:GUI::getFont(screenNode->getApplicationRootPathName(), font);;
	if (_font != nullptr) _font->initialize();
	// find position to insert
	auto j = -1;
	for (auto i = 0; i < styles.size(); i++) {
		auto& style = styles[i];
		if (startIdx > style.endIdx) {
			j = i + 1;
		}
	}
	// Console::println("insert@" + to_string(j));
	if (j == -1) j = 0;
	// for (auto& style: styles) Console::println("pre: " + to_string(style.startIdx) + " ... " + to_string(style.endIdx));
	// insert
	styles.insert(
		styles.begin() + j,
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
	//
	startTextStyleIdx = -1;
	// for (auto& style: styles) Console::println("post: " + to_string(style.startIdx) + " ... " + to_string(style.endIdx));
}

void GUIStyledTextNode::setTextStyle(int startIdx, int endIdx, const string& font, const string& url) {
	// Console::print("GUIStyledTextNode::setTextStyle(): " + to_string(startIdx) + " ... " + to_string(endIdx) + ": '");
	// for (auto i = startIdx; i <= endIdx; i++) Console::print(string() + text.charAt(i));
	// Console::print("'");
	// Console::print(", url = '" + url + "'");
	// Console::println();
	unsetTextStyle(startIdx, endIdx);
	// TODO: a.drewke
	auto _font = font.empty() == true?nullptr:GUI::getFont(screenNode->getApplicationRootPathName(), font);;
	if (_font != nullptr) _font->initialize();
	// find position to insert
	auto j = -1;
	for (auto i = 0; i < styles.size(); i++) {
		auto& style = styles[i];
		if (startIdx > style.endIdx) {
			j = i + 1;
		}
	}
	// for (auto& style: styles) Console::println("pre: " + to_string(style.startIdx) + " ... " + to_string(style.endIdx));
	// Console::println("insert@" + to_string(j));
	if (j == -1) j = 0;
	// insert
	styles.insert(
		styles.begin() + j,
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
	//
	startTextStyleIdx = -1;
	// for (auto& style: styles) Console::println("post: " + to_string(style.startIdx) + " ... " + to_string(style.endIdx));
}

void GUIStyledTextNode::setImage(int idx, const string& image, const string& url, int width, int height) {
	// Console::println("GUIStyledTextNode::setImage(): " + to_string(idx) + ": " + image + ", url = '" + url + "', width = " + to_string(width) + ", height = " + to_string(height));
	unsetTextStyle(idx,idx);
	// TODO: a.drewke
	auto _image = image.empty() == true?nullptr:GUI::getImage(screenNode->getApplicationRootPathName(), image);
	// find position to insert
	auto j = -1;
	for (auto i = 0; i < styles.size(); i++) {
		auto& style = styles[i];
		if (idx > style.endIdx) {
			j = i + 1;
		}
	}
	// for (auto& style: styles) Console::println("pre: " + to_string(style.startIdx) + " ... " + to_string(style.endIdx));
	// Console::println("insert@" + to_string(j));
	if (j == -1) j = 0;
	// insert
	styles.insert(
		styles.begin() + j,
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
	//
	startTextStyleIdx = -1;
	// for (auto& style: styles) Console::println("post: " + to_string(style.startIdx) + " ... " + to_string(style.endIdx));
}
