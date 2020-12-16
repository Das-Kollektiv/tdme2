#include <tdme/tools/shared/controller/PrototypeBaseSubScreenController.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/ScenePropertyPresets.h>
#include <tdme/engine/prototype/PrototypeProperty.h>
#include <tdme/tools/shared/views/EntityBaseView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>

using std::map;
using std::vector;
using std::string;

using tdme::tools::shared::controller::PrototypeBaseSubScreenController;
using tdme::gui::GUIParser;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::ScenePropertyPresets;
using tdme::engine::prototype::PrototypeProperty;
using tdme::tools::shared::views::EntityBaseView;
using tdme::tools::shared::views::PopUps;
using tdme::utilities::MutableString;
using tdme::utilities::Console;
using tdme::utilities::Exception;

MutableString PrototypeBaseSubScreenController::TEXT_EMPTY = MutableString("");

PrototypeBaseSubScreenController::PrototypeBaseSubScreenController(PopUps* popUps, Action* onSetEntityDataAction)
{
	this->view = new EntityBaseView(this);
	this->popUps = popUps;
	this->onSetEntityDataAction = onSetEntityDataAction;
}

PrototypeBaseSubScreenController::~PrototypeBaseSubScreenController() {
	delete view;
	delete onSetEntityDataAction;
}

void PrototypeBaseSubScreenController::initialize(GUIScreenNode* screenNode)
{
	try {
		entityName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("entity_name"));
		entityDescription = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("entity_description"));
		entityApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_entity_apply"));
		entityPropertyName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("entity_property_name"));
		entityPropertyValue = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("entity_property_value"));
		entityPropertySave = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_entity_properties_save"));
		entityPropertyAdd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_entity_properties_add"));
		entityPropertyRemove = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_entity_properties_remove"));
		entityPropertiesList = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("entity_properties_listbox"));
		entityPropertyPresetApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_entity_properties_presetapply"));
		entityPropertiesPresets = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("entity_properties_presets"));
	} catch (Exception& exception) {
		Console::print(string("PrototypeBaseSubScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	setEntityPresetIds(ScenePropertyPresets::getInstance()->getEntityPropertiesPresets());
}

void PrototypeBaseSubScreenController::setEntityData(const string& name, const string& description)
{
	entityName->getController()->setDisabled(false);
	entityName->getController()->setValue(name);
	entityDescription->getController()->setDisabled(false);
	entityDescription->getController()->setValue(description);
	entityApply->getController()->setDisabled(false);
}

void PrototypeBaseSubScreenController::unsetEntityData()
{
	entityName->getController()->setValue(TEXT_EMPTY);
	entityName->getController()->setDisabled(true);
	entityDescription->getController()->setValue(TEXT_EMPTY);
	entityDescription->getController()->setDisabled(true);
	entityApply->getController()->setDisabled(true);
}

void PrototypeBaseSubScreenController::onEntityDataApply(Prototype* model)
{
	if (model == nullptr)
		return;

	view->setEntityData(model, entityName->getController()->getValue().getString(), entityDescription->getController()->getValue().getString());
	onSetEntityDataAction->performAction();
}

void PrototypeBaseSubScreenController::setEntityPresetIds(const map<string, vector<PrototypeProperty*>>& entityPresetIds)
{
	auto entityPropertiesPresetsInnerNode = dynamic_cast< GUIParentNode* >((entityPropertiesPresets->getScreenNode()->getNodeById(entityPropertiesPresets->getId() + "_inner")));
	auto idx = 0;
	string entityPropertiesPresetsInnerNodeSubNodesXML = "";
	entityPropertiesPresetsInnerNodeSubNodesXML =
		entityPropertiesPresetsInnerNodeSubNodesXML +
		"<scrollarea-vertical id=\"" +
		entityPropertiesPresets->getId() +
		"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
	for (auto it: entityPresetIds) {
		auto entityPresetId = it.first;
		entityPropertiesPresetsInnerNodeSubNodesXML =
			entityPropertiesPresetsInnerNodeSubNodesXML + "<dropdown-option text=\"" +
			GUIParser::escapeQuotes(entityPresetId) +
			"\" value=\"" +
			GUIParser::escapeQuotes(entityPresetId) +
			"\" " +
			(idx == 0 ? "selected=\"true\" " : "") +
			" />\n";
		idx++;
	}
	entityPropertiesPresetsInnerNodeSubNodesXML = entityPropertiesPresetsInnerNodeSubNodesXML + "</scrollarea-vertical>";
	try {
		entityPropertiesPresetsInnerNode->replaceSubNodes(entityPropertiesPresetsInnerNodeSubNodesXML, true);
	} catch (Exception& exception) {
		Console::print(string("PrototypeBaseSubScreenController::setEntityPresetIds(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void PrototypeBaseSubScreenController::setEntityProperties(Prototype* entity, const string& presetId, const string& selectedName)
{
	entityPropertiesPresets->getController()->setDisabled(false);
	entityPropertyPresetApply->getController()->setDisabled(false);
	entityPropertiesList->getController()->setDisabled(false);
	entityPropertyAdd->getController()->setDisabled(false);
	entityPropertyRemove->getController()->setDisabled(false);
	entityPropertySave->getController()->setDisabled(true);
	entityPropertyName->getController()->setDisabled(true);
	entityPropertyValue->getController()->setDisabled(true);
	entityPropertiesPresets->getController()->setValue(presetId.length() > 0 ? MutableString(presetId) : MutableString("none"));
	auto entityPropertiesListBoxInnerNode = dynamic_cast< GUIParentNode* >((entityPropertiesList->getScreenNode()->getNodeById(entityPropertiesList->getId() + "_inner")));
	auto idx = 1;
	string entityPropertiesListBoxSubNodesXML = "";
	entityPropertiesListBoxSubNodesXML =
		entityPropertiesListBoxSubNodesXML +
		"<scrollarea-vertical id=\"" +
		entityPropertiesList->getId() +
		"_inner_scrollarea\" width=\"100%\" height=\"100%\">\n";
	for (auto i = 0; i < entity->getPropertyCount(); i++) {
		PrototypeProperty* entityProperty = entity->getPropertyByIndex(i);
		entityPropertiesListBoxSubNodesXML =
			entityPropertiesListBoxSubNodesXML +
			"<selectbox-option text=\"" +
			GUIParser::escapeQuotes(entityProperty->getName()) +
			": " +
			GUIParser::escapeQuotes(entityProperty->getValue()) +
			"\" value=\"" +
			GUIParser::escapeQuotes(entityProperty->getName()) +
			"\" " +
			(selectedName.length() > 0 && entityProperty->getName() == selectedName ? "selected=\"true\" " : "") +
			"/>\n";
	}
	entityPropertiesListBoxSubNodesXML = entityPropertiesListBoxSubNodesXML + "</scrollarea-vertical>\n";
	try {
		entityPropertiesListBoxInnerNode->replaceSubNodes(entityPropertiesListBoxSubNodesXML, false);
	} catch (Exception& exception) {
		Console::print(string("PrototypeBaseSubScreenController::setEntityProperties(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	onEntityPropertiesSelectionChanged(entity);
}

void PrototypeBaseSubScreenController::unsetEntityProperties()
{
	auto modelPropertiesListBoxInnerNode = dynamic_cast< GUIParentNode* >((entityPropertiesList->getScreenNode()->getNodeById(entityPropertiesList->getId() + "_inner")));
	modelPropertiesListBoxInnerNode->clearSubNodes();
	entityPropertiesPresets->getController()->setValue(MutableString("none"));
	entityPropertiesPresets->getController()->setDisabled(true);
	entityPropertyPresetApply->getController()->setDisabled(true);
	entityPropertiesList->getController()->setDisabled(true);
	entityPropertyAdd->getController()->setDisabled(true);
	entityPropertyRemove->getController()->setDisabled(true);
	entityPropertySave->getController()->setDisabled(true);
	entityPropertyName->getController()->setValue(TEXT_EMPTY);
	entityPropertyName->getController()->setDisabled(true);
	entityPropertyValue->getController()->setValue(TEXT_EMPTY);
	entityPropertyValue->getController()->setDisabled(true);
}

void PrototypeBaseSubScreenController::onEntityPropertySave(Prototype* entity)
{
	if (view->entityPropertySave(
		entity,
		entityPropertiesList->getController()->getValue().getString(),
		entityPropertyName->getController()->getValue().getString(),
		entityPropertyValue->getController()->getValue().getString()) == false) {
		showErrorPopUp("Warning", "Saving entity property failed");
	}
}

void PrototypeBaseSubScreenController::onEntityPropertyAdd(Prototype* entity)
{
	if (view->entityPropertyAdd(entity) == false) {
		showErrorPopUp("Warning", "Adding new entity property failed");
	}
}

void PrototypeBaseSubScreenController::onEntityPropertyRemove(Prototype* entity)
{
	if (view->entityPropertyRemove(entity, entityPropertiesList->getController()->getValue().getString()) == false) {
		showErrorPopUp("Warning", "Removing entity property failed");
	}
}

void PrototypeBaseSubScreenController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void PrototypeBaseSubScreenController::onEntityPropertyPresetApply(Prototype* model)
{
	view->entityPropertiesPreset(model, entityPropertiesPresets->getController()->getValue().getString());
}

void PrototypeBaseSubScreenController::onEntityPropertiesSelectionChanged(Prototype* entity)
{
	entityPropertyName->getController()->setDisabled(true);
	entityPropertyName->getController()->setValue(TEXT_EMPTY);
	entityPropertyValue->getController()->setDisabled(true);
	entityPropertyValue->getController()->setValue(TEXT_EMPTY);
	entityPropertySave->getController()->setDisabled(true);
	entityPropertyRemove->getController()->setDisabled(true);
	auto entityProperty = entity->getProperty(entityPropertiesList->getController()->getValue().getString());
	if (entityProperty != nullptr) {
		entityPropertyName->getController()->setValue(MutableString(entityProperty->getName()));
		entityPropertyValue->getController()->setValue(MutableString(entityProperty->getValue()));
		entityPropertyName->getController()->setDisabled(false);
		entityPropertyValue->getController()->setDisabled(false);
		entityPropertySave->getController()->setDisabled(false);
		entityPropertyRemove->getController()->setDisabled(false);
	}
}

void PrototypeBaseSubScreenController::onValueChanged(GUIElementNode* node, Prototype* model)
{
	if (node == entityPropertiesList) {
		onEntityPropertiesSelectionChanged(model);
	} else {
	}
}

void PrototypeBaseSubScreenController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node, Prototype* entity)
{
	if (type == GUIActionListenerType::PERFORMED)
	{
		if (node->getId().compare("button_entity_apply") == 0) {
			onEntityDataApply(entity);
		} else
		if (node->getId().compare("button_entity_properties_presetapply") == 0) {
			onEntityPropertyPresetApply(entity);
		} else
		if (node->getId().compare("button_entity_properties_add") == 0) {
			onEntityPropertyAdd(entity);
		} else
		if (node->getId().compare("button_entity_properties_remove") == 0) {
			onEntityPropertyRemove(entity);
		} else
		if (node->getId().compare("button_entity_properties_save") == 0) {
			onEntityPropertySave(entity);
		}
	}
}
