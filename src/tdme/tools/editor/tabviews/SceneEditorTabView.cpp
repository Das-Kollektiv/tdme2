#include <tdme/tools/editor/tabviews/SceneEditorTabView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabcontrollers/SceneEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;
using std::to_string;

using tdme::tools::editor::tabviews::SceneEditorTabView;

using tdme::engine::Engine;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::SceneEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

SceneEditorTabView::SceneEditorTabView(EditorView* editorView, const string& tabId, const string& fileName)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	engine = Engine::createOffScreenInstance(512, 512, true);
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	Console::println("SceneEditorTabView::SceneEditorTabView(): " + fileName);
}

SceneEditorTabView::~SceneEditorTabView() {
}

EditorView* SceneEditorTabView::getEditorView() {
	return editorView;
}

TabController* SceneEditorTabView::getTabController() {
	return sceneEditorTabController;
}

PopUps* SceneEditorTabView::getPopUps()
{
	return popUps;
}

const string& SceneEditorTabView::getFileName()
{
	return sceneFileName;
}

void SceneEditorTabView::handleInputEvents()
{
}

void SceneEditorTabView::display()
{
	engine->display();
}

void SceneEditorTabView::initialize()
{
	try {
		sceneEditorTabController = new SceneEditorTabController(this);
	} catch (Exception& exception) {
		Console::print(string("SceneEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	// TODO: load settings
	// TODO: reloadTabOutliner
}

void SceneEditorTabView::dispose()
{
	engine->reset();
	delete sceneEditorTabController;
}

void SceneEditorTabView::updateRendering() {
}

Engine* SceneEditorTabView::getEngine() {
	return engine;
}

void SceneEditorTabView::activate() {
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
}

void SceneEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void SceneEditorTabView::reloadOutliner() {
}
