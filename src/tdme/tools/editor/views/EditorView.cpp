#include <tdme/tools/editor/views/EditorView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/PartitionNone.h>
#include <tdme/gui/nodes/GUIFrameBufferNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/TDMEEditor.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::PartitionNone;
using tdme::gui::nodes::GUIFrameBufferNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::TDMEEditor;
using tdme::utilities::Console;
using tdme::utilities::Exception;

EditorView::EditorView(PopUps* popUps)
{
	this->popUps = popUps;
	editorScreenController = nullptr;
	engine = Engine::getInstance();
}

EditorView::~EditorView() {
	delete editorScreenController;
}

PopUps* EditorView::getPopUps()
{
	return popUps;
}

void EditorView::handleInputEvents()
{
	auto selectedTabId = editorScreenController->getSelectedTabId();
	auto& tabViews = editorScreenController->getTabViews();
	auto tabViewIt = tabViews.find(selectedTabId);
	if (tabViewIt != tabViews.end()){
		int left, top, width, height;
		getViewPort(left, top, width, height);
		auto& tab = tabViewIt->second;
		if (lastSelectedTabId != selectedTabId) tab.getTabView()->activate();
		for (auto event: Engine::getInstance()->getGUI()->getMouseEvents()) {
			auto eventX = event.getXUnscaled();
			auto eventY = event.getYUnscaled();
			event.setX(eventX - left);
			event.setY(eventY - top);
			event.setXUnscaled(eventX - left);
			event.setYUnscaled(eventY - top);
			tab.getEngine()->getGUI()->getMouseEvents().push_back(event);
		}
		for (auto& event: Engine::getInstance()->getGUI()->getKeyboardEvents()) {
			tab.getEngine()->getGUI()->getKeyboardEvents().push_back(event);
		}
		tab.getTabView()->handleInputEvents();
		tab.getEngine()->getGUI()->getMouseEvents().clear();
		tab.getEngine()->getGUI()->getKeyboardEvents().clear();
	}
	lastSelectedTabId = selectedTabId;
}

void EditorView::display()
{
	auto selectedTabId = editorScreenController->getSelectedTabId();
	auto& tabViews = editorScreenController->getTabViews();
	auto tabViewIt = tabViews.find(selectedTabId);
	if (tabViewIt != tabViews.end()){
		int left, top, width, height;
		getViewPort(left, top, width, height);
		auto& tab = tabViewIt->second;
		if (tab.getEngine()->getWidth() != width || tab.getEngine()->getHeight() != height) tab.getEngine()->reshape(width, height);
		tab.getTabView()->display();
		tab.getFrameBufferNode()->setFrameBuffer(tab.getEngine()->getFrameBuffer());
	}
}

void EditorView::updateGUIElements()
{
}

void EditorView::initialize()
{
	try {
		editorScreenController = new EditorScreenController(this);
		editorScreenController->initialize();
		engine->getGUI()->addScreen(editorScreenController->getScreenNode()->getId(), editorScreenController->getScreenNode());
		editorScreenController->getScreenNode()->setInputEventHandler(this);
	} catch (Exception& exception) {
		Console::print(string("EditorView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	updateGUIElements();
}

void EditorView::activate()
{
	engine->reset();
	engine->setPartition(new PartitionNone());
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->getGUI()->resetRenderScreens();
	engine->getGUI()->addRenderScreen(editorScreenController->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());
}

void EditorView::deactivate()
{
}

void EditorView::dispose()
{
	Engine::getInstance()->reset();
}

void EditorView::setOutlinerContent(const string& xml) {
	editorScreenController->setOutlinerContent(xml);
}

void EditorView::setDetailsContent(const string& xml) {
	editorScreenController->setDetailsContent(xml);
}

void EditorView::reloadTabOutliner(const string& newSelectionId) {
	auto selectedTabId = editorScreenController->getSelectedTabId();
	auto& tabViews = editorScreenController->getTabViews();
	auto tabViewIt = tabViews.find(selectedTabId);
	if (tabViewIt != tabViews.end()){
		auto& tab = tabViewIt->second;
		tab.getTabView()->reloadOutliner();
	}
}

void EditorView::getViewPort(int& left, int& top, int& width, int& height) {
	auto xScale = (float)engine->getWidth() / (float)editorScreenController->getScreenNode()->getScreenWidth();
	auto yScale = (float)engine->getHeight() / (float)editorScreenController->getScreenNode()->getScreenHeight();
	editorScreenController->getViewPort(left, top, width, height);
	left*= xScale;
	top*= yScale;
	width*= xScale;
	height*= yScale;
}
