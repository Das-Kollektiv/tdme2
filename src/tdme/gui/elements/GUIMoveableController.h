#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/utilities/MutableString.h>

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::utilities::MutableString;

/**
 * GUI moveable controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUIMoveableController final: GUINodeController
{
	friend class GUIMoveable;

private:
	MutableString value;
	int mouseLastX { -1 };
	int mouseLastY { -1 };

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIMoveableController(GUINode* node);

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
