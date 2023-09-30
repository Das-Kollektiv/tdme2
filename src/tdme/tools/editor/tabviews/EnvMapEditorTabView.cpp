#include <tdme/tools/editor/tabviews/EnvMapEditorTabView.h>

#include <memory>
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

using std::make_unique;
using std::string;
using std::unique_ptr;

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
	this->scene = unique_ptr<Scene>(scene);
	this->prototype = unique_ptr<Prototype>(prototype);
	engine = unique_ptr<Engine>(Engine::createOffScreenInstance(512, 512, true, true, true));
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	engine->setSkyShaderEnabled(true);
}

EnvMapEditorTabView::~EnvMapEditorTabView() {
}

void EnvMapEditorTabView::handleInputEvents()
{
}

void EnvMapEditorTabView::display()
{
	envMapEditorTabController->updateInfoText(MutableString(engine->getTiming()->getAvarageFPS()).append(" FPS"));
	engine->display();
}

void EnvMapEditorTabView::initialize()
{
	try {
		envMapEditorTabController = make_unique<EnvMapEditorTabController>(this);
		envMapEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
	} catch (Exception& exception) {
		Console::println("EnvMapEditorTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings
	// TODO: reloadTabOutliner
	// environment mapping
	auto environmentMapping = new EnvironmentMapping("sky_environment_mapping", Engine::getEnvironmentMappingWidth(), Engine::getEnvironmentMappingHeight(), BoundingBox(Vector3(-30.0f, 0.0f, -30.0f), Vector3(30.0f, 60.0f, -30.0f)));
	environmentMapping->setFrustumCulling(false);
	environmentMapping->setTranslation(Vector3(64.0f, -5.0f, 73.0f));
	environmentMapping->setTimeRenderUpdateFrequency(prototype->getEnvironmentMapTimeRenderUpdateFrequency());
	environmentMapping->setRenderPassMask(prototype->getEnvironmentMapRenderPassMask());
	environmentMapping->update();
	engine->addEntity(environmentMapping);
	// camera
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(150.0f);
	cam->setLookFrom(Vector3(81.296799f, 15.020234f, 101.091347f));
	cam->setLookAt(Vector3(57.434414f, 0.695241f, 67.012329f));
	// scene
	SceneConnector::setLights(engine.get(), scene.get());
	SceneConnector::addScene(engine.get(), scene.get(), false, false, false, false, false);
}

void EnvMapEditorTabView::dispose()
{
	engine->reset();
}

void EnvMapEditorTabView::updateRendering() {
}

Engine* EnvMapEditorTabView::getEngine() {
	return engine.get();
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
	PrototypeWriter::write(pathName, fileName, prototype.get());
}
