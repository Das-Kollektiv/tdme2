#include <tdme/tools/editor/tabviews/TriggerEditorTabView.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/prototypes/PrototypeWriter.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandler.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>
#include <tdme/tools/editor/tabcontrollers/TriggerEditorTabController.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeDisplaySubView.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::TriggerEditorTabView;

using tdme::engine::fileio::prototypes::PrototypeWriter;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::TriggerEditorTabController;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

TriggerEditorTabView::TriggerEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->prototype = prototype;
	engine = Engine::createOffScreenInstance(512, 512, true, true, false);
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	cameraRotationInputHandler = new CameraRotationInputHandler(engine);
	Tools::setupPrototype(prototype, engine, cameraRotationInputHandler->getLookFromRotations(), 1, objectScale, cameraRotationInputHandler);
	outlinerState.expandedOutlinerParentOptionValues.push_back("prototype");
}

TriggerEditorTabView::~TriggerEditorTabView() {
	delete prototype;
	delete triggerEditorTabController;
	delete cameraRotationInputHandler;
	delete engine;

}

void TriggerEditorTabView::handleInputEvents()
{
	prototypePhysicsView->handleInputEvents(prototype);
	cameraRotationInputHandler->handleInputEvents();
}

void TriggerEditorTabView::display()
{
	//
	triggerEditorTabController->updateInfoText(MutableString(engine->getTiming()->getAvarageFPS()).append(" FPS"));

	//
	prototypeDisplayView->display(prototype);
	prototypePhysicsView->display(prototype);
	engine->display();
}

void TriggerEditorTabView::initialize()
{
	try {
		triggerEditorTabController = new TriggerEditorTabController(this);
		triggerEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
		prototypeDisplayView = triggerEditorTabController->getPrototypeDisplaySubController()->getView();
		prototypePhysicsView = triggerEditorTabController->getPrototypePhysicsSubController()->getView();
	} catch (Exception& exception) {
		Console::println("TriggerEditorTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings
	if (prototypePhysicsView != nullptr) prototypePhysicsView->setObjectScale(objectScale);
}

void TriggerEditorTabView::dispose()
{
	engine->reset();
}

void TriggerEditorTabView::updateRendering() {
}

Engine* TriggerEditorTabView::getEngine() {
	return engine;
}

void TriggerEditorTabView::activate() {
	triggerEditorTabController->setOutlinerAddDropDownContent();
	triggerEditorTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	triggerEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void TriggerEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void TriggerEditorTabView::reloadOutliner() {
	triggerEditorTabController->setOutlinerContent();
	triggerEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void TriggerEditorTabView::saveFile(const string& pathName, const string& fileName) {
	PrototypeWriter::write(pathName, fileName, prototype);
}

void TriggerEditorTabView::onCameraRotation() {
	prototypePhysicsView->updateGizmo(prototype);
}

void TriggerEditorTabView::onCameraScale() {
	prototypePhysicsView->updateGizmo(prototype);
}
