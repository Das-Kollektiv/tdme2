
#pragma once

#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::shared::model::LevelEditorEntityLibrary;

class tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController_onValueChanged_1
	: public virtual Action
{
	friend class LevelEditorEntityLibraryScreenController;

public:
	void performAction() override;

	// Generated
	LevelEditorEntityLibraryScreenController_onValueChanged_1(LevelEditorEntityLibraryScreenController *levelEditorEntityLibraryScreenController, LevelEditorEntityLibrary* entityLibrary);

private:
	LevelEditorEntityLibraryScreenController *levelEditorEntityLibraryScreenController;
	LevelEditorEntityLibrary* entityLibrary;
};
