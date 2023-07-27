#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIInputInternalNode;
using tdme::gui::nodes::GUINode;
using tdme::utilities::MutableString;

/**
 * GUI input controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUIInputController final
	: public GUIElementController
{
	friend class GUIInput;

private:
	STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	GUIInputInternalNode* inputNode { nullptr };
	bool disabled;

	// forbid class copy
	CLASS_FORBID_COPY(GUIInputController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIInputController(GUINode* node);

public:

	/**
	 * On value change
	 */
	void onChange();

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
