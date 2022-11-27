#include <tdme/gui/GUI.h>

#if defined(__APPLE__)
	#include <Carbon/Carbon.h>
#endif

#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIInputEventHandler.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Time.h>

using std::map;
using std::remove;
using std::reverse;
using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::Engine;
using tdme::gui::events::GUIInputEventHandler;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::GUI;
using tdme::gui::GUIParserException;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Time;

bool GUI::disableTabFocusControl = false;

GUI::GUI(Engine* engine, GUIRenderer* guiRenderer)
{
	this->lastMouseButton = 0;
	this->engine = engine;
	this->guiRenderer = guiRenderer;
	this->width = engine->getWidth();
	this->height = engine->getHeight();
	try {
		this->foccussedBorderColor = GUIColor("#5680C2");
	} catch (Exception& exception) {
		Console::print(string("GUI(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

GUI::~GUI() {
}

void GUI::initialize()
{
}

void GUI::reshape(int width, int height)
{
	this->width = width;
	this->height = height;
	for (auto screenIt: screens) {
		auto screen = screenIt.second;
		reshapeScreen(screen);
	}
}

void GUI::dispose()
{
	reset();
}

void GUI::addScreen(const string& id, GUIScreenNode* screen)
{
	if (id != screen->getId()) {
		Console::println("GUI::addScreen(): screen id '" + id + "' must be '" + screen->getId() + "'");
		return;
	}
	screens.emplace(id, screen);
	reshapeScreen(screen);
}

void GUI::removeScreen(const string& id)
{
	auto screensIt = screens.find(id);
	if (screensIt != screens.end()) {
		removeRenderScreen(id);
		auto screen = screensIt->second;
		screens.erase(screensIt);
		mouseOutCandidateEventNodeIds.erase(id);
		mouseOutClickCandidateEventNodeIds.erase(id);
		mousePressedEventNodeIds.erase(id);
		mouseDraggingEventNodeIds.erase(id);
		mouseIsDragging.erase(id);
		delete screen;
	}
}

void GUI::reset()
{
	vector<string> entitiesToRemove;
	for (auto screenKeysIt: screens) {
		entitiesToRemove.push_back(screenKeysIt.first);
	}
	for (auto i = 0; i < entitiesToRemove.size(); i++) {
		removeScreen(entitiesToRemove[i]);
	}
	renderScreens.clear();
}

void GUI::resetRenderScreens()
{
	// focussed node
	unfocusNode();
	focussedNodeScreenId.clear();
	focussedNodeNodeId.clear();

	//
	applyRenderScreensChange();

	// unset GUI
	for (auto i = 0; i < renderScreens.size(); i++) {
		renderScreens[i]->setGUI(nullptr);
	}

	// clear
	renderScreens.clear();
}

void GUI::addRenderScreen(const string& screenId)
{
	auto screenIt = screens.find(screenId);
	if (screenIt == screens.end()) return;

	//
	applyRenderScreensChange();

	//
	auto screen = screenIt->second;
	screen->setGUI(this);
	screen->setConditionsMet();
	renderScreens.push_back(screenIt->second);

	// focussed node
	focussedNodeScreenId.clear();
	focussedNodeNodeId.clear();
	determineFocussedNodes();
}

void GUI::removeRenderScreen(const string& screenId)
{
	auto screenIt = screens.find(screenId);
	if (screenIt == screens.end()) return;

	//
	screenIt->second->setGUI(nullptr);

	//
	applyRenderScreensChange();

	//
	renderScreens.erase(remove(renderScreens.begin(), renderScreens.end(), screenIt->second), renderScreens.end());
}

void GUI::invalidateFocussedNode()
{
	unfocusNode();
	focussedNodeScreenId.clear();
	focussedNodeNodeId.clear();
}

void GUI::determineFocussedNodes()
{
	focusableNodes.clear();
	focusableScreenNodes.clear();
	for (int i = renderScreens.size() - 1; i >= 0; i--) {
		auto screen = renderScreens[i];
		if (screen->isVisible() == false)
			continue;

		focusableScreenNodes.push_back(screen);
		if (screen->isPopUp() == true)
			break;

	}
	for (int i = focusableScreenNodes.size() - 1; i >= 0; i--) {
		auto screen = focusableScreenNodes[i];
		screen->determineFocussedNodes(screen, focusableNodes);
	}
}

GUIElementNode* GUI::getFocussedNode()
{
	if (focussedNodeScreenId.empty() == true || focussedNodeNodeId.empty() == true) return nullptr;
	auto focussedNodeScreen = getScreen(focussedNodeScreenId);
	auto focussedNode = dynamic_cast<GUIElementNode*>(focussedNodeScreen != nullptr?focussedNodeScreen->getNodeById(focussedNodeNodeId):nullptr);
	return focussedNode;
}

void GUI::unfocusNode()
{
	if (focussedNodeScreenId.empty() == true || focussedNodeNodeId.empty() == true) return;
	auto focussedNodeScreen = getScreen(focussedNodeScreenId);
	auto focussedNode = dynamic_cast<GUIElementNode*>(focussedNodeScreen != nullptr?focussedNodeScreen->getNodeById(focussedNodeNodeId):nullptr);
	if (focussedNode != nullptr) {
		focussedNode->getActiveConditions().remove(GUIElementNode::CONDITION_FOCUS);
		focussedNode->getBorder().topColor = unfocussedNodeBorderTopColor;
		focussedNode->getBorder().leftColor = unfocussedNodeBorderLeftColor;
		focussedNode->getBorder().bottomColor = unfocussedNodeBorderBottomColor;
		focussedNode->getBorder().rightColor = unfocussedNodeBorderRightColor;
		if (focussedNode->getController() != nullptr) focussedNode->getController()->onFocusLost();
		focussedNode->getScreenNode()->forwardUnfocus(focussedNode);
	}
}

void GUI::focusNode()
{
	auto focussedNodeScreen = getScreen(focussedNodeScreenId);
	auto focussedNode = dynamic_cast<GUIElementNode*>(focussedNodeScreen != nullptr?focussedNodeScreen->getNodeById(focussedNodeNodeId):nullptr);
	if (focussedNode != nullptr) {
		focussedNode->getActiveConditions().add(GUIElementNode::CONDITION_FOCUS);
		unfocussedNodeBorderTopColor = focussedNode->getBorder().topColor;
		unfocussedNodeBorderLeftColor = focussedNode->getBorder().leftColor;
		unfocussedNodeBorderBottomColor = focussedNode->getBorder().bottomColor;
		unfocussedNodeBorderRightColor = focussedNode->getBorder().rightColor;
		focussedNode->getBorder().topColor = foccussedBorderColor;
		focussedNode->getBorder().leftColor = foccussedBorderColor;
		focussedNode->getBorder().bottomColor = foccussedBorderColor;
		focussedNode->getBorder().rightColor = foccussedBorderColor;
		if (focussedNode->getController() != nullptr) focussedNode->getController()->onFocusGained();
		focussedNode->getScreenNode()->forwardFocus(focussedNode);
	}
}

void GUI::setFoccussedNode(GUIElementNode* newFoccussedNode)
{
	auto focussedNodeScreen = getScreen(focussedNodeScreenId);
	auto focussedNode = dynamic_cast<GUIElementNode*>(focussedNodeScreen != nullptr?focussedNodeScreen->getNodeById(focussedNodeNodeId):nullptr);
	if (focussedNode == newFoccussedNode) {
		return;
	}
	unfocusNode();
	determineFocussedNodes();
	this->focussedNodeScreenId = newFoccussedNode == nullptr?string():newFoccussedNode->getScreenNode()->getId();
	this->focussedNodeNodeId = newFoccussedNode == nullptr?string():newFoccussedNode->getId();
	if (newFoccussedNode != nullptr) focusNode();
}

void GUI::focusNextNode()
{
	determineFocussedNodes();
	unfocusNode();
	auto focussedNodeScreen = getScreen(focussedNodeScreenId);
	auto focussedNode = dynamic_cast<GUIElementNode*>(focussedNodeScreen != nullptr?focussedNodeScreen->getNodeById(focussedNodeNodeId):nullptr);
	if (focusableNodes.size() > 0) {
		auto focussedNodeIdx = -1;
		for (auto i = 0; i < focusableNodes.size(); i++) {
			if (focussedNode == focusableNodes[i]) {
				focussedNodeIdx = i;
			}
		}
		auto focussedNextNodeIdx = (focussedNodeIdx + 1) % focusableNodes.size();
		auto newFocussedNode = focusableNodes[focussedNextNodeIdx];
		setFoccussedNode(newFocussedNode);
		newFocussedNode->scrollToNodeX();
		newFocussedNode->scrollToNodeY();
	}
}

void GUI::focusPreviousNode()
{
	determineFocussedNodes();
	unfocusNode();
	auto focussedNodeScreen = getScreen(focussedNodeScreenId);
	auto focussedNode = dynamic_cast<GUIElementNode*>(focussedNodeScreen != nullptr?focussedNodeScreen->getNodeById(focussedNodeNodeId):nullptr);
	if (focusableNodes.size() > 0) {
		auto focussedNodeIdx = -1;
		for (auto i = 0; i < focusableNodes.size(); i++) {
			if (focussedNode == focusableNodes[i]) {
				focussedNodeIdx = i;
			}
		}
		int focussedPreviousNodeIdx = (focussedNodeIdx - 1) % focusableNodes.size();
		if (focussedPreviousNodeIdx < 0) focussedPreviousNodeIdx += focusableNodes.size();
		auto newFocussedNode = focusableNodes[focussedPreviousNodeIdx];
		setFoccussedNode(newFocussedNode);
		newFocussedNode->scrollToNodeX();
		newFocussedNode->scrollToNodeY();
	}
}

void GUI::render()
{
	//
	if (renderScreens.empty() == true)
		return;

	// invalidate layouts
	for (int i = renderScreens.size() - 1; i >= 0; i--) {
		auto screen = renderScreens[i];

		if (screen->isVisible() == false) continue;

		screen->invalidateLayouts();
		screen->scrollToNodes();
	}

	//
	guiRenderer->setGUI(this);
	engine->initGUIMode();
	guiRenderer->initRendering();
	for (auto i = 0; i < renderScreens.size(); i++) {
		auto screen = renderScreens[i];

		if (screen->isVisible() == false) continue;

		//
		screen->render(guiRenderer);
		screen->renderFloatingNodes(guiRenderer);
	}
	guiRenderer->doneRendering();
	engine->doneGUIMode();
}

bool GUI::isHavingMouseInteraction(GUINode* node) {
	auto nodeId = node->getId();
	auto screenNodeId = node->getScreenNode()->getId();
	return
		mousePressedEventNodeIds[screenNodeId].find(nodeId) != mousePressedEventNodeIds[screenNodeId].end() ||
		mouseDraggingEventNodeIds[screenNodeId].find(nodeId) != mouseDraggingEventNodeIds[screenNodeId].end();
}

void GUI::handleMouseEvent(GUINode* node, GUIMouseEvent* event, const unordered_set<string>& mouseOutCandidateEventNodeIds, const unordered_set<string>& mouseOutClickCandidateEventNodeIds, unordered_set<string>& mousePressedEventNodeIds, bool floatingNodes)
{
	// handle each event
	unordered_set<string> mouseEventNodeIgnore;
	unordered_set<string> mouseEventNodeIds;

	//
	event->setX((float)event->getXUnscaled() * (float)node->getScreenNode()->getScreenWidth() / (float)width + node->getScreenNode()->getGUIEffectOffsetX());
	event->setY((float)event->getYUnscaled() * (float)node->getScreenNode()->getScreenHeight() / (float)height + node->getScreenNode()->getGUIEffectOffsetY());

	// if dragging only send events to dragging origin nodes
	if (event->getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) {
		mouseEventNodeIds = mouseDraggingEventNodeIds[node->getScreenNode()->getId()];
	} else
	if (event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED &&
		mouseIsDragging[node->getScreenNode()->getId()] == true) {
		mouseEventNodeIds = mouseDraggingEventNodeIds[node->getScreenNode()->getId()];
	} else {
		// otherwise continue with determining nodes that receive this event
		if (floatingNodes == true) {
			node->determineMouseEventNodes(event, node->flow == GUINode_Flow::FLOATING, mouseEventNodeIgnore, mouseEventNodeIds);
		} else {
			node->determineMouseEventNodes(event, node->flow == GUINode_Flow::FLOATING, mouseEventNodeIds, mouseEventNodeIgnore);
		}
	}

	// inject former mouse out candidates
	for (auto eventNodeId: mouseOutCandidateEventNodeIds) {
		mouseEventNodeIds.insert(eventNodeId);
	}

	// inject former mouse out click candidates
	for (auto eventNodeId: mouseOutClickCandidateEventNodeIds) {
		mouseEventNodeIds.insert(eventNodeId);
	}

	// handle mouse event for each node we collected
	for (auto eventNodeId: mouseEventNodeIds) {
		// node event occurred on
		auto eventNode = node->getScreenNode()->getNodeById(eventNodeId);
		if (eventNode == nullptr) continue;
		if (floatingNodes == false && eventNode->flow == GUINode_Flow::FLOATING) continue;

		// controller node
		auto controllerNode = eventNode;
		if (controllerNode->getController() == nullptr) {
			controllerNode = controllerNode->getParentControllerNode();
		}
		if (controllerNode == nullptr) continue;

		// this corresponding screen node could have been detached from GUI by removing it from render screens
		if (eventNode->getScreenNode()->getGUI() == nullptr) continue;

		// handle event with determined controller
		controllerNode->getController()->handleMouseEvent(eventNode, event);
	}

	// compile list of gui node ids that received mouse PRESSED events
	if (event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED) {
		for (auto eventNodeId: mouseEventNodeIds) {
			mousePressedEventNodeIds.insert(eventNodeId);
		}
	}

	// clear event node id list
	mouseEventNodeIds.clear();
}

void GUI::handleKeyboardEvent(GUIKeyboardEvent* event) {
	// skip if processed
	if (event->isProcessed() == true) return;

	// otherwise dispatch event to focussed node
	if (focussedNodeScreenId.empty() == false && focussedNodeNodeId.empty() == false) {
		auto focussedNodeScreen = getScreen(focussedNodeScreenId);
		auto focussedNode = dynamic_cast<GUIElementNode*>(focussedNodeScreen != nullptr?focussedNodeScreen->getNodeById(focussedNodeNodeId):nullptr);
		if (focussedNode != nullptr) focussedNode->handleKeyboardEvent(event);
	}

	// skip if already processed
	if (event->isProcessed() == true) return;

	//
	switch (event->getKeyCode()) {
		case (GUIKeyboardEvent::KEYCODE_TAB):
			if (disableTabFocusControl == false) {
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					if (event->isShiftDown() == true) {
						focusPreviousNode();
					} else {
						focusNextNode();
					}
				}
				event->setProcessed(true);
			}
			break;
		case (GUIKeyboardEvent::KEYCODE_LEFT_ALT):
		case (GUIKeyboardEvent::KEYCODE_RIGHT_ALT):
			{
				altDown = event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED;
				break;
			}
		case (GUIKeyboardEvent::KEYCODE_LEFT_CONTROL):
		case (GUIKeyboardEvent::KEYCODE_RIGHT_CONTROL):
			{
				controlDown = event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED;
				break;
			}
		case (GUIKeyboardEvent::KEYCODE_LEFT_SHIFT):
		case (GUIKeyboardEvent::KEYCODE_RIGHT_SHIFT):
			{
				shiftDown = event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED;
				break;
			}
		default:
			{
				break;
			}
	}
}

void GUI::handleEvents(bool clearEvents)
{
	unordered_map<string, unordered_set<string>> _mouseOutCandidateEventNodeIds;
	unordered_map<string, unordered_set<string>> _mouseOutClickCandidateEventNodeIds;

	//
	auto renderScreensCopy = renderScreens;

	// tooltips
	if (mouseEvents.empty() == true && keyboardEvents.empty() == true) {
		if (tooltipShown == false && Time::getCurrentMillis() - lastEventTime > TOOLTIP_TIME) {
			//
			map<string, GUINode*> tooltipFloatingNodes;
			map<string, GUINode*> tooltipNodes;

			// handle floating nodes first
			for (int i = renderScreensCopy.size() - 1; i >= 0; i--) {
				auto screen = renderScreensCopy[i];

				// skip on invisible
				if (screen->isVisible() == false) continue;

				//
				auto& floatingNodes = screen->getFloatingNodes();
				for (auto j = 0; j < floatingNodes.size(); j++) {
					//
					unordered_set<string> eventNodeIds;
					unordered_set<string> eventFloatingNodeIds;

					//
					auto floatingNode = floatingNodes[j];
					// TODO: collect only nodes with tooltips
					floatingNode->determineMouseEventNodes(&lastMouseEvent, floatingNode->flow == GUINode_Flow::FLOATING, eventNodeIds, eventFloatingNodeIds, GUINode::DETERMINEMOUSEEVENTNODES_FLAG_TOOLTIP);

					// collect as hierarchical ids -> node
					for (auto& eventFloatingNodeId: eventFloatingNodeIds) {
						auto node = screen->getNodeById(eventFloatingNodeId);
						tooltipFloatingNodes[node->getHierarchicalId()] = node;
					}
					for (auto& eventNodeId: eventNodeIds) {
						auto node = screen->getNodeById(eventNodeId);
						tooltipFloatingNodes[node->getHierarchicalId()] = node;
					}
				}
				// skip on pop ups
				if (screen->isPopUp() == true) break;
			}

			// handle normal screen nodes if not processed already by floating node
			for (int i = renderScreensCopy.size() - 1; i >= 0; i--) {
				//
				unordered_set<string> eventNodeIds;
				unordered_set<string> eventFloatingNodeIds;

				//
				auto screen = renderScreensCopy[i];
				if (screen->isVisible() == false) continue;

				//
				screen->determineMouseEventNodes(&lastMouseEvent, screen->flow == GUINode_Flow::FLOATING, eventNodeIds, eventFloatingNodeIds, GUINode::DETERMINEMOUSEEVENTNODES_FLAG_TOOLTIP);

				// collect as hierarchical ids -> node
				for (auto& eventFloatingNodeId: eventFloatingNodeIds) {
					auto node = screen->getNodeById(eventFloatingNodeId);
					tooltipNodes[node->getHierarchicalId()] = node;
				}
				for (auto& eventNodeId: eventNodeIds) {
					auto node = screen->getNodeById(eventNodeId);
					tooltipNodes[node->getHierarchicalId()] = node;
				}

				//
				if (screen->isPopUp() == true) break;
			}

			//
			if (tooltipFloatingNodes.empty() == false) {
				vector<GUINode*> tooltipFloatingNodesVector;
				for (auto& tooltipFloatingNodeIt: tooltipFloatingNodes) {
					tooltipFloatingNodesVector.push_back(tooltipFloatingNodeIt.second);
				}
				reverse(tooltipFloatingNodesVector.begin(), tooltipFloatingNodesVector.end());
				//
				auto node = tooltipFloatingNodesVector[0];
				node->getScreenNode()->forwardTooltipShowRequest(node, lastMouseEvent.getXUnscaled(), lastMouseEvent.getYUnscaled());
			} else
			if (tooltipNodes.empty() == false) {
				vector<GUINode*> tooltipNodesVector;
				for (auto& tooltipNodeIt: tooltipNodes) {
					tooltipNodesVector.push_back(tooltipNodeIt.second);
				}
				reverse(tooltipNodesVector.begin(), tooltipNodesVector.end());

				//
				auto node = tooltipNodesVector[0];
				node->getScreenNode()->forwardTooltipShowRequest(node, lastMouseEvent.getXUnscaled(), lastMouseEvent.getYUnscaled());
			}

			//
			tooltipShown = true;
		}
	} else
	if (tooltipShown == true) {
		// close tooltip
		tooltipShown = false;
		//
		for (int i = renderScreensCopy.size() - 1; i >= 0; i--) {
			//
			auto screen = renderScreensCopy[i];

			//
			screen->forwardTooltipCloseRequest();
		}
	}

	// handle mouse events
	for (auto& event: mouseEvents) {
		//
		lastEventTime = event.getTime();

		// fetch and clear last mouse out candidates as we now will actually send them
		if (event.getType() == GUIMouseEvent::MOUSEEVENT_MOVED) {
			_mouseOutCandidateEventNodeIds = mouseOutCandidateEventNodeIds;
			mouseOutCandidateEventNodeIds.clear();
		} else
		if (event.getType() == GUIMouseEvent::MOUSEEVENT_PRESSED || event.getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
			_mouseOutClickCandidateEventNodeIds = mouseOutClickCandidateEventNodeIds;
			mouseOutClickCandidateEventNodeIds.clear();
		}

		// handle mouse dragged event
		if (event.getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) {
			for (int i = renderScreensCopy.size() - 1; i >= 0; i--) {
				auto screen = renderScreensCopy[i];
				if (mouseIsDragging[screen->getId()] == false) {
					mouseIsDragging[screen->getId()] = true;
					mouseDraggingEventNodeIds[screen->getId()] = mousePressedEventNodeIds[screen->getId()];
				}
			}
		}

		// handle floating nodes first
		for (int i = renderScreensCopy.size() - 1; i >= 0; i--) {
			auto screen = renderScreensCopy[i];

			// skip on invisible
			if (screen->isVisible() == false) continue;

			//
			auto processed = false;
			auto& floatingNodes = screen->getFloatingNodes();
			for (auto j = 0; j < floatingNodes.size(); j++) {
				auto floatingNode = floatingNodes[j];

				handleMouseEvent(floatingNode, &event, _mouseOutCandidateEventNodeIds[screen->getId()], _mouseOutClickCandidateEventNodeIds[screen->getId()], mousePressedEventNodeIds[screen->getId()], true);

				// do not continue handling mouse events if already processed
				if (event.isProcessed() == true) break;

				// We do not consume mouse moved events by default, so:
				// consume mouse move event, if floating node has conditions met and is expanded/collapsed by condition
				// as in this case you do not want to have other mouse movement event handling
				if ((event.getType() == GUIMouseEvent::MOUSEEVENT_MOVED || floatingNode->isEventBelongingToNode(&event) == true) &&
					floatingNode->flow == GUINode_Flow::FLOATING &&
					floatingNode->conditionsMet == true &&
					((floatingNode->showOn.getConditions().empty() == false && floatingNode->showOn.has("always") == false) ||
					(floatingNode->hideOn.getConditions().empty() == false && floatingNode->showOn.has("never") == false))) processed = true;
			}
			// do not continue handling mouse events if already processed
			if (event.isProcessed() == true) break;
			// set processed if we decided to do so :D
			if (processed == true) event.setProcessed(true);
			// skip on pop ups
			if (screen->isPopUp() == true) break;
		}

		// handle normal screen nodes if not processed already by floating node
		// 	Note: Different screens should not have UI elements that overlap and process events
		if (event.isProcessed() == false) {
			for (int i = renderScreensCopy.size() - 1; i >= 0; i--) {
				auto screen = renderScreensCopy[i];
				if (screen->isVisible() == false) continue;
				handleMouseEvent(screen, &event, _mouseOutCandidateEventNodeIds[screen->getId()], _mouseOutClickCandidateEventNodeIds[screen->getId()], mousePressedEventNodeIds[screen->getId()], false);
				if (screen->isPopUp() == true) break;
			}
		}

		// handle mouse released event
		if (event.getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
			for (int i = renderScreensCopy.size() - 1; i >= 0; i--) {
				auto screen = renderScreensCopy[i];
				mouseIsDragging[screen->getId()] = false;
				mouseDraggingEventNodeIds.erase(screen->getId());
				mousePressedEventNodeIds.erase(screen->getId());
			}
		}
	}

	//
	if (mouseEvents.empty() == false) {
		lastMouseEvent = mouseEvents[mouseEvents.size()];
	}

	// handle keyboard events
	for (auto& event: keyboardEvents) {
		//
		lastEventTime = event.getTime();
		//
		handleKeyboardEvent(&event);
	}

	// call tick and input event handler
	for (int i = renderScreensCopy.size() - 1; i >= 0; i--) {
		auto screen = renderScreensCopy[i];
		if (screen->isVisible() == false) continue;
		screen->tick();
		if (screen->getInputEventHandler() != nullptr) {
			screen->getInputEventHandler()->handleInputEvents();
		}
		if (screen->isPopUp() == true) break;
	}

	//
	if (clearEvents == true) {
		mouseEvents.clear();
		keyboardEvents.clear();
	}
}

void GUI::onChar(int key, int x, int y) {
	fakeMouseMovedEvent();
	GUIKeyboardEvent guiKeyboardEvent;
	guiKeyboardEvent.setTime(Time::getCurrentMillis());
	guiKeyboardEvent.setType(GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED);
	guiKeyboardEvent.setKeyCode(-1);
	guiKeyboardEvent.setKeyChar(key);
	guiKeyboardEvent.setMetaDown(false);
	guiKeyboardEvent.setControlDown(controlDown);
	guiKeyboardEvent.setAltDown(altDown);
	guiKeyboardEvent.setShiftDown(shiftDown);
	guiKeyboardEvent.setRepeat(false);
	guiKeyboardEvent.setProcessed(false);
	keyboardEvents.push_back(guiKeyboardEvent);
}

void GUI::onKeyDown (int key, int keyCode, int x, int y, bool repeat, int modifiers) {
	fakeMouseMovedEvent();
	GUIKeyboardEvent guiKeyboardEvent;
	guiKeyboardEvent.setTime(Time::getCurrentMillis());
	guiKeyboardEvent.setType(GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED);
	guiKeyboardEvent.setKeyCode(keyCode);
	guiKeyboardEvent.setKeyChar(key);
	guiKeyboardEvent.setMetaDown(false);
	guiKeyboardEvent.setControlDown((modifiers & KEYBOARD_MODIFIER_CTRL) != 0);
	guiKeyboardEvent.setAltDown((modifiers & KEYBOARD_MODIFIER_ALT) != 0);
	guiKeyboardEvent.setShiftDown((modifiers & KEYBOARD_MODIFIER_SHIFT) != 0);
	guiKeyboardEvent.setRepeat(repeat);
	guiKeyboardEvent.setProcessed(false);
	keyboardEvents.push_back(guiKeyboardEvent);
}

void GUI::onKeyUp(int key, int keyCode, int x, int y) {
	fakeMouseMovedEvent();
	GUIKeyboardEvent guiKeyboardEvent;
	guiKeyboardEvent.setTime(Time::getCurrentMillis());
	guiKeyboardEvent.setType(GUIKeyboardEvent::KEYBOARDEVENT_KEY_RELEASED);
	guiKeyboardEvent.setKeyCode(keyCode);
	guiKeyboardEvent.setKeyChar(key);
	guiKeyboardEvent.setMetaDown(false);
	guiKeyboardEvent.setControlDown(controlDown);
	guiKeyboardEvent.setAltDown(altDown);
	guiKeyboardEvent.setShiftDown(shiftDown);
	guiKeyboardEvent.setRepeat(false);
	guiKeyboardEvent.setProcessed(false);
	keyboardEvents.push_back(guiKeyboardEvent);
}

void GUI::onMouseDragged(int x, int y) {
	fakeKeyboardModifierEvent();

	GUIMouseEvent guiMouseEvent;
	guiMouseEvent.setTime(Time::getCurrentMillis());
	guiMouseEvent.setType(GUIMouseEvent::MOUSEEVENT_DRAGGED);
	guiMouseEvent.setXUnscaled(x);
	guiMouseEvent.setYUnscaled(y);
	guiMouseEvent.setX(x);
	guiMouseEvent.setY(y);
	guiMouseEvent.setButton(lastMouseButton);
	guiMouseEvent.setWheelX(0.0f);
	guiMouseEvent.setWheelY(0.0f);
	guiMouseEvent.setWheelZ(0.0f);
	guiMouseEvent.setControlDown(controlDown);
	guiMouseEvent.setAltDown(altDown);
	guiMouseEvent.setShiftDown(shiftDown);
	guiMouseEvent.setProcessed(false);
	mouseEvents.push_back(guiMouseEvent);
}

void GUI::onMouseMoved(int x, int y) {
	fakeKeyboardModifierEvent();

	GUIMouseEvent guiMouseEvent;
	guiMouseEvent.setTime(Time::getCurrentMillis());
	guiMouseEvent.setType(GUIMouseEvent::MOUSEEVENT_MOVED);
	guiMouseEvent.setXUnscaled(x);
	guiMouseEvent.setYUnscaled(y);
	guiMouseEvent.setX(x);
	guiMouseEvent.setY(y);
	guiMouseEvent.setButton(0);
	guiMouseEvent.setWheelX(0.0f);
	guiMouseEvent.setWheelY(0.0f);
	guiMouseEvent.setWheelZ(0.0f);
	guiMouseEvent.setControlDown(controlDown);
	guiMouseEvent.setAltDown(altDown);
	guiMouseEvent.setShiftDown(shiftDown);
	guiMouseEvent.setProcessed(false);
	mouseEvents.push_back(guiMouseEvent);
}

void GUI::onMouseButton(int button, int state, int x, int y) {
	fakeKeyboardModifierEvent();

	lastMouseButton = button + 1;
	GUIMouseEvent guiMouseEvent;
	guiMouseEvent.setTime(Time::getCurrentMillis());
	guiMouseEvent.setType(state == MOUSE_BUTTON_DOWN?GUIMouseEvent::MOUSEEVENT_PRESSED:GUIMouseEvent::MOUSEEVENT_RELEASED);
	guiMouseEvent.setXUnscaled(x);
	guiMouseEvent.setYUnscaled(y);
	guiMouseEvent.setX(x);
	guiMouseEvent.setY(y);
	guiMouseEvent.setButton(lastMouseButton);
	guiMouseEvent.setWheelX(0.0f);
	guiMouseEvent.setWheelY(0.0f);
	guiMouseEvent.setWheelZ(0.0f);
	guiMouseEvent.setControlDown(controlDown);
	guiMouseEvent.setAltDown(altDown);
	guiMouseEvent.setShiftDown(shiftDown);
	guiMouseEvent.setProcessed(false);
	mouseEvents.push_back(guiMouseEvent);
}

void GUI::onMouseWheel(int button, int direction, int x, int y) {
	fakeKeyboardModifierEvent();

	lastMouseButton = button + 1;
	GUIMouseEvent guiMouseEvent;
	guiMouseEvent.setTime(Time::getCurrentMillis());
	guiMouseEvent.setType(GUIMouseEvent::MOUSEEVENT_WHEEL_MOVED);
	guiMouseEvent.setXUnscaled(x);
	guiMouseEvent.setYUnscaled(y);
	guiMouseEvent.setX(x);
	guiMouseEvent.setY(y);
	guiMouseEvent.setButton(lastMouseButton);
	guiMouseEvent.setWheelX(0.0f);
	guiMouseEvent.setWheelY(direction * 1.0f);
	guiMouseEvent.setWheelZ(0.0f);
	guiMouseEvent.setControlDown(controlDown);
	guiMouseEvent.setAltDown(altDown);
	guiMouseEvent.setShiftDown(shiftDown);
	guiMouseEvent.setProcessed(false);
	mouseEvents.push_back(guiMouseEvent);
}

void GUI::fakeMouseMovedEvent()
{
	GUIMouseEvent guiMouseEvent;
	guiMouseEvent.setTime(Time::getCurrentMillis());
	guiMouseEvent.setType(GUIMouseEvent::MOUSEEVENT_MOVED);
	guiMouseEvent.setXUnscaled(-10000);
	guiMouseEvent.setYUnscaled(-10000);
	guiMouseEvent.setX(-10000);
	guiMouseEvent.setY(-10000);
	guiMouseEvent.setButton(0);
	guiMouseEvent.setWheelX(0.0f);
	guiMouseEvent.setWheelY(0.0f);
	guiMouseEvent.setWheelZ(0.0f);
	guiMouseEvent.setProcessed(false);
	mouseEvents.push_back(guiMouseEvent);
}

void GUI::fakeKeyboardModifierEvent() {
	bool isControlDown = false;
	bool isAltDown = false;
	bool isShiftDown = false;
	#if defined(__APPLE__)
		KeyMap keys;
		GetKeys(keys);
		#define IS_KEY_DOWN(key, var) \
		{ \
			uint8_t index = key / 32 ; \
			uint8_t shift = key % 32 ; \
			var = keys[index].bigEndianValue & (1 << shift); \
		}
		IS_KEY_DOWN(kVK_Command, isControlDown);
		IS_KEY_DOWN(kVK_Option, isAltDown);
		IS_KEY_DOWN(kVK_Shift, isShiftDown);
	#endif

	if (isControlDown == false &&
		isAltDown == false &&
		isShiftDown == false) {
		return;
	}

	GUIKeyboardEvent guiKeyboardEvent;
	guiKeyboardEvent.setTime(Time::getCurrentMillis());
	guiKeyboardEvent.setType(GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED);
	guiKeyboardEvent.setKeyCode(-1);
	guiKeyboardEvent.setKeyChar(-1);
	guiKeyboardEvent.setMetaDown(false);
	guiKeyboardEvent.setControlDown(isControlDown);
	guiKeyboardEvent.setAltDown(isAltDown);
	guiKeyboardEvent.setShiftDown(isShiftDown);
	guiKeyboardEvent.setProcessed(false);
	keyboardEvents.push_back(guiKeyboardEvent);
}

void GUI::reshapeScreen(GUIScreenNode* screenNode) {
	// TODO: maybe move logic into GUIScreenNode
	// FIXME: always keep aspect ratio
	auto screenNodeWidthConstrained = width;
	auto screenNodeHeightConstrained = height;

	auto minRatio = 1.0f;

	if ((screenNode->sizeConstraints.maxWidth > 0 && screenNodeWidthConstrained > screenNode->sizeConstraints.maxWidth) ||
		(screenNode->sizeConstraints.maxHeight > 0 && screenNodeHeightConstrained > screenNode->sizeConstraints.maxHeight)) {
		if (screenNode->sizeConstraints.maxWidth > 0 && screenNodeWidthConstrained > screenNode->sizeConstraints.maxWidth) {
			minRatio = (float)screenNode->sizeConstraints.maxWidth / (float)width;
			screenNodeWidthConstrained = screenNode->sizeConstraints.maxWidth;
			screenNodeHeightConstrained = (int)((float)screenNodeHeightConstrained * minRatio);
		}
		if (screenNode->sizeConstraints.maxHeight > 0 && screenNodeHeightConstrained > screenNode->sizeConstraints.maxHeight) {
			minRatio = (float)screenNode->sizeConstraints.maxHeight / (float)height;
			screenNodeHeightConstrained = screenNode->sizeConstraints.maxHeight;
			screenNodeWidthConstrained = (int)((float)screenNodeWidthConstrained * minRatio);
		}
	}
	if ((screenNode->sizeConstraints.minWidth > 0 && screenNodeWidthConstrained < screenNode->sizeConstraints.minWidth) ||
		(screenNode->sizeConstraints.minHeight > 0 && screenNodeHeightConstrained < screenNode->sizeConstraints.minHeight)) {
		if (screenNode->sizeConstraints.minWidth > 0 && screenNodeWidthConstrained < screenNode->sizeConstraints.minWidth) {
			auto ratio = (float)screenNode->sizeConstraints.minWidth / (float)width;
			screenNodeWidthConstrained = screenNode->sizeConstraints.minWidth;
			screenNodeHeightConstrained = (int)((float)screenNodeHeightConstrained * ratio / minRatio);
		}
		if (screenNode->sizeConstraints.minHeight > 0 && screenNodeHeightConstrained < screenNode->sizeConstraints.minHeight) {
			auto ratio = (float)screenNode->sizeConstraints.minHeight / (float)height;
			screenNodeHeightConstrained = screenNode->sizeConstraints.minHeight;
			screenNodeWidthConstrained = (int)((float)screenNodeWidthConstrained * ratio / minRatio);
		}
	}

	screenNode->setScreenSize(screenNodeWidthConstrained, screenNodeHeightConstrained);
}

void GUI::applyRenderScreensChange() {
	for (auto screen: renderScreens) screen->unsetMouseStates();
}
