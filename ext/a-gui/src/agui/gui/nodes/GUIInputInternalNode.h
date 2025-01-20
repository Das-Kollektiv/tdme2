#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/renderer/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>
#include <agui/utilities/Exception.h>
#include <agui/utilities/MutableString.h>

using std::string;

// namespaces
namespace agui {
namespace gui {
namespace nodes {
	using ::agui::gui::renderer::GUIFont;
	using ::agui::gui::renderer::GUIRenderer;
	using ::agui::utilities::Exception;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI input internal node
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUIInputInternalNode final
	: public GUINode
{
	friend class agui::gui::GUIParser;

public:

	/**
	 * Create max length
	 * @param s s
	 * @returns max length
	 */
	static int createMaxLength(const string& s);

private:
	GUIFont* font { nullptr };
	GUIColor color;
	GUIColor colorDisabled;
	MutableString text;
	int maxLength;

protected:
	// forbid class copy
	FORBID_CLASS_COPY(GUIInputInternalNode)

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
	 * @returns font
	 */
	inline GUIFont* getFont() {
		return font;
	}

	/**
	 * @returns text
	 */
	inline MutableString& getText() {
		return text;
	}

	/**
	 * @returns max length
	 */
	inline int getMaxLength() {
		return maxLength;
	}

};
