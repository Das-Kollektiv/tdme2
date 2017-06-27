// Generated from /tdme/src/tdme/gui/elements/GUIScrollAreaHorizontalController.java

#pragma once

#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/gui/events/GUIActionListener.h>

using java::lang::Object;
using tdme::gui::events::GUIActionListener;
using tdme::gui::elements::GUIScrollAreaHorizontalController;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIParentNode;


struct default_init_tag;
class tdme::gui::elements::GUIScrollAreaHorizontalController_initialize_1
	: public virtual Object
	, public virtual GUIActionListener
{

public:
	typedef Object super;
	void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) override;

	// Generated
	GUIScrollAreaHorizontalController_initialize_1(GUIScrollAreaHorizontalController *GUIScrollAreaHorizontalController_this, GUIElementNode* leftArrowNode, GUIParentNode* contentNode, GUIElementNode* rightArrowNode);
	static ::java::lang::Class *class_();
	GUIScrollAreaHorizontalController *GUIScrollAreaHorizontalController_this;
	GUIElementNode* leftArrowNode;
	GUIParentNode* contentNode;
	GUIElementNode* rightArrowNode;

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUIScrollAreaHorizontalController;
};
