#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeScriptSubController.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Engine.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUIImageNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
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
#include <agui/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>


using std::map;
using std::string;
using std::vector;

using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIImageNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUIParser;
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
using agui::utilities::MutableString;
using tdme::utilities::StringTools;

PrototypeScriptSubController::PrototypeScriptSubController(EditorView* editorView)
{
	this->editorView = editorView;
	this->view = make_unique<PrototypeScriptSubView>(this);
	this->popUps = editorView->getPopUps();
}

PrototypeScriptSubController::~PrototypeScriptSubController() {
}

void PrototypeScriptSubController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void PrototypeScriptSubController::createScriptXML(Prototype* prototype, string& xml) {
	xml+= "<selectbox-option image=\"resources/engine/images/script.png\" text=\"" + GUIParser::escape("Script") + "\" value=\"" + GUIParser::escape("script") + "\" />\n";
}

void PrototypeScriptSubController::setScriptDetails(Prototype* prototype) {
	editorView->setDetailsContent(
		"<template id=\"details_script\" src=\"resources/engine/gui/template_details_script.xml\" />\n"
	);
	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_script"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::printLine("PrototypeScriptSubController::setScriptDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
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
		Console::printLine("PrototypeScriptSubController::updateScriptDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void PrototypeScriptSubController::updateDetails(Prototype* prototype, const string& outlinerNode) {
	if (outlinerNode == "script") {
		setScriptDetails(prototype);
	}
}

bool PrototypeScriptSubController::onChange(GUIElementNode* node, Prototype* prototype)
{
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (outlinerNode == "script") {
			setScriptDetails(prototype);
			return true;
		}
	} else
	if (node->getId() == "script_hid") {
		prototype->setScriptHandlingHID(node->getController()->getValue().equals("1"));
		return true;
	}
	//
	return false;
}

bool PrototypeScriptSubController::onAction(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype)
{
	if (type != GUIActionListenerType::PERFORMED) return false;
	//
	if (node->getId() == "script_open") {
		onScriptSet(prototype);
		return true;
	} else
	if (node->getId() == "script_remove") {
		onScriptUnset(prototype);
		return true;
	} else
	if (node->getId() == "script_browseto") {
		onScriptBrowseTo(prototype);
		return true;
	}
	//
	return false;
}

void PrototypeScriptSubController::onScriptSet(Prototype* prototype) {
	class OnSetScript: public virtual Action
	{
	public:
		void performAction() override {
			prototypeScriptSubController->setScript(
				prototypeScriptSubController->popUps->getFileDialogScreenController()->getPathName() +
				"/" +
				prototypeScriptSubController->popUps->getFileDialogScreenController()->getFileName(),
				prototype
			);
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

void PrototypeScriptSubController::onScriptBrowseTo(Prototype* prototype) {
	if (prototype->getScript().empty() == true) {
		showInfoPopUp("Browse To", "Nothing to browse to");
	} else {
		editorView->getScreenController()->browseTo(prototype->getScript());
	}
}

void PrototypeScriptSubController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void PrototypeScriptSubController::setScript(const string& fileName, Prototype* prototype) {
	prototype->setScript(fileName);
	updateScriptDetails(prototype);
}

bool PrototypeScriptSubController::onDrop(const string& payload, int mouseX, int mouseY, Prototype* prototype) {
	if (StringTools::startsWith(payload, "file:") == false) {
		return false;
	} else {
		auto fileName = StringTools::substring(payload, string("file:").size());
		if (editorView->getScreenController()->isDropOnNode(mouseX, mouseY, "script") == true) {
			if (Tools::hasFileExtension(fileName, {{ "tscript" }}) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions({{ "tscript" }}));
			} else {
				setScript(fileName, prototype);
			}
			return true;
		} else {
			return false;
		}
	}
}
