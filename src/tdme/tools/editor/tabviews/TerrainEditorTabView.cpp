#include <tdme/tools/editor/tabviews/TerrainEditorTabView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/EnvironmentMapping.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Object3DRenderGroup.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeTerrain.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/CameraInputHandler.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabcontrollers/TerrainEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::TerrainEditorTabView;

using tdme::engine::Engine;
using tdme::engine::EnvironmentMapping;
using tdme::engine::Object3D;
using tdme::engine::Object3DRenderGroup;
using tdme::engine::Light;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::model::Material;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeTerrain;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::CameraInputHandler;
using tdme::tools::editor::tabcontrollers::TerrainEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

TerrainEditorTabView::TerrainEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->prototype = prototype;
	engine = Engine::createOffScreenInstance(512, 512, true);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	for (auto i = 1; i < engine->getLightCount(); i++) engine->getLightAt(i)->setEnabled(false);
	{
		auto light0 = engine->getLightAt(0);
		light0->setAmbient(Color4(0.7f, 0.7f, 0.7f, 1.0f));
		light0->setDiffuse(Color4(0.3f, 0.3f, 0.3f, 1.0f));
		light0->setSpecular(Color4(1.0f, 1.0f, 1.0f, 1.0f));
		light0->setPosition(Vector4(0.0f, 20000.0f, 0.0f, 0.0f));
		light0->setSpotDirection(Vector3(0.0f, 0.0f, 0.0f).sub(Vector3(light0->getPosition().getX(), light0->getPosition().getY(), light0->getPosition().getZ())).normalize());
		light0->setConstantAttenuation(0.5f);
		light0->setLinearAttenuation(0.0f);
		light0->setQuadraticAttenuation(0.0f);
		light0->setSpotExponent(0.0f);
		light0->setSpotCutOff(180.0f);
		light0->setEnabled(true);
	}
	this->cameraInputHandler = new CameraInputHandler(engine);
}

TerrainEditorTabView::~TerrainEditorTabView() {
	delete cameraInputHandler;
	delete prototype;
}

void TerrainEditorTabView::handleInputEvents()
{
	cameraInputHandler->handleInputEvents();
}

void TerrainEditorTabView::display()
{
	updateSky();
	engine->display();
}

void TerrainEditorTabView::initialize()
{
	try {
		terrainEditorTabController = new TerrainEditorTabController(this);
		terrainEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
		skySpherePrototype = PrototypeReader::read("resources/engine/models", "sky_sphere.tmodel");
		skyDomePrototype = PrototypeReader::read("resources/engine/models", "sky_dome.tmodel");
		skyPanoramaPrototype = PrototypeReader::read("resources/engine/models", "sky_panorama.tmodel");
	} catch (Exception& exception) {
		Console::print(string("TerrainEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	// TODO: load settings
	// TODO: reloadTabOutliner
	initializeTerrain();
}

void TerrainEditorTabView::dispose()
{
	engine->reset();
	delete terrainEditorTabController;
}

void TerrainEditorTabView::updateRendering() {
}

Engine* TerrainEditorTabView::getEngine() {
	return engine;
}

void TerrainEditorTabView::activate() {
	// uiTabController->setOutlinerAddDropDownContent();
	terrainEditorTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
}

void TerrainEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void TerrainEditorTabView::reloadOutliner() {
	terrainEditorTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

void TerrainEditorTabView::initSky() {
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

void TerrainEditorTabView::updateSky() {
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

void TerrainEditorTabView::initializeTerrain() {
	engine->reset();
	for (auto terrainModel: terrainModels) delete terrainModel;
	terrainBoundingBox = BoundingBox();
	terrainModels.clear();
	unsetWater();

	//
	partitionFoliageIdx.clear();
	temporaryPartitionIdxs.clear();

	//
	terrainEditorTabController->initializeTerrain();

	//
	if (terrainModels.empty() == false) {
		auto idx = 0;
		for (auto terrainModel: terrainModels) {
			auto terrainObject3D = new Object3D("terrain." + to_string(idx), terrainModel);
			terrainObject3D->setRenderPass(Entity::RENDERPASS_TERRAIN);
			terrainObject3D->setShader("terraineditor");
			terrainObject3D->setContributesShadows(true);
			terrainObject3D->setReceivesShadows(true);
			terrainObject3D->setPickable(true);
			engine->addEntity(terrainObject3D);
			idx++;
		}

		Vector3 sceneCenter = terrainBoundingBox.getCenter();
		sceneCenter.set(Vector3(sceneCenter.getX(), terrainBoundingBox.getMax().getY() + 3.0f, sceneCenter.getZ()));
		cameraInputHandler->setSceneCenter(sceneCenter);
	}

	//
	if (waters.empty() == false) {
		for (auto& it: waters) {
			auto& water = it.second;
			for (auto waterModel: water.waterModels) {
				auto waterObject3D = new Object3D(waterModel->getId(), waterModel);
				waterObject3D->setRenderPass(Entity::RENDERPASS_WATER);
				waterObject3D->setShader("water");
				waterObject3D->setContributesShadows(false);
				waterObject3D->setReceivesShadows(false);
				waterObject3D->setReflectionEnvironmentMappingId("sky_environment_mapping");
				waterObject3D->setReflectionEnvironmentMappingPosition(water.waterReflectionEnvironmentMappingPosition);
				waterObject3D->setPickable(true);
				engine->addEntity(waterObject3D);
			}
		}
	}

	//
	initSky();

	//
	cameraInputHandler->reset();
}

void TerrainEditorTabView::unsetWater() {
	for (auto& it: waters) {
		for (auto waterModel: it.second.waterModels) {
			engine->removeEntity(waterModel->getId());
			delete waterModel;
		}
	}
	this->waters.clear();
}

void TerrainEditorTabView::addFoliage() {
	if (prototype == nullptr) return;

	//
	auto& foliageMaps = prototype->getTerrain()->getFoliageMaps();

	//
	auto partitionIdx = 0;
	for (auto& foliageMapPartition: foliageMaps) {
		engine->removeEntity("foliage.entityhierarchy." + to_string(partitionIdx));
		auto shaderParameterIdx = 0;
		while (engine->removeEntity("foliage.object3drendergroup." + to_string(partitionIdx) + "." + to_string(shaderParameterIdx)) == true) shaderParameterIdx++;
		auto partitionPrototypeInstanceCount = 0;
		for (auto& foliageMapPartitionIt: foliageMapPartition) {
			partitionPrototypeInstanceCount+= foliageMapPartitionIt.second.size();
		}
		if (partitionPrototypeInstanceCount > 0) {
			unordered_map<string, Object3DRenderGroup*> object3DRenderGroupByShaderParameters;
			for (auto& foliageMapPartitionIt: foliageMapPartition) {
				auto prototypeIdx = foliageMapPartitionIt.first;
				auto& transformationsVector = foliageMapPartitionIt.second;
				if (transformationsVector.empty() == false) {
					auto foliagePrototype = prototype->getTerrain()->getFoliagePrototype(prototypeIdx);
					Object3DRenderGroup* foliagePartitionObject3DRenderGroup = nullptr;
					auto foliagePartitionObject3DRenderGroupIt = object3DRenderGroupByShaderParameters.find(foliagePrototype->getShaderParameters().getShaderParametersHash());
					if (foliagePartitionObject3DRenderGroupIt != object3DRenderGroupByShaderParameters.end()) {
						foliagePartitionObject3DRenderGroup = foliagePartitionObject3DRenderGroupIt->second;
					}
					if (foliagePartitionObject3DRenderGroup == nullptr) {
						foliagePartitionObject3DRenderGroup = new Object3DRenderGroup(
							"foliage.object3drendergroup." + to_string(partitionIdx) + "." + to_string(object3DRenderGroupByShaderParameters.size()),
							1,
							25.0f,
							50.0f,
							4,
							16,
							false
						);
						foliagePartitionObject3DRenderGroup->setContributesShadows(true);
						foliagePartitionObject3DRenderGroup->setReceivesShadows(true);
						foliagePartitionObject3DRenderGroup->setShader(foliagePrototype->getShader());
						auto shaderParametersDefault = Engine::getShaderParameterDefaults(foliagePrototype->getShader());
						for (auto& parameterIt: shaderParametersDefault) {
							auto& parameterName = parameterIt.first;
							auto parameterValue = foliagePrototype->getShaderParameters().getShaderParameter(parameterName);
							foliagePartitionObject3DRenderGroup->setShaderParameter(parameterName, parameterValue);
						}
						engine->addEntity(foliagePartitionObject3DRenderGroup);
						object3DRenderGroupByShaderParameters[foliagePrototype->getShaderParameters().getShaderParametersHash()] = foliagePartitionObject3DRenderGroup;
					}
					for (auto& transformations: transformationsVector) {
						foliagePartitionObject3DRenderGroup->addObject(foliagePrototype->getModel(), transformations);
					}
				}
			}
			for (auto& object3DRenderGroupByShaderParametersIt: object3DRenderGroupByShaderParameters) {
				object3DRenderGroupByShaderParametersIt.second->updateRenderGroup();
			}
		}
		partitionIdx++;
	}
}

void TerrainEditorTabView::removeWater(int waterIdx) {
	auto& water = waters[waterIdx];
	for (auto waterModel: water.waterModels) {
		engine->removeEntity(waterModel->getId());
		delete waterModel;
	}
	waters.erase(waterIdx);
}

void TerrainEditorTabView::addWater(int waterIdx, vector<Model*> waterModels, const Vector3& waterReflectionEnvironmentMappingPosition) {
	auto& water = waters[waterIdx];
	for (auto waterModel: water.waterModels) {
		engine->removeEntity(waterModel->getId());
		delete waterModel;
	}
	water.waterModels = waterModels;
	water.waterReflectionEnvironmentMappingPosition = waterReflectionEnvironmentMappingPosition;
}

void TerrainEditorTabView::setTerrain(BoundingBox& terrainBoundingBox, vector<Model*> terrainModels) {
	for (auto terrainModel: this->terrainModels) delete terrainModel;
	this->terrainBoundingBox = terrainBoundingBox;
	this->terrainModels = terrainModels;
	this->partitionFoliageIdx.resize(terrainModels.size());
}
