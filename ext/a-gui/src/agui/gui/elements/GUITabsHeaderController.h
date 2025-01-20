#pragma once

#include <vector>

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/utilities/MutableString.h>

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
 * GUI tabs header controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUITabsHeaderController final
	: public GUIElementController
{
	friend class GUITabsHeader;
	friend class GUITabController;

private:
	GUINode* tabsNode { nullptr };
	vector<GUITabController*> tabControllers;
	int tabControllerIdx { -1 };
	bool focus;
	MutableString value;

	// forbid class copy
	FORBID_CLASS_COPY(GUITabsHeaderController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUITabsHeaderController(GUINode* node);

	/**
	 * @returns has focus
	 */
	bool hasFocus();

	/**
	 * Determine select box option controllers
	 */
	void determineTabControllers();

	/**
	 * Select next node
	 */
	void selectNext();

	/**
	 * Select previous
	 */
	void selectPrevious();

	/**
	 * Select current
	 */
	void selectCurrent();

public:
	/**
	 * Unselect selected tab
	 */
	void unselect();

	/**
	 * Select selected tab
	 */
	void select();

	/**
	 * Select tab by index
	 * @param idx index
	 */
	void select(int idx);

	/**
	 * Select tab by index
	 * @param tabElementNode tab element node
	 */
	void select(GUIElementNode* tabElementNode);

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
