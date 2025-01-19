#include <tdme/tools/editor/tabviews/MarkdownTabView.h>

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/tabcontrollers/MarkdownTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

using tdme::tools::editor::tabviews::MarkdownTabView;

using tdme::engine::Engine;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::MarkdownTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

MarkdownTabView::MarkdownTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode, const vector<Markdown::TOCEntry>& toc)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->screenNode = screenNode;
	this->popUps = editorView->getPopUps();
	this->toc = toc;
	engine = unique_ptr<Engine>(Engine::createOffScreenInstance(512, 512, false, false, false));
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());
}

MarkdownTabView::~MarkdownTabView() {
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
		markdownTabController = make_unique<MarkdownTabController>(this);
		markdownTabController->initialize(editorView->getScreenController()->getScreenNode());
		screenNode->addTooltipRequestListener(markdownTabController.get());
	} catch (Exception& exception) {
		Console::printLine("MarkdownTabView::initialize(): An error occurred: " + string(exception.what()));
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
	return engine.get();
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

