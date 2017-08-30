// Generated from /tdme/src/tdme/tools/shared/controller/EntityBaseSubScreenController.java
#include <tdme/tools/shared/controller/EntityBaseSubScreenController.h>

#include <map>
#include <string>
#include <vector>

#include <java/lang/Iterable.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Collection.h>
#include <java/util/Iterator.h>
#include <java/util/Set.h>
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
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>
#include <tdme/utils/MutableString.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::tools::shared::controller::EntityBaseSubScreenController;
using java::lang::Iterable;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Collection;
using java::util::Iterator;
using java::util::Set;
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
using tdme::utils::_Console;
using tdme::utils::_Exception;

MutableString* EntityBaseSubScreenController::TEXT_EMPTY = new MutableString(u""_j);

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
		entityName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"entity_name"_j));
		entityDescription = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"entity_description"_j));
		entityApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_entity_apply"_j));
		entityPropertyName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"entity_property_name"_j));
		entityPropertyValue = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"entity_property_value"_j));
		entityPropertySave = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_entity_properties_save"_j));
		entityPropertyAdd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_entity_properties_add"_j));
		entityPropertyRemove = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_entity_properties_remove"_j));
		entityPropertiesList = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"entity_properties_listbox"_j));
		entityPropertyPresetApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_entity_properties_presetapply"_j));
		entityPropertiesPresets = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"entity_properties_presets"_j));
	} catch (_Exception& exception) {
		_Console::print(string("EntityBaseSubScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	setEntityPresetIds(LevelPropertyPresets::getInstance()->getObjectPropertiesPresets());
}

void EntityBaseSubScreenController::setEntityData(String* name, String* description)
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

	view->setEntityData(model, entityName->getController()->getValue()->toString(), entityDescription->getController()->getValue()->toString());
	onSetEntityDataAction->performAction();
}

void EntityBaseSubScreenController::setEntityPresetIds(const map<wstring, vector<PropertyModelClass*>>* entityPresetIds)
{
	auto entityPropertiesPresetsInnerNode = dynamic_cast< GUIParentNode* >((entityPropertiesPresets->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(entityPropertiesPresets->getId())->append(u"_inner"_j)->toString())));
	auto idx = 0;
	auto entityPropertiesPresetsInnerNodeSubNodesXML = u""_j;
	entityPropertiesPresetsInnerNodeSubNodesXML = ::java::lang::StringBuilder(entityPropertiesPresetsInnerNodeSubNodesXML).append(::java::lang::StringBuilder().append(u"<scrollarea-vertical id=\""_j)->append(entityPropertiesPresets->getId())
		->append(u"_inner_scrollarea\" width=\"100%\" height=\"100\">\n"_j)->toString())->toString();
	for (auto it: *entityPresetIds) {
		String* entityPresetId = new String(it.first);
		entityPropertiesPresetsInnerNodeSubNodesXML = ::java::lang::StringBuilder(entityPropertiesPresetsInnerNodeSubNodesXML).append(::java::lang::StringBuilder().append(u"<dropdown-option text=\""_j)->append(GUIParser::escapeQuotes(entityPresetId))
			->append(u"\" value=\""_j)
			->append(GUIParser::escapeQuotes(entityPresetId))
			->append(u"\" "_j)
			->append((idx == 0 ? u"selected=\"true\" "_j : u""_j))
			->append(u" />\n"_j)->toString())->toString();
		idx++;
	}
	entityPropertiesPresetsInnerNodeSubNodesXML = ::java::lang::StringBuilder(entityPropertiesPresetsInnerNodeSubNodesXML).append(u"</scrollarea-vertical>"_j)->toString();
	try {
		entityPropertiesPresetsInnerNode->replaceSubNodes(entityPropertiesPresetsInnerNodeSubNodesXML, true);
	} catch (_Exception& exception) {
		_Console::print(string("EntityBaseSubScreenController::setEntityPresetIds(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
}

void EntityBaseSubScreenController::setEntityProperties(LevelEditorEntity* entity, String* presetId, String* selectedName)
{
	entityPropertiesPresets->getController()->setDisabled(false);
	entityPropertyPresetApply->getController()->setDisabled(false);
	entityPropertiesList->getController()->setDisabled(false);
	entityPropertyAdd->getController()->setDisabled(false);
	entityPropertyRemove->getController()->setDisabled(false);
	entityPropertySave->getController()->setDisabled(true);
	entityPropertyName->getController()->setDisabled(true);
	entityPropertyValue->getController()->setDisabled(true);
	entityPropertiesPresets->getController()->setValue(presetId != nullptr ? value->set(presetId) : value->set(u"none"_j));
	auto entityPropertiesListBoxInnerNode = dynamic_cast< GUIParentNode* >((entityPropertiesList->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(entityPropertiesList->getId())->append(u"_inner"_j)->toString())));
	auto idx = 1;
	auto entityPropertiesListBoxSubNodesXML = u""_j;
	entityPropertiesListBoxSubNodesXML = ::java::lang::StringBuilder(entityPropertiesListBoxSubNodesXML).append(::java::lang::StringBuilder().append(u"<scrollarea-vertical id=\""_j)->append(entityPropertiesList->getId())
		->append(u"_inner_scrollarea\" width=\"100%\" height=\"100%\">\n"_j)->toString())->toString();
	for (auto i = 0; i < entity->getPropertyCount(); i++) {
		PropertyModelClass* entityProperty = entity->getPropertyByIndex(i);
		entityPropertiesListBoxSubNodesXML = ::java::lang::StringBuilder(entityPropertiesListBoxSubNodesXML).append(::java::lang::StringBuilder().append(u"<selectbox-option text=\""_j)->append(GUIParser::escapeQuotes(entityProperty->getName()))
			->append(u": "_j)
			->append(GUIParser::escapeQuotes(entityProperty->getValue()))
			->append(u"\" value=\""_j)
			->append(GUIParser::escapeQuotes(entityProperty->getName()))
			->append(u"\" "_j)
			->append((selectedName != nullptr && entityProperty->getName()->equals(selectedName) ? u"selected=\"true\" "_j : u""_j))
			->append(u"/>\n"_j)->toString())->toString();
	}
	entityPropertiesListBoxSubNodesXML = ::java::lang::StringBuilder(entityPropertiesListBoxSubNodesXML).append(u"</scrollarea-vertical>\n"_j)->toString();
	try {
		entityPropertiesListBoxInnerNode->replaceSubNodes(entityPropertiesListBoxSubNodesXML, false);
	} catch (_Exception& exception) {
		_Console::print(string("EntityBaseSubScreenController::setEntityProperties(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	onEntityPropertiesSelectionChanged(entity);
}

void EntityBaseSubScreenController::unsetEntityProperties()
{
	auto modelPropertiesListBoxInnerNode = dynamic_cast< GUIParentNode* >((entityPropertiesList->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(entityPropertiesList->getId())->append(u"_inner"_j)->toString())));
	modelPropertiesListBoxInnerNode->clearSubNodes();
	entityPropertiesPresets->getController()->setValue(value->set(u"none"_j));
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
	if (view->entityPropertySave(entity, entityPropertiesList->getController()->getValue()->toString(), entityPropertyName->getController()->getValue()->toString(), entityPropertyValue->getController()->getValue()->toString()) == false) {
		showErrorPopUp(u"Warning"_j, u"Saving entity property failed"_j);
	}
}

void EntityBaseSubScreenController::onEntityPropertyAdd(LevelEditorEntity* entity)
{
	if (view->entityPropertyAdd(entity) == false) {
		showErrorPopUp(u"Warning"_j, u"Adding new entity property failed"_j);
	}
}

void EntityBaseSubScreenController::onEntityPropertyRemove(LevelEditorEntity* entity)
{
	if (view->entityPropertyRemove(entity, entityPropertiesList->getController()->getValue()->toString()) == false) {
		showErrorPopUp(u"Warning"_j, u"Removing entity property failed"_j);
	}
}

void EntityBaseSubScreenController::showErrorPopUp(String* caption, String* message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void EntityBaseSubScreenController::onEntityPropertyPresetApply(LevelEditorEntity* model)
{
	view->entityPropertiesPreset(model, entityPropertiesPresets->getController()->getValue()->toString());
}

void EntityBaseSubScreenController::onEntityPropertiesSelectionChanged(LevelEditorEntity* entity)
{
	entityPropertyName->getController()->setDisabled(true);
	entityPropertyName->getController()->setValue(TEXT_EMPTY);
	entityPropertyValue->getController()->setDisabled(true);
	entityPropertyValue->getController()->setValue(TEXT_EMPTY);
	entityPropertySave->getController()->setDisabled(true);
	entityPropertyRemove->getController()->setDisabled(true);
	auto entityProperty = entity->getProperty(entityPropertiesList->getController()->getValue()->toString());
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
				if (node->getId()->equals(u"button_entity_apply"_j)) {
					onEntityDataApply(entity);
				} else
				if (node->getId()->equals(u"button_entity_properties_presetapply"_j)) {
					onEntityPropertyPresetApply(entity);
				} else
				if (node->getId()->equals(u"button_entity_properties_add"_j)) {
					onEntityPropertyAdd(entity);
				} else
				if (node->getId()->equals(u"button_entity_properties_remove"_j)) {
					onEntityPropertyRemove(entity);
				} else
				if (node->getId()->equals(u"button_entity_properties_save"_j)) {
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
