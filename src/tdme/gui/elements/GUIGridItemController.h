#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/utilities/MutableString.h>

using std::string;

using tdme::gui::elements::GUIGridController;
using tdme::gui::elements::GUIGridItem;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::utilities::MutableString;

/**
 * GUI grid item controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUIGridItemController: public GUIElementController
{
	friend class GUIGridItem;
	friend class GUIGridController;

protected:
	GUIParentNode* gridNode { nullptr };

private:
	STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
	STATIC_DLL_IMPEXT static string CONDITION_FOCUSSED;
	STATIC_DLL_IMPEXT static string CONDITION_UNFOCUSSED;
	STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	bool initialPostLayout;
	bool selected;
	bool focussed;
	MutableString value;

	// forbid class copy
	FORBID_CLASS_COPY(GUIGridItemController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIGridItemController(GUINode* node);

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
