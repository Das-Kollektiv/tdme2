#include <tdme/tools/editor/tabviews/FontTabView.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/tabcontrollers/FontTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::FontTabView;

using tdme::engine::Engine;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::FontTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

FontTabView::FontTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->screenNode = screenNode;
	this->popUps = editorView->getPopUps();
	engine = Engine::createOffScreenInstance(512, 512, true, false, false);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());
}

FontTabView::~FontTabView() {
	delete fontTabController;
	delete engine;
}

void FontTabView::handleInputEvents()
{
	engine->getGUI()->handleEvents();
}

void FontTabView::display()
{
	engine->display();
	engine->getGUI()->render();
}

void FontTabView::initialize()
{
	try {
		fontTabController = new FontTabController(this);
		fontTabController->initialize(editorView->getScreenController()->getScreenNode());
		screenNode->addTooltipRequestListener(fontTabController);
	} catch (Exception& exception) {
		Console::print(string("FontTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	// TODO: load settings
	// TODO: reloadTabOutliner
}

void FontTabView::dispose()
{
	engine->dispose();
}

void FontTabView::updateRendering() {
}

Engine* FontTabView::getEngine() {
	return engine;
}

void FontTabView::activate() {
	fontTabController->setOutlinerAddDropDownContent();
	fontTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
}

void FontTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void FontTabView::reloadOutliner() {
	fontTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

