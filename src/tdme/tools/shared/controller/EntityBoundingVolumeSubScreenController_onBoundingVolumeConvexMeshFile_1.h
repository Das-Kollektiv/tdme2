// Generated from /tdme/src/tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/gui/events/Action.h>

using java::lang::Object;
using tdme::gui::events::Action;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;


struct default_init_tag;
class tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1
	: public virtual Object
	, public virtual Action
{

public:
	typedef Object super;
	void performAction() override;

	// Generated
	EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1(EntityBoundingVolumeSubScreenController *EntityBoundingVolumeSubScreenController_this, int32_t idxFinal, LevelEditorEntity* entityFinal);
	static ::java::lang::Class *class_();
	EntityBoundingVolumeSubScreenController *EntityBoundingVolumeSubScreenController_this;
	int32_t idxFinal;
	LevelEditorEntity* entityFinal;

private:
	virtual ::java::lang::Class* getClass0();
	friend class EntityBoundingVolumeSubScreenController;
	friend class EntityBoundingVolumeSubScreenController_BoundingVolumeType;
};
