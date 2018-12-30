
#pragma once

#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::tools::shared::controller::ParticleSystemScreenController;

class tdme::tools::shared::controller::ParticleSystemScreenController_onActionPerformed_5
	: public virtual Action
{
	friend class ParticleSystemScreenController;
	friend class ParticleSystemScreenController_ParticleSystemScreenController_1;
	friend class ParticleSystemScreenController_onParticleSystemLoad_2;
	friend class ParticleSystemScreenController_onEntitySave_3;

public:
	void performAction() override;

	// Generated
	ParticleSystemScreenController_onActionPerformed_5(ParticleSystemScreenController* particleSystemScreenController);

private:
	ParticleSystemScreenController* particleSystemScreenController;
};
