#include <tdme/tools/editor/views/EditorView.h>

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/audio/Audio.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/SimplePartition.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/AboutDialogScreenController.h>
#include <tdme/tools/editor/controllers/ColorPickerScreenController.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/DraggingScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/FindReplaceDialogScreenController.h>
#include <tdme/tools/editor/controllers/ImportDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/InputDialogScreenController.h>
#include <tdme/tools/editor/controllers/ProgressBarScreenController.h>
#include <tdme/tools/editor/controllers/SelectorDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/Editor.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using std::make_unique;
using std::string;
using std::vector;
using std::unique_ptr;

using tdme::audio::Audio;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::SimplePartition;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::AboutDialogScreenController;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::DraggingScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::FindReplaceDialogScreenController;
using tdme::tools::editor::controllers::ImportDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::InputDialogScreenController;
using tdme::tools::editor::controllers::ProgressBarScreenController;
using tdme::tools::editor::controllers::SelectorDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::Editor;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;

EditorView::EditorView(PopUps* popUps)
{
	this->popUps = popUps;
	engine = Engine::getInstance();
}

EditorView::~EditorView() {
}

PopUps* EditorView::getPopUps()
{
	return popUps;
}

void EditorView::handleInputEvents()
{
	for (auto& event: Engine::getInstance()->getGUI()->getKeyboardEvents()) {
		// skip if already processed
		if (event.isProcessed() == true) return;

		// determine redo and undo
		if (Character::toLowerCase(event.getKeyChar()) == 'z' && event.isControlDown() == true && event.isShiftDown() == true) {
			if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				auto selectedTab = editorScreenController->getSelectedTab();
				if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_REDO);
			}
			event.setProcessed(true);
		} else
		if (Character::toLowerCase(event.getKeyChar()) == 'z' && event.isControlDown() == true) {
			if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				auto selectedTab = editorScreenController->getSelectedTab();
				if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_UNDO);
			}
			event.setProcessed(true);
		} else
		// determine select all, copy, paste, cut
		if (Character::toLowerCase(event.getKeyChar()) == 'a' && event.isControlDown() == true) {
			if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				auto selectedTab = editorScreenController->getSelectedTab();
				if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_SELECTALL);
			}
			event.setProcessed(true);
		} else
		if (Character::toLowerCase(event.getKeyChar()) == 'x' && event.isControlDown() == true) {
			if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				auto selectedTab = editorScreenController->getSelectedTab();
				if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_CUT);
			}
			event.setProcessed(true);
		} else
		if (Character::toLowerCase(event.getKeyChar()) == 'c' && event.isControlDown() == true) {
			if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				auto selectedTab = editorScreenController->getSelectedTab();
				if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_COPY);
			}
			event.setProcessed(true);
		} else
		if (Character::toLowerCase(event.getKeyChar()) == 'v' && event.isControlDown() == true) {
			if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				auto selectedTab = editorScreenController->getSelectedTab();
				if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_PASTE);
			}
			event.setProcessed(true);
		} else
		if (Character::toLowerCase(event.getKeyChar()) == 'f' && event.isControlDown() == true) {
			if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				auto selectedTab = editorScreenController->getSelectedTab();
				if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_FINDREPLACE);
			}
			event.setProcessed(true);
		} else
		if (Character::toLowerCase(event.getKeyChar()) == 's' && event.isControlDown() == true) {
			if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				auto selectedTab = editorScreenController->getSelectedTab();
				if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_SAVE);
			}
			event.setProcessed(true);
		} else
		if (Character::toLowerCase(event.getKeyChar()) == 'w' && event.isControlDown() == true) {
			if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				auto selectedTab = editorScreenController->getSelectedTab();
				if (selectedTab != nullptr) editorScreenController->closeTab(selectedTab->getId());
			}
			event.setProcessed(true);
		} else
		if (event.getKeyChar() >= '0' && event.getKeyChar() <= '9' && event.isControlDown() == true) {
			if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				if (event.getKeyChar() == '0') {
					editorScreenController->selectTabAt(10);
				} else {
					editorScreenController->selectTabAt(event.getKeyChar() - '1');
				}
			}
			event.setProcessed(true);
		} else {
			//
			switch (event.getKeyCode()) {
				case GUIKeyboardEvent::KEYCODE_PAGE_UP:
					if (event.isControlDown() == true) {
						if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							if (editorScreenController->getTabCount() > 0) {
								auto selectedTabIdx = editorScreenController->getSelectedTabIdx() - 1;
								if (selectedTabIdx == -1) selectedTabIdx = editorScreenController->getTabCount() - 1;
								editorScreenController->selectTabAt(selectedTabIdx);
							}
						}
						event.setProcessed(true);
					}
					break;
				case GUIKeyboardEvent::KEYCODE_PAGE_DOWN:
					if (event.isControlDown() == true) {
						if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							if (editorScreenController->getTabCount() > 0) {
								auto selectedTabIdx = editorScreenController->getSelectedTabIdx() + 1;
								if (selectedTabIdx == editorScreenController->getTabCount()) selectedTabIdx = 0;
								editorScreenController->selectTabAt(selectedTabIdx);
							}
						}
						event.setProcessed(true);
					}
					break;
				case GUIKeyboardEvent::KEYCODE_F4:
					if (event.isControlDown() == true) {
						if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							auto selectedTab = editorScreenController->getSelectedTab();
							if (selectedTab != nullptr) editorScreenController->closeTab(selectedTab->getId());
						}
						event.setProcessed(true);
					}
					break;
				case GUIKeyboardEvent::KEYCODE_F11:
					if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						editorScreenController->setFullScreen(editorScreenController->isFullScreen() == false?true:false);
					}
					event.setProcessed(true);
					break;
				case GUIKeyboardEvent::KEYCODE_F12:
					if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						try {
							if (FileSystem::getStandardFileSystem()->exists("./screenshots") == false) FileSystem::getStandardFileSystem()->createPath("./screenshots");
							Engine::getInstance()->makeScreenshot("./screenshots", "TDME2-Screenshot-" + StringTools::replace(Time::getAsString(), ':', '-') + ".png");
						} catch (Exception& exception) {
							Console::println("EditorView::handleInputEvents(): Could not create screenshot: " + string(exception.what()));
						}
					}
					event.setProcessed(true);
					break;
				default: break;
			}
		}
	}

	//
	auto tabView = editorScreenController->getSelectedTab();
	if (tabView != nullptr) {
		// deactivate old tab/activate new tab
		if (tabView->getId() != lastSelectedTabId) {
			auto lastTabView = lastSelectedTabId.empty() == true?nullptr:editorScreenController->getTab(lastSelectedTabId);
			if (lastTabView != nullptr) lastTabView->getTabView()->deactivate();
			tabView->getTabView()->activate();
			editorScreenController->getScreenNode()->invalidateLayout(editorScreenController->getScreenNode()->getNodeById(tabView->getFrameBufferNode()->getId()));
		}
		if (tabView->getTabView()->getEngine() != nullptr) {
			// get viewport position, dimension
			auto xScale = static_cast<float>(engine->getWidth()) / static_cast<float>(editorScreenController->getScreenNode()->getScreenWidth());
			auto yScale = static_cast<float>(engine->getHeight()) / static_cast<float>(editorScreenController->getScreenNode()->getScreenHeight());
			int left, top, width, height, offsetX, offsetY;
			getViewPort(tabView->getFrameBufferNode(), left, top, width, height, offsetX, offsetY);
			// forward mouse events if belonging to view
			for (auto event: Engine::getInstance()->getGUI()->getMouseEvents()) {
				// event position in our tab
				auto eventX = (event.getXUnscaled() - left) / xScale + offsetX;
				auto eventY = (event.getYUnscaled() - top) / yScale + offsetY;
				// out of tab bounds?
				if (eventX < 0 || eventX >= width || eventY < 0 || eventY >= height) {
					switch (event.getType()) {
						case GUIMouseEvent::MOUSEEVENT_RELEASED:
						case GUIMouseEvent::MOUSEEVENT_DRAGGED:
							// if no mouse down is registered on button do not forward the event to the tab
							if (mouseButtonsDown[event.getButton() - 1] == false) {
								continue;
							}
							break;
						default:
							break;
					}
				}
				// track mouse buttons down states
				switch (event.getType()) {
					case GUIMouseEvent::MOUSEEVENT_PRESSED:
						mouseButtonsDown[event.getButton() - 1] = true;
						break;
					case GUIMouseEvent::MOUSEEVENT_RELEASED:
						mouseButtonsDown[event.getButton() - 1] = false;
						break;
					default:
						break;
				}
				// pass the event on to tab
				event.setX(eventX);
				event.setY(eventY);
				event.setXUnscaled(eventX);
				event.setYUnscaled(eventY);
				tabView->getTabView()->getEngine()->getGUI()->getMouseEvents().push_back(event);
			}
			// just forward keyboard events
			for (auto& event: Engine::getInstance()->getGUI()->getKeyboardEvents()) {
				tabView->getTabView()->getEngine()->getGUI()->getKeyboardEvents().push_back(event);
			}
			// handle events
			tabView->getTabView()->handleInputEvents();
			//
			for (auto i = 0; i < Engine::getInstance()->getGUI()->getKeyboardEvents().size(); i++) {
				auto& srcEvent = Engine::getInstance()->getGUI()->getKeyboardEvents()[i];
				const auto& dstEvent = tabView->getTabView()->getEngine()->getGUI()->getKeyboardEvents()[i];
				if (dstEvent.isProcessed() == true) srcEvent.setProcessed(true);
			}
			// clear
			tabView->getTabView()->getEngine()->getGUI()->getMouseEvents().clear();
			tabView->getTabView()->getEngine()->getGUI()->getKeyboardEvents().clear();
		}
		// last tab
		lastSelectedTabId = tabView->getId();
	} else {
		// no current tab, just deactivate last one
		auto lastTabView = editorScreenController->getTab(lastSelectedTabId);
		if (lastTabView != nullptr) lastTabView->getTabView()->deactivate();
		lastSelectedTabId.clear();
	}
}

void EditorView::display()
{
	auto tabView = editorScreenController->getSelectedTab();
	if (tabView != nullptr) {
		auto xScale = static_cast<float>(engine->getWidth()) / static_cast<float>(editorScreenController->getScreenNode()->getScreenWidth());
		auto yScale = static_cast<float>(engine->getHeight()) / static_cast<float>(editorScreenController->getScreenNode()->getScreenHeight());
		int left, top, width, height, offsetX, offsetY;
		getViewPort(tabView->getFrameBufferNode()->getParentNode(), left, top, width, height, offsetX, offsetY);
		width/= xScale;
		height/= yScale;
		auto reshaped = false;
		if (tabView->getTabView()->hasFixedSize() == false &&
			tabView->getTabView()->getEngine() != nullptr &&
			(tabView->getTabView()->getEngine()->getWidth() != width || tabView->getTabView()->getEngine()->getHeight() != height)) {
			tabView->getTabView()->getEngine()->reshape(width, height);
			reshaped = true;
		}
		if (tabView->getTabView()->getEngine() != nullptr) {
			tabView->getFrameBufferNode()->setFrameBuffer(tabView->getTabView()->getEngine()->getFrameBuffer());
		}
		tabView->getTabView()->display();
		if (reshaped == true) {
			editorScreenController->getScreenNode()->invalidateLayout(editorScreenController->getScreenNode()->getNodeById(tabView->getFrameBufferNode()->getId()));
		}
	}
	//
	Audio::getInstance()->update();
}

void EditorView::updateGUIElements()
{
}

void EditorView::initialize()
{
	try {
		editorScreenController = make_unique<EditorScreenController>(this);
		editorScreenController->initialize();
		engine->getGUI()->addScreen(editorScreenController->getScreenNode()->getId(), editorScreenController->getScreenNode());
		editorScreenController->getScreenNode()->setInputEventHandler(this);
	} catch (Exception& exception) {
		Console::println("EditorView::initialize(): An error occurred: " + string(exception.what()));
	}
	updateGUIElements();
}

void EditorView::activate()
{
	engine->reset();
	engine->setPartition(new SimplePartition());
	engine->getGUI()->resetRenderScreens();
	engine->getGUI()->addRenderScreen(editorScreenController->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getAboutDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getImportDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getColorPickerScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getFindReplaceDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getInputDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getSelectorDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getContextMenuScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getProgressBarScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getTooltipScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getDraggingScreenController()->getScreenNode()->getId());
}

void EditorView::deactivate()
{
}

void EditorView::dispose()
{
	editorScreenController->dispose();
	Engine::getInstance()->reset();
}

void EditorView::tick()
{
	//
	editorScreenController->tick();
}

void EditorView::setOutlinerContent(const string& xml) {
	editorScreenController->setOutlinerContent(xml);
}

void EditorView::setOutlinerAddDropDownContent(const string& xml) {
	editorScreenController->setOutlinerAddDropDownContent(xml);
}

void EditorView::setDetailsContent(const string& xml) {
	editorScreenController->setDetailsContent(xml);
}

void EditorView::reloadTabOutliner(const string& newSelectionValue) {
	auto tabView = editorScreenController->getSelectedTab();
	if (tabView != nullptr) {
		TabView::OutlinerState outlinerState;
		editorScreenController->storeOutlinerState(outlinerState);
		tabView->getTabView()->reloadOutliner();
		if (newSelectionValue.empty() == false) outlinerState.value = newSelectionValue;
		editorScreenController->restoreOutlinerState(outlinerState);
	}
	editorScreenController->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(editorScreenController->getScreenNode()->getNodeById("selectbox_outliner")));
}

bool EditorView::getCurrentTabViewPort(int& left, int& top, int& width, int& height, int& offsetX, int& offsetY) {
	auto currentTab = editorScreenController->getSelectedTab();
	if (currentTab == nullptr) return false;
	getViewPort(currentTab->getFrameBufferNode(), left, top, width, height, offsetX, offsetY);
	return true;
}

void EditorView::getViewPort(GUINode* viewPortNode, int& left, int& top, int& width, int& height, int& offsetX, int& offsetY) {
	auto xScale = static_cast<float>(engine->getWidth()) / static_cast<float>(editorScreenController->getScreenNode()->getScreenWidth());
	auto yScale = static_cast<float>(engine->getHeight()) / static_cast<float>(editorScreenController->getScreenNode()->getScreenHeight());
	editorScreenController->getViewPort(viewPortNode, left, top, width, height);
	left = static_cast<int>(static_cast<float>(left) * xScale);
	top = static_cast<int>(static_cast<float>(top) * yScale);
	width = static_cast<int>(static_cast<float>(width) * xScale);
	height = static_cast<int>(static_cast<float>(height) * yScale);
	offsetX = viewPortNode->computeParentChildrenRenderOffsetXTotal();
	offsetY = viewPortNode->computeParentChildrenRenderOffsetYTotal();
}

bool EditorView::getCurrentTabTooltipPosition(GUIScreenNode* screenNode, int mouseX, int mouseY, int& tooltipLeft, int& tooltipTop) {
	int left, top, width, height, offsetX, offsetY;
	if (getCurrentTabViewPort(left, top, width, height, offsetX, offsetY) == false) return false;
	//
	auto xScale = static_cast<float>(Engine::getInstance()->getWidth()) / static_cast<float>(screenNode->getScreenWidth());
	auto yScale = static_cast<float>(Engine::getInstance()->getHeight()) / static_cast<float>(screenNode->getScreenHeight());
	//
	tooltipLeft = left + mouseX * xScale - offsetX * xScale;
	tooltipTop = top + mouseY * yScale - offsetY * yScale;
	//
	return true;
}

void EditorView::onDrop(const vector<string>& paths) {
	editorScreenController->onDrop(paths);
}
