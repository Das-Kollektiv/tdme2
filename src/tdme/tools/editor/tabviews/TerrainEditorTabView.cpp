#include <tdme/tools/editor/tabviews/TerrainEditorTabView.h>

#include <string>

#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeWriter.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeTerrain.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/EnvironmentMapping.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Object3DRenderGroup.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/CameraInputHandler.h>
#include <tdme/tools/editor/tabcontrollers/TerrainEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Terrain2.h>

using std::string;

using tdme::tools::editor::tabviews::TerrainEditorTabView;

using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::prototypes::PrototypeWriter;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::model::Material;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeTerrain;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::Engine;
using tdme::engine::EntityHierarchy;
using tdme::engine::EnvironmentMapping;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::Object3DRenderGroup;
using tdme::engine::SceneConnector;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::CameraInputHandler;
using tdme::tools::editor::tabcontrollers::TerrainEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Integer;
using tdme::utilities::StringTools;
using tdme::utilities::Terrain2;

TerrainEditorTabView::TerrainEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->prototype = prototype;
	engine = Engine::createOffScreenInstance(512, 512, true, true);
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
	outlinerState.expandedOutlinerParentOptionValues.push_back("terrain");
}

TerrainEditorTabView::~TerrainEditorTabView() {
	delete cameraInputHandler;
	delete prototype;
	delete terrainEditorTabController;
	delete engine;
}

void TerrainEditorTabView::handleInputEvents()
{
	brushMoved = false;
	for (auto i = 0; i < engine->getGUI()->getMouseEvents().size(); i++) {
		auto& event = engine->getGUI()->getMouseEvents()[i];
		if (event.isProcessed() == true) continue;

		if (event.getType() == GUIMouseEvent::MOUSEEVENT_WHEEL_MOVED) {
			if (event.isShiftDown() == true) {
				setBrushScale(Math::clamp(brushScale + 0.1 * event.getWheelY(), 0.1f, 100.0f));
				event.setProcessed(true);
			}
			if (event.isControlDown() == true) {
				setBrushDensityStrength(Math::clamp(brushDensityStrength + 0.1 * event.getWheelY(), 0.1f, 100.0f));
				event.setProcessed(true);
			}
		} else
		if (event.getType() == GUIMouseEvent::MOUSEEVENT_MOVED) {
			brushMoved = true;
			engine->getEntityByMousePosition(event.getXUnscaled(), event.getYUnscaled(), brushCenterPosition);
			if (terrainEditorTabController->getTerrainBrushOperation() == Terrain2::BRUSHOPERATION_RAMP && rampMode == 0) {
				rampVertices[1] = brushCenterPosition;
				//
				auto brushEnabled = rampVertices[1].clone().sub(rampVertices[0]).computeLength() > 0.1f;
				brushCenterPosition = rampVertices[0].clone().add(rampVertices[1]).scale(0.5f);
				engine->setShaderParameter("terraineditor", "brushEnabled", brushEnabled);
				if (brushEnabled == true) {
					auto brushRotation = -(Vector3::computeAngle(rampVertices[1].clone().sub(rampVertices[0]).setY(0.0f).normalize(), Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 1.0f, 0.0f)) - 180.0f);
					if (Math::abs(rampVertices[0].getY() - rampVertices[1].getY()) > Math::EPSILON && rampVertices[0].getY() < rampVertices[1].getY()) brushRotation = brushRotation + 180.0f;
					engine->setShaderParameter("terraineditor", "brushRotation", brushRotation);
					engine->setShaderParameter("terraineditor", "brushScale",
						Vector2(
							(brushScale * 5.0f) / engine->getShaderParameter("terraineditor", "brushDimension").getVector2Value().getX(),
							1.0f / (engine->getShaderParameter("terraineditor", "brushDimension").getVector2Value().getY() / rampVertices[1].clone().sub(rampVertices[0]).computeLength())
						)
					);
				}
			}
		} else
		if (event.getButton() == MOUSE_BUTTON_RIGHT) {
			if (event.getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
				if (terrainEditorTabController->getTerrainBrushOperation() == Terrain2::BRUSHOPERATION_RAMP) {
					rampMode = -1;
					engine->setShaderParameter("terraineditor", "brushEnabled", false);
					engine->setShaderParameter("terraineditor", "brushRotation", 0.0f);
					engine->setShaderParameter("terraineditor", "brushScale", Vector2(1.0f, 1.0f));
				}
				event.setProcessed(true);
			}
		} else
		if (event.getButton() == MOUSE_BUTTON_LEFT) {
			if (event.getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
				if (terrainEditorTabController->getTerrainBrushOperation() == Terrain2::BRUSHOPERATION_RAMP) {
					if (engine->getEntityByMousePosition(event.getXUnscaled(), event.getYUnscaled(), brushCenterPosition) != nullptr &&
						terrainEditorTabController->determineRampHeight(terrainBoundingBox, terrainModels, brushCenterPosition, rampHeight[rampMode + 1]) == true) {
						//
						rampMode++;
						rampVertices[rampMode] = brushCenterPosition;
						if (rampMode == 0) {
							// no op
						} else
						if (rampMode == 1) {
							// place ramp
							brushCenterPosition = rampVertices[0].clone().add(rampVertices[1]).scale(0.5f);
							terrainEditorTabController->applyRampTerrainBrush(
								terrainBoundingBox,
								terrainModels,
								brushCenterPosition,
								engine->getShaderParameter("terraineditor", "brushRotation").getFloatValue(),
								engine->getShaderParameter("terraineditor", "brushScale").getVector2Value(),
								Math::min(rampHeight[0], rampHeight[1]),
								Math::max(rampHeight[0], rampHeight[1])
							);
							//
							rampMode = -1;
							engine->setShaderParameter("terraineditor", "brushEnabled", false);
							engine->setShaderParameter("terraineditor", "brushRotation", 0.0f);
							engine->setShaderParameter("terraineditor", "brushScale", Vector2(1.0f, 1.0f));
						}
					}
				} else {
					recreateFoliage(temporaryPartitionIdxs);
					temporaryPartitionIdxs.clear();
					brushingEnabled = false;
					terrainEditorTabController->unsetCurrentBrushFlattenHeight();
				}
				event.setProcessed(true);
			} else
			if (event.getType() == GUIMouseEvent::MOUSEEVENT_PRESSED ||
				event.getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) {
				brushMoved = true;
				if (terrainEditorTabController->getTerrainBrushOperation() != Terrain2::BRUSHOPERATION_RAMP) {
					engine->getEntityByMousePosition(event.getXUnscaled(), event.getYUnscaled(), brushCenterPosition);
				}
				if (terrainEditorTabController->getTerrainBrushOperation() == Terrain2::BRUSHOPERATION_RAMP) {
					// no op
				} else
				if (terrainEditorTabController->getTerrainBrushOperation() == Terrain2::BRUSHOPERATION_WATER) {
					if (terrainEditorTabController->determineCurrentBrushHeight(terrainBoundingBox, terrainModels, brushCenterPosition) == true) {
						vector<Model*> waterModels;
						Vector3 waterReflectionEnvironmentMappingPosition;
						terrainEditorTabController->createWater(terrainBoundingBox, brushCenterPosition, waterModels, waterReflectionEnvironmentMappingPosition);
						brushingEnabled = false;
						terrainEditorTabController->unsetCurrentBrushFlattenHeight();
						//
						for (auto waterModel: waterModels) {
							auto waterObject3D = new Object3D(waterModel->getId(), waterModel);
							waterObject3D->setRenderPass(Entity::RENDERPASS_WATER);
							waterObject3D->setShader("water");
							waterObject3D->setContributesShadows(false);
							waterObject3D->setReceivesShadows(false);
							waterObject3D->setReflectionEnvironmentMappingId("sky_environment_mapping");
							waterObject3D->setReflectionEnvironmentMappingPosition(waterReflectionEnvironmentMappingPosition);
							waterObject3D->setPickable(true);
							engine->addEntity(waterObject3D);
						}
					}
				} else
				if (terrainEditorTabController->getTerrainBrushOperation() == Terrain2::BRUSHOPERATION_DELETE) {
					auto selectedEntity = engine->getEntityByMousePosition(event.getXUnscaled(), event.getYUnscaled());
					if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "water.") == true) {
						auto waterBeginIdx = selectedEntity->getId().find('.', selectedEntity->getId().find('.') + 1) + 1;
						auto waterEndIdx = selectedEntity->getId().find('.', waterBeginIdx + 1);
						auto waterPositionMapIdx = Integer::parseInt(StringTools::substring(selectedEntity->getId(), waterBeginIdx, waterEndIdx));
						terrainEditorTabController->deleteWater(waterPositionMapIdx);
					} else {
						brushingEnabled = true;
					}
				} else {
					brushingEnabled = true;
				}
				event.setProcessed(true);
			}
		}
	}
	for (auto i = 0; i < engine->getGUI()->getKeyboardEvents().size(); i++) {
		auto& event = engine->getGUI()->getKeyboardEvents()[i];
		if (event.isProcessed() == true) continue;
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED) continue;
		auto isKeyDown = event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED;
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_ESCAPE) {
			if (isKeyDown == true) {
				if (terrainEditorTabController->getTerrainBrushOperation() == Terrain2::BRUSHOPERATION_RAMP) {
					rampMode = -1;
					engine->setShaderParameter("terraineditor", "brushEnabled", false);
					engine->setShaderParameter("terraineditor", "brushRotation", 0.0f);
					engine->setShaderParameter("terraineditor", "brushScale", Vector2(1.0f, 1.0f));
				}
			}
			event.setProcessed(true);
		}
	}
	cameraInputHandler->handleInputEvents();
}

void TerrainEditorTabView::display()
{
	//
	engine->setShaderParameter("terraineditor", "brushPosition", Vector2(brushCenterPosition.getX(), brushCenterPosition.getZ()));

	//
	updateSky();

	// actually do the brushing
	if (brushingEnabled == true && terrainEditorTabController->determineCurrentBrushHeight(terrainBoundingBox, terrainModels, brushCenterPosition) == true) {
		if (terrainEditorTabController->getTerrainBrushOperation() != Terrain2::BRUSHOPERATION_NONE) {
			terrainEditorTabController->applyTerrainBrush(terrainBoundingBox, terrainModels, brushCenterPosition, engine->getTiming()->getDeltaTime());
		}
		if (terrainEditorTabController->getFoliageBrushOperation() != Terrain2::BRUSHOPERATION_NONE) {
			if (brushMoved == true) {
				terrainEditorTabController->applyFoliageBrush(terrainBoundingBox, brushCenterPosition, engine->getTiming()->getDeltaTime());
			}
		}
	}

	//
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
	initializeTerrain();
}

void TerrainEditorTabView::dispose()
{
	engine->dispose();
}

void TerrainEditorTabView::updateRendering() {
}

Engine* TerrainEditorTabView::getEngine() {
	return engine;
}

void TerrainEditorTabView::activate() {
	terrainEditorTabController->setOutlinerAddDropDownContent();
	terrainEditorTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
	terrainEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void TerrainEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void TerrainEditorTabView::reloadOutliner() {
	terrainEditorTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
	terrainEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void TerrainEditorTabView::saveFile(const string& pathName, const string& fileName)
{
	PrototypeWriter::write(pathName, fileName, prototype);
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

void TerrainEditorTabView::reset() {
	engine->reset();
	for (auto terrainModel: terrainModels) delete terrainModel;
	terrainBoundingBox = BoundingBox();
	terrainModels.clear();
	unsetWater();
	initSky();
}

void TerrainEditorTabView::initializeTerrain() {
	reset();

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

void TerrainEditorTabView::addTemporaryFoliage(const vector<unordered_map<int, vector<Transformations>>>& newFoliageMaps) {
	if (prototype == nullptr) return;

	//
	auto& foliageMaps = prototype->getTerrain()->getFoliageMaps();

	//
	auto partitionIdx = 0;
	for (auto& foliageMapPartition: newFoliageMaps) {
		auto partitionPrototypeInstanceCount = 0;
		for (auto& foliageMapPartitionIt: foliageMapPartition) {
			partitionPrototypeInstanceCount+= foliageMapPartitionIt.second.size();
		}
		if (partitionPrototypeInstanceCount > 0) {
			//
			temporaryPartitionIdxs.insert(partitionIdx);

			//
			auto foliagePartitionObject3DRenderGroup = engine->getEntity("foliage.object3drendergroup." + to_string(partitionIdx) + ".0");
			if (foliagePartitionObject3DRenderGroup != nullptr) {
				auto shaderParameterIdx = 0;
				while (engine->removeEntity("foliage.object3drendergroup." + to_string(partitionIdx) + "." + to_string(shaderParameterIdx)) == true) shaderParameterIdx++;
				recreateTemporaryFoliage(partitionIdx);
			}
			auto foliagePartitionEntityHierarchy = dynamic_cast<EntityHierarchy*>(engine->getEntity("foliage.entityhierarchy." + to_string(partitionIdx)));
			if (foliagePartitionEntityHierarchy == nullptr) {
				foliagePartitionEntityHierarchy = new EntityHierarchy("foliage.entityhierarchy." + to_string(partitionIdx));
				foliagePartitionEntityHierarchy->setContributesShadows(true);
				foliagePartitionEntityHierarchy->setReceivesShadows(true);
				engine->addEntity(foliagePartitionEntityHierarchy);
			}
			for (auto& foliageMapPartitionIt: foliageMapPartition) {
				auto prototypeIdx = foliageMapPartitionIt.first;
				auto& transformationsVector = foliageMapPartitionIt.second;
				if (transformationsVector.empty() == false) {
					auto foliagePrototype = prototype->getTerrain()->getFoliagePrototype(prototypeIdx);
					auto& foliageIdx = partitionFoliageIdx[partitionIdx];
					for (auto& transformations: transformationsVector) {
						auto foliageEntity = SceneConnector::createEntity(foliagePrototype, foliagePartitionEntityHierarchy->getId() + "." + to_string(prototypeIdx) + "." + to_string(foliageIdx), transformations, 1, foliagePartitionEntityHierarchy);
						foliagePartitionEntityHierarchy->addEntity(foliageEntity);
						foliageIdx++;
					}
				}
			}
			foliagePartitionEntityHierarchy->update();
		}
		partitionIdx++;
	}
}

void TerrainEditorTabView::updateTemporaryFoliage(const unordered_set<int>& partitionIdxSet) {
	if (prototype == nullptr) return;

	//
	auto& foliageMaps = prototype->getTerrain()->getFoliageMaps();

	//
	auto partitionIdx = 0;
	for (auto partitionIdx: partitionIdxSet) {
		auto& foliageMapPartition = foliageMaps[partitionIdx];
		auto partitionPrototypeInstanceCount = 0;
		for (auto& foliageMapPartitionIt: foliageMapPartition) {
			partitionPrototypeInstanceCount+= foliageMapPartitionIt.second.size();
		}
		if (partitionPrototypeInstanceCount > 0) {
			//
			temporaryPartitionIdxs.insert(partitionIdx);

			//
			auto foliagePartitionObject3DRenderGroup = engine->getEntity("foliage.object3drendergroup." + to_string(partitionIdx) + ".0");
			auto foliagePartitionEntityHierarchy = dynamic_cast<EntityHierarchy*>(engine->getEntity("foliage.entityhierarchy." + to_string(partitionIdx)));
			if (foliagePartitionObject3DRenderGroup != nullptr || foliagePartitionEntityHierarchy == nullptr) {
				auto shaderParameterIdx = 0;
				while (engine->removeEntity("foliage.object3drendergroup." + to_string(partitionIdx) + "." + to_string(shaderParameterIdx)) == true) shaderParameterIdx++;
				recreateTemporaryFoliage(partitionIdx);
			}
			if (foliagePartitionEntityHierarchy == nullptr) foliagePartitionEntityHierarchy = dynamic_cast<EntityHierarchy*>(engine->getEntity("foliage.entityhierarchy." + to_string(partitionIdx)));
			auto foliageIdx = 0;
			for (auto& foliageMapPartitionIt: foliageMapPartition) {
				auto& transformationsVector = foliageMapPartitionIt.second;
				for (auto i = 0; i < transformationsVector.size(); i++) {
					foliagePartitionEntityHierarchy->getEntities()[foliageIdx]->fromTransformations(transformationsVector[i]);
					foliageIdx++;
				}
			}
			foliagePartitionEntityHierarchy->update();
		}
		partitionIdx++;
	}
}

void TerrainEditorTabView::recreateTemporaryFoliage(int partitionIdx) {
	if (prototype == nullptr) return;

	//
	temporaryPartitionIdxs.insert(partitionIdx);

	//
	auto& foliageMaps = prototype->getTerrain()->getFoliageMaps();

	//
	auto& foliageMapPartition = foliageMaps[partitionIdx];
	engine->removeEntity("foliage.entityhierarchy." + to_string(partitionIdx));
	auto shaderParameterIdx = 0;
	while (engine->removeEntity("foliage.object3drendergroup." + to_string(partitionIdx) + "." + to_string(shaderParameterIdx)) == true) shaderParameterIdx++;
	auto partitionPrototypeInstanceCount = 0;
	for (auto& foliageMapPartitionIt: foliageMapPartition) {
		partitionPrototypeInstanceCount+= foliageMapPartitionIt.second.size();
	}
	if (partitionPrototypeInstanceCount > 0) {
		auto foliagePartitionEntityHierarchy = new EntityHierarchy("foliage.entityhierarchy." + to_string(partitionIdx));
		foliagePartitionEntityHierarchy->setContributesShadows(true);
		foliagePartitionEntityHierarchy->setReceivesShadows(true);
		engine->addEntity(foliagePartitionEntityHierarchy);
		for (auto& foliageMapPartitionIt: foliageMapPartition) {
			auto prototypeIdx = foliageMapPartitionIt.first;
			auto foliagePrototype = prototype->getTerrain()->getFoliagePrototype(prototypeIdx);
			auto& transformationsVector = foliageMapPartitionIt.second;
			auto& foliageIdx = partitionFoliageIdx[partitionIdx];
			for (auto& transformations: transformationsVector) {
				auto foliageEntity = SceneConnector::createEntity(foliagePrototype, foliagePartitionEntityHierarchy->getId() + "." + to_string(prototypeIdx) + "." + to_string(foliageIdx), transformations, 1, foliagePartitionEntityHierarchy);
				foliagePartitionEntityHierarchy->addEntity(foliageEntity);
				foliageIdx++;
			}
		}
		foliagePartitionEntityHierarchy->update();
	}
}

void TerrainEditorTabView::recreateFoliage(const unordered_set<int>& partitionIdxSet) {
	if (prototype == nullptr) return;

	//
	auto& foliageMaps = prototype->getTerrain()->getFoliageMaps();

	//
	for (auto partitionIdx: partitionIdxSet) {
		auto& foliageMapPartition = foliageMaps[partitionIdx];
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

void TerrainEditorTabView::unsetTerrain() {
	for (auto terrainModel: this->terrainModels) delete terrainModel;
	this->terrainBoundingBox = BoundingBox();
	this->terrainModels.clear();
	this->partitionFoliageIdx.clear();
}

void TerrainEditorTabView::setTerrain(BoundingBox& terrainBoundingBox, vector<Model*> terrainModels) {
	unsetTerrain();
	this->terrainBoundingBox = terrainBoundingBox;
	this->terrainModels = terrainModels;
	this->partitionFoliageIdx.resize(terrainModels.size());
}

void TerrainEditorTabView::setBrush(Texture* texture, float scale, float densityStrength) {
	unsetBrush();
	if (texture != nullptr) texture->acquireReference();
	brushTexture = texture;
	//
	brushScale = scale;
	auto _scale = terrainEditorTabController->getTerrainBrushOperation() != Terrain2::BRUSHOPERATION_RAMP?scale:1.0f;
	engine->setShaderParameter("terraineditor", "brushDimension", Vector2(static_cast<int>(texture->getTextureWidth()) * _scale, static_cast<int>(texture->getTextureHeight()) * _scale));
	engine->setShaderParameter("terraineditor", "brushTexture", brushTexture == nullptr?0:engine->getTextureManager()->addTexture(brushTexture));
	engine->setShaderParameter(
		"terraineditor",
		"brushEnabled",
		(terrainEditorTabController->getTerrainBrushOperation() != Terrain2::BRUSHOPERATION_NONE && terrainEditorTabController->getTerrainBrushOperation() != Terrain2::BRUSHOPERATION_RAMP) ||
		terrainEditorTabController->getFoliageBrushOperation() != Terrain2::BRUSHOPERATION_NONE
	);
	rampMode = -1;
	brushDensityStrength = densityStrength;
}

void TerrainEditorTabView::setBrushScale(float scale) {
	if (brushTexture == nullptr ||
		terrainEditorTabController->getTerrainBrushOperation() == Terrain2::BRUSHOPERATION_RAMP ||
		terrainEditorTabController->getTerrainBrushOperation() == Terrain2::BRUSHOPERATION_WATER ||
		(terrainEditorTabController->getTerrainBrushOperation() == Terrain2::BRUSHOPERATION_NONE && terrainEditorTabController->getFoliageBrushOperation() == Terrain2::BRUSHOPERATION_NONE)) return;
	engine->setShaderParameter("terraineditor", "brushDimension", Vector2(static_cast<int>(brushTexture->getTextureWidth()) * scale, static_cast<int>(brushTexture->getTextureHeight()) * scale));
	brushScale = scale;
	terrainEditorTabController->setBrushScale(scale);
}

void TerrainEditorTabView::setBrushDensityStrength(float densityStrength) {
	if (brushTexture == nullptr ||
		terrainEditorTabController->getTerrainBrushOperation() == Terrain2::BRUSHOPERATION_RAMP ||
		terrainEditorTabController->getTerrainBrushOperation() == Terrain2::BRUSHOPERATION_WATER ||
		(terrainEditorTabController->getTerrainBrushOperation() == Terrain2::BRUSHOPERATION_NONE && terrainEditorTabController->getFoliageBrushOperation() == Terrain2::BRUSHOPERATION_NONE)) return;
	brushDensityStrength = densityStrength;
	terrainEditorTabController->setBrushDensityStrength(densityStrength);
}

void TerrainEditorTabView::unsetBrush() {
	if (brushTexture != nullptr) {
		engine->getTextureManager()->removeTexture(brushTexture->getId());
		brushTexture->releaseReference();
		brushTexture = nullptr;
		engine->setShaderParameter("terraineditor", "brushEnabled", false);
	}
}
