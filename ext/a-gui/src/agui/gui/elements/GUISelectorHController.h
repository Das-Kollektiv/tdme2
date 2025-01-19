#pragma once

#include <memory>
#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/utilities/MutableString.h>

using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

// namespaces
namespace agui {
namespace gui {
namespace elements {
	using ::agui::gui::events::GUIActionListener;
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
 * GUI selector horizontal controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUISelectorHController final
	: public GUIElementController
{
	friend class GUISelectorH;
	friend class GUISelectorHOptionController;

private:
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	vector<GUISelectorHOptionController*> selectorHOptionControllers;
	bool disabled;
	MutableString value;
	string search;
	int selectedHOptionControllerIdx { -1 };
	unique_ptr<GUIActionListener> actionListener;
	GUIParentNode* innerNode { nullptr };

private:
	// forbid class copy
	FORBID_CLASS_COPY(GUISelectorHController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUISelectorHController(GUINode* node);

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
	 * @param selectedSelectorHOptionElementNode selected selector horizontal option element node
	 */
	void select(GUIElementNode* selectedSelectorHOptionElementNode);

	/**
	 * Determine drop down option controllers
	 */
	void determineSelectorHOptionControllers();

	/**
	 * Select next node
	 */
	void selectNext();

	/**
	 * Select previous
	 */
	void selectPrevious();

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
