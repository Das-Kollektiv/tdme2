#include <tdme/gui/nodes/GUIInputInternalController.h>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/gui/elements/GUIInputController.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIInputInternalNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIFont.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using tdme::gui::nodes::GUIInputInternalController;

using tdme::application::Application;
using tdme::gui::elements::GUIInputController;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIInputInternalController_CursorMode;
using tdme::gui::nodes::GUIInputInternalNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIFont;
using tdme::gui::GUI;
using tdme::utilities::Character;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

constexpr int64_t GUIInputInternalController::CURSOR_MODE_DURATION;
constexpr int64_t GUIInputInternalController::DRAGGING_CALMDOWN;

GUIInputInternalController::GUIInputInternalController(GUINode* node)
	: GUINodeController(node)
{
}

bool GUIInputInternalController::isDisabled()
{
	return false;
}

void GUIInputInternalController::setDisabled(bool disabled)
{
}

void GUIInputInternalController::initialize()
{
	inputNode = required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode());

	auto typeAsString = StringTools::toLowerCase(inputNode->getOptionValue("type"));
	if (typeAsString == "float") type = TYPE_FLOAT; else
	if (typeAsString == "int") type = TYPE_INT; else
		type = TYPE_STRING;

	auto minAsString = inputNode->getOptionValue("min");
	auto maxAsString = inputNode->getOptionValue("max");
	auto stepAsString = inputNode->getOptionValue("step");
	auto decimalsAsString = inputNode->getOptionValue("decimals");

	min = Float::parse(minAsString);
	max = Float::parse(maxAsString);
	step = Float::parse(stepAsString);

	if (decimalsAsString.empty() == false)
		decimals = Integer::parse(decimalsAsString);

	haveMin = minAsString.empty() == false;
	haveMax = maxAsString.empty() == false;
	haveStep = stepAsString.empty() == false;

	formatText();
}

void GUIInputInternalController::dispose()
{
}

void GUIInputInternalController::postLayout()
{
}

void GUIInputInternalController::resetCursorMode()
{
	cursorModeStarted = Time::getCurrentMillis();
	cursorMode = CURSORMODE_SHOW;
}

GUIInputInternalController::CursorMode GUIInputInternalController::getCursorMode()
{
	if (cursorModeStarted == -1) {
		resetCursorMode();
		return cursorMode;
	}
	if (mouseDraggingSelectionActive == true) {
		return CURSORMODE_SHOW;
	}
	if (Time::getCurrentMillis() - cursorModeStarted > CURSOR_MODE_DURATION) {
		cursorMode = cursorMode == CURSORMODE_SHOW?CURSORMODE_HIDE:CURSORMODE_SHOW;
		cursorModeStarted = Time::getCurrentMillis();
	}
	return cursorMode;
}

void GUIInputInternalController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	auto disabled = required_dynamic_cast<GUIInputController*>(inputNode->getController())->isDisabled();
	if (disabled == true) {
		return;
	}
	if (event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
		if (doubleClick == true) {
			//
			auto textInputNode = required_dynamic_cast<GUIInputInternalNode*>(node);
			auto& text = textInputNode->getText();
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
		} else
		if (mouseDraggingSlideValueActive == false) {
			if (node->isEventBelongingToNode(event) == true &&
				event->getButton() == MOUSE_BUTTON_LEFT) {
				auto textInputNode = required_dynamic_cast<GUIInputInternalNode*>(node);
				index = textInputNode->getFont()->getTextIndexByX(
					textInputNode->getText(),
					offset,
					0,
					event->getX() -
						(
							textInputNode->computedConstraints.left + textInputNode->computedConstraints.alignmentLeft +
							textInputNode->border.left+ textInputNode->padding.left
						)
				);
				resetCursorMode();
				event->setProcessed(true);
				if (editMode == false) {
					index = 0;
					selectionIndex = textInputNode->getText().length() == 0?-1:textInputNode->getText().length();
				}
				editMode = true;
			}
		} else
		if (mouseDraggingSlideValueActive == true) {
			// Application::setMouseCursor(MOUSE_CURSOR_NORMAL);
			Application::setMousePosition(mouseOriginalPosition[0], mouseOriginalPosition[1]);
		}
		Application::setMouseCursor(MOUSE_CURSOR_NORMAL); // TODO: fix me
		mouseDraggingInit = false;
		mouseDraggingSlideValueActive = false;
		mouseDraggingSelectionActive = false;
		mouseDragPosition[0] = -1;
		mouseDragPosition[1] = -1;
		mouseOriginalPosition[0] = -1;
		mouseOriginalPosition[1] = -1;
		event->setProcessed(true);
	} else
	if (mouseDraggingInit == true || mouseDraggingSlideValueActive == true || mouseDraggingSelectionActive == true) {
		if (mouseDraggingInit == true &&
			Math::abs(mouseDragPosition[0] - event->getXUnscaled()) >= 10) {
			mouseDraggingInit = false;
			if (editMode == false) {
				mouseDraggingSlideValueActive = true;
				auto application = Application::getApplication();
				Application::setMouseCursor(MOUSE_CURSOR_DISABLED);
				Application::setMousePosition(mouseOriginalPosition[0], mouseOriginalPosition[1]);
			} else {
				mouseDraggingSelectionActive = true;
				selectionIndex = index;
			}
			mouseDragPosition[0] = Application::getMousePositionX();
			mouseDragPosition[1] = Application::getMousePositionY();
		}
		if (mouseDraggingSlideValueActive == true) {
			auto textInputNode = required_dynamic_cast<GUIInputInternalNode*>(node);
			switch (type) {
				case TYPE_STRING:
					break;
				case TYPE_FLOAT:
					{
						auto mouseDraggedX = Application::getMousePositionX() - mouseDragPosition[0];
						auto value = Float::parse(textInputNode->getText().getString());
						if (haveStep == true) {
							value+= static_cast<float>(mouseDraggedX) * step;
						}
						if (haveMin == true) {
							if (value < min) value = min;
						}
						if (haveMax == true) {
							if (value > max) value = max;
						}
						textInputNode->getText().set(value, decimals);
						node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
					}
					break;
				case TYPE_INT:
					{
						auto mouseDraggedX = Application::getMousePositionX() - mouseDragPosition[0];
						auto value = Integer::parse(textInputNode->getText().getString());
						if (haveStep == true) {
							value+= mouseDraggedX * static_cast<int>(step);
						}
						if (haveMin == true) {
							if (value < static_cast<int>(min)) value = static_cast<int>(min);
						}
						if (haveMax == true) {
							if (value > static_cast<int>(max)) value = static_cast<int>(max);
						}
						textInputNode->getText().set(value);
						node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
					}
					break;
			}
			auto application = Application::getApplication();
			Application::setMousePosition(mouseOriginalPosition[0], mouseOriginalPosition[1]);
			mouseDragPosition[0] = Application::getMousePositionX();
			mouseDragPosition[1] = Application::getMousePositionY();
		} else
		if (mouseDraggingSelectionActive == true) {
			auto textInputNode = required_dynamic_cast<GUIInputInternalNode*>(node);
			index = textInputNode->getFont()->getTextIndexByX(
				textInputNode->getText(),
				offset,
				0,
				event->getX() -
					(
						textInputNode->computedConstraints.left + textInputNode->computedConstraints.alignmentLeft +
						textInputNode->border.left+ textInputNode->padding.left
					)
			);
		}
		event->setProcessed(true);
	} else
	if (node == this->node &&
		node->isEventBelongingToNode(event) == true &&
		event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED &&
		event->getButton() == MOUSE_BUTTON_LEFT) {
		//
		if (timeLastClick != -1LL &&
			Time::getCurrentMillis() - timeLastClick < TIME_DOUBLECLICK) {
			doubleClick = true;
			timeLastClick = -1LL;
		} else {
			timeLastClick = Time::getCurrentMillis();
			doubleClick = false;
		}

		//
		auto textInputNode = required_dynamic_cast<GUIInputInternalNode*>(node);
		index = textInputNode->getFont()->getTextIndexByX(
			textInputNode->getText(),
			offset,
			0,
			event->getX() -
				(
					textInputNode->computedConstraints.left + textInputNode->computedConstraints.alignmentLeft +
					textInputNode->border.left+ textInputNode->padding.left
				)
		);
		resetCursorMode();
		mouseDraggingInit = true;
		mouseOriginalPosition[0] = Application::getMousePositionX();
		mouseOriginalPosition[1] = Application::getMousePositionY();
		selectionIndex = -1;
		event->setProcessed(true);
	}
}

void GUIInputInternalController::checkOffset()
{
	if (index < offset) {
		offset = index;
		return;
	}
	auto textInputNode = required_dynamic_cast<GUIInputInternalNode*>(node);
	auto textInputNodeConstraints = textInputNode->computedConstraints;
	auto textInputNodeBorder = textInputNode->border;
	auto textInputNodePadding = textInputNode->padding;
	auto textInputNodeWidth = textInputNodeConstraints.width - textInputNodeBorder.left - textInputNodeBorder.right - textInputNodePadding.left - textInputNodePadding.right;
	auto charsMax = textInputNode->getFont()->getTextIndexByX(textInputNode->getText(), offset, 0, textInputNodeWidth) - offset;
	if (index - offset >= charsMax) {
		offset = index - charsMax;
	}
}

void GUIInputInternalController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	auto disabled = required_dynamic_cast<GUIInputController*>(inputNode->getController())->isDisabled();
	if (disabled == true) {
		return;
	}

	//
	editMode = true;

	//
	auto textInputNode = required_dynamic_cast<GUIInputInternalNode*>(node);
	auto keyControl = event->isControlDown();
	auto keyChar = event->getKeyChar();
	if (disabled == false &&
		keyControl == false &&
		event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED &&
		(
			(type == TYPE_STRING) ||
			(type == TYPE_FLOAT && ((keyChar >= '0' && keyChar <= '9') || (keyChar == '.') || keyChar == '-')) ||
			(type == TYPE_INT && ((keyChar >= '0' && keyChar <= '9') || keyChar == '-'))
		)) {
		event->setProcessed(true);
		if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
			textInputNode->getText().remove(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
			index = Math::min(index, selectionIndex);
			selectionIndex = -1;
		}
		if (textInputNode->getMaxLength() == 0 || textInputNode->getText().length() < textInputNode->getMaxLength()) {
			if (type == TYPE_FLOAT && keyChar == '.' && textInputNode->getText().getString().find('.') != string::npos) {
				// no op
			} else
			if (type == TYPE_FLOAT && keyChar == '-' && (textInputNode->getText().getString().find('-') != string::npos || index != 0)) {
				// no op
			} else
			if (type == TYPE_INT && keyChar == '-' && (textInputNode->getText().getString().find('-') != string::npos || index != 0)) {
				// no op
			} else {
				textInputNode->getText().insert(index, Character::toString(event->getKeyChar()));
				index++;
				resetCursorMode();
				checkOffset();
				required_dynamic_cast<GUIInputController*>(inputNode->getController())->onChange();
				node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
			}
		}
	} else {
		auto keyControlA = false;
		auto keyControlX = false;
		auto keyControlC = false;
		auto keyControlV = false;
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
		// handle them
		if (keyControlA == true) {
			index = 0;
			selectionIndex = textInputNode->getText().length();
		} else
		if (keyControlX == true && disabled == false) {
			if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
				auto& text = textInputNode->getText();
				Application::getApplication()->setClipboardContent(StringTools::substring(text.getString(), Math::min(text.getUtf8BinaryIndex(index), text.getUtf8BinaryIndex(selectionIndex)), Math::max(text.getUtf8BinaryIndex(index), text.getUtf8BinaryIndex(selectionIndex))));
				textInputNode->getText().remove(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
				index = Math::min(index, selectionIndex);
				selectionIndex = -1;
				checkOffset();
			}
		} else
		if (keyControlC == true || keyControlX == true) {
			if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
				auto& text = textInputNode->getText();
				Application::getApplication()->setClipboardContent(StringTools::substring(text.getString(), Math::min(text.getUtf8BinaryIndex(index), text.getUtf8BinaryIndex(selectionIndex)), Math::max(text.getUtf8BinaryIndex(index), text.getUtf8BinaryIndex(selectionIndex))));
			}
		} else
		if (keyControlV == true) {
			if (disabled == false) {
				auto clipboardContent = Application::getApplication()->getClipboardContent();
				auto clipboardContentLength = StringTools::getUtf8Length(clipboardContent);
				if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
					if (textInputNode->getMaxLength() == 0 || textInputNode->getText().length() - Math::abs(index - selectionIndex) + clipboardContentLength < textInputNode->getMaxLength()) {
						textInputNode->getText().remove(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
						index = Math::min(index, selectionIndex);
						selectionIndex = -1;
					}
				}
				if (textInputNode->getMaxLength() == 0 || textInputNode->getText().length() + clipboardContentLength < textInputNode->getMaxLength()) {
					textInputNode->getText().insert(index, clipboardContent);
					index+= clipboardContentLength;
					checkOffset();
				}
			}
		} else {
			// navigation, delete, return
			switch (event->getKeyCode()) {
			case GUIKeyboardEvent::KEYCODE_LEFT: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						auto wordLeftIdx = -1;
						if (event->isControlDown() == true) {
							auto textInputNode = required_dynamic_cast<GUIInputInternalNode*>(node);
							auto& text = textInputNode->getText();
							auto textLength = text.length();
							if (textLength > 0) {
								wordLeftIdx = 0;
								auto i = index - 1;
								for (; i >= 0 && Character::isAlphaNumeric(text.getUTF8CharAt(i)) == false; i--);
								for (; i >= 0; i--) {
									auto c = text.getUTF8CharAt(i);
									if (Character::isAlphaNumeric(c) == false) {
										wordLeftIdx = i + 1;
										break;
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
							checkOffset();
							resetCursorMode();
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_RIGHT: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						auto wordRightIdx = -1;
						if (event->isControlDown() == true) {
							auto textInputNode = required_dynamic_cast<GUIInputInternalNode*>(node);
							auto& text = textInputNode->getText();
							auto textLength = text.length();
							if (textLength > 0) {
								wordRightIdx = textLength;
								auto i = index + 1;
								for (; i < textLength && Character::isAlphaNumeric(text.getUTF8CharAt(i)) == false; i++);
								for (; i < textLength; i++) {
									auto c = text.getUTF8CharAt(i);
									if (Character::isAlphaNumeric(c) == false) {
										wordRightIdx = i;
										break;
									}
								}
								for (; wordRightIdx < textLength && Character::isAlphaNumeric(text.getUTF8CharAt(wordRightIdx)) == false; wordRightIdx++);
							}
						}
						if (event->isShiftDown() == false) {
							selectionIndex = -1;
						} else {
							if (selectionIndex == -1) selectionIndex = index;
						}
						if (index < textInputNode->getText().length()) {
							if (wordRightIdx == -1) {
								index++;
							} else {
								index = wordRightIdx;
							}
							checkOffset();
							resetCursorMode();
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_BACKSPACE: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
								textInputNode->getText().remove(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
								index = Math::min(index, selectionIndex);
								selectionIndex = -1;
								required_dynamic_cast<GUIInputController*>(inputNode->getController())->onChange();
								node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
							} else
							if (index > 0) {
								textInputNode->getText().remove(index - 1, 1);
								index--;
								checkOffset();
								resetCursorMode();
								required_dynamic_cast<GUIInputController*>(inputNode->getController())->onChange();
								node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
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
								textInputNode->getText().remove(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
								index = Math::min(index, selectionIndex);
								selectionIndex = -1;
								required_dynamic_cast<GUIInputController*>(inputNode->getController())->onChange();
								node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
							} else
							if (index < textInputNode->getText().length()) {
								textInputNode->getText().remove(index, 1);
								resetCursorMode();
								required_dynamic_cast<GUIInputController*>(inputNode->getController())->onChange();
								node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
							}
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_RETURN: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							node->getScreenNode()->forwardAction(GUIActionListenerType::PERFORMED, required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_POS1: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							resetCursorMode();
							if (event->isShiftDown() == false) {
								selectionIndex = -1;
							} else {
								if (selectionIndex == -1) selectionIndex = index;
							}
							index = 0;
							checkOffset();
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_END: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							resetCursorMode();
							if (event->isShiftDown() == false) {
								selectionIndex = -1;
							} else {
								if (selectionIndex == -1) selectionIndex = index;
							}
							index = textInputNode->getText().length();
							checkOffset();
						}
					}
				}
				break;
			}
		}
	}
}

void GUIInputInternalController::tick()
{
}

void GUIInputInternalController::onFocusGained()
{
}

void GUIInputInternalController::onFocusLost()
{
	formatText();
	editMode = false;
	index = 0;
	selectionIndex = -1;
}

bool GUIInputInternalController::hasValue()
{
	return false;
}

const MutableString& GUIInputInternalController::getValue()
{
	return value;
}

void GUIInputInternalController::setValue(const MutableString& value)
{
}

void GUIInputInternalController::onTextUpdate()
{
	auto textInputNode = required_dynamic_cast<GUIInputInternalNode*>(node);
	if (index < 0) index = 0;
	if (index >= textInputNode->getText().length()) index = textInputNode->getText().length();
	if (selectionIndex != -1) {
		if (selectionIndex < 0) selectionIndex = 0;
		if (selectionIndex >= textInputNode->getText().length()) selectionIndex = textInputNode->getText().length();
	}
	checkOffset();
	resetCursorMode();
}

bool GUIInputInternalController::isShowCursor()
{
	return editMode;
}

void GUIInputInternalController::formatText()
{
	auto textInputNode = required_dynamic_cast<GUIInputInternalNode*>(node);
	auto originalText = textInputNode->getText().getString();
	switch (type) {
		case TYPE_STRING:
			break;
		case TYPE_FLOAT:
			{
				auto stringValue = StringTools::trim(textInputNode->getText().getString());
				auto value = stringValue == "-"?0.0f:Float::parse(stringValue);
				if (haveMin == true) {
					if (value < min) value = min;
				}
				if (haveMax == true) {
					if (value > max) value = max;
				}
				if (value == 0.0f && StringTools::startsWith(stringValue, "-") == true && (haveMin == false || min < 0.0f)) {
					textInputNode->getText().set("-");
					textInputNode->getText().append(value, decimals);
				} else {
					textInputNode->getText().set(value, decimals);
				}
			}
			break;
		case TYPE_INT:
			{
				auto stringValue = StringTools::trim(textInputNode->getText().getString());
				auto value = stringValue == "-"?0:Integer::parse(stringValue);
				if (haveMin == true) {
					if (value < static_cast<int>(min)) value = static_cast<int>(min);
				}
				if (haveMax == true) {
					if (value > static_cast<int>(max)) value = static_cast<int>(max);
				}
				if (value == 0 && StringTools::startsWith(stringValue, "-") == true && (haveMin == false || min < 0.0f)) {
					textInputNode->getText().set("-");
					textInputNode->getText().append(value);
				} else {
					textInputNode->getText().set(value);
				}
			}
			break;
	}
	if (originalText != textInputNode->getText().getString()) {
		node->getScreenNode()->forwardAction(GUIActionListenerType::PERFORMED, required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
	}
}

void GUIInputInternalController::onSubTreeChange()
{
}
