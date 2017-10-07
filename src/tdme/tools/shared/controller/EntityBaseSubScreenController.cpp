#include <tdme/tools/shared/controller/EntityBaseSubScreenController.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/Action.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelPropertyPresets.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/tools/shared/views/EntityBaseView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/MutableString.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::gui::GUIParser;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelPropertyPresets;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::tools::shared::views::EntityBaseView;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;
using tdme::utils::Console;
using tdme::utils::Exception;

MutableString* EntityBaseSubScreenController::TEXT_EMPTY = new MutableString(L"");

EntityBaseSubScreenController::EntityBaseSubScreenController(PopUps* popUps, Action* onSetEntityDataAction) 
{
	this->view = new EntityBaseView(this);
	this->popUps = popUps;
	this->onSetEntityDataAction = onSetEntityDataAction;
	value = new MutableString();
}

void EntityBaseSubScreenController::initialize(GUIScreenNode* screenNode)
{
	try {
		entityName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"entity_name"));
		entityDescription = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"entity_description"));
		entityApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"button_entity_apply"));
		entityPropertyName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"entity_property_name"));
		entityPropertyValue = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"entity_property_value"));
		entityPropertySave = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"button_entity_properties_save"));
		entityPropertyAdd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"button_entity_properties_add"));
		entityPropertyRemove = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"button_entity_properties_remove"));
		entityPropertiesList = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"entity_properties_listbox"));
		entityPropertyPresetApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"button_entity_properties_presetapply"));
		entityPropertiesPresets = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"entity_properties_presets"));
	} catch (Exception& exception) {
		Console::print(string("EntityBaseSubScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	setEntityPresetIds(LevelPropertyPresets::getInstance()->getObjectPropertiesPresets());
}

void EntityBaseSubScreenController::setEntityData(const wstring& name, const wstring& description)
{
	entityName->getController()->setDisabled(false);
	entityName->getController()->getValue()->set(name);
	entityDescription->getController()->setDisabled(false);
	entityDescription->getController()->getValue()->set(description);
	entityApply->getController()->setDisabled(false);
}

void EntityBaseSubScreenController::unsetEntityData()
{
	entityName->getController()->setValue(TEXT_EMPTY);
	entityName->getController()->setDisabled(true);
	entityDescription->getController()->setValue(TEXT_EMPTY);
	entityDescription->getController()->setDisabled(true);
	entityApply->getController()->setDisabled(true);
}

void EntityBaseSubScreenController::onEntityDataApply(LevelEditorEntity* model)
{
	if (model == nullptr)
		return;

	view->setEntityData(model, entityName->getController()->getValue()->toWString(), entityDescription->getController()->getValue()->toWString());
	onSetEntityDataAction->performAction();
}

void EntityBaseSubScreenController::setEntityPresetIds(const map<wstring, vector<PropertyModelClass*>>* entityPresetIds)
{
	auto entityPropertiesPresetsInnerNode = dynamic_cast< GUIParentNode* >((entityPropertiesPresets->getScreenNode()->getNodeById(entityPropertiesPresets->getId() + L"_inner")));
	auto idx = 0;
	wstring entityPropertiesPresetsInnerNodeSubNodesXML = L"";
	entityPropertiesPresetsInnerNodeSubNodesXML =
		entityPropertiesPresetsInnerNodeSubNodesXML +
		L"<scrollarea-vertical id=\"" +
		entityPropertiesPresets->getId() +
		L"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
	for (auto it: *entityPresetIds) {
		auto entityPresetId = it.first;
		entityPropertiesPresetsInnerNodeSubNodesXML =
			entityPropertiesPresetsInnerNodeSubNodesXML + L"<dropdown-option text=\"" +
			GUIParser::escapeQuotes(entityPresetId) +
			L"\" value=\"" +
			GUIParser::escapeQuotes(entityPresetId) +
			L"\" " +
			(idx == 0 ? L"selected=\"true\" " : L"") +
			L" />\n";
		idx++;
	}
	entityPropertiesPresetsInnerNodeSubNodesXML = entityPropertiesPresetsInnerNodeSubNodesXML + L"</scrollarea-vertical>";
	try {
		entityPropertiesPresetsInnerNode->replaceSubNodes(entityPropertiesPresetsInnerNodeSubNodesXML, true);
	} catch (Exception& exception) {
		Console::print(string("EntityBaseSubScreenController::setEntityPresetIds(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void EntityBaseSubScreenController::setEntityProperties(LevelEditorEntity* entity, const wstring& presetId, const wstring& selectedName)
{
	entityPropertiesPresets->getController()->setDisabled(false);
	entityPropertyPresetApply->getController()->setDisabled(false);
	entityPropertiesList->getController()->setDisabled(false);
	entityPropertyAdd->getController()->setDisabled(false);
	entityPropertyRemove->getController()->setDisabled(false);
	entityPropertySave->getController()->setDisabled(true);
	entityPropertyName->getController()->setDisabled(true);
	entityPropertyValue->getController()->setDisabled(true);
	entityPropertiesPresets->getController()->setValue(presetId.length() > 0 ? value->set(presetId) : value->set(L"none"));
	auto entityPropertiesListBoxInnerNode = dynamic_cast< GUIParentNode* >((entityPropertiesList->getScreenNode()->getNodeById(entityPropertiesList->getId() + L"_inner")));
	auto idx = 1;
	wstring entityPropertiesListBoxSubNodesXML = L"";
	entityPropertiesListBoxSubNodesXML =
		entityPropertiesListBoxSubNodesXML +
		L"<scrollarea-vertical id=\"" +
		entityPropertiesList->getId() +
		L"_inner_scrollarea\" width=\"100%\" height=\"100%\">\n";
	for (auto i = 0; i < entity->getPropertyCount(); i++) {
		PropertyModelClass* entityProperty = entity->getPropertyByIndex(i);
		entityPropertiesListBoxSubNodesXML =
			entityPropertiesListBoxSubNodesXML +
			L"<selectbox-option text=\"" +
			GUIParser::escapeQuotes(entityProperty->getName()) +
			L": " +
			GUIParser::escapeQuotes(entityProperty->getValue()) +
			L"\" value=\"" +
			GUIParser::escapeQuotes(entityProperty->getName()) +
			L"\" " +
			(selectedName.length() > 0 && entityProperty->getName() == selectedName ? L"selected=\"true\" " : L"") +
			L"/>\n";
	}
	entityPropertiesListBoxSubNodesXML = entityPropertiesListBoxSubNodesXML + L"</scrollarea-vertical>\n";
	try {
		entityPropertiesListBoxInnerNode->replaceSubNodes(entityPropertiesListBoxSubNodesXML, false);
	} catch (Exception& exception) {
		Console::print(string("EntityBaseSubScreenController::setEntityProperties(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	onEntityPropertiesSelectionChanged(entity);
}

void EntityBaseSubScreenController::unsetEntityProperties()
{
	auto modelPropertiesListBoxInnerNode = dynamic_cast< GUIParentNode* >((entityPropertiesList->getScreenNode()->getNodeById(entityPropertiesList->getId() + L"_inner")));
	modelPropertiesListBoxInnerNode->clearSubNodes();
	entityPropertiesPresets->getController()->setValue(value->set(L"none"));
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

void EntityBaseSubScreenController::onEntityPropertySave(LevelEditorEntity* entity)
{
	if (view->entityPropertySave(
		entity,
		entityPropertiesList->getController()->getValue()->toWString(),
		entityPropertyName->getController()->getValue()->toWString(),
		entityPropertyValue->getController()->getValue()->toWString()) == false) {
		showErrorPopUp(L"Warning", L"Saving entity property failed");
	}
}

void EntityBaseSubScreenController::onEntityPropertyAdd(LevelEditorEntity* entity)
{
	if (view->entityPropertyAdd(entity) == false) {
		showErrorPopUp(L"Warning", L"Adding new entity property failed");
	}
}

void EntityBaseSubScreenController::onEntityPropertyRemove(LevelEditorEntity* entity)
{
	if (view->entityPropertyRemove(entity, entityPropertiesList->getController()->getValue()->toWString()) == false) {
		showErrorPopUp(L"Warning", L"Removing entity property failed");
	}
}

void EntityBaseSubScreenController::showErrorPopUp(const wstring& caption, const wstring& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void EntityBaseSubScreenController::onEntityPropertyPresetApply(LevelEditorEntity* model)
{
	view->entityPropertiesPreset(model, entityPropertiesPresets->getController()->getValue()->toWString());
}

void EntityBaseSubScreenController::onEntityPropertiesSelectionChanged(LevelEditorEntity* entity)
{
	entityPropertyName->getController()->setDisabled(true);
	entityPropertyName->getController()->setValue(TEXT_EMPTY);
	entityPropertyValue->getController()->setDisabled(true);
	entityPropertyValue->getController()->setValue(TEXT_EMPTY);
	entityPropertySave->getController()->setDisabled(true);
	entityPropertyRemove->getController()->setDisabled(true);
	auto entityProperty = entity->getProperty(entityPropertiesList->getController()->getValue()->toWString());
	if (entityProperty != nullptr) {
		entityPropertyName->getController()->setValue(value->set(entityProperty->getName()));
		entityPropertyValue->getController()->setValue(value->set(entityProperty->getValue()));
		entityPropertyName->getController()->setDisabled(false);
		entityPropertyValue->getController()->setDisabled(false);
		entityPropertySave->getController()->setDisabled(false);
		entityPropertyRemove->getController()->setDisabled(false);
	}
}

void EntityBaseSubScreenController::onValueChanged(GUIElementNode* node, LevelEditorEntity* model)
{
	if (node == entityPropertiesList) {
		onEntityPropertiesSelectionChanged(model);
	} else {
	}
}

void EntityBaseSubScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node, LevelEditorEntity* entity)
{
	{
		auto v = type;
		if ((v == GUIActionListener_Type::PERFORMED))
		{
			{
				if (node->getId().compare(L"button_entity_apply") == 0) {
					onEntityDataApply(entity);
				} else
				if (node->getId().compare(L"button_entity_properties_presetapply") == 0) {
					onEntityPropertyPresetApply(entity);
				} else
				if (node->getId().compare(L"button_entity_properties_add") == 0) {
					onEntityPropertyAdd(entity);
				} else
				if (node->getId().compare(L"button_entity_properties_remove") == 0) {
					onEntityPropertyRemove(entity);
				} else
				if (node->getId().compare(L"button_entity_properties_save") == 0) {
					onEntityPropertySave(entity);
				} else {
				}
				goto end_switch0;;
			}
		}
		if ((v == GUIActionListener_Type::PERFORMED) || (v == GUIActionListener_Type::PERFORMING))
		{
			{
				goto end_switch0;;
			}
		}
		end_switch0:;
	}

}
