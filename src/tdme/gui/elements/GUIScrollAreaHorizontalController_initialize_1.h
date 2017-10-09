#pragma once

#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>

using tdme::gui::events::GUIActionListener;
using tdme::gui::elements::GUIScrollAreaHorizontalController;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIParentNode;

class tdme::gui::elements::GUIScrollAreaHorizontalController_initialize_1
	: public virtual GUIActionListener
{

public:
	void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) override;

	GUIScrollAreaHorizontalController_initialize_1(GUIScrollAreaHorizontalController *GUIScrollAreaHorizontalController_this, GUIElementNode* leftArrowNode, GUIParentNode* contentNode, GUIElementNode* rightArrowNode);
	GUIScrollAreaHorizontalController *GUIScrollAreaHorizontalController_this;
	GUIElementNode* leftArrowNode;
	GUIParentNode* contentNode;
	GUIElementNode* rightArrowNode;

private:
	friend class GUIScrollAreaHorizontalController;
};
