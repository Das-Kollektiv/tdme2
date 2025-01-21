#include <tdme/tools/editor/tabcontrollers/TerrainEditorTabController.h>

#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUIImageNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUITextNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <agui/utilities/MutableString.h>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeTerrain.h>
#include <tdme/engine/tools/FileSystemTools.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Texture.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
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
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Terrain.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::tools::editor::tabcontrollers::TerrainEditorTabController;

using std::array;
using std::make_unique;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIImageNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextNode;
using agui::gui::GUI;
using agui::gui::GUIParser;
using agui::utilities::MutableString;

using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeTerrain;
using tdme::engine::tools::FileSystemTools;
using tdme::engine::Engine;
using tdme::engine::Texture;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
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
using tdme::utilities::StringTools;
using tdme::utilities::Terrain;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

TerrainEditorTabController::TerrainEditorTabController(TerrainEditorTabView* view)
{
	this->view = view;
	this->basePropertiesSubController = make_unique<BasePropertiesSubController>(view->getEditorView(), "terrain");
	this->popUps = view->getPopUps();
	this->currentTerrainBrushTextureFileName = "resources/engine/textures/terrain_brush_soft.png";
	this->currentTerrainBrushTexture = TextureReader::read(FileSystemTools::getPathName(currentTerrainBrushTextureFileName), FileSystemTools::getFileName(currentTerrainBrushTextureFileName), false, false);
	this->rampTerrainBrushTexture = TextureReader::read("./resources/engine/textures", "terrain_ramp.png", false, false);
}

TerrainEditorTabController::~TerrainEditorTabController() {
}

void TerrainEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	basePropertiesSubController->initialize(screenNode);
	view->setBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
}

void TerrainEditorTabController::dispose()
{
}

void TerrainEditorTabController::onCommand(TabControllerCommand command)
{
	switch (command) {
		case COMMAND_SAVE:
			{
				//
				auto prototype = view->getPrototype();
				if (prototype == nullptr) return;

				//
				try {
					if (prototype->getFileName().empty() == true) throw ExceptionBase("Could not save file. No filename known");
					view->saveFile(
						FileSystemTools::getPathName(prototype->getFileName()),
						FileSystemTools::getFileName(prototype->getFileName())
					);
				} catch (Exception& exception) {
					showInfoPopUp("Warning", string(exception.what()));
				}
			}
			break;
		case COMMAND_SAVEAS:
			{
				class OnModelSave: public Action
				{
				public:
					void performAction() override {
						try {
							modelEditorTabController->view->saveFile(
								modelEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
								modelEditorTabController->popUps->getFileDialogScreenController()->getFileName()
							);
						} catch (Exception& exception) {
							modelEditorTabController->showInfoPopUp("Warning", string(exception.what()));
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
					prototype->getFileName().empty() == false?FileSystemTools::getPathName(prototype->getFileName()):string(),
					"Save to: ",
					{{ "tterrain" }},
					FileSystemTools::getFileName(prototype->getFileName()),
					false,
					new OnModelSave(this)
				);
			}
			break;
		default:
			showInfoPopUp("Warning", "This command is not supported yet");
			break;
	}
}

void TerrainEditorTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	if (StringTools::startsWith(payload, "file:") == false) {
		showInfoPopUp("Warning", "Unknown payload in drop");
	} else {
		auto fileName = StringTools::substring(payload, string("file:").size());
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "terrainbrush_texture") == true) {
			if (FileSystemTools::hasFileExtension(fileName, TextureReader::getTextureExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + FileSystemTools::enumerateFileExtensions(TextureReader::getTextureExtensions()));
			} else {
				setTerrainBrushTexture(fileName);
			}
		} else
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "foliagebrush_texture") == true) {
			if (FileSystemTools::hasFileExtension(fileName, TextureReader::getTextureExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + FileSystemTools::enumerateFileExtensions(TextureReader::getTextureExtensions()));
			} else {
				setFoliageBrushTexture(fileName);
			}
		} else
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "foliagebrush_prototype_file") == true) {
			if (FileSystemTools::hasFileExtension(fileName, PrototypeReader::getModelExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + FileSystemTools::enumerateFileExtensions(PrototypeReader::getModelExtensions()));
			} else {
				setFoliageBrushPrototype(fileName);
			}
		} else {
			showInfoPopUp("Warning", "You can not drop a file here");
		}
	}
}

void TerrainEditorTabController::updateInfoText(const MutableString& text) {
	required_dynamic_cast<GUITextNode*>(screenNode->getNodeById(view->getTabId() + "_tab_text_info"))->setText(text);
}

void TerrainEditorTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void TerrainEditorTabController::onChange(GUIElementNode* node)
{
	if (basePropertiesSubController->onChange(node, view->getPrototype(), view->getPrototype()) == true) return;
	//
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		updateDetails(outlinerNode);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_terrain_add") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_ADD;
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_terrain_substract") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_SUBTRACT;
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_terrain_flatten") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_FLATTEN;
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_terrain_smooth") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_SMOOTH;
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_terrain_ramp") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_RAMP;
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_terrain_delete") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_DELETE;
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_water_water") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_WATER_ADD;
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.waters");
		updateDetails("terrain.waters");
		view->unsetBrush();
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_water_delete") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_WATER_DELETE;
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_NONE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.waters");
		updateDetails("terrain.waters");
		view->unsetBrush();
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_foliage_add") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_NONE;
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_ADD;
		view->unsetBrush();
		setFoliageBrush();
		updateFoliageBrush();
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_foliage_delete") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_NONE;
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_DELETE;
		view->unsetBrush();
		setFoliageBrush();
		updateFoliageBrush();
	} else {
		for (const auto& textureBrushApplyNode: textureBrushApplyNodes) {
			if (node->getId() == textureBrushApplyNode) {
				applyTerrainBrushDetails();
				break;
			}
		}
		for (const auto& foliageBrushApplyNode: foliageBrushApplyNodes) {
			if (node->getId() == foliageBrushApplyNode) {
				applyFoliageBrushDetails();
				updateFoliageBrush();
				break;
			}
		}
		for (const auto& foliageBrushPrototypeApplyNode: foliageBrushPrototypeApplyNodes) {
			if (node->getId() == foliageBrushPrototypeApplyNode) {
				applyFoliageBrushPrototypeDetails();
				updateFoliageBrush();
				break;
			}
		}
	}
}

void TerrainEditorTabController::onFocus(GUIElementNode* node) {
	if (basePropertiesSubController->onFocus(node, view->getPrototype()) == true) return;
}

void TerrainEditorTabController::onUnfocus(GUIElementNode* node) {
	if (basePropertiesSubController->onUnfocus(node, view->getPrototype()) == true) return;
}

void TerrainEditorTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "terrain.waters.") == true) {
			// clear
			popUps->getContextMenuScreenController()->clear();
			// delete
			class OnTerrainWaterDelete: public Action
			{
			public:
				void performAction() override {
					auto outlinerNode = terrainEditorTabController->view->getEditorView()->getScreenController()->getOutlinerSelection();
					auto waterIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.waters.").size(), outlinerNode.size()));
					terrainEditorTabController->deleteWater(waterIdx);
					//
					terrainEditorTabController->view->getEditorView()->reloadTabOutliner("terrain.waters");
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
			class OnTerrainFoliageAddBrush: public Action
			{
			public:
				void performAction() override {
					auto prototype = terrainEditorTabController->view->getPrototype();
					auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
					if (terrain == nullptr) return;
					auto brush = terrain->addBrush();
					//
					terrainEditorTabController->view->getEditorView()->reloadTabOutliner("terrain.foliage." + to_string(terrain->getBrushCount() - 1));
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
			class OnTerrainDeleteFoliageBrush: public Action
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
					terrainEditorTabController->view->getEditorView()->reloadTabOutliner(newOutlinerNode);
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
			class OnTerrainAddFoliageBrushPrototype: public Action
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
					auto newOutlinerNode = "terrain.foliagebrushes." + to_string(foliageBrushIdx) + "." + to_string(brush->getPrototypeCount() - 1);
					//
					terrainEditorTabController->view->getEditorView()->reloadTabOutliner(newOutlinerNode);
				}
				OnTerrainAddFoliageBrushPrototype(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
				}
			private:
				TerrainEditorTabController* terrainEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Add Foliage Prototype", "contextmenu_add", new OnTerrainAddFoliageBrushPrototype(this));


			// delete
			class OnTerrainDeleteFoliageBrush: public Action
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
					terrainEditorTabController->view->getEditorView()->reloadTabOutliner("terrain.foliage");
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
	basePropertiesSubController->onContextMenuRequest(node, mouseX, mouseY, view->getPrototype());
}

void TerrainEditorTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int tooltipLeft, tooltipTop;
	if (view->getEditorView()->getCurrentTabTooltipPosition(screenNode, mouseX, mouseY, tooltipLeft, tooltipTop) == false) return;
	//
	popUps->getTooltipScreenController()->show(tooltipLeft, tooltipTop, node->getToolTip());
}

void TerrainEditorTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void TerrainEditorTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	//
	if (basePropertiesSubController->onAction(type, node, view->getPrototype()) == true) return;
	//
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
			class OnFoliageBrushFileOpenAction: public Action
			{
			public:
				void performAction() override {
					terrainEditorTabController->setFoliageBrushTexture(
						terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
						"/" +
						terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
					);
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
				brush->getFileName().empty() == false?FileSystemTools::getPathName(brush->getFileName()):string(),
				"Load foliage brush texture from: ",
				extensions,
				FileSystemTools::getFileName(brush->getFileName()),
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
			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == false) return;
			auto foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.foliage.").size(), outlinerNode.size()));
			auto prototype = view->getPrototype();
			auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
			if (terrain == nullptr) {
				showInfoPopUp("Browse To", "Nothing to browse to");
				return;
			}
			auto brush = terrain->getBrush(foliageBrushIdx);
			if (brush == nullptr || brush->getFileName().empty() == true) {
				showInfoPopUp("Browse To", "Nothing to browse to");
				return;
			}
			view->getEditorView()->getScreenController()->browseTo(brush->getFileName());
		} else
		if (node->getId() == "foliagebrush_prototype_file_open") {
			class OnTerrainBrushPrototypeFileOpenAction: public Action
			{
			public:
				void performAction() override {
					terrainEditorTabController->setFoliageBrushPrototype(
						terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
						"/" +
						terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
					);
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

			view->getPopUps()->getFileDialogScreenController()->show(
				brushPrototype->getFileName().empty() == false?FileSystemTools::getPathName(brushPrototype->getFileName()):string(),
				"Load terrain brush texture from: ",
				PrototypeReader::getPrototypeExtensions(),
				FileSystemTools::getFileName(brushPrototype->getFileName()),
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
				Console::printLine("TerrainEditorTabController::onAction(): " + string(exception.what()));
			}
		} else
		if (node->getId() == "foliagebrush_prototype_file_browseto") {
			auto prototype = view->getPrototype();
			auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
			if (terrain == nullptr) return;

			auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
			auto foliageBrushIdx = -1;
			auto foliageBrushPrototypeIdx = -1;
			if (checkOutlinerFoliageBrushPrototype(outlinerNode, foliageBrushIdx, foliageBrushPrototypeIdx) == false) return;
			auto brush = terrain->getBrush(foliageBrushIdx);
			if (brush == nullptr) {
				showInfoPopUp("Browse To", "Nothing to browse to");
				return;
			}
			auto brushPrototype = brush->getPrototype(foliageBrushPrototypeIdx);
			if (brushPrototype == nullptr || brushPrototype->getFileName().empty() == true) {
				showInfoPopUp("Browse To", "Nothing to browse to");
				return;
			}
			view->getEditorView()->getScreenController()->browseTo(brushPrototype->getFileName());
		} else
		if (node->getId() == "terrainbrush_texture_open") {
			class OnTerrainBrushFileOpenAction: public Action
			{
			public:
				void performAction() override {
					terrainEditorTabController->setTerrainBrushTexture(
						terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
						"/" +
						terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
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
				currentTerrainBrushTextureFileName.empty() == false?FileSystemTools::getPathName(currentTerrainBrushTextureFileName):string(),
				"Load terrain brush texture from: ",
				extensions,
				FileSystemTools::getFileName(currentTerrainBrushTextureFileName),
				true,
				new OnTerrainBrushFileOpenAction(this)
			);
		} else
		if (node->getId() == "terrainbrush_texture_remove") {
			if (currentTerrainBrushTexture != nullptr) currentTerrainBrushTexture->releaseReference();
			currentTerrainBrushTexture = nullptr;
			currentTerrainBrushTextureFileName.clear();
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("terrainbrush_texture"))->setTexture(currentTerrainBrushTexture->toGUITexture());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("terrainbrush_texture"))->setTooltip(currentTerrainBrushTextureFileName);
		} else
		if (node->getId() == "terrainbrush_texture_browseto") {
			if (currentTerrainBrushTextureFileName.empty() == true) {
				showInfoPopUp("Browse To", "Nothing to browse to");
			} else {
				view->getEditorView()->getScreenController()->browseTo(currentTerrainBrushTextureFileName);
			}
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
				Terrain::mirrorXAxis(
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
				Terrain::mirrorZAxis(
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
				Terrain::mirrorXAxis(
					flipped,
					terrain->getWidth(),
					terrain->getDepth(),
					terrain->getHeightVector(),
					terrain->getWaterPositionMapsHeight(),
					terrain->getWaterPositionMaps(),
					terrain->getFoliageMaps()
				);
				terrain->setWidth(terrain->getWidth() * 2.0f);
				Terrain::mirrorZAxis(
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
}

void TerrainEditorTabController::setOutlinerContent() {
	auto prototype = view->getPrototype();
	auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Terrain") + "\" value=\"" + GUIParser::escape("terrain") + "\">\n";
	basePropertiesSubController->createBasePropertiesXML(view->getPrototype(), xml);
	xml+= "<selectbox-option image=\"resources/engine/images/terrain.png\" text=\"" + GUIParser::escape("Terrain Brush") + "\" value=\"" + GUIParser::escape("terrain.brush") + "\" />\n";
	if (terrain != nullptr && terrain->getWaterPositionMapsIndices().empty() == false) {
		xml+= "<selectbox-parent-option image=\"resources/engine/images/terrain_water.png\" text=\"" + GUIParser::escape("Water") + "\" value=\"" + GUIParser::escape("terrain.waters") + "\">\n";
		auto i = 0;
		for (auto waterIdx: terrain->getWaterPositionMapsIndices()) {
			xml+= "<selectbox-option image=\"resources/engine/images/terrain_water.png\" text=\"" + GUIParser::escape("Water " + to_string(i)) + "\" value=\"" + GUIParser::escape("terrain.waters." + to_string(waterIdx)) + "\" />\n";
			i++;
		}
		xml+= "</selectbox-parent-option>\n";
	} else {
		xml+= "<selectbox-option image=\"resources/engine/images/terrain_water.png\" text=\"" + GUIParser::escape("Water") + "\" value=\"" + GUIParser::escape("terrain.waters") + "\" />\n";
	}
	if (terrain != nullptr && terrain->getBrushCount() > 0) {
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Foliage") + "\" value=\"" + GUIParser::escape("terrain.foliage") + "\">\n";
		auto i = 0;
		for (auto brush: terrain->getBrushes()) {
			if (brush->getPrototypeCount() > 0) {
				xml+= "<selectbox-parent-option image=\"resources/engine/images/foliage.png\" text=\"" + GUIParser::escape("Foliage Brush " + to_string(i)) + "\" value=\"" + GUIParser::escape("terrain.foliage." + to_string(i)) + "\" >\n";
				auto j = 0;
				for (auto brushPrototype: brush->getPrototypes()) {
					xml+= "<selectbox-option image=\"resources/engine/images/mesh.png\" text=\"" + GUIParser::escape("Prototype " + to_string(j)) + "\" value=\"" + GUIParser::escape("terrain.foliagebrushes." + to_string(i) + "." + to_string(j)) + "\" />\n";
					j++;
				}
				xml+= "</selectbox-parent-option>\n";
			} else {
				xml+= "<selectbox-option image=\"resources/engine/images/foliage.png\" text=\"" + GUIParser::escape("Foliage Brush " + to_string(i)) + "\" value=\"" + GUIParser::escape("terrain.foliage." + to_string(i)) + "\" />\n";
			}
			i++;
		}
		xml+= "</selectbox-parent-option>\n";
	} else {
		xml+= "<selectbox-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Foliage") + "\" value=\"" + GUIParser::escape("terrain.foliage") + "\" />\n";
	}
	auto foliagePrototypeIndices = terrain != nullptr?terrain->getFoliagePrototypeIndices():vector<int>();
	if (foliagePrototypeIndices.empty() == false) {
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Prototypes") + "\" value=\"" + GUIParser::escape("terrain.foliageprototypes") + "\">\n";
		auto i = 0;
		for (auto prototypeIdx: foliagePrototypeIndices) {
			auto foliagePrototype = terrain->getFoliagePrototype(prototypeIdx);
			xml+= "<selectbox-option image=\"resources/engine/images/mesh.png\" text=\"" + GUIParser::escape(FileSystemTools::removeFileExtension(FileSystemTools::getFileName(foliagePrototype->getFileName()))) + "\" value=\"" + GUIParser::escape("terrain.foliageprototypes." + to_string(prototypeIdx)) + "\" />\n";
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
		Terrain::createTerrainModels(width, depth, 0.0f, terrain->getHeightVector(), terrainBoundingBox, terrainModels);
		Terrain::createFoliageMaps(terrainBoundingBox, terrain->getFoliageMaps());
		Terrain::createFoliageMaps(terrainBoundingBox, newFoliageMaps);
		terrain->setWidth(terrainBoundingBox.getDimensions().getX());
		terrain->setDepth(terrainBoundingBox.getDimensions().getZ());
		view->initializeTerrain();
	} catch (Exception& exception) {
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	view->getEditorView()->reloadTabOutliner("terrain");
}

void TerrainEditorTabController::setBrushScale(float scale) {
	if (currentTerrainBrushOperation != Terrain::BRUSHOPERATION_NONE) {
		currentTerrainBrushScale = scale;
		if (view->getEditorView()->getScreenController()->getOutlinerSelection() == "terrain.brush") {
			updateTerrainBrushDetails();
		}
	} else
	if (currentFoliageBrushOperation != Terrain::BRUSHOPERATION_NONE) {
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
	if (currentTerrainBrushOperation != Terrain::BRUSHOPERATION_NONE) {
		currentTerrainBrushStrength = densityStrength;
		if (view->getEditorView()->getScreenController()->getOutlinerSelection() == "terrain.brush") {
			updateTerrainBrushDetails();
		}
	} else
	if (currentFoliageBrushOperation != Terrain::BRUSHOPERATION_NONE) {
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
		Console::printLine("TerrainEditorTabController::setTerrainDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void TerrainEditorTabController::setTerrainBrushDetails() {
	view->getEditorView()->setDetailsContent(
		"<template id=\"details_terrainbrush\" src=\"resources/engine/gui/template_details_terrainbrush.xml\" />\n"
	);

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_terrainbrush"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("terrainbrush_texture"))->setTexture(currentTerrainBrushTexture->toGUITexture());
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("terrainbrush_texture"))->setTooltip(currentTerrainBrushTextureFileName);
	} catch (Exception& exception) {
		Console::printLine("TerrainEditorTabController::setTerrainBrushDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	updateTerrainBrushDetails();
}

void TerrainEditorTabController::updateTerrainBrushDetails() {
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrainbrush_size"))->getController()->setValue(MutableString(currentTerrainBrushScale));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrainbrush_strength"))->getController()->setValue(MutableString(currentTerrainBrushStrength));
	} catch (Exception& exception) {
		Console::printLine("TerrainEditorTabController::updateTerrainBrushDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void TerrainEditorTabController::applyTerrainBrushDetails() {
	try {
		currentTerrainBrushScale = Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrainbrush_size"))->getController()->getValue().getString()); // TODO: a.drewke, size != scale
		currentTerrainBrushStrength = Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrainbrush_strength"))->getController()->getValue().getString());
	} catch (Exception& exception) {
		Console::printLine("TerrainEditorTabController::setTerrainBrushDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
	// TODO: a.drewke, maybe improve me
	view->setBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
}

void TerrainEditorTabController::setFoliageBrushDetails() {
	view->getEditorView()->setDetailsContent(
		"<template id=\"details_foliagebrush\" src=\"resources/engine/gui/template_details_foliagebrush.xml\" />\n"
	);

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_foliagebrush"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::printLine("TerrainEditorTabController::setFoliageBrushDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
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
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("foliagebrush_texture"))->setTooltip(brush->getFileName());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_size"))->getController()->setValue(MutableString(brush->getSize()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("foliagebrush_density"))->getController()->setValue(MutableString(brush->getDensity()));
	} catch (Exception& exception) {
		Console::printLine("TerrainEditorTabController::updateFoliageBrushDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
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
		Console::printLine("TerrainEditorTabController::applyFoliageBrushDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
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
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("foliagebrush_prototype_file"))->setTooltip(brushPrototype->getFileName());
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
		Console::printLine("TerrainEditorTabController::setFoliageBrushPrototypeDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
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
		Console::printLine("TerrainEditorTabController::applyFoliageBrushPrototypeDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
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
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_NONE;
		view->setBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
		required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById(view->getTabId() + "_tab_toolbar"))->getActiveConditions().set("terrain");
	} else
	if (outlinerNode == "terrain.brush") {
		setTerrainBrushDetails();
		currentTerrainBrushOperation = getUITerrainBrushOperation();
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_NONE;
		view->unsetBrush();
		required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById(view->getTabId() + "_tab_toolbar"))->getActiveConditions().set("terrain");
	} else
	if (outlinerNode == "terrain.waters" || StringTools::startsWith(outlinerNode, "terrain.waters.") == true) {
		currentTerrainBrushOperation = getUIWaterOperation();
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_NONE;
		view->unsetBrush();
		required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById(view->getTabId() + "_tab_toolbar"))->getActiveConditions().set("water");
	} else
	if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == true) {
		setFoliageBrushDetails();
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_NONE;
		currentFoliageBrushOperation = getUIFoliageBrushOperation();
		updateFoliageBrush();
		required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById(view->getTabId() + "_tab_toolbar"))->getActiveConditions().set("foliage");
	} else
	if (StringTools::startsWith(outlinerNode, "terrain.foliagebrushes.") == true) {
		setFoliageBrushPrototypeDetails();
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_NONE;
		currentFoliageBrushOperation = getUIFoliageBrushOperation();
		updateFoliageBrush();
		required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById(view->getTabId() + "_tab_toolbar"))->getActiveConditions().set("foliage");
	} else {
		view->unsetBrush();
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_NONE;
		currentFoliageBrushOperation = Terrain::BRUSHOPERATION_NONE;
		required_dynamic_cast<GUIElementNode*>(view->getEditorView()->getScreenController()->getScreenNode()->getNodeById(view->getTabId() + "_tab_toolbar"))->getActiveConditions().removeAll();
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
		Terrain::createTerrainModels(width, depth, 0.0f, prototype->getTerrain()->getHeightVector(), terrainBoundingBox, terrainModels);
		view->unsetWater();
		view->setTerrain(terrainBoundingBox, terrainModels);
		auto waterPositionMapsIndices = prototype->getTerrain()->getWaterPositionMapsIndices();
		for (auto waterPositionMapIdx: waterPositionMapsIndices) {
			vector<Model*> waterModels;
			Terrain::createWaterModels(
				terrainBoundingBox,
				prototype->getTerrain()->getWaterPositionMap(waterPositionMapIdx),
				prototype->getTerrain()->getWaterPositionMapHeight(waterPositionMapIdx),
				waterPositionMapIdx,
				waterModels
			);
			view->addWater(
				waterPositionMapIdx,
				waterModels,
				Terrain::computeWaterReflectionEnvironmentMappingPosition(
					prototype->getTerrain()->getWaterPositionMap(waterPositionMapIdx),
					prototype->getTerrain()->getWaterPositionMapHeight(waterPositionMapIdx)
				)
			);
		}
		view->addFoliage();
		Terrain::createFoliageMaps(terrainBoundingBox, newFoliageMaps);
		prototype->getTerrain()->setWidth(terrainBoundingBox.getDimensions().getX());
		prototype->getTerrain()->setDepth(terrainBoundingBox.getDimensions().getZ());
	} catch (Exception& exception) {
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void TerrainEditorTabController::applyTerrainBrush(BoundingBox& terrainBoundingBox, vector<Model*>& terrainModels, const Vector3& brushCenterPosition, int64_t deltaTime) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;
	if (terrainModels.empty() == true) return;

	// apply brush first
	Terrain::applyBrushToTerrainModels(
		terrainBoundingBox,
		terrainModels,
		prototype->getTerrain()->getHeightVector(),
		brushCenterPosition,
		currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture,
		currentTerrainBrushScale,
		currentTerrainBrushStrength * static_cast<float>(deltaTime) / 200.0f, // if strength = 1.0f it will e.g. add to level 5 meters/second
		currentTerrainBrushOperation,
		currentTerrainBrushHeight
	);

	//
	Terrain::FoliageBrush foliageBrush = {
		foliageBrush.brushTexture = Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture,
		foliageBrush.brushScale = currentTerrainBrushScale,
		foliageBrush.brushDensity = 1.0f
	};

	// and update foliage
	Terrain::updateFoliageTerrainBrush(
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
	if (currentTerrainBrushOperation != Terrain::BRUSHOPERATION_FLATTEN &&
		currentTerrainBrushOperation != Terrain::BRUSHOPERATION_WATER_ADD &&
		currentTerrainBrushOperation != Terrain::BRUSHOPERATION_RAMP) {
		return true;
	}
	if (haveCurrentTerrainBrushHeight == true) return true;
	if (terrainModels.empty() == true) return false;
	auto terrainModel = terrainModels[0];
	if (terrainModel == nullptr) return false;
	haveCurrentTerrainBrushHeight = Terrain::getTerrainModelsHeight(
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
	if (currentTerrainBrushOperation != Terrain::BRUSHOPERATION_RAMP) {
		return false;
	}
	if (terrainModels.empty() == true) return false;
	auto terrainModel = terrainModels[0];
	if (terrainModel == nullptr) return false;
	return Terrain::getTerrainModelsHeight(
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
	Terrain::applyRampBrushToTerrainModels(
		terrainBoundingBox,
		terrainModels,
		prototype->getTerrain()->getHeightVector(),
		position,
		currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture,
		rotation,
		scale,
		minHeight,
		maxHeight
	);

	// and update foliage
	Terrain::updateFoliageTerrainRampBrush(
		terrainBoundingBox,
		prototype->getTerrain()->getHeightVector(),
		position,
		currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture,
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
	if (Terrain::computeWaterPositionMap(
		terrainBoundingBox,
		prototype->getTerrain()->getHeightVector(),
		brushCenterPosition,
		prototype->getTerrain()->getWaterPositionMapHeight(waterPositionMapIdx),
		prototype->getTerrain()->getWaterPositionMap(waterPositionMapIdx)) == true) {
		//
		Terrain::createWaterModels(
			terrainBoundingBox,
			prototype->getTerrain()->getWaterPositionMap(waterPositionMapIdx),
			prototype->getTerrain()->getWaterPositionMapHeight(waterPositionMapIdx),
			waterPositionMapIdx,
			waterModels
		);
		waterReflectionEnvironmentMappingPosition = Terrain::computeWaterReflectionEnvironmentMappingPosition(
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
	auto foliageBrushTexture = TextureReader::read(FileSystemTools::getPathName(brush->getFileName()), FileSystemTools::getFileName(brush->getFileName()), false, false);
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
	foliageBrush.brushTexture = TextureReader::read(FileSystemTools::getPathName(brush->getFileName()), FileSystemTools::getFileName(brush->getFileName()), false, false);
	foliageBrush.brushScale = brush->getSize();
	foliageBrush.brushDensity = brush->getDensity();
	if (foliageBrush.brushTexture != nullptr) foliageBrush.brushTexture->acquireReference();

	//
	foliageBrushPrototypes.clear();
	for (auto foliageBrushPrototype: brush->getPrototypes()) {
		Prototype* foliagePrototype = nullptr;
		if (foliageBrushPrototype->getFileName().empty() == false) {
			try {
				foliagePrototype = PrototypeReader::read(
					PrototypeReader::getResourcePathName(FileSystemTools::getPathName(foliageBrushPrototype->getFileName()), foliageBrushPrototype->getFileName()),
					FileSystemTools::getFileName(foliageBrushPrototype->getFileName())
				);
			} catch (Exception& exception) {
				Console::printLine("TerrainEditorTabController::updateFoliageBrush(): failed to load prototype: " + foliageBrushPrototype->getFileName());
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
	if (currentFoliageBrushOperation == Terrain::BRUSHOPERATION_ADD) {
		auto haveBrushPrototypeIds = false;
		for (auto& foliageBrushPrototype: foliageBrushPrototypes) {
			if (foliageBrushPrototype.prototypeId != -1) haveBrushPrototypeIds = true;
		}
		if (haveBrushPrototypeIds == false) return;
	}

	//
	switch(currentFoliageBrushOperation) {
		case Terrain::BRUSHOPERATION_ADD:
			//
			Terrain::applyFoliageDeleteBrush(
				terrainBoundingBox,
				brushCenterPosition,
				foliageBrush,
				foliageBrushPrototypes,
				Terrain::BRUSHOPERATION_DELETE,
				prototype->getTerrain()->getFoliageMaps(),
				recreateFoliagePartitions
			);
			//
			Terrain::applyFoliageBrush(
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
		case Terrain::BRUSHOPERATION_DELETE:
			//
			Terrain::applyFoliageDeleteBrush(
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
	Terrain::emptyFoliageMaps(newFoliageMaps);
}

Terrain::BrushOperation TerrainEditorTabController::getUITerrainBrushOperation() {
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_terrain_add"))->getController()->getValue().equals("1") == true) {
		return Terrain::BRUSHOPERATION_ADD;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_terrain_substract"))->getController()->getValue().equals("1") == true) {
		return Terrain::BRUSHOPERATION_SUBTRACT;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_terrain_flatten"))->getController()->getValue().equals("1") == true) {
		return Terrain::BRUSHOPERATION_FLATTEN;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_terrain_smooth"))->getController()->getValue().equals("1") == true) {
		return Terrain::BRUSHOPERATION_SMOOTH;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_terrain_ramp"))->getController()->getValue().equals("1") == true) {
		return Terrain::BRUSHOPERATION_RAMP;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_terrain_delete"))->getController()->getValue().equals("1") == true) {
		return Terrain::BRUSHOPERATION_DELETE;
	} else {
		return Terrain::BRUSHOPERATION_NONE;
	}
}

Terrain::BrushOperation TerrainEditorTabController::getUIWaterOperation() {
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_water_water"))->getController()->getValue().equals("1") == true) {
		return Terrain::BRUSHOPERATION_WATER_ADD;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_water_delete"))->getController()->getValue().equals("1") == true) {
		return Terrain::BRUSHOPERATION_WATER_DELETE;
	} else {
		return Terrain::BRUSHOPERATION_NONE;
	}
}

Terrain::BrushOperation TerrainEditorTabController::getUIFoliageBrushOperation() {
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_foliage_add"))->getController()->getValue().equals("1") == true) {
		return Terrain::BRUSHOPERATION_ADD;
	} else
	if (required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(view->getTabId() + "_tab_foliage_delete"))->getController()->getValue().equals("1") == true) {
		return Terrain::BRUSHOPERATION_DELETE;
	} else {
		return Terrain::BRUSHOPERATION_NONE;
	}
}

void TerrainEditorTabController::setTerrainBrushTexture(const string& fileName) {
	if (currentTerrainBrushTexture != nullptr) currentTerrainBrushTexture->releaseReference();
	currentTerrainBrushTexture = nullptr;
	currentTerrainBrushTextureFileName = fileName;
	currentTerrainBrushTexture =
		TextureReader::read(
			FileSystemTools::getPathName(currentTerrainBrushTextureFileName),
			FileSystemTools::getFileName(currentTerrainBrushTextureFileName),
			false,
			false
		);
	try {
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("terrainbrush_texture"))->setTexture(currentTerrainBrushTexture->toGUITexture());
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("terrainbrush_texture"))->setTooltip(currentTerrainBrushTextureFileName);
	} catch (Exception& exception) {
		Console::printLine("TerrainEditorTabController::setTerrainBrushTexture(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
	view->setBrush(
		currentTerrainBrushTexture,
		currentTerrainBrushScale,
		currentTerrainBrushStrength
	);
}

void TerrainEditorTabController::setFoliageBrushTexture(const string& fileName) {
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	if (StringTools::startsWith(outlinerNode, "terrain.foliage.") == false) return;
	auto foliageBrushIdx = Integer::parse(StringTools::substring(outlinerNode, string("terrain.foliage.").size(), outlinerNode.size()));
	auto prototype = view->getPrototype();
	auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
	if (terrain == nullptr) return;
	auto brush = terrain->getBrush(foliageBrushIdx);
	if (brush == nullptr) return;
	brush->setFileName(fileName);
	try {
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("foliagebrush_texture"))->setSource(brush->getFileName());
	} catch (Exception& exception) {
		Console::printLine("TerrainEditorTabController::setFoliageBrushTexture(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
	updateFoliageBrush();
}

void TerrainEditorTabController::setFoliageBrushPrototype(const string& fileName) {
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
	brushPrototype->setFileName(fileName);
	try {
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("foliagebrush_prototype_file"))->setSource(brushPrototype->getFileName());
	} catch (Exception& exception) {
		Console::printLine("TerrainEditorTabController::setFoliageBrushPrototype(): " + string(exception.what()));
	}
	updateFoliageBrush();
}
