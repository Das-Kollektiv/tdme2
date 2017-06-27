// Generated from /tdme/src/tdme/gui/elements/GUIRadioButtonController.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>

using tdme::gui::nodes::GUINodeController;
using java::lang::String;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;
using tdme::utils::_HashMap;


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
	static String* CONDITION_SELECTED;
	static String* CONDITION_UNSELECTED;
	static String* CONDITION_DISABLED;
	static String* CONDITION_ENABLED;
	bool selected {  };
	bool disabled {  };
	static _HashMap* radioButtonGroupNodesByName;
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
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
