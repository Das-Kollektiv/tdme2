#pragma once

#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>

using tdme::gui::events::GUIActionListener;
using tdme::gui::elements::GUIScrollAreaVerticalController;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIParentNode;

class tdme::gui::elements::GUIScrollAreaVerticalController_initialize_1
	: public virtual GUIActionListener
{

public:
	void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) override;

	GUIScrollAreaVerticalController_initialize_1(GUIScrollAreaVerticalController *GUIScrollAreaVerticalController_this, GUIElementNode* upArrowNode, GUIParentNode* contentNode, GUIElementNode* downArrowNode);
	GUIScrollAreaVerticalController *GUIScrollAreaVerticalController_this;
	GUIElementNode* upArrowNode;
	GUIParentNode* contentNode;
	GUIElementNode* downArrowNode;

private:
	friend class GUIScrollAreaVerticalController;
};
