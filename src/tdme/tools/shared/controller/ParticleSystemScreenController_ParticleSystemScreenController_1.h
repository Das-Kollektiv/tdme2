
#pragma once

#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::views::SharedParticleSystemView;

class tdme::tools::shared::controller::ParticleSystemScreenController_ParticleSystemScreenController_1
	: public virtual Action
{
	friend class ParticleSystemScreenController;
	friend class ParticleSystemScreenController_onParticleSystemLoad_2;
	friend class ParticleSystemScreenController_onEntitySave_3;
	friend class ParticleSystemScreenController_onActionPerformed_4;

public:
	void performAction() override;

	// Generated
	ParticleSystemScreenController_ParticleSystemScreenController_1(ParticleSystemScreenController* particleSystemScreenController, SharedParticleSystemView* finalView);

private:
	ParticleSystemScreenController* particleSystemScreenController;
	SharedParticleSystemView* finalView;
};
