#include <tdme/tools/editor/tabviews/DecalEditorTabView.h>

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
#include <tdme/tools/editor/tabcontrollers/DecalEditorTabController.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeDisplaySubView.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using tdme::tools::editor::tabviews::DecalEditorTabView;

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
using tdme::tools::editor::tabcontrollers::DecalEditorTabController;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

DecalEditorTabView::DecalEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->prototype = unique_ptr<Prototype>(prototype);
	engine = unique_ptr<Engine>(Engine::createOffScreenInstance(512, 512, true, true, false));
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	cameraRotationInputHandler = make_unique<CameraRotationInputHandler>(engine.get());
	Tools::setupPrototype(prototype, engine.get(), cameraRotationInputHandler->getLookFromRotations(), 1, objectScale, cameraRotationInputHandler.get());
	outlinerState.expandedOutlinerParentOptionValues.push_back("prototype");
}

DecalEditorTabView::~DecalEditorTabView() {
}

void DecalEditorTabView::handleInputEvents()
{
	prototypePhysicsView->handleInputEvents(prototype.get());
	cameraRotationInputHandler->handleInputEvents();
}

void DecalEditorTabView::display()
{
	//
	decalEditorTabController->updateInfoText(MutableString(engine->getTiming()->getAvarageFPS()).append(" FPS"));

	//
	prototypeDisplayView->display(prototype.get());
	prototypePhysicsView->display(prototype.get());
	engine->display();
}

void DecalEditorTabView::initialize()
{
	try {
		decalEditorTabController = make_unique<DecalEditorTabController>(this);
		decalEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
		prototypeDisplayView = decalEditorTabController->getPrototypeDisplaySubController()->getView();
		prototypePhysicsView = decalEditorTabController->getPrototypePhysicsSubController()->getView();
	} catch (Exception& exception) {
		Console::println("DecalEditorTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings
	if (prototypePhysicsView != nullptr) prototypePhysicsView->setObjectScale(objectScale);
}

void DecalEditorTabView::dispose()
{
	engine->reset();
}

void DecalEditorTabView::updateRendering() {
}

Engine* DecalEditorTabView::getEngine() {
	return engine.get();
}

void DecalEditorTabView::activate() {
	decalEditorTabController->setOutlinerAddDropDownContent();
	decalEditorTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	decalEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void DecalEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void DecalEditorTabView::reloadOutliner() {
	decalEditorTabController->setOutlinerContent();
	decalEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void DecalEditorTabView::saveFile(const string& pathName, const string& fileName) {
	PrototypeWriter::write(pathName, fileName, prototype.get());
}

void DecalEditorTabView::onCameraRotation() {
	prototypePhysicsView->updateGizmo(prototype.get());
}

void DecalEditorTabView::onCameraScale() {
	prototypePhysicsView->updateGizmo(prototype.get());
}
