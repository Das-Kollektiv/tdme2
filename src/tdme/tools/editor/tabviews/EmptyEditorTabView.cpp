#include <tdme/tools/editor/tabviews/EmptyEditorTabView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabcontrollers/EmptyEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::EmptyEditorTabView;

using tdme::engine::Engine;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::EmptyEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

EmptyEditorTabView::EmptyEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	engine = Engine::createOffScreenInstance(512, 512, true, false);
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
}

EmptyEditorTabView::~EmptyEditorTabView() {
}

EditorView* EmptyEditorTabView::getEditorView() {
	return editorView;
}

TabController* EmptyEditorTabView::getTabController() {
	return emptyEditorTabController;
}

PopUps* EmptyEditorTabView::getPopUps()
{
	return popUps;
}

void EmptyEditorTabView::handleInputEvents()
{
}

void EmptyEditorTabView::display()
{
	engine->display();
}

void EmptyEditorTabView::initialize()
{
	try {
		emptyEditorTabController = new EmptyEditorTabController(this);
	} catch (Exception& exception) {
		Console::print(string("EmptyEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	// TODO: load settings
}

void EmptyEditorTabView::dispose()
{
	engine->reset();
	delete emptyEditorTabController;
}

void EmptyEditorTabView::updateRendering() {
}

Engine* EmptyEditorTabView::getEngine() {
	return engine;
}

void EmptyEditorTabView::activate() {
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
}

void EmptyEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void EmptyEditorTabView::reloadOutliner() {
}
