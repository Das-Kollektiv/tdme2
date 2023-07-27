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
 * GUI selector horizontal option controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUISelectorHOptionController final
	: public GUIElementController
{
	friend class GUISelectorHOption;
	friend class GUISelectorHController;

private:
	STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
	GUIParentNode* selectorHNode { nullptr };
	bool selected;
	bool hidden;
	MutableString value;

	// forbid class copy
	FORBID_CLASS_COPY(GUISelectorHOptionController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUISelectorHOptionController(GUINode* node);

	/**
	 * @return is selected
	 */
	inline bool isSelected() {
		return selected;
	}

	/**
	 * @return is hidden
	 */
	inline bool isHidden() {
		return hidden;
	}

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
	void setDisabled(bool disabled) override;
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
