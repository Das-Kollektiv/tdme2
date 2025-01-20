#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/utilities/fwd-agui.h>
#include <agui/utilities/MutableString.h>

using std::string;

// namespaces
namespace agui {
namespace gui {
namespace elements {
	using ::agui::gui::events::GUIKeyboardEvent;
	using ::agui::gui::events::GUIMouseEvent;
	using ::agui::gui::nodes::GUIColor;
	using ::agui::gui::nodes::GUIElementController;
	using ::agui::gui::nodes::GUINode;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI tab controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUITabController final: public GUIElementController
{
	friend class GUITab;
	friend class GUITabsController;
	friend class GUITabsHeaderController;

private:
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
	GUINode* tabsNode { nullptr };
	GUINode* tabsHeaderNode { nullptr };
	bool selected;
	GUIColor unfocussedNodeBorderLeftColor;
	GUIColor unfocussedNodeBorderRightColor;
	GUIColor unfocussedNodeBorderTopColor;
	GUIColor unfocussedNodeBorderBottomColor;
	bool disabled;
	MutableString value;

	// forbid class copy
	FORBID_CLASS_COPY(GUITabController)

	/**
	 * Private constructor
	 */
	GUITabController(GUINode* node);

	/**
	 * @returns is checked
	 */
	bool isSelected();

	/**
	 * Set checked
	 * @param selected selected
	 */
	void setSelected(bool selected);

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
