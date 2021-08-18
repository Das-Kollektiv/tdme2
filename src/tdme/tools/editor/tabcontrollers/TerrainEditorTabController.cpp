#include <tdme/tools/editor/tabcontrollers/TerrainEditorTabController.h>

#include <string>

#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeTerrain.h>
#include <tdme/gui/GUI.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabviews/TerrainEditorTabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Terrain.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::tools::editor::tabcontrollers::TerrainEditorTabController;

using std::string;

using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeTerrain;
using tdme::utilities::Action;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TerrainEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Terrain;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

TerrainEditorTabController::TerrainEditorTabController(TerrainEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

TerrainEditorTabController::~TerrainEditorTabController() {
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
}

void TerrainEditorTabController::onFocus(GUIElementNode* node) {
}

void TerrainEditorTabController::onUnfocus(GUIElementNode* node) {
}

void TerrainEditorTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
}

void TerrainEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-option text=\"Terrain\" value=\"texture\" />\n";
	view->getEditorView()->setOutlinerContent(xml);
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

void TerrainEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
}
