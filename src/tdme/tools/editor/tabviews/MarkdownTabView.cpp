#include <tdme/tools/editor/tabviews/MarkdownTabView.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/tabcontrollers/MarkdownTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::MarkdownTabView;

using tdme::engine::Engine;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::MarkdownTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

MarkdownTabView::MarkdownTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->screenNode = screenNode;
	this->popUps = editorView->getPopUps();
	engine = Engine::createOffScreenInstance(512, 512, false, false, false);
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());
}

MarkdownTabView::~MarkdownTabView() {
	delete markdownTabController;
	delete engine;
}

void MarkdownTabView::handleInputEvents()
{
	engine->getGUI()->handleEvents();
}

void MarkdownTabView::display()
{
	engine->display();
	engine->getGUI()->render();
}

void MarkdownTabView::initialize()
{
	try {
		markdownTabController = new MarkdownTabController(this);
		markdownTabController->initialize(editorView->getScreenController()->getScreenNode());
		screenNode->addTooltipRequestListener(markdownTabController);
	} catch (Exception& exception) {
		Console::println("MarkdownTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings
}

void MarkdownTabView::dispose()
{
	engine->dispose();
}

void MarkdownTabView::updateRendering() {
}

Engine* MarkdownTabView::getEngine() {
	return engine;
}

void MarkdownTabView::activate() {
	markdownTabController->setOutlinerAddDropDownContent();
	markdownTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
}

void MarkdownTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void MarkdownTabView::reloadOutliner() {
	markdownTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

