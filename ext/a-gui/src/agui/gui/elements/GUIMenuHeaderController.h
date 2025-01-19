#pragma once

#include <vector>

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/utilities/MutableString.h>

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
 * GUI menu header controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUIMenuHeaderController final
	: public GUINodeController
{
	friend class GUIMenuHeader;
	friend class GUIMenuHeaderItemController;

private:
	vector<GUIMenuHeaderItemController*> menuHeaderItemControllers;
	bool focus;
	MutableString value;
	int menuHeaderItemControllerIdx { -1 };

	// forbid class copy
	FORBID_CLASS_COPY(GUIMenuHeaderController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIMenuHeaderController(GUINode* node);

	/**
	 * @return has focus
	 */
	bool hasFocus();

	/**
	 * Determine menu header item controllers
	 */
	void determineMenuHeaderItemControllers();

	/**
	 * @return if menu is open
	 */
	bool isOpen();

	/**
	 * Unselect
	 */
	void unselect();

	/**
	 * Select next node
	 */
	void selectNext();

	/**
	 * Select previous
	 */
	void selectPrevious();

	/**
	 * Select by index
	 * @param idx index
	 */
	void select(int idx);

	/**
	 * Select element node
	 * @param elementNode element node
	 */
	void select(GUIElementNode* elementNode);

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
