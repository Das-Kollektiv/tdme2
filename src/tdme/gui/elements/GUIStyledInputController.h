#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/utilities/MutableString.h>

using std::string;

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIStyledTextNodeController;
using tdme::utilities::MutableString;

/**
 * GUI styled input controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUIStyledInputController final
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
