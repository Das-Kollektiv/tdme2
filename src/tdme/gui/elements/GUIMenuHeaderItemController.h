#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/utilities/MutableString.h>

using std::string;
using std::vector;

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::utilities::MutableString;

/**
 * GUI menu header item controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUIMenuHeaderItemController final
	: public GUIElementController
{
	friend class GUIMenuHeaderController;
	friend class GUIMenuHeaderItem;
	friend class GUIMenuHeaderItemOptionController;
	friend class GUIMenuItemController;

private:
	STATIC_DLL_IMPEXT static string CONDITION_OPENED;
	STATIC_DLL_IMPEXT static string CONDITION_CLOSED;
	STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
	GUIElementNode* menuHeaderNode { nullptr };
	vector<GUIMenuItemController*> menuItemControllers;
	bool open;
	bool selected;
	MutableString value;
	int selectedMenuItemControllerIdx { -1 };

private:
	// forbid class copy
	FORBID_CLASS_COPY(GUIMenuHeaderItemController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIMenuHeaderItemController(GUINode* node);

	/**
	 * @returns menu open state
	 */
	bool isOpen();

	/**
	 * @returns is selected
	 */
	bool isSelected();

	/**
	 * Select
	 */
	void select();

	/**
	 * Unselect
	 */
	void unselect();

	/**
	 * Toggle open state
	 */
	void toggleOpenState();

	/**
	 * Determine menu item controllers
	 */
	void determineMenuItemControllers();

	/**
	 * Unselect selection
	 */
	void unselectSelection();

	/**
	 * Select first menu item
	 */
	void selectFirst();

	/**
	 * Select next menu item
	 */
	void selectNext();

	/**
	 * Select previous menu item
	 */
	void selectPrevious();

	/**
	 * Handle current menu item keyboard event
	 * @param event event
	 */
	void handleCurrentMenuItemKeyboardEvent(GUIKeyboardEvent* event);

public:
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

};
