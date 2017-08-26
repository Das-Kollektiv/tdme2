// Generated from /tdme/src/tdme/gui/nodes/GUINode.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using std::vector;

using java::lang::Object;
using java::lang::String;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIRenderer;


struct default_init_tag;

/** 
 * GUI Node class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUINode
	: public virtual Object
{

public:
	typedef Object super;

public: /* protected */
	GUIScreenNode* screenNode {  };
	GUIParentNode* parentNode {  };
	String* id {  };
	GUINode_Flow* flow {  };
	GUINode_Alignments* alignments {  };
	GUINode_RequestedConstraints* requestedConstraints {  };
	GUINode_ComputedConstraints* computedConstraints {  };
	GUIColor* backgroundColor {  };
	GUINode_Padding* padding {  };
	GUINode_Border* border {  };
	GUINodeConditions* showOn {  };
	GUINodeConditions* hideOn {  };
	GUINodeController* controller {  };
	bool conditionsMet {  };
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
	void ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn);

public: /* protected */

	/** 
	 * @return node type
	 */
	virtual String* getNodeType() = 0;

public:

	/** 
	 * @return scren node
	 */
	virtual GUIScreenNode* getScreenNode();

	/** 
	 * @return parent node
	 */
	virtual GUIParentNode* getParentNode();

	/** 
	 * @return id
	 */
	virtual String* getId();

public: /* protected */

	/** 
	 * @return is content node
	 */
	virtual bool isContentNode() = 0;

public:

	/** 
	 * @return content width including border, margin
	 */
	virtual int32_t getContentWidth() = 0;

	/** 
	 * @return content height including border, margin
	 */
	virtual int32_t getContentHeight() = 0;

	/** 
	 * @return auto width if auto width requested or content width
	 */
	virtual int32_t getAutoWidth();

	/** 
	 * @return auto height if auto height requested or content height
	 */
	virtual int32_t getAutoHeight();

	/** 
	 * @return border
	 */
	virtual GUINode_Border* getBorder();

public: /* protected */

	/** 
	 * @return requested constraints
	 */
	virtual GUINode_RequestedConstraints* getRequestsConstraints();

public:

	/** 
	 * @return computed constraints
	 */
	virtual GUINode_ComputedConstraints* getComputedConstraints();

public: /* protected */

	/** 
	 * Set computed left
	 * @param left
	 */
	virtual void setLeft(int32_t left);

	/** 
	 * Set computed top
	 * @param top
	 */
	virtual void setTop(int32_t top);

	/** 
	 * Layout
	 */
	virtual void layout();

	/** 
	 * Do content alignment
	 */
	virtual void computeContentAlignment();

	/** 
	 * Layout constraint
	 * @param type
	 * @param auto value
	 * @param parent value
	 * @param value
	 * @return pixel
	 */
	virtual int32_t layoutConstraintPixel(GUINode_RequestedConstraints_RequestedConstraintsType* type, int32_t autoValue, int32_t parentValue, int32_t value);

public:

	/** 
	 * Create alignments
	 * @param horizontal
	 * @param vertical
	 * @return alignments
	 */
	static GUINode_Alignments* createAlignments(String* horizontal, String* vertical);

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
	 * Get requested constraints type
	 * @param constraint
	 * @param default constraints type
	 * @return requested constraints type
	 */
	static GUINode_RequestedConstraints_RequestedConstraintsType* getRequestedConstraintsType(String* constraint, GUINode_RequestedConstraints_RequestedConstraintsType* defaultConstraintsType);

	/** 
	 * Get requested constraints value
	 * @param constraint
	 * @param default constraints value
	 * @return requested constraints value
	 */
	static int32_t getRequestedConstraintsValue(String* constraint, int32_t defaultConstraintsValue);

	/** 
	 * Get requested pixel value
	 * @param value
	 * @param default value
	 * @return value
	 */
	static int32_t getRequestedPixelValue(String* value, int32_t defaultValue);

public:

	/** 
	 * Get color
	 * @param color
	 * @param default color
	 * @return value
	 */
	static GUIColor* getRequestedColor(String* color, GUIColor* defaultColor) /* throws(GUIParserException) */;

	/** 
	 * Create flow
	 * @param flow
	 * @return flow
	 */
	static GUINode_Flow* createFlow(String* flow);

	/** 
	 * Create border
	 * @param all border
	 * @param left
	 * @param top
	 * @param right
	 * @param bottom
	 * @param all border color
	 * @param left color
	 * @param top color
	 * @param right color
	 * @param bottom color
	 * @return border
	 */
	static GUINode_Border* createBorder(String* allBorder, String* left, String* top, String* right, String* bottom, String* allBorderColor, String* leftColor, String* topColor, String* rightColor, String* bottomColor) /* throws(GUIParserException) */;

	/** 
	 * Create padding
	 * @param all padding
	 * @param left
	 * @param top
	 * @param right
	 * @param bottom
	 * @return padding
	 */
	static GUINode_Padding* createPadding(String* allPadding, String* left, String* top, String* right, String* bottom) /* throws(GUIParserException) */;

	/** 
	 * Create conditions
	 * @param conditions
	 */
	static GUINodeConditions* createConditions(String* conditions);

public: /* protected */

	/** 
	 * @return conditions met
	 */
	virtual bool checkConditions();

public:

	/** 
	 * Dispose node
	 */
	virtual void dispose();

	/** 
	 * Set conditions met for the while tree
	 */
	virtual void setConditionsMet();

	/** 
	 * Render
	 * @param gui renderer
	 * @param floating nodes
	 */
	virtual void render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes);

public: /* protected */

	/** 
	 * @return compute parent children render offset X total
	 */
	virtual float computeParentChildrenRenderOffsetXTotal();

	/** 
	 * @return compute children render offset Y total
	 */
	virtual float computeParentChildrenRenderOffsetYTotal();

public:

	/** 
	 * Is event belonging to node
	 * @param event
	 * @param x,y position in node coordinate system 
	 * @return boolean
	 */
	virtual bool isEventBelongingToNode(GUIMouseEvent* event, int32_tArray* position);

	/** 
	 * Is event belonging to node
	 * @param event
	 * @return boolean
	 */
	virtual bool isEventBelongingToNode(GUIMouseEvent* event);

	/** 
	 * Get event off node relative position
	 * @param event
	 * @param x,y position (will return x = 0 if in node on x axis, will return x < 0  (-pixel) if on the left of element, x > 0 (+pixel) if on the right of element, y behaves analogous to x)  
	 * @return void
	 */
	virtual void getEventOffNodeRelativePosition(GUIMouseEvent* event, int32_tArray* position);

	/** 
	 * @return first parent node in tree with controller node attached
	 */
	virtual GUIParentNode* getParentControllerNode();

	/** 
	 * Handle mouse event
	 * @param event
	 */
	virtual void handleMouseEvent(GUIMouseEvent* event);

	/** 
	 * Handle keyboard event
	 * @param event
	 */
	virtual void handleKeyboardEvent(GUIKeyboardEvent* event);

	/** 
	 * Tick method will be executed once per frame
	 */
	virtual void tick();

	/** 
	 * @return controller
	 */
	virtual GUINodeController* getController();

	/** 
	 * Set up node controller
	 * @param controller
	 */
	virtual void setController(GUINodeController* controller);

	/** 
	 * Scroll to node Y
	 */
	virtual void scrollToNodeY();

	/** 
	 * Scroll to node Y
	 * @param stop at node to node
	 */
	virtual void scrollToNodeY(GUIParentNode* toNode);

	/** 
	 * Scroll to node X
	 */
	virtual void scrollToNodeX();

	/** 
	 * Scroll to node X
	 * @param stop at node to node
	 */
	virtual void scrollToNodeX(GUIParentNode* toNode);

public: /* protected */

	/** 
	 * Compute indent string
	 * @param ident
	 * @return indented string
	 */
	virtual String* indent(int32_t indent);

public:
	String* toString() override;

public: /* protected */

	/** 
	 * Indented string representation
	 * @param ident
	 * @return string representation
	 */
	virtual String* toString(int32_t indent);

	// Generated
	GUINode(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn);
protected:
	GUINode(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUINode_Flow;
	friend class GUINode_AlignmentHorizontal;
	friend class GUINode_AlignmentVertical;
	friend class GUINode_Alignments;
	friend class GUINode_RequestedConstraints;
	friend class GUINode_RequestedConstraints_RequestedConstraintsType;
	friend class GUINode_ComputedConstraints;
	friend class GUINode_Padding;
	friend class GUINode_Border;
};
