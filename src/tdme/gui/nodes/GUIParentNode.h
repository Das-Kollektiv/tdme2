#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/gui/nodes/GUINode.h>

using std::vector;
using std::string;

using tdme::gui::nodes::GUINode;
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

/** 
 * A parent node supporting child notes
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIParentNode
	: public GUINode
{
	friend class tdme::gui::GUIParser;
	friend class GUIElementNode;
	friend class GUILayoutNode;
	friend class GUINode;
	friend class GUIScreenNode;
	friend class GUIHorizontalScrollbarInternalController;
	friend class GUIVerticalScrollbarInternalController;
	friend class GUIParentNode_Overflow;

protected:
	vector<GUINode*> subNodes {  };
	GUIParentNode_Overflow* overflowX {  };
	GUIParentNode_Overflow* overflowY {  };
	float childrenRenderOffsetX {  };
	float childrenRenderOffsetY {  };

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

	GUIParentNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const string& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn);

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
	virtual void replaceSubNodes(const string& xml, bool resetScrollOffsets) /* throws(Exception) */;

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
	static GUIParentNode_Overflow* createOverflow(const string& overflow) throw (GUIParserException);

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
	static GUINode_RequestedConstraints* createRequestedConstraints(const string& left, const string& top, const string& width, const string& height);

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

private:
	/**
	 * Get child controller nodes internal
	 * @param child controller nodes
	 */
	void getChildControllerNodesInternal(vector<GUINode*>* childControllerNodes);
};
