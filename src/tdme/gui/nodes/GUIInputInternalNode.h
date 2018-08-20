#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/MutableString.h>
#include <tdme/gui/nodes/GUINode.h>

using std::string;

using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIColor;
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
using tdme::utils::Exception;
using tdme::utils::MutableString;

/** 
 * GUI input internal node
 * @author Andreas Drewke
 * @version $Id$
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
	static int32_t createMaxLength(const string& s);

private:
	GUIFont* font {  };
	GUIColor color;
	GUIColor colorDisabled;
	MutableString text {  };
	int32_t maxLength {  };

protected:

	/** 
	 * @return node type
	 */
	const string getNodeType() override;
	bool isContentNode() override;

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
	 * @param border border
	 * @param padding padding
	 * @param showOn show on
	 * @param hideOn hide on
	 * @param font font
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
		const GUINode_Border& border,
		const GUINode_Padding& padding,
		const GUINodeConditions& showOn,
		const GUINodeConditions& hideOn,
		const string& font,
		const string& color,
		const string& colorDisabled,
		const MutableString& text,
		int32_t maxLength
	) throw(Exception);

public:
	int32_t getContentWidth() override;
	int32_t getContentHeight() override;

	/** 
	 * @return font
	 */
	GUIFont* getFont();

	/** 
	 * @return text
	 */
	MutableString& getText();

	/** 
	 * @return max length
	 */
	int32_t getMaxLength();
	void dispose() override;
	void render(GUIRenderer* guiRenderer, vector<GUINode*>& floatingNodes) override;

};
