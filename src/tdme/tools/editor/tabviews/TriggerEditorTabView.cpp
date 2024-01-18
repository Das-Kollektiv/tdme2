#include <tdme/tools/editor/tabviews/TriggerEditorTabView.h>

#include <memory>
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

using std::make_unique;
using std::string;
using std::unique_ptr;

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
	this->prototype = unique_ptr<Prototype>(prototype);
	engine = unique_ptr<Engine>(Engine::createOffScreenInstance(512, 512, true, true, false));
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	cameraRotationInputHandler = make_unique<CameraRotationInputHandler>(engine.get()	);
	Tools::setupPrototype(prototype, engine.get(), cameraRotationInputHandler->getLookFromRotations(), 1, objectScale, cameraRotationInputHandler.get());
	outlinerState.expandedOutlinerParentOptionValues.push_back("prototype");
}

TriggerEditorTabView::~TriggerEditorTabView() {
}

void TriggerEditorTabView::handleInputEvents()
{
	prototypePhysicsView->handleInputEvents(prototype.get());
	cameraRotationInputHandler->handleInputEvents();
}

void TriggerEditorTabView::display()
{
	//
	triggerEditorTabController->updateInfoText(MutableString(engine->getTiming()->getAvarageFPS()).append(" FPS"));

	//
	prototypeDisplayView->display(prototype.get());
	prototypePhysicsView->display(prototype.get());
	engine->display();
}

void TriggerEditorTabView::initialize()
{
	try {
		triggerEditorTabController = make_unique<TriggerEditorTabController>(this);
		triggerEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
		prototypeDisplayView = triggerEditorTabController->getPrototypeDisplaySubController()->getView();
		prototypePhysicsView = triggerEditorTabController->getPrototypePhysicsSubController()->getView();
	} catch (Exception& exception) {
		Console::printLine("TriggerEditorTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings
	if (prototypePhysicsView != nullptr) prototypePhysicsView->setObjectScale(objectScale);
}

void TriggerEditorTabView::dispose()
{
	engine->dispose();
}

void TriggerEditorTabView::updateRendering() {
}

Engine* TriggerEditorTabView::getEngine() {
	return engine.get();
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
	PrototypeWriter::write(pathName, fileName, prototype.get());
}

void TriggerEditorTabView::onCameraRotation() {
	prototypePhysicsView->updateGizmo(prototype.get());
}

void TriggerEditorTabView::onCameraScale() {
	prototypePhysicsView->updateGizmo(prototype.get());
}
