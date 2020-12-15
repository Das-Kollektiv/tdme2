#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>

#include <string>

#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/Action.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/tools/leveleditor/views/EmptyView.h>
#include <tdme/tools/leveleditor/views/EnvironmentMappingView.h>
#include <tdme/tools/leveleditor/views/LevelEditorView.h>
#include <tdme/tools/leveleditor/views/ModelEditorView.h>
#include <tdme/tools/leveleditor/views/ParticleSystemView.h>
#include <tdme/tools/leveleditor/views/TriggerView.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::to_string;

using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::models::TMWriter;
using tdme::utilities::ModelTools;
using tdme::gui::GUIParser;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::tools::leveleditor::views::EmptyView;
using tdme::tools::leveleditor::views::EnvironmentMappingView;
using tdme::tools::leveleditor::views::LevelEditorView;
using tdme::tools::leveleditor::views::ModelEditorView;
using tdme::tools::leveleditor::views::ParticleSystemView;
using tdme::tools::leveleditor::views::TriggerView;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::SceneEntity;
using tdme::engine::scene::Scene;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::View;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;
using tdme::utilities::MutableString;

LevelEditorEntityLibraryScreenController::LevelEditorEntityLibraryScreenController(PopUps* popUps)
{
	this->popUps = popUps;
	this->modelPath = ".";
}

GUIScreenNode* LevelEditorEntityLibraryScreenController::getScreenNode()
{
	return screenNode;
}

const string& LevelEditorEntityLibraryScreenController::getModelPath()
{
	return modelPath;
}

void LevelEditorEntityLibraryScreenController::setModelPath(const string& modelPath)
{
	this->modelPath = modelPath;
}

void LevelEditorEntityLibraryScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/tools/leveleditor/gui", "screen_leveleditor_entitylibrary.xml");
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		entityLibraryListBox = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("entity_library_listbox"));
		buttonEntityPlace = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_entity_place"));
		buttonLevelEdit = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_level_edit"));
	} catch (Exception& exception) {
		Console::print(string("LevelEditorEntityLibraryScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	buttonEntityPlace->getController()->setDisabled(false);
	buttonLevelEdit->getController()->setDisabled(true);
}

void LevelEditorEntityLibraryScreenController::dispose()
{
}

void LevelEditorEntityLibraryScreenController::selectEntity(int entityId)
{
	MutableString entityLibraryListBoxSelection;
	entityLibraryListBoxSelection.set(entityId);
	entityLibraryListBox->getController()->setValue(entityLibraryListBoxSelection);
}

void LevelEditorEntityLibraryScreenController::setEntityLibrary()
{
	MutableString entityLibraryListBoxSelection;
	auto entityLibrary = TDMELevelEditor::getInstance()->getEntityLibrary();
	entityLibraryListBoxSelection.set(entityLibraryListBox->getController()->getValue());
	auto entityLibraryListBoxInnerNode = dynamic_cast< GUIParentNode* >((entityLibraryListBox->getScreenNode()->getNodeById(entityLibraryListBox->getId() + "_inner")));
	auto idx = 1;
	string entityLibraryListBoxSubNodesXML;
	entityLibraryListBoxSubNodesXML =
		entityLibraryListBoxSubNodesXML +
		"<scrollarea-vertical id=\"" +
		entityLibraryListBox->getId() +
		"_inner_scrollarea\" width=\"100%\" height=\"100%\">\n";
	for (auto i = 0; i < entityLibrary->getPrototypeCount(); i++) {
		auto objectId = entityLibrary->getPrototypeAt(i)->getId();
		auto objectName = entityLibrary->getPrototypeAt(i)->getName();
		entityLibraryListBoxSubNodesXML =
			entityLibraryListBoxSubNodesXML +
			"<selectbox-option text=\"" +
			GUIParser::escapeQuotes(objectName) +
			"\" value=\"" +
			to_string(objectId) +
			"\" " +
			(i == 0 ? "selected=\"true\" " : "") +
			"/>\n";
	}
	entityLibraryListBoxSubNodesXML = entityLibraryListBoxSubNodesXML + "</scrollarea-vertical>\n";
	try {
		entityLibraryListBoxInnerNode->replaceSubNodes(entityLibraryListBoxSubNodesXML, false);
	} catch (Exception& exception) {
		Console::print(string("LevelEditorEntityLibraryScreenController::setEntityLibrary(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	if (entityLibraryListBoxSelection.length() > 0) {
		entityLibraryListBox->getController()->setValue(entityLibraryListBoxSelection);
	}
	onEntitySelectionChanged();
	buttonEntityPlace->getController()->setDisabled(entityLibrary->getPrototypeCount() == 0);
}

void LevelEditorEntityLibraryScreenController::onEntitySelectionChanged()
{
	auto view = TDMELevelEditor::getInstance()->getView();
	if (dynamic_cast< LevelEditorView* >(view) != nullptr) {
		auto entity = TDMELevelEditor::getInstance()->getEntityLibrary()->getPrototype(Tools::convertToIntSilent(entityLibraryListBox->getController()->getValue().getString()));
		if (entity != nullptr) {
			(dynamic_cast< LevelEditorView* >(view))->loadEntityFromLibrary(entity->getId());
		}
	}
}

void LevelEditorEntityLibraryScreenController::onEditEntity()
{
	auto entity = TDMELevelEditor::getInstance()->getEntityLibrary()->getPrototype(Tools::convertToIntSilent(entityLibraryListBox->getController()->getValue().getString()));
	if (entity == nullptr) return;
	{
		auto v = entity->getType();
		if (v == Prototype_Type::MODEL) {
			if (dynamic_cast<ModelEditorView*>(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToModelEditor();
			}
			(dynamic_cast<ModelEditorView*>(TDMELevelEditor::getInstance()->getView()))->setEntity(entity);
		} else
		if (v == Prototype_Type::TRIGGER) {
			if (dynamic_cast<TriggerView*>(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToTriggerView();
			}
			(dynamic_cast<TriggerView*>(TDMELevelEditor::getInstance()->getView()))->setEntity(entity);
		} else
		if (v == Prototype_Type::ENVIRONMENTMAPPING) {
			if (dynamic_cast<EnvironmentMappingView*>(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToEnvironmentMappingView();
			}
			(dynamic_cast<EnvironmentMappingView*>(TDMELevelEditor::getInstance()->getView()))->setEntity(entity);
		} else
		if (v == Prototype_Type::EMPTY) {
			if (dynamic_cast< EmptyView* >(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToEmptyView();
			}
			(dynamic_cast< EmptyView* >(TDMELevelEditor::getInstance()->getView()))->setEntity(entity);
		} else
		if (v == Prototype_Type::PARTICLESYSTEM) {
			if (dynamic_cast<ParticleSystemView*>(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToParticleSystemView();
			}
			(dynamic_cast<ParticleSystemView*>(TDMELevelEditor::getInstance()->getView()))->setEntity(entity);
		}
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
	auto entity = TDMELevelEditor::getInstance()->getEntityLibrary()->getPrototype(Tools::convertToIntSilent(entityLibraryListBox->getController()->getValue().getString()));
	if (entity == nullptr) return;
	auto view = TDMELevelEditor::getInstance()->getView();
	if (dynamic_cast< LevelEditorView* >(view) != nullptr) {
		(dynamic_cast< LevelEditorView* >(view))->setPlaceObjectMode();
	}
}

void LevelEditorEntityLibraryScreenController::onDeleteEntity()
{
	auto entity = TDMELevelEditor::getInstance()->getEntityLibrary()->getPrototype(Tools::convertToIntSilent(entityLibraryListBox->getController()->getValue().getString()));
	if (entity == nullptr) return;
	TDMELevelEditor::getInstance()->getLevel()->removeEntitiesByPrototypeId(entity->getId());
	auto view = TDMELevelEditor::getInstance()->getView();
	if (dynamic_cast< LevelEditorView* >(view) != nullptr) {
		(dynamic_cast< LevelEditorView* >(view))->loadLevel();
	} else {
		TDMELevelEditor::getInstance()->switchToLevelEditor();
	}
	TDMELevelEditor::getInstance()->getLevel()->getLibrary()->removePrototype(entity->getId());
	setEntityLibrary();
}

void LevelEditorEntityLibraryScreenController::onPartitionEntity()
{
	// check if we have a entity
	auto entity = TDMELevelEditor::getInstance()->getEntityLibrary()->getPrototype(Tools::convertToIntSilent(entityLibraryListBox->getController()->getValue().getString()));
	if (entity == nullptr || entity->getType() != Prototype_Type::MODEL) return;
	// TODO: there can always be the tdme default animation, do not do skinned objects
	if (/*entity->getModel()->hasAnimations() == true || */entity->getModel()->hasSkinning() == true) {
		popUps->getInfoDialogScreenController()->show("Warning", "This model has animations or skinning");
		return;
	}

	// check if entity exists only once
	vector<string> objectsByEntityId;
	TDMELevelEditor::getInstance()->getLevel()->getEntitiesByPrototypeId(entity->getId(), objectsByEntityId);
	if (objectsByEntityId.size() != 1) {
		popUps->getInfoDialogScreenController()->show("Warning", "This model has several object instances");
		return;
	}

	//
	auto scene = TDMELevelEditor::getInstance()->getLevel();
	auto levelEntityLibrary = scene->getLibrary();
	auto sceneEntity = scene->getEntity(objectsByEntityId[0]);

	// partition object
	map<string, Model*> modelsByPartition;
	map<string, Vector3> modelsPosition;
	ModelTools::partition(
		sceneEntity->getPrototype()->getModel(),
		sceneEntity->getTransformations(),
		modelsByPartition,
		modelsPosition
	);

	try {
		// add partitions to scene
		auto pathName = Tools::getPath(entity->getModelFileName());
		auto fileName = Tools::getFileName(entity->getModelFileName());
		for (auto modelsByPartitionIt: modelsByPartition) {
			auto key = modelsByPartitionIt.first;
			auto model = modelsByPartitionIt.second;
			auto fileNamePartition = StringTools::substring(fileName, 0, StringTools::lastIndexOf(fileName, '.') - 1) + "." + key + ".tm";

			// create entity
			TMWriter::write(
				model,
				pathName,
				fileNamePartition
			);
			auto prototypePartition = levelEntityLibrary->addModel(
				SceneLibrary::ID_ALLOCATE,
				model->getName(),
				model->getName(),
				pathName,
				fileNamePartition,
				Vector3(0.0f, 0.0f, 0.0f)
			);
			prototypePartition->setShader(entity->getShader());
			prototypePartition->setDistanceShader(entity->getDistanceShader());
			prototypePartition->setDistanceShaderDistance(entity->getDistanceShaderDistance());

			// avoid name collision
			auto objectName = model->getName();
			while (scene->getEntity(objectName) != nullptr) {
				objectName+= ".p";
			}

			// add to scene
			auto sceneEntityPartition = new SceneEntity(
				objectName,
				"",
				sceneEntity->getTransformations(),
				prototypePartition
			);
			prototypePartition->setTerrainMesh(sceneEntity->getPrototype()->isTerrainMesh());

			// add to objects
			scene->addEntity(sceneEntityPartition);
		}
	} catch (Exception& exception) {
		popUps->getInfoDialogScreenController()->show("Warning", exception.what());
	}

	// remove original object
	scene->removeEntitiesByPrototypeId(entity->getId());
	// TODO: check if to delete original model
	//	as long as .tl has not been saved it is still required to have this file
	// FileSystem::getInstance()->removeFile(pathName, fileName);

	// (re-)load scene editor view
	auto view = TDMELevelEditor::getInstance()->getView();
	if (dynamic_cast< LevelEditorView* >(view) != nullptr) {
		(dynamic_cast< LevelEditorView* >(view))->loadLevel();
	} else {
		TDMELevelEditor::getInstance()->switchToLevelEditor();
	}

	// remove original entity from entity library
	// TODO: delete file
	scene->getLibrary()->removePrototype(entity->getId());

	//
	setEntityLibrary();
}

void LevelEditorEntityLibraryScreenController::onValueChanged(GUIElementNode* node)
{
	if (node->getId().compare("entity_library_listbox") == 0) {
		onEntitySelectionChanged();
	} else
	if (node->getId().compare("dropdown_entity_action") == 0) {
		if (node->getController()->getValue().getString() == "edit") {
			onEditEntity();
		} else
		if (node->getController()->getValue().getString() == "delete") {
			onDeleteEntity();
		} else
		if (node->getController()->getValue().getString() == "partition") {
			onPartitionEntity();
		} else
		if (node->getController()->getValue().getString() == "create_model") {
			class OnCreateModel: public virtual Action
			{
			public:
				void performAction() override {
					try {
						auto entity = entityLibrary->addModel(
							SceneLibrary::ID_ALLOCATE,
							prototypeLibraryScreenController->popUps->getFileDialogScreenController()->getFileName(),
							"",
							prototypeLibraryScreenController->popUps->getFileDialogScreenController()->getPathName(),
							prototypeLibraryScreenController->popUps->getFileDialogScreenController()->getFileName(),
							Vector3(0.0f, 0.0f, 0.0f)
						);
						entity->setDefaultBoundingVolumes();
						prototypeLibraryScreenController->setEntityLibrary();
						prototypeLibraryScreenController->entityLibraryListBox->getController()->setValue(MutableString(entity->getId()));
						prototypeLibraryScreenController->onEditEntity();
					} catch (Exception& exception) {
						prototypeLibraryScreenController->popUps->getInfoDialogScreenController()->show(
							"Error",
							"An error occurred: " + string(exception.what())
						);
					}
					prototypeLibraryScreenController->modelPath = prototypeLibraryScreenController->popUps->getFileDialogScreenController()->getPathName();
					prototypeLibraryScreenController->popUps->getFileDialogScreenController()->close();
				}

				/**
				 * Public constructor
				 * @param prototypeLibraryScreenController scene editor entity library screen controller
				 * @param entityLibrary entity library
				 */
				OnCreateModel(LevelEditorEntityLibraryScreenController* prototypeLibraryScreenController, SceneLibrary* entityLibrary)
					: prototypeLibraryScreenController(prototypeLibraryScreenController)
					, entityLibrary(entityLibrary) {
				}

			private:
				LevelEditorEntityLibraryScreenController *prototypeLibraryScreenController;
				SceneLibrary* entityLibrary;
			};

			auto const entityLibrary = TDMELevelEditor::getInstance()->getEntityLibrary();
			vector<string> extensions = ModelReader::getModelExtensions();
			extensions.push_back("tmm");
			popUps->getFileDialogScreenController()->show(
				modelPath,
				"Load from: ",
				extensions,
				"",
				true,
				new OnCreateModel(this, entityLibrary)
			);
		} else
		if (node->getController()->getValue().getString() == "create_trigger") {
			try {
				auto model = TDMELevelEditor::getInstance()->getEntityLibrary()->addTrigger(SceneLibrary::ID_ALLOCATE, "New trigger", "", 1.0f, 1.0f, 1.0f);
				setEntityLibrary();
				entityLibraryListBox->getController()->setValue(MutableString(model->getId()));
				onEditEntity();
			} catch (Exception& exception) {
				popUps->getInfoDialogScreenController()->show(
					"Error",
					"An error occurred: " + (string(exception.what()))
				);
			}
		} else
		if (node->getController()->getValue().getString() == "create_environmentmapping") {
			try {
				auto model = TDMELevelEditor::getInstance()->getEntityLibrary()->addEnvironmentMapping(SceneLibrary::ID_ALLOCATE, "New environment mapping", "", 1.0f, 1.0f, 1.0f);
				setEntityLibrary();
				entityLibraryListBox->getController()->setValue(MutableString(model->getId()));
				onEditEntity();
			} catch (Exception& exception) {
				popUps->getInfoDialogScreenController()->show(
					"Error",
					"An error occurred: " + (string(exception.what()))
				);
			}
		} else
		if (node->getController()->getValue().getString() == "create_empty") {
			try {
				auto model = TDMELevelEditor::getInstance()->getEntityLibrary()->addEmpty(SceneLibrary::ID_ALLOCATE, "New empty", "");
				setEntityLibrary();
				entityLibraryListBox->getController()->setValue(MutableString(model->getId()));
				onEditEntity();
			} catch (Exception& exception) {
				popUps->getInfoDialogScreenController()->show(
					"Error",
					"An error occurred: " + (string(exception.what()))
				 );
			}
		} else
		if (node->getController()->getValue().getString() == "create_light") {
		} else
		if (node->getController()->getValue().getString() == "create_particlesystem") {
			try {
				auto model = TDMELevelEditor::getInstance()->getEntityLibrary()->addParticleSystem(SceneLibrary::ID_ALLOCATE, "New particle system", "");
				setEntityLibrary();
				entityLibraryListBox->getController()->setValue(MutableString(model->getId()));
				onEditEntity();
			} catch (Exception& exception) {
				popUps->getInfoDialogScreenController()->show(
					"Error",
					"An error occurred: " + (string(exception.what()))
				 );
			}
		} else {
			Console::println("LevelEditorEntityLibraryScreenController::onValueChanged: dropdown_model_create: " + node->getController()->getValue().getString());
		}
		node->getController()->setValue(MutableString("action"));
	}
}

void LevelEditorEntityLibraryScreenController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId().compare("button_entity_place") == 0) {
			onPlaceEntity();
		} else if (node->getId().compare("button_level_edit") == 0) {
			onEditLevel();
		}
	}
}
