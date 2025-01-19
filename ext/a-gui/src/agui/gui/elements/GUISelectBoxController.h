#pragma once

#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/utilities/MutableString.h>

using std::string;
using std::vector;

// namespaces
namespace agui {
namespace gui {
namespace elements {
	using ::agui::gui::events::GUIKeyboardEvent;
	using ::agui::gui::events::GUIMouseEvent;
	using ::agui::gui::nodes::GUIElementController;
	using ::agui::gui::nodes::GUIElementNode;
	using ::agui::gui::nodes::GUINode;
	using ::agui::gui::nodes::GUINodeController;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI select box controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUISelectBoxController final
	: public GUIElementController
{
	friend class GUISelectBox;
	friend class GUISelectBoxOptionController;

private:
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	AGUI_STATIC_DLL_IMPEXT static constexpr char VALUE_DELIMITER { '|' };
	vector<GUISelectBoxOptionController*> selectBoxOptionControllers;
	bool disabled;
	bool multipleSelection;
	int focussedOptionIdx;
	MutableString value;
	MutableString singleValue;

	bool keyControl;

	// forbid class copy
	FORBID_CLASS_COPY(GUISelectBoxController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUISelectBoxController(GUINode* node);

	/**
	 * @return if multiple selection is enabled
	 */
	bool isMultipleSelection();

	/**
	 * @return is control down
	 */
	bool isKeyControlDown();

	/**
	 * Get focussed option idx
	 */
	int getFocussedOptionIdx();

	/**
	 * Get focussed option idx
	 * @param optionElementNode option element node
	 */
	int getOptionIdx(GUIElementNode* optionElementNode);

	/**
	 * Unselect all nodes
	 */
	void unselect();

	/**
	 * Select
	 * @param optionIdx option index
	 */
	void select(int optionIdx);

	/**
	 * Select
	 * @param optionElementNode option element node
	 */
	void select(GUIElementNode* optionElementNode);

	/**
	 * Unfocus all nodes
	 */
	void unfocus();

	/**
	 * Focus
	 * @param optionIdx option index
	 */
	void focus(int optionIdx);

	/**
	 * Focus
	 * @param optionElementNode option element node
	 */
	void focus(GUIElementNode* optionElementNode);

	/**
	 * Select current options
	 */
	void selectCurrent();

	/**
	 * Focus next option
	 */
	void focusNext();

	/**
	 * Focus previous option
	 */
	void focusPrevious();

	/**
	 * Toggle
	 * @param optionIdx option index
	 */
	void toggle(int optionIdx);

	/**
	 * Toggle
	 * @param optionElementNode option element node
	 */
	void toggle(GUIElementNode* optionElementNode);

	/**
	 * Select focussed node
	 */
	void select();

	/**
	 * Determine all options
	 */
	void determineAllOptions();

	/**
	 * Determine expanded options
	 */
	void determineExpandedOptions();

	/**
	 * Determine parent options
	 */
	void determineParentOptions();

	/**
	 * Toggle open state of current parent option
	 * @param optionIdx option index
	 */
	void toggleOpenState(int optionIdx);

	/**
	 * Expand
	 * @param optionIdx option index
	 */
	void expand(int optionIdx);

	/**
	 * Collapse
	 * @param optionIdx option index
	 */
	void collapse(int optionIdx);

public:
	/**
	 * Toggle open state of current parent option
	 * @param optionElementNode option element node
	 */
	void toggleOpenState(GUIElementNode* optionElementNode);

	// overridden methods
	void initialize() override;
	void dispose() override;
	void postLayout() override;
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	const MutableString& getValue() override;
	void setValue(const MutableString& value) override;
	void onSubTreeChange() override;

	/**
	 * Determine expanded parent option values
	 * @param expandedParentOptionValues expanded parent option values
	 */
	void determineExpandedParentOptionValues(vector<string>& expandedParentOptionValues);

	/**
	 * Expand parent options by values
	 * @param expandedParentOptionValues expanded parent option values
	 */
	void expandParentOptionsByValues(const vector<string>& expandedParentOptionValues);

};
