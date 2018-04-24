#pragma once

#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::tools::shared::controller::ModelEditorScreenController;


class tdme::tools::shared::controller::ModelEditorScreenController_onLODModelLoad
	: public virtual Action
{
	friend class ModelEditorScreenController;

public:
	void performAction() override;

	// Generated
	ModelEditorScreenController_onLODModelLoad(ModelEditorScreenController* modelEditorScreenController);

private:
	ModelEditorScreenController *modelEditorScreenController;
};
