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
	disposeStyles();
	this->text.reset();
	// TODO: parse BBCode styles
	/*
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
			if (c == ']' && lc != '\\') {
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
						Console::println(styleImage);
						parseImage = false;
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
				// style command
				currentStyle+= c;
			}
		} else
		// start of style
		if (c == '[' && lc != '\\') {
			parseStyle = true;
		} else {
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
		charEndIdx = text.size();
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
	string spaceString = " ";
	string tabString3 = "   ";
	string tabString4 = "    ";
	vector<int> lineCharIdxs;
	auto boundTexture = -1;
	GUIColor lastColor = color;
	for (auto i = charStartIdx; i < charEndIdx;) {
		// determine line to render
		{
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

		// determine baseline and part of line to render
		auto baseLine = font->getBaseLine();
		auto lineHeight = font->getLineHeight();
		auto lineWidth = 0.0f;

		//
		{
			Style* textStyle = nullptr;
			auto _font = font;
			auto _textStyleIdx = textStyleIdx;
			for (auto k = 0; k < line.size(); k++) {
				if (styles.empty() == false) {
					// find style to start with, aligned with last line start, if we do not have a start yet
					if (_textStyleIdx == -1) {
						_textStyleIdx = 0;
						for (auto l = 0; l < styles.size(); l++) {
							auto textStyle = &styles[l];
							if (textStyle->startIdx > lineCharIdxs[k]) {
								_textStyleIdx = l - 1;
								break;
							}
						}
					}
					// ok proceed to find correct style for character in text, based on our text style index
					auto _textStyle = _textStyleIdx < styles.size()?&styles[_textStyleIdx]:nullptr;
					if (_textStyle != nullptr && lineCharIdxs[k] >= _textStyle->startIdx) {
						if (lineCharIdxs[k] > _textStyle->endIdx) {
							// invalid text style, check next text style
							_textStyleIdx++;
							_textStyle = _textStyleIdx < styles.size()?&styles[_textStyleIdx]:nullptr;
							if (_textStyle != nullptr && lineCharIdxs[k] >= _textStyle->startIdx) {
								if (lineCharIdxs[k] <= _textStyle->endIdx) {
									// valid text style
									textStyle = _textStyle;
								}
							}
						} else
						if (lineCharIdxs[k] <= _textStyle->endIdx) {
							// valid text style
							textStyle = _textStyle;
						}
					}
				}
				if (textStyle != nullptr && textStyle->font != nullptr) {
					_font = textStyle->font;
					baseLine = Math::max(baseLine, _font->getBaseLine());
					lineHeight = Math::max(lineHeight, _font->getLineHeight());
				} else {
					_font = font;
				}
				auto character = _font->getCharacter(line[k]);
				if (character != nullptr) {
					lineWidth+= character->getXAdvance();
				}
			}
		}

		//
		{
			auto _color = color;
			auto _font = font;
			Style* textStyle = nullptr;
			auto& _textStyleIdx = textStyleIdx;
			auto x = 0;
			for (auto k = 0; k < line.size(); k++) {
				if (styles.empty() == false) {
					// find style to start with, aligned with last line start, if we do not have a start yet
					if (_textStyleIdx == -1) {
						_textStyleIdx = 0;
						for (auto l = 0; l < styles.size(); l++) {
							auto textStyle = &styles[l];
							if (textStyle->startIdx > lineCharIdxs[k]) {
								_textStyleIdx = l - 1;
								break;
							}
						}
					}
					// ok proceed to find correct style for character in text, based on our text style index
					auto _textStyle = _textStyleIdx < styles.size()?&styles[_textStyleIdx]:nullptr;
					if (_textStyle != nullptr && lineCharIdxs[k] >= _textStyle->startIdx) {
						if (lineCharIdxs[k] > _textStyle->endIdx) {
							// invalid text style, check next text style
							_textStyleIdx++;
							_textStyle = _textStyleIdx < styles.size()?&styles[_textStyleIdx]:nullptr;
							if (_textStyle != nullptr && lineCharIdxs[k] >= _textStyle->startIdx) {
								if (lineCharIdxs[k] <= _textStyle->endIdx) {
									// valid text style
									textStyle = _textStyle;
								}
							}
						} else
						if (lineCharIdxs[k] <= _textStyle->endIdx) {
							// valid text style
							textStyle = _textStyle;
						}
					}
				}
				if (textStyle != nullptr) {
					_font = textStyle->font != nullptr?textStyle->font:font;
					_color = textStyle->color;
				} else {
					_font = font;
					_color = color;
				}
				auto character = _font->getCharacter(line[k]);
				if (character != nullptr) {
					float left = x + xIndentLeft;
					// 30 LineHeight, 24 Baseline
					// 19 LineHeight, 15 Baseline
					float top = y + yIndentTop + (baseLine - _font->getBaseLine());
					if (boundTexture == -1) {
						boundTexture = _font->getTextureId();
						guiRenderer->bindTexture(boundTexture);
						lastColor = _color;
					} else
					if (boundTexture != _font->getTextureId()) {
						boundTexture = _font->getTextureId();
						guiRenderer->render();
						guiRenderer->bindTexture(boundTexture);
						lastColor = _color;
					} else
					if (_color.equals(lastColor) == false) {
						guiRenderer->render();
						lastColor = _color;
					}
					_font->drawCharacter(guiRenderer, character, left, top, _color);
					x+= character->getXAdvance();
				}
			}
		}

		//
		guiRenderer->render();

		//
		y+= lineHeight;

		/*
			// check for separation char or last char
			auto lineWidth = currentFont->getTextWidth(MutableString(line)) + currentFont->getTextWidth(MutableString(word));
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
				Style* textStyleLast = nullptr;
				Style* textStyle = nullptr;

				//
				do {
					//
					auto separationAt = currentFont->getTextIndexXAtWidth(MutableString(lineToRender), computedConstraints.width - (border.left + border.right + padding.left + padding.right));
					lineLeft = StringTools::substring(lineToRender, separationAt + 1);
					lineToRender = StringTools::substring(lineToRender, 0, separationAt + 1);
					// determine current line width
					lineWidth = currentFont->getTextWidth(MutableString(lineToRender));
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
						float height = currentFont->getLineHeight();
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
								Style* validTextStyle = nullptr;
								if (styles.empty() == false) {
									// find style to start with, aligned with last line start
									if (textStyleIdx == -1) {
										textStyleIdx = 0;
										for (auto i = 0; i < styles.size(); i++) {
											auto textStyle = &styles[i];
											if (textStyle->startIdx > j) {
												textStyleIdx = i - 1;
												break;
											}
										}
										_startTextStyleIdx = textStyleIdx;
									}
									//
									textStyle = textStyleIdx < styles.size()?&styles[textStyleIdx]:nullptr;
									if (textStyle != nullptr && j + k + l >= textStyle->startIdx) {
										if (j + k + l >= textStyle->endIdx) {
											// invalid text style, check next text style
											textStyleIdx++;
											textStyle = textStyleIdx < styles.size()?&styles[textStyleIdx]:nullptr;
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
									currentFont->drawString(
										guiRenderer,
										left,
										top,
										textToRender,
										0,
										0,
										textStyleLast != nullptr?textStyleLast->color:color
									);
									left+= currentFont->getTextWidth(textToRender);
									textToRender.clear();
								}
								//
								textToRender+= lineToRender[l];
								textStyleLast = validTextStyle;
								currentFont = validTextStyle != nullptr && validTextStyle->font != nullptr?validTextStyle->font:font;
							}
							if (textToRender.empty() == false) {
								// flush/draw to screen
								currentFont->drawString(
									guiRenderer,
									left,
									top,
									textToRender,
									0,
									0,
									textStyleLast != nullptr?textStyleLast->color:color
								);
								left+= currentFont->getTextWidth(textToRender);
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
					y+= currentFont->getLineHeight();
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
		*/
	}
	//
	guiRenderer->bindTexture(0);
}

void GUIMultilineTextNode::unsetTextStyle(int startIdx, int endIdx) {
	// TODO: a.drewke
}

void GUIMultilineTextNode::setTextStyle(int startIdx, int endIdx, const GUIColor& color, const string& font, const string& url) {
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
