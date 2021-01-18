#include <string>

#include <tdme/engine/prototype/Prototype.h>
#include <tdme/gui/events/Action.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/controller/PrototypeBaseSubScreenController.h>
#include <tdme/tools/shared/controller/TerrainEditorScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedTerrainEditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/Terrain.h>

using std::string;
using std::to_string;

using tdme::gui::events::Action;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::controller::PrototypeBaseSubScreenController;
using tdme::tools::shared::controller::TerrainEditorScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedTerrainEditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::MutableString;
using tdme::utilities::Terrain;

TerrainEditorScreenController::TerrainEditorScreenController(SharedTerrainEditorView* view)
{
	class OnSetEntityDataAction: public virtual Action
	{
	public:
		void performAction() override {
			finalView->updateGUIElements();
			finalView->onSetPrototypeData();
		}

		/**
		 * Public constructor
		 * @param TerrainEditorScreenController empty screen controller
		 * @param finalView final view
		 */
		OnSetEntityDataAction(TerrainEditorScreenController* TerrainEditorScreenController, SharedTerrainEditorView* finalView): terrainEditorScreenController(terrainEditorScreenController), finalView(finalView) {
		}

	private:
		TerrainEditorScreenController* terrainEditorScreenController;
		SharedTerrainEditorView* finalView;
	};

	this->view = view;
	auto const finalView = view;
	this->prototypeBaseSubScreenController = new PrototypeBaseSubScreenController(view->getPopUpsViews(), new OnSetEntityDataAction(this, finalView));
}

GUIScreenNode* TerrainEditorScreenController::getScreenNode()
{
	return screenNode;
}

void TerrainEditorScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/tools/terraineditor/gui", "screen_terraineditor.xml");
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = dynamic_cast< GUITextNode* >(screenNode->getNodeById("screen_caption"));
		viewPort = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("viewport"));
		terrainDimensionWidth = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("terrain_dimension_width"));
		terrainDimensionDepth = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("terrain_dimension_depth"));
		btnTerrainDimensionApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_terrain_dimension_apply"));
		brushStrength = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("brush_strength"));
		brushFile = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("brush_file"));
		brushFileLoad = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("brush_file_load"));
		brushFileClear = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("brush_file_clear"));
	} catch (Exception& exception) {
		Console::print(string("TerrainEditorScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	prototypeBaseSubScreenController->initialize(screenNode);
}

void TerrainEditorScreenController::dispose()
{
}

void TerrainEditorScreenController::setScreenCaption(const string& text)
{
	screenCaption->setText(text);
}

void TerrainEditorScreenController::setPrototypeData(const string& name, const string& description)
{
	prototypeBaseSubScreenController->setPrototypeData(name, description);
}

void TerrainEditorScreenController::unsetPrototypeData()
{
	prototypeBaseSubScreenController->unsetPrototypeData();
}

void TerrainEditorScreenController::setPrototypeProperties(const string& presetId, const string& selectedName)
{
	prototypeBaseSubScreenController->setPrototypeProperties(view->getPrototype(), presetId, selectedName);
}

void TerrainEditorScreenController::unsetPrototypeProperties()
{
	prototypeBaseSubScreenController->unsetPrototypeProperties();
}

void TerrainEditorScreenController::showErrorPopUp(const string& caption, const string& message)
{
	view->getPopUpsViews()->getInfoDialogScreenController()->show(caption, message);
}

void TerrainEditorScreenController::onValueChanged(GUIElementNode* node)
{
	prototypeBaseSubScreenController->onValueChanged(node, view->getPrototype());
}

void TerrainEditorScreenController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	prototypeBaseSubScreenController->onActionPerformed(type, node, view->getPrototype());
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId().compare(btnTerrainDimensionApply->getId()) == 0) {
			onApplyTerrainDimension();
		}
	}
}

void TerrainEditorScreenController::setTerrainDimension(float width, float height) {
	terrainDimensionWidth->getController()->setValue(MutableString(width));
	terrainDimensionDepth->getController()->setValue(MutableString(height));
}

void TerrainEditorScreenController::onApplyTerrainDimension() {
	try {
		auto width = Float::parseFloat(terrainDimensionWidth->getController()->getValue().getString());
		auto depth = Float::parseFloat(terrainDimensionDepth->getController()->getValue().getString());
		auto prototype = view->getPrototype();
		auto terrainModel = Terrain::createTerrainModel(width, depth, 0.0f, terrainVerticesVector);
		prototype->setModel(terrainModel);
		view->setPrototype(prototype);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void TerrainEditorScreenController::applyBrush(const Vector3& brushCenterPosition) {
	auto prototype = view->getPrototype();
	auto terrainModel = prototype->getModel();
	if (terrainModel == nullptr) return;
	Terrain::updateTerrainModel(terrainModel, terrainVerticesVector, brushCenterPosition, "./resources/engine/textures/terrain_brush_soft.png", 0.5f, 0.05f);
}

void TerrainEditorScreenController::getViewPort(int& left, int& top, int& width, int& height) {
	auto& constraints = viewPort->getComputedConstraints();
	left = constraints.left + constraints.alignmentLeft + constraints.contentAlignmentLeft;
	top = constraints.top + constraints.alignmentTop + constraints.contentAlignmentTop;
	width = constraints.width;
	height = constraints.height;
}
