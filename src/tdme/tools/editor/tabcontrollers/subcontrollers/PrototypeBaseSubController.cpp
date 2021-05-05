#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeBaseSubController.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeProperty.h>
#include <tdme/engine/scene/ScenePropertyPresets.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/events/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeBaseSubView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeProperty;
using tdme::engine::scene::ScenePropertyPresets;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUIParser;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeBaseSubController;
using tdme::tools::editor::tabviews::subviews::PrototypeBaseSubView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

PrototypeBaseSubController::PrototypeBaseSubController(EditorView* editorView, PopUps* popUps, Action* onSetEntityDataAction)
{
	this->editorView = editorView;
	this->view = new PrototypeBaseSubView(this);
	this->popUps = popUps;
	this->onSetPrototypeDataAction = onSetEntityDataAction;
}

PrototypeBaseSubController::~PrototypeBaseSubController() {
	delete view;
	delete onSetPrototypeDataAction;
}

void PrototypeBaseSubController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	// TODO: a.drewke
	// setPrototypePresetIds(ScenePropertyPresets::getInstance()->getEntityPropertiesPresets());
}

void PrototypeBaseSubController::setPrototypeData(const string& name, const string& description)
{
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("entity_name"))->getController()->setDisabled(false);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("entity_name"))->getController()->setValue(name);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("entity_description"))->getController()->setDisabled(false);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("entity_description"))->getController()->setValue(description);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("button_entity_apply"))->getController()->setDisabled(false);
}

void PrototypeBaseSubController::unsetPrototypeData()
{
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("entity_name"))->getController()->setValue(MutableString());
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("entity_name"))->getController()->setDisabled(true);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("entity_description"))->getController()->setValue(MutableString());
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("entity_description"))->getController()->setDisabled(true);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("button_entity_apply"))->getController()->setDisabled(true);
}

void PrototypeBaseSubController::onPrototypeDataApply(Prototype* prototype)
{
	if (prototype == nullptr)
		return;

	view->setPrototypeData(prototype, required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("entity_name"))->getController()->getValue().getString(), required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("entity_description"))->getController()->getValue().getString());
	onSetPrototypeDataAction->performAction();
}

void PrototypeBaseSubController::createPrototypePropertiesXML(Prototype* prototype, string& xml) {
	if (prototype->getPropertyCount() > 0) {
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Properties") + "\" value=\"" + GUIParser::escapeQuotes("properties") + "\">\n";
		for (auto i = 0; i < prototype->getPropertyCount(); i++) {
			auto property = prototype->getPropertyByIndex(i);
			xml+= "	<selectbox-option text=\"" + GUIParser::escapeQuotes(property->getName() + ": " + property->getValue()) + "\" value=\"" + GUIParser::escapeQuotes("properties." + property->getName()) + "\" />\n";
		}
		xml+= "</selectbox-parent-option>\n";
	}
}

void PrototypeBaseSubController::setPropertyDetails(Prototype* prototype, const string& propertyName) {
	Console::println("PrototypeBaseSubController::setPropertyDetails(): " + propertyName);

	auto property = prototype->getProperty(propertyName);
	if (property == nullptr) return;

	editorView->setDetailsContent(
		"<template id=\"details_property\" src=\"resources/engine/gui/template_details_property.xml\" />\n"
	);

	auto screenNode = editorView->getScreenController()->getScreenNode();

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_property"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("property_name"))->getController()->setValue(MutableString(property->getName()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("property_value"))->getController()->setValue(MutableString(property->getValue()));
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::setPropertyDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypeBaseSubController::applyPropertyDetails(Prototype* prototype, const string& propertyName) {
	Console::println("PrototypeBaseSubController::applyPropertyDetails(): " + propertyName);

	try {
		if (prototype->updateProperty(
			propertyName,
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("property_name"))->getController()->getValue().getString(),
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("property_value"))->getController()->getValue().getString()) == false) {
			throw ExceptionBase("Could not apply property details");
		}
	} catch (Exception& exception) {
		Console::println(string("PrototypeBaseSubController::applyPropertyDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypeBaseSubController::onValueChanged(GUIElementNode* node, Prototype* prototype)
{
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "properties.") == true) {
			auto selectedPropertyName = StringTools::substring(outlinerNode, string("properties.").size(), outlinerNode.size());
			setPropertyDetails(prototype, selectedPropertyName);
		}
	}
}

void PrototypeBaseSubController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype)
{
}

void PrototypeBaseSubController::onFocus(GUIElementNode* node, Prototype* prototype) {
	auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
	for (auto& applyPropertyNode: applyPropertyNodes)
	if (node->getId() == applyPropertyNode) {
		propertyName = StringTools::substring(outlinerNode, string("properties.").size(), outlinerNode.size());
	}
}

void PrototypeBaseSubController::onUnfocus(GUIElementNode* node, Prototype* prototype) {
	if (propertyName.empty() == true) return;
	applyPropertyDetails(prototype, propertyName);
	propertyName.clear();
	editorView->reloadTabOutliner();
}

void PrototypeBaseSubController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}
