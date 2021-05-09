#include <tdme/tools/editor/controllers/ColorPickerScreenController.h>

#include <string>

#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIMultilineTextNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::utilities::Console;
using tdme::utilities::Exception;
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

void ColorPickerScreenController::show()
{
	screenNode->setVisible(true);
}

void ColorPickerScreenController::close()
{
	screenNode->setVisible(false);
}

void ColorPickerScreenController::onValueChanged(GUIElementNode* node) {
	Console::println("ColorPickerScreenController::onValueChanged(): " + node->getId());
	if (node->getId() == "colorpicker_red") {

	} else
	if (node->getId() == "colorpicker_green") {

	} else
	if (node->getId() == "colorpicker_blue") {

	} else
	if (node->getId() == "colorpicker_alpha") {

	} else
	if (node->getId() == "colorpicker_hex") {

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

