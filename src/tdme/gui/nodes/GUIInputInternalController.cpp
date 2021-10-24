#include <tdme/gui/nodes/GUIInputInternalController.h>

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
	this->cursorModeStarted = -1LL;
	this->cursorMode = CURSORMODE_SHOW;
	this->index = 0;
	this->offset = 0;
	this->mouseDraggingSlideValueActive = false;
	this->mouseDraggingInit = false;
	this->mouseDragPosition = {{ -1, -1 }};
	this->mouseOriginalPosition = {{ -1, -1 }};
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

	min = Float::parseFloat(minAsString);
	max = Float::parseFloat(maxAsString);
	step = Float::parseFloat(stepAsString);

	if (decimalsAsString.empty() == false)
		decimals = Integer::parseInt(decimalsAsString);

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
	if (node == this->node &&
		event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED == true) {
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
				editMode = true;
			}
		}
		if (mouseDraggingSlideValueActive == true) {
			Application::setMouseCursor(MOUSE_CURSOR_NORMAL);
			Application::setMousePosition(mouseOriginalPosition[0], mouseOriginalPosition[1]);
		}
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
			(Math::abs(mouseDragPosition[0] - event->getXUnscaled()) >= 5 ||
			Math::abs(mouseDragPosition[1] - event->getYUnscaled()) >= 5)) {
			mouseDraggingInit = false;
			if (editMode == false) {
				mouseDraggingSlideValueActive = true;
				auto application = Application::getApplication();
				Application::setMouseCursor(MOUSE_CURSOR_DISABLED);
				Application::setMousePosition(
					application->getWindowXPosition() + application->getWindowWidth() / 2,
					application->getWindowYPosition() + application->getWindowHeight() / 2
				);
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
						auto value = Float::parseFloat(textInputNode->getText().getString());
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
						node->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
					}
					break;
				case TYPE_INT:
					{
						auto mouseDraggedX = Application::getMousePositionX() - mouseDragPosition[0];
						auto value = Integer::parseInt(textInputNode->getText().getString());
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
						node->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
					}
					break;
			}
			auto application = Application::getApplication();
			Application::setMousePosition(
				application->getWindowXPosition() + application->getWindowWidth() / 2,
				application->getWindowYPosition() + application->getWindowHeight() / 2
			);
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
	if (node == this->node && node->isEventBelongingToNode(event) == true &&
		event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED == true &&
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
		mouseDraggingInit = true;
		mouseOriginalPosition[0] = Application::getMousePositionX();
		mouseOriginalPosition[1] = Application::getMousePositionY();
		selectionIndex = -1;
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
		(
			(type == TYPE_STRING && keyChar >= 32 && keyChar < 127) ||
			(type == TYPE_FLOAT && ((keyChar >= '0' && keyChar < '9') || (keyChar == '.') || keyChar == '-')) ||
			(type == TYPE_INT && ((keyChar >= '0' && keyChar < '9') || keyChar == '-'))
		)) {
		event->setProcessed(true);
		#if defined(VULKAN) || defined(GLFW3)
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED) {
		#else
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
		#endif
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
					textInputNode->getText().insert(index, event->getKeyChar());
					index++;
					resetCursorMode();
					checkOffset();
					required_dynamic_cast<GUIInputController*>(inputNode->getController())->onValueChange();
					node->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
				}
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
			Application::getApplication()->setClipboardContent(StringTools::substring(textInputNode->getText().getString(), Math::min(index, selectionIndex), Math::max(index, selectionIndex)));
			if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
				textInputNode->getText().remove(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
				index = Math::min(index, selectionIndex);
				selectionIndex = -1;
				checkOffset();
			}
		} else
		if (keyControlC == true) {
			if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
				Application::getApplication()->setClipboardContent(StringTools::substring(textInputNode->getText().getString(), Math::min(index, selectionIndex), Math::max(index, selectionIndex)));
			}
		} else
		if (keyControlV == true) {
			auto clipboardContent = Application::getApplication()->getClipboardContent();
			if (index != -1 && selectionIndex != -1 && index != selectionIndex) {
				if (textInputNode->getMaxLength() == 0 || textInputNode->getText().length() - Math::abs(index - selectionIndex) + clipboardContent.size() < textInputNode->getMaxLength()) {
					textInputNode->getText().remove(Math::min(index, selectionIndex), Math::abs(index - selectionIndex));
					index = Math::min(index, selectionIndex);
					selectionIndex = -1;
				}
			}
			if (textInputNode->getMaxLength() == 0 || textInputNode->getText().length() + clipboardContent.size() < textInputNode->getMaxLength()) {
				textInputNode->getText().insert(index, clipboardContent);
				index+= clipboardContent.size();
				checkOffset();
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
							checkOffset();
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
						if (index < textInputNode->getText().length()) {
							index++;
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
							} else
							if (index > 0) {
								textInputNode->getText().remove(index - 1, 1);
								index--;
								checkOffset();
								resetCursorMode();
								required_dynamic_cast<GUIInputController*>(inputNode->getController())->onValueChange();
								node->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
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
							} else
							if (index < textInputNode->getText().length()) {
								textInputNode->getText().remove(index, 1);
								resetCursorMode();
								required_dynamic_cast<GUIInputController*>(inputNode->getController())->onValueChange();
								node->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
							}
						}
					}
				}
				break;
			case GUIKeyboardEvent::KEYCODE_RETURN: {
					if (disabled == false) {
						event->setProcessed(true);
						if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
							node->getScreenNode()->delegateActionPerformed(GUIActionListenerType::PERFORMED, required_dynamic_cast<GUIElementNode*>(node->getParentControllerNode()));
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
						index = 0;
						checkOffset();
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
						index = textInputNode->getText().length();
						checkOffset();
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

void GUIInputInternalController::reset()
{
	index = 0;
	offset = 0;
	resetCursorMode();
}

bool GUIInputInternalController::isShowCursor()
{
	return editMode;
}

void GUIInputInternalController::formatText()
{
	switch (type) {
		case TYPE_STRING:
			break;
		case TYPE_FLOAT:
			{
				auto textInputNode = required_dynamic_cast<GUIInputInternalNode*>(node);
				auto stringValue = StringTools::trim(textInputNode->getText().getString());
				auto value = stringValue == "-"?0.0f:Float::parseFloat(stringValue);
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
				auto textInputNode = required_dynamic_cast<GUIInputInternalNode*>(node);
				auto stringValue = StringTools::trim(textInputNode->getText().getString());
				auto value = stringValue == "-"?0:Integer::parseInt(stringValue);
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
}

void GUIInputInternalController::onSubTreeChange()
{
}
