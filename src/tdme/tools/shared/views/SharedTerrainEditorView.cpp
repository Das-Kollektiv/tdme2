#include <tdme/tools/shared/views/SharedTerrainEditorView.h>

#include <string>

#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeProperty.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/PartitionNone.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/sceneeditor/TDMESceneEditor.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/controller/TerrainEditorScreenController.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/CameraRotationInputHandler.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeProperty;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::PartitionNone;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::math::Vector3;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::controller::TerrainEditorScreenController;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedTerrainEditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

SharedTerrainEditorView::SharedTerrainEditorView(PopUps* popUps)
{
	this->popUps = popUps;
	terrainEditorScreenController = nullptr;
	initModelRequested = false;
	prototype = nullptr;
	engine = Engine::getInstance();
	cameraRotationInputHandler = new CameraRotationInputHandler(engine);
}

SharedTerrainEditorView::~SharedTerrainEditorView() {
	delete terrainEditorScreenController;
	delete cameraRotationInputHandler;
}

PopUps* SharedTerrainEditorView::getPopUpsViews()
{
	return popUps;
}

Prototype* SharedTerrainEditorView::getPrototype()
{
	return prototype;
}

void SharedTerrainEditorView::setPrototype(Prototype* prototype)
{
	engine->reset();
	this->prototype = prototype;
	initModelRequested = true;
}

void SharedTerrainEditorView::initModel()
{
	if (prototype == nullptr)
		return;

	//
	if (prototype->getModel() != nullptr) {
		Tools::setupEntity(prototype, engine, cameraRotationInputHandler->getLookFromRotations(), cameraRotationInputHandler->getScale(), 1, objectScale);
		Tools::oseThumbnail(prototype);
		cameraRotationInputHandler->setMaxAxisDimension(Tools::computeMaxAxisDimension(prototype->getModel()->getBoundingBox()));
		auto model = engine->getEntity("model");
		auto ground = engine->getEntity("ground");
		model->setContributesShadows(false);
		model->setReceivesShadows(false);
		ground->setEnabled(false);
		auto modelBoundingVolume = engine->getEntity("model_bv");
		if (modelBoundingVolume != nullptr) {
			modelBoundingVolume->setEnabled(false);
		}
	}

	//
	updateGUIElements();
}

void SharedTerrainEditorView::handleInputEvents()
{
	cameraRotationInputHandler->handleInputEvents();
}

void SharedTerrainEditorView::display()
{
	// commands
	if (initModelRequested == true) {
		initModel();
		cameraRotationInputHandler->reset();
		initModelRequested = false;
	}

	// viewport
	auto xScale = (float)engine->getWidth() / (float)terrainEditorScreenController->getScreenNode()->getScreenWidth();
	auto yScale = (float)engine->getHeight() / (float)terrainEditorScreenController->getScreenNode()->getScreenHeight();
	auto viewPortLeft = 0;
	auto viewPortTop = 0;
	auto viewPortWidth = 0;
	auto viewPortHeight = 0;
	terrainEditorScreenController->getViewPort(viewPortLeft, viewPortTop, viewPortWidth, viewPortHeight);
	viewPortLeft = (int)((float)viewPortLeft * xScale);
	viewPortTop = (int)((float)viewPortTop * yScale);
	viewPortWidth = (int)((float)viewPortWidth * xScale);
	viewPortHeight = (int)((float)viewPortHeight * yScale);
	engine->getCamera()->enableViewPort(viewPortLeft, viewPortTop, viewPortWidth, viewPortHeight);

	// rendering
	engine->getGUI()->handleEvents();
	engine->getGUI()->render();
}

void SharedTerrainEditorView::updateGUIElements()
{
	if (prototype != nullptr) {
		terrainEditorScreenController->setScreenCaption("Terrain Editor - " + prototype->getName());
		auto preset = prototype->getProperty("preset");
		terrainEditorScreenController->setPrototypeProperties(preset != nullptr ? preset->getValue() : "", "");
		terrainEditorScreenController->setPrototypeData(prototype->getName(), prototype->getDescription());
		if (prototype->getModel() != nullptr) {
			auto boundingBox = prototype->getModel()->getBoundingBox();
			terrainEditorScreenController->setTerrainDimension(
				boundingBox->getMax().getX() - boundingBox->getMin().getX(),
				boundingBox->getMax().getZ() - boundingBox->getMin().getZ()
			);
		} else {
			terrainEditorScreenController->setTerrainDimension(64.0f, 64.0f);
		}
	} else {
		terrainEditorScreenController->setScreenCaption("Terrain Editor - no terrain loaded");
		terrainEditorScreenController->unsetPrototypeProperties();
		terrainEditorScreenController->unsetPrototypeData();
		terrainEditorScreenController->setTerrainDimension(64.0f, 64.0f);
	}
}

void SharedTerrainEditorView::initialize()
{
	try {
		terrainEditorScreenController = new TerrainEditorScreenController(this);
		terrainEditorScreenController->initialize();
		engine->getGUI()->addScreen(terrainEditorScreenController->getScreenNode()->getId(), terrainEditorScreenController->getScreenNode());
		terrainEditorScreenController->getScreenNode()->setInputEventHandler(this);
	} catch (Exception& exception) {
		Console::print(string("SharedTerrainEditorView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	updateGUIElements();
}

void SharedTerrainEditorView::activate()
{
	engine->reset();
	engine->setPartition(new PartitionNone());
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->getGUI()->resetRenderScreens();
	engine->getGUI()->addRenderScreen(terrainEditorScreenController->getScreenNode()->getId());
	onInitAdditionalScreens();
	engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());
}

void SharedTerrainEditorView::deactivate()
{
}

void SharedTerrainEditorView::dispose()
{
	Engine::getInstance()->reset();
}

void SharedTerrainEditorView::onSetPrototypeData() {
}

void SharedTerrainEditorView::onInitAdditionalScreens() {
}
