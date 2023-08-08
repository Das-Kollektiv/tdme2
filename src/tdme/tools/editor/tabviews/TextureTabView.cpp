#include <tdme/tools/editor/tabviews/TextureTabView.h>

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/tabcontrollers/TextureTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using tdme::tools::editor::tabviews::TextureTabView;

using tdme::engine::Engine;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::TextureTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

TextureTabView::TextureTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->screenNode = screenNode;
	this->popUps = editorView->getPopUps();
	engine = unique_ptr<Engine>(Engine::createOffScreenInstance(512, 512, false, false, false));
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());
}

TextureTabView::~TextureTabView() {
}

void TextureTabView::handleInputEvents()
{
	engine->getGUI()->handleEvents();
}

void TextureTabView::display()
{
	engine->display();
	engine->getGUI()->render();
}

void TextureTabView::initialize()
{
	try {
		textureTabController = make_unique<TextureTabController>(this);
		textureTabController->initialize(editorView->getScreenController()->getScreenNode());
		screenNode->addTooltipRequestListener(textureTabController.get());
	} catch (Exception& exception) {
		Console::println("TextureTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings
}

void TextureTabView::dispose()
{
	engine->dispose();
}

void TextureTabView::updateRendering() {
}

Engine* TextureTabView::getEngine() {
	return engine.get();
}

void TextureTabView::activate() {
	textureTabController->setOutlinerAddDropDownContent();
	textureTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
}

void TextureTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void TextureTabView::reloadOutliner() {
	textureTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

