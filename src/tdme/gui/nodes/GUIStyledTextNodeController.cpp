#include <tdme/gui/nodes/GUIStyledTextNodeController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::string;
using std::to_string;

using tdme::application::Application;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUIStyledTextNodeController;
using tdme::gui::GUI;
using tdme::utilities::Console;
using tdme::utilities::Character;
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
	//
	auto maxLength = 0;
	auto disabled = false;
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	auto keyControl = event->isControlDown();
	auto keyChar = event->getKeyChar();
	if (disabled == false &&
		keyControl == false &&
		keyChar >= 32 && keyChar < 127) {
		event->setProcessed(true);
		if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED) {
			if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
				styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
				index = Math::min(index, selectionIndex);
				selectionIndex = -1;
			}
			if (maxLength == 0 || styledTextNode->getTextSize() < maxLength) {
				styledTextNode->insertText(index, event->getKeyChar());
				index++;
				resetCursorMode();
			}
		}
	} else {
		auto keyControlX = false;
		auto keyControlC = false;
		auto keyControlV = false;
		auto isKeyDown = event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED;
		// copy, paste, cut
		{
			if (event->getKeyChar() == 24) {
				keyControlX = isKeyDown;
				event->setProcessed(true);
			}
			if (event->getKeyChar() == 3) {
				keyControlC = isKeyDown;
				event->setProcessed(true);
			}
			if (event->getKeyChar() == 22) {
				keyControlV = isKeyDown;
				event->setProcessed(true);
			}
			if (Character::toLowerCase(event->getKeyChar()) == 'x' && keyControl == true) {
				keyControlX = isKeyDown;
				event->setProcessed(true);
			}
			if (Character::toLowerCase(event->getKeyChar()) == 'c' && keyControl == true) {
				keyControlC = isKeyDown;
				event->setProcessed(true);
			}
			if (Character::toLowerCase(event->getKeyChar()) == 'v' && keyControl == true) {
				keyControlV = isKeyDown;
				event->setProcessed(true);
			}
		}
		if (keyControlX == true) {
			Application::getApplication()->setClipboardContent(StringTools::substring(styledTextNode->getText().getString(), Math::min(index, selectionIndex), Math::max(index, selectionIndex)));
			if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
				styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
				index = Math::min(index, selectionIndex);
				selectionIndex = -1;
			}
		} else
		if (keyControlC == true) {
			if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
				Application::getApplication()->setClipboardContent(StringTools::substring(styledTextNode->getText().getString(), Math::min(index, selectionIndex), Math::max(index, selectionIndex)));
			}
		} else
		if (keyControlV == true) {
			auto clipboardContent = Application::getApplication()->getClipboardContent();
			if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
				if (maxLength == 0 || styledTextNode->getTextSize() - Math::abs(index - selectionIndex) + clipboardContent.size() < maxLength) {
					styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
					index = Math::min(index, selectionIndex);
					selectionIndex = -1;
				}
			}
			if (maxLength == 0 || styledTextNode->getTextSize() + clipboardContent.size() < maxLength) {
				styledTextNode->insertText(index, clipboardContent);
				index+= clipboardContent.size();
			}
		} else {
			// navigation, delete, return
			switch (event->getKeyCode()) {
			case GUIKeyboardEvent::KEYCODE_LEFT: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						if (event->isShiftDown() == false) {
							selectionIndex = -1;
						} else {
							if (selectionIndex == -1) selectionIndex = index;
						}
						if (index > 0) {
							index--;
							resetCursorMode();
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_RIGHT: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						if (event->isShiftDown() == false) {
							selectionIndex = -1;
						} else {
							if (selectionIndex == -1) selectionIndex = index;
						}
						if (index < styledTextNode->getTextSize()) {
							index++;
							resetCursorMode();
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_UP: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						if (event->isShiftDown() == false) {
							selectionIndex = -1;
						} else {
							if (selectionIndex == -1) selectionIndex = index;
						}
						// find index of previous newline and store difference
						auto& text = styledTextNode->getText();
						auto previousNewLineIndex = index;
						while (previousNewLineIndex >= 0 && text.charAt(previousNewLineIndex) != '\n') previousNewLineIndex--;
						previousNewLineIndex = Math::min(previousNewLineIndex + 1, text.size() - 1);
						auto lineIndex = index - previousNewLineIndex;
						// find index of previous newline and iterate to difference if possible
						auto previous2NewLineIndex = Math::max(previousNewLineIndex - 2, 0);
						while (previous2NewLineIndex >= 0 && text.charAt(previous2NewLineIndex) != '\n') previous2NewLineIndex--;
						previous2NewLineIndex = Math::min(previous2NewLineIndex + 1, text.size() - 1);
						//
						index = Math::max(previous2NewLineIndex + lineIndex, 0);
						//
						resetCursorMode();
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_DOWN: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						if (event->isShiftDown() == false) {
							selectionIndex = -1;
						} else {
							if (selectionIndex == -1) selectionIndex = index;
						}
						// find index of previous newline and store difference
						auto& text = styledTextNode->getText();
						auto previousNewLineIndex = index;
						while (previousNewLineIndex >= 0 && text.charAt(previousNewLineIndex) != '\n') previousNewLineIndex--;
						previousNewLineIndex = Math::min(previousNewLineIndex + 1, text.size() - 1);
						auto lineIndex = index - previousNewLineIndex;
						// find index of next newline
						auto nextNewLineIndex = Math::min(text.charAt(index) == '\n'?index + 1:index, text.size() - 1);
						while (nextNewLineIndex < text.size() && text.charAt(nextNewLineIndex) != '\n') nextNewLineIndex++;
						nextNewLineIndex = Math::min(nextNewLineIndex + 1, text.size() - 1);
						// find index of next * 2 newline as upper bound
						auto next2NewLineIndex = Math::min(nextNewLineIndex + 1, text.size() - 1);
						while (next2NewLineIndex < text.size() && text.charAt(next2NewLineIndex) != '\n') next2NewLineIndex++;
						// iterate to difference if possible
						index = Math::min(nextNewLineIndex + lineIndex, next2NewLineIndex - 1);
						//
						resetCursorMode();
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_BACKSPACE: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
								styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
								index = Math::min(index, selectionIndex);
								selectionIndex = -1;
							} else
							if (index > 0) {
								styledTextNode->removeText(index - 1, 1);
								index--;
								resetCursorMode();
							}
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_DELETE: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
								styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
								index = Math::min(index, selectionIndex);
								selectionIndex = -1;
							} else
							if (index < styledTextNode->getTextSize()) {
								styledTextNode->removeText(index, 1);
								resetCursorMode();
							}
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_RETURN: {
					if (disabled == false) {
						event->setProcessed(true);
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_POS1: {
					if (disabled == false) {
						event->setProcessed(true);
						resetCursorMode();
						if (event->isShiftDown() == false) {
							selectionIndex = -1;
						} else {
							if (selectionIndex == -1) selectionIndex = index;
						}
						if (keyControl == true) {
							index = 0;
						} else {
							// find index of previous newline and store difference
							auto& text = styledTextNode->getText();
							auto previousNewLineIndex = Math::max(text.charAt(index) == '\n'?index - 1:index, 0);
							while (previousNewLineIndex >= 0 && text.charAt(previousNewLineIndex) != '\n') previousNewLineIndex--;
							previousNewLineIndex = Math::min(previousNewLineIndex + 1, text.size() - 1);
							index = previousNewLineIndex;
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_END: {
					if (disabled == false) {
						resetCursorMode();
						if (event->isShiftDown() == false) {
							selectionIndex = -1;
						} else {
							if (selectionIndex == -1) selectionIndex = index;
						}
						if (keyControl == true) {
							index = styledTextNode->getTextSize() - 1;
						} else {
							// find index of next newline
							auto& text = styledTextNode->getText();
							auto nextNewLineIndex = index;
							while (nextNewLineIndex < text.size() && text.charAt(nextNewLineIndex) != '\n') nextNewLineIndex++;
							index = nextNewLineIndex;
						}
					}
				}
				break;
			}
		}
	}
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
