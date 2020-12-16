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
		sceneLibraryListBox = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("entity_library_listbox"));
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
	MutableString sceneLibraryListBoxSelection;
	sceneLibraryListBoxSelection.set(entityId);
	sceneLibraryListBox->getController()->setValue(sceneLibraryListBoxSelection);
}

void LevelEditorEntityLibraryScreenController::setEntityLibrary()
{
	MutableString sceneLibraryListBoxSelection;
	auto sceneLibrary = TDMELevelEditor::getInstance()->getSceneLibrary();
	sceneLibraryListBoxSelection.set(sceneLibraryListBox->getController()->getValue());
	auto sceneLibraryListBoxInnerNode = dynamic_cast< GUIParentNode* >((sceneLibraryListBox->getScreenNode()->getNodeById(sceneLibraryListBox->getId() + "_inner")));
	auto idx = 1;
	string sceneLibraryListBoxSubNodesXML;
	sceneLibraryListBoxSubNodesXML =
		sceneLibraryListBoxSubNodesXML +
		"<scrollarea-vertical id=\"" +
		sceneLibraryListBox->getId() +
		"_inner_scrollarea\" width=\"100%\" height=\"100%\">\n";
	for (auto i = 0; i < sceneLibrary->getPrototypeCount(); i++) {
		auto prototypeId = sceneLibrary->getPrototypeAt(i)->getId();
		auto prototypeName = sceneLibrary->getPrototypeAt(i)->getName();
		sceneLibraryListBoxSubNodesXML =
			sceneLibraryListBoxSubNodesXML +
			"<selectbox-option text=\"" +
			GUIParser::escapeQuotes(prototypeName) +
			"\" value=\"" +
			to_string(prototypeId) +
			"\" " +
			(i == 0 ? "selected=\"true\" " : "") +
			"/>\n";
	}
	sceneLibraryListBoxSubNodesXML = sceneLibraryListBoxSubNodesXML + "</scrollarea-vertical>\n";
	try {
		sceneLibraryListBoxInnerNode->replaceSubNodes(sceneLibraryListBoxSubNodesXML, false);
	} catch (Exception& exception) {
		Console::print(string("LevelEditorEntityLibraryScreenController::setEntityLibrary(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	if (sceneLibraryListBoxSelection.length() > 0) {
		sceneLibraryListBox->getController()->setValue(sceneLibraryListBoxSelection);
	}
	onEntitySelectionChanged();
	buttonEntityPlace->getController()->setDisabled(sceneLibrary->getPrototypeCount() == 0);
}

void LevelEditorEntityLibraryScreenController::onEntitySelectionChanged()
{
	auto view = TDMELevelEditor::getInstance()->getView();
	if (dynamic_cast< LevelEditorView* >(view) != nullptr) {
		auto prototype = TDMELevelEditor::getInstance()->getSceneLibrary()->getPrototype(Tools::convertToIntSilent(sceneLibraryListBox->getController()->getValue().getString()));
		if (prototype != nullptr) {
			(dynamic_cast< LevelEditorView* >(view))->selectPrototypeFromLibrary(prototype->getId());
		}
	}
}

void LevelEditorEntityLibraryScreenController::onEditEntity()
{
	auto prototype = TDMELevelEditor::getInstance()->getSceneLibrary()->getPrototype(Tools::convertToIntSilent(sceneLibraryListBox->getController()->getValue().getString()));
	if (prototype == nullptr) return;
	{
		auto v = prototype->getType();
		if (v == Prototype_Type::MODEL) {
			if (dynamic_cast<ModelEditorView*>(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToModelEditor();
			}
			(dynamic_cast<ModelEditorView*>(TDMELevelEditor::getInstance()->getView()))->setPrototype(prototype);
		} else
		if (v == Prototype_Type::TRIGGER) {
			if (dynamic_cast<TriggerView*>(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToTriggerView();
			}
			(dynamic_cast<TriggerView*>(TDMELevelEditor::getInstance()->getView()))->setPrototype(prototype);
		} else
		if (v == Prototype_Type::ENVIRONMENTMAPPING) {
			if (dynamic_cast<EnvironmentMappingView*>(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToEnvironmentMappingView();
			}
			(dynamic_cast<EnvironmentMappingView*>(TDMELevelEditor::getInstance()->getView()))->setPrototype(prototype);
		} else
		if (v == Prototype_Type::EMPTY) {
			if (dynamic_cast< EmptyView* >(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToEmptyView();
			}
			(dynamic_cast< EmptyView* >(TDMELevelEditor::getInstance()->getView()))->setPrototype(prototype);
		} else
		if (v == Prototype_Type::PARTICLESYSTEM) {
			if (dynamic_cast<ParticleSystemView*>(TDMELevelEditor::getInstance()->getView()) != nullptr == false) {
				TDMELevelEditor::getInstance()->switchToParticleSystemView();
			}
			(dynamic_cast<ParticleSystemView*>(TDMELevelEditor::getInstance()->getView()))->setPrototype(prototype);
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
	auto prototype = TDMELevelEditor::getInstance()->getSceneLibrary()->getPrototype(Tools::convertToIntSilent(sceneLibraryListBox->getController()->getValue().getString()));
	if (prototype == nullptr) return;
	auto view = TDMELevelEditor::getInstance()->getView();
	if (dynamic_cast< LevelEditorView* >(view) != nullptr) {
		(dynamic_cast< LevelEditorView* >(view))->setPlaceEntityMode();
	}
}

void LevelEditorEntityLibraryScreenController::onDeleteEntity()
{
	auto prototype = TDMELevelEditor::getInstance()->getSceneLibrary()->getPrototype(Tools::convertToIntSilent(sceneLibraryListBox->getController()->getValue().getString()));
	if (prototype == nullptr) return;
	TDMELevelEditor::getInstance()->getScene()->removeEntitiesByPrototypeId(prototype->getId());
	auto view = TDMELevelEditor::getInstance()->getView();
	if (dynamic_cast< LevelEditorView* >(view) != nullptr) {
		(dynamic_cast< LevelEditorView* >(view))->loadScene();
	} else {
		TDMELevelEditor::getInstance()->switchToLevelEditor();
	}
	TDMELevelEditor::getInstance()->getScene()->getLibrary()->removePrototype(prototype->getId());
	setEntityLibrary();
}

void LevelEditorEntityLibraryScreenController::onPartitionEntity()
{
	// check if we have a entity
	auto prototype = TDMELevelEditor::getInstance()->getSceneLibrary()->getPrototype(Tools::convertToIntSilent(sceneLibraryListBox->getController()->getValue().getString()));
	if (prototype == nullptr || prototype->getType() != Prototype_Type::MODEL) return;
	// TODO: there can always be the tdme default animation, do not do skinned objects
	if (/*entity->getModel()->hasAnimations() == true || */prototype->getModel()->hasSkinning() == true) {
		popUps->getInfoDialogScreenController()->show("Warning", "This model has animations or skinning");
		return;
	}

	// check if entity exists only once
	vector<string> entitiesByPrototypeId;
	TDMELevelEditor::getInstance()->getScene()->getEntitiesByPrototypeId(prototype->getId(), entitiesByPrototypeId);
	if (entitiesByPrototypeId.size() != 1) {
		popUps->getInfoDialogScreenController()->show("Warning", "This model has several instances");
		return;
	}

	//
	auto scene = TDMELevelEditor::getInstance()->getScene();
	auto sceneLibrary = scene->getLibrary();
	auto sceneEntity = scene->getEntity(entitiesByPrototypeId[0]);

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
		auto pathName = Tools::getPath(prototype->getModelFileName());
		auto fileName = Tools::getFileName(prototype->getModelFileName());
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
			auto prototypePartition = sceneLibrary->addModel(
				SceneLibrary::ID_ALLOCATE,
				model->getName(),
				model->getName(),
				pathName,
				fileNamePartition,
				Vector3(0.0f, 0.0f, 0.0f)
			);
			prototypePartition->setShader(prototype->getShader());
			prototypePartition->setDistanceShader(prototype->getDistanceShader());
			prototypePartition->setDistanceShaderDistance(prototype->getDistanceShaderDistance());

			// avoid name collision
			auto sceneEntityName = model->getName();
			while (scene->getEntity(sceneEntityName) != nullptr) {
				sceneEntityName+= ".p";
			}

			// add to scene
			auto sceneEntityPartition = new SceneEntity(
				sceneEntityName,
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
	scene->removeEntitiesByPrototypeId(prototype->getId());
	// TODO: check if to delete original model
	//	as long as .tl has not been saved it is still required to have this file
	// FileSystem::getInstance()->removeFile(pathName, fileName);

	// (re-)load scene editor view
	auto view = TDMELevelEditor::getInstance()->getView();
	if (dynamic_cast< LevelEditorView* >(view) != nullptr) {
		(dynamic_cast< LevelEditorView* >(view))->loadScene();
	} else {
		TDMELevelEditor::getInstance()->switchToLevelEditor();
	}

	// remove prototype from scene prototype library
	// TODO: delete file
	scene->getLibrary()->removePrototype(prototype->getId());

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
						auto prototype = sceneLibrary->addModel(
							SceneLibrary::ID_ALLOCATE,
							prototypeLibraryScreenController->popUps->getFileDialogScreenController()->getFileName(),
							"",
							prototypeLibraryScreenController->popUps->getFileDialogScreenController()->getPathName(),
							prototypeLibraryScreenController->popUps->getFileDialogScreenController()->getFileName(),
							Vector3(0.0f, 0.0f, 0.0f)
						);
						prototype->setDefaultBoundingVolumes();
						prototypeLibraryScreenController->setEntityLibrary();
						prototypeLibraryScreenController->sceneLibraryListBox->getController()->setValue(MutableString(prototype->getId()));
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
				 * @param prototypeLibraryScreenController scene editor scene prototype library screen controller
				 * @param sceneLibrary scene prototype library
				 */
				OnCreateModel(LevelEditorEntityLibraryScreenController* prototypeLibraryScreenController, SceneLibrary* sceneLibrary)
					: prototypeLibraryScreenController(prototypeLibraryScreenController)
					, sceneLibrary(sceneLibrary) {
				}

			private:
				LevelEditorEntityLibraryScreenController *prototypeLibraryScreenController;
				SceneLibrary* sceneLibrary;
			};

			auto const sceneLibrary = TDMELevelEditor::getInstance()->getSceneLibrary();
			vector<string> extensions = ModelReader::getModelExtensions();
			extensions.push_back("tmm");
			popUps->getFileDialogScreenController()->show(
				modelPath,
				"Load from: ",
				extensions,
				"",
				true,
				new OnCreateModel(this, sceneLibrary)
			);
		} else
		if (node->getController()->getValue().getString() == "create_trigger") {
			try {
				auto prototype = TDMELevelEditor::getInstance()->getSceneLibrary()->addTrigger(SceneLibrary::ID_ALLOCATE, "New trigger", "", 1.0f, 1.0f, 1.0f);
				setEntityLibrary();
				sceneLibraryListBox->getController()->setValue(MutableString(prototype->getId()));
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
				auto prototype = TDMELevelEditor::getInstance()->getSceneLibrary()->addEnvironmentMapping(SceneLibrary::ID_ALLOCATE, "New environment mapping", "", 1.0f, 1.0f, 1.0f);
				setEntityLibrary();
				sceneLibraryListBox->getController()->setValue(MutableString(prototype->getId()));
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
				auto prototype = TDMELevelEditor::getInstance()->getSceneLibrary()->addEmpty(SceneLibrary::ID_ALLOCATE, "New empty", "");
				setEntityLibrary();
				sceneLibraryListBox->getController()->setValue(MutableString(prototype->getId()));
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
				auto prototype = TDMELevelEditor::getInstance()->getSceneLibrary()->addParticleSystem(SceneLibrary::ID_ALLOCATE, "New particle system", "");
				setEntityLibrary();
				sceneLibraryListBox->getController()->setValue(MutableString(prototype->getId()));
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
