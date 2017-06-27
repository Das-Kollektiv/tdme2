// Generated from /tdme/src/tdme/tools/leveleditor/controller/EmptyScreenController.java

#pragma once

#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/gui/events/Action.h>

using java::lang::Object;
using tdme::gui::events::Action;
using tdme::tools::leveleditor::controller::EmptyScreenController;
using tdme::tools::leveleditor::views::EmptyView;


struct default_init_tag;
class tdme::tools::leveleditor::controller::EmptyScreenController_EmptyScreenController_1
	: public virtual Object
	, public virtual Action
{

public:
	typedef Object super;
	void performAction() override;

	// Generated
	EmptyScreenController_EmptyScreenController_1(EmptyScreenController *EmptyScreenController_this, EmptyView* finalView);
	static ::java::lang::Class *class_();
	EmptyScreenController *EmptyScreenController_this;
	EmptyView* finalView;

private:
	virtual ::java::lang::Class* getClass0();
	friend class EmptyScreenController;
};
