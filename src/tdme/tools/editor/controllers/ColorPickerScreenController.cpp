#include <tdme/tools/editor/controllers/ColorPickerScreenController.h>

#include <string>

#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIMultilineTextNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/HexEncDec.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::HexEncDec;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

ColorPickerScreenController::ColorPickerScreenController()
{
}

GUIScreenNode* ColorPickerScreenController::getScreenNode()
{
	return screenNode;
}

void ColorPickerScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_colorpicker.xml");
		screenNode->setVisible(false);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenNode->addFocusListener(this);
		redInput = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("colorpicker_red"));
		greenInput = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("colorpicker_green"));
		blueInput = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("colorpicker_blue"));
		alphaInput = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("colorpicker_alpha"));
		hexInput = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("colorpicker_hex"));
		brightnessSlider = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("slider_colorpicker_brightness"));
	} catch (Exception& exception) {
		Console::print(string("ColorPickerScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void ColorPickerScreenController::dispose()
{
	screenNode = nullptr;
}

void ColorPickerScreenController::show(const Color4Base& color)
{
	this->initialColor = color;
	this->color = color;
	updateColor();
	updateColorHex();
	screenNode->setVisible(true);
}

void ColorPickerScreenController::close()
{
	screenNode->setVisible(false);
}

void ColorPickerScreenController::onValueChanged(GUIElementNode* node) {
	Console::println("ColorPickerScreenController::onValueChanged(): " + node->getId());
	if (node->getId() == "colorpicker_red") {
		color.setRed(Float::parseFloat(node->getController()->getValue().getString()) / 255.0f);
		updateColor();
		updateColorHex();
	} else
	if (node->getId() == "colorpicker_green") {
		color.setGreen(Float::parseFloat(node->getController()->getValue().getString()) / 255.0f);
		updateColor();
		updateColorHex();
	} else
	if (node->getId() == "colorpicker_blue") {
		color.setBlue(Float::parseFloat(node->getController()->getValue().getString()) / 255.0f);
		updateColor();
		updateColorHex();
	} else
	if (node->getId() == "colorpicker_alpha") {
		color.setAlpha(Float::parseFloat(node->getController()->getValue().getString()) / 255.0f);
		updateColor();
		updateColorHex();
	} else
	if (node->getId() == "colorpicker_hex") {
		auto hexString = StringTools::trim(node->getController()->getValue().getString());
		if (StringTools::startsWith(hexString, "#") == true) hexString = StringTools::substring(hexString, 1);
		if (hexString.size() >= 2) {
			color.setRed(static_cast<float>(HexEncDec::decodeInt(StringTools::substring(hexString, 0, 2)) / 255.0f));
		}
		if (hexString.size() >= 4) {
			color.setGreen(static_cast<float>(HexEncDec::decodeInt(StringTools::substring(hexString, 2, 4)) / 255.0f));
		}
		if (hexString.size() >= 6) {
			color.setBlue(static_cast<float>(HexEncDec::decodeInt(StringTools::substring(hexString, 4, 6)) / 255.0f));
		}
		if (hexString.size() >= 8) {
			color.setAlpha(static_cast<float>(HexEncDec::decodeInt(StringTools::substring(hexString, 6, 8)) / 255.0f));
		}
		updateColor();
	} else
	if (node->getId() == "slider_colorpicker_brightness") {

	}
}

void ColorPickerScreenController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	Console::println("ColorPickerScreenController::onActionPerformed(): " + to_string(type) + ": " + node->getId());
	if (type == GUIActionListenerType::PERFORMED) {
		if (StringTools::startsWith(node->getId(), "colorpicker_caption_close_") == true) { // TODO: a.drewke, check with DH) {
			close();
		}
	}
}

void ColorPickerScreenController::onFocus(GUIElementNode* node) {
}

void ColorPickerScreenController::onUnfocus(GUIElementNode* node) {
	if (node->getId() == "colorpicker_hex") {
		updateColorHex();
	}
}


void ColorPickerScreenController::updateColor() {
	redInput->getController()->setValue(MutableString((int)(color.getRed() * 255.0f)));
	greenInput->getController()->setValue(MutableString((int)(color.getGreen() * 255.0f)));
	blueInput->getController()->setValue(MutableString((int)(color.getBlue() * 255.0f)));
	alphaInput->getController()->setValue(MutableString((int)(color.getAlpha() * 255.0f)));
	brightnessSlider->getController()->setValue(MutableString((color.getRed() + color.getGreen() + color.getBlue()) / 3.0f));
}

void ColorPickerScreenController::updateColorHex() {
	string hexRed = HexEncDec::encodeInt(Integer::parseInt(redInput->getController()->getValue().getString()));
	string hexGreen = HexEncDec::encodeInt(Integer::parseInt(greenInput->getController()->getValue().getString()));
	string hexBlue = HexEncDec::encodeInt(Integer::parseInt(blueInput->getController()->getValue().getString()));
	string hexAlpha = HexEncDec::encodeInt(Integer::parseInt(alphaInput->getController()->getValue().getString()));
	while (hexRed.size() < 2) hexRed = "0" + hexRed;
	while (hexGreen.size() < 2) hexGreen = "0" + hexGreen;
	while (hexBlue.size() < 2) hexBlue = "0" + hexBlue;
	while (hexAlpha.size() < 2) hexAlpha = "0" + hexAlpha;
	hexInput->getController()->setValue(MutableString("#" + hexRed + hexGreen + hexBlue + (hexAlpha == "ff"?"":hexAlpha)));
}
