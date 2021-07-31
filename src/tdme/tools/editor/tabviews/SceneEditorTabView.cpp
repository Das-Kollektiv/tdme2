#include <tdme/tools/editor/tabviews/SceneEditorTabView.h>

#include <string>

#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/CameraInputHandler.h>
#include <tdme/tools/editor/misc/CameraInputHandlerEventHandler.h>
#include <tdme/tools/editor/tabcontrollers/SceneEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;
using std::to_string;

using tdme::tools::editor::tabviews::SceneEditorTabView;

using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::SceneConnector;
using tdme::engine::scene::Scene;
using tdme::tools::editor::misc::CameraInputHandler;
using tdme::tools::editor::misc::CameraInputHandlerEventHandler;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::SceneEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

SceneEditorTabView::SceneEditorTabView(EditorView* editorView, const string& tabId, Scene* scene)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	engine = Engine::createOffScreenInstance(512, 512, true);
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	this->scene = scene;
	this->cameraInputHandler = new CameraInputHandler(engine, this);
}

SceneEditorTabView::~SceneEditorTabView() {
}

EditorView* SceneEditorTabView::getEditorView() {
	return editorView;
}

TabController* SceneEditorTabView::getTabController() {
	return sceneEditorTabController;
}

PopUps* SceneEditorTabView::getPopUps()
{
	return popUps;
}

const string& SceneEditorTabView::getFileName()
{
	return sceneFileName;
}

void SceneEditorTabView::handleInputEvents()
{
	cameraInputHandler->handleInputEvents();
}

void SceneEditorTabView::display()
{
	updateSkyPosition();
	engine->display();
}

void SceneEditorTabView::initialize()
{
	try {
		sceneEditorTabController = new SceneEditorTabController(this);
	} catch (Exception& exception) {
		Console::print(string("SceneEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	//
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
	SceneConnector::setLights(engine, scene, Vector3());
	SceneConnector::addScene(engine, scene, true, true, true, true);
	updateSky();
	cameraInputHandler->setSceneCenter(scene->getCenter());
	// TODO: load settings
	// TODO: reloadTabOutliner
}

void SceneEditorTabView::dispose()
{
	delete sceneEditorTabController;
}

void SceneEditorTabView::updateRendering() {
}

Engine* SceneEditorTabView::getEngine() {
	return engine;
}

void SceneEditorTabView::activate() {
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
}

void SceneEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void SceneEditorTabView::reloadOutliner() {
}

void SceneEditorTabView::onCameraTranslation() {
}

void SceneEditorTabView::onCameraRotation() {
}

void SceneEditorTabView::onCameraScale() {
}

void SceneEditorTabView::updateSky() {
	engine->removeEntity("tdme.sky");
	if (scene->getSkyModel() == nullptr) return;
	auto sky = new Object3D("tdme.sky", scene->getSkyModel());
	sky->setRenderPass(Entity::RENDERPASS_NOFRUSTUMCULLING);
	sky->setShader("sky");
	sky->setFrustumCulling(false);
	sky->setTranslation(Vector3(0.0f, 0.0f, 0.0f));
	sky->setScale(scene->getSkyModelScale());
	sky->update();
	sky->setContributesShadows(false);
	sky->setReceivesShadows(false);
	sky->setExcludeEffectPass(Engine::EFFECTPASS_LIGHTSCATTERING);
	engine->addEntity(sky);
}

void SceneEditorTabView::updateSkyPosition() {
	auto sky = engine->getEntity("tdme.sky");
	if (sky == nullptr) return;
	sky->setTranslation(engine->getCamera()->getLookAt());
	sky->update();
}
