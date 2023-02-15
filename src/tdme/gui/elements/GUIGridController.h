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

using tdme::gui::elements::GUIGrid;
using tdme::gui::elements::GUIGridItemController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::utilities::MutableString;

/**
 * Grid controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUIGridController final
	: public GUIElementController
{
	friend class GUIGrid;
	friend class GUIGridItemController;

private:
	STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	STATIC_DLL_IMPEXT static constexpr char VALUE_DELIMITER { '|' };
	vector<GUIGridItemController*> gridItemControllers;
	bool disabled;
	bool multipleSelection;
	int focussedItemIdx;
	MutableString value;
	MutableString singleValue;

	bool keyControl;

	bool onSubTreeChangeRun { false };
	int horizontalItems { 1 };

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIGridController(GUINode* node);

	/**
	 * @return if multiple selection is enabled
	 */
	bool isMultipleSelection();

	/**
	 * @return is control down
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
