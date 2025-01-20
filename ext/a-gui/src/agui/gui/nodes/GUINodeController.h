#pragma once

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>

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
 * GUI node controller base class
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUINodeController
{
protected:
	GUINode* node { nullptr };

	// forbid class copy
	FORBID_CLASS_COPY(GUINodeController)

	/**
	 * Private constructor
	 */
	inline GUINodeController(GUINode* node): node(node) {}

public:
	/**
	 * Destructor
	 */
	inline virtual ~GUINodeController() {}

	/**
	 * @returns node
	 */
	inline GUINode* getNode() {
		return node;
	}

	/**
	 * Initialize controller after element has been created
	 */
	virtual void initialize() = 0;

	/**
	 * Dispose controller
	 */
	virtual void dispose() = 0;

	/**
	 * Post layout event
	 */
	virtual void postLayout() = 0;

	/**
	 * Handle mouse event
	 * @param node node
	 * @param event event
	 */
	virtual void handleMouseEvent(GUINode* node, GUIMouseEvent* event) = 0;

	/**
	 * Handle keyboard event
	 * @param event event
	 */
	virtual void handleKeyboardEvent(GUIKeyboardEvent* event) = 0;

	/**
	 * Tick method will be executed once per frame
	 */
	virtual void tick() = 0;

	/**
	 * On focus gained
	 */
	virtual void onFocusGained() = 0;

	/**
	 * On focus lost
	 */
	virtual void onFocusLost() = 0;

	/**
	 * @returns has value
	 */
	virtual bool hasValue() = 0;

	/**
	 * @returns value
	 */
	virtual const MutableString& getValue() = 0;

	/**
	 * Set value
	 * @param value value
	 */
	virtual void setValue(const MutableString& value) = 0;

	/**
	 * @returns is disabled
	 */
	virtual bool isDisabled() = 0;

	/**
	 * Set disabled
	 * @param disabled disabled
	 */
	virtual void setDisabled(bool disabled) = 0;

	/**
	 * On sub tree change
	 */
	virtual void onSubTreeChange() = 0;

};
