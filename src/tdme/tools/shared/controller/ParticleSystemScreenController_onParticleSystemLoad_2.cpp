#include <tdme/tools/shared/controller/ParticleSystemScreenController_onParticleSystemLoad_2.h>

#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>

using tdme::tools::shared::controller::ParticleSystemScreenController_onParticleSystemLoad_2;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedParticleSystemView;

ParticleSystemScreenController_onParticleSystemLoad_2::ParticleSystemScreenController_onParticleSystemLoad_2(ParticleSystemScreenController* particleSystemScreenController)
	: particleSystemScreenController(particleSystemScreenController)
{
}

void ParticleSystemScreenController_onParticleSystemLoad_2::performAction()
{
	particleSystemScreenController->view->loadFile(particleSystemScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName(), particleSystemScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName());
	particleSystemScreenController->particleSystemPath->setPath(particleSystemScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
	particleSystemScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
}
