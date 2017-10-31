#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>

using tdme::gui::nodes::GUINodeController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUILayoutNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIVerticalScrollbarInternalController_State;
using tdme::utils::MutableString;

/** 
 * GUI Scrollbar controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIVerticalScrollbarInternalController
	: public GUINodeController
{

private:
	GUILayoutNode* contentNode {  };
	GUIVerticalScrollbarInternalController_State* state {  };
	int32_t mouseYOffset {  };

public:
	bool isDisabled() override;
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;

	/** 
	 * @return state
	 */
	virtual GUIVerticalScrollbarInternalController_State* getState();

public: /* protected */

	/** 
	 * @return bar height
	 */
	virtual float getBarHeight();

	/** 
	 * @return bar top
	 */
	virtual float getBarTop();

	/** 
	 * Set dragged y
	 * @param dragged y
	 */
	virtual void setDraggedY(float draggedY);

public:
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	MutableString* getValue() override;
	void setValue(MutableString* value) override;

public: /* protected */
	GUIVerticalScrollbarInternalController(GUINode* node);

private:
	void init();
	friend class GUIVerticalScrollbarInternalController_State;
};
