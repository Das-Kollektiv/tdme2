#include <tdme/tools/editor/tabviews/FontTabView.h>

#include <memory>
#include <string>

#include <agui/agui.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/tabcontrollers/FontTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using tdme::tools::editor::tabviews::FontTabView;

using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;

using tdme::engine::Engine;
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
	engine = unique_ptr<Engine>(Engine::createOffScreenInstance(512, 512, true, false, false));
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());
}

FontTabView::~FontTabView() {
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
		fontTabController = make_unique<FontTabController>(this);
		fontTabController->initialize(editorView->getScreenController()->getScreenNode());
		screenNode->addTooltipRequestListener(fontTabController.get());
	} catch (Exception& exception) {
		Console::printLine("FontTabView::initialize(): An error occurred: " + string(exception.what()));
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
	return engine.get();
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

