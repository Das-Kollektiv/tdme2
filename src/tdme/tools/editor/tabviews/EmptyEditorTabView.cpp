#include <tdme/tools/editor/tabviews/EmptyEditorTabView.h>

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
#include <tdme/tools/editor/tabcontrollers/EmptyEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::EmptyEditorTabView;

using tdme::engine::fileio::prototypes::PrototypeWriter;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::EmptyEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

EmptyEditorTabView::EmptyEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->prototype = prototype;
	engine = Engine::createOffScreenInstance(512, 512, true, true, false);
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	Vector3 objectScale;
	cameraRotationInputHandler = new CameraRotationInputHandler(engine);
	Tools::setupPrototype(prototype, engine, cameraRotationInputHandler->getLookFromRotations(), 1, objectScale, cameraRotationInputHandler);
	outlinerState.expandedOutlinerParentOptionValues.push_back("prototype");
}

EmptyEditorTabView::~EmptyEditorTabView() {
	delete prototype;
	delete emptyEditorTabController;
	delete cameraRotationInputHandler;
	delete engine;

}

void EmptyEditorTabView::handleInputEvents()
{
}

void EmptyEditorTabView::display()
{
	emptyEditorTabController->updateInfoText(MutableString(engine->getTiming()->getAvarageFPS()).append(" FPS"));
	engine->display();
}

void EmptyEditorTabView::initialize()
{
	try {
		emptyEditorTabController = new EmptyEditorTabController(this);
		emptyEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
	} catch (Exception& exception) {
		Console::println("EmptyEditorTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings
}

void EmptyEditorTabView::dispose()
{
	engine->reset();
}

void EmptyEditorTabView::updateRendering() {
}

Engine* EmptyEditorTabView::getEngine() {
	return engine;
}

void EmptyEditorTabView::activate() {
	emptyEditorTabController->setOutlinerAddDropDownContent();
	emptyEditorTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	emptyEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void EmptyEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void EmptyEditorTabView::reloadOutliner() {
	emptyEditorTabController->setOutlinerContent();
	emptyEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void EmptyEditorTabView::saveFile(const string& pathName, const string& fileName) {
	PrototypeWriter::write(pathName, fileName, prototype);
}
