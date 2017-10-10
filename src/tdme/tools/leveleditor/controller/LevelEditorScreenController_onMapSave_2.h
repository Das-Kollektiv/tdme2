
#pragma once

#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::tools::leveleditor::controller::LevelEditorScreenController;

class tdme::tools::leveleditor::controller::LevelEditorScreenController_onMapSave_2
	: public virtual Action
{
	friend class LevelEditorScreenController;
	friend class LevelEditorScreenController_onMapLoad_1;

public:
	void performAction() override;

	// Generated
	LevelEditorScreenController_onMapSave_2(LevelEditorScreenController* levelEditorScreenController);

private:
	LevelEditorScreenController* levelEditorScreenController;
};
