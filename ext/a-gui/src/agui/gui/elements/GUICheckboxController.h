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
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI check box controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUICheckboxController final
	: public GUIElementController
{
	friend class GUICheckbox;

private:
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_CHECKED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_UNCHECKED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	bool checked;
	bool disabled;
	MutableString value;

	// forbid class copy
	FORBID_CLASS_COPY(GUICheckboxController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUICheckboxController(GUINode* node);

	/**
	 * @return is checked
	 */
	bool isChecked();

	/**
	 * Set checked
	 * @param checked checked
	 */
	void setChecked(bool checked);

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
