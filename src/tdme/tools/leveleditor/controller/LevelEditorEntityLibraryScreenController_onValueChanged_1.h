// Generated from /tdme/src/tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.java

#pragma once

#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/gui/events/Action.h>

using java::lang::Object;
using tdme::gui::events::Action;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::shared::model::LevelEditorEntityLibrary;


struct default_init_tag;
class tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController_onValueChanged_1
	: public virtual Object
	, public virtual Action
{

public:
	typedef Object super;
	void performAction() override;

	// Generated
	LevelEditorEntityLibraryScreenController_onValueChanged_1(LevelEditorEntityLibraryScreenController *LevelEditorEntityLibraryScreenController_this, LevelEditorEntityLibrary* entityLibrary);
	static ::java::lang::Class *class_();
	LevelEditorEntityLibraryScreenController *LevelEditorEntityLibraryScreenController_this;
	LevelEditorEntityLibrary* entityLibrary;

private:
	virtual ::java::lang::Class* getClass0();
	friend class LevelEditorEntityLibraryScreenController;
};
