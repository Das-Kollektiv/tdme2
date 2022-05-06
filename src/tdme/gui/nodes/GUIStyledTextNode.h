#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>

using std::string;
using std::vector;

using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;
using tdme::utilities::Exception;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;

/**
 * GUI styled text node
 * @author Andreas Drewke
 */
class tdme::gui::nodes::GUIStyledTextNode final
	: public GUINode
{
	friend class tdme::gui::GUIParser;
	friend class tdme::gui::elements::GUIStyledInputController;
	friend class tdme::gui::nodes::GUIStyledTextNodeController;

private:
	struct TextStyle {
		int startIdx;
		int endIdx;
		GUIColor color;
		GUIFont* font;
		string url;
		Texture* image;
		int textureId;
		int width;
		int height;
		GUIColor effectColorMul;
		GUIColor effectColorAdd;
	};

	bool preformatted;
	GUIFont* font { nullptr };
	GUIColor color;
	MutableString text;

	int autoWidth { 0 };
	int autoHeight { 0 };

	bool parentOffsetsChanged;
	float parentXOffsetLast;
	float parentYOffsetLast;
	int charStartIdx;
	int charEndIdx;
	int startRenderY;
	int widthLast;
	int heightLast;

	vector<TextStyle> styles;
	int startTextStyleIdx { -1 };

	struct Line {
		int idx;
		float width;
		float height;
		float lineHeight;
		float baseLine;
		bool spaceWrap;
	};

	int tabSize { 4 };
	string spaceString { " " };
	string newLine { "\n" };
	string line;
	vector<int> lineCharIdxs;
	vector<Line> lineConstraints;

	struct URLArea {
		int left;
		int top;
		int width;
		int height;
		string url;
	};
	vector<URLArea> urlAreas;

	static constexpr int MOUSEPOSITION_NONE { Integer::MIN_VALUE };
	int indexPositionX { 0 };
	int indexPositionY { 0 };
	int indexMousePositionX { MOUSEPOSITION_NONE };
	int indexMousePositionY { MOUSEPOSITION_NONE };
	int selectionIndexMousePositionX { MOUSEPOSITION_NONE };
	int selectionIndexMousePositionY { MOUSEPOSITION_NONE };
	GUIColor selectionTextColor { "#a0a0a0" };
	GUIColor selectionBackgroundColor { "#5050d0" };

	bool editMode { false };

	/**
	 * @return edit mode
	 */
	inline bool isEditMode() {
		return editMode;
	}

	/**
	 * @return edit mode
	 */
	inline void setEditMode(bool editMode) {
		this->editMode = editMode;
	}

	/**
	 * Unset index mouse position
	 */
	void unsetIndexMousePosition();

	/**
	 * Set index mouse position
	 */
	void setIndexMousePosition(int x, int y);

	/**
	 * Unset selection index mouse position
	 */
	void unsetSelectionIndexMousePosition();

	/**
	 * Set selection index mouse position
	 */
	void setSelectionIndexMousePosition(int x, int y);

	/**
	 * @return URL areas
	 */
	inline const vector<URLArea>& getURLAreas() {
		return urlAreas;
	}

	/**
	 * Set scroll to index
	 */
	void scrollToIndex(int index);

	/**
	 * Set scroll to index
	 */
	void scrollToIndex();

	/**
	 * Set scroll to selection index
	 */
	void scrollToSelectionIndex();

	/**
	 * Do page up
	 * @return cursor index
	 */
	int doPageUp();

	/**
	 * Do page down
	 * @return cursor index
	 */
	int doPageDown();

	/**
	 * Get text style for
	 * @param lineCharIdxs line character indices
	 * @param lineCharIdx line character idx
	 * @param textStyleIdx text style to start looking up with, will also be written
	 * @return text style
	 */
	inline TextStyle* getTextStyle(const vector<int>& lineCharIdxs, int lineCharIdx, int& textStyleIdx) {
		if (styles.empty() == true) return nullptr;
		TextStyle* textStyle = nullptr;
		// find style to start with, aligned with last line start, if we do not have a start yet
		if (textStyleIdx == -1) {
			textStyleIdx = 0;
			for (auto l = 0; l < styles.size(); l++) {
				auto textStyle = &styles[l];
				if (textStyle->startIdx > lineCharIdxs[lineCharIdx]) {
					textStyleIdx = l - 1;
					break;
				}
			}
		}
		// ok proceed to find correct style for character in text, based on our text style index
		auto _textStyle = textStyleIdx < styles.size()?&styles[textStyleIdx]:nullptr;
		if (_textStyle != nullptr && lineCharIdxs[lineCharIdx] >= _textStyle->startIdx) {
			if (lineCharIdxs[lineCharIdx] > _textStyle->endIdx) {
				// invalid text style, check next text style
				textStyleIdx++;
				_textStyle = textStyleIdx < styles.size()?&styles[textStyleIdx]:nullptr;
				if (_textStyle != nullptr && lineCharIdxs[lineCharIdx] >= _textStyle->startIdx) {
					if (lineCharIdxs[lineCharIdx] <= _textStyle->endIdx) {
						// valid text style
						textStyle = _textStyle;
					}
				}
			} else
			if (lineCharIdxs[lineCharIdx] <= _textStyle->endIdx) {
				// valid text style
				textStyle = _textStyle;
			}
		}
		return textStyle;
	}

	/**
	 * Determine next line constraints
	 * @param i current loop index
	 * @param charEndIdx character end index
	 * @param textStyleIdx text style index to start with
	 */
	void determineNextLineConstraints(int& i, int charEndIdx, int textStyleIdx);

protected:
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
	 * @param preformatted preformatted
	 * @param font font
	 * @param color color
	 * @param text text
	 * @throws tdme::gui::GUIParserException
	 */
	GUIStyledTextNode(
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
	);

	// overridden methods
	const string getNodeType() override;
	bool isContentNode() override;

public:
	// overridden methods
	int getContentWidth() override;
	int getContentHeight() override;
	void computeContentAlignment() override;
	void dispose() override;
	void render(GUIRenderer* guiRenderer) override;

	/**
	 * @return index position x
	 */
	int getIndexPositionX() {
		return indexPositionX;
	}

	/**
	 * @return index position x
	 */
	int getIndexPositionY() {
		return indexPositionY;
	}

	/**
	 * @return text
	 */
	inline const MutableString& getText() const {
		return text;
	}

	/**
	 * Get previous new line
	 * @param index index
	 */
	inline int getPreviousNewLine(int index) {
		// find index of previous newline and store difference
		auto previousNewLineIndex = index;
		while (previousNewLineIndex >= 0 && text.charAt(previousNewLineIndex) != '\n') previousNewLineIndex--;
		previousNewLineIndex = Math::max(previousNewLineIndex, 0);
		return previousNewLineIndex;
	}

	/**
	 * Get next newline
	 * @param index index
	 */
	inline int getNextNewLine(int index) {
		// find index of next newline
		auto nextNewLineIndex = index;
		while (nextNewLineIndex < text.size() && text.charAt(nextNewLineIndex) != '\n') nextNewLineIndex++;
		nextNewLineIndex = Math::min(nextNewLineIndex, text.size() - 1);
		return nextNewLineIndex;
	}

	/**
	 * Get previous delimiter
	 * @param index index
	 * @param delimiters delimiters
	 */
	inline int getPreviousDelimiter(int index, const string& delimiters) {
		// find index of previous newline and store difference
		auto previousDelimiterIndex = index;
		while (previousDelimiterIndex >= 0 && delimiters.find(text.charAt(previousDelimiterIndex)) == string::npos) previousDelimiterIndex--;
		previousDelimiterIndex = Math::max(previousDelimiterIndex, 0);
		return previousDelimiterIndex;
	}

	/**
	 * Get next delimiter
	 * @param index index
	 * @param delimiters
	 */
	inline int getNextDelimiter(int index, const string& delimiters) {
		// find index of next newline
		auto nextDelimiterIndex = index;
		while (nextDelimiterIndex < text.size() && delimiters.find(text.charAt(nextDelimiterIndex)) == string::npos) nextDelimiterIndex++;
		nextDelimiterIndex = Math::min(nextDelimiterIndex, text.size() - 1);
		return nextDelimiterIndex;
	}

	/**
	 * @return text size
	 */
	inline int getTextSize() {
		return text.size();
	}

	/**
	 * Remove characters at idx with given length
	 * @param idx idx
	 * @param count length
	 * @return this mutable string
	 */
	void removeText(int32_t idx, int32_t count);

	/**
	 * Insert character c at idx
	 * @param idx index
	 * @param c char
	 * @return this mutable string
	 */
	void insertText(int32_t idx, char c);

	/**
	 * Insert string at idx
	 * @param idx index
	 * @param s string
	 * @return this mutable string
	 */
	void insertText(int32_t idx, const string& s);

	/**
	 * Unset/dispose styles
	 */
	void unsetStyles();

	/**
	 * Set text
	 * @param text text
	 */
	void setText(const MutableString& text);

	/**
	 * Unset text style
	 * @param startIdx text start index
	 * @param endIdx text end index
	 */
	void unsetTextStyle(int startIdx, int endIdx);

	/**
	 * Set text style
	 * @param startIdx text start index
	 * @param endIdx text end index
	 * @param color color
	 * @param font font
	 * @param url url
	 */
	void setTextStyle(int startIdx, int endIdx, const GUIColor& color, const string& font = string(), const string& url = string());

	/**
	 * Set text style
	 * @param startIdx text start index
	 * @param endIdx text end index
	 * @param font font
	 * @param url url
	 */
	void setTextStyle(int startIdx, int endIdx, const string& font, const string& url = string());

	/**
	 * Set image
	 * @param idx index
	 * @param image image
	 * @param url url
	 * @param width width or -1 for original image width
	 * @param height height or -1 for original image height
	 * @param horizontalScale horizontal scale as factor
	 * @param verticalScale vertical scale as factor
	 * @param effectColorMul effect color mul
	 * @param effectColorAdd effect color add
	 */
	void setImage(
		int idx,
		const string& image,
		const string& url = string(),
		int width = -1,
		int height = -1,
		float horizontalScale = 1.0f,
		float verticalScale = 1.0f,
		const GUIColor& effectColorMul = GUIColor::GUICOLOR_EFFECT_COLOR_MUL,
		const GUIColor& effectColorAdd = GUIColor::GUICOLOR_EFFECT_COLOR_ADD
	);

};
