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
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::utilities::MutableString;

/**
 * GUI context menu item controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUIContextMenuItemController final
	: public GUIElementController
{
	friend class GUIContextMenuController;
	friend class GUIContextMenuItem;

private:
	STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
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
