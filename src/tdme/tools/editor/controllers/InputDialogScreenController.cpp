#include <tdme/tools/editor/controllers/InputDialogScreenController.h>

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>

using std::remove;
using std::string;
using std::unordered_map;
using std::vector;

using tdme::tools::editor::controllers::InputDialogScreenController;

using tdme::engine::Engine;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;

InputDialogScreenController::InputDialogScreenController(PopUps* popUps)
{
	this->popUps = popUps;
}

InputDialogScreenController::~InputDialogScreenController() {
	if (applyAction != nullptr) delete applyAction;
	if (cancelAction != nullptr) delete cancelAction;
}

GUIScreenNode* InputDialogScreenController::getScreenNode()
{
	return screenNode;
}

const string InputDialogScreenController::getInputText()
{
	return inputNode->getController()->getValue().getString();
}

void InputDialogScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_inputdialog.xml");
		screenNode->setVisible(false);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenNode->addFocusListener(this);
		screenNode->addTooltipRequestListener(this);
		tabsHeaderNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("inputdialog_tabs-header"));
		inputNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("inputdialog_inputtext"));
	} catch (Exception& exception) {
		Console::print(string("InputDialogScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void InputDialogScreenController::dispose()
{
	screenNode = nullptr;
}


void InputDialogScreenController::show(const string& captionText, const string& inputText, Action* applyAction, Action* cancelAction)
{
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(tabsHeaderNode->getId()))->replaceSubNodes("<tab id=\"inputdialog_caption\" image=\"resources/engine/images/attention.png\" text=\"" + GUIParser::escapeQuotes(captionText)+ "\" closeable=\"true\"/>", true);
	this->inputNode->getController()->setValue(inputText);
	if (this->applyAction != nullptr) delete this->applyAction;
	this->applyAction = applyAction;
	if (this->cancelAction != nullptr) delete this->cancelAction;
	this->cancelAction = cancelAction;
	//
	screenNode->setVisible(true);
	Engine::getInstance()->getGUI()->setFoccussedNode(inputNode);
}

void InputDialogScreenController::close()
{
	screenNode->setVisible(false);
	if (applyAction != nullptr) delete applyAction;
	if (cancelAction != nullptr) delete cancelAction;
	applyAction = nullptr;
	cancelAction = nullptr;
}

void InputDialogScreenController::onChange(GUIElementNode* node)
{
}

void InputDialogScreenController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == "inputdialog_apply") {
			if (applyAction != nullptr) {
				applyAction->performAction();
				delete applyAction;
				applyAction = nullptr;
			}
		} else
		if (node->getId() == "inputdialog_abort" ||
			StringTools::startsWith(node->getId(), "filedialog_caption_close_") == true) { // TODO: a.drewke, check with DH
			if (cancelAction != nullptr) {
				cancelAction->performAction();
				delete cancelAction;
				cancelAction = nullptr;
			}
			close();
		}
	}
}

void InputDialogScreenController::onFocus(GUIElementNode* node) {
	GUI::setDisableTabFocusControl(node->getScreenNode() != screenNode);
}

void InputDialogScreenController::onUnfocus(GUIElementNode* node) {
}

void InputDialogScreenController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	popUps->getTooltipScreenController()->show(mouseX, mouseY, node->getToolTip());
}

void InputDialogScreenController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}
