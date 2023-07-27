#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unordered_set;
using std::vector;

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::GUIParserException;

/**
 * GUI parent node base class thats supporting child nodes
 * @author Andreas Drewke
 */
class tdme::gui::nodes::GUIParentNode
	: public GUINode
{
	friend class tdme::gui::GUI;
	friend class tdme::gui::GUIParser;
	friend class GUIElementNode;
	friend class GUILayerNode;
	friend class GUILayoutNode;
	friend class GUINode;
	friend class GUINodeConditions;
	friend class GUIScreenNode;
	friend class GUITableNode;
	friend class GUITableCellNode;
	friend class GUITableRowNode;
	friend class GUIHorizontalScrollbarInternalController;
	friend class GUIVerticalScrollbarInternalController;
	friend class GUIParentNode_Overflow;
private:
	float childrenRenderOffsetX;
	float childrenRenderOffsetY;

protected:
	vector<GUINode*> subNodes;
	bool computeViewportCache;
	vector<GUINode*> vieportSubNodesCache;
	vector<GUINode*> floatingNodesCache;
	GUIParentNode_Overflow* overflowX;
	GUIParentNode_Overflow* overflowY;

	// forbid class copy
	CLASS_FORBID_COPY(GUIParentNode)

	/**
	 * Constructor
	 * @param screenNode screen node
	 * @param parentNode parent node
	 * @param id id
	 * @param flow flow
	 * @param overflowX overflow x
	 * @param overflowY overflow y
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
	 * @throws tdme::gui::GUIParserException
	 */
	GUIParentNode(
		GUIScreenNode* screenNode,
		GUIParentNode* parentNode,
		const string& id,
		GUINode_Flow* flow,
		GUIParentNode_Overflow* overflowX,
		GUIParentNode_Overflow* overflowY,
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
		const string& tooltip
	);

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

	/**
	 * Detach sub node at given index
	 * @param index sub node index
	 * @returns sub node at given index
	 */
	GUINode* detachSubNode(int index);

	/**
	 * Detach sub nodes
	 * @returns sub nodes
	 */
	vector<GUINode*> detachSubNodes();

public:

	/**
	 * @return sub nodes count
	 */
	inline int getSubNodesCount() {
		return subNodes.size();
	}

	/**
	 * Clear sub nodes
	 */
	void clearSubNodes();

	/**
	 * Replace sub nodes with given XML
	 * @param xml xml
	 * @param resetScrollOffsets reset scroll offsets
	 * @throws tdme::gui::GUIParserException
	 */
	void replaceSubNodes(const string& xml, bool resetScrollOffsets);

	/**
	 * Add sub nodes with given XML
	 * @param xml xml
	 * @param resetScrollOffsets reset scroll offsets
	 * @throws tdme::gui::GUIParserException
	 */
	void addSubNodes(const string& xml, bool resetScrollOffsets);

	/**
	 * Add sub node
	 * @param node node
	 * @throws tdme::gui::GUIParserException
	 */
	void addSubNode(GUINode* node);

	/**
	 * Move children node from other parent node into this parent node
	 * @param otherParentNode other parent node
	 * @param index other parent node sub node index
	 */
	void moveSubNode(GUIParentNode* otherParentNode, int index);

	/**
	 * Move children nodes from other parent node into this parent node
	 * @param otherParentNode other parent node
	 */
	void moveSubNodes(GUIParentNode* otherParentNode);

	/**
	 * @return overflow x
	 */
	GUIParentNode_Overflow* getOverflowX();

	/**
	 * @return overflow y
	 */
	GUIParentNode_Overflow* getOverflowY();

	/**
	 * Create over flow
	 * @param overflow over flow
	 * @return over flow
	 * @throws tdme::gui::GUIParserException
	 */
	static GUIParentNode_Overflow* createOverflow(const string& overflow);

	/**
	 * @return children render offset x
	 */
	inline float getChildrenRenderOffsetX() {
		return childrenRenderOffsetX;
	}

	/**
	 * Set children render offset x
	 * @param childrenRenderOffSetX children render offset x
	 */
	void setChildrenRenderOffsetX(float childrenRenderOffSetX);

	/**
	 * @return children render offset y
	 */
	inline float getChildrenRenderOffsetY() {
		return childrenRenderOffsetY;
	}

	/**
	 * Set children render offset y
	 * @param childrenRenderOffSetY children render offset y
	 */
	void setChildrenRenderOffsetY(float childrenRenderOffSetY);

	/**
	 * Create requested constraints
	 * @param left left
	 * @param top top
	 * @param width width
	 * @param height height
	 * @param factor factor
	 * @return requested constraints
	 */
	static GUINode_RequestedConstraints createRequestedConstraints(const string& left, const string& top, const string& width, const string& height, int factor);

	/**
	 * Get child controller nodes
	 * @param childControllerNodes child controller nodes
	 * @param requireConditionsMet require conditions met
	 */
	void getChildControllerNodes(vector<GUINode*>& childControllerNodes, bool requireConditionsMet = false);

	// overridden methods
	void dispose() override;
	void setConditionsMet() override;
	void render(GUIRenderer* guiRenderer) override;
	void determineNodesByCoordinate(const Vector2& coordinate, unordered_set<string>& nodeIds) override;
	void determineMouseEventNodes(GUIMouseEvent* event, bool floatingNode, unordered_set<string>& eventNodeIds, unordered_set<string>& eventFloatingNodeIds, int flags = DETERMINEMOUSEEVENTNODES_FLAG_NONE) override;

	/**
	 * Invalidate render caches
	 */
	void invalidateRenderCaches();

private:
	/**
	 * Get child controller nodes internal
	 * @param childControllerNodes child controller nodes
	 * @param requireConditionsMet require conditions met
	 */
	void getChildControllerNodesInternal(vector<GUINode*>& childControllerNodes, bool requireConditionsMet = false);

	/**
	 * Remove sub node
	 * @param node node
	 * @param resetScrollOffsets reset scroll offsets
	 */
	void removeSubNode(GUINode* node, bool resetScrollOffsets);

	/**
	 * Unset mouse over and click conditions on element nodes
	 */
	void unsetMouseStates();

};
