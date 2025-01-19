#pragma once

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/utilities/MutableString.h>

// namespaces
namespace agui {
namespace gui {
namespace nodes {
	using ::agui::gui::events::GUIKeyboardEvent;
	using ::agui::gui::events::GUIMouseEvent;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI vertical scroll bar internal controller
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUIVerticalScrollbarInternalController
	: public GUINodeController
{
	friend class GUIVerticalScrollbarInternalNode;
public:
	enum State {STATE_NONE, STATE_MOUSEOVER, STATE_DRAGGING};

private:
	GUILayoutNode* contentNode { nullptr };
	float contentHeight;
	State state;
	int mouseYOffset;
	MutableString value;

	// forbid class copy
	FORBID_CLASS_COPY(GUIVerticalScrollbarInternalController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIVerticalScrollbarInternalController(GUINode* node);

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

	/**
	 * @return state
	 */
	virtual State getState();

private:

	/**
	 * @return bar height
	 */
	virtual float getBarHeight();

	/**
	 * @return bar top
	 */
	virtual float getBarTop();

	/**
	 * Set dragged y
	 * @param draggedY dragged y
	 */
	virtual void setDraggedY(float draggedY);

};
