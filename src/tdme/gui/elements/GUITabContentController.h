// Generated from /tdme/src/tdme/gui/elements/GUITabContentController.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>

using std::wstring;

using tdme::gui::nodes::GUINodeController;
using java::lang::String;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;


struct default_init_tag;

/** 
 * GUI tab content controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUITabContentController final
	: public GUINodeController
{

public:
	typedef GUINodeController super;

private:
	wstring CONDITION_SELECTED {  };
	wstring CONDITION_UNSELECTED {  };
	bool selected {  };
protected:

	/** 
	 * GUI Checkbox controller
	 * @param node
	 */
	void ctor(GUINode* node);

public:
	bool isDisabled() override;
	void setDisabled(bool disabled) override;

public: /* protected */

	/** 
	 * @return is checked
	 */
	bool isSelected();

	/** 
	 * Set checked
	 * @param selected
	 */
	void setSelected(bool selected);

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

	// Generated

public: /* protected */
	GUITabContentController(GUINode* node);
protected:
	GUITabContentController(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
