#include <tdme/tools/shared/controller/ParticleSystemScreenController_onActionPerformed_5.h>

#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>
#include <tdme/utils/MutableString.h>

using tdme::tools::shared::controller::ParticleSystemScreenController_onActionPerformed_5;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedParticleSystemView;
using tdme::utils::MutableString;

ParticleSystemScreenController_onActionPerformed_5::ParticleSystemScreenController_onActionPerformed_5(ParticleSystemScreenController* particleSystemScreenController)
	: particleSystemScreenController(particleSystemScreenController)
{
}

void ParticleSystemScreenController_onActionPerformed_5::performAction()
{
	particleSystemScreenController->ppsTexture->getController()->setValue(MutableString(particleSystemScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName() + "/" + particleSystemScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName()));
	particleSystemScreenController->modelPath->setPath(particleSystemScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
	particleSystemScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
}
