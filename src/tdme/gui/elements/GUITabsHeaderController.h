// Generated from /tdme/src/tdme/gui/elements/GUITabsHeaderController.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>

using tdme::gui::nodes::GUINodeController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;
using tdme::utils::_ArrayList;


struct default_init_tag;

/** 
 * GUI tabs header controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUITabsHeaderController final
	: public GUINodeController
{

public:
	typedef GUINodeController super;

private:
	GUINode* tabsNode {  };
	_ArrayList* childControllerNodes {  };
	_ArrayList* tabControllers {  };
	bool hasFocus_ {  };
protected:

	/** 
	 * GUI Checkbox controller
	 * @param node
	 */
	void ctor(GUINode* node);

public:
	bool isDisabled() override;
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;

public: /* protected */

	/** 
	 * @return has focus
	 */
	bool hasFocus();

	/** 
	 * Unselect all nodes
	 */
	void unselect();

private:

	/** 
	 * Determine select box option controllers
	 */
	void determineTabControllers();

	/** 
	 * Get selected tab idx
	 */
	int32_t getSelectedTabIdx();

	/** 
	 * Select next node
	 */
	void selectNext();

	/** 
	 * Select previous
	 */
	void selectPrevious();

	/** 
	 * Select current
	 */
	void selectCurrent();

public:
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
	GUITabsHeaderController(GUINode* node);
protected:
	GUITabsHeaderController(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
