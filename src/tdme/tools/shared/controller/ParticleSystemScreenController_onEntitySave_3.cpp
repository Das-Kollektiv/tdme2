#include <tdme/tools/shared/controller/ParticleSystemScreenController_onEntitySave_3.h>

#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>
#include <tdme/utils/Exception.h>

using tdme::tools::shared::controller::ParticleSystemScreenController_onEntitySave_3;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedParticleSystemView;
using tdme::utils::Exception;

ParticleSystemScreenController_onEntitySave_3::ParticleSystemScreenController_onEntitySave_3(ParticleSystemScreenController* particleSystemScreenController)
	: particleSystemScreenController(particleSystemScreenController)
{
}

void ParticleSystemScreenController_onEntitySave_3::performAction()
{
	try {
		particleSystemScreenController->view->saveFile(particleSystemScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName(), particleSystemScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName());
		particleSystemScreenController->particleSystemPath->setPath(particleSystemScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
		particleSystemScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
	} catch (Exception& exception) {
		particleSystemScreenController->showErrorPopUp("Warning", (exception.what()));
	}
}
