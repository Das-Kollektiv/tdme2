#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/MutableString.h>
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
	friend class GUIHorizontalScrollbarInternalNode;
	friend class GUIHorizontalScrollbarInternalController_State;

private:
	GUILayoutNode* contentNode {  };
	float contentWidth { };
	GUIHorizontalScrollbarInternalController_State* state {  };
	int32_t mouseXOffset {  };
	MutableString value;

protected:
	GUIHorizontalScrollbarInternalController(GUINode* node);

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

private:

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
	 * @param draggedX dragged x
	 */
	virtual void setDraggedX(float draggedX);

public:
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	const MutableString& getValue() override;
	void setValue(const MutableString& value) override;

private:
	void init();

};
