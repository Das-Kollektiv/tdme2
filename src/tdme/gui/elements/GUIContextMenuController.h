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
 * GUI context menu controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUIContextMenuController final
	: public GUIElementController
{
	friend class GUIContextMenu;
	friend class GUIContextMenuItemController;

private:
	STATIC_DLL_IMPEXT static string CONDITION_OPENED;
	STATIC_DLL_IMPEXT static string CONDITION_CLOSED;
	STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
	vector<GUIContextMenuItemController*> menuItemControllers;
	MutableString value;
	int selectedMenuItemControllerIdx { -1 };

private:
	// forbid class copy
	FORBID_CLASS_COPY(GUIContextMenuController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIContextMenuController(GUINode* node);

	/**
	 * @return menu open state
	 */
	bool isOpen();

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
