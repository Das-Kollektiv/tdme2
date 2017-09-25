// Generated from /tdme/src/tdme/gui/nodes/GUIParentNode.java

#pragma once

#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/gui/nodes/GUINode.h>

using std::vector;
using std::wstring;

using tdme::gui::nodes::GUINode;
using java::lang::String;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::GUIParserException;


struct default_init_tag;

/** 
 * A parent node supporting child notes
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIParentNode
	: public GUINode
{

public:
	typedef GUINode super;

public: /* protected */
	vector<GUINode*> subNodes {  };
	GUIParentNode_Overflow* overflowX {  };
	GUIParentNode_Overflow* overflowY {  };
	float childrenRenderOffsetX {  };
	float childrenRenderOffsetY {  };
protected:

	/** 
	 * Constructor
	 * @param screen node
	 * @param parent node
	 * @param id
	 * @param flow
	 * @param overflow x
	 * @param overflow y
	 * @param alignments
	 * @param requested constraints
	 * @oaram background color
	 * @param border
	 * @param padding
	 * @param show on
	 * @param hide on 
	 */
	void ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn) /* throws(GUIParserException) */;

public:

	/** 
	 * Clear sub nodes
	 */
	virtual void clearSubNodes();

	/** 
	 * Replace sub nodes with given XML
	 * @param xml
	 * @param reset scroll offsets
	 */
	virtual void replaceSubNodes(const wstring& xml, bool resetScrollOffsets) /* throws(Exception) */;

	/** 
	 * Add sub node
	 * @param node
	 */
	virtual void addSubNode(GUINode* node) throw (GUIParserException);

	/** 
	 * @return overflow x
	 */
	virtual GUIParentNode_Overflow* getOverflowX();

	/** 
	 * @return overflow y
	 */
	virtual GUIParentNode_Overflow* getOverflowY();

	/** 
	 * Create over flow
	 * @param over flow
	 * @return over flow
	 * @throws gui parser exception
	 */
	static GUIParentNode_Overflow* createOverflow(String* overflow) throw (GUIParserException);

	/** 
	 * @return children render offset x
	 */
	virtual float getChildrenRenderOffsetX();

	/** 
	 * Set children render offset x
	 * @param children render offset x
	 */
	virtual void setChildrenRenderOffsetX(float childrenRenderOffSetX);

	/** 
	 * @return children render offset y
	 */
	virtual float getChildrenRenderOffsetY();

	/** 
	 * Set children render offset y
	 * @param children render offset y
	 */
	virtual void setChildrenRenderOffsetY(float childrenRenderOffSetY);

	/** 
	 * Create requested constraints
	 * @param left
	 * @param top
	 * @param width
	 * @param height
	 * @return requested constraints
	 */
	static GUINode_RequestedConstraints* createRequestedConstraints(String* left, String* top, String* width, String* height);

public: /* protected */

	/** 
	 * Layout
	 */
	void layout() override;

	/** 
	 * Layout sub nodes
	 */
	virtual void layoutSubNodes();

	/** 
	 * Compute horizontal children alignment
	 */
	virtual void computeHorizontalChildrenAlignment();

	/** 
	 * Compute vertical children alignment
	 */
	virtual void computeVerticalChildrenAlignment();

private:

	/** 
	 * Get child controller nodes internal
	 * @param child controller nodes
	 */
	void getChildControllerNodesInternal(vector<GUINode*>* childControllerNodes);

public:

	/** 
	 * Get child controller nodes
	 * @param child controller nodes
	 */
	virtual void getChildControllerNodes(vector<GUINode*>* childControllerNodes);
	void dispose() override;
	void setConditionsMet() override;
	void render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes) override;
	void handleMouseEvent(GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUIKeyboardEvent* event) override;
	void tick() override;
	String* toString() override;

public: /* protected */
	String* toString(int32_t indent) override;

	// Generated
	GUIParentNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn);
protected:
	GUIParentNode(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUIParentNode_Overflow;
};
