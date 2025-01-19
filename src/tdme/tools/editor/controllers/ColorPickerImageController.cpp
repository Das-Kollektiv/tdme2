#include <tdme/tools/editor/controllers/ColorPickerImageController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/Color4.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUIImageNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeConditions.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/math/Vector2.h>
#include <tdme/tools/editor/controllers/ColorPickerScreenController.h>

using std::string;
using std::to_string;

using tdme::tools::editor::controllers::ColorPickerImageController;

using tdme::engine::Texture;
using tdme::engine::Color4;
using agui::gui::events::GUIActionListenerType;
using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIImageNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::math::Vector2;
using tdme::tools::editor::controllers::ColorPickerScreenController;

ColorPickerImageController::ColorPickerImageController(GUINode* node, ColorPickerScreenController* colorPickerScreenController)
	: GUINodeController(node), colorPickerScreenController(colorPickerScreenController)
{
}

bool ColorPickerImageController::isDisabled()
{
	return false;
}

void ColorPickerImageController::setDisabled(bool disabled)
{
}

void ColorPickerImageController::initialize()
{
}

void ColorPickerImageController::dispose()
{
}

void ColorPickerImageController::postLayout()
{
}

void ColorPickerImageController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	Vector2 imageMouseCoordinate;
	if (node == this->node && this->node->isEventBelongingToNode(event, imageMouseCoordinate) == true && event->getButton() == MOUSE_BUTTON_LEFT) {
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED || event->getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) {
			auto imageNode = required_dynamic_cast<GUIImageNode*>(this->node);
			auto imageNodeWidth = imageNode->getComputedConstraints().width;
			auto imageNodeHeight = imageNode->getComputedConstraints().height;
			auto imageNodeTexture = imageNode->getTexture();
			if (imageNodeTexture != nullptr) {
				auto textureWidth = imageNodeTexture->getTextureWidth();
				auto textureHeight = imageNodeTexture->getTextureHeight();
				auto textureData = imageNodeTexture->getRGBTextureData();
				auto textureX = static_cast<int>(static_cast<float>(textureWidth) * (imageMouseCoordinate[0] / imageNodeWidth));
				auto textureY = static_cast<int>(static_cast<float>(textureHeight) * (imageMouseCoordinate[1] / imageNodeHeight));
				auto textureBytesPerPixel = -1;
				switch (imageNodeTexture->getRGBDepthBitsPerPixel()) {
					case 24:
						textureBytesPerPixel = 3;
						break;
					case 32:
						textureBytesPerPixel = 4;
						break;
				}
				auto texturePixelOffset = textureY * textureWidth * textureBytesPerPixel + textureX * textureBytesPerPixel;
				colorPickerScreenController->setColor(
					Color4(
						static_cast<float>(textureData.get(texturePixelOffset + 0)) / 255.0f,
						static_cast<float>(textureData.get(texturePixelOffset + 1)) / 255.0f,
						static_cast<float>(textureData.get(texturePixelOffset + 2)) / 255.0f,
						1.0f
					)
				);
			}
		}
		event->setProcessed(true);
	}
}

void ColorPickerImageController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
}

void ColorPickerImageController::tick()
{
}

void ColorPickerImageController::onFocusGained()
{
}

void ColorPickerImageController::onFocusLost()
{
}

bool ColorPickerImageController::hasValue()
{
	return false;
}

const MutableString& ColorPickerImageController::getValue()
{
	return value;
}

void ColorPickerImageController::setValue(const MutableString& value)
{
}

void ColorPickerImageController::onSubTreeChange()
{
}
