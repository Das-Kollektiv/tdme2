#include <tdme/tools/editor/tabviews/EnvMapEditorTabView.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeWriter.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/EnvironmentMapping.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/Timing.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/tabcontrollers/EnvMapEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::EnvMapEditorTabView;

using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::prototypes::PrototypeWriter;
using tdme::engine::model::Material;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::EnvironmentMapping;
using tdme::engine::Light;
using tdme::engine::Object;
using tdme::engine::SceneConnector;
using tdme::engine::Timing;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::EnvMapEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

EnvMapEditorTabView::EnvMapEditorTabView(EditorView* editorView, const string& tabId, Scene* scene, Prototype* prototype)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->scene = scene;
	this->prototype = prototype;
	engine = Engine::createOffScreenInstance(512, 512, true, true, true);
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
}

EnvMapEditorTabView::~EnvMapEditorTabView() {
	delete scene;
}

void EnvMapEditorTabView::handleInputEvents()
{
}

void EnvMapEditorTabView::display()
{
	updateSky();
	envMapEditorTabController->updateInfoText(MutableString(engine->getTiming()->getAvarageFPS()).append(" FPS"));
	engine->display();
}

void EnvMapEditorTabView::initialize()
{
	try {
		envMapEditorTabController = new EnvMapEditorTabController(this);
		envMapEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
		skySpherePrototype = PrototypeReader::read("resources/engine/models", "sky_sphere.tmodel");
		skyDomePrototype = PrototypeReader::read("resources/engine/models", "sky_dome.tmodel");
		skyPanoramaPrototype = PrototypeReader::read("resources/engine/models", "sky_panorama.tmodel");
	} catch (Exception& exception) {
		Console::println("EnvMapEditorTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings
	// TODO: reloadTabOutliner
	for (auto i = 1; i < engine->getLightCount(); i++) engine->getLightAt(i)->setEnabled(false);
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
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(150.0f);
	cam->setLookFrom(Vector3(81.296799f, 15.020234f, 101.091347f));
	cam->setLookAt(Vector3(57.434414f, 0.695241f, 67.012329f));
	SceneConnector::setLights(engine, scene, Vector3());
	SceneConnector::addScene(engine, scene, false, false, false, false, false);
	initSky();
}

void EnvMapEditorTabView::dispose()
{
	engine->reset();
	delete envMapEditorTabController;
}

void EnvMapEditorTabView::updateRendering() {
}

Engine* EnvMapEditorTabView::getEngine() {
	return engine;
}

void EnvMapEditorTabView::activate() {
	envMapEditorTabController->setOutlinerAddDropDownContent();
	envMapEditorTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	envMapEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void EnvMapEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void EnvMapEditorTabView::reloadOutliner() {
	envMapEditorTabController->setOutlinerContent();
	envMapEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}


void EnvMapEditorTabView::initSky() {
	// sky sphere
	auto skySphere = new Object("sky_sphere", skySpherePrototype->getModel());
	skySphere->setRenderPass(Entity::RENDERPASS_NOFRUSTUMCULLING);
	skySphere->setShader("sky");
	skySphere->setFrustumCulling(false);
	skySphere->setTranslation(Vector3(0.0f, -20.0f, 0.0f));
	skySphere->setScale(Vector3(300.0f/200.0f, 300.0f/200.0f, 300.0f/200.0f));
	skySphere->update();
	skySphere->setContributesShadows(false);
	skySphere->setReceivesShadows(false);
	skySphere->setExcludeEffectPass(Engine::EFFECTPASS_LIGHTSCATTERING);
	engine->addEntity(skySphere);

	// sky dome
	auto skyDome = new Object("sky_dome", skyDomePrototype->getModel());
	skyDome->setRenderPass(Entity::RENDERPASS_NOFRUSTUMCULLING);
	skyDome->setShader("sky");
	skyDome->setFrustumCulling(false);
	skyDome->setTranslation(Vector3(0.0f, -20.0f, 0.0f));
	skyDome->setScale(Vector3(295.0f/190.0f, 295.0f/190.0f, 295.0f/190.0f));
	skyDome->getModel()->getMaterials().begin()->second->getSpecularMaterialProperties()->setDiffuseTextureMaskedTransparency(true);
	skyDome->update();
	skyDome->setContributesShadows(false);
	skyDome->setReceivesShadows(false);
	skyDome->setEffectColorMul(Color4(1.0f, 1.0f, 1.0f, 0.7f));
	skyDome->setExcludeEffectPass(Engine::EFFECTPASS_LIGHTSCATTERING);
	engine->addEntity(skyDome);

	// sky panorama
	auto skyPanorama = new Object("sky_panorama", skyPanoramaPrototype->getModel());
	skyPanorama->setRenderPass(Entity::RENDERPASS_NOFRUSTUMCULLING);
	skyPanorama->setShader("sky");
	skyPanorama->setFrustumCulling(false);
	skyPanorama->setTranslation(Vector3(0.0f, -20.0f, 0.0f));
	skyPanorama->setScale(Vector3(280.0f/190.0f, 280.0f/180.0f, 280.0f/180.0f));
	skyPanorama->addRotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
	skyPanorama->update();
	skyPanorama->setContributesShadows(false);
	skyPanorama->setReceivesShadows(false);
	skyPanorama->setExcludeEffectPass(Engine::EFFECTPASS_LIGHTSCATTERING);
	engine->addEntity(skyPanorama);

	auto environmentMapping = new EnvironmentMapping("sky_environment_mapping", Engine::getEnvironmentMappingWidth(), Engine::getEnvironmentMappingHeight(), BoundingBox(Vector3(-30.0f, 0.0f, -30.0f), Vector3(30.0f, 60.0f, -30.0f)));
	environmentMapping->setFrustumCulling(false);
	environmentMapping->setTranslation(Vector3(64.0f, -5.0f, 73.0f));
	environmentMapping->setTimeRenderUpdateFrequency(prototype->getEnvironmentMapTimeRenderUpdateFrequency());
	environmentMapping->setRenderPassMask(prototype->getEnvironmentMapRenderPassMask());
	environmentMapping->update();
	engine->addEntity(environmentMapping);
}

void EnvMapEditorTabView::updateSky() {
	auto skySphere = engine->getEntity("sky_sphere");
	skySphere->setTranslation(engine->getCamera()->getLookFrom().clone().sub(Vector3(0.0f, 20.0f, 0.0f)));
	skySphere->update();

	auto skyDome = static_cast<Object*>(engine->getEntity("sky_dome"));
	skyDome->setTranslation(engine->getCamera()->getLookFrom().clone().sub(Vector3(0.0f, 20.0f, 0.0f)));
	skyDome->setTextureMatrix((Matrix2D3x3()).identity().translate(Vector2(0.0f, skyDomeTranslation * 0.01f)));
	skyDome->update();

	auto skyPanorama = engine->getEntity("sky_panorama");
	skyPanorama->setTranslation(engine->getCamera()->getLookFrom().clone().sub(Vector3(0.0f, 20.0f, 0.0f)));
	skyPanorama->setRotationAngle(0, skyDomeTranslation * 1.0f * 0.1f);
	skyPanorama->update();

	skyDomeTranslation+= 1.0f / 60.0;
}

const Vector3& EnvMapEditorTabView::getEnvironmentMapTranslation() {
	auto environmentMapping = dynamic_cast<EnvironmentMapping*>(engine->getEntity("sky_environment_mapping"));
	return environmentMapping->getTranslation();
}

void EnvMapEditorTabView::setEnvironmentMapTranslation(const Vector3& translation) {
	auto environmentMapping = dynamic_cast<EnvironmentMapping*>(engine->getEntity("sky_environment_mapping"));
	environmentMapping->setTranslation(translation);
	environmentMapping->update();
}

int32_t EnvMapEditorTabView::getEnvironmentMapRenderPassMask() {
	auto environmentMapping = dynamic_cast<EnvironmentMapping*>(engine->getEntity("sky_environment_mapping"));
	return environmentMapping->getRenderPassMask();
}

void EnvMapEditorTabView::setEnvironmentMapRenderPassMask(int32_t renderPassMask) {
	auto environmentMapping = dynamic_cast<EnvironmentMapping*>(engine->getEntity("sky_environment_mapping"));
	environmentMapping->setRenderPassMask(renderPassMask);
}

int64_t EnvMapEditorTabView::getEnvironmentMapFrequency() {
	auto environmentMapping = dynamic_cast<EnvironmentMapping*>(engine->getEntity("sky_environment_mapping"));
	return environmentMapping->getTimeRenderUpdateFrequency();
}

void EnvMapEditorTabView::setEnvironmentMapFrequency(int64_t frequency) {
	auto environmentMapping = dynamic_cast<EnvironmentMapping*>(engine->getEntity("sky_environment_mapping"));
	environmentMapping->setTimeRenderUpdateFrequency(frequency);
}

void EnvMapEditorTabView::saveFile(const string& pathName, const string& fileName) {
	PrototypeWriter::write(pathName, fileName, prototype);
}
