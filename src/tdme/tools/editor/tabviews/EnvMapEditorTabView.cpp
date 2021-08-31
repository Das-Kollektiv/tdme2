#include <tdme/tools/editor/tabviews/EnvMapEditorTabView.h>

#include <string>

#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabcontrollers/EnvMapEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::EnvMapEditorTabView;

using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::SceneConnector;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::EnvMapEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

EnvMapEditorTabView::EnvMapEditorTabView(EditorView* editorView, const string& tabId, Scene* scene)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->scene = scene;
	engine = Engine::createOffScreenInstance(512, 512, true, true);
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
}

EnvMapEditorTabView::~EnvMapEditorTabView() {
	delete scene;
}

void EnvMapEditorTabView::handleInputEvents()
{
}

void EnvMapEditorTabView::display()
{
	engine->display();
}

void EnvMapEditorTabView::initialize()
{
	try {
		envMapEditorTabController = new EnvMapEditorTabController(this);
	} catch (Exception& exception) {
		Console::print(string("EnvMapEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
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
	SceneConnector::addScene(engine, scene, true, true, true, true);
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
