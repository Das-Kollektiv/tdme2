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
 * GUI drop down controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUIDropDownController final
	: public GUIElementController
{
	friend class GUIDropDown;
	friend class GUIDropDownOptionController;

private:
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_OPENED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_CLOSED;
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
