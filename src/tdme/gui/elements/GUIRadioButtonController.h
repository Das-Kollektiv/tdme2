#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/MutableString.h>
#include <tdme/gui/nodes/GUINodeController.h>

using std::map;
using std::string;
using std::vector;

using tdme::gui::nodes::GUINodeController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;

/** 
 * GUI Checkbox controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUIRadioButtonController final
	: public GUINodeController
{
	friend class GUIRadioButton;

private:
	static string CONDITION_SELECTED;
	static string CONDITION_UNSELECTED;
	static string CONDITION_DISABLED;
	static string CONDITION_ENABLED;
	bool selected {  };
	bool disabled {  };
	static map<string, vector<GUIElementNode*>> radioButtonGroupNodesByName;
	MutableString value {  };

	/** 
	 * @return is checked
	 */
	bool isSelected();

	/** 
	 * Select
	 */
	void select();

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIRadioButtonController(GUINode* node);

public:
	bool isDisabled() override;
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	const MutableString& getValue() override;
	void setValue(const MutableString& value) override;

private:
	void init();
};
