#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/utilities/MutableString.h>

using std::string;

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::utilities::MutableString;

/**
 * Color picker image controller controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::ColorPickerImageController
	: public GUINodeController
{
	friend class GUIElementNode;

private:
	MutableString value;
	ColorPickerScreenController* colorPickerScreenController { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(ColorPickerImageController)

	/**
	 * Constructor
	 * @param node node
	 * @param colorPickerScreenController color picker screen controller
	 */
	ColorPickerImageController(GUINode* node, ColorPickerScreenController* colorPickerScreenController);

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
