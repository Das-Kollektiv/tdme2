#include <tdme/tools/shared/controller/ParticleSystemScreenController_ParticleSystemScreenController_1.h>

#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>

using tdme::tools::shared::controller::ParticleSystemScreenController_ParticleSystemScreenController_1;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::views::SharedParticleSystemView;

ParticleSystemScreenController_ParticleSystemScreenController_1::ParticleSystemScreenController_ParticleSystemScreenController_1(ParticleSystemScreenController* particleSystemScreenController, SharedParticleSystemView* finalView)
	: particleSystemScreenController(particleSystemScreenController)
	, finalView(finalView)
{
}

void ParticleSystemScreenController_ParticleSystemScreenController_1::performAction()
{
	finalView->updateGUIElements();
	finalView->onSetEntityData();
}
