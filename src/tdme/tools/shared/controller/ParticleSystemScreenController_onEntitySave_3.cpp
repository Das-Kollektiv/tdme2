#include <tdme/tools/shared/controller/ParticleSystemScreenController_onEntitySave_3.h>

#include <java/lang/String.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Exception.h>

using tdme::tools::shared::controller::ParticleSystemScreenController_onEntitySave_3;
using java::lang::String;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedParticleSystemView;
using tdme::utils::StringConverter;
using tdme::utils::_Exception;

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
	} catch (_Exception& exception) {
		particleSystemScreenController->showErrorPopUp(L"Warning", StringConverter::toWideString(exception.what()));
	}
}
