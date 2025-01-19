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
 * GUI drop down controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUIDropDownController final
	: public GUIElementController
{
	friend class GUIDropDown;
	friend class GUIDropDownOptionController;

private:
	STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	STATIC_DLL_IMPEXT static string CONDITION_OPENED;
	STATIC_DLL_IMPEXT static string CONDITION_CLOSED;
	vector<GUIDropDownOptionController*> dropDownOptionControllers;
	bool open;
	bool disabled;
	GUIParentNode* dropDownContainerNode { nullptr };
	GUIElementNode* arrowNode { nullptr };
	GUIElementNode* textElementNode { nullptr };
	MutableString value;
	string search;
	int selectedDropDownOptionControllerIdx { -1 };
	int lastSelectedDropDownOptionControllerIdx { -1 };

private:
	// forbid class copy
	FORBID_CLASS_COPY(GUIDropDownController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIDropDownController(GUINode* node);

	/**
	 * @returns drop down open state
	 */
	bool isOpen();

	/**
	 * Unselect
	 */
	void unselect();

	/**
	 * Select by index
	 * @param idx index
	 */
	void select(int idx);

	/**
	 * Select by option element node
	 * @param selectedDropDownOptionElementNode selected drop down option element node
	 */
	void select(GUIElementNode* selectedDropDownOptionElementNode);

	/**
	 * Toggle open state
	 */
	void toggleOpenState();

	/**
	 * Determine drop down option controllers
	 */
	void determineDropDownOptionControllers();

	/**
	 * Select next node
	 */
	void selectNext();

	/**
	 * Select previous
	 */
	void selectPrevious();

	/**
	 * Select last
	 */
	void selectLast();

	/**
	 * Do search
	 */
	void doSearch();

public:
	// overridden methods
	bool isDisabled() override;
	void setDisabled(bool disabled) override;
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
