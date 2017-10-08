#pragma once

#include <string>

#include <tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>

using std::wstring;

using tdme::gui::nodes::GUINodeController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::utils::MutableString;

/** 
 * GUI drop down option controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUIDropDownOptionController final
	: public GUINodeController
{

private:
	static wstring CONDITION_SELECTED;
	static wstring CONDITION_UNSELECTED;
	GUIParentNode* dropDownNode {  };
	bool selected {  };

public: /* protected */

	/** 
	 * @return is selected
	 */
	bool isSelected();

public:
	bool isDisabled() override;
	void setDisabled(bool disabled) override;

public: /* protected */

	/** 
	 * Select
	 */
	void select();

	/** 
	 * Unselect
	 * @param checked
	 */
	void unselect();

public:
	void initialize() override;
	void postLayout() override;
	void dispose() override;
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	MutableString* getValue() override;
	void setValue(MutableString* value) override;

public: /* protected */
	GUIDropDownOptionController(GUINode* node);

public:
	static void clinit();
};
