#include <tdme/tools/editor/tabcontrollers/TerrainEditorTabController.h>

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeTerrain.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/gui/GUI.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextureNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabviews/TerrainEditorTabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Terrain.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::tools::editor::tabcontrollers::TerrainEditorTabController;

using std::array;
using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeTerrain;
using tdme::utilities::Action;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextureNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabviews::TerrainEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Float;
using tdme::utilities::Terrain;

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
}

void TerrainEditorTabController::dispose()
{
}

void TerrainEditorTabController::save()
{
}

void TerrainEditorTabController::saveAs()
{
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
	} else {
		for (auto& textureBrushApplyNode: textureBrushApplyNodes) {
			if (node->getId() == textureBrushApplyNode) {
				applyTerrainBrushDetails();
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
	basePropertiesSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
}

void TerrainEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == "terrainbrush_texture_open") {
			class OnTerrainBrushFileLoadAction: public virtual Action
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
					terrainEditorTabController->brushTexturePath.setPath(terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName());
					terrainEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
				}

				/**
				 * Public constructor
				 * @param terrainEditorTabController terrain editor tab controller
				 */
				OnTerrainBrushFileLoadAction(TerrainEditorTabController* terrainEditorTabController): terrainEditorTabController(terrainEditorTabController) {
				}

			private:
				TerrainEditorTabController* terrainEditorTabController;
			};

			vector<string> extensions = TextureReader::getTextureExtensions();
			view->getPopUps()->getFileDialogScreenController()->show(
				currentTerrainBrushTextureFileName.empty() == true?brushTexturePath.getPath():Tools::getPathName(currentTerrainBrushTextureFileName),
				"Load terrain brush texture from: ",
				extensions,
				Tools::getFileName(currentTerrainBrushTextureFileName),
				true,
				new OnTerrainBrushFileLoadAction(this)
			);
		} else
		if (node->getId() == "terrainbrush_texture_remove") {
			if (currentTerrainBrushTexture != nullptr) currentTerrainBrushTexture->releaseReference();
			currentTerrainBrushTexture = nullptr;
			required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("terrainbrush_texture"))->setTexture(currentTerrainBrushTexture);
		} else
		if (node->getId() == "terrainbrush_texture_browseto") {
		}
	}
	basePropertiesSubController->onActionPerformed(type, node, view->getPrototype());
}

void TerrainEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Terrain") + "\" value=\"" + GUIParser::escapeQuotes("terrain") + "\">\n";
	xml+= "<selectbox-option image=\"resources/engine/images/terrain.png\" text=\"" + GUIParser::escapeQuotes("Terrain Brush") + "\" value=\"" + GUIParser::escapeQuotes("terrain.brush") + "\" />\n";
	basePropertiesSubController->createBasePropertiesXML(view->getPrototype(), xml);
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void TerrainEditorTabController::setTerrainBrushDetails() {
	view->getEditorView()->setDetailsContent(
		"<template id=\"details_terrainbrush\" src=\"resources/engine/gui/template_details_terrainbrush.xml\" />\n"
	);

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_terrainbrush"))->getActiveConditions().add("open");
		required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("terrainbrush_texture"))->setTexture(currentTerrainBrushTexture);
	} catch (Exception& exception) {
		Console::println(string("TerrainEditorTabController::setTerrainBrushDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void TerrainEditorTabController::applyTerrainBrushDetails() {
	try {
		currentTerrainBrushScale = Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrainbrush_size"))->getController()->getValue().getString()); // TODO: a.drewke, size != scale
		currentTerrainBrushStrength = Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrainbrush_strength"))->getController()->getValue().getString());
	} catch (Exception& exception) {
		Console::println(string("TerrainEditorTabController::setTerrainBrushDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void TerrainEditorTabController::updateDetails(const string& outlinerNode) {
	view->getEditorView()->setDetailsContent(string());
	if (outlinerNode == "terrain.brush") {
		setTerrainBrushDetails();
	} else {
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
		showErrorPopUp("Warning", (string(exception.what())));
	}
}
