#pragma once

#include <set>
#include <string>

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUILayerNode.h>
#include <agui/gui/nodes/GUINode_Alignments.h>
#include <agui/gui/nodes/GUINodeConditions.h>

using std::set;
using std::string;

// namespaces
namespace agui {
namespace gui {
namespace nodes {
	using ::agui::gui::events::GUIKeyboardEvent;
	using ::agui::gui::events::GUIMouseEvent;
}
}
}

/**
 * GUI element node
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUIElementNode final: public GUILayerNode
{
	friend class agui::gui::GUIParser;
	friend class GUINode;
	friend class GUIScreenNode;

public:
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_FOCUS;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_ALWAYS;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_ONMOUSEOVER;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_CLICK;

private:
	string name;
	string value;
	bool selected;
	bool disabled;
	GUINodeConditions activeConditions;
	bool focusable;
	bool ignoreEvents;
	string onInitializeExpression;
	string onMouseClickExpression;
	string onMouseDoubleClickExpression;
	string onMouseOverExpression;
	string onMouseOutExpression;
	string onChangeExpression;
	string parentElementId;
	vector<string> options;

protected:
	// forbid class copy
	FORBID_CLASS_COPY(GUIElementNode)

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
	 * @param name name
	 * @param value value
	 * @param selected selected
	 * @param disabled disabled
	 * @param focusable focusable
	 * @param ignoreEvents ignore events
	 * @param onInitialize on initialize expression
	 * @param onMouseClick on mouse click expression
	 * @param onMouseDoubleClickExpression on mouse double click expression
	 * @param onMouseOver on mouse over expression
	 * @param onMouseOut on mouse out expression
	 * @param onChangeExpression on change expression
	 * @param parentElementId parent element id
	 * @param options options
	 */
	GUIElementNode(
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
		const string& tooltip,
		const string& name,
		const string& value,
		bool selected,
		bool disabled,
		bool focusable,
		bool ignoreEvents,
		const string& onInitialize,
		const string& onMouseClick,
		const string& onMouseDoubleClickExpression,
		const string& onMouseOver,
		const string& onMouseOut,
		const string& onChangeExpression,
		const string& parentElementId,
		const string& options
	);

	// overridden methods
	const string getNodeType() override;
	bool isContentNode() override;

public:
	/**
	 * @return focusable
	 */
	inline bool isFocusable() {
		return focusable;
	}

	/**
	 * @return name
	 */
	inline const string& getName() {
		return name;
	}

	/**
	 * @return value
	 */
	inline const string& getValue() {
		return value;
	}

	/**
	 * @return is selected
	 */
	inline bool isSelected() {
		return selected;
	}

	/**
	 * @return is disabled
	 */
	inline bool isDisabled() {
		return disabled;
	}

	/**
	 * @return on initialize expression
	 */
	inline const string& getOnInitializeExpression() {
		return onInitializeExpression;
	}

	/**
	 * @return on mouse click expression
	 */
	inline const string& getOnMouseClickExpression() {
		return onMouseClickExpression;
	}

	/**
	 * @return on mouse double click expression
	 */
	inline const string& getOnMouseDoubleClickExpression() {
		return onMouseDoubleClickExpression;
	}

	/**
	 * @return on mouse over expression
	 */
	inline const string& getOnMouseOverExpression() {
		return onMouseOverExpression;
	}

	/**
	 * @return on mouse out expression
	 */
	inline const string& getOnMouseOutExpression() {
		return onMouseOutExpression;
	}

	/**
	 * @return on change expression
	 */
	inline const string& getOnChangeExpression() {
		return onChangeExpression;
	}

	/**
	 * Execute on change expression
	 */
	inline void executeOnChangeExpression() {
		if (onChangeExpression.size() > 0) executeExpression(getScreenNode(), onChangeExpression);
	}

	/**
	 * Execute expression
	 * @param screenNode screen node
	 * @param expression expression
	 */
	static void executeExpression(GUIScreenNode* screenNode, const string& expression);

	/**
	 * @return parent element id
	 */
	inline const string& getParentElementNodeId() {
		return parentElementId;
	}

	/**
	 * @return options
	 */
	inline const vector<string> getOptions() {
		return options;
	}

	/**
	 * @returns if option is among given options
	 */
	inline bool hasOption(const string& option) {
		return find(begin(options), end(options), option) != end(options);
	}

	/**
	 * @returns an option value, like <... options="type=float,min=0.0,max=1.0,step=0.1" /> or empty string if option does not exist
	 */
	const string getOptionValue(const string& option);

	/**
	 * @return active conditions
	 */
	inline GUINodeConditions& getActiveConditions() {
		return activeConditions;
	}

	/**
	 * Handle keyboard event
	 * @param event keyboard event
	 */
	void handleKeyboardEvent(GUIKeyboardEvent* event);

};
