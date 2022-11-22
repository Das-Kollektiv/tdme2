#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>

using std::string;

using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;

/**
 * GUI input internal node
 * @author Andreas Drewke
 */
class tdme::gui::nodes::GUIInputInternalNode final
	: public GUINode
{
	friend class tdme::gui::GUIParser;

public:

	/**
	 * Create max length
	 * @param s s
	 * @return max length
	 */
	static int createMaxLength(const string& s);

private:
	GUIFont* font { nullptr };
	GUIColor color;
	GUIColor colorDisabled;
	MutableString text;
	int maxLength;

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
	 * @param tooltip tooltip
	 * @param font font
	 * @param size font size
	 * @param color color
	 * @param colorDisabled color disabled
	 * @param text text
	 * @param maxLength max length
	 */
	GUIInputInternalNode(
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
		const string& colorDisabled,
		const MutableString& text,
		int maxLength
	);

	// overridden methods
	const string getNodeType() override;
	bool isContentNode() override;

public:
	// overridden methods
	int getContentWidth() override;
	int getContentHeight() override;
	void dispose() override;
	void render(GUIRenderer* guiRenderer) override;

	/**
	 * @return font
	 */
	inline GUIFont* getFont() {
		return font;
	}

	/**
	 * @return text
	 */
	inline MutableString& getText() {
		return text;
	}

	/**
	 * @return max length
	 */
	inline int getMaxLength() {
		return maxLength;
	}

};
