
#pragma once

#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/gui/events/GUIChangeListener.h>

using java::lang::Object;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::tests::GUITest;


struct default_init_tag;
class tdme::tests::GUITest_init_2
	: public virtual Object
	, public virtual GUIChangeListener
{

public:
	typedef Object super;
	void onValueChanged(GUIElementNode* node) override;

	// Generated
	GUITest_init_2(GUITest *GUITest_this);
	static ::java::lang::Class *class_();
	GUITest *GUITest_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUITest;
	friend class GUITest_init_1;
};
