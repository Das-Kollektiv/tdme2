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
	using ::agui::gui::nodes::GUIParentNode;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI context menu controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUIContextMenuController final
	: public GUIElementController
{
	friend class GUIContextMenu;
	friend class GUIContextMenuItemController;

private:
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_OPENED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_CLOSED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
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
