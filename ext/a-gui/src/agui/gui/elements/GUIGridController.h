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
 * Grid controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUIGridController final
	: public GUIElementController
{
	friend class GUIGrid;
	friend class GUIGridItemController;

private:
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	AGUI_STATIC_DLL_IMPEXT static constexpr char VALUE_DELIMITER { '|' };
	vector<GUIGridItemController*> gridItemControllers;
	bool disabled;
	bool multipleSelection;
	int focussedItemIdx;
	MutableString value;
	MutableString singleValue;

	bool keyControl;

	bool onSubTreeChangeRun { false };
	int horizontalItems { 1 };

	// forbid class copy
	FORBID_CLASS_COPY(GUIGridController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIGridController(GUINode* node);

	/**
	 * @returns if multiple selection is enabled
	 */
	bool isMultipleSelection();

	/**
	 * @returns is control down
	 */
	bool isKeyControlDown();

	/**
	 * Get focussed item idx
	 */
	int getFocussedItemIdx();

	/**
	 * Get item idx
	 * @param gridItemElementNode grid item element node
	 */
	int getItemIdx(GUIElementNode* gridItemElementNode);

	/**
	 * Unselect all items
	 */
	void unselect();

	/**
	 * Select
	 * @param itemIdx item index
	 */
	void select(int itemIdx);

	/**
	 * Select
	 * @param gridItemElementNode grid item element node
	 */
	void select(GUIElementNode* gridItemElementNode);

	/**
	 * Unfocus all items
	 */
	void unfocus();

	/**
	 * Focus
	 * @param itemIdx item index
	 */
	void focus(int itemIdx);

	/**
	 * Focus
	 * @param gridItemElementNode grid item element node
	 */
	void focus(GUIElementNode* gridItemElementNode);

	/**
	 * Select current item
	 */
	void selectCurrent();

	/**
	 * Focus next item
	 */
	void focusNext();

	/**
	 * Focus previous item
	 */
	void focusPrevious();

	/**
	 * Toggle
	 * @param itemIdx item index
	 */
	void toggle(int itemIdx);

	/**
	 * Toggle
	 * @param gridItemElementNode grid item element node
	 */
	void toggle(GUIElementNode* gridItemElementNode);

	/**
	 * Select focussed node
	 */
	void select();

	/**
	 * Determine items
	 */
	void determineItems();

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
