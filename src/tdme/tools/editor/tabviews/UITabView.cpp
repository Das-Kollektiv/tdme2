#include <tdme/tools/editor/tabviews/UITabView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabcontrollers/UITabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::UITabView;

using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::UITabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

UITabView::UITabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode)
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

UITabView::~UITabView() {
}

void UITabView::handleInputEvents()
{
	engine->getGUI()->handleEvents();
}

void UITabView::display()
{
	engine->display();
	engine->getGUI()->render();
}

void UITabView::initialize()
{
	try {
		uiTabController = new UITabController(this);
		uiTabController->initialize(editorView->getScreenController()->getScreenNode());
	} catch (Exception& exception) {
		Console::print(string("UITabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	// TODO: load settings
	// TODO: reloadTabOutliner
}

void UITabView::dispose()
{
	engine->reset();
	delete uiTabController;
}

void UITabView::updateRendering() {
}

Engine* UITabView::getEngine() {
	return engine;
}

void UITabView::activate() {
	// uiTabController->setOutlinerAddDropDownContent();
	uiTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	// uiTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void UITabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void UITabView::reloadOutliner() {
	uiTabController->setOutlinerContent();
}

