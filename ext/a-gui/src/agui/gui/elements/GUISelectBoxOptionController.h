#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/utilities/MutableString.h>

using std::string;

// namespaces
namespace agui {
namespace gui {
namespace elements {
	using ::agui::gui::events::GUIKeyboardEvent;
	using ::agui::gui::events::GUIMouseEvent;
	using ::agui::gui::nodes::GUIElementController;
	using ::agui::gui::nodes::GUINode;
	using ::agui::gui::nodes::GUIParentNode;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI select box option controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUISelectBoxOptionController: public GUIElementController
{
	friend class GUISelectBoxOption;
	friend class GUISelectBoxController;
	friend class GUISelectBoxParentOptionController;

protected:
	GUIParentNode* selectBoxNode { nullptr };

private:
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_FOCUSSED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_UNFOCUSSED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_CHILD;
	bool initialPostLayout;
	bool selected;
	bool focussed;
	MutableString value;

	// forbid class copy
	FORBID_CLASS_COPY(GUISelectBoxOptionController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUISelectBoxOptionController(GUINode* node);

	/**
	 * @return is selected
	 */
	inline bool isSelected() {
		return selected;
	}

	/**
	 * Select
	 */
	void select();

	/**
	 * Unselect
	 */
	void unselect();

	/**
	 * Toggle selection
	 */
	void toggle();

	/**
	 * @return is focussed
	 */
	inline bool isFocussed() {
		return focussed;
	}

	/**
	 * Focus
	 */
	void focus();

	/**
	 * Unfocus
	 */
	void unfocus();

	/**
	 * @return if hierarchy is expanded
	 */
	bool isHierarchyExpanded();

	/**
	 * Expand hierarchy
	 */
	void expandHierarchy();
public:
	// overridden methods
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUIKeyboardEvent* event) override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	const MutableString& getValue() override;
	void setValue(const MutableString& value) override;

};
