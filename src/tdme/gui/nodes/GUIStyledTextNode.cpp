#include <tdme/gui/nodes/GUIStyledTextNode.h>

#include <list>
#include <string>
#include <string_view>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
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
#include <tdme/gui/GUIParser.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/UTF8CharacterIterator.h>

using std::list;
using std::string;
using std::string_view;
using std::to_string;

using tdme::gui::nodes::GUIStyledTextNode;

using tdme::engine::Texture;
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
using tdme::gui::GUIParser;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::MutableString;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;
using tdme::utilities::UTF8CharacterIterator;

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
	const string& tooltip,
	bool editable,
	bool preformatted,
	const string& font,
	int size,
	const string& color,
	const MutableString& text
):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn, tooltip)
{
	this->font = font.empty() == true?nullptr:screenNode->getFont(font, size);
	this->size = size;
	this->color = color.empty() == true || color.length() == 0?GUIColor():GUIColor(color);
	this->autoWidth = 0;
	this->autoHeight = 0;
	this->parentOffsetsChanged = true;
	this->parentXOffsetLast = 0.0f;
	this->parentYOffsetLast = 0.0f;
	this->startRenderY = 0;
	this->charStartIdx = 0;
	this->charEndIdx = text.size();
	this->widthLast = -1;
	this->heightLast = -1;
	this->startTextStyleIdx = -1;
	this->editable = editable;
	this->preformatted = preformatted;
	this->selectionBackgroundColor = GUIColor(GUIParser::getEngineThemeProperties()->get("color.focus", "#ff0000"));
	if (this->font != nullptr) this->font->initialize();
	setText(text);
}

void GUIStyledTextNode::unsetIndexMousePosition() {
	indexMousePositionX = MOUSEPOSITION_NONE;
	indexMousePositionY = MOUSEPOSITION_NONE;
}

void GUIStyledTextNode::setIndexMousePosition(int x, int y) {
	indexMousePositionX = x;
	indexMousePositionY = y;
}

void GUIStyledTextNode::unsetSelectionIndexMousePosition() {
	selectionIndexMousePositionX = MOUSEPOSITION_NONE;
	selectionIndexMousePositionY = MOUSEPOSITION_NONE;
}

void GUIStyledTextNode::setSelectionIndexMousePosition(int x, int y) {
	selectionIndexMousePositionX = x;
	selectionIndexMousePositionY = y;
}

void GUIStyledTextNode::removeText(int32_t idx, int32_t count) {
	// TODO: we have new node dimension after remove
	text.remove(idx, count, &count);
	idx = text.getUtf8BinaryIndex(idx);
	// Haha: This was answered by OpenGPT
	auto start = idx;
	auto end = idx + count + 1;
	for (auto it = styles.begin(); it != styles.end();) {
		// check if the current range overlaps with the range to be removed
		if (it->startIdx < end && it->endIdx > start) {
			// split the overlapping range into two non-overlapping ranges
			if (it->startIdx < start) {
				auto style = *it;
				style.startIdx = it->startIdx;
				style.endIdx = start;
				styles.insert(it - 1, style);
			}
			if (it->endIdx > end) {
				auto style = *it;
				style.startIdx = end;
				style.endIdx = it->endIdx;
				styles.insert(it - 1, style);
			}
			// remove the overlapping range
			it = styles.erase(it);
		} else {
			// adjust the indices of the remaining ranges if necessary
			if (it->startIdx >= end) {
				it->startIdx -= (end - start);
			}
			if (it->endIdx > end) {
				it->endIdx -= (end - start);
			}
			++it;
		}
	}
	//
	charEndIdx = text.size();
	startTextStyleIdx = -1;
	// TODO: this can be optimized later
	computeContentAlignmentInternal();
	//
	screenNode->invalidateLayout(parentNode);
}

void GUIStyledTextNode::insertText(int32_t idx, int c) {
	auto s = Character::toString(c);
	text.insert(idx, s);
	//
	idx = text.getUtf8BinaryIndex(idx);
	auto count = s.size();
	// Haha: ChatGPT
	auto startIdx = idx;
	auto endIdx = idx + count;
	for (auto it = styles.begin(); it != styles.end();) {
	    // check if the current range overlaps with the range to be inserted
	    if (it->startIdx < endIdx && it->endIdx > startIdx) {
	        // split the overlapping range into two non-overlapping ranges
	        if (it->startIdx < startIdx) {
	        	auto style = *it;
	        	style.endIdx = startIdx;
	            styles.insert(it - 1, style);
	        }
	        if (it->endIdx > endIdx) {
	        	auto style = *it;
	        	style.startIdx = endIdx;
	            styles.insert(it - 1, style);
	        }
	        // remove the overlapping range
			it = styles.erase(it);
	    } else {
	        // adjust the indices of the remaining ranges if necessary
	        if (it->endIdx > startIdx) {
	            it->endIdx += (endIdx - startIdx);
	        }
	        ++it;
	    }
	}
	charEndIdx = text.size();
	startTextStyleIdx = -1;
	// TODO: this can be optimized later
	computeContentAlignmentInternal();
	//
	screenNode->invalidateLayout(parentNode);
}

void GUIStyledTextNode::insertText(int32_t idx, const string& s) {
	// TODO: we have new node dimension after remove
	text.insert(idx, s);
	idx = text.getUtf8BinaryIndex(idx);
	//
	auto count = s.size();
	// Haha: ChatGPT
	auto startIdx = idx;
	auto endIdx = idx + count;
	for (auto it = styles.begin(); it != styles.end();) {
	    // check if the current range overlaps with the range to be inserted
	    if (it->startIdx < endIdx && it->endIdx > startIdx) {
	        // split the overlapping range into two non-overlapping ranges
	        if (it->startIdx < startIdx) {
	        	auto style = *it;
	        	style.endIdx = startIdx;
	            styles.insert(it - 1, style);
	        }
	        if (it->endIdx > endIdx) {
	        	auto style = *it;
	        	style.startIdx = endIdx;
	            styles.insert(it - 1, style);
	        }
	        // remove the overlapping range
			it = styles.erase(it);
	    } else {
	        // adjust the indices of the remaining ranges if necessary
	        if (it->endIdx > startIdx) {
	            it->endIdx += (endIdx - startIdx);
	        }
	        ++it;
	    }
	}
	//
	charEndIdx = text.size();
	startTextStyleIdx = -1;
	// TODO: this can be optimized later
	computeContentAlignmentInternal();
	//
	screenNode->invalidateLayout(parentNode);
}

void GUIStyledTextNode::scrollToIndex(int cursorIndex) {
	// no font, exit
	if (font == nullptr) return;

	//
	auto yBefore = 0.0f;
	auto y = 0.0f;
	auto textStyleIdx = 0;
	auto u8It = text.getUTF8CharacterIterator();
	while (u8It.hasNext() == true) {
		//
		determineNextLineConstraints(u8It, text.size(), textStyleIdx);

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
		lineCharBinaryIdxs.clear();
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

void GUIStyledTextNode::scrollToIndex() {
	// no font, exit
	if (font == nullptr) return;

	//
	auto styledTextController = required_dynamic_cast<GUIStyledTextNodeController*>(controller);
	scrollToIndex(styledTextController->getIndex());
}

void GUIStyledTextNode::scrollToSelectionIndex() {
	// no font, exit
	if (font == nullptr) return;

	//
	auto styledTextController = required_dynamic_cast<GUIStyledTextNodeController*>(controller);
	scrollToIndex(styledTextController->getSelectionIndex());
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
		LineInfo(
			int charIdx,
			float y
		):
			charIdx(charIdx),
			y(y)
		{}
		int charIdx;
		float y;
	};
	vector<LineInfo> lines;
	auto u8It = text.getUTF8CharacterIterator();
	while (u8It.hasNext() == true) {
		//
		determineNextLineConstraints(u8It, text.size(), textStyleIdx);

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
			lines.emplace_back(
				lineCharIdxs[0],
				y
			);
			y+= lineConstraintsEntity.height;
		}

		//
		line.clear();
		lineCharBinaryIdxs.clear();
		lineCharIdxs.clear();
		lineConstraints.clear();

		//
		if (reachedCursorIndex == true) break;
	}

	// scroll down
	if (visibleHeight < autoHeight) {
		auto renderOffsetY = parentNode->getChildrenRenderOffsetY();
		parentOffsetsChanged = true;
		parentNode->setChildrenRenderOffsetY(Math::max(renderOffsetY - visibleHeight, 0.0f));
	}

	// determine cursor index
	for (int i = lines.size() - 1; i >= 0; i--) {
		auto& line = lines[i];
		if (y - line.y >= visibleHeight) {
			return line.charIdx;
		}
	}

	// otherwise fallback to previous value
	return 0;
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
	auto u8It = text.getUTF8CharacterIterator();
	while (u8It.hasNext() == true) {
		//
		determineNextLineConstraints(u8It, text.size(), textStyleIdx);

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
		lineCharBinaryIdxs.clear();
		lineCharIdxs.clear();
		lineConstraints.clear();

		//
		if (finished == true) break;
	}

	// scroll down
	if (visibleHeight < autoHeight) {
		auto renderOffsetY = parentNode->getChildrenRenderOffsetY();
		parentOffsetsChanged = true;
		parentNode->setChildrenRenderOffsetY(Math::min(renderOffsetY + visibleHeight, static_cast<float>(autoHeight - visibleHeight)));
	}

	//
	if (finished == true) {
		return cursorIndex;
	} else {
		return u8It.getCharacterPosition() - 1;
	}
}

const string GUIStyledTextNode::getNodeType()
{
	return "styledtext";
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

void GUIStyledTextNode::computeContentAlignmentInternal() {
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
	auto u8It = text.getUTF8CharacterIterator();
	while (u8It.hasNext() == true) {
		//
		determineNextLineConstraints(u8It, text.size(), textStyleIdx);

		//
		for (auto& lineConstraintsEntity: lineConstraints) {
			if (lineConstraintsEntity.width > autoWidth) autoWidth = lineConstraintsEntity.width;
			autoHeight+= lineConstraintsEntity.height;
		}

		//
		line.clear();
		lineCharBinaryIdxs.clear();
		lineCharIdxs.clear();
		lineConstraints.clear();
	}

	//
	this->widthLast = computedConstraints.width;
	this->heightLast = computedConstraints.height;
}

void GUIStyledTextNode::computeContentAlignment() {
	computeContentAlignmentInternal();

	//
	this->parentOffsetsChanged = true;
}

void GUIStyledTextNode::setText(const MutableString& text) {
	this->parentOffsetsChanged = true;
	this->parentXOffsetLast = 0.0f;
	this->parentYOffsetLast = 0.0f;
	this->charStartIdx = 0;
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
	[image=horizontal-scale:50%|0.5,vertical-scale:50%|0.5,width:100,height:100,effect-color-mul:#ff0000ff,effect-color-add:#ff000000]example.com/bild.jpg[/image]
	*/
	string styleFont;
	int styleSize = size;
	string styleColor;
	string styleUrl;
	string styleImage;
	//
	auto parseStyle = false;
	auto parseImage = false;
	int imageWidth = -1;
	int imageHeight = -1;
	float imageHorizontalScale = 1.0f;
	float imageVerticalScale = 1.0f;
	GUIColor imageEffectColorMul = GUIColor::GUICOLOR_EFFECT_COLOR_MUL;
	GUIColor imageEffectColorAdd = GUIColor::GUICOLOR_EFFECT_COLOR_ADD;
	string currentStyle;
	int styleStartIdx = -1;
	char lc = 0;
	for (auto i = 0; i < text.size(); i++) {
		auto c = text.getCharAt(i);
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
							if (this->text.size() > styleStartIdx) setTextStyle(styleStartIdx, this->text.size() - 1, GUIColor(styleColor), styleFont, styleSize, styleUrl);
						} else {
							if (this->text.size() > styleStartIdx) setTextStyle(styleStartIdx, this->text.size() - 1, styleFont, styleSize, styleUrl);
						}
					}
					if (styleTokenized.size() == 2) {
						auto command = StringTools::toLowerCase(StringTools::trim(styleTokenized[0]));
						auto argument = StringTools::trim(styleTokenized[1]);
						if (command == "font") {
							styleFont = argument;
							styleStartIdx = this->text.size();
						} else
						if (command == "size") {
							try {
								styleSize = Integer::parse(argument);
							} catch (Exception& exception) {
								Console::println("GUIStyledTextNode::setText(): size: unknown value: " + argument);
							}
							styleStartIdx = this->text.size();
						} else
						if (command == "color") {
							styleColor = argument;
							styleStartIdx = this->text.size();
						} else
						if (command == "url") {
							styleUrl = argument;
							styleStartIdx = this->text.size();
						} else
						if (command == "image") {
							parseImage = true;
							auto imageOptions = StringTools::tokenize(styleTokenized[1], ",");
							for (auto& imageOption: imageOptions) {
								auto nameValuePair = StringTools::tokenize(imageOption, ":");
								if (nameValuePair.size() != 2) {
									Console::println("GUIStyledTextNode::setText(): unknown image style command option: " + imageOption);
								} else {
									auto name = StringTools::trim(nameValuePair[0]);
									auto value = StringTools::trim(nameValuePair[1]);
									if (name.empty() == true || value.empty() == true) {
										Console::println("GUIStyledTextNode::setText(): unknown image style command option: name or value empty");
									} else
									if (name == "width") {
										try {
											imageWidth = Integer::parse(value);
										} catch (Exception& exception) {
											Console::println("GUIStyledTextNode::setText(): unknown image style command option: width: unknown value: " + value);
										}
									} else
									if (name == "height") {
										try {
											imageHeight = Integer::parse(value);
										} catch (Exception& exception) {
											Console::println("GUIStyledTextNode::setText(): unknown image style command option: height: unknown value: " + value);
										}
									} else
									if (name == "horizontal-scale") {
										try {
											if (StringTools::endsWith(value, "%")) {
												imageHorizontalScale = Float::parse(value.substr(0, value.length() - 1)) / 100.0f;
											} else {
												imageHorizontalScale = Float::parse(value);
											}
										} catch (Exception& exception) {
											Console::println("GUIStyledTextNode::setText(): unknown image style command option: horizontal-scale: unknown value: " + value);
										}
									} else
									if (name == "vertical-scale") {
										try {
											if (StringTools::endsWith(value, "%")) {
												imageVerticalScale = Float::parse(value.substr(0, value.length() - 1)) / 100.0f;
											} else {
												imageVerticalScale = Float::parse(value);
											}
										} catch (Exception& exception) {
											Console::println("GUIStyledTextNode::setText(): unknown image style command option: vertical-scale: unknown value: " + value);
										}
									} else
									if (name == "effect-color-mul") {
										try {
											imageEffectColorMul = GUIColor(value);
										} catch (Exception& exception) {
											Console::println("GUIStyledTextNode::setText(): unknown image style command option: effect-color-mul: unknown value: " + value);
										}
									} else
									if (name == "effect-color-add") {
										try {
											imageEffectColorAdd = GUIColor(value);
										} catch (Exception& exception) {
											Console::println("GUIStyledTextNode::setText(): unknown image style command option: effect-color-add: unknown value: " + value);
										}
									} else {
										Console::println("GUIStyledTextNode::setText(): image style command option: " + name + " = '" + value + "'");
									}
								}
							}
						} else {
							Console::println("GUIStyledTextNode::setText(): unknown style command: " + currentStyle);
						}
					} else
					if (styleTokenized.size() == 1) {
						auto command = StringTools::toLowerCase(StringTools::trim(styleTokenized[0]));
						if (command == "/font") {
							styleFont.clear();
						} else
						if (command == "/size") {
							styleSize = size;
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
							setImage(this->text.size() - 1, styleImage, styleUrl, imageWidth, imageHeight, imageHorizontalScale, imageVerticalScale, imageEffectColorMul, imageEffectColorAdd);
							styleImage.clear();
							imageWidth = -1;
							imageHeight = -1;
							imageHorizontalScale = 1.0f;
							imageVerticalScale = 1.0f;
							imageEffectColorMul = GUIColor::GUICOLOR_EFFECT_COLOR_MUL;
							imageEffectColorAdd = GUIColor::GUICOLOR_EFFECT_COLOR_ADD;
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
			if (this->text.size() > styleStartIdx) setTextStyle(styleStartIdx, this->text.size() - 1, GUIColor(styleColor), styleFont, styleSize, styleUrl);
		} else {
			if (this->text.size() > styleStartIdx) setTextStyle(styleStartIdx, this->text.size() - 1, styleFont, styleSize, styleUrl);
		}
	}

	// add a trailing newline
	if (StringTools::endsWith(this->text.getString(), newLine) == false) this->text.append(newLine);

	//
	this->charEndIdx = text.size();
}

void GUIStyledTextNode::dispose()
{
	unsetStyles();
	if (font != nullptr) font->dispose();
	GUINode::dispose();
}

void GUIStyledTextNode::determineNextLineConstraints(UTF8CharacterIterator& u8It, int charEndIdx, int textStyleIdx) {
	//
	auto maxLineWidth = requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO?Float::MAX_VALUE:computedConstraints.width - (border.left + border.right + padding.left + padding.right);

	// determine line to render
	if (preformatted == true) {
		line.clear();
		lineCharBinaryIdxs.clear();
		lineCharIdxs.clear();
		while (u8It.getBinaryPosition() < charEndIdx && u8It.hasNext() == true) {
			auto k = u8It.getBinaryPosition();
			auto kc = u8It.getCharacterPosition();
			auto c = u8It.next();
			// line finished?
			if (c == '\n') {
				auto l1 = line.size();
				Character::appendToString(line, c);
				auto l2 = line.size();
				for (auto l = l1; l < l2; l++) lineCharBinaryIdxs.push_back(k);
				lineCharIdxs.push_back(kc);
				break;
			} else {
				auto l1 = line.size();
				Character::appendToString(line, c);
				auto l2 = line.size();
				for (auto l = l1; l < l2; l++) lineCharBinaryIdxs.push_back(k);
				lineCharIdxs.push_back(kc);
			}
		}
	} else {
		line.clear();
		lineCharBinaryIdxs.clear();
		lineCharIdxs.clear();
		while (u8It.getBinaryPosition() < charEndIdx && u8It.hasNext() == true) {
			auto k = u8It.getBinaryPosition();
			auto kc = u8It.getCharacterPosition();
			auto c = u8It.next();
			// line finished?
			if (c == '\n') {
				auto l1 = line.size();
				Character::appendToString(line, c);
				auto l2 = line.size();
				for (auto l = l1; l < l2; l++) lineCharBinaryIdxs.push_back(k);
				lineCharIdxs.push_back(kc);
				break;
			} else
			if (line.empty() == false && c == ' ' && StringTools::endsWith(line, spaceString) == true) {
				// no op as we have a line which already has a space at the end
			} else
			if (line.empty() == true && (c == ' ' || c == '\t')) {
				// no op
			} else {
				auto l1 = line.size();
				Character::appendToString(line, c);
				auto l2 = line.size();
				for (auto l = l1; l < l2; l++) lineCharBinaryIdxs.push_back(k);
				lineCharIdxs.push_back(kc);
			}
		}
	}

	// remove trailing space
	while (StringTools::endsWith(line, spaceString) == true) line.erase(line.begin() + line.size() - 1);

	if (line.empty() == true) {
		//
		lineConstraints.emplace_back(
			0,
			0,
			0.0f,
			font->getLineHeight(),
			font->getLineHeight(),
			font->getBaseLine(),
			true
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
		auto charIdx = 0;

		//
		lineConstraints.clear();
		lineConstraints.emplace_back(
			-1,
			-1,
			0.0f,
			0.0f,
			0.0f,
			0.0f,
			false
		);
		{
			auto currentTextStyleIdx = textStyleIdx;
			UTF8CharacterIterator lineU8It(line);
			while (lineU8It.hasNext() == true) {
				charIdx = lineU8It.getCharacterPosition();
				auto k = lineU8It.getBinaryPosition();
				auto kc = charIdx;
				auto c = lineU8It.next();
				auto textStyle = getTextStyle(lineCharBinaryIdxs, k, currentTextStyleIdx);
				auto currentFont = textStyle != nullptr && textStyle->font != nullptr?textStyle->font:font;
				baseLine = Math::max(baseLine, currentFont->getBaseLine());
				baseLineSpaceWrap = Math::max(baseLineSpaceWrap, currentFont->getBaseLine());
				lineHeight = Math::max(lineHeight, currentFont->getLineHeight());
				lineHeightSpaceWrap = Math::max(lineHeightSpaceWrap, currentFont->getLineHeight());
				// render a image
				if (textStyle != nullptr && textStyle->image != nullptr) {
					if (lineConstraints[lineConstraints.size() - 1].spaceWrap == false) {
						lineConstraints[lineConstraints.size() - 1] = Line(
							k,
							kc,
							lineWidth,
							Math::max(lineHeight, baseLine + imageHeight),
							lineHeight,
							baseLine,
							false
						);
						lineWidthSpaceWrap = 0.0f;
						lineHeightSpaceWrap = 0.0f;
						baseLineSpaceWrap = 0.0f;
					}
					if (lineWidth > maxLineWidth) {
						imageHeight = 0.0f;
						lineWidth = lineWidthSpaceWrap;
						lineHeight = lineHeightSpaceWrap;
						baseLine = baseLineSpaceWrap;
						lineConstraints.emplace_back(
							-1,
							kc,
							0.0f,
							0.0f,
							0.0f,
							0.0f,
							false
						);
					}
					lineWidth+= textStyle->width;
					lineWidthSpaceWrap+= textStyle->width;
					imageHeight = Math::max(imageHeight, static_cast<float>(textStyle->height));
				} else {
					// render text
					if (c == ' ') {
						lineConstraints[lineConstraints.size() - 1] = Line(
							k,
							kc,
							lineWidth,
							Math::max(lineHeight, baseLine + imageHeight),
							lineHeight,
							baseLine,
							true
						);
						lineWidthSpaceWrap = 0.0f;
						lineHeightSpaceWrap = 0.0f;
						baseLineSpaceWrap = 0.0f;
					}
					auto character = currentFont->getCharacter(c == '\t'?' ':c);
					if (character != nullptr) {
						if (lineConstraints[lineConstraints.size() - 1].spaceWrap == false) {
							lineConstraints[lineConstraints.size() - 1] = Line(
								k,
								kc,
								lineWidth,
								Math::max(lineHeight, baseLine + imageHeight),
								lineHeight,
								baseLine,
								false
							);
							lineWidthSpaceWrap = 0.0f;
							lineHeightSpaceWrap = 0.0f;
							baseLineSpaceWrap = 0.0f;
						}
						if (lineWidth > maxLineWidth) {
							lineWidth = lineWidthSpaceWrap;
							if (lineU8It.hasNext() == true) {
								imageHeight = 0.0f;
								lineHeight = lineHeightSpaceWrap;
								baseLine = baseLineSpaceWrap;
							}
							lineConstraints.emplace_back(
								-1,
								-1,
								0.0f,
								0.0f,
								0.0f,
								0.0f,
								false
							);
						}
						auto charXAdvance = c == '\t'?character->getXAdvance() * tabSize:character->getXAdvance();
						lineWidth+= charXAdvance;
						lineWidthSpaceWrap+= lineWidthSpaceWrap < Math::EPSILON && (c == ' ' || c == '\t')?0.0f:charXAdvance;
					}
				}
			}
		}

		//
		lineConstraints[lineConstraints.size() - 1] = Line(
			static_cast<int>(line.size()),
			charIdx,
			lineWidth,
			Math::max(lineHeight, baseLine + imageHeight),
			lineHeight,
			baseLine,
			false
		);
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
		Float::equals(parentXOffset, parentXOffsetLast) == true ||
		Float::equals(parentYOffset, parentYOffsetLast) == true) {
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
	auto styledTextController = required_dynamic_cast<GUIStyledTextNodeController*>(controller);
	auto cursorMode = GUIStyledTextNodeController::CURSORMODE_HIDE;
	auto cursorIndex = styledTextController->getIndex();
	auto cursorSelectionIndex = styledTextController->getSelectionIndex();
	if (editMode == true) {
		cursorMode = styledTextController->getCursorMode();
	}

	//
	urlAreas.clear();

	// do we have a mouse x and y index position
	auto indexMousePositionX = this->indexMousePositionX;
	auto indexMousePositionY = this->indexMousePositionY;
	auto findNewIndex = editMode == true && indexMousePositionX != MOUSEPOSITION_NONE && indexMousePositionY != MOUSEPOSITION_NONE;
	if (findNewIndex == true) {
		cursorIndex = -1;
		indexMousePositionX+= parentNode->getChildrenRenderOffsetX();
		indexMousePositionY+= parentNode->getChildrenRenderOffsetY();
		indexMousePositionX+= xIndentLeft;
		indexMousePositionY+= yIndentTop;
	}

	// do we have a mouse x and y selection index position
	auto selectionIndexMousePositionX = this->selectionIndexMousePositionX;
	auto selectionIndexMousePositionY = this->selectionIndexMousePositionY;
	auto findNewSelectionIndex = editMode == true && findNewIndex == false && selectionIndexMousePositionX != MOUSEPOSITION_NONE && selectionIndexMousePositionY != MOUSEPOSITION_NONE;
	if (findNewSelectionIndex == true) {
		cursorSelectionIndex = -1;
		selectionIndexMousePositionX+= parentNode->getChildrenRenderOffsetX();
		selectionIndexMousePositionY+= parentNode->getChildrenRenderOffsetY();
		selectionIndexMousePositionX+= xIndentLeft;
		selectionIndexMousePositionY+= yIndentTop;
	}

	//
	auto maxLineWidth = getAutoWidth();
	auto textStyleIdx = startTextStyleIdx;
	auto boundTexture = -1;
	GUIColor lastColor = color;
	string currentURL;
	string styleURL;
	int x = 0;
	auto u8It = text.getUTF8CharacterIterator();
	u8It.seekBinaryPosition(charStartIdx);
	for (;u8It.hasNext() == true && u8It.getBinaryPosition() < charEndIdx;) {

		//
		auto nextCharStartIdx = u8It.getBinaryPosition();
		auto nextStartTextStyleIdx = textStyleIdx;
		auto nextStartRenderY = y;

		//
		determineNextLineConstraints(u8It, charEndIdx, textStyleIdx);

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
				if (guiRenderer->isQuadVisible2(
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
				for (auto k = lineIdx == 0?0:lineConstraints[lineIdx - 1].binaryIdx; k < lineConstraints[lineIdx].binaryIdx; k++)
					getTextStyle(lineCharBinaryIdxs, k, currentTextStyleIdx);
			}
			// render
			if (lineIdx == lineConstraints.size()) {
				// was visible, then store text render end values
				if (visible == true) {
					visible = false;
					charEndIdx = lineCharBinaryIdxs[0];
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
				// find new indices if requested
				// 	index
				if (findNewIndex == true &&
					indexMousePositionY >= y + yIndentTop && indexMousePositionY < y + yIndentTop + lineConstraints[lineIdx].height &&
					indexMousePositionX <= x + xIndentLeft) {
					cursorIndex = lineCharIdxs[0];
				}
				// 	selection index
				if (findNewSelectionIndex == true &&
					selectionIndexMousePositionY >= y + yIndentTop && selectionIndexMousePositionY < y + yIndentTop + lineConstraints[lineIdx].height &&
					selectionIndexMousePositionX <= x + xIndentLeft) {
					cursorSelectionIndex = lineCharIdxs[0];
				}
				// render
				UTF8CharacterIterator lineU8It(line);
				lineU8It.seekBinaryPosition(lineIdx == 0?0:lineConstraints[lineIdx - 1].binaryIdx);
				while (lineU8It.hasNext() == true) {
					auto k = lineU8It.getBinaryPosition();
					auto kc = lineU8It.getCharacterPosition();
					auto c = lineU8It.next();
					auto textStyle = getTextStyle(lineCharBinaryIdxs, k, currentTextStyleIdx);
					Color4 currentColor = color;
					GUIFont* currentFont = font;
					styleURL.clear();
					// apply text style or defaults
					if (textStyle != nullptr) {
						currentFont = textStyle->font != nullptr?textStyle->font:font;
						currentColor = textStyle->color;
						styleURL = textStyle->url;
					}
					// image rendering
					if (textStyle != nullptr && textStyle->image != nullptr) {
						// draw
						guiRenderer->render();
						auto rendererEffectColorMul = guiRenderer->getGUIEffectColorMul();
						auto rendererEffectColorAdd = guiRenderer->getGUIEffectColorAdd();
						guiRenderer->setGUIEffectColorMul(textStyle->effectColorMul);
						guiRenderer->setGUIEffectColorAdd(textStyle->effectColorAdd);
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
						}
						if (cursorMode == GUIStyledTextNodeController::CURSORMODE_SHOW && (findNewSelectionIndex == true?cursorSelectionIndex == lineCharIdxs[kc]:cursorIndex == lineCharIdxs[kc])) {
							// draw cursor
							float left = x + xIndentLeft;
							float top = y + yIndentTop + (lineConstraints[lineIdx].baseLine - textStyle->height) + (lineConstraints[lineIdx].height - lineConstraints[lineIdx].lineHeight);
							float width = 2;
							float height = textStyle->height;
							auto& colorData = color.getArray();
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
								0.0f, 0.0f,
								true
							);
							// store new index position
							indexPositionX = static_cast<int>(left);
							indexPositionY = static_cast<int>(top);
						}
						//
						guiRenderer->render();
						guiRenderer->bindTexture(boundTexture);
						guiRenderer->setGUIEffectColorMul(rendererEffectColorMul);
						guiRenderer->setGUIEffectColorAdd(rendererEffectColorAdd);
						// flush current URL
						if (currentURL.empty() == false && urlAreas.empty() == false) {
							auto& urlArea = urlAreas[urlAreas.size() - 1];
							urlArea.width = x - urlArea.left;
							urlArea.height = lineConstraints[lineIdx].lineHeight;
						}
						currentURL.clear();
						// add url area if URL is given
						if (textStyle->url.empty() == false) {
							urlAreas.emplace_back(
								static_cast<int>(x),
								static_cast<int>(y),
								static_cast<int>(textStyle->width),
								static_cast<int>(textStyle->height),
								textStyle->url
							);
						}
						//
						x+= textStyle->width;
					} else {
						// text rendering
						// do line break
						if (k == lineConstraints[lineIdx].binaryIdx) {
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
							// find new indices if requested
							// 	index
							if (findNewIndex == true &&
								indexMousePositionY >= y + yIndentTop && indexMousePositionY < y + yIndentTop + lineConstraints[lineIdx].height &&
								indexMousePositionX <= x + xIndentLeft) {
								cursorIndex = lineCharIdxs[kc];
							}
							// 	selection index
							if (findNewSelectionIndex == true &&
								selectionIndexMousePositionY >= y + yIndentTop && selectionIndexMousePositionY < y + yIndentTop + lineConstraints[lineIdx].height &&
								selectionIndexMousePositionX <= x + xIndentLeft) {
								cursorSelectionIndex = lineCharIdxs[kc];
							}
							//
							{
								float left = x + xIndentLeft;
								float top = y + yIndentTop;
								float width = lineConstraints[lineIdx].width;
								float height = lineConstraints[lineIdx].height;
								if (guiRenderer->isQuadVisible2(
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
										//

										charEndIdx = lineCharBinaryIdxs[lineIdx == 0?0:lineConstraints[lineIdx - 1].charIdx];
										break;
									}
								}
							}
						}
						// skip spaces if requested
						if (skipSpaces == true) {
							if (c == ' ' || c == '\t') {
								continue;
							} else {
								skipSpaces = false;
							}
						}
						if (c == '\n') {
							// find new indices if requested
							// 	index
							if (findNewIndex == true &&
								indexMousePositionY >= y + yIndentTop && indexMousePositionY < y + yIndentTop + lineConstraints[lineIdx].height &&
								indexMousePositionX >= x + xIndentLeft) {
								cursorIndex = lineCharIdxs[kc];
							}
							// 	selection index
							if (findNewSelectionIndex == true &&
								selectionIndexMousePositionY >= y + yIndentTop && selectionIndexMousePositionY < y + yIndentTop + lineConstraints[lineIdx].height &&
								selectionIndexMousePositionX >= x + xIndentLeft) {
								cursorSelectionIndex = lineCharIdxs[kc];
							}
							// draw cursor
							if (cursorMode == GUIStyledTextNodeController::CURSORMODE_SHOW && (findNewSelectionIndex == true?cursorSelectionIndex == lineCharIdxs[kc]:cursorIndex == lineCharIdxs[kc])) {
								float left = x + xIndentLeft;
								float top = y + yIndentTop + (lineConstraints[lineIdx].baseLine - currentFont->getBaseLine()) + (lineConstraints[lineIdx].height - lineConstraints[lineIdx].lineHeight);
								float width = 2;
								float height = lineConstraints[lineIdx].lineHeight;
								auto& colorData = color.getArray();
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
									0.0f, 0.0f,
									true
								);
								// store new index position
								indexPositionX = static_cast<int>(left);
								indexPositionY = static_cast<int>(top);
							}
						} else {
							// otherwise draw
							auto characterCount = c == '\t'?tabSize:1;
							auto character = currentFont->getCharacter(c == '\t'?' ':c);
							if (character != nullptr) {
								// next x advance
								auto xAdvance = c == '\t'?tabSize * character->getXAdvance():character->getXAdvance();

								// find new indices if requested
								// 	index
								if (findNewIndex == true &&
									indexMousePositionY >= y + yIndentTop && indexMousePositionY < y + yIndentTop + lineConstraints[lineIdx].height &&
									indexMousePositionX >= x + xIndentLeft && indexMousePositionX < x + xIndentLeft + xAdvance) {
									cursorIndex = lineCharIdxs[kc];
								}
								// 	selection index
								if (findNewSelectionIndex == true &&
									selectionIndexMousePositionY >= y + yIndentTop && selectionIndexMousePositionY < y + yIndentTop + lineConstraints[lineIdx].height &&
									selectionIndexMousePositionX >= x + xIndentLeft && selectionIndexMousePositionX < x + xIndentLeft + xAdvance) {
									cursorSelectionIndex = lineCharIdxs[kc];
								}

								//
								auto hasSelection = false;
								if (cursorSelectionIndex != -1 || findNewSelectionIndex == true) {
									if ((cursorSelectionIndex != -1 && lineCharIdxs[kc] >= Math::min(cursorIndex, cursorSelectionIndex) && lineCharIdxs[kc] < Math::max(cursorIndex, cursorSelectionIndex)) ||
										(cursorSelectionIndex == -1 && lineCharIdxs[kc] >= cursorIndex)) {
										for (auto l = 0; l < characterCount; l++) {
											float left = x + xIndentLeft + (l * character->getXAdvance());
											float top = y + yIndentTop + (lineConstraints[lineIdx].baseLine - currentFont->getBaseLine()) + (lineConstraints[lineIdx].height - lineConstraints[lineIdx].lineHeight);
											currentFont->drawCharacterBackground(guiRenderer, character, left, top, lineConstraints[lineIdx].lineHeight, selectionBackgroundColor);
										}
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
									currentFont->drawCharacter(guiRenderer, character, left, top, currentColor);
								}

								// draw cursor
								if (cursorMode == GUIStyledTextNodeController::CURSORMODE_SHOW && (findNewSelectionIndex == true?cursorSelectionIndex == lineCharIdxs[kc]:cursorIndex == lineCharIdxs[kc])) {
									float left = x + xIndentLeft;
									float top = y + yIndentTop + (lineConstraints[lineIdx].baseLine - currentFont->getBaseLine()) + (lineConstraints[lineIdx].height - lineConstraints[lineIdx].lineHeight);
									float width = 2;
									float height = lineConstraints[lineIdx].lineHeight;
									auto& colorData = color.getArray();
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
										0.0f, 0.0f,
										true
									);
									// store new index position
									indexPositionX = static_cast<int>(left);
									indexPositionY = static_cast<int>(top);
								}

								// if URL did change, create URL areas
								if (styleURL != currentURL) {
									if (currentURL.empty() == false && urlAreas.empty() == false) {
										auto& urlArea = urlAreas[urlAreas.size() - 1];
										urlArea.width = x - urlArea.left;
										urlArea.height = lineConstraints[lineIdx].lineHeight;
									}
									if (styleURL.empty() == false) {
										urlAreas.emplace_back(
											static_cast<int>(x),
											static_cast<int>(y),
											-1,
											1,
											styleURL
										);
									}
									currentURL = styleURL;
								}

								// advance X
								x+= xAdvance;
							}
						}
					}
				}

				// find new indices if requested
				// 	index
				if (findNewIndex == true &&
					indexMousePositionY >= y + yIndentTop && indexMousePositionY < y + yIndentTop + lineConstraints[lineIdx].height &&
					indexMousePositionX >= x + xIndentLeft) {
					cursorIndex = lineCharIdxs[lineCharIdxs.size() - 1];
				}

				// 	selection index
				if (findNewSelectionIndex == true &&
					selectionIndexMousePositionY >= y + yIndentTop && selectionIndexMousePositionY < y + yIndentTop + lineConstraints[lineIdx].height &&
					selectionIndexMousePositionX >= x + xIndentLeft) {
					cursorSelectionIndex = lineCharIdxs[lineCharIdxs.size() - 1];
				}

				//
				if (lineConstraints[lineConstraints.size() - 1].binaryIdx == line.size()) {
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
		line.clear();
		lineCharBinaryIdxs.clear();
		lineConstraints.clear();
	}

	//
	// Console::println("y: " + to_string(y) + " / " + to_string(autoHeight));

	//
	guiRenderer->render();
	guiRenderer->bindTexture(0);

	// index
	if (findNewIndex == true) {
		if (cursorIndex != -1) styledTextController->setIndex(cursorIndex);
		unsetIndexMousePosition();
	}
	// selection index
	if (findNewSelectionIndex == true) {
		if (cursorSelectionIndex != -1) styledTextController->setSelectionIndex(cursorSelectionIndex);
	}
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
	// HAHA: OpenGPT
	// Iterate through the list of ranges
	for (auto it = styles.begin(); it != styles.end();) {
	    // Check if the start index of the range to be removed is within the range of the current range
	    // or if the end index of the range to be removed is within the range of the current range
	    if ((startIdx >= it->startIdx && startIdx < it->endIdx) || (endIdx > it->startIdx && endIdx <= it->endIdx)) {
	        // Split the overlapping range into two non-overlapping ranges
	        if (startIdx > it->startIdx) {
	        	auto style = *it;
	        	style.endIdx = startIdx;
	            styles.insert(it - 1, style);
	        }
	        if (endIdx < it->endIdx) {
	        	auto style = *it;
	        	style.startIdx = endIdx;
	            styles.insert(it - 1, style);
	        }
	        // Remove the overlapping range
	        it = styles.erase(it);
	    } else {
	        ++it;
	    }
	}
}

void GUIStyledTextNode::setTextStyle(int startIdx, int endIdx, const GUIColor& color, const string& font, int size, const string& url) {
	// Console::print("GUIStyledTextNode::setTextStyle(): " + to_string(startIdx) + " ... " + to_string(endIdx) + ": '");
	// for (auto i = startIdx; i <= endIdx; i++) Console::print(string() + text.charAt(i));
	// Console::print("'");
	// Console::print(", color = " + to_string(color.getRed()) + ", " + to_string(color.getGreen()) + ", " + to_string(color.getBlue()) + ", " + to_string(color.getAlpha()));
	// Console::print(", url = '" + url + "'");
	// Console::println();
	unsetTextStyle(startIdx, endIdx);
	//
	if (size <= 0) size = this->size;
	auto _font = font.empty() == true?nullptr:screenNode->getFont(font, size);
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
			.height = -1,
			.effectColorMul = GUIColor::GUICOLOR_EFFECT_COLOR_MUL,
			.effectColorAdd = GUIColor::GUICOLOR_EFFECT_COLOR_ADD
		}
	);
	//
	startTextStyleIdx = -1;
	// for (auto& style: styles) Console::println("post: " + to_string(style.startIdx) + " ... " + to_string(style.endIdx));
}

void GUIStyledTextNode::setTextStyle(int startIdx, int endIdx, const string& font, int size, const string& url) {
	// Console::print("GUIStyledTextNode::setTextStyle(): " + to_string(startIdx) + " ... " + to_string(endIdx) + ": '");
	// for (auto i = startIdx; i <= endIdx; i++) Console::print(string() + text.charAt(i));
	// Console::print("'");
	// Console::print(", url = '" + url + "'");
	// Console::println();
	unsetTextStyle(startIdx, endIdx);
	//
	if (size <= 0) size = this->size;
	auto _font = font.empty() == true?nullptr:screenNode->getFont(font, size);
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
			.height = -1,
			.effectColorMul = GUIColor::GUICOLOR_EFFECT_COLOR_MUL,
			.effectColorAdd = GUIColor::GUICOLOR_EFFECT_COLOR_ADD
		}
	);
	//
	startTextStyleIdx = -1;
	// for (auto& style: styles) Console::println("post: " + to_string(style.startIdx) + " ... " + to_string(style.endIdx));
}

void GUIStyledTextNode::setImage(int idx, const string& image, const string& url, int width, int height, float horizontalScale, float verticalScale, const GUIColor& effectColorMul, const GUIColor& effectColorAdd) {
	// Console::println("GUIStyledTextNode::setImage(): " + to_string(idx) + ": " + image + ", url = '" + url + "', width = " + to_string(width) + ", height = " + to_string(height));
	unsetTextStyle(idx,idx);
	// TODO: a.drewke
	auto _image = image.empty() == true?nullptr:screenNode->getImage(image);
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
			.width = width == -1?static_cast<int>(_image->getWidth() * horizontalScale):static_cast<int>(width * horizontalScale),
			.height = height == -1?static_cast<int>(_image->getHeight() * verticalScale):static_cast<int>(height * verticalScale),
			.effectColorMul = effectColorMul,
			.effectColorAdd = effectColorAdd
		}
	);
	//
	startTextStyleIdx = -1;
	// for (auto& style: styles) Console::println("post: " + to_string(style.startIdx) + " ... " + to_string(style.endIdx));
}
