// Generated from /tdme/src/tdme/gui/elements/GUIScrollAreaVerticalController.java

#pragma once

#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/gui/events/GUIActionListener.h>

using java::lang::Object;
using tdme::gui::events::GUIActionListener;
using tdme::gui::elements::GUIScrollAreaVerticalController;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIParentNode;


struct default_init_tag;
class tdme::gui::elements::GUIScrollAreaVerticalController_initialize_1
	: public virtual Object
	, public virtual GUIActionListener
{

public:
	typedef Object super;
	void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) override;

	// Generated
	GUIScrollAreaVerticalController_initialize_1(GUIScrollAreaVerticalController *GUIScrollAreaVerticalController_this, GUIElementNode* upArrowNode, GUIParentNode* contentNode, GUIElementNode* downArrowNode);
	static ::java::lang::Class *class_();
	GUIScrollAreaVerticalController *GUIScrollAreaVerticalController_this;
	GUIElementNode* upArrowNode;
	GUIParentNode* contentNode;
	GUIElementNode* downArrowNode;

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUIScrollAreaVerticalController;
};
