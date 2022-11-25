#include <tdme/gui/nodes/GUIStyledTextNodeController.h>

#include <algorithm>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/gui/elements/GUIStyledInputController.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::remove;
using std::string;
using std::to_string;
using std::vector;

using tdme::application::Application;
using tdme::gui::elements::GUIStyledInputController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUIStyledTextNodeController;
using tdme::gui::GUI;
using tdme::utilities::Character;
using tdme::utilities::Console;
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
	auto inputControllerNodeCandidate = node->getParentControllerNode();
	while (inputControllerNodeCandidate != nullptr) {
		if (dynamic_cast<GUIStyledInputController*>(inputControllerNodeCandidate->getController()) != nullptr) {
			input = true;
			break;
		}
		inputControllerNodeCandidate = inputControllerNodeCandidate->getParentControllerNode();
	}
}

void GUIStyledTextNodeController::dispose()
{
}

void GUIStyledTextNodeController::postLayout()
{
	//
	if (input == false) return;

	// extend styledTextNode auto width to parent width if this is larger
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	if (styledTextNode->getRequestsConstraints().widthType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		auto& styledTextNodeBorder = styledTextNode->getBorder();
		auto& styledTextNodePadding = styledTextNode->getPadding();
		auto styledTextNodeAutoWidth = styledTextNode->getContentWidth();
		auto parentNode = styledTextNode->getParentNode();
		auto parentNodeWidth = parentNode->getComputedConstraints().width;
		auto& parentNodeBorder = parentNode->getBorder();
		auto& parentNodePadding = parentNode->getPadding();
		if (parentNodeWidth > styledTextNodeAutoWidth) {
			styledTextNode->getComputedConstraints().width =
				parentNodeWidth
					- (parentNodeBorder.left + parentNodeBorder.right + parentNodePadding.left + parentNodePadding.right)
					- (styledTextNodeBorder.left + styledTextNodeBorder.right + styledTextNodePadding.left + styledTextNodePadding.right);
		}
	}
	if (styledTextNode->getRequestsConstraints().heightType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		auto& styledTextNodeBorder = styledTextNode->getBorder();
		auto& styledTextNodePadding = styledTextNode->getPadding();
		auto styledTextNodeAutoHeight = styledTextNode->getContentHeight();
		auto parentNode = styledTextNode->getParentNode();
		auto parentNodeHeight = parentNode->getComputedConstraints().height;
		auto& parentNodeBorder = parentNode->getBorder();
		auto& parentNodePadding = parentNode->getPadding();
		if (parentNodeHeight > styledTextNodeAutoHeight) {
			styledTextNode->getComputedConstraints().height =
				parentNodeHeight
					- (parentNodeBorder.top + parentNodeBorder.bottom + parentNodePadding.top + parentNodePadding.bottom)
					- (styledTextNodeBorder.top + styledTextNodeBorder.bottom + styledTextNodePadding.top + styledTextNodePadding.bottom);
		}
	}
}

void GUIStyledTextNodeController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	//
	auto released = false;
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	if (node == styledTextNode) {
		Vector2 nodeMouseCoordinate;
		Vector2 nodeMouseCoordinateNoOffsets;
		if (styledTextNode->isEventBelongingToNode(event, nodeMouseCoordinate) == true) {
			nodeMouseCoordinateNoOffsets = nodeMouseCoordinate.clone().sub(Vector2(styledTextNode->getParentNode()->getChildrenRenderOffsetX(), styledTextNode->getParentNode()->getChildrenRenderOffsetY()));
			switch(event->getType()) {
				case GUIMouseEvent::MOUSEEVENT_PRESSED:
					{
						if (input == true) {
							// submit to styled text node
							selectionIndex = -1;
							styledTextNode->setIndexMousePosition(nodeMouseCoordinateNoOffsets.getX(), nodeMouseCoordinateNoOffsets.getY());
							//
							resetCursorMode();
							//
							event->setProcessed(true);
						}

						//
						break;
					}
				case GUIMouseEvent::MOUSEEVENT_MOVED:
					{
						// find URL area that had a hit and setup corresponding cursor
						auto& urlAreas = styledTextNode->getURLAreas();
						const GUIStyledTextNode::URLArea* urlAreaHit = nullptr;
						for (auto& urlArea: urlAreas) {
							if (nodeMouseCoordinate.getX() < urlArea.left ||
								nodeMouseCoordinate.getY() < urlArea.top ||
								nodeMouseCoordinate.getX() > urlArea.left + urlArea.width ||
								nodeMouseCoordinate.getY() > urlArea.top + urlArea.height) {
								continue;
							}
							urlAreaHit = &urlArea;
							if (Application::getMouseCursor() != MOUSE_CURSOR_HAND) {
								Application::setMouseCursor(MOUSE_CURSOR_HAND);
								Console::println("hand: " + node->getId() + "(" + urlAreaHit->url + ")");
							}
							break;
						}
						if (urlAreaHit == nullptr) {
							if (Application::getMouseCursor() != MOUSE_CURSOR_ENABLED) {
								Application::setMouseCursor(MOUSE_CURSOR_ENABLED);
								Console::println("normal: " + node->getId());
							}
						}

						//
						event->setProcessed(true);

						//
						break;
					}
				case GUIMouseEvent::MOUSEEVENT_RELEASED:
					{
						if (input == true) {
							//
							styledTextNode->unsetIndexMousePosition();
							styledTextNode->unsetSelectionIndexMousePosition();

							//
							styledTextNode->getScreenNode()->removeTickNode(styledTextNode);

							//
							if (dragging == true && selectionIndex != -1) {
								auto _index = index;
								index = selectionIndex;
								selectionIndex = _index;
							}

							//
							released = true;

							//
							scrollMode = SCROLLMODE_NONE;
							//
							styledTextNode->scrollToIndex();
						}

						// find URL area that had a hit and setup corresponding cursor
						auto& urlAreas = styledTextNode->getURLAreas();
						const GUIStyledTextNode::URLArea* urlAreaHit = nullptr;
						for (auto& urlArea: urlAreas) {
							if (nodeMouseCoordinate.getX() < urlArea.left ||
								nodeMouseCoordinate.getY() < urlArea.top ||
								nodeMouseCoordinate.getX() > urlArea.left + urlArea.width ||
								nodeMouseCoordinate.getY() > urlArea.top + urlArea.height) {
								continue;
							}
							urlAreaHit = &urlArea;
							break;
						}
						// if release open browser if URL is valid
						if (urlAreaHit != nullptr) {
							node->getScreenNode()->getGUI()->addMouseOutCandidateNode(styledTextNode);
							if (StringTools::startsWith(urlAreaHit->url, "http://") == true || StringTools::startsWith(urlAreaHit->url, "https://") == true) {
								Application::openBrowser(urlAreaHit->url);
								return;
							}
						}
						//
						event->setProcessed(true);
					}
					break;
				default:
					break;
			}
		}

		//
		nodeMouseCoordinateNoOffsets = nodeMouseCoordinate.clone().sub(Vector2(styledTextNode->getParentNode()->getChildrenRenderOffsetX(), styledTextNode->getParentNode()->getChildrenRenderOffsetY()));

		//
		if (input == true) {
			// dragging, releasing
			switch(event->getType()) {
				case GUIMouseEvent::MOUSEEVENT_DRAGGED:
					{
						//
						dragging = true;
						//
						if (nodeMouseCoordinateNoOffsets.getY() < 50) {
							scrollMode = SCROLLMODE_UP;
							// unset
							styledTextNode->unsetIndexMousePosition();
							styledTextNode->unsetSelectionIndexMousePosition();
							//
							styledTextNode->getScreenNode()->addTickNode(styledTextNode);
						} else
						if (nodeMouseCoordinateNoOffsets.getY() > styledTextNode->getParentNode()->getComputedConstraints().height - 50) {
							scrollMode = SCROLLMODE_DOWN;
							// unset
							styledTextNode->unsetIndexMousePosition();
							styledTextNode->unsetSelectionIndexMousePosition();
							//
							styledTextNode->getScreenNode()->addTickNode(styledTextNode);
						} else {
							styledTextNode->getScreenNode()->removeTickNode(styledTextNode);
							//
							scrollMode = SCROLLMODE_NONE;
							// submit to styled text node
							styledTextNode->setSelectionIndexMousePosition(nodeMouseCoordinateNoOffsets.getX(), nodeMouseCoordinateNoOffsets.getY());
						}
						//
						resetCursorMode();
						//
						event->setProcessed(true);
						break;
					}
				case GUIMouseEvent::MOUSEEVENT_RELEASED:
					{
						if (released == false) {
							//
							styledTextNode->unsetIndexMousePosition();
							styledTextNode->unsetSelectionIndexMousePosition();

							//
							styledTextNode->getScreenNode()->removeTickNode(styledTextNode);

							//
							if (dragging == true && selectionIndex != -1) {
								auto _index = index;
								index = selectionIndex;
								selectionIndex = _index;
							}

							//
							scrollMode = SCROLLMODE_NONE;
							//
							styledTextNode->scrollToIndex();
							//
							event->setProcessed(true);
							//
							dragging = false;
						}
						break;
					}
				default:
					break;
			}
		}
	}
}

void GUIStyledTextNodeController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	if (input == false) return;

	//
	auto maxLength = 0;
	auto disabled = false;
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	auto keyControl = event->isControlDown();
	auto keyChar = event->getKeyChar();
	if (disabled == false &&
		keyControl == false &&
		event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED) {
		event->setProcessed(true);
		if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
			styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
			styledTextNode->scrollToIndex();
			forwardRemoveText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
			index = Math::min(index, selectionIndex);
			selectionIndex = -1;
		}
		if (maxLength == 0 || styledTextNode->getTextLength() < maxLength) {
			styledTextNode->insertText(index, event->getKeyChar());
			styledTextNode->scrollToIndex();
			forwardInsertText(index, 1);
			index++;
			resetCursorMode();
		}
	} else {
		auto keyControlA = false;
		auto keyControlX = false;
		auto keyControlC = false;
		auto keyControlV = false;
		auto keyControlSpace = false;
		auto isKeyDown = event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED;
		// determine select all, copy, paste, cut
		if (Character::toLowerCase(event->getKeyChar()) == 'a' && keyControl == true) {
			keyControlA = isKeyDown;
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
		if (event->getKeyChar() == ' ' && keyControl == true) {
			keyControlSpace = isKeyDown;
			event->setProcessed(true);
		}
		// handle them ...
		if (keyControlA == true) {
			auto& text = styledTextNode->getText();
			index = 0;
			selectionIndex = text.length() - 1;
		} else
		if (keyControlX == true) {
			if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
				auto& text = styledTextNode->getText();
				Application::getApplication()->setClipboardContent(StringTools::substring(text.getString(), Math::min(text.getUtf8BinaryIndex(index), text.getUtf8BinaryIndex(selectionIndex)), Math::max(text.getUtf8BinaryIndex(index), text.getUtf8BinaryIndex(selectionIndex))));
				styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
				styledTextNode->scrollToIndex();
				forwardRemoveText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
				index = Math::min(index, selectionIndex);
				selectionIndex = -1;
			}
		} else
		if (keyControlC == true) {
			if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
				auto& text = styledTextNode->getText();
				Application::getApplication()->setClipboardContent(StringTools::substring(text.getString(), Math::min(text.getUtf8BinaryIndex(index), text.getUtf8BinaryIndex(selectionIndex)), Math::max(text.getUtf8BinaryIndex(index), text.getUtf8BinaryIndex(selectionIndex))));
			}
		} else
		if (keyControlV == true) {
			auto clipboardContent = Application::getApplication()->getClipboardContent();
			auto clipboardContentLength = StringTools::getUtf8Length(clipboardContent);
			if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
				if (maxLength == 0 || styledTextNode->getTextLength() - Math::abs(index - selectionIndex) + clipboardContentLength < maxLength) {
					styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
					styledTextNode->scrollToIndex();
					forwardRemoveText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
					index = Math::min(index, selectionIndex);
					selectionIndex = -1;
				}
			}
			if (maxLength == 0 || styledTextNode->getTextLength() + clipboardContentLength < maxLength) {
				styledTextNode->insertText(index, clipboardContent);
				styledTextNode->scrollToIndex();
				forwardInsertText(index, clipboardContentLength);
				index+= clipboardContentLength;
			}
		} else
		if (keyControlSpace == true) {
			forwardCodeCompletion(index);
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
							styledTextNode->scrollToIndex();
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
						if (index < styledTextNode->getTextLength()) {
							index++;
							styledTextNode->scrollToIndex();
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
						//
						auto& text = styledTextNode->getText();
						// find index of current line newline and store difference
						auto lineNewLineIndex = styledTextNode->getPreviousNewLineUtf8(index);
						if (lineNewLineIndex == index) lineNewLineIndex = styledTextNode->getPreviousNewLineUtf8(index - 1);
						lineNewLineIndex++;
						// current line index
						auto lineIndex = Math::max(index - lineNewLineIndex, 0);
						// take tabs into account
						for (auto i = lineNewLineIndex; i < index; i++) {
							if (text.getUTF8CharAt(i) == '\t') lineIndex+= 3;
						}
						// store or reuse line index
						if (lineIndex != 0) {
							this->lineIndex = lineIndex;
						} else {
							lineIndex = this->lineIndex;
						}
						// find index of previous newline and iterate to difference if possible
						auto previousNewLineIndex = styledTextNode->getPreviousNewLineUtf8(styledTextNode->getPreviousNewLineUtf8(index - 1) - 1);
						if (previousNewLineIndex != 0) previousNewLineIndex++;
						// find next index of previous 2 newline as upper bound
						auto nextNewLineIndex = styledTextNode->getNextNewLineUtf8(previousNewLineIndex);
						// take tabs into account
						index = previousNewLineIndex;
						for (auto i = 0; i < lineIndex && index < nextNewLineIndex; ) {
							if (text.getUTF8CharAt(index) == '\t') i+= 4; else i+= 1;
							index++;
						}
						//
						styledTextNode->scrollToIndex();
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
						//
						auto& text = styledTextNode->getText();
						// find index of current line newline and store difference
						auto lineNewLineIndex = styledTextNode->getPreviousNewLineUtf8(index);
						if (lineNewLineIndex == index) lineNewLineIndex = styledTextNode->getPreviousNewLineUtf8(index - 1);
						lineNewLineIndex++;
						// current line index
						auto lineIndex = Math::max(index - lineNewLineIndex, 0);
						// take tabs into account
						for (auto i = lineNewLineIndex; i < index; i++) {
							if (text.getUTF8CharAt(i) == '\t') lineIndex+= 3;
						}
						// store or reuse line index
						if (lineIndex != 0) {
							this->lineIndex = lineIndex;
						} else {
							lineIndex = this->lineIndex;
						}
						// find index of next newline
						auto nextNewLineIndex = styledTextNode->getNextNewLineUtf8(index);
						// find index of next * 2 newline as upper bound
						auto next2NewLineIndex = styledTextNode->getNextNewLineUtf8(nextNewLineIndex + 1);
						// take tabs into account
						index = nextNewLineIndex + 1;
						for (auto i = 0; i < lineIndex && index < next2NewLineIndex; ) {
							if (text.getUTF8CharAt(index) == '\t') i+= 4; else i+= 1;
							index++;
						}
						//
						styledTextNode->scrollToIndex();
						resetCursorMode();
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_PAGE_UP: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						if (event->isShiftDown() == false) {
							selectionIndex = -1;
						} else {
							if (selectionIndex == -1) selectionIndex = index;
						}
						index = styledTextNode->doPageUp();
						resetCursorMode();
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_PAGE_DOWN: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						if (event->isShiftDown() == false) {
							selectionIndex = -1;
						} else {
							if (selectionIndex == -1) selectionIndex = index;
						}
						index = styledTextNode->doPageDown();
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
								styledTextNode->scrollToIndex();
								forwardRemoveText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
								index = Math::min(index, selectionIndex);
								selectionIndex = -1;
							} else
							if (index > 0) {
								styledTextNode->removeText(index - 1, 1);
								styledTextNode->scrollToIndex();
								forwardRemoveText(index - 1, 1);
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
								styledTextNode->scrollToIndex();
								forwardRemoveText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
								index = Math::min(index, selectionIndex);
								selectionIndex = -1;
							} else
							if (index < styledTextNode->getTextLength()) {
								styledTextNode->removeText(index, 1);
								styledTextNode->scrollToIndex();
								forwardRemoveText(index, 1);
								resetCursorMode();
							}
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_RETURN: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							// find out current line indenting
							string newLinePrefix;
							{
								auto& text = styledTextNode->getText();
								auto lineNewLineIndex = styledTextNode->getPreviousNewLineUtf8(index);
								if (lineNewLineIndex == index) lineNewLineIndex = styledTextNode->getPreviousNewLineUtf8(index - 1);
								lineNewLineIndex++;
								//
								for (auto i = lineNewLineIndex; i < index; i++) {
									auto c = text.getUTF8CharAt(i);
									if (c == ' ' || c == '\t') {
										newLinePrefix+= (char)c;
									} else {
										break;
									}
								}
							}
							//
							if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
								styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
								styledTextNode->scrollToIndex();
								forwardRemoveText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
								index = Math::min(index, selectionIndex);
								selectionIndex = -1;
							}
							if (maxLength == 0 || styledTextNode->getTextLength() < maxLength) {
								// insert new line and new line prefix
								styledTextNode->insertText(index, '\n' + newLinePrefix);
								styledTextNode->scrollToIndex();
								forwardInsertText(index, 1);
								index+= 1 + newLinePrefix.size();
								resetCursorMode();
							}
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_TAB: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
								styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
								styledTextNode->scrollToIndex();
								forwardRemoveText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
								index = Math::min(index, selectionIndex);
								selectionIndex = -1;
							}
							if (maxLength == 0 || styledTextNode->getTextLength() < maxLength) {
								styledTextNode->insertText(index, '\t');
								styledTextNode->scrollToIndex();
								forwardInsertText(index, 1);
								index++;
								resetCursorMode();
							}
						}
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
							// find index of previous newline
							index = styledTextNode->getPreviousNewLineUtf8(index - 1);
							if (index != 0) index++;
						}
						styledTextNode->scrollToIndex();
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
							index = styledTextNode->getTextLength() - 1;
						} else {
							// find index of next newline
							index = styledTextNode->getNextNewLineUtf8(index);;
						}
						styledTextNode->scrollToIndex();
					}
				}
				break;
			}
		}
	}
}

void GUIStyledTextNodeController::tick()
{
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	if (scrollMode == SCROLLMODE_UP) {
		// find index of current line newline and store difference
		auto lineNewLineIndex = styledTextNode->getPreviousNewLineUtf8(selectionIndex) + (selectionIndex == 0?0:1);
		// current line index
		auto lineIndex = Math::max(selectionIndex - lineNewLineIndex, 0);
		// find index of previous newline and iterate to difference if possible
		auto previousNewLineIndex = styledTextNode->getPreviousNewLineUtf8(styledTextNode->getPreviousNewLineUtf8(selectionIndex - 1) - 1);
		if (previousNewLineIndex != 0) previousNewLineIndex++;
		// find next index of previous 2 newline as upper bound
		auto nextNewLineIndex = styledTextNode->getNextNewLineUtf8(previousNewLineIndex);
		//
		selectionIndex = Math::min(previousNewLineIndex + lineIndex, nextNewLineIndex);
		//
		styledTextNode->scrollToSelectionIndex();
	} else
	if (scrollMode == SCROLLMODE_DOWN) {
		// find index of current line newline and store difference
		auto lineNewLineIndex = styledTextNode->getPreviousNewLineUtf8(selectionIndex) + (selectionIndex == 0?0:1);
		// current line index
		auto lineIndex = Math::max(selectionIndex - lineNewLineIndex, 0);
		// find index of next newline
		auto nextNewLineIndex = styledTextNode->getNextNewLineUtf8(selectionIndex);
		// find index of next * 2 newline as upper bound
		auto next2NewLineIndex = styledTextNode->getNextNewLineUtf8(nextNewLineIndex + 1);
		// iterate to difference if possible
		selectionIndex = Math::min(nextNewLineIndex + 1 + lineIndex, next2NewLineIndex);
		//
		styledTextNode->scrollToSelectionIndex();
	}
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

void GUIStyledTextNodeController::addChangeListener(ChangeListener* listener)
{
	removeChangeListener(listener);
	changeListeners.push_back(listener);
}

void GUIStyledTextNodeController::removeChangeListener(ChangeListener* listener)
{
	changeListeners.erase(std::remove(changeListeners.begin(), changeListeners.end(), listener), changeListeners.end());
}

void GUIStyledTextNodeController::addCodeCompletionListener(CodeCompletionListener* listener) {
	removeCodeCompletionListener(listener);
	codeCompletionListeners.push_back(listener);
}

void GUIStyledTextNodeController::removeCodeCompletionListener(CodeCompletionListener* listener) {
	codeCompletionListeners.erase(std::remove(codeCompletionListeners.begin(), codeCompletionListeners.end(), listener), codeCompletionListeners.end());
}

void GUIStyledTextNodeController::forwardRemoveText(int idx, int count) {
	// determine binary start and end positions
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	auto& text = styledTextNode->getText();
	auto u8It = text.getUTF8CharacterIterator();
	u8It.seekCharacterPosition(idx);
	auto binaryStartIdx = u8It.getBinaryPosition();
	for (auto i = 0; u8It.hasNext() == true && i < count; i++) u8It.next();
	auto binaryEndIdx = u8It.getBinaryPosition();
	// forward remove text
	for (auto i = 0; i < changeListeners.size(); i++) {
		changeListeners[i]->onRemoveText(binaryStartIdx, binaryEndIdx - binaryStartIdx);
	}
}

void GUIStyledTextNodeController::forwardInsertText(int idx, int count) {
	// determine binary start and end positions
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	auto& text = styledTextNode->getText();
	auto u8It = text.getUTF8CharacterIterator();
	u8It.seekCharacterPosition(idx);
	auto binaryStartIdx = u8It.getBinaryPosition();
	for (auto i = 0; u8It.hasNext() == true && i < count; i++) u8It.next();
	auto binaryEndIdx = u8It.getBinaryPosition();

	//
	for (auto i = 0; i < changeListeners.size(); i++) {
		changeListeners[i]->onInsertText(binaryStartIdx, binaryEndIdx - binaryStartIdx);
	}
}

void GUIStyledTextNodeController::forwardCodeCompletion(int idx) {
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	auto& text = styledTextNode->getText();
	auto binaryIdx = text.getUtf8BinaryIndex(idx);
	for (auto i = 0; i < changeListeners.size(); i++) {
		codeCompletionListeners[i]->onCodeCompletion(binaryIdx);
	}
}
