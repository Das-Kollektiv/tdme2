#include <tdme/tools/shared/views/SharedTerrainEditorView.h>

#include <string>

#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeWriter.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeProperty.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/PartitionOctTree.h>
#include <tdme/engine/EnvironmentMapping.h>
#include <tdme/engine/Timing.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/sceneeditor/TDMESceneEditor.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/controller/TerrainEditorScreenController.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/CameraInputHandler.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::prototypes::PrototypeWriter;
using tdme::engine::model::Model;
using tdme::engine::model::Material;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeProperty;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EnvironmentMapping;
using tdme::engine::Object3D;
using tdme::engine::PartitionOctTree;
using tdme::engine::Timing;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::math::Vector3;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::controller::TerrainEditorScreenController;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::CameraInputHandler;
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
	cameraInputHandler = new CameraInputHandler(engine);
}

SharedTerrainEditorView::~SharedTerrainEditorView() {
	delete terrainEditorScreenController;
	delete cameraInputHandler;
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
	for (auto terrainModel: terrainModels) delete terrainModel;
	terrainBoundingBox = BoundingBox();
	terrainModels.clear();
	this->prototype = prototype;
	initModelRequested = true;
}

void SharedTerrainEditorView::setTerrain(BoundingBox& terrainBoundingBox, vector<Model*> terrainModels) {
	engine->reset();
	for (auto terrainModel: this->terrainModels) delete terrainModel;
	this->terrainBoundingBox = terrainBoundingBox;
	this->terrainModels = terrainModels;
	initModelRequested = true;
}

void SharedTerrainEditorView::setWater(vector<Model*> waterModels) {
	for (auto waterModel: this->waterModels) {
		engine->removeEntity(waterModel->getId());
		delete waterModel;
	}
	this->waterModels = waterModels;
	initModelRequested = true;
}

void SharedTerrainEditorView::initModel()
{
	if (prototype == nullptr)
		return;

	//
	if (terrainModels.empty() == false) {
		auto idx = 0;
		for (auto terrainModel: terrainModels) {
			auto terrainObject3D = new Object3D("terrain." + to_string(idx), terrainModel);
			terrainObject3D->setRenderPass(Entity::RENDERPASS_TERRAIN);
			terrainObject3D->setShader("terrain");
			terrainObject3D->setContributesShadows(true);
			terrainObject3D->setReceivesShadows(true);
			engine->addEntity(terrainObject3D);
			idx++;
		}

		Vector3 sceneCenter = terrainBoundingBox.getCenter();
		sceneCenter.set(Vector3(sceneCenter.getX(), terrainBoundingBox.getMax().getY() + 3.0f, sceneCenter.getZ()));
		cameraInputHandler->setSceneCenter(sceneCenter);
		Tools::oseThumbnail(prototype);
		auto modelBoundingVolume = engine->getEntity("model_bv");
		if (modelBoundingVolume != nullptr) {
			modelBoundingVolume->setEnabled(false);
		}
	}

	//
	if (waterModels.empty() == false) {
		for (auto waterModel: waterModels) {
			auto waterObject3D = new Object3D(waterModel->getId(), waterModel);
			waterObject3D->setRenderPass(Entity::RENDERPASS_WATER);
			waterObject3D->setShader("water");
			waterObject3D->setContributesShadows(false);
			waterObject3D->setReceivesShadows(false);
			waterObject3D->setReflectionEnvironmentMappingId("sky_environment_mapping");
			engine->addEntity(waterObject3D);
		}
	}

	//
	initSky();

	//
	updateGUIElements();
}

void SharedTerrainEditorView::initSky() {
	// sky sphere
	auto skySphere = new Object3D("sky_sphere", skySpherePrototype->getModel());
	skySphere->setRenderPass(Entity::RENDERPASS_NOFRUSTUMCULLING);
	skySphere->setShader("sky");
	skySphere->setFrustumCulling(false);
	skySphere->setTranslation(Vector3(0.0f, 0.0f, 0.0f));
	skySphere->setScale(Vector3(300.0f/200.0f, 300.0f/200.0f, 300.0f/200.0f));
	skySphere->update();
	skySphere->setContributesShadows(false);
	skySphere->setReceivesShadows(false);
	skySphere->setExcludeEffectPass(Engine::EFFECTPASS_LIGHTSCATTERING);
	engine->addEntity(skySphere);

	// sky dome
	auto skyDome = new Object3D("sky_dome", skyDomePrototype->getModel());
	skyDome->setRenderPass(Entity::RENDERPASS_NOFRUSTUMCULLING);
	skyDome->setShader("sky");
	skyDome->setFrustumCulling(false);
	skyDome->setTranslation(Vector3(0.0f, 0.0f, 0.0f));
	skyDome->setScale(Vector3(295.0f/190.0f, 295.0f/190.0f, 295.0f/190.0f));
	skyDome->getModel()->getMaterials().begin()->second->getSpecularMaterialProperties()->setDiffuseTextureMaskedTransparency(true);
	skyDome->update();
	skyDome->setContributesShadows(false);
	skyDome->setReceivesShadows(false);
	skyDome->setEffectColorMul(Color4(1.0f, 1.0f, 1.0f, 0.7f));
	skyDome->setExcludeEffectPass(Engine::EFFECTPASS_LIGHTSCATTERING);
	engine->addEntity(skyDome);

	// sky panorama
	auto skyPanorama = new Object3D("sky_panorama", skyPanoramaPrototype->getModel());
	skyPanorama->setRenderPass(Entity::RENDERPASS_NOFRUSTUMCULLING);
	skyPanorama->setShader("sky");
	skyPanorama->setFrustumCulling(false);
	skyPanorama->setTranslation(Vector3(0.0f, 0.0f, 0.0f));
	skyPanorama->setScale(Vector3(280.0f/190.0f, 280.0f/180.0f, 280.0f/180.0f));
	skyPanorama->addRotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
	skyPanorama->update();
	skyPanorama->setContributesShadows(false);
	skyPanorama->setReceivesShadows(false);
	skyPanorama->setExcludeEffectPass(Engine::EFFECTPASS_LIGHTSCATTERING);
	engine->addEntity(skyPanorama);

	auto environmentMapping = new EnvironmentMapping("sky_environment_mapping", Engine::getEnvironmentMappingWidth(), Engine::getEnvironmentMappingHeight(), BoundingBox(Vector3(-30.0f, 0.0f, -30.0f), Vector3(30.0f, 60.0f, -30.0f)));
	environmentMapping->setFrustumCulling(false);
	environmentMapping->setRenderPassMask(Entity::RENDERPASS_NOFRUSTUMCULLING);
	environmentMapping->setTimeRenderUpdateFrequency(33LL);
	environmentMapping->update();
	engine->addEntity(environmentMapping);
}

void SharedTerrainEditorView::updateSky() {
	auto skySphere = engine->getEntity("sky_sphere");
	skySphere->setTranslation(engine->getCamera()->getLookFrom());
	skySphere->update();

	auto skyDome = static_cast<Object3D*>(engine->getEntity("sky_dome"));
	skyDome->setTranslation(engine->getCamera()->getLookFrom());
	skyDome->setTextureMatrix((Matrix2D3x3()).identity().translate(Vector2(0.0f, skyDomeTranslation * 0.01f)));
	skyDome->update();

	auto skyPanorama = engine->getEntity("sky_panorama");
	skyPanorama->setTranslation(engine->getCamera()->getLookFrom());
	skyPanorama->setRotationAngle(0, skyDomeTranslation * 1.0f * 0.1f);
	skyPanorama->update();

	auto environmentMapping = engine->getEntity("sky_environment_mapping");
	environmentMapping->setTranslation(engine->getCamera()->getLookFrom());
	environmentMapping->update();

	skyDomeTranslation+= 1.0f / 60.0;
}

void SharedTerrainEditorView::handleInputEvents()
{
	for (auto i = 0; i < engine->getGUI()->getMouseEvents().size(); i++) {
		auto& event = engine->getGUI()->getMouseEvents()[i];
		if (event.isProcessed() == true) continue;

		if (event.getButton() == MOUSE_BUTTON_LEFT) {
			if (event.getType() == GUIMouseEvent::MOUSEEVENT_PRESSED ||
				event.getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) {
				engine->computeWorldCoordinateByMousePosition(event.getXUnscaled(), event.getYUnscaled(), brushCenterPosition);
				if (terrainEditorScreenController->getBrushOperation() == Terrain::BRUSHOPERATION_WATER) {
					if (terrainEditorScreenController->determineCurrentBrushHeight(terrainBoundingBox, terrainModels, brushCenterPosition) == true) {
						static int terrainModelIdx = 0;
						vector<Model*> waterModels;
						terrainEditorScreenController->createWaterModels(terrainBoundingBox, brushCenterPosition, terrainModelIdx++, waterModels);
						brushingEnabled = false;
						terrainEditorScreenController->unsetCurrentBrushFlattenHeight();

						//
						for (auto waterModel: waterModels) {
							auto waterObject3D = new Object3D(waterModel->getId(), waterModel); // TODO: make this persistent
							waterObject3D->setRenderPass(Entity::RENDERPASS_WATER);
							waterObject3D->setShader("water");
							waterObject3D->setContributesShadows(false);
							waterObject3D->setReceivesShadows(false);
							waterObject3D->setReflectionEnvironmentMappingId("sky_environment_mapping");
							engine->addEntity(waterObject3D);
						}
					}
				} else {
					brushingEnabled = true;
				}

				event.setProcessed(true);
			} else
			if (event.getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
				brushingEnabled = false;
				terrainEditorScreenController->unsetCurrentBrushFlattenHeight();
				event.setProcessed(true);
			}
		}
	}
	cameraInputHandler->handleInputEvents();
}

void SharedTerrainEditorView::display()
{
	// commands
	if (initModelRequested == true) {
		initModel();
		cameraInputHandler->reset();
		initModelRequested = false;
	}

	// actually do the brushing
	if (brushingEnabled == true && terrainEditorScreenController->determineCurrentBrushHeight(terrainBoundingBox, terrainModels, brushCenterPosition) == true) {
		if (terrainEditorScreenController->getBrushOperation() != Terrain::BRUSHOPERATION_WATER) {
			terrainEditorScreenController->applyBrush(terrainBoundingBox, terrainModels, brushCenterPosition, engine->getTiming()->getDeltaTime());
		}
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

	//
	updateSky();
}

void SharedTerrainEditorView::updateGUIElements()
{
	if (prototype != nullptr) {
		terrainEditorScreenController->setScreenCaption("Terrain Editor - " + prototype->getName());
		auto preset = prototype->getProperty("preset");
		terrainEditorScreenController->setPrototypeProperties(preset != nullptr ? preset->getValue() : "", "");
		terrainEditorScreenController->setPrototypeData(prototype->getName(), prototype->getDescription());
		if (terrainModels.empty() == false) {
			terrainEditorScreenController->setTerrainDimension(
				terrainBoundingBox.getDimensions().getX(),
				terrainBoundingBox.getDimensions().getZ()
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

		//
		// load sky
		skySpherePrototype = PrototypeReader::read("resources/tests/levels/water", "Mesh_Environment_Sky_Sphere.fbx.tmm");
		skyDomePrototype = PrototypeReader::read("resources/tests/levels/water", "Mesh_Environment_Sky_Dome.fbx.tmm");
		skyPanoramaPrototype = PrototypeReader::read("resources/tests/levels/water", "Mesh_Environment_Sky_Panorama.fbx.tmm");
		spherePrototype = PrototypeReader::read("resources/tests/levels/water", "CM_Sphere.tmm");

	} catch (Exception& exception) {
		Console::print(string("SharedTerrainEditorView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	updateGUIElements();
}

void SharedTerrainEditorView::activate()
{
	engine->reset();
	engine->setPartition(new PartitionOctTree());
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->getGUI()->resetRenderScreens();
	engine->getGUI()->addRenderScreen(terrainEditorScreenController->getScreenNode()->getId());
	onInitAdditionalScreens();
	engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());

	// lights
	for (auto i = 1; i < engine->getLightCount(); i++) engine->getLightAt(i)->setEnabled(false);
	{
		auto light0 = engine->getLightAt(0);
		light0->setAmbient(Color4(0.7f, 0.7f, 0.7f, 1.0f));
		light0->setDiffuse(Color4(0.3f, 0.3f, 0.3f, 1.0f));
		light0->setSpecular(Color4(1.0f, 1.0f, 1.0f, 1.0f));
		light0->setPosition(Vector4(0.0f, 20000.0f, 0.0f, 1.0f));
		light0->setSpotDirection(Vector3(0.0f, 0.0f, 0.0f).sub(Vector3(light0->getPosition().getX(), light0->getPosition().getY(), light0->getPosition().getZ())).normalize());
		light0->setConstantAttenuation(0.5f);
		light0->setLinearAttenuation(0.0f);
		light0->setQuadraticAttenuation(0.0f);
		light0->setSpotExponent(0.0f);
		light0->setSpotCutOff(180.0f);
		light0->setEnabled(true);
	}

	//
	initSky();
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

void SharedTerrainEditorView::loadFile(const string& pathName, const string& fileName) {
	prototype = PrototypeReader::read(pathName, fileName);
	setPrototype(prototype);
	terrainEditorScreenController->onLoadTerrain();
}

void SharedTerrainEditorView::saveFile(const string& pathName, const string& fileName) {
	PrototypeWriter::write(pathName, fileName, prototype);
}

