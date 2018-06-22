#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/gui/nodes/GUINode.h>

using std::string;

using tdme::gui::nodes::GUINode;
using tdme::engine::fileio::textures::Texture;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIRenderer;

/** 
 * GUI image node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIImageNode final
	: public GUINode
{
	friend class tdme::gui::GUIParser;

private:
	Texture* texture {  };
	int32_t textureId {  };
	GUIColor effectColorMul;
	GUIColor effectColorAdd;

protected:
	/** 
	 * @return node type
	 */
	const string getNodeType() override;
	bool isContentNode() override;

	/**
	 * Constructor
	 * @param screen node
	 * @param parent node
	 * @param id
	 * @param flow
	 * @param alignments
	 * @param requested constraints
	 * @param background color
	 * @param background image
	 * @param border
	 * @param padding
	 * @param show on
	 * @param hide on
	 * @param src
	 * @param effect color mul
	 * @param effect color add
	 */
	GUIImageNode(
		GUIScreenNode* screenNode,
		GUIParentNode* parentNode,
		const string& id,
		GUINode_Flow* flow,
		const GUINode_Alignments& alignments,
		const GUINode_RequestedConstraints& requestedConstraints,
		const GUIColor& backgroundColor,
		const string& backgroundImage,
		const GUINode_Border& border,
		const GUINode_Padding& padding,
		const GUINodeConditions& showOn,
		const GUINodeConditions& hideOn,
		const string& src,
		const GUIColor& effectColorMul,
		const GUIColor& effectColorAdd
	) throw(GUIParserException);

public:
	int32_t getContentWidth() override;
	int32_t getContentHeight() override;
	void dispose() override;
	void render(GUIRenderer* guiRenderer, vector<GUINode*>& floatingNodes) override;

private:
	void init();
};
