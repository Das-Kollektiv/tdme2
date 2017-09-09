// Generated from /tdme/src/tdme/gui/elements/GUITabController.java

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
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;


struct default_init_tag;

/** 
 * GUI tab controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUITabController final
	: public GUINodeController
{

public:
	typedef GUINodeController super;

private:
	static wstring CONDITION_DISABLED;
	static wstring CONDITION_ENABLED;
	static wstring CONDITION_SELECTED;
	static wstring CONDITION_UNSELECTED;
	GUINode* tabsNode {  };
	GUINode* tabsHeaderNode {  };
	bool selected {  };
	GUIColor* unfocussedNodeBorderLeftColor {  };
	GUIColor* unfocussedNodeBorderRightColor {  };
	GUIColor* unfocussedNodeBorderTopColor {  };
	GUIColor* unfocussedNodeBorderBottomColor {  };
	bool disabled {  };
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

	/** 
	 * Select this tab
	 */
	void selectTab();

	// Generated

public: /* protected */
	GUITabController(GUINode* node);
protected:
	GUITabController(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
};
