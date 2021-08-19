#include <tdme/tools/editor/tabcontrollers/TerrainEditorTabController.h>

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/engine/Engine.h>
#include <tdme/engine/prototype/Prototype.h>
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
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Terrain.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::tools::editor::tabcontrollers::TerrainEditorTabController;

using std::array;
using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::Engine;
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
using tdme::utilities::StringTools;
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
	view->setTerrainBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
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
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_button_add") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_ADD;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setTerrainBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_button_substract") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_SUBTRACT;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setTerrainBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_button_flatten") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_FLATTEN;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setTerrainBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_button_smooth") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_SMOOTH;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setTerrainBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_button_ramp") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_RAMP;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setTerrainBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
	} else
	if (StringTools::startsWith(node->getId(), view->getTabId() + "_tab_button_delete") == true) {
		currentTerrainBrushOperation = Terrain::BRUSHOPERATION_DELETE;
		view->getEditorView()->getScreenController()->setOutlinerSelection("terrain.brush");
		updateDetails("terrain.brush");
		view->setTerrainBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
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
		if (node->getId() == "terrain_create") {
			onCreateTerrain();
		} else
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
					terrainEditorTabController->view->setTerrainBrush(
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

void TerrainEditorTabController::onCreateTerrain() {
	auto prototype = view->getPrototype();
	auto terrain = prototype != nullptr?prototype->getTerrain():nullptr;
	if (terrain == nullptr) return;

	//
	try {
		view->reset();
		auto width = Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrain_size_x"))->getController()->getValue().getString());
		auto depth = Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrain_size_z"))->getController()->getValue().getString());
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
	if (currentTerrainBrushOperation != Terrain::BRUSHOPERATION_NONE) {
		currentTerrainBrushScale = scale;
		if (view->getEditorView()->getScreenController()->getOutlinerSelection() == "terrain.brush") {
			updateTerrainBrushDetails();
		}
	}
}

void TerrainEditorTabController::setBrushDensityStrength(float densityStrength) {
	if (currentTerrainBrushOperation != Terrain::BRUSHOPERATION_NONE) {
		currentTerrainBrushStrength = densityStrength;
		if (view->getEditorView()->getScreenController()->getOutlinerSelection() == "terrain.brush") {
			updateTerrainBrushDetails();
		}
	}
}

void TerrainEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Terrain") + "\" value=\"" + GUIParser::escapeQuotes("terrain") + "\">\n";
	xml+= "<selectbox-option image=\"resources/engine/images/terrain.png\" text=\"" + GUIParser::escapeQuotes("Terrain Brush") + "\" value=\"" + GUIParser::escapeQuotes("terrain.brush") + "\" />\n";
	basePropertiesSubController->createBasePropertiesXML(view->getPrototype(), xml);
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
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
		currentTerrainBrushScale = Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrainbrush_size"))->getController()->getValue().getString()); // TODO: a.drewke, size != scale
		currentTerrainBrushStrength = Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("terrainbrush_strength"))->getController()->getValue().getString());
	} catch (Exception& exception) {
		Console::println(string("TerrainEditorTabController::setTerrainBrushDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
	// TODO: a.drewke, maybe improve me
	view->setTerrainBrush(currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture, currentTerrainBrushScale, currentTerrainBrushStrength);
}

void TerrainEditorTabController::updateDetails(const string& outlinerNode) {
	view->getEditorView()->setDetailsContent(string());
	if (outlinerNode == "terrain") {
		setTerrainDetails();
	} else
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

	// and update foliage
	Terrain::updateFoliageTerrainBrush(
		terrainBoundingBox,
		prototype->getTerrain()->getHeightVector(),
		brushCenterPosition,
		currentTerrainBrushOperation == Terrain::BRUSHOPERATION_RAMP?rampTerrainBrushTexture:currentTerrainBrushTexture,
		currentTerrainBrushScale,
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
		currentTerrainBrushOperation != Terrain::BRUSHOPERATION_WATER &&
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

