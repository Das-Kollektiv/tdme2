// Generated from /tdme/src/tdme/tools/leveleditor/controller/LevelEditorScreenController.java

#pragma once

#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/gui/events/Action.h>

using java::lang::Object;
using tdme::gui::events::Action;
using tdme::tools::leveleditor::controller::LevelEditorScreenController;


struct default_init_tag;
class tdme::tools::leveleditor::controller::LevelEditorScreenController_onMapLoad_1
	: public virtual Object
	, public virtual Action
{

public:
	typedef Object super;
	void performAction() override;

	// Generated
	LevelEditorScreenController_onMapLoad_1(LevelEditorScreenController *LevelEditorScreenController_this);
	static ::java::lang::Class *class_();
	LevelEditorScreenController *LevelEditorScreenController_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class LevelEditorScreenController;
	friend class LevelEditorScreenController_onMapSave_2;
};
