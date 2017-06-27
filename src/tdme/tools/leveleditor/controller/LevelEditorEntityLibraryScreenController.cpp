// Generated from /tdme/src/tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.java
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/CharSequence.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Exception.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
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
#include <tdme/utils/_Console.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::CharSequence;
using java::lang::ClassCastException;
using java::lang::Comparable;
using java::lang::Exception;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
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
using tdme::utils::_Console;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

LevelEditorEntityLibraryScreenController::LevelEditorEntityLibraryScreenController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorEntityLibraryScreenController::LevelEditorEntityLibraryScreenController(PopUps* popUps) 
	: LevelEditorEntityLibraryScreenController(*static_cast< ::default_init_tag* >(0))
{
	ctor(popUps);
}

void LevelEditorEntityLibraryScreenController::ctor(PopUps* popUps)
{
	super::ctor();
	this->popUps = popUps;
	this->modelPath = u"."_j;
	entityLibraryListBoxSelection = new MutableString();
}

GUIScreenNode* LevelEditorEntityLibraryScreenController::getScreenNode()
{
	return screenNode;
}

String* LevelEditorEntityLibraryScreenController::getModelPath()
{
	return modelPath;
}

void LevelEditorEntityLibraryScreenController::setModelPath(String* modelPath)
{
	this->modelPath = modelPath;
}

void LevelEditorEntityLibraryScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse(u"resources/tools/leveleditor/gui"_j, u"screen_leveleditor_entitylibrary.xml"_j);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		entityLibraryListBox = java_cast< GUIElementNode* >(screenNode->getNodeById(u"entity_library_listbox"_j));
		buttonEntityPlace = java_cast< GUIElementNode* >(screenNode->getNodeById(u"button_entity_place"_j));
		buttonLevelEdit = java_cast< GUIElementNode* >(screenNode->getNodeById(u"button_level_edit"_j));
	} catch (Exception* e) {
		e->printStackTrace();
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
	auto entityLibraryListBoxInnerNode = java_cast< GUIParentNode* >((entityLibraryListBox->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(entityLibraryListBox->getId())->append(u"_inner"_j)->toString())));
	auto idx = 1;
	auto entityLibraryListBoxSubNodesXML = u""_j;
	entityLibraryListBoxSubNodesXML = ::java::lang::StringBuilder(entityLibraryListBoxSubNodesXML).append(::java::lang::StringBuilder().append(u"<scrollarea-vertical id=\""_j)->append(entityLibraryListBox->getId())
		->append(u"_inner_scrollarea\" width=\"100%\" height=\"100%\">\n"_j)->toString())->toString();
	for (auto i = 0; i < entityLibrary->getEntityCount(); i++) {
		auto objectId = entityLibrary->getEntityAt(i)->getId();
		auto objectName = entityLibrary->getEntityAt(i)->getName();
		entityLibraryListBoxSubNodesXML = ::java::lang::StringBuilder(entityLibraryListBoxSubNodesXML).append(::java::lang::StringBuilder().append(u"<selectbox-option text=\""_j)->append(GUIParser::escapeQuotes(objectName))
			->append(u"\" value=\""_j)
			->append(objectId)
			->append(u"\" "_j)
			->append((i == 0 ? u"selected=\"true\" "_j : u""_j))
			->append(u"/>\n"_j)->toString())->toString();
	}
	entityLibraryListBoxSubNodesXML = ::java::lang::StringBuilder(entityLibraryListBoxSubNodesXML).append(u"</scrollarea-vertical>\n"_j)->toString();
	try {
		entityLibraryListBoxInnerNode->replaceSubNodes(entityLibraryListBoxSubNodesXML, false);
	} catch (Exception* e) {
		e->printStackTrace();
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
			(java_cast< LevelEditorView* >(view))->loadEntityFromLibrary(entity->getId());
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
			(java_cast< ModelViewerView* >(TDMELevelEditor::getInstance()->getView()))->setEntity(entity);
			goto end_switch0;;
		}
		if ((v == LevelEditorEntity_EntityType::TRIGGER)) {
			if (dynamic_cast< TriggerView* >(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToTriggerView();
			}
			(java_cast< TriggerView* >(TDMELevelEditor::getInstance()->getView()))->setEntity(entity);
			goto end_switch0;;
		}
		if ((v == LevelEditorEntity_EntityType::EMPTY)) {
			if (dynamic_cast< EmptyView* >(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToEmptyView();
			}
			(java_cast< EmptyView* >(TDMELevelEditor::getInstance()->getView()))->setEntity(entity);
			goto end_switch0;;
		}
		if ((v == LevelEditorEntity_EntityType::PARTICLESYSTEM)) {
			if (dynamic_cast< ParticleSystemView* >(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToParticleSystemView();
			}
			(java_cast< ParticleSystemView* >(TDMELevelEditor::getInstance()->getView()))->setEntity(entity);
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
		(java_cast< LevelEditorView* >(view))->placeObject();
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
		(java_cast< LevelEditorView* >(view))->loadLevel();
	} else {
		TDMELevelEditor::getInstance()->switchToLevelEditor();
	}
}

void LevelEditorEntityLibraryScreenController::onValueChanged(GUIElementNode* node)
{
	if (node->getId()->equals(u"entity_library_listbox"_j) == true) {
		onEntitySelectionChanged();
	} else if (node->getId()->equals(u"dropdown_entity_action"_j) == true) {
		if (node->getController()->getValue()->equals(u"edit"_j) == true) {
			onEditEntity();
		} else if (node->getController()->getValue()->equals(u"delete"_j) == true) {
			onDeleteEntity();
		} else if (node->getController()->getValue()->equals(u"create_model"_j) == true) {
			auto const entityLibrary = TDMELevelEditor::getInstance()->getEntityLibrary();
			popUps->getFileDialogScreenController()->show(modelPath, u"Load from: "_j, new StringArray({
				u"tmm"_j,
				u"dae"_j,
				u"tm"_j
			}), u""_j, new LevelEditorEntityLibraryScreenController_onValueChanged_1(this, entityLibrary));
		} else if (node->getController()->getValue()->equals(u"create_trigger"_j) == true) {
			try {
				auto model = TDMELevelEditor::getInstance()->getEntityLibrary()->addTrigger(LevelEditorEntityLibrary::ID_ALLOCATE, u"New trigger"_j, u""_j, 1.0f, 1.0f, 1.0f);
				setEntityLibrary();
				entityLibraryListBox->getController()->setValue(entityLibraryListBoxSelection->set(model->getId()));
				onEditEntity();
			} catch (Exception* exception) {
				popUps->getInfoDialogScreenController()->show(u"Error"_j, ::java::lang::StringBuilder().append(u"An error occurred: "_j)->append(exception->getMessage())->toString());
			}
		} else if (node->getController()->getValue()->equals(u"create_empty"_j) == true) {
			try {
				auto model = TDMELevelEditor::getInstance()->getEntityLibrary()->addEmpty(LevelEditorEntityLibrary::ID_ALLOCATE, u"New empty"_j, u""_j);
				setEntityLibrary();
				entityLibraryListBox->getController()->setValue(entityLibraryListBoxSelection->set(model->getId()));
				onEditEntity();
			} catch (Exception* exception) {
				popUps->getInfoDialogScreenController()->show(u"Error"_j, ::java::lang::StringBuilder().append(u"An error occurred: "_j)->append(exception->getMessage())->toString());
			}
		} else if (node->getController()->getValue()->equals(u"create_light"_j) == true) {
		} else if (node->getController()->getValue()->equals(u"create_particlesystem"_j) == true) {
			try {
				auto model = TDMELevelEditor::getInstance()->getEntityLibrary()->addParticleSystem(LevelEditorEntityLibrary::ID_ALLOCATE, u"New particle system"_j, u""_j);
				setEntityLibrary();
				entityLibraryListBox->getController()->setValue(entityLibraryListBoxSelection->set(model->getId()));
				onEditEntity();
			} catch (Exception* exception) {
				popUps->getInfoDialogScreenController()->show(u"Error"_j, ::java::lang::StringBuilder().append(u"An error occurred: "_j)->append(exception->getMessage())->toString());
			}
		} else {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"LevelEditorEntityLibraryScreenController::onValueChanged: dropdown_model_create: "_j)->append(static_cast< Object* >(node->getController()->getValue()))->toString()));
		}
		node->getController()->setValue(dropdownEntityActionReset);
	} else {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"LevelEditorEntityLibraryScreenController::onValueChanged: "_j)->append(node->getId())->toString()));
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
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"LevelEditorScreenController::onActionPerformed: "_j)->append(node->getId())->toString()));
		}
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorEntityLibraryScreenController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.leveleditor.controller.LevelEditorEntityLibraryScreenController", 74);
    return c;
}

java::lang::Class* LevelEditorEntityLibraryScreenController::getClass0()
{
	return class_();
}

