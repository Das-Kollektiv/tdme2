
#pragma once

#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::tools::shared::controller::ModelEditorScreenController;

class tdme::tools::shared::controller::ModelEditorScreenController_onModelSave_3
	: public virtual Action
{
	friend class ModelEditorScreenController;
	friend class ModelEditorScreenController_ModelEditorScreenController_1;
	friend class ModelEditorScreenController_onModelLoad_2;

public:
	void performAction() override;

	// Generated
	ModelEditorScreenController_onModelSave_3(ModelEditorScreenController* modelEditorScreenController);

private:
	ModelEditorScreenController* modelEditorScreenController;
};
