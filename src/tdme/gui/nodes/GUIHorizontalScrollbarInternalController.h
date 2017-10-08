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

/** 
 * GUI Scrollbar controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIHorizontalScrollbarInternalController
	: public GUINodeController
{

private:
	GUILayoutNode* contentNode {  };
	GUIHorizontalScrollbarInternalController_State* state {  };
	int32_t mouseXOffset {  };

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

public: /* protected */
	GUIHorizontalScrollbarInternalController(GUINode* node);

private:
	void init();
	friend class GUIHorizontalScrollbarInternalController_State;
};
