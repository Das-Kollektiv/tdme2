#include <tdme/tools/editor/tabviews/ParticleSystemEditorTabView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandler.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandlerEventHandler.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandler.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabcontrollers/ParticleSystemEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::ParticleSystemEditorTabView;

using tdme::engine::Engine;
using tdme::engine::prototype::Prototype;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::CameraRotationInputHandlerEventHandler;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::ParticleSystemEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

ParticleSystemEditorTabView::ParticleSystemEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->prototype = prototype;
	engine = Engine::createOffScreenInstance(512, 512, true);
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	cameraRotationInputHandler = new CameraRotationInputHandler(engine, this);
	Tools::setupPrototype(prototype, engine, cameraRotationInputHandler->getLookFromRotations(), cameraRotationInputHandler->getScale(), 1, objectScale);
}

ParticleSystemEditorTabView::~ParticleSystemEditorTabView() {
	delete particleSystemEditorTabController;
}

EditorView* ParticleSystemEditorTabView::getEditorView() {
	return editorView;
}

TabController* ParticleSystemEditorTabView::getTabController() {
	return particleSystemEditorTabController;
}

PopUps* ParticleSystemEditorTabView::getPopUps()
{
	return popUps;
}

void ParticleSystemEditorTabView::handleInputEvents()
{
}

void ParticleSystemEditorTabView::display()
{
	engine->display();
}

void ParticleSystemEditorTabView::initialize()
{
	try {
		particleSystemEditorTabController = new ParticleSystemEditorTabController(this);
	} catch (Exception& exception) {
		Console::print(string("ParticleSystemEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	// TODO: load settings
	// TODO: reloadTabOutliner
}

void ParticleSystemEditorTabView::dispose()
{
	engine->reset();
	delete particleSystemEditorTabController;
}

void ParticleSystemEditorTabView::updateRendering() {
}

Engine* ParticleSystemEditorTabView::getEngine() {
	return engine;
}

void ParticleSystemEditorTabView::activate() {
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
}

void ParticleSystemEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void ParticleSystemEditorTabView::reloadOutliner() {
}

void ParticleSystemEditorTabView::onCameraRotation() {
}

void ParticleSystemEditorTabView::onCameraScale() {
}
