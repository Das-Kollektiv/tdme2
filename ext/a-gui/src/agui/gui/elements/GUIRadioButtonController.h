#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/utilities/MutableString.h>

using std::string;
using std::unordered_map;
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
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI radio button controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUIRadioButtonController final
	: public GUIElementController
{
	friend class GUIRadioButton;

private:
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	//
	AGUI_STATIC_DLL_IMPEXT static unordered_map<string, vector<string>> radioButtonGroupNodesByName;
	//
	bool selected;
	bool disabled;
	bool deselectable;
	MutableString value;

	// forbid class copy
	FORBID_CLASS_COPY(GUIRadioButtonController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIRadioButtonController(GUINode* node);

	/**
	 * @returns is checked
	 */
	bool isSelected();

	/**
	 * Select
	 */
	void select();

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

};
