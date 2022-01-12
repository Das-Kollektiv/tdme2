#include <tdme/tools/editor/tabcontrollers/TerrainEditorTabController.h>

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeTerrain.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextureNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/TerrainEditorTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Terrain2.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::tools::editor::tabcontrollers::TerrainEditorTabController;

using std::array;
using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeTerrain;
using tdme::engine::Engine;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextureNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TerrainEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;
using tdme::utilities::Terrain2;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

TerrainEditorTabController::TerrainEditorTabController(TerrainEditorTabView* view)
{
	this->view = view;
	this->basePropertiesSubController = new BasePropertiesSubController(view->getEditorView(), "terrain");
	this->popUps = view->getPopUps();
	this->currentTerrainBrushTextureFileName = "resources/engine/textures/terrain_brush_soft.png";
	this->currentTerrainBrushTexture = TextureReader::read(Tools::getPathName(currentTerrainBrushTextureFileName), Tools::getFileName(currentTerrainBrushTextureFileName), false, false);
	this->rampTerrainBrushTexture = TextureReader::read("./resources/engine/textures", "terrain_ramp.png", false, false);
}

TerrainEditorTabController::~TerrainEditorTabController() {
	delete basePropertiesSubController;
}

TerrainEditorTabView* TerrainEditorTabController::getView() {
	return view;
}

GUIScreenNode* TerrainEditorTabController::getScreenNode()
{
	return screenNode;
}

void TerrainEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	basePropertiesSubController->initialize(screenNode);
	view->setBrush(currentTerrainBrushOperation == Terrain2::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
}

void TerrainEditorTabController::dispose()
{
}

void TerrainEditorTabController::save()
{
	//
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	//
	try {
		if (prototype->getFileName().empty() == true) throw ExceptionBase("Could not save file. No filename known");
		view->saveFile(
			Tools::getPathName(prototype->getFileName()),
			Tools::getFileName(prototype->getFileName())
		);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void TerrainEditorTabController::saveAs()
{
	class OnModelSave: public virtual Action
	{
	public:
		void performAction() override {
			try {
				modelEditorTabController->view->saveFile(
					modelEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
					modelEditorTabController->popUps->getFileDialogScreenController()->getFileName()
				);
			} catch (Exception& exception) {
				modelEditorTabController->showErrorPopUp("Warning", (string(exception.what())));
			}
			modelEditorTabController->popUps->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 */
		OnModelSave(TerrainEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
		}

	private:
		TerrainEditorTabController* modelEditorTabController;
	};

	//
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	//
	popUps->getFileDialogScreenController()->show(
		prototype->getFileName().empty() == false?Tools::getPathName(prototype->getFileName()):string(),
		"Save to: ",
		{{ "tterrain" }},
		Tools::getFileName(prototype->getFileName()),
		false,
		new OnModelSave(this)
	);
}

void TerrainEditorTabController::updateInfoText(const MutableString& text) {
	required_dynamic_cast<GUITextNode*>(screenNode->getNodeById(view->getTabId() + "_tab_text_info"))->setText(text);
}

void TerrainEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void TerrainEditorTabController::onValueChanged(GUIElementNode* node)
{
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		updateDetails(outlinerNode);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_terrain_add") == true) {
		currentTerrainBrushOperation = Terrain2::BRUSHOPERATION_ADD;
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setBrush(currentTerrainBrushOperation == Terrain2::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_terrain_substract") == true) {
		currentTerrainBrushOperation = Terrain2::BRUSHOPERATION_SUBTRACT;
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setBrush(currentTerrainBrushOperation == Terrain2::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_terrain_flatten") == true) {
		currentTerrainBrushOperation = Terrain2::BRUSHOPERATION_FLATTEN;
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setBrush(currentTerrainBrushOperation == Terrain2::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_terrain_smooth") == true) {
		currentTerrainBrushOperation = Terrain2::BRUSHOPERATION_SMOOTH;
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setBrush(currentTerrainBrushOperation == Terrain2::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_terrain_ramp") == true) {
		currentTerrainBrushOperation = Terrain2::BRUSHOPERATION_RAMP;
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setBrush(currentTerrainBrushOperation == Terrain2::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_terrain_delete") == true) {
		currentTerrainBrushOperation = Terrain2::BRUSHOPERATION_DELETE;
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setBrush(currentTerrainBrushOperation == Terrain2::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_water_water") == true) {
		currentTerrainBrushOperation = Terrain2::BRUSHOPERATION_WATER_ADD;
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.waters");
		updateDetails("terrain.waters");
		view->unsetBrush();
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_water_delete") == true) {
		currentTerrainBrushOperation = Terrain2::BRUSHOPERATION_WATER_DELETE;
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.waters");
		updateDetails("terrain.waters");
		view->unsetBrush();
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_foliage_add") == true) {
		currentTerrainBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_ADD;
		view->unsetBrush();
		setFoliageBrush();
		updateFoliageBrush();
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_foliage_delete") == true) {
		currentTerrainBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_DELETE;
		view->unsetBrush();
		setFoliageBrush();
		updateFoliageBrush();
	} else {
		for (auto& textureBrushApplyNode: textureBrushApplyNodes) {
			if (node->getId() == textureBrushApplyNode) {
				applyTerrainBrushDetails();
				break;
			}
		}
		for (auto& foliageBrushApplyNode: foliageBrushApplyNodes) {
			if (node->getId() == foliageBrushApplyNode) {
				applyFoliageBrushDetails();
				updateFoliageBrush();
				break;
			}
		}
		for (auto& foliageBrushPrototypeApplyNode: foliageBrushPrototypeApplyNodes) {
			if (node->getId() == foliageBrushPrototypeApplyNode) {
				applyFoliageBrushPrototypeDetails();
				updateFoliageBrush();
				break;
			}
		}
	}
	basePropertiesSubController->onValueChanged(node, view->getPrototype());
}

void TerrainEditorTabController::onFocus(GUIElementNode* node) {
	basePropertiesSubController->onFocus(node, view->getPrototype());
}

void TerrainEditorTabController::onUnfocus(GUIElementNode* node) {
	basePropertiesSubController->onUnfocus(node, view->getPrototype());
}

void TerrainEditorTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "terrain.waters.") == true) {
			// clear
			popUps->getContextMenuScreenController()->clear();
			// delete
			class OnTerrainWaterDelete: public virtual Action
			{
			public:
				void performAction() override {
					auto outlinerNode = terrainEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection();
					auto waterIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.waters.").size(), outlinerNode.size()));
					terrainEditorTabController->deleteWater(waterIdx);
					//
					class ReloadOutlinerAction: public Action {
					public:
						void performAction() override {
							terrainEditorTabController->view->getEditorView()->reloadTabOutliner("terrain.waters");
						}
						ReloadOutlinerAction(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
						}
					private:
						TerrainEditorTabController* terrainEditorTabController;
					};
					Engine::getInstance()->enqueueAction(new ReloadOutlinerAction(terrainEditorTabController));
				}
				OnTerrainWaterDelete(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
				}
			private:
				TerrainEditorTabController* terrainEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Delete Water", "contextmenu_delete", new OnTerrainWaterDelete(this));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (outlinerNode == "terrain.foliage") {
			// clear
			popUps->getContextMenuScreenController()->clear();
			// add
			class OnTerrainFoliageAddBrush: public virtual Action
			{
			public:
				void performAction() override {
					auto prototype = terrainEditorTabController->view->getPrototype();
					auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
					if (terrain == nullptr) return;
					auto brush = terrain->addBrush();
					//
					class ReloadOutlinerAction: public Action {
					public:
						void performAction() override {
							string outlinerNode = "terrain.foliage";
							auto prototype = terrainEditorTabController->view->getPrototype();
							auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
							if (terrain != nullptr) outlinerNode = "terrain.foliage." + to_string(terrain->getBrushes().size() - 1);
							terrainEditorTabController->view->getEditorView()->reloadTabOutliner(outlinerNode);
						}
						ReloadOutlinerAction(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
						}
					private:
						TerrainEditorTabController* terrainEditorTabController;
					};
					Engine::getInstance()->enqueueAction(new ReloadOutlinerAction(terrainEditorTabController));
				}
				OnTerrainFoliageAddBrush(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
				}
			private:
				TerrainEditorTabController* terrainEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Add Foliage Brush", "contextmenu_add", new OnTerrainFoliageAddBrush(this));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (StringTools::startsWith(outlinerNode, "terrain.foliagebrushes.") == true) {
			// clear
			popUps->getContextMenuScreenController()->clear();

			// delete
			class OnTerrainDeleteFoliageBrush: public virtual Action
			{
			public:
				void performAction() override {
					auto outlinerNode = terrainEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection();
					auto foliageBrushIdx = -1;
					auto foliageBrushPrototypeIdx = -1;
					if (terrainEditorTabController->checkOutlinerFoliageBrushPrototype(outlinerNode, foliageBrushIdx, foliageBrushPrototypeIdx) == false) return;
					auto prototype = terrainEditorTabController->view->getPrototype();
					auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
					if (terrain == nullptr) return;
					auto brush = terrain->getBrush(foliageBrushIdx);
					brush->removePrototype(foliageBrushPrototypeIdx);
					auto newOutlinerNode = "terrain.brushes." + to_string(foliageBrushIdx);

					//
					class ReloadOutlinerAction: public Action {
					public:
						void performAction() override {
							terrainEditorTabController->view->getEditorView()->reloadTabOutliner(outlinerNode);
						}
						ReloadOutlinerAction(TerrainEditorTabController* terrainEditorTabController, const string& outlinerNode): terrainEditorTabController(terrainEditorTabController), outlinerNode(outlinerNode) {
						}
					private:
						TerrainEditorTabController* terrainEditorTabController;
						string outlinerNode;
					};
					Engine::getInstance()->enqueueAction(new ReloadOutlinerAction(terrainEditorTabController, newOutlinerNode));
				}
				OnTerrainDeleteFoliageBrush(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
				}
			private:
				TerrainEditorTabController* terrainEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Delete Foliage Brush Prototype", "contextmenu_delete", new OnTerrainDeleteFoliageBrush(this));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == true) {
			// clear
			popUps->getContextMenuScreenController()->clear();


			// add prototype
			class OnTerrainAddFoliageBrushPrototype: public virtual Action
			{
			public:
				void performAction() override {
					auto outlinerNode = terrainEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection();
					if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == false) return;
					auto foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.foliage.").size(), outlinerNode.size()));
					auto prototype = terrainEditorTabController->view->getPrototype();
					auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
					if (terrain == nullptr) return;
					auto brush = terrain->getBrush(foliageBrushIdx);
					if (brush == nullptr) return;
					auto brushPrototype = brush->addPrototype();
					auto newOutlinerNode = "terrain.foliagebrushes." + to_string(foliageBrushIdx) + "." + to_string(brush->getPrototypes().size() - 1);

					//
					class ReloadOutlinerAction: public Action {
					public:
						void performAction() override {
							terrainEditorTabController->view->getEditorView()->reloadTabOutliner(outlinerNode);
						}
						ReloadOutlinerAction(TerrainEditorTabController* terrainEditorTabController, const string& outlinerNode): terrainEditorTabController(terrainEditorTabController), outlinerNode(outlinerNode) {
						}
					private:
						TerrainEditorTabController* terrainEditorTabController;
						string outlinerNode;
					};
					Engine::getInstance()->enqueueAction(new ReloadOutlinerAction(terrainEditorTabController, newOutlinerNode));
				}
				OnTerrainAddFoliageBrushPrototype(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
				}
			private:
				TerrainEditorTabController* terrainEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Add Foliage Prototype", "contextmenu_add", new OnTerrainAddFoliageBrushPrototype(this));


			// delete
			class OnTerrainDeleteFoliageBrush: public virtual Action
			{
			public:
				void performAction() override {
					auto outlinerNode = terrainEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection();
					if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == false) return;
					auto foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.foliage.").size(), outlinerNode.size()));
					auto prototype = terrainEditorTabController->view->getPrototype();
					auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
					if (terrain == nullptr) return;
					terrain->removeBrush(foliageBrushIdx);

					//
					class ReloadOutlinerAction: public Action {
					public:
						void performAction() override {
							terrainEditorTabController->view->getEditorView()->reloadTabOutliner("terrain.foliage");
						}
						ReloadOutlinerAction(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
						}
					private:
						TerrainEditorTabController* terrainEditorTabController;
					};
					Engine::getInstance()->enqueueAction(new ReloadOutlinerAction(terrainEditorTabController));
				}
				OnTerrainDeleteFoliageBrush(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
				}
			private:
				TerrainEditorTabController* terrainEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Delete Foliage Brush", "contextmenu_delete", new OnTerrainDeleteFoliageBrush(this));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		}
	}
	basePropertiesSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
}

void TerrainEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == "terrain_create") {
			onCreateTerrain();
		} else
		if (node->getId() == "foliagebrush_texture_open") {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == false) return;
			auto foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.foliage.").size(), outlinerNode.size()));
			auto prototype = view->getPrototype();
			auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
			if (terrain == nullptr) return;
			auto brush = terrain->getBrush(foliageBrushIdx);
			if (brush == nullptr) return;

			//
			class OnFoliageBrushFileOpenAction: public virtual Action
			{
			public:
				void performAction() override {
					auto outlinerNode = terrainEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection();
					if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == false) return;
					auto foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.foliage.").size(), outlinerNode.size()));
					auto prototype = terrainEditorTabController->view->getPrototype();
					auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
					if (terrain == nullptr) return;
					auto brush = terrain->getBrush(foliageBrushIdx);
					if (brush == nullptr) return;
					brush->setFileName(
						terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
						"/" +
						terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
					);
					required_dynamic_cast<GUIImageNode*>(terrainEditorTabController->screenNode->getNodeById("foliagebrush_texture"))->setSource(brush->getFileName());
					terrainEditorTabController->updateFoliageBrush();
					terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
				}

				/**
				 * Public constructor
				 * @param terrainEditorTabController terrain editor tab controller
				 */
				OnFoliageBrushFileOpenAction(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
				}

			private:
				TerrainEditorTabController* terrainEditorTabController;
			};

			vector<string> extensions = TextureReader::getTextureExtensions();
			view->getPopUps()->getFileDialogScreenController()->show(
				brush->getFileName().empty() == false?Tools::getPathName(brush->getFileName()):string(),
				"Load foliage brush texture from: ",
				extensions,
				Tools::getFileName(brush->getFileName()),
				true,
				new OnFoliageBrushFileOpenAction(this)
			);
		} else
		if (node->getId() == "foliagebrush_texture_remove") {
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == false) return;
			auto foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.foliage.").size(), outlinerNode.size()));
			auto prototype = view->getPrototype();
			auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
			if (terrain == nullptr) return;
			auto brush = terrain->getBrush(foliageBrushIdx);
			if (brush == nullptr) return;
			brush->setFileName(string());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("foliagebrush_texture"))->setSource(brush->getFileName());
			updateFoliageBrush();
		} else
		if (node->getId() == "foliagebrush_texture_browseto") {

		} else
		if (node->getId() == "foliagebrush_prototype_file_open") {
			class OnTerrainBrushPrototypeFileOpenAction: public virtual Action
			{
			public:
				void performAction() override {
					auto prototype = terrainEditorTabController->view->getPrototype();
					auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
					if (terrain == nullptr) return;

					auto outlinerNode = terrainEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection();
					auto foliageBrushIdx = -1;
					auto foliageBrushPrototypeIdx = -1;
					if (terrainEditorTabController->checkOutlinerFoliageBrushPrototype(outlinerNode, foliageBrushIdx, foliageBrushPrototypeIdx) == false) return;
					auto brush = terrain->getBrush(foliageBrushIdx);
					if (brush == nullptr) return;
					auto brushPrototype = brush->getPrototype(foliageBrushPrototypeIdx);
					brushPrototype->setFileName(
						terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
						"/" +
						terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
					);
					try {
						required_dynamic_cast<GUIImageNode*>(terrainEditorTabController->screenNode->getNodeById("foliagebrush_prototype_file"))->setSource(brushPrototype->getFileName());
					} catch (Exception& exception) {
						Console::println(string("OnTerrainBrushPrototypeFileOpenAction::performAction(): ") + exception.what());
					}
					terrainEditorTabController->updateFoliageBrush();
					terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
				}

				/**
				 * Public constructor
				 * @param terrainEditorTabController terrain editor tab controller
				 */
				OnTerrainBrushPrototypeFileOpenAction(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
				}

			private:
				TerrainEditorTabController* terrainEditorTabController;
			};

			auto prototype = view->getPrototype();
			auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
			if (terrain == nullptr) return;

			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			auto foliageBrushIdx = -1;
			auto foliageBrushPrototypeIdx = -1;
			if (checkOutlinerFoliageBrushPrototype(outlinerNode, foliageBrushIdx, foliageBrushPrototypeIdx) == false) return;
			auto brush = terrain->getBrush(foliageBrushIdx);
			if (brush == nullptr) return;
			auto brushPrototype = brush->getPrototype(foliageBrushPrototypeIdx);
			if (brushPrototype == nullptr) return;

			vector<string> extensions = {"tmodel"};
			view->getPopUps()->getFileDialogScreenController()->show(
				brushPrototype->getFileName().empty() == false?Tools::getPathName(brushPrototype->getFileName()):string(),
				"Load terrain brush texture from: ",
				extensions,
				Tools::getFileName(brushPrototype->getFileName()),
				true,
				new OnTerrainBrushPrototypeFileOpenAction(this)
			);
		} else
		if (node->getId() == "foliagebrush_prototype_file_remove") {
			auto prototype = view->getPrototype();
			auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
			if (terrain == nullptr) return;

			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			auto foliageBrushIdx = -1;
			auto foliageBrushPrototypeIdx = -1;
			if (checkOutlinerFoliageBrushPrototype(outlinerNode, foliageBrushIdx, foliageBrushPrototypeIdx) == false) return;
			auto brush = terrain->getBrush(foliageBrushIdx);
			if (brush == nullptr) return;
			auto brushPrototype = brush->getPrototype(foliageBrushPrototypeIdx);
			if (brushPrototype == nullptr) return;
			brushPrototype->setFileName(string());
			updateFoliageBrush();
			try {
				required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("foliagebrush_prototype_file"))->setSource(brushPrototype->getFileName());
			} catch (Exception& exception) {
				Console::println(string("TerrainEditorTabController::onActionPerformed(): ") + exception.what());
			}
		} else
		if (node->getId() == "terrainbrush_texture_open") {
			class OnTerrainBrushFileOpenAction: public virtual Action
			{
			public:
				void performAction() override {
					if (terrainEditorTabController->currentTerrainBrushTexture != nullptr) terrainEditorTabController->currentTerrainBrushTexture->releaseReference();
					terrainEditorTabController->currentTerrainBrushTexture = nullptr;
					terrainEditorTabController->currentTerrainBrushTextureFileName =
						terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
						"/" +
						terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName();
					terrainEditorTabController->currentTerrainBrushTexture =
						TextureReader::read(
							Tools::getPathName(terrainEditorTabController->currentTerrainBrushTextureFileName),
							Tools::getFileName(terrainEditorTabController->currentTerrainBrushTextureFileName),
							false,
							false
						);
					required_dynamic_cast<GUITextureNode*>(terrainEditorTabController->screenNode->getNodeById("terrainbrush_texture"))->setTexture(terrainEditorTabController->currentTerrainBrushTexture);
					terrainEditorTabController->view->setBrush(
						terrainEditorTabController->currentTerrainBrushTexture,
						terrainEditorTabController->currentTerrainBrushScale,
						terrainEditorTabController->currentTerrainBrushStrength
					);
					terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
				}

				/**
				 * Public constructor
				 * @param terrainEditorTabController terrain editor tab controller
				 */
				OnTerrainBrushFileOpenAction(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
				}

			private:
				TerrainEditorTabController* terrainEditorTabController;
			};

			vector<string> extensions = TextureReader::getTextureExtensions();
			view->getPopUps()->getFileDialogScreenController()->show(
				currentTerrainBrushTextureFileName.empty() == false?Tools::getPathName(currentTerrainBrushTextureFileName):string(),
				"Load terrain brush texture from: ",
				extensions,
				Tools::getFileName(currentTerrainBrushTextureFileName),
				true,
				new OnTerrainBrushFileOpenAction(this)
			);
		} else
		if (node->getId() == "terrainbrush_texture_remove") {
			if (currentTerrainBrushTexture != nullptr) currentTerrainBrushTexture->releaseReference();
			currentTerrainBrushTexture = nullptr;
			required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("terrainbrush_texture"))->setTexture(currentTerrainBrushTexture);
		} else
		if (node->getId() == "terrainbrush_texture_browseto") {
		} else
		if (node->getId() == "terrain_mirrormode_apply") {
			auto prototype = view->getPrototype();
			auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
			if (terrain == nullptr) return;
			auto mirrorMode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrain_mirrormode"))->getController()->getValue().getString();
			auto flipped = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrain_mirrormode_flipped"))->getController()->getValue().getString() == "1";
			view->reset();
			if (mirrorMode == "1") {
				// no op
			} else
			if (mirrorMode == "2") {
				Terrain2::mirrorXAxis(
					flipped,
					terrain->getWidth(),
					terrain->getDepth(),
					terrain->getHeightVector(),
					terrain->getWaterPositionMapsHeight(),
					terrain->getWaterPositionMaps(),
					terrain->getFoliageMaps()
				);
				terrain->setWidth(terrain->getWidth() * 2.0f);
			} else
			if (mirrorMode == "3") {
				Terrain2::mirrorZAxis(
					flipped,
					terrain->getWidth(),
					terrain->getDepth(),
					terrain->getHeightVector(),
					terrain->getWaterPositionMapsHeight(),
					terrain->getWaterPositionMaps(),
					terrain->getFoliageMaps()
				);
				terrain->setDepth(terrain->getDepth() * 2.0f);
			} else
			if (mirrorMode == "4") {
				Terrain2::mirrorXAxis(
					flipped,
					terrain->getWidth(),
					terrain->getDepth(),
					terrain->getHeightVector(),
					terrain->getWaterPositionMapsHeight(),
					terrain->getWaterPositionMaps(),
					terrain->getFoliageMaps()
				);
				terrain->setWidth(terrain->getWidth() * 2.0f);
				Terrain2::mirrorZAxis(
					flipped,
					terrain->getWidth(),
					terrain->getDepth(),
					terrain->getHeightVector(),
					terrain->getWaterPositionMapsHeight(),
					terrain->getWaterPositionMaps(),
					terrain->getFoliageMaps()
				);
				terrain->setDepth(terrain->getDepth() * 2.0f);
			}
			view->initializeTerrain();
		}
	}
	basePropertiesSubController->onActionPerformed(type, node, view->getPrototype());
}

void TerrainEditorTabController::setOutlinerContent() {
	auto prototype = view->getPrototype();
	auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Terrain") + "\" value=\"" + GUIParser::escapeQuotes("terrain") + "\">\n";
	basePropertiesSubController->createBasePropertiesXML(view->getPrototype(), xml);
	xml+= "<selectbox-option image=\"resources/engine/images/terrain.png\" text=\"" + GUIParser::escapeQuotes("Terrain Brush") + "\" value=\"" + GUIParser::escapeQuotes("terrain.brush") + "\" />\n";
	if (terrain != nullptr && terrain->getWaterPositionMapsIndices().empty() == false) {
		xml+= "<selectbox-parent-option image=\"resources/engine/images/terrain_water.png\" text=\"" + GUIParser::escapeQuotes("Water") + "\" value=\"" + GUIParser::escapeQuotes("terrain.waters") + "\">\n";
		auto i = 0;
		for (auto waterIdx: terrain->getWaterPositionMapsIndices()) {
			xml+= "<selectbox-option image=\"resources/engine/images/terrain_water.png\" text=\"" + GUIParser::escapeQuotes("Water " + to_string(i)) + "\" value=\"" + GUIParser::escapeQuotes("terrain.waters." + to_string(waterIdx)) + "\" />\n";
			i++;
		}
		xml+= "</selectbox-parent-option>\n";
	} else {
		xml+= "<selectbox-option image=\"resources/engine/images/terrain_water.png\" text=\"" + GUIParser::escapeQuotes("Water") + "\" value=\"" + GUIParser::escapeQuotes("terrain.waters") + "\" />\n";
	}
	if (terrain != nullptr && terrain->getBrushes().empty() == false) {
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Foliage") + "\" value=\"" + GUIParser::escapeQuotes("terrain.foliage") + "\">\n";
		auto i = 0;
		for (auto brush: terrain->getBrushes()) {
			if (brush->getPrototypes().empty() == false) {
				xml+= "<selectbox-parent-option image=\"resources/engine/images/foliage.png\" text=\"" + GUIParser::escapeQuotes("Foliage Brush " + to_string(i)) + "\" value=\"" + GUIParser::escapeQuotes("terrain.foliage." + to_string(i)) + "\" >\n";
				auto j = 0;
				for (auto brushPrototype: brush->getPrototypes()) {
					xml+= "<selectbox-option image=\"resources/engine/images/mesh.png\" text=\"" + GUIParser::escapeQuotes("Prototype " + to_string(j)) + "\" value=\"" + GUIParser::escapeQuotes("terrain.foliagebrushes." + to_string(i) + "." + to_string(j)) + "\" />\n";
					j++;
				}
				xml+= "</selectbox-parent-option>\n";
			} else {
				xml+= "<selectbox-option image=\"resources/engine/images/foliage.png\" text=\"" + GUIParser::escapeQuotes("Foliage Brush " + to_string(i)) + "\" value=\"" + GUIParser::escapeQuotes("terrain.foliage." + to_string(i)) + "\" />\n";
			}
			i++;
		}
		xml+= "</selectbox-parent-option>\n";
	} else {
		xml+= "<selectbox-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Foliage") + "\" value=\"" + GUIParser::escapeQuotes("terrain.foliage") + "\" />\n";
	}
	auto foliagePrototypeIndices = terrain != nullptr?terrain->getFoliagePrototypeIndices():vector<int>();
	if (foliagePrototypeIndices.empty() == false) {
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Prototypes") + "\" value=\"" + GUIParser::escapeQuotes("terrain.foliageprototypes") + "\">\n";
		auto i = 0;
		for (auto prototypeIdx: foliagePrototypeIndices) {
			auto foliagePrototype = terrain->getFoliagePrototype(prototypeIdx);
			xml+= "<selectbox-option image=\"resources/engine/images/mesh.png\" text=\"" + GUIParser::escapeQuotes(Tools::removeFileEnding(Tools::getFileName(foliagePrototype->getFileName()))) + "\" value=\"" + GUIParser::escapeQuotes("terrain.foliageprototypes." + to_string(prototypeIdx)) + "\" />\n";
			i++;
		}
		xml+= "</selectbox-parent-option>\n";
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void TerrainEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(string());
}

void TerrainEditorTabController::onCreateTerrain() {
	auto prototype = view->getPrototype();
	auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
	if (terrain == nullptr) return;

	//
	try {
		view->reset();
		auto width = Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrain_size_x"))->getController()->getValue().getString());
		auto depth = Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrain_size_z"))->getController()->getValue().getString());
		if (width < 1.0f || width > 4000.0f) throw ExceptionBase("Width must be within 1 .. 4000");
		if (depth < 1.0f || depth > 4000.0f) throw ExceptionBase("Depth must be within 1 .. 4000");
		terrain->getHeightVector().clear();
		for (auto idx: terrain->getWaterPositionMapsIndices()) terrain->removeWaterPositionMap(idx);
		BoundingBox terrainBoundingBox;
		vector<Model*> terrainModels;
		Terrain2::createTerrainModels(width, depth, 0.0f, terrain->getHeightVector(), terrainBoundingBox, terrainModels);
		Terrain2::createFoliageMaps(terrainBoundingBox, terrain->getFoliageMaps());
		Terrain2::createFoliageMaps(terrainBoundingBox, newFoliageMaps);
		terrain->setWidth(terrainBoundingBox.getDimensions().getX());
		terrain->setDepth(terrainBoundingBox.getDimensions().getZ());
		view->initializeTerrain();
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}

	//
	class ReloadOutlinerAction: public Action {
	public:
		void performAction() override {
			terrainEditorTabController->view->getEditorView()->reloadTabOutliner("terrain");
		}
		ReloadOutlinerAction(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
		}
	private:
		TerrainEditorTabController* terrainEditorTabController;
	};
	Engine::getInstance()->enqueueAction(new ReloadOutlinerAction(this));
}

void TerrainEditorTabController::setBrushScale(float scale) {
	if (currentTerrainBrushOperation != Terrain2::BRUSHOPERATION_NONE) {
		currentTerrainBrushScale = scale;
		if (view->getEditorView()->getScreenController()->getOutlinerSelection() == "terrain.brush") {
			updateTerrainBrushDetails();
		}
	} else
	if (currentFoliageBrushOperation != Terrain2::BRUSHOPERATION_NONE) {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		auto foliageBrushIdx = -1;
		if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == true) {
			foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.foliage.").size(), outlinerNode.size()));
		} else {
			auto foliageBrushPrototypeIdx = -1;
			if (checkOutlinerFoliageBrushPrototype(outlinerNode, foliageBrushIdx, foliageBrushPrototypeIdx) == false) return;
		}
		auto prototype = view->getPrototype();
		auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
		if (terrain == nullptr) return;
		auto brush = terrain->getBrush(foliageBrushIdx);
		if (brush == nullptr) return;
		brush->setSize(scale);
		if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == true) updateFoliageBrushDetails();
		updateFoliageBrush();
	}
}

void TerrainEditorTabController::setBrushDensityStrength(float densityStrength) {
	if (currentTerrainBrushOperation != Terrain2::BRUSHOPERATION_NONE) {
		currentTerrainBrushStrength = densityStrength;
		if (view->getEditorView()->getScreenController()->getOutlinerSelection() == "terrain.brush") {
			updateTerrainBrushDetails();
		}
	} else
	if (currentFoliageBrushOperation != Terrain2::BRUSHOPERATION_NONE) {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		auto foliageBrushIdx = -1;
		if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == true) {
			foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.foliage.").size(), outlinerNode.size()));
		} else {
			auto foliageBrushPrototypeIdx = -1;
			if (checkOutlinerFoliageBrushPrototype(outlinerNode, foliageBrushIdx, foliageBrushPrototypeIdx) == false) return;
		}
		auto prototype = view->getPrototype();
		auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
		if (terrain == nullptr) return;
		auto brush = terrain->getBrush(foliageBrushIdx);
		if (brush == nullptr) return;
		brush->setDensity(densityStrength);
		if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == true) updateFoliageBrushDetails();
		updateFoliageBrush();
	}
}

void TerrainEditorTabController::setTerrainDetails() {
	auto prototype = view->getPrototype();
	auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
	if (terrain == nullptr) return;

	//
	view->getEditorView()->setDetailsContent(
		"<template id=\"details_terrain\" src=\"resources/engine/gui/template_details_terrain.xml\" />\n"
	);

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_terrain"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrain_size_x"))->getController()->setValue(MutableString(terrain->getWidth()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrain_size_z"))->getController()->setValue(MutableString(terrain->getDepth()));
	} catch (Exception& exception) {
		Console::println(string("TerrainEditorTabController::setTerrainDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void TerrainEditorTabController::setTerrainBrushDetails() {
	view->getEditorView()->setDetailsContent(
		"<template id=\"details_terrainbrush\" src=\"resources/engine/gui/template_details_terrainbrush.xml\" />\n"
	);

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_terrainbrush"))->getActiveConditions().add("open");
		required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("terrainbrush_texture"))->setTexture(currentTerrainBrushTexture);
	} catch (Exception& exception) {
		Console::println(string("TerrainEditorTabController::setTerrainBrushDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}

	//
	updateTerrainBrushDetails();
}

void TerrainEditorTabController::updateTerrainBrushDetails() {
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrainbrush_size"))->getController()->setValue(MutableString(currentTerrainBrushScale));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrainbrush_strength"))->getController()->setValue(MutableString(currentTerrainBrushStrength));
	} catch (Exception& exception) {
		Console::println(string("TerrainEditorTabController::updateTerrainBrushDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void TerrainEditorTabController::applyTerrainBrushDetails() {
	try {
		currentTerrainBrushScale = Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrainbrush_size"))->getController()->getValue().getString()); // TODO: a.drewke, size != scale
		currentTerrainBrushStrength = Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrainbrush_strength"))->getController()->getValue().getString());
	} catch (Exception& exception) {
		Console::println(string("TerrainEditorTabController::setTerrainBrushDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
	// TODO: a.drewke, maybe improve me
	view->setBrush(currentTerrainBrushOperation == Terrain2::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
}

void TerrainEditorTabController::setFoliageBrushDetails() {
	view->getEditorView()->setDetailsContent(
		"<template id=\"details_foliagebrush\" src=\"resources/engine/gui/template_details_foliagebrush.xml\" />\n"
	);

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_foliagebrush"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::println(string("TerrainEditorTabController::setFoliageBrushDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}

	//
	updateFoliageBrushDetails();
}

void TerrainEditorTabController::updateFoliageBrushDetails() {
	//
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == false) return;
	auto foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.foliage.").size(), outlinerNode.size()));
	auto prototype = view->getPrototype();
	auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
	if (terrain == nullptr) return;
	auto brush = terrain->getBrush(foliageBrushIdx);
	if (brush == nullptr) return;

	//
	try {
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("foliagebrush_texture"))->setSource(brush->getFileName());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_size"))->getController()->setValue(MutableString(brush->getSize()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_density"))->getController()->setValue(MutableString(brush->getDensity()));
	} catch (Exception& exception) {
		Console::println(string("TerrainEditorTabController::updateFoliageBrushDetails(): An error occurred: ") + exception.what());
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void TerrainEditorTabController::applyFoliageBrushDetails() {
	//
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == false) return;
	auto foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.foliage.").size(), outlinerNode.size()));
	auto prototype = view->getPrototype();
	auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
	if (terrain == nullptr) return;
	auto brush = terrain->getBrush(foliageBrushIdx);
	if (brush == nullptr) return;

	//
	try {
		brush->setSize(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_size"))->getController()->getValue().getString()));
		brush->setDensity(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_density"))->getController()->getValue().getString()));
	} catch (Exception& exception) {
		Console::println(string("TerrainEditorTabController::applyFoliageBrushDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void TerrainEditorTabController::setFoliageBrushPrototypeDetails() {
	view->getEditorView()->setDetailsContent(
		"<template id=\"details_foliagebrush_prototype\" src=\"resources/engine/gui/template_details_foliagebrush_prototype.xml\" />\n"
	);

	auto prototype = view->getPrototype();
	auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
	if (terrain == nullptr) return;

	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	auto foliageBrushIdx = -1;
	auto foliageBrushPrototypeIdx = -1;
	if (checkOutlinerFoliageBrushPrototype(outlinerNode, foliageBrushIdx, foliageBrushPrototypeIdx) == false) return;
	auto brush = terrain->getBrush(foliageBrushIdx);
	if (brush == nullptr) return;
	auto brushPrototype = brush->getPrototype(foliageBrushPrototypeIdx);
	if (brushPrototype == nullptr) return;

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_foliagebrush_prototype"))->getActiveConditions().add("open");

		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("foliagebrush_prototype_file"))->setSource(brushPrototype->getFileName());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_object_count"))->getController()->setValue(MutableString(brushPrototype->getCount()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_normalalign"))->getController()->setValue(MutableString(brushPrototype->isNormalAlign() == true?"1":""));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_rotationrange_x_min"))->getController()->setValue(MutableString(brushPrototype->getRotationXMin()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_rotationrange_x_max"))->getController()->setValue(MutableString(brushPrototype->getRotationXMax()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_rotationrange_y_min"))->getController()->setValue(MutableString(brushPrototype->getRotationYMin()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_rotationrange_y_max"))->getController()->setValue(MutableString(brushPrototype->getRotationYMax()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_rotationrange_z_min"))->getController()->setValue(MutableString(brushPrototype->getRotationZMin()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_rotationrange_z_max"))->getController()->setValue(MutableString(brushPrototype->getRotationZMax()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_scalerange_min"))->getController()->setValue(MutableString(brushPrototype->getScaleMin()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_scalerange_max"))->getController()->setValue(MutableString(brushPrototype->getScaleMax()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_heightrange_min"))->getController()->setValue(MutableString(brushPrototype->getHeightMin()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_heightrange_max"))->getController()->setValue(MutableString(brushPrototype->getHeightMax()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_sloperange_min"))->getController()->setValue(MutableString(brushPrototype->getSlopeMin()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_sloperange_max"))->getController()->setValue(MutableString(brushPrototype->getSlopeMax()));
	} catch (Exception& exception) {
		Console::println(string("TerrainEditorTabController::setFoliageBrushPrototypeDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void TerrainEditorTabController::applyFoliageBrushPrototypeDetails() {
	auto prototype = view->getPrototype();
	auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
	if (terrain == nullptr) return;

	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	auto foliageBrushIdx = -1;
	auto foliageBrushPrototypeIdx = -1;
	if (checkOutlinerFoliageBrushPrototype(outlinerNode, foliageBrushIdx, foliageBrushPrototypeIdx) == false) return;
	auto brush = terrain->getBrush(foliageBrushIdx);
	if (brush == nullptr) return;
	auto brushPrototype = brush->getPrototype(foliageBrushPrototypeIdx);
	if (brushPrototype == nullptr) return;

	try {
		brushPrototype->setCount(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_object_count"))->getController()->getValue().getString()));
		brushPrototype->setNormalAlign(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_normalalign"))->getController()->getValue().getString() == "1");
		brushPrototype->setRotationXMin(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_rotationrange_x_min"))->getController()->getValue().getString()));
		brushPrototype->setRotationXMax(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_rotationrange_x_max"))->getController()->getValue().getString()));
		brushPrototype->setRotationYMin(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_rotationrange_y_min"))->getController()->getValue().getString()));
		brushPrototype->setRotationYMax(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_rotationrange_y_max"))->getController()->getValue().getString()));
		brushPrototype->setRotationZMin(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_rotationrange_z_min"))->getController()->getValue().getString()));
		brushPrototype->setRotationZMax(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_rotationrange_z_max"))->getController()->getValue().getString()));
		brushPrototype->setScaleMin(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_scalerange_min"))->getController()->getValue().getString()));
		brushPrototype->setScaleMax(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_scalerange_max"))->getController()->getValue().getString()));
		brushPrototype->setHeightMin(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_heightrange_min"))->getController()->getValue().getString()));
		brushPrototype->setHeightMax(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_heightrange_max"))->getController()->getValue().getString()));
		brushPrototype->setSlopeMin(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_sloperange_min"))->getController()->getValue().getString()));
		brushPrototype->setSlopeMax(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_prototype_sloperange_max"))->getController()->getValue().getString()));
	} catch (Exception& exception) {
		Console::println(string("TerrainEditorTabController::applyFoliageBrushPrototypeDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

bool TerrainEditorTabController::checkOutlinerFoliageBrushPrototype(const string& outlinerNode, int& foliageBrushIdx, int& foliageBrushPrototypeIdx) {
	if (StringTools::startsWith(outlinerNode, "terrain.foliagebrushes.") == false) return false;
	auto brushIdxBeginIdx = string("terrain.foliagebrushes.").size();
	auto brushIdxEndIdx = outlinerNode.find('.', brushIdxBeginIdx + 1);
	auto prototypeBeginIdx = brushIdxEndIdx + 1;
	auto prototypeEndIdx = outlinerNode.size();
	foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, brushIdxBeginIdx, brushIdxEndIdx));
	foliageBrushPrototypeIdx = Integer::parse(StringTools::substring(outlinerNode, prototypeBeginIdx, prototypeEndIdx));
	return true;
}

void TerrainEditorTabController::updateDetails(const string& outlinerNode) {
	view->getEditorView()->setDetailsContent(string());
	if (outlinerNode == "terrain") {
		setTerrainDetails();
		currentTerrainBrushOperation = getUITerrainBrushOperation();
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		view->setBrush(currentTerrainBrushOperation == Terrain2::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
		required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById(view->getTabId() + "_tab_viewport"))->getActiveConditions().set("terrain");
	} else
	if (outlinerNode == "terrain.brush") {
		setTerrainBrushDetails();
		currentTerrainBrushOperation = getUITerrainBrushOperation();
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		view->unsetBrush();
		required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById(view->getTabId() + "_tab_viewport"))->getActiveConditions().set("terrain");
	} else
	if (outlinerNode == "terrain.waters" || StringTools::startsWith(outlinerNode, "terrain.waters.") == true) {
		currentTerrainBrushOperation = getUIWaterOperation();
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		view->unsetBrush();
		required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById(view->getTabId() + "_tab_viewport"))->getActiveConditions().set("water");
	} else
	if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == true) {
		setFoliageBrushDetails();
		currentTerrainBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		currentFoliageBrushOperation = getUIFoliageBrushOperation();
		updateFoliageBrush();
		required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById(view->getTabId() + "_tab_viewport"))->getActiveConditions().set("foliage");
	} else
	if (StringTools::startsWith(outlinerNode, "terrain.foliagebrushes.") == true) {
		setFoliageBrushPrototypeDetails();
		currentTerrainBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		currentFoliageBrushOperation = getUIFoliageBrushOperation();
		updateFoliageBrush();
		required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById(view->getTabId() + "_tab_viewport"))->getActiveConditions().set("foliage");
	} else {
		view->unsetBrush();
		currentTerrainBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		currentFoliageBrushOperation = Terrain2::BRUSHOPERATION_NONE;
		required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById(view->getTabId() + "_tab_viewport"))->getActiveConditions().removeAll();
		basePropertiesSubController->updateDetails(view->getPrototype(), outlinerNode);
	}
}

void TerrainEditorTabController::initializeTerrain() {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	//
	try {
		auto width = prototype->getTerrain()->getWidth();
		auto depth = prototype->getTerrain()->getDepth();
		BoundingBox terrainBoundingBox;
		vector<Model*> terrainModels;
		Terrain2::createTerrainModels(width, depth, 0.0f, prototype->getTerrain()->getHeightVector(), terrainBoundingBox, terrainModels);
		view->unsetWater();
		view->setTerrain(terrainBoundingBox, terrainModels);
		auto waterPositionMapsIndices = prototype->getTerrain()->getWaterPositionMapsIndices();
		for (auto waterPositionMapIdx: waterPositionMapsIndices) {
			vector<Model*> waterModels;
			Terrain2::createWaterModels(
				terrainBoundingBox,
				prototype->getTerrain()->getWaterPositionMap(waterPositionMapIdx),
				prototype->getTerrain()->getWaterPositionMapHeight(waterPositionMapIdx),
				waterPositionMapIdx,
				waterModels
			);
			view->addWater(
				waterPositionMapIdx,
				waterModels,
				Terrain2::computeWaterReflectionEnvironmentMappingPosition(
					prototype->getTerrain()->getWaterPositionMap(waterPositionMapIdx),
					prototype->getTerrain()->getWaterPositionMapHeight(waterPositionMapIdx)
				)
			);
		}
		view->addFoliage();
		Terrain2::createFoliageMaps(terrainBoundingBox, newFoliageMaps);
		prototype->getTerrain()->setWidth(terrainBoundingBox.getDimensions().getX());
		prototype->getTerrain()->setDepth(terrainBoundingBox.getDimensions().getZ());
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void TerrainEditorTabController::applyTerrainBrush(BoundingBox& terrainBoundingBox, vector<Model*>& terrainModels, const Vector3& brushCenterPosition, int64_t deltaTime) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;
	if (terrainModels.empty() == true) return;

	// apply brush first
	Terrain2::applyBrushToTerrainModels(
		terrainBoundingBox,
		terrainModels,
		prototype->getTerrain()->getHeightVector(),
		brushCenterPosition,
		currentTerrainBrushOperation == Terrain2::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture,
		currentTerrainBrushScale,
		currentTerrainBrushStrength * static_cast<float>(deltaTime) / 200.0f, // if strength = 1.0f it will e.g. add to level 5 meters/second
		currentTerrainBrushOperation,
		currentTerrainBrushHeight
	);

	//
	Terrain2::FoliageBrush foliageBrush = {
		foliageBrush.brushTexture = Terrain2::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture,
		foliageBrush.brushScale = currentTerrainBrushScale,
		foliageBrush.brushDensity = 1.0f
	};

	// and update foliage
	Terrain2::updateFoliageTerrainBrush(
		terrainBoundingBox,
		prototype->getTerrain()->getHeightVector(),
		brushCenterPosition,
		foliageBrush,
		prototype->getTerrain()->getFoliageMaps(),
		recreateFoliagePartitions
	);

	//
	view->updateTemporaryFoliage(recreateFoliagePartitions);
	recreateFoliagePartitions.clear();
}

bool TerrainEditorTabController::determineCurrentBrushHeight(BoundingBox& terrainBoundingBox, vector<Model*> terrainModels, const Vector3& brushCenterPosition) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return false;
	if (currentTerrainBrushOperation != Terrain2::BRUSHOPERATION_FLATTEN &&
		currentTerrainBrushOperation != Terrain2::BRUSHOPERATION_WATER_ADD &&
		currentTerrainBrushOperation != Terrain2::BRUSHOPERATION_RAMP) {
		return true;
	}
	if (haveCurrentTerrainBrushHeight == true) return true;
	if (terrainModels.empty() == true) return false;
	auto terrainModel = terrainModels[0];
	if (terrainModel == nullptr) return false;
	haveCurrentTerrainBrushHeight = Terrain2::getTerrainModelsHeight(
		terrainBoundingBox,
		terrainModels,
		prototype->getTerrain()->getHeightVector(),
		brushCenterPosition,
		currentTerrainBrushHeight
	);
	return haveCurrentTerrainBrushHeight;
}

bool TerrainEditorTabController::determineRampHeight(BoundingBox& terrainBoundingBox, vector<Model*> terrainModels, const Vector3& position, float& height) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return false;
	if (currentTerrainBrushOperation != Terrain2::BRUSHOPERATION_RAMP) {
		return false;
	}
	if (terrainModels.empty() == true) return false;
	auto terrainModel = terrainModels[0];
	if (terrainModel == nullptr) return false;
	return Terrain2::getTerrainModelsHeight(
		terrainBoundingBox,
		terrainModels,
		prototype->getTerrain()->getHeightVector(),
		position,
		height
	);
}

void TerrainEditorTabController::unsetCurrentBrushFlattenHeight() {
	haveCurrentTerrainBrushHeight = false;
}

void TerrainEditorTabController::applyRampTerrainBrush(BoundingBox& terrainBoundingBox, vector<Model*>& terrainModels, const Vector3& position, float rotation, const Vector2& scale, float minHeight, float maxHeight) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;
	if (terrainModels.empty() == true) return;

	// apply brush first
	Terrain2::applyRampBrushToTerrainModels(
		terrainBoundingBox,
		terrainModels,
		prototype->getTerrain()->getHeightVector(),
		position,
		currentTerrainBrushOperation == Terrain2::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture,
		rotation,
		scale,
		minHeight,
		maxHeight
	);

	// and update foliage
	Terrain2::updateFoliageTerrainRampBrush(
		terrainBoundingBox,
		prototype->getTerrain()->getHeightVector(),
		position,
		currentTerrainBrushOperation == Terrain2::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture,
		rotation,
		scale,
		prototype->getTerrain()->getFoliageMaps(),
		recreateFoliagePartitions
	);

	//
	view->recreateFoliage(recreateFoliagePartitions);
	recreateFoliagePartitions.clear();
}

void TerrainEditorTabController::createWater(BoundingBox& terrainBoundingBox, const Vector3& brushCenterPosition, vector<Model*>& waterModels, Vector3& waterReflectionEnvironmentMappingPosition) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;
	auto waterPositionMapIdx = prototype->getTerrain()->allocateWaterPositionMapIdx();
	prototype->getTerrain()->setWaterPositionMapHeight(waterPositionMapIdx, currentTerrainBrushHeight);
	if (Terrain2::computeWaterPositionMap(
		terrainBoundingBox,
		prototype->getTerrain()->getHeightVector(),
		brushCenterPosition,
		prototype->getTerrain()->getWaterPositionMapHeight(waterPositionMapIdx),
		prototype->getTerrain()->getWaterPositionMap(waterPositionMapIdx)) == true) {
		//
		Terrain2::createWaterModels(
			terrainBoundingBox,
			prototype->getTerrain()->getWaterPositionMap(waterPositionMapIdx),
			prototype->getTerrain()->getWaterPositionMapHeight(waterPositionMapIdx),
			waterPositionMapIdx,
			waterModels
		);
		waterReflectionEnvironmentMappingPosition = Terrain2::computeWaterReflectionEnvironmentMappingPosition(
			prototype->getTerrain()->getWaterPositionMap(waterPositionMapIdx),
			prototype->getTerrain()->getWaterPositionMapHeight(waterPositionMapIdx)
		);
		view->addWater(
			waterPositionMapIdx,
			waterModels,
			waterReflectionEnvironmentMappingPosition
		);
	}
	view->getEditorView()->reloadTabOutliner("terrain.waters." + to_string(waterPositionMapIdx));
}

void TerrainEditorTabController::deleteWater(int waterPositionMapIdx) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;
	prototype->getTerrain()->removeWaterPositionMap(waterPositionMapIdx);
	view->removeWater(waterPositionMapIdx);
	view->getEditorView()->reloadTabOutliner("terrain.waters");
}

void TerrainEditorTabController::setFoliageBrush() {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	//
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	auto foliageBrushIdx = -1;
	auto foliageBrushPrototypeIdx = -1;
	if (checkOutlinerFoliageBrushPrototype(outlinerNode, foliageBrushIdx, foliageBrushPrototypeIdx) == false) return;
	auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
	if (terrain == nullptr) return;
	auto brush = terrain->getBrush(foliageBrushIdx);
	if (brush == nullptr) return;

	// texture
	auto foliageBrushTexture = TextureReader::read(Tools::getPathName(brush->getFileName()), Tools::getFileName(brush->getFileName()), false, false);
	if (foliageBrushTexture == nullptr) return;

	//
	view->setBrush(foliageBrushTexture, brush->getSize(), brush->getDensity());
}

void TerrainEditorTabController::updateFoliageBrush() {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	//
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	auto foliageBrushIdx = -1;
	if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == true) {
		foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.foliage.").size(), outlinerNode.size()));
	} else {
		auto foliageBrushPrototypeIdx = -1;
		if (checkOutlinerFoliageBrushPrototype(outlinerNode, foliageBrushIdx, foliageBrushPrototypeIdx) == false) return;
	}

	//
	auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
	if (terrain == nullptr) return;
	auto brush = terrain->getBrush(foliageBrushIdx);
	if (brush == nullptr) return;

	//
	if (foliageBrush.brushTexture != nullptr) foliageBrush.brushTexture->releaseReference();

	//
	foliageBrush.brushTexture = TextureReader::read(Tools::getPathName(brush->getFileName()), Tools::getFileName(brush->getFileName()), false, false);
	foliageBrush.brushScale = brush->getSize();
	foliageBrush.brushDensity = brush->getDensity();
	foliageBrush.brushTexture->acquireReference();

	//
	foliageBrushPrototypes.clear();
	for (auto foliageBrushPrototype: brush->getPrototypes()) {
		Prototype* foliagePrototype = nullptr;
		if (foliageBrushPrototype->getFileName().empty() == false) {
			try {
				foliagePrototype = PrototypeReader::read(
					PrototypeReader::getResourcePathName(Tools::getPathName(foliageBrushPrototype->getFileName()), foliageBrushPrototype->getFileName()),
					Tools::getFileName(foliageBrushPrototype->getFileName())
				);
			} catch (Exception& exception) {
				Console::println("TerrainEditorTabController::updateFoliageBrush(): failed to load prototype: " + foliageBrushPrototype->getFileName());
			}
		}
		if (foliagePrototype == nullptr) continue;
		foliageBrushPrototypes.push_back(
			{
				.prototypeId = terrain->getFoliagePrototypeIndex(foliagePrototype),
				.count = foliageBrushPrototype->getCount(),
				.normalAlign = foliageBrushPrototype->isNormalAlign(),
				.rotationXMin = foliageBrushPrototype->getRotationXMin(),
				.rotationXMax = foliageBrushPrototype->getRotationXMax(),
				.rotationYMin = foliageBrushPrototype->getRotationYMin(),
				.rotationYMax = foliageBrushPrototype->getRotationYMax(),
				.rotationZMin = foliageBrushPrototype->getRotationZMin(),
				.rotationZMax = foliageBrushPrototype->getRotationZMax(),
				.scaleMin = foliageBrushPrototype->getScaleMin(),
				.scaleMax = foliageBrushPrototype->getScaleMax(),
				.heightMin = foliageBrushPrototype->getHeightMin(),
				.heightMax = foliageBrushPrototype->getHeightMax(),
				.slopeMin = foliageBrushPrototype->getSlopeMin(),
				.slopeMax = foliageBrushPrototype->getSlopeMax()
			}
		);
	}

	//
	view->setBrush(foliageBrush.brushTexture, brush->getSize(), brush->getDensity());
}

void TerrainEditorTabController::applyFoliageBrush(BoundingBox& terrainBoundingBox, const Vector3& brushCenterPosition, int64_t deltaTime) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	//
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	auto foliageBrushIdx = -1;
	if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == true) {
		foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.foliage.").size(), outlinerNode.size()));
	} else {
		auto foliageBrushPrototypeIdx = -1;
		if (checkOutlinerFoliageBrushPrototype(outlinerNode, foliageBrushIdx, foliageBrushPrototypeIdx) == false) return;
	}
	auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
	if (terrain == nullptr) return;
	auto brush = terrain->getBrush(foliageBrushIdx);
	if (brush == nullptr) return;

	// check if having brush prototypes (ids)
	if (currentFoliageBrushOperation == Terrain2::BRUSHOPERATION_ADD) {
		auto haveBrushPrototypeIds = false;
		for (auto& foliageBrushPrototype: foliageBrushPrototypes) {
			if (foliageBrushPrototype.prototypeId != -1) haveBrushPrototypeIds = true;
		}
		if (haveBrushPrototypeIds == false) return;
	}

	//
	switch(currentFoliageBrushOperation) {
		case Terrain2::BRUSHOPERATION_ADD:
			//
			Terrain2::applyFoliageDeleteBrush(
				terrainBoundingBox,
				brushCenterPosition,
				foliageBrush,
				foliageBrushPrototypes,
				Terrain2::BRUSHOPERATION_DELETE,
				prototype->getTerrain()->getFoliageMaps(),
				recreateFoliagePartitions
			);
			//
			Terrain2::applyFoliageBrush(
				terrainBoundingBox,
				prototype->getTerrain()->getHeightVector(),
				brushCenterPosition,
				foliageBrush,
				foliageBrushPrototypes,
				currentFoliageBrushOperation,
				prototype->getTerrain()->getFoliageMaps(),
				newFoliageMaps
			);
			break;
		case Terrain2::BRUSHOPERATION_DELETE:
			//
			Terrain2::applyFoliageDeleteBrush(
				terrainBoundingBox,
				brushCenterPosition,
				foliageBrush,
				foliageBrushPrototypes,
				currentFoliageBrushOperation,
				prototype->getTerrain()->getFoliageMaps(),
				recreateFoliagePartitions
			);
			break;
	}

	//
	view->addTemporaryFoliage(newFoliageMaps);
	view->recreateTemporaryFoliage(recreateFoliagePartitions);

	//
	recreateFoliagePartitions.clear();
	Terrain2::emptyFoliageMaps(newFoliageMaps);
}

Terrain2::BrushOperation TerrainEditorTabController::getUITerrainBrushOperation() {
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_terrain_add"))->getController()->getValue().equals("1") == true) {
		return Terrain2::BRUSHOPERATION_ADD;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_terrain_substract"))->getController()->getValue().equals("1") == true) {
		return Terrain2::BRUSHOPERATION_SUBTRACT;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_terrain_flatten"))->getController()->getValue().equals("1") == true) {
		return Terrain2::BRUSHOPERATION_FLATTEN;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_terrain_smooth"))->getController()->getValue().equals("1") == true) {
		return Terrain2::BRUSHOPERATION_SMOOTH;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_terrain_ramp"))->getController()->getValue().equals("1") == true) {
		return Terrain2::BRUSHOPERATION_RAMP;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_terrain_delete"))->getController()->getValue().equals("1") == true) {
		return Terrain2::BRUSHOPERATION_DELETE;
	} else {
		return Terrain2::BRUSHOPERATION_NONE;
	}
}

Terrain2::BrushOperation TerrainEditorTabController::getUIWaterOperation() {
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_water_water"))->getController()->getValue().equals("1") == true) {
		return Terrain2::BRUSHOPERATION_WATER_ADD;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_water_delete"))->getController()->getValue().equals("1") == true) {
		return Terrain2::BRUSHOPERATION_WATER_DELETE;
	} else {
		return Terrain2::BRUSHOPERATION_NONE;
	}
}

Terrain2::BrushOperation TerrainEditorTabController::getUIFoliageBrushOperation() {
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_foliage_add"))->getController()->getValue().equals("1") == true) {
		return Terrain2::BRUSHOPERATION_ADD;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_foliage_delete"))->getController()->getValue().equals("1") == true) {
		return Terrain2::BRUSHOPERATION_DELETE;
	} else {
		return Terrain2::BRUSHOPERATION_NONE;
	}
}
