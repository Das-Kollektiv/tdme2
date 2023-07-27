#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::utilities::MutableString;

/**
 * GUI node controller base class
 * @author Andreas Drewke
 */
class tdme::gui::nodes::GUINodeController
{
protected:
	GUINode* node { nullptr };

	// forbid class copy
	CLASS_FORBID_COPY(GUINodeController)

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
	 * @return node
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
	 * @return has value
	 */
	virtual bool hasValue() = 0;

	/**
	 * @return value
	 */
	virtual const MutableString& getValue() = 0;

	/**
	 * Set value
	 * @param value value
	 */
	virtual void setValue(const MutableString& value) = 0;

	/**
	 * @return is disabled
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
