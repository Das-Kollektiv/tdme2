#include <tdme/tools/shared/controller/ModelViewerScreenController_onModelSave_3.h>

#include <java/lang/String.h>

#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ModelViewerScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Exception.h>

using java::lang::String;

using tdme::tools::shared::controller::ModelViewerScreenController_onModelSave_3;
using java::lang::String;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ModelViewerScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedModelViewerView;
using tdme::utils::StringConverter;
using tdme::utils::_Exception;

ModelViewerScreenController_onModelSave_3::ModelViewerScreenController_onModelSave_3(ModelViewerScreenController* modelViewerScreenController)
	: modelViewerScreenController(modelViewerScreenController)
{
}

void ModelViewerScreenController_onModelSave_3::performAction()
{
	try {
		modelViewerScreenController->view->saveFile(
			modelViewerScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName(),
			modelViewerScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getFileName()
		);
		modelViewerScreenController->modelPath->setPath(
			modelViewerScreenController->view->getPopUpsViews()->getFileDialogScreenController()->getPathName()
		);
		modelViewerScreenController->view->getPopUpsViews()->getFileDialogScreenController()->close();
	} catch (_Exception& exception) {
		modelViewerScreenController->showErrorPopUp(L"Warning", StringConverter::toWideString(string(exception.what())));
	}
}
