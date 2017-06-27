// Generated from /tdme/src/tdme/gui/elements/GUICheckboxController.java

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


struct default_init_tag;

/** 
 * GUI Checkbox controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUICheckboxController final
	: public GUINodeController
{

public:
	typedef GUINodeController super;

private:
	static String* CONDITION_CHECKED;
	static String* CONDITION_UNCHECKED;
	static String* CONDITION_DISABLED;
	static String* CONDITION_ENABLED;
	bool checked {  };
	bool disabled {  };
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
	bool isChecked();

	/** 
	 * Set checked
	 * @param checked
	 */
	void setChecked(bool checked);

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
	GUICheckboxController(GUINode* node);
protected:
	GUICheckboxController(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
};
