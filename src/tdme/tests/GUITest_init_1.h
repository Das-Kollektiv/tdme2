
#pragma once

#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/gui/events/GUIActionListener.h>

using java::lang::Object;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::tests::GUITest;


struct default_init_tag;
class tdme::tests::GUITest_init_1
	: public virtual Object
	, public virtual GUIActionListener
{

public:
	typedef Object super;
	void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) override;

	// Generated
	GUITest_init_1(GUITest *GUITest_this);
	static ::java::lang::Class *class_();
	GUITest *GUITest_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUITest;
	friend class GUITest_init_2;
};
