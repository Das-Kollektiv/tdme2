#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/utilities/MutableString.h>

using std::map;
using std::string;
using std::vector;

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::utilities::MutableString;

/**
 * GUI radio button controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUIRadioButtonController final
	: public GUIElementController
{
	friend class GUIRadioButton;

private:
	STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
	STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	bool selected;
	bool disabled;
	STATIC_DLL_IMPEXT static map<string, vector<GUIElementNode*>>* radioButtonGroupNodesByName;
	MutableString value;

	// forbid class copy
	CLASS_FORBID_COPY(GUIRadioButtonController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIRadioButtonController(GUINode* node);

	/**
	 * @return is checked
	 */
	bool isSelected();

	/**
	 * Select
	 */
	void select();

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

};
