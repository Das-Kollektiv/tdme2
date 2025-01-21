#include <tdme/tools/editor/tabviews/EmptyEditorTabView.h>

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/prototypes/PrototypeWriter.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/tools/ThumbnailTool.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/engine/tools/CameraRotationInputHandler.h>
#include <tdme/engine/tools/ThumbnailTool.h>
#include <tdme/tools/editor/tabcontrollers/EmptyEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using tdme::tools::editor::tabviews::EmptyEditorTabView;

using tdme::engine::fileio::prototypes::PrototypeWriter;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::engine::tools::ThumbnailTool;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::engine::tools::CameraRotationInputHandler;
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
	this->prototype = unique_ptr<Prototype>(prototype);
	engine = unique_ptr<Engine>(Engine::createOffScreenInstance(512, 512, true, true, false));
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	Vector3 objectScale;
	cameraRotationInputHandler = make_unique<CameraRotationInputHandler>(engine.get());
	ThumbnailTool::setupPrototype(prototype, engine.get(), cameraRotationInputHandler->getLookFromRotations(), 1, objectScale, cameraRotationInputHandler.get());
	outlinerState.expandedOutlinerParentOptionValues.push_back("prototype");
}

EmptyEditorTabView::~EmptyEditorTabView() {
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
		emptyEditorTabController = make_unique<EmptyEditorTabController>(this);
		emptyEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
	} catch (Exception& exception) {
		Console::printLine("EmptyEditorTabView::initialize(): An error occurred: " + string(exception.what()));
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
	return engine.get();
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
	PrototypeWriter::write(pathName, fileName, prototype.get());
}
