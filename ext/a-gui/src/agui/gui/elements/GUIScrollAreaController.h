#pragma once

#include <memory>

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/utilities/MutableString.h>

using std::unique_ptr;

// namespaces
namespace agui {
namespace gui {
namespace elements {
	using ::agui::gui::events::GUIActionListener;
	using ::agui::gui::events::GUIKeyboardEvent;
	using ::agui::gui::events::GUIMouseEvent;
	using ::agui::gui::nodes::GUINode;
	using ::agui::gui::nodes::GUINodeController;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI scroll area controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUIScrollAreaController final: public GUINodeController
{
	friend class GUIScrollArea;

private:
	MutableString value;
	unique_ptr<GUIActionListener> actionListener;
	bool scrollToBottomIssued { false };

	// forbid class copy
	FORBID_CLASS_COPY(GUIScrollAreaController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIScrollAreaController(GUINode* node);

	/**
	 * Scroll to bottom internal
	 */
	void scrollToBottomInternal();

public:
	bool isAtBottom();
	void scrollToBottom();

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
