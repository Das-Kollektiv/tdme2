// Generated from /tdme/src/tdme/tools/shared/controller/ParticleSystemScreenController.java

#pragma once

#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/gui/events/Action.h>

using java::lang::Object;
using tdme::gui::events::Action;
using tdme::tools::shared::controller::ParticleSystemScreenController;


struct default_init_tag;
class tdme::tools::shared::controller::ParticleSystemScreenController_onParticleSystemLoad_2
	: public virtual Object
	, public virtual Action
{

public:
	typedef Object super;
	void performAction() override;

	// Generated
	ParticleSystemScreenController_onParticleSystemLoad_2(ParticleSystemScreenController *ParticleSystemScreenController_this);
	static ::java::lang::Class *class_();
	ParticleSystemScreenController *ParticleSystemScreenController_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class ParticleSystemScreenController;
	friend class ParticleSystemScreenController_ParticleSystemScreenController_1;
	friend class ParticleSystemScreenController_onEntitySave_3;
	friend class ParticleSystemScreenController_onActionPerformed_4;
};
