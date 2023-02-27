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
			input = required_dynamic_cast<GUIStyledTextNode*>(this->node)->isEditable();
			//
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
						//
						if (input == true) storeTypingHistoryEntry();
						//
						if (timeLastClick != -1LL &&
							Time::getCurrentMillis() - timeLastClick < TIME_DOUBLECLICK) {
							doubleClick = true;
							timeLastClick = -1LL;
						} else {
							timeLastClick = Time::getCurrentMillis();
							doubleClick = false;
						}

						// submit to styled text node
						selectionIndex = -1;
						styledTextNode->setIndexMousePosition(nodeMouseCoordinateNoOffsets.getX(), nodeMouseCoordinateNoOffsets.getY());
						//
						resetCursorMode();
						//
						event->setProcessed(true);

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
							//
						if (input == true) storeTypingHistoryEntry();
						//
						if (doubleClick == true) {
							//
							auto& text = styledTextNode->getText();
							auto textLength = text.length();
							if (textLength > 0) {
								auto wordLeftIdx = 0;
								for (auto i = 0; i < index && i < textLength; i++) {
									auto c = text.getUTF8CharAt(i);
									if (Character::isAlphaNumeric(c) == false) {
										wordLeftIdx = i + 1;
									}
								}
								auto wordRightIdx = textLength;
								for (auto i = index; i < textLength; i++) {
									auto c = text.getUTF8CharAt(i);
									if (Character::isAlphaNumeric(c) == false) {
										wordRightIdx = i;
										break;
									}
								}
								if (wordLeftIdx != wordRightIdx) {
									index = wordLeftIdx;
									selectionIndex = wordRightIdx;
								}
								//
								resetCursorMode();
							}
							//
							doubleClick = false;
						} else {
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

						//
						if (input == true) unsetTypingHistoryEntryIdx();

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

		// dragging, releasing
		switch(event->getType()) {
			case GUIMouseEvent::MOUSEEVENT_DRAGGED:
				{
					//
					if (input == true) storeTypingHistoryEntry();
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
						if (input == true) storeTypingHistoryEntry();

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
						//
						unsetTypingHistoryEntryIdx();
					}
					break;
				}
			default:
				break;
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
	if (disabled == false &&
		event->isControlDown() == false &&
		event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED) {
		event->setProcessed(true);
		//
		auto selection = selectionIndex != -1 && index != selectionIndex;
		if (event->getKeyChar() == ' ' || selection == true) {
			storeTypingHistoryEntry();
		}
		//
		if (selection == true) {
			//
			storeDeletionHistoryEntry(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
			//
			styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
			styledTextNode->scrollToIndex();
			forwardRemoveText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
			//
			index = Math::min(index, selectionIndex);
			selectionIndex = -1;
		}
		if (maxLength == 0 || styledTextNode->getTextLength() < maxLength) {
			//
			setTypingHistoryEntryIdx();
			//
			styledTextNode->insertText(index, event->getKeyChar());
			styledTextNode->scrollToIndex();
			forwardInsertText(index, 1);
			index++;
			resetCursorMode();
		}
		//
		typedChars = true;
		//
		if (selection == true) {
			storeTypingHistoryEntry();
			unsetTypingHistoryEntryIdx();
		}
		//
		typedChars = true;
	} else {
		if (Character::toLowerCase(event->getKeyChar()) == 'z' && event->isControlDown() == true && event->isShiftDown() == true) {
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) redo();
			event->setProcessed(true);
		} else
		if (Character::toLowerCase(event->getKeyChar()) == 'z' && event->isControlDown() == true) {
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) undo();
			event->setProcessed(true);
		} else
		// determine select all, copy, paste, cut
		if (Character::toLowerCase(event->getKeyChar()) == 'a' && event->isControlDown() == true) {
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) selectAll();
			event->setProcessed(true);
		} else
		if (Character::toLowerCase(event->getKeyChar()) == 'x' && event->isControlDown() == true) {
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) cut();
			event->setProcessed(true);
		} else
		if (Character::toLowerCase(event->getKeyChar()) == 'c' && event->isControlDown() == true) {
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) copy();
			event->setProcessed(true);
		} else
		if (Character::toLowerCase(event->getKeyChar()) == 'v' && event->isControlDown() == true) {
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) paste();
			event->setProcessed(true);
		} else
		if (event->getKeyChar() == ' ' && event->isControlDown() == true) {
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) forwardCodeCompletion(index);
			event->setProcessed(true);
		} else {
			// navigation, delete, return
			switch (event->getKeyCode()) {
			case GUIKeyboardEvent::KEYCODE_LEFT: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						//
						storeTypingHistoryEntry();
						//
						auto wordLeftIdx = -1;
						auto lineStartIdx = styledTextNode->getPreviousNewLineUtf8(index - 1);
						if (lineStartIdx != 0) lineStartIdx++;
						if (event->isControlDown() == true) {
							string delimiter = "^´!\"§$%&/()=?`+#<,.-*'>;:_";
							auto& text = styledTextNode->getText();
							auto textLength = text.length();
							if (textLength > 0) {
								wordLeftIdx = lineStartIdx;
								auto i = index - 1;
								for (; i >= lineStartIdx; i--) {
									auto c = text.getUTF8CharAt(i);
									if (Character::isAlphaNumeric(c) == true || delimiter.find(c) != string::npos) break;
								}
								if (delimiter.find(text.getUTF8CharAt(i)) != string::npos) {
									for (; i >= lineStartIdx && delimiter.find(text.getUTF8CharAt(i)) != string::npos; i--);
									wordLeftIdx = i + 1;
								} else {
									for (; i >= lineStartIdx; i--) {
										auto c = text.getUTF8CharAt(i);
										if (Character::isAlphaNumeric(c) == false || delimiter.find(c) != string::npos) {
											wordLeftIdx = i + 1;
											break;
										}
									}
								}
							}
						}
						if (event->isShiftDown() == false) {
							selectionIndex = -1;
						} else {
							if (selectionIndex == -1) selectionIndex = index;
						}
						if (index > 0) {
							if (wordLeftIdx == -1) {
								index--;
							} else {
								index = wordLeftIdx;
							}
							styledTextNode->scrollToIndex();
							resetCursorMode();
						}
						//
						unsetTypingHistoryEntryIdx();
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_RIGHT: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						//
						storeTypingHistoryEntry();
						//
						auto wordRightIdx = -1;
						if (event->isControlDown() == true) {
							string delimiter = "^´!\"§$%&/()=?`+#<,.-*'>;:_";
							auto& text = styledTextNode->getText();
							auto lineEndIdx = styledTextNode->getNextNewLineUtf8(index);
							if (lineEndIdx > 0) {
								wordRightIdx = lineEndIdx;
								auto i = index;
								for (; i < lineEndIdx; i++) {
									auto c = text.getUTF8CharAt(i);
									if (Character::isAlphaNumeric(c) == true || delimiter.find(c) != string::npos) break;
								}
								if (delimiter.find(text.getUTF8CharAt(i)) != string::npos) {
									for (; i < lineEndIdx && delimiter.find(text.getUTF8CharAt(i)) != string::npos; i++);
									wordRightIdx = i;
								} else {
									for (; i < lineEndIdx; i++) {
										auto c = text.getUTF8CharAt(i);
										if (Character::isAlphaNumeric(c) == false || delimiter.find(c) != string::npos) {
											wordRightIdx = i;
											break;
										}
									}
								}
								if (Character::isSpace(text.getUTF8CharAt(i)) == true) {
									for (; i < lineEndIdx && Character::isSpace(text.getUTF8CharAt(i)) == true; i++);
									wordRightIdx = i;
								}
							}
						}
						if (event->isShiftDown() == false) {
							selectionIndex = -1;
						} else {
							if (selectionIndex == -1) selectionIndex = index;
						}
						if (index < styledTextNode->getTextLength()) {
							if (wordRightIdx == -1) {
								index++;
							} else {
								index = wordRightIdx;
							}
							styledTextNode->scrollToIndex();
							resetCursorMode();
						}
						//
						unsetTypingHistoryEntryIdx();
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_UP: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						//
						storeTypingHistoryEntry();
						//
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
						//
						unsetTypingHistoryEntryIdx();
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_DOWN: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						//
						storeTypingHistoryEntry();
						//
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
						//
						unsetTypingHistoryEntryIdx();
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_PAGE_UP: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						//
						storeTypingHistoryEntry();
						//
						if (event->isShiftDown() == false) {
							selectionIndex = -1;
						} else {
							if (selectionIndex == -1) selectionIndex = index;
						}
						index = styledTextNode->doPageUp();
						resetCursorMode();
						//
						unsetTypingHistoryEntryIdx();
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_PAGE_DOWN: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						//
						storeTypingHistoryEntry();
						//
						if (event->isShiftDown() == false) {
							selectionIndex = -1;
						} else {
							if (selectionIndex == -1) selectionIndex = index;
						}
						index = styledTextNode->doPageDown();
						resetCursorMode();
						//
						unsetTypingHistoryEntryIdx();
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_BACKSPACE: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							//
							storeTypingHistoryEntry();
							//
							if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
								storeDeletionHistoryEntryStoreTypingEntry(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
								styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
								styledTextNode->scrollToIndex();
								forwardRemoveText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
								index = Math::min(index, selectionIndex);
								selectionIndex = -1;
							} else
							if (index > 0) {
								storeDeletionHistoryEntryStoreTypingEntry(index - 1, 1);
								styledTextNode->removeText(index - 1, 1);
								styledTextNode->scrollToIndex();
								forwardRemoveText(index - 1, 1);
								index--;
								resetCursorMode();
							}
							//
							unsetTypingHistoryEntryIdx();
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_DELETE: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							delete_();
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_RETURN: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							//
							setTypingHistoryEntryIdx();
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
							//
							typedChars = true;
							//
							storeTypingHistoryEntry();
							unsetTypingHistoryEntryIdx();
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_TAB: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							//
							storeTypingHistoryEntry();
							//
							if ((maxLength == 0 || styledTextNode->getTextLength() + 1 < maxLength) &&
								index != -1 && selectionIndex != -1 && index != selectionIndex) {
								//
								auto lineNewLineIndex = styledTextNode->getPreviousNewLineUtf8(Math::min(index, selectionIndex)) + (Math::min(index, selectionIndex) == 0?0:1);
								styledTextNode->insertText(lineNewLineIndex, '\t');
								forwardInsertText(lineNewLineIndex, 1);
								storeTypingHistoryEntry2(lineNewLineIndex, "\t");
								if (index > selectionIndex) index++; else selectionIndex++;
								//
								auto nextNewLineIndex = lineNewLineIndex;
								for (;;) {
									//
									nextNewLineIndex = styledTextNode->getNextNewLineUtf8(nextNewLineIndex) + 1;
									styledTextNode->insertText(nextNewLineIndex, '\t');
									forwardInsertText(nextNewLineIndex, 1);
									storeTypingHistoryEntry2(nextNewLineIndex, "\t");
									if (index > selectionIndex) index++; else selectionIndex++;
									if (nextNewLineIndex > Math::max(index, selectionIndex)) break;
									if (styledTextNode->getTextLength() >= maxLength) break;
								}
							} else
							if ((maxLength == 0 || styledTextNode->getTextLength() < maxLength) &&
								index != -1 && selectionIndex == -1) {
								//
								setTypingHistoryEntryIdx();
								//
								styledTextNode->insertText(index, '\t');
								styledTextNode->scrollToIndex();
								forwardInsertText(index, 1);
								index++;
								resetCursorMode();
								//
								typedChars = true;
							}
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_POS1: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							//
							storeTypingHistoryEntry();
							//
							resetCursorMode();
							if (event->isShiftDown() == false) {
								selectionIndex = -1;
							} else {
								if (selectionIndex == -1) selectionIndex = index;
							}
							if (event->isControlDown() == true) {
								index = 0;
							} else {
								// find index of previous newline
								index = styledTextNode->getPreviousNewLineUtf8(index - 1);
								if (index != 0) index++;

							}
							styledTextNode->scrollToIndex();
							//
							unsetTypingHistoryEntryIdx();
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_END: {
					if (disabled == false) {
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							//
							storeTypingHistoryEntry();
							//
							resetCursorMode();
							if (event->isShiftDown() == false) {
								selectionIndex = -1;
							} else {
								if (selectionIndex == -1) selectionIndex = index;
							}
							if (event->isControlDown() == true) {
								index = styledTextNode->getTextLength() - 1;
							} else {
								// find index of next newline
								index = styledTextNode->getNextNewLineUtf8(index);;
							}
							styledTextNode->scrollToIndex();
							//
							unsetTypingHistoryEntryIdx();
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

void GUIStyledTextNodeController::storeTypingHistoryEntry() {
	Console::println("GUIStyledTextNodeController::storeTypingHistoryEntry()");

	// if no char has been typed we have nothing to do
	if (typedChars == false) {
		return;
	}

	// unset
	typedChars = false;

	// no position to start storing from?
	if (historyEntryIdx == -1) {
		return;
	}

	// get upper modification char bound
	auto index = this->index;
	if (selectionIndex != -1) index = Math::max(index, selectionIndex);

	// no change?
	if (historyEntryIdx == index) {
		historyEntryIdx = -1;
		return;
	}

	// we need to remove history from now on
	if (historyIdx != -1 && historyIdx < history.size()) {
		history.erase(history.begin() + historyIdx, history.end());
		historyIdx = history.size();
	}

	//
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	auto& text = styledTextNode->getText();
	auto u8It = text.getUTF8CharacterIterator();
	u8It.seekCharacterPosition(historyEntryIdx);
	string data;
	for (; u8It.hasNext() == true && u8It.getCharacterPosition() < index;) Character::appendToString(data, u8It.next());
	history.push_back(
		{
			.type = HistoryEntry::TYPE_INSERT,
			.idx = historyEntryIdx,
			.data = data,
			.joinable = false
		}
	);
	//
	historyEntryIdx = -1;

	// just point to the latest history entry
	historyIdx = history.size();

	//
	for (auto i = history.size() - 1; i < history.size(); i++) {
		auto& historyEntry = history[i];
		string historyEntryTypeString;
		switch (historyEntry.type) {
			case HistoryEntry::TYPE_NONE:
				historyEntryTypeString = "NONE";
				break;
			case HistoryEntry::TYPE_INSERT:
				historyEntryTypeString = "INSERT";
				break;
			case HistoryEntry::TYPE_DELETE:
				historyEntryTypeString = "DELETE";
				break;

		}
		Console::println("GUIStyledTextNodeController::storeTypingHistoryEntry(): " + to_string(i) + ": history entry @ " + to_string(historyEntry.idx) + ": '" + historyEntry.data + "'" + ": " + historyEntryTypeString);
	}
}

void GUIStyledTextNodeController::storeTypingHistoryEntry2(int index, const string& data) {
	Console::println("GUIStyledTextNodeController::storeTypingHistoryEntry2()");

	// we need to remove history from now on
	if (historyIdx != -1 && historyIdx < history.size()) {
		history.erase(history.begin() + historyIdx, history.end());
		historyIdx = history.size();
	}

	//
	history.push_back(
		{
			.type = HistoryEntry::TYPE_INSERT,
			.idx = index,
			.data = data,
			.joinable = false
		}
	);
	//
	historyEntryIdx = -1;

	// just point to the latest history entry
	historyIdx = history.size();

	//
	for (auto i = history.size() - 1; i < history.size(); i++) {
		auto& historyEntry = history[i];
		string historyEntryTypeString;
		switch (historyEntry.type) {
			case HistoryEntry::TYPE_NONE:
				historyEntryTypeString = "NONE";
				break;
			case HistoryEntry::TYPE_INSERT:
				historyEntryTypeString = "INSERT";
				break;
			case HistoryEntry::TYPE_DELETE:
				historyEntryTypeString = "DELETE";
				break;

		}
		Console::println("GUIStyledTextNodeController::storeTypingHistoryEntry2(): " + to_string(i) + ": history entry @ " + to_string(historyEntry.idx) + ": '" + historyEntry.data + "'" + ": " + historyEntryTypeString);
	}
}

void GUIStyledTextNodeController::storeDeletionHistoryInternal(int index, int count) {
	Console::println("GUIStyledTextNodeController::storeDeletionHistoryInternal(): " + to_string(index) + " / " + to_string(count));
	//
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	auto& text = styledTextNode->getText();
	auto u8It = text.getUTF8CharacterIterator();
	u8It.seekCharacterPosition(index);
	string data;
	for (auto i = 0; u8It.hasNext() == true && i < count; i++) Character::appendToString(data, u8It.next());
	history.push_back(
		{
			.type = HistoryEntry::TYPE_DELETE,
			.idx = index,
			.data = data,
			.joinable = count == 1
		}
	);
	// just point to the latest history entry
	historyIdx = history.size();

	//
	for (auto i = history.size() - 1; i < history.size(); i++) {
		auto& historyEntry = history[i];
		string historyEntryTypeString;
		switch (historyEntry.type) {
			case HistoryEntry::TYPE_NONE:
				historyEntryTypeString = "NONE";
				break;
			case HistoryEntry::TYPE_INSERT:
				historyEntryTypeString = "INSERT";
				break;
			case HistoryEntry::TYPE_DELETE:
				historyEntryTypeString = "DELETE";
				break;

		}
		Console::println("GUIStyledTextNodeController::storeDeletionHistoryInternal(): " + to_string(i) + ": history entry @ " + to_string(historyEntry.idx) + ": '" + historyEntry.data + "'" + ": " + historyEntryTypeString);
	}
	//
}

void GUIStyledTextNodeController::redo() {
	//
	storeTypingHistoryEntry();

	//
	Console::println("GUIStyledTextNodeController::redo(): " + to_string(historyIdx) + " / " + to_string(history.size()));

	// exit if no history
	if (history.empty() == true) return;

	// after undoing everything we can point to history index of -1
	if (historyIdx == -1) historyIdx = 0;

	// do not go further than the history entries we have
	if (historyIdx >= history.size()) return;

	//
	auto& historyEntry = history[historyIdx];

	//
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	switch (historyEntry.type) {
		case HistoryEntry::TYPE_INSERT:
			{
				auto dataUtf8Length = StringTools::getUtf8Length(historyEntry.data);
				index = historyEntry.idx;
				selectionIndex = -1;
				styledTextNode->insertText(index, historyEntry.data);
				forwardInsertText(index, dataUtf8Length);
				index+= dataUtf8Length;
			}
			break;
		case HistoryEntry::TYPE_DELETE:
			{
				index = historyEntry.idx;
				selectionIndex = -1;
				auto dataUtf8Length = StringTools::getUtf8Length(historyEntry.data);
				styledTextNode->removeText(index, dataUtf8Length);
				forwardRemoveText(index, dataUtf8Length);
			}
			break;
		default: break;
	}

	//
	historyIdx++;

	//
	styledTextNode->scrollToIndex();
}

void GUIStyledTextNodeController::undo() {
	//
	storeTypingHistoryEntry();

	//
	// Console::println("GUIStyledTextNodeController::undo(): " + to_string(historyIdx) + " / " + to_string(history.size()));

	// skip if empty history
	if (history.empty() == true) return;

	// we should not go beyond first history entry
	if (historyIdx == 0) return;

	//
	historyIdx--;

	//
	auto& historyEntry = history[historyIdx];

	//
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);

	//
	switch (historyEntry.type) {
		case HistoryEntry::TYPE_INSERT:
			{
				index = historyEntry.idx;
				selectionIndex = -1;
				auto dataUtf8Length = StringTools::getUtf8Length(historyEntry.data);
				styledTextNode->removeText(index, dataUtf8Length);
				forwardRemoveText(index, dataUtf8Length);
			}
			break;
		case HistoryEntry::TYPE_DELETE:
			{
				auto dataUtf8Length = StringTools::getUtf8Length(historyEntry.data);
				index = historyEntry.idx;
				selectionIndex = -1;
				styledTextNode->insertText(index, historyEntry.data);
				forwardInsertText(index, dataUtf8Length);
				index+= dataUtf8Length;
			}
			break;
		default: break;
	}

	//
	styledTextNode->scrollToIndex();
}

void GUIStyledTextNodeController::selectAll() {
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	auto& text = styledTextNode->getText();
	index = 0;
	selectionIndex = text.length() - 1;
}

void GUIStyledTextNodeController::cut() {
	//
	storeTypingHistoryEntry();
	//
	if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
		auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
		auto& text = styledTextNode->getText();
		Application::getApplication()->setClipboardContent(StringTools::substring(text.getString(), Math::min(text.getUtf8BinaryIndex(index), text.getUtf8BinaryIndex(selectionIndex)), Math::max(text.getUtf8BinaryIndex(index), text.getUtf8BinaryIndex(selectionIndex))));
		storeDeletionHistoryEntryStoreTypingEntry(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
		styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
		styledTextNode->scrollToIndex();
		forwardRemoveText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
		index = Math::min(index, selectionIndex);
		selectionIndex = -1;
	}
	//
	unsetTypingHistoryEntryIdx();
}

void GUIStyledTextNodeController::copy() {
	if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
		auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
		auto& text = styledTextNode->getText();
		Application::getApplication()->setClipboardContent(StringTools::substring(text.getString(), Math::min(text.getUtf8BinaryIndex(index), text.getUtf8BinaryIndex(selectionIndex)), Math::max(text.getUtf8BinaryIndex(index), text.getUtf8BinaryIndex(selectionIndex))));
	}
}

void GUIStyledTextNodeController::paste() {
	//
	storeTypingHistoryEntry();
	//
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	auto maxLength = 0;
	auto clipboardContent = Application::getApplication()->getClipboardContent();
	auto clipboardContentLength = StringTools::getUtf8Length(clipboardContent);
	if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
		if (maxLength == 0 || styledTextNode->getTextLength() - Math::abs(index - selectionIndex) + clipboardContentLength < maxLength) {
			storeDeletionHistoryEntryStoreTypingEntry(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
			styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
			styledTextNode->scrollToIndex();
			forwardRemoveText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
			index = Math::min(index, selectionIndex);
			selectionIndex = -1;
		}
	}
	//
	if (maxLength == 0 || styledTextNode->getTextLength() + clipboardContentLength < maxLength) {
		//
		setTypingHistoryEntryIdx();
		typedChars = true;
		//
		styledTextNode->insertText(index, clipboardContent);
		styledTextNode->scrollToIndex();
		forwardInsertText(index, clipboardContentLength);
		index+= clipboardContentLength;
		//
		storeTypingHistoryEntry();
	}
	//
	unsetTypingHistoryEntryIdx();
}

void GUIStyledTextNodeController::delete_() {
	//
	storeTypingHistoryEntry();
	//
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
		storeDeletionHistoryEntryStoreTypingEntry(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
		styledTextNode->removeText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
		styledTextNode->scrollToIndex();
		forwardRemoveText(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
		index = Math::min(index, selectionIndex);
		selectionIndex = -1;
	} else
	if (index < styledTextNode->getTextLength()) {
		storeDeletionHistoryEntryStoreTypingEntry(index, 1);
		styledTextNode->removeText(index, 1);
		styledTextNode->scrollToIndex();
		forwardRemoveText(index, 1);
		resetCursorMode();
	}
	//
	unsetTypingHistoryEntryIdx();
}

void GUIStyledTextNodeController::replace(const string& by, int index, int count) {
	auto styledTextNode = required_dynamic_cast<GUIStyledTextNode*>(this->node);
	// unselect
	setSelectionIndex(-1);
	// remove
	storeDeletionHistoryEntryStoreTypingEntry(index, count);
	styledTextNode->removeText(index, count);
	// insert
	setIndex(index);
	setTypingHistoryEntryIdx();
	styledTextNode->insertText(index, by);
	typedChars = true;
	setIndex(index + StringTools::getUtf8Length(by));
	storeTypingHistoryEntry();
	// unset history typing index
	unsetTypingHistoryEntryIdx();

}
