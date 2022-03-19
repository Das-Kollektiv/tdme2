#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Exception.h>
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
using tdme::utilities::MutableString;

/**
 * GUI styled text node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIStyledTextNode final
	: public GUINode
{
	friend class tdme::gui::GUIParser;
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
	};

	bool preformatted;
	GUIFont* font { nullptr };
	GUIColor color;
	MutableString text;

	int autoWidth;
	int autoHeight;

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

	string spaceString { " " };
	string tabString3 { "   " };
	string tabString4 { "    " };
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
	 * @return URL areas
	 */
	inline const vector<URLArea>& getURLAreas() {
		return urlAreas;
	}

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
	 * @return text
	 */
	inline const MutableString& getText() const {
		return text;
	}

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
	 */
	void setImage(int idx, const string& image, const string& url = string(), int width = -1, int height = -1);

};
