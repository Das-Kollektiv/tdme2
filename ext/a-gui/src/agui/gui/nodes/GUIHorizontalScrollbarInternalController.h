#pragma once

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/utilities/fwd-agui.h>
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
 * GUI scroll bar controller
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUIHorizontalScrollbarInternalController
	: public GUINodeController
{
	friend class GUIHorizontalScrollbarInternalNode;
public:
	enum State { STATE_NONE, STATE_MOUSEOVER, STATE_DRAGGING };

private:
	GUILayoutNode* contentNode { nullptr };
	float contentWidth;
	State state { STATE_NONE };
	int mouseXOffset;
	MutableString value;

	/**
	 * @returns bar width
	 */
	virtual float getBarWidth();

	/**
	 * @returns bar left
	 */
	virtual float getBarLeft();

	/**
	 * Set dragged x
	 * @param draggedX dragged x
	 */
	virtual void setDraggedX(float draggedX);

protected:
	// forbid class copy
	FORBID_CLASS_COPY(GUIHorizontalScrollbarInternalController)

	/**
	 * Constructor
	 * @param node node
	 */
	GUIHorizontalScrollbarInternalController(GUINode* node);

public:
	/**
	 * @returns state
	 */
	virtual State getState();

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
