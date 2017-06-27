// Generated from /tdme/src/tdme/gui/nodes/GUIHorizontalScrollbarInternalController.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>

using tdme::gui::nodes::GUINodeController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State;
using tdme::gui::nodes::GUILayoutNode;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;


struct default_init_tag;

/** 
 * GUI Scrollbar controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIHorizontalScrollbarInternalController
	: public GUINodeController
{

public:
	typedef GUINodeController super;

private:
	GUILayoutNode* contentNode {  };
	GUIHorizontalScrollbarInternalController_State* state {  };
	int32_t mouseXOffset {  };
protected:

	/** 
	 * Constructor
	 * @param node
	 */
	void ctor(GUINode* node);

public:
	bool isDisabled() override;
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;

	/** 
	 * @return state
	 */
	virtual GUIHorizontalScrollbarInternalController_State* getState();

public: /* protected */

	/** 
	 * @return bar width
	 */
	virtual float getBarWidth();

	/** 
	 * @return bar left
	 */
	virtual float getBarLeft();

	/** 
	 * Set dragged x
	 * @param dragged x
	 */
	virtual void setDraggedX(float draggedX);

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
	GUIHorizontalScrollbarInternalController(GUINode* node);
protected:
	GUIHorizontalScrollbarInternalController(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
	friend class GUIHorizontalScrollbarInternalController_State;
};
