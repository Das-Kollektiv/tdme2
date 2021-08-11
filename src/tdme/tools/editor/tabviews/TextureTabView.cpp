#include <tdme/tools/editor/tabviews/TextureTabView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabcontrollers/TextureTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::TextureTabView;

using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::TextureTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

TextureTabView::TextureTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->uiScreenNode = screenNode;
	engine = Engine::createOffScreenInstance(512, 512, true);
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
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
		uiTabController = new TextureTabController(this);
		uiTabController->initialize(editorView->getScreenController()->getScreenNode());
	} catch (Exception& exception) {
		Console::print(string("TextureTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	// TODO: load settings
	// TODO: reloadTabOutliner
}

void TextureTabView::dispose()
{
	engine->reset();
	delete uiTabController;
}

void TextureTabView::updateRendering() {
}

Engine* TextureTabView::getEngine() {
	return engine;
}

void TextureTabView::activate() {
	// uiTabController->setOutlinerAddDropDownContent();
	uiTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
}

void TextureTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void TextureTabView::reloadOutliner() {
	uiTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

