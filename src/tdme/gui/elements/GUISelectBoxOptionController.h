#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/utilities/MutableString.h>

using std::string;

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::utilities::MutableString;

/**
 * GUI select box option controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUISelectBoxOptionController: public GUIElementController
{
	friend class GUISelectBoxOption;
	friend class GUISelectBoxController;
	friend class GUISelectBoxParentOptionController;

protected:
	GUIParentNode* selectBoxNode { nullptr };

private:
	STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
	STATIC_DLL_IMPEXT static string CONDITION_FOCUSSED;
	STATIC_DLL_IMPEXT static string CONDITION_UNFOCUSSED;
	STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	STATIC_DLL_IMPEXT static string CONDITION_CHILD;
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
	 * @returns is selected
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
	 * @returns is focussed
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
	 * @returns if hierarchy is expanded
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
