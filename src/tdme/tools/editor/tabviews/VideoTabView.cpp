#include <tdme/tools/editor/tabviews/VideoTabView.h>

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/tabcontrollers/VideoTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using tdme::tools::editor::tabviews::VideoTabView;

using tdme::engine::Engine;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::VideoTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

VideoTabView::VideoTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode)
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

VideoTabView::~VideoTabView() {
}

void VideoTabView::handleInputEvents()
{
	engine->getGUI()->handleEvents();
}

void VideoTabView::display()
{
	engine->display();
	engine->getGUI()->render();
}

void VideoTabView::initialize()
{
	try {
		videoTabController = make_unique<VideoTabController>(this);
		videoTabController->initialize(editorView->getScreenController()->getScreenNode());
		screenNode->addTooltipRequestListener(videoTabController.get());
	} catch (Exception& exception) {
		Console::printLine("VideoTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings
}

void VideoTabView::dispose()
{
	engine->dispose();
}

void VideoTabView::updateRendering() {
}

Engine* VideoTabView::getEngine() {
	return engine.get();
}

void VideoTabView::activate() {
	videoTabController->setOutlinerAddDropDownContent();
	videoTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
}

void VideoTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void VideoTabView::reloadOutliner() {
	videoTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

