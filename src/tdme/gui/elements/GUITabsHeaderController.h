#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/utilities/MutableString.h>

using std::vector;

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::utilities::MutableString;

/**
 * GUI tabs header controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUITabsHeaderController final
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
	CLASS_FORBID_COPY(GUITabsHeaderController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUITabsHeaderController(GUINode* node);

	/**
	 * @return has focus
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
