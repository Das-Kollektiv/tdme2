#pragma once

#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>

using std::map;
using std::wstring;
using std::vector;

using tdme::gui::nodes::GUINodeController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;


struct default_init_tag;

/** 
 * GUI Checkbox controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUIRadioButtonController final
	: public GUINodeController
{

public:
	typedef GUINodeController super;

private:
	static wstring CONDITION_SELECTED;
	static wstring CONDITION_UNSELECTED;
	static wstring CONDITION_DISABLED;
	static wstring CONDITION_ENABLED;
	bool selected {  };
	bool disabled {  };
	static map<wstring, vector<GUIElementNode*>> radioButtonGroupNodesByName;
	MutableString* value {  };

protected:

	/** 
	 * GUI Checkbox controller
	 * @param node
	 */
	void ctor(GUINode* node);

public: /* protected */

	/** 
	 * @return is checked
	 */
	bool isSelected();

	/** 
	 * Select
	 * @param checked
	 */
	void select();

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
	MutableString* getValue() override;
	void setValue(MutableString* value) override;

	// Generated

public: /* protected */
	GUIRadioButtonController(GUINode* node);
protected:
	GUIRadioButtonController(const ::default_init_tag&);

public:
	static void clinit();

private:
	void init();
};
