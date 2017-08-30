// Generated from /tdme/src/tdme/tools/shared/controller/ModelViewerScreenController.java

#pragma once

#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::tools::shared::controller::ModelViewerScreenController;
using tdme::tools::shared::views::SharedModelViewerView;


class tdme::tools::shared::controller::ModelViewerScreenController_ModelViewerScreenController_1
	: public virtual Action
{
	friend class ModelViewerScreenController;
	friend class ModelViewerScreenController_onModelLoad_2;
	friend class ModelViewerScreenController_onModelSave_3;

public:
	void performAction() override;

	// Generated
	ModelViewerScreenController_ModelViewerScreenController_1(ModelViewerScreenController* modelViewerScreenController, SharedModelViewerView* finalView);

private:
	ModelViewerScreenController* modelViewerScreenController;
	SharedModelViewerView* finalView;
};
