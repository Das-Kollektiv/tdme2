#pragma once

#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/utilities/MutableString.h>

using std::string;
using std::vector;

// namespaces
namespace agui {
namespace gui {
namespace elements {
	using ::agui::gui::events::GUIKeyboardEvent;
	using ::agui::gui::events::GUIMouseEvent;
	using ::agui::gui::nodes::GUIElementNode;
	using ::agui::gui::nodes::GUINode;
	using ::agui::gui::nodes::GUINodeController;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI tabs controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUITabsController final
	: public GUINodeController
{
	friend class GUITabs;
	friend class GUITabController;
	friend class GUITabsHeaderController;

private:
	vector<GUITabController*> tabControllers;
	vector<GUITabContentController*> tabContentControllers;
	GUITabsHeaderController* tabsHeaderController { nullptr };
	MutableString value;
	bool tabSelected { false };

	// forbid class copy
	FORBID_CLASS_COPY(GUITabsController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUITabsController(GUINode* node);

	/**
	 * Determine tab controllers
	 */
	void determineTabContentControllers();

	/**
	 * Unselect
	 */
	void unselect();

	/**
	 * Select
	 * @param tabElementNode tab element node
	 */
	void select(GUIElementNode* tabElementNode);

	/**
	 * Set tab content selected
	 * @param id id
	 */
	void setTabContentSelected(const string& id);

	/**
	 * Set tab content selected internal
	 * @param id id
	 */
	void setTabContentSelectedInternal(const string& id);

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
