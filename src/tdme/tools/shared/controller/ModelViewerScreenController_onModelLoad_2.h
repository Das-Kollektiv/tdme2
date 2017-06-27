// Generated from /tdme/src/tdme/tools/shared/controller/ModelViewerScreenController.java

#pragma once

#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/gui/events/Action.h>

using java::lang::Object;
using tdme::gui::events::Action;
using tdme::tools::shared::controller::ModelViewerScreenController;


struct default_init_tag;
class tdme::tools::shared::controller::ModelViewerScreenController_onModelLoad_2
	: public virtual Object
	, public virtual Action
{

public:
	typedef Object super;
	void performAction() override;

	// Generated
	ModelViewerScreenController_onModelLoad_2(ModelViewerScreenController *ModelViewerScreenController_this);
	static ::java::lang::Class *class_();
	ModelViewerScreenController *ModelViewerScreenController_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class ModelViewerScreenController;
	friend class ModelViewerScreenController_ModelViewerScreenController_1;
	friend class ModelViewerScreenController_onModelSave_3;
};
