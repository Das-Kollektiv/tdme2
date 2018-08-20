
#pragma once

#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::tools::leveleditor::controller::LevelEditorScreenController;

class tdme::tools::leveleditor::controller::LevelEditorScreenController_onMapLoad_1
	: public virtual Action
{
	friend class LevelEditorScreenController;
	friend class LevelEditorScreenController_onMapSave_2;

public:
	void performAction() override;

	/**
	 * Public constructor
	 * @param levelEditorScreenController level editor screen controller
	 */
	LevelEditorScreenController_onMapLoad_1(LevelEditorScreenController* levelEditorScreenController);

private:
	LevelEditorScreenController* levelEditorScreenController;
};
