// Generated from /tdme/src/tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.java
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>

#include <string>

#include <java/lang/String.h>

#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController_onValueChanged_1.h>
#include <tdme/tools/leveleditor/views/EmptyView.h>
#include <tdme/tools/leveleditor/views/LevelEditorView.h>
#include <tdme/tools/leveleditor/views/ModelViewerView.h>
#include <tdme/tools/leveleditor/views/ParticleSystemView.h>
#include <tdme/tools/leveleditor/views/TriggerView.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::wstring;
using std::to_wstring;

using java::lang::String;

using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController_onValueChanged_1;
using tdme::tools::leveleditor::views::EmptyView;
using tdme::tools::leveleditor::views::LevelEditorView;
using tdme::tools::leveleditor::views::ModelViewerView;
using tdme::tools::leveleditor::views::ParticleSystemView;
using tdme::tools::leveleditor::views::TriggerView;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::View;
using tdme::utils::MutableString;
using tdme::utils::StringConverter;
using tdme::utils::_Console;
using tdme::utils::_Exception;

LevelEditorEntityLibraryScreenController::LevelEditorEntityLibraryScreenController(PopUps* popUps) 
{
	this->popUps = popUps;
	this->modelPath = L".";
	entityLibraryListBoxSelection = new MutableString();
}

GUIScreenNode* LevelEditorEntityLibraryScreenController::getScreenNode()
{
	return screenNode;
}

const wstring& LevelEditorEntityLibraryScreenController::getModelPath()
{
	return modelPath;
}

void LevelEditorEntityLibraryScreenController::setModelPath(const wstring& modelPath)
{
	this->modelPath = modelPath;
}

void LevelEditorEntityLibraryScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse(u"resources/tools/leveleditor/gui"_j, u"screen_leveleditor_entitylibrary.xml"_j);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		entityLibraryListBox = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"entity_library_listbox"_j));
		buttonEntityPlace = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_entity_place"_j));
		buttonLevelEdit = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(u"button_level_edit"_j));
	} catch (_Exception& exception) {
		_Console::print(string("LevelEditorEntityLibraryScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	buttonEntityPlace->getController()->setDisabled(false);
	buttonLevelEdit->getController()->setDisabled(true);
	dropdownEntityActionReset = new MutableString(u"action"_j);
}

void LevelEditorEntityLibraryScreenController::dispose()
{
}

void LevelEditorEntityLibraryScreenController::selectEntity(int32_t entityId)
{
	entityLibraryListBoxSelection->set(entityId);
	entityLibraryListBox->getController()->setValue(entityLibraryListBoxSelection);
}

void LevelEditorEntityLibraryScreenController::setEntityLibrary()
{
	auto entityLibrary = TDMELevelEditor::getInstance()->getEntityLibrary();
	entityLibraryListBoxSelection->set(entityLibraryListBox->getController()->getValue());
	auto entityLibraryListBoxInnerNode = dynamic_cast< GUIParentNode* >((entityLibraryListBox->getScreenNode()->getNodeById(new String(entityLibraryListBox->getId()->getCPPWString() + L"_inner"))));
	auto idx = 1;
	wstring entityLibraryListBoxSubNodesXML;
	entityLibraryListBoxSubNodesXML =
		entityLibraryListBoxSubNodesXML +
		L"<scrollarea-vertical id=\"" +
		entityLibraryListBox->getId()->getCPPWString() +
		L"_inner_scrollarea\" width=\"100%\" height=\"100%\">\n";
	for (auto i = 0; i < entityLibrary->getEntityCount(); i++) {
		auto objectId = entityLibrary->getEntityAt(i)->getId();
		auto objectName = entityLibrary->getEntityAt(i)->getName();
		entityLibraryListBoxSubNodesXML =
			entityLibraryListBoxSubNodesXML +
			L"<selectbox-option text=\"" +
			GUIParser::escapeQuotes(objectName) +
			L"\" value=\"" +
			to_wstring(objectId) +
			L"\" " +
			(i == 0 ? L"selected=\"true\" " : L"") +
			L"/>\n";
	}
	entityLibraryListBoxSubNodesXML = entityLibraryListBoxSubNodesXML + L"</scrollarea-vertical>\n";
	try {
		entityLibraryListBoxInnerNode->replaceSubNodes(new String(entityLibraryListBoxSubNodesXML), false);
	} catch (_Exception& exception) {
		_Console::print(string("LevelEditorEntityLibraryScreenController::setEntityLibrary(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	if (entityLibraryListBoxSelection->length() > 0) {
		entityLibraryListBox->getController()->setValue(entityLibraryListBoxSelection);
	}
	onEntitySelectionChanged();
	buttonEntityPlace->getController()->setDisabled(entityLibrary->getEntityCount() == 0);
}

void LevelEditorEntityLibraryScreenController::onEntitySelectionChanged()
{
	auto view = TDMELevelEditor::getInstance()->getView();
	if (dynamic_cast< LevelEditorView* >(view) != nullptr) {
		auto entity = TDMELevelEditor::getInstance()->getEntityLibrary()->getEntity(Tools::convertToIntSilent(entityLibraryListBox->getController()->getValue()->toString()));
		if (entity != nullptr) {
			(dynamic_cast< LevelEditorView* >(view))->loadEntityFromLibrary(entity->getId());
		}
	}
}

void LevelEditorEntityLibraryScreenController::onEditEntity()
{
	auto entity = TDMELevelEditor::getInstance()->getEntityLibrary()->getEntity(Tools::convertToIntSilent(entityLibraryListBox->getController()->getValue()->toString()));
	if (entity == nullptr)
		return;

	{
		auto v = entity->getType();
		if ((v == LevelEditorEntity_EntityType::MODEL)) {
			if (dynamic_cast< ModelViewerView* >(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToModelViewer();
			}
			(dynamic_cast< ModelViewerView* >(TDMELevelEditor::getInstance()->getView()))->setEntity(entity);
			goto end_switch0;;
		}
		if ((v == LevelEditorEntity_EntityType::TRIGGER)) {
			if (dynamic_cast< TriggerView* >(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToTriggerView();
			}
			(dynamic_cast< TriggerView* >(TDMELevelEditor::getInstance()->getView()))->setEntity(entity);
			goto end_switch0;;
		}
		if ((v == LevelEditorEntity_EntityType::EMPTY)) {
			if (dynamic_cast< EmptyView* >(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToEmptyView();
			}
			(dynamic_cast< EmptyView* >(TDMELevelEditor::getInstance()->getView()))->setEntity(entity);
			goto end_switch0;;
		}
		if ((v == LevelEditorEntity_EntityType::PARTICLESYSTEM)) {
			if (dynamic_cast< ParticleSystemView* >(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToParticleSystemView();
			}
			(dynamic_cast< ParticleSystemView* >(TDMELevelEditor::getInstance()->getView()))->setEntity(entity);
			goto end_switch0;;
		}
		end_switch0:;
	}

	buttonEntityPlace->getController()->setDisabled(true);
	buttonLevelEdit->getController()->setDisabled(false);
}

void LevelEditorEntityLibraryScreenController::onEditLevel()
{
	TDMELevelEditor::getInstance()->switchToLevelEditor();
	buttonEntityPlace->getController()->setDisabled(false);
	buttonLevelEdit->getController()->setDisabled(true);
}

void LevelEditorEntityLibraryScreenController::onPlaceEntity()
{
	auto entity = TDMELevelEditor::getInstance()->getEntityLibrary()->getEntity(Tools::convertToIntSilent(entityLibraryListBox->getController()->getValue()->toString()));
	if (entity == nullptr)
		return;

	auto view = TDMELevelEditor::getInstance()->getView();
	if (dynamic_cast< LevelEditorView* >(view) != nullptr) {
		(dynamic_cast< LevelEditorView* >(view))->placeObject();
	}
}

void LevelEditorEntityLibraryScreenController::onDeleteEntity()
{
	auto entity = TDMELevelEditor::getInstance()->getEntityLibrary()->getEntity(Tools::convertToIntSilent(entityLibraryListBox->getController()->getValue()->toString()));
	if (entity == nullptr)
		return;

	TDMELevelEditor::getInstance()->getLevel()->removeObjectsByEntityId(entity->getId());
	TDMELevelEditor::getInstance()->getLevel()->getEntityLibrary()->removeEntity(entity->getId());
	setEntityLibrary();
	auto view = TDMELevelEditor::getInstance()->getView();
	if (dynamic_cast< LevelEditorView* >(view) != nullptr) {
		(dynamic_cast< LevelEditorView* >(view))->loadLevel();
	} else {
		TDMELevelEditor::getInstance()->switchToLevelEditor();
	}
}

void LevelEditorEntityLibraryScreenController::onValueChanged(GUIElementNode* node)
{
	if (node->getId()->equals(u"entity_library_listbox"_j) == true) {
		onEntitySelectionChanged();
	} else
		if (node->getId()->equals(u"dropdown_entity_action"_j) == true) {
		if (node->getController()->getValue()->equals(u"edit"_j) == true) {
			onEditEntity();
		} else
		if (node->getController()->getValue()->equals(u"delete"_j) == true) {
			onDeleteEntity();
		} else
		if (node->getController()->getValue()->equals(u"create_model"_j) == true) {
			auto const entityLibrary = TDMELevelEditor::getInstance()->getEntityLibrary();
			popUps->getFileDialogScreenController()->show(
				modelPath,
				L"Load from: ",
				new StringArray({
					u"tmm"_j,
					u"dae"_j,
					u"tm"_j
				}),
				L"",
				new LevelEditorEntityLibraryScreenController_onValueChanged_1(this, entityLibrary)
			);
		} else
		if (node->getController()->getValue()->equals(u"create_trigger"_j) == true) {
			try {
				auto model = TDMELevelEditor::getInstance()->getEntityLibrary()->addTrigger(LevelEditorEntityLibrary::ID_ALLOCATE, L"New trigger", L"", 1.0f, 1.0f, 1.0f);
				setEntityLibrary();
				entityLibraryListBox->getController()->setValue(entityLibraryListBoxSelection->set(model->getId()));
				onEditEntity();
			} catch (_Exception& exception) {
				popUps->getInfoDialogScreenController()->show(
					L"Error",
					L"An error occurred: " + StringConverter::toWideString(string(exception.what()))
				);
			}
		} else
		if (node->getController()->getValue()->equals(u"create_empty"_j) == true) {
			try {
				auto model = TDMELevelEditor::getInstance()->getEntityLibrary()->addEmpty(LevelEditorEntityLibrary::ID_ALLOCATE, L"New empty", L"");
				setEntityLibrary();
				entityLibraryListBox->getController()->setValue(entityLibraryListBoxSelection->set(model->getId()));
				onEditEntity();
			} catch (_Exception& exception) {
				popUps->getInfoDialogScreenController()->show(
					L"Error",
					L"An error occurred: " + StringConverter::toWideString(string(exception.what()))
				 );
			}
		} else
		if (node->getController()->getValue()->equals(u"create_light"_j) == true) {
		} else
		if (node->getController()->getValue()->equals(u"create_particlesystem"_j) == true) {
			try {
				auto model = TDMELevelEditor::getInstance()->getEntityLibrary()->addParticleSystem(LevelEditorEntityLibrary::ID_ALLOCATE, L"New particle system", L"");
				setEntityLibrary();
				entityLibraryListBox->getController()->setValue(entityLibraryListBoxSelection->set(model->getId()));
				onEditEntity();
			} catch (_Exception& exception) {
				popUps->getInfoDialogScreenController()->show(
					L"Error",
					L"An error occurred: " + StringConverter::toWideString(string(exception.what()))
				 );
			}
		} else {
			_Console::println(L"LevelEditorEntityLibraryScreenController::onValueChanged: dropdown_model_create: " + node->getController()->getValue()->toString()->getCPPWString());
		}
		node->getController()->setValue(dropdownEntityActionReset);
	} else {
		_Console::println(L"LevelEditorEntityLibraryScreenController::onValueChanged: " + node->getId()->getCPPWString());
	}
}

void LevelEditorEntityLibraryScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	if (type == GUIActionListener_Type::PERFORMED) {
		if (node->getId()->equals(u"button_entity_place"_j) == true) {
			onPlaceEntity();
		} else if (node->getId()->equals(u"button_level_edit"_j) == true) {
			onEditLevel();
		} else {
			_Console::println(L"LevelEditorScreenController::onActionPerformed: " + node->getId()->getCPPWString());
		}
	}
}
