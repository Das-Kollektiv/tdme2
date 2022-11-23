#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeScriptSubController.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeScriptSubView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>


using std::map;
using std::string;
using std::vector;

using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUIParser;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeScriptSubController;
using tdme::tools::editor::tabviews::subviews::PrototypeScriptSubView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

PrototypeScriptSubController::PrototypeScriptSubController(EditorView* editorView)
{
	this->editorView = editorView;
	this->view = new PrototypeScriptSubView(this);
	this->popUps = editorView->getPopUps();
}

PrototypeScriptSubController::~PrototypeScriptSubController() {
	delete view;
}

void PrototypeScriptSubController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void PrototypeScriptSubController::createScriptXML(Prototype* prototype, string& xml) {
	xml+= "<selectbox-option image=\"resources/engine/images/script.png\" text=\"" + GUIParser::escapeQuotes("Script") + "\" value=\"" + GUIParser::escapeQuotes("script") + "\" />\n";
}

void PrototypeScriptSubController::setScriptDetails(Prototype* prototype) {
	editorView->setDetailsContent(
		"<template id=\"details_script\" src=\"resources/engine/gui/template_details_script.xml\" />\n"
	);
	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_script"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::println(string("PrototypeScriptSubController::setScriptDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
	//
	updateScriptDetails(prototype);
}

void PrototypeScriptSubController::updateScriptDetails(Prototype* prototype) {
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("script_hid"))->getController()->setValue(MutableString(prototype->isScriptHandlingHID() == true?"1":""));
		if (prototype->getScript().empty() == true) {
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("script"))->setSource(string());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("script"))->setTooltip(string());
		} else {
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("script"))->setSource("resources/engine/images/script_big.png");
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("script"))->setTooltip(prototype->getScript());
		}
	} catch (Exception& exception) {
		Console::println(string("PrototypeScriptSubController::updateScriptDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypeScriptSubController::updateDetails(Prototype* prototype, const string& outlinerNode) {
	if (outlinerNode == "script") {
		setScriptDetails(prototype);
	}
}

void PrototypeScriptSubController::onChange(GUIElementNode* node, Prototype* prototype)
{
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (outlinerNode == "script") setScriptDetails(prototype);
	} else
	if (node->getId() == "script_hid") {
		prototype->setScriptHandlingHID(node->getController()->getValue().equals("1"));
	}
}

void PrototypeScriptSubController::onAction(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype)
{
	if (type != GUIActionListenerType::PERFORMED) return;
	Console::println("PrototypeScriptSubController::onAction(): " + node->getId());
	if (node->getId() == "script_open") {
		onScriptSet(prototype);
	} else
	if (node->getId() == "script_remove") {
		onScriptUnset(prototype);
	} else
	if (node->getId() == "script_browseto") {
		// TODO
	}
}

void PrototypeScriptSubController::onScriptSet(Prototype* prototype) {
	class OnSetScript: public virtual Action
	{
	public:
		void performAction() override {
			string scriptFileName =
				prototypeScriptSubController->popUps->getFileDialogScreenController()->getPathName() +
				"/" +
				prototypeScriptSubController->popUps->getFileDialogScreenController()->getFileName();
			prototype->setScript(scriptFileName);
			prototypeScriptSubController->updateScriptDetails(prototype);
			prototypeScriptSubController->popUps->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param prototypeScriptSubController prototype script sub controller
		 * @param screenIdx screen index
		 */
		OnSetScript(PrototypeScriptSubController* prototypeScriptSubController, Prototype* prototype)
			: prototypeScriptSubController(prototypeScriptSubController), prototype(prototype) {
		}

	private:
		PrototypeScriptSubController* prototypeScriptSubController;
		Prototype* prototype;
	};

	auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
	auto pathName = prototype->getScript().empty() == true?Tools::getPathName(screenNode->getFileName()):string();
	auto fileName = prototype->getScript().empty() == true?Tools::getFileName(screenNode->getFileName()):string();
	popUps->getFileDialogScreenController()->show(
		pathName,
		"Load script from: ",
		{ { "tscript" } },
		fileName,
		true,
		new OnSetScript(this, prototype)
	);
}

void PrototypeScriptSubController::onScriptUnset(Prototype* prototype) {
	prototype->setScript(string());
	updateScriptDetails(prototype);
}

void PrototypeScriptSubController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}
