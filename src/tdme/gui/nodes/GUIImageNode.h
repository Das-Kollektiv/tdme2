#pragma once

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINode.h>

using std::array;
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
	array<float, 4> color {  };
	GUIColor* effectColorMul {  };
	GUIColor* effectColorAdd {  };

protected:
	/** 
	 * @return node type
	 */
	const string getNodeType() override;
	bool isContentNode() override;
	GUIImageNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const string& id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, const string& src, GUIColor* effectColorMul, GUIColor* effectColorAdd);

public:
	int32_t getContentWidth() override;
	int32_t getContentHeight() override;
	void dispose() override;
	void render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes) override;

private:
	void init();
};
