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
	using ::agui::gui::nodes::GUINodeController;
	using ::agui::gui::nodes::GUIParentNode;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI context menu item controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUIContextMenuItemController final
	: public GUIElementController
{
	friend class GUIContextMenuController;
	friend class GUIContextMenuItem;

private:
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
	bool selected;
	MutableString value;
	GUIParentNode* contextMenuNode { nullptr };

	// forbid class copy
	FORBID_CLASS_COPY(GUIContextMenuItemController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIContextMenuItemController(GUINode* node);

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

public:
	// overridden methods
	void initialize() override;
	void postLayout() override;
	void dispose() override;
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	const MutableString& getValue() override;
	void setValue(const MutableString& value) override;

};
