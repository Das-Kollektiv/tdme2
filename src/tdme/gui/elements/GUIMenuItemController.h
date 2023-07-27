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
 * GUI menu item controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUIMenuItemController final
	: public GUIElementController
{
	friend class GUIMenuItem;
	friend class GUIMenuHeaderItemController;

private:
	STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
	bool selected;
	MutableString value;
	GUIParentNode* menuHeaderItemNode { nullptr };

	// forbid class copy
	FORBID_CLASS_COPY(GUIMenuItemController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIMenuItemController(GUINode* node);

	/**
	 * @return is selected
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
