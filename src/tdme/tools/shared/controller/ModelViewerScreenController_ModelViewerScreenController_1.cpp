#include <tdme/tools/shared/controller/ModelViewerScreenController_ModelViewerScreenController_1.h>

#include <tdme/tools/shared/controller/ModelViewerScreenController.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>

using tdme::tools::shared::controller::ModelViewerScreenController_ModelViewerScreenController_1;
using tdme::tools::shared::controller::ModelViewerScreenController;
using tdme::tools::shared::views::SharedModelViewerView;

ModelViewerScreenController_ModelViewerScreenController_1::ModelViewerScreenController_ModelViewerScreenController_1(ModelViewerScreenController* modelViewerScreenController, SharedModelViewerView* finalView)
	: modelViewerScreenController(modelViewerScreenController)
	, finalView(finalView)
{
}

void ModelViewerScreenController_ModelViewerScreenController_1::performAction()
{
	finalView->updateGUIElements();
	finalView->onSetEntityData();
}
