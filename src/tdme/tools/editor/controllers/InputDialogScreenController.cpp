#include <tdme/tools/editor/controllers/InputDialogScreenController.h>

#include <memory>
#include <string>

#include <agui/agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/events/GUITooltipRequestListener.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::unique_ptr;

using tdme::tools::editor::controllers::InputDialogScreenController;

using agui::gui::events::GUIActionListener;
using agui::gui::events::GUIActionListenerType;
using agui::gui::events::GUITooltipRequestListener;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::gui::GUIParser;

using tdme::engine::Engine;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;

InputDialogScreenController::InputDialogScreenController(PopUps* popUps)
{
	this->popUps = popUps;
}

InputDialogScreenController::~InputDialogScreenController() {
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
		screenNode->setEnabled(false);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenNode->addFocusListener(this);
		screenNode->addTooltipRequestListener(this);
		tabsHeaderNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("inputdialog_tabs-header"));
		inputNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("inputdialog_inputtext"));
	} catch (Exception& exception) {
		Console::printLine("InputDialogScreenController::initialize(): An error occurred: " + string(exception.what()));
	}
}

void InputDialogScreenController::dispose()
{
	screenNode = nullptr;
}


void InputDialogScreenController::show(const string& captionText, const string& inputText, Action* applyAction, Action* cancelAction)
{
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(tabsHeaderNode->getId()))->replaceSubNodes("<tab id=\"inputdialog_caption\" image=\"resources/engine/images/attention.png\" text=\"" + GUIParser::escape(captionText)+ "\" closeable=\"true\"/>", true);
	this->inputNode->getController()->setValue(inputText);
	this->applyAction = unique_ptr<Action>(applyAction);
	this->cancelAction = unique_ptr<Action>(cancelAction);
	//
	screenNode->setEnabled(true);
	Engine::getInstance()->getGUI()->setFoccussedNode(inputNode);
}

void InputDialogScreenController::close()
{
	screenNode->setEnabled(false);
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
			if (applyAction != nullptr) applyAction->performAction();
			applyAction = nullptr;
			cancelAction = nullptr;
		} else
		if (node->getId() == "inputdialog_cancel" ||
			StringTools::startsWith(node->getId(), "inputdialog_caption_close_") == true) { // TODO: a.drewke, check with DH
			if (cancelAction != nullptr) cancelAction->performAction();
			applyAction = nullptr;
			cancelAction = nullptr;
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
