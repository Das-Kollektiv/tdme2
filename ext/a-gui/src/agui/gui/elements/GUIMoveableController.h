#pragma once

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/utilities/MutableString.h>

// namespaces
namespace agui {
namespace gui {
namespace elements {
	using ::agui::gui::events::GUIKeyboardEvent;
	using ::agui::gui::events::GUIMouseEvent;
	using ::agui::gui::nodes::GUINode;
	using ::agui::gui::nodes::GUINodeController;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI moveable controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUIMoveableController final: GUINodeController
{
	friend class GUIMoveable;

private:
	MutableString value;
	int mouseLastX { -1 };
	int mouseLastY { -1 };
	bool dragging { false };
	bool clicked { false };

	// forbid class copy
	FORBID_CLASS_COPY(GUIMoveableController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIMoveableController(GUINode* node);

public:
	/**
	 * Start moving
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 */
	void startMoving(int mouseX, int mouseY);

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
