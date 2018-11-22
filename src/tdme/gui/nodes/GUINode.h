#pragma once

#include <array>
#include <string>
#include <vector>
#include <set>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINode_Alignments.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Flow.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUINode_Flow.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::array;
using std::vector;
using std::set;
using std::string;

using tdme::engine::fileio::textures::Texture;
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

/** 
 * GUI Node class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUINode
{
	friend class GUIElementNode;
	friend class GUIImageNode;
	friend class GUILayoutNode;
	friend class GUIParentNode;
	friend class GUIScreenNode;
	friend class GUIHorizontalScrollbarInternalController;
	friend class GUIVerticalScrollbarInternalController;
	friend class GUIInputInternalController;
	friend class GUINodeConditions;
	friend class GUINode_Flow;
	friend class GUINode_AlignmentHorizontal;
	friend class GUINode_AlignmentVertical;
	friend class GUINode_RequestedConstraints;
	friend class GUINode_RequestedConstraints_RequestedConstraintsType;

protected:
	GUIScreenNode* screenNode {  };
	GUIParentNode* parentNode {  };
	string id {  };
	GUINode_Flow* flow;
	GUINode_Alignments alignments;
	GUINode_RequestedConstraints requestedConstraints;
	GUINode_ComputedConstraints computedConstraints;
	GUIColor backgroundColor;
	Texture* backgroundTexture;
	int32_t backgroundTextureId;
	GUINode_Scale9Grid backgroundImageScale9Grid;
	GUINode_Padding padding;
	GUINode_Border border;
	GUINodeConditions showOn;
	GUINodeConditions hideOn;
	GUINodeController* controller {  };
	bool conditionsMet {  };

	/** 
	 * @return node type
	 */
	virtual const string getNodeType() = 0;

	/**
	 * @return is content node
	 */
	virtual bool isContentNode() = 0;

	/**
	 * @return requested constraints
	 */
	virtual GUINode_RequestedConstraints& getRequestsConstraints();

	/**
	 * Set computed left
	 * @param left left
	 */
	virtual void setLeft(int32_t left);

	/**
	 * Set computed top
	 * @param top top
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
	 * @param type type
	 * @param autoValue auto value
	 * @param parentValue parent value
	 * @param value value
	 * @return pixel
	 */
	virtual int32_t layoutConstraintPixel(GUINode_RequestedConstraints_RequestedConstraintsType* type, int32_t autoValue, int32_t parentValue, int32_t value);

	/**
	 * Get requested constraints type
	 * @param constraint constraint
	 * @param defaultConstraintsType default constraints type
	 * @return requested constraints type
	 */
	static GUINode_RequestedConstraints_RequestedConstraintsType* getRequestedConstraintsType(const string& constraint, GUINode_RequestedConstraints_RequestedConstraintsType* defaultConstraintsType);

	/**
	 * Get requested constraints value
	 * @param constraint constraint
	 * @param defaultConstraintsValue default constraints value
	 * @return requested constraints value
	 */
	static int32_t getRequestedConstraintsValue(const string& constraint, int32_t defaultConstraintsValue);

	/**
	 * Get requested pixel value
	 * @param value value
	 * @param defaultValue default value
	 * @return value
	 */
	static int32_t getRequestedPixelValue(const string& value, int32_t defaultValue);

	/**
	 * Check if conditions are met
	 * @param elementNode element node
	 * @return conditions met
	 */
	virtual bool checkConditions(GUIElementNode* elementNode = nullptr);

	/**
	 * @return compute parent children render offset X total
	 */
	virtual float computeParentChildrenRenderOffsetXTotal();

	/**
	 * @return compute children render offset Y total
	 */
	virtual float computeParentChildrenRenderOffsetYTotal();

	/**
	 * Public constructor
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
	 */
	GUINode(
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
		const GUINodeConditions& hideOn
	);

	/**
	 * Destructor
	 */
	virtual ~GUINode();

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
	virtual const string& getId();

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
	virtual GUINode_Border& getBorder();

	/**
	 * @return padding
	 */
	virtual GUINode_Padding& getPadding();

	/**
	 * @return computed constraints
	 */
	virtual GUINode_ComputedConstraints& getComputedConstraints();

	/** 
	 * Create alignments
	 * @param horizontal horizontal
	 * @param vertical vertical
	 * @return alignments
	 */
	static GUINode_Alignments createAlignments(const string& horizontal, const string& vertical);

	/** 
	 * Create requested constraints
	 * @param left left
	 * @param top top
	 * @param width width
	 * @param height height
	 * @return requested constraints
	 */
	static GUINode_RequestedConstraints createRequestedConstraints(const string& left, const string& top, const string& width, const string& height);

	/** 
	 * Get color
	 * @param color color
	 * @param defaultColor default color
	 * @return value
	 */
	static GUIColor getRequestedColor(const string& color, const GUIColor& defaultColor) throw (GUIParserException);

	/** 
	 * Create flow
	 * @param flow flow
	 * @return flow
	 */
	static GUINode_Flow* createFlow(const string& flow);

	/** 
	 * Create border
	 * @param allBorder all border
	 * @param left left
	 * @param top top
	 * @param right right
	 * @param bottom bottom
	 * @param allBorderColor all border color
	 * @param leftColor left color
	 * @param topColor top color
	 * @param rightColor right color
	 * @param bottomColor bottom color
	 * @return border
	 */
	static GUINode_Border createBorder(const string& allBorder, const string& left, const string& top, const string& right, const string& bottom, const string& allBorderColor, const string& leftColor, const string& topColor, const string& rightColor, const string& bottomColor) throw(GUIParserException);

	/** 
	 * Create padding
	 * @param allPadding all padding
	 * @param left left
	 * @param top top
	 * @param right right
	 * @param bottom bottom
	 * @return padding
	 */
	static GUINode_Padding createPadding(const string& allPadding, const string& left, const string& top, const string& right, const string& bottom) throw(GUIParserException);

	/** 
	 * Create scale 9 grid
	 * @param all all
	 * @param left left
	 * @param top top
	 * @param right right
	 * @param bottom bottom
	 * @return scale 9 grid
	 */
	static GUINode_Scale9Grid createScale9Grid(const string& all, const string& left, const string& top, const string& right, const string& bottom) throw(GUIParserException);

	/**
	 * Create conditions
	 * @param conditions conditions
	 */
	static GUINodeConditions createConditions(const string& conditions);

	/** 
	 * Dispose node
	 */
	virtual void dispose();

	/** 
	 * Set conditions met for this node and its subnodes
	 */
	virtual void setConditionsMet();

	/**
	 * Render
	 * @param guiRenderer gui renderer
	 * @param floatingNodes floating nodes
	 */
	virtual void render(GUIRenderer* guiRenderer, vector<GUINode*>& floatingNodes);

	/** 
	 * Is event belonging to node
	 * @param event event
	 * @param position x,y position in node coordinate system 
	 * @return boolean
	 */
	virtual bool isEventBelongingToNode(GUIMouseEvent* event, array<float, 2>& position);

	/** 
	 * Is event belonging to node
	 * @param event event
	 * @return boolean
	 */
	virtual bool isEventBelongingToNode(GUIMouseEvent* event);

	/** 
	 * Get event off node relative position
	 * 	TODO: use Vector2 instead of array<float, 2>
	 * @param event event
	 * @param position x,y position (will return x = 0 if in node on x axis, will return x < 0  (-pixel) if on the left of element, x > 0 (+pixel) if on the right of element, y behaves analogous to x)  
	 * @return void
	 */
	virtual void getEventOffNodeRelativePosition(GUIMouseEvent* event, array<float, 2>& position);

	/** 
	 * @return first parent node in tree with controller node attached
	 */
	virtual GUIParentNode* getParentControllerNode();

	/**
	 * Determine mouse event nodes
	 * @param event event
	 * @param eventNodeIds event node ids
	 */
	virtual void determineMouseEventNodes(GUIMouseEvent* event, set<string>& eventNodeIds); // TODO: std container: maybe use call by reference

	/**
	 * Handle keyboard event
	 * @param event event
	 */
	virtual void handleKeyboardEvent(GUIKeyboardEvent* event);

	/** 
	 * @return controller
	 */
	virtual GUINodeController* getController();

	/** 
	 * Set up node controller
	 * @param controller controller
	 */
	virtual void setController(GUINodeController* controller);

	/** 
	 * Scroll to node Y
	 */
	virtual void scrollToNodeY();

	/** 
	 * Scroll to node Y
	 * @param toNode stop at node to node
	 */
	virtual void scrollToNodeY(GUIParentNode* toNode);

	/** 
	 * Scroll to node X
	 */
	virtual void scrollToNodeX();

	/** 
	 * Scroll to node X
	 * @param toNode stop at node to node
	 */
	virtual void scrollToNodeX(GUIParentNode* toNode);

	/**
	 * Dump node
	 * @param node node to dump
	 * @param indent indention depth
	 */
	static void dumpNode(GUINode* node, int indent = 0);
};
