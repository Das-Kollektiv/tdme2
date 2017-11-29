
#pragma once

#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::tools::shared::controller::ModelEditorScreenController;
using tdme::tools::shared::views::SharedModelEditorView;


class tdme::tools::shared::controller::ModelEditorScreenController_ModelEditorScreenController_1
	: public virtual Action
{
	friend class ModelEditorScreenController;
	friend class ModelEditorScreenController_onModelLoad_2;
	friend class ModelEditorScreenController_onModelSave_3;

public:
	void performAction() override;

	// Generated
	ModelEditorScreenController_ModelEditorScreenController_1(ModelEditorScreenController* modelEditorScreenController, SharedModelEditorView* finalView);

private:
	ModelEditorScreenController* modelEditorScreenController;
	SharedModelEditorView* finalView;
};
