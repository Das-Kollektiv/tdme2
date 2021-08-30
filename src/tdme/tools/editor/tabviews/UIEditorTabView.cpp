#include <tdme/tools/editor/tabviews/UIEditorTabView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabcontrollers/UIEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::UIEditorTabView;

using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::UIEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

UIEditorTabView::UIEditorTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->uiScreenNode = screenNode;
	engine = Engine::createOffScreenInstance(512, 512, false);
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());
	outlinerState.expandedOutlinerParentOptionValues.push_back("0");
}

UIEditorTabView::~UIEditorTabView() {
	delete uiTabController;
	delete engine;
}

void UIEditorTabView::handleInputEvents()
{
	engine->getGUI()->handleEvents();
}

void UIEditorTabView::display()
{
	engine->display();
	engine->getGUI()->render();
}

void UIEditorTabView::initialize()
{
	try {
		uiTabController = new UIEditorTabController(this);
		uiTabController->initialize(editorView->getScreenController()->getScreenNode());
	} catch (Exception& exception) {
		Console::print(string("UIEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	// TODO: load settings
}

void UIEditorTabView::dispose()
{
	engine->dispose();
}

void UIEditorTabView::updateRendering() {
}

Engine* UIEditorTabView::getEngine() {
	return engine;
}

void UIEditorTabView::activate() {
	uiTabController->setOutlinerAddDropDownContent();
	uiTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
}

void UIEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void UIEditorTabView::reloadOutliner() {
	uiTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

