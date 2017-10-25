#pragma once

#include <string>

#include <tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>

using std::string;

using tdme::gui::nodes::GUINodeController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::utils::MutableString;

/** 
 * GUI select box option controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUISelectBoxOptionController final
	: public GUINodeController
{

private:
	static string CONDITION_SELECTED;
	static string CONDITION_UNSELECTED;
	static string CONDITION_DISABLED;
	static string CONDITION_ENABLED;
	GUIParentNode* selectBoxNode {  };
	bool selected {  };

public:
	bool isDisabled() override;
	void setDisabled(bool disabled) override;

public: /* protected */

	/** 
	 * @return is selected
	 */
	bool isSelected();

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
	void dispose() override;
	void postLayout() override;
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	MutableString* getValue() override;
	void setValue(MutableString* value) override;

public: /* protected */
	GUISelectBoxOptionController(GUINode* node);
};
