#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/utilities/MutableString.h>

using std::string;

// namespaces
namespace agui {
namespace gui {
namespace elements {
	using ::agui::gui::events::GUIKeyboardEvent;
	using ::agui::gui::events::GUIMouseEvent;
	using ::agui::gui::nodes::GUINode;
	using ::agui::gui::nodes::GUINodeController;
	using ::agui::gui::nodes::GUIStyledTextNodeController;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI styled input controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUIStyledInputController final
	: public GUINodeController
{
	friend class GUIStyledInput;

private:
	// forbid class copy
	FORBID_CLASS_COPY(GUIStyledInputController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIStyledInputController(GUINode* node);

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

private:
	GUIStyledTextNodeController* styledTextNodeController { nullptr };
};
