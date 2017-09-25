// Generated from /tdme/src/tdme/gui/nodes/GUITextNode.java

#pragma once

#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINode.h>

using std::vector;
using std::wstring;

using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIFont;
using tdme::gui::renderer::GUIRenderer;
using tdme::utils::MutableString;


struct default_init_tag;

/** 
 * GUI text node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUITextNode final
	: public GUINode
{

public:
	typedef GUINode super;

private:
	GUIFont* font {  };
	GUIColor* color {  };
	MutableString* text {  };
protected:

	/** 
	 * Constructor
	 * @param screen node
	 * @param parent mode
	 * @param id
	 * @param flow
	 * @param alignments
	 * @param requested constraints
	 * @param border
	 * @param padding
	 * @param show on
	 * @param hide on
	 * @param font
	 * @param color
	 * @param text
	 * @throws Exception
	 */
	void ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, const wstring& font, const wstring& color, MutableString* text) /* throws(Exception) */;

public: /* protected */

	/** 
	 * @return node type
	 */
	const wstring getNodeType() override;
	bool isContentNode() override;

public:
	int32_t getContentWidth() override;
	int32_t getContentHeight() override;

	/** 
	 * @return text
	 */
	MutableString* getText();
	void dispose() override;
	void render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes) override;

	// Generated
	GUITextNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn, const wstring& font, const wstring& color, MutableString* text);
protected:
	GUITextNode(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
