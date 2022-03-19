#include <tdme/gui/nodes/GUIStyledTextNodeController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::string;

using tdme::application::Application;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUIStyledTextNodeController;
using tdme::gui::GUI;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

GUIStyledTextNodeController::GUIStyledTextNodeController(GUINode* node)
	: GUINodeController(node)
{
}

void GUIStyledTextNodeController::resetCursorMode()
{
	cursorModeStarted = Time::getCurrentMillis();
	cursorMode = CURSORMODE_SHOW;
}

GUIStyledTextNodeController::CursorMode GUIStyledTextNodeController::getCursorMode()
{
	if (cursorModeStarted == -1) {
		resetCursorMode();
		return cursorMode;
	}
	if (Time::getCurrentMillis() - cursorModeStarted > CURSOR_MODE_DURATION) {
		cursorMode = cursorMode == CURSORMODE_SHOW?CURSORMODE_HIDE:CURSORMODE_SHOW;
		cursorModeStarted = Time::getCurrentMillis();
	}
	return cursorMode;
}

bool GUIStyledTextNodeController::isDisabled()
{
	return false;
}

void GUIStyledTextNodeController::setDisabled(bool disabled)
{
}

void GUIStyledTextNodeController::initialize()
{
}

void GUIStyledTextNodeController::dispose()
{
}

void GUIStyledTextNodeController::postLayout()
{
}

void GUIStyledTextNodeController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	Vector2 nodeMousePosition;
	if (node == styledTextNode) {
		if (styledTextNode->isEventBelongingToNode(event, nodeMousePosition) == true) {
			switch(event->getType()) {
				case GUIMouseEvent::MOUSEEVENT_MOVED:
				case GUIMouseEvent::MOUSEEVENT_RELEASED:
					{
						// find URL area that had a hit and setup corresponding cursor
						auto& urlAreas = styledTextNode->getURLAreas();
						const GUIStyledTextNode::URLArea* urlAreaHit = nullptr;
						for (auto& urlArea: urlAreas) {
							if (nodeMousePosition.getX() < urlArea.left ||
								nodeMousePosition.getY() < urlArea.top ||
								nodeMousePosition.getX() > urlArea.left + urlArea.width ||
								nodeMousePosition.getY() > urlArea.top + urlArea.height) {
								continue;
							}
							if (Application::getMouseCursor() != MOUSE_CURSOR_HAND) Application::setMouseCursor(MOUSE_CURSOR_HAND);
							urlAreaHit = &urlArea;
							break;
						}
						if (urlAreaHit == nullptr) {
							if (Application::getMouseCursor() != MOUSE_CURSOR_ENABLED) Application::setMouseCursor(MOUSE_CURSOR_ENABLED);
						}
						// if release open browser if URL is valid
						if (urlAreaHit != nullptr) {
							node->getScreenNode()->getGUI()->addMouseOutCandidateNode(styledTextNode);
							if (event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
								if (StringTools::startsWith(urlAreaHit->url, "http://") == true || StringTools::startsWith(urlAreaHit->url, "https://") == true) {
									Application::openBrowser(urlAreaHit->url);
									return;
								}
							}
						}
						//
						event->setProcessed(true);
					}
					break;
				default:
					break;
			}
		} else {
			if (Application::getMouseCursor() != MOUSE_CURSOR_ENABLED) Application::setMouseCursor(MOUSE_CURSOR_ENABLED);
		}
	}
}

void GUIStyledTextNodeController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
}

void GUIStyledTextNodeController::tick()
{
}

void GUIStyledTextNodeController::onFocusGained()
{
}

void GUIStyledTextNodeController::onFocusLost()
{
}

bool GUIStyledTextNodeController::hasValue()
{
	return false;
}

const MutableString& GUIStyledTextNodeController::getValue()
{
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	return styledTextNode->getText();
}

void GUIStyledTextNodeController::setValue(const MutableString& value)
{
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	styledTextNode->setText(value);
}

void GUIStyledTextNodeController::onSubTreeChange()
{
}
