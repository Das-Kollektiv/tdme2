#include <tdme/tools/editor/controllers/FindReplaceDialogScreenController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Version.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::tools::editor::controllers::FindReplaceDialogScreenController;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::engine::Version;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

FindReplaceDialogScreenController::FindReplaceDialogScreenController(PopUps* popUps): popUps(popUps)
{
}

FindReplaceDialogScreenController::~FindReplaceDialogScreenController()
{
	screenNode = nullptr;
	if (findAction != nullptr) delete findAction;
	if (countAction != nullptr) delete countAction;
	if (replaceAction != nullptr) delete replaceAction;
	if (replaceAllAction != nullptr) delete replaceAllAction;
	if (completeAction != nullptr) delete completeAction;
}

GUIScreenNode* FindReplaceDialogScreenController::getScreenNode()
{
	return screenNode;
}

void FindReplaceDialogScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_findreplace.xml");
		screenNode->setVisible(false);
		screenNode->addActionListener(this);
		screenNode->addFocusListener(this);
		screenNode->addTooltipRequestListener(this);
		findText = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_findtext"));
		replaceText = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_replacetext"));
		matchCase = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_matchcase"));
		wholeWordOnly = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_wholewordonly"));
		inSelectionOnly = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_inselectiononly"));
		findButton = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_find"));
		countButton = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_count"));
		cancelButton = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_cancel"));
		replaceButton = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_replace"));
		replaceAllButton = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_replaceall"));
	} catch (Exception& exception) {
		Console::print(string("FindReplaceDialogScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void FindReplaceDialogScreenController::dispose()
{
}

const string FindReplaceDialogScreenController::getFindText() {
	return findText->getController()->getValue().getString();
}

const string FindReplaceDialogScreenController::getReplaceText() {
	return replaceText->getController()->getValue().getString();
}

bool FindReplaceDialogScreenController::isMatchCase() {
	return matchCase->getController()->getValue().equals("1");
}

bool FindReplaceDialogScreenController::isWholeWordOnly() {
	return wholeWordOnly->getController()->getValue().equals("1");
}

bool FindReplaceDialogScreenController::isInSelectionOnly() {
	return inSelectionOnly->getController()->getValue().equals("1");
}

void FindReplaceDialogScreenController::show(Action* findAction, Action* countAction, Action* replaceAction, Action* replaceAllAction, Action* completeAction)
{
	this->findAction = findAction;
	this->countAction = countAction;
	this->replaceAction = replaceAction;
	this->replaceAllAction = replaceAllAction;
	this->completeAction = completeAction;
	//
	screenNode->setVisible(true);
}

void FindReplaceDialogScreenController::close()
{
	screenNode->setVisible(false);
	if (findAction != nullptr) delete findAction;
	if (countAction != nullptr) delete countAction;
	if (replaceAction != nullptr) delete replaceAction;
	if (replaceAllAction != nullptr) delete replaceAllAction;
	if (completeAction != nullptr) delete completeAction;
	findAction = nullptr;
	countAction = nullptr;
	replaceAction = nullptr;
	replaceAllAction = nullptr;
	completeAction = nullptr;
}

void FindReplaceDialogScreenController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (StringTools::startsWith(node->getId(), "findreplace_caption_close_") == true) { // TODO: a.drewke, check with DH) {
			if (completeAction != nullptr) completeAction->performAction();
		} else
		if (node->getId() == findButton->getId()) {
			if (findAction != nullptr) findAction->performAction();
		} else
		if (node->getId() == countButton->getId()) {
			if (countAction != nullptr) countAction->performAction();
		} else
		if (node->getId() == replaceButton->getId()) {
			if (replaceAction != nullptr) replaceAction->performAction();
		} else
		if (node->getId() == replaceAllButton->getId()) {
			if (replaceAllAction != nullptr) replaceAllAction->performAction();
		} else
		if (node->getId() == cancelButton->getId()) {
			if (completeAction != nullptr) completeAction->performAction();
		}
	}
}

void FindReplaceDialogScreenController::onFocus(GUIElementNode* node) {
	GUI::setDisableTabFocusControl(node->getScreenNode() != screenNode);
}

void FindReplaceDialogScreenController::onUnfocus(GUIElementNode* node) {
}

void FindReplaceDialogScreenController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	popUps->getTooltipScreenController()->show(mouseX, mouseY, node->getToolTip());
}

void FindReplaceDialogScreenController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}
