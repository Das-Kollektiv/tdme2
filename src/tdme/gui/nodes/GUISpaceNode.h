// Generated from /tdme/src/tdme/gui/nodes/GUISpaceNode.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINode.h>

using std::wstring;

using tdme::gui::nodes::GUINode;
using java::lang::String;
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


struct default_init_tag;

/** 
 * GUI space node
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUISpaceNode final
	: public GUINode
{

public:
	typedef GUINode super;
protected:

	/** 
	 * Constructor
	 * @param screen node
	 * @param parent node
	 * @param id
	 * @param flow
	 * @param alignments
	 * @param requested constraints
	 * @param border
	 * @param padding
	 * @param show on
	 * @param hide on
	 */
	void ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn);

public: /* protected */

	/** 
	 * @return node type
	 */
	String* getNodeType() override;
	bool isContentNode() override;

public:
	int32_t getContentWidth() override;
	int32_t getContentHeight() override;

	/** 
	 * Create requested constraints
	 * @param left
	 * @param top
	 * @param width
	 * @param height
	 * @return requested constraints
	 */
	static GUINode_RequestedConstraints* createRequestedConstraints(const wstring& left, const wstring& top, const wstring& width, const wstring& height);
	void dispose() override;
	void render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes) override;

	// Generated
	GUISpaceNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn);
protected:
	GUISpaceNode(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
