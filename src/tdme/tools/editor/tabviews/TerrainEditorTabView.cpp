#include <tdme/tools/editor/tabviews/TerrainEditorTabView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabcontrollers/TerrainEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::TerrainEditorTabView;

using tdme::engine::Engine;
using tdme::engine::prototype::Prototype;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::TerrainEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

TerrainEditorTabView::TerrainEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->prototype = prototype;
	engine = Engine::createOffScreenInstance(512, 512, false);
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
}

TerrainEditorTabView::~TerrainEditorTabView() {
	delete prototype;
}

void TerrainEditorTabView::handleInputEvents()
{
	engine->getGUI()->handleEvents();
}

void TerrainEditorTabView::display()
{
	engine->display();
	engine->getGUI()->render();
}

void TerrainEditorTabView::initialize()
{
	try {
		terrainEditorTabController = new TerrainEditorTabController(this);
		terrainEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
	} catch (Exception& exception) {
		Console::print(string("TerrainEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	// TODO: load settings
	// TODO: reloadTabOutliner
}

void TerrainEditorTabView::dispose()
{
	engine->reset();
	delete terrainEditorTabController;
}

void TerrainEditorTabView::updateRendering() {
}

Engine* TerrainEditorTabView::getEngine() {
	return engine;
}

void TerrainEditorTabView::activate() {
	// uiTabController->setOutlinerAddDropDownContent();
	terrainEditorTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
}

void TerrainEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void TerrainEditorTabView::reloadOutliner() {
	terrainEditorTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

