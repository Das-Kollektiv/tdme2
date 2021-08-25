#include <tdme/tools/editor/tabviews/ParticleSystemEditorTabView.h>

#include <string>

#include <tdme/audio/Audio.h>
#include <tdme/audio/Sound.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandler.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandlerEventHandler.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandler.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/views/PlayableSoundView.h>
#include <tdme/tools/editor/tabcontrollers/ParticleSystemEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Time.h>

using std::string;

using tdme::tools::editor::tabviews::ParticleSystemEditorTabView;

using tdme::audio::Audio;
using tdme::audio::Sound;
using tdme::engine::Engine;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::prototype::Prototype;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::CameraRotationInputHandlerEventHandler;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::ParticleSystemEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::PlayableSoundView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Time;

ParticleSystemEditorTabView::ParticleSystemEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->prototype = prototype;
	this->audio = Audio::getInstance();
	this->engine = Engine::createOffScreenInstance(512, 512, true);
	this->engine->setShadowMapLightEyeDistanceScale(0.1f);
	this->engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	this->cameraRotationInputHandler = new CameraRotationInputHandler(engine, this);
	this->audioStarted = -1LL;
	this->audioOffset = -1LL;
	Tools::setupPrototype(prototype, engine, cameraRotationInputHandler->getLookFromRotations(), cameraRotationInputHandler->getScale(), 1, objectScale);
}

ParticleSystemEditorTabView::~ParticleSystemEditorTabView() {
	delete particleSystemEditorTabController;
}

EditorView* ParticleSystemEditorTabView::getEditorView() {
	return editorView;
}

TabController* ParticleSystemEditorTabView::getTabController() {
	return particleSystemEditorTabController;
}

PopUps* ParticleSystemEditorTabView::getPopUps()
{
	return popUps;
}

void ParticleSystemEditorTabView::handleInputEvents()
{
}

void ParticleSystemEditorTabView::display()
{
	// audio
	if (audioOffset > 0 && Time::getCurrentMillis() - audioStarted >= audioOffset) {
		auto sound = audio->getEntity("sound");
		if (sound != nullptr) sound->play();
		audioOffset = -1LL;
	}

	//
	engine->display();
}

void ParticleSystemEditorTabView::initialize()
{
	try {
		particleSystemEditorTabController = new ParticleSystemEditorTabController(this);
	} catch (Exception& exception) {
		Console::print(string("ParticleSystemEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	// TODO: load settings
	// TODO: reloadTabOutliner
}

void ParticleSystemEditorTabView::dispose()
{
	engine->reset();
	delete particleSystemEditorTabController;
}

void ParticleSystemEditorTabView::updateRendering() {
}

Engine* ParticleSystemEditorTabView::getEngine() {
	return engine;
}

void ParticleSystemEditorTabView::activate() {
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
}

void ParticleSystemEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void ParticleSystemEditorTabView::reloadOutliner() {
}

void ParticleSystemEditorTabView::onCameraRotation() {
}

void ParticleSystemEditorTabView::onCameraScale() {
}

void ParticleSystemEditorTabView::playSound(const string& soundId) {
	audio->removeEntity("sound");
	auto soundDefinition = prototype->getSound(soundId);
	if (soundDefinition != nullptr && soundDefinition->getFileName().length() > 0) {
		auto pathName = PrototypeReader::getResourcePathName(
			Tools::getPathName(prototype->getFileName()),
			soundDefinition->getFileName()
		);
		auto fileName = Tools::getFileName(soundDefinition->getFileName());
		auto sound = new Sound(
			"sound",
			pathName,
			fileName
		);
		sound->setGain(soundDefinition->getGain());
		sound->setPitch(soundDefinition->getPitch());
		sound->setLooping(soundDefinition->isLooping());
		sound->setFixed(true);
		audio->addEntity(sound);
		audioStarted = Time::getCurrentMillis();
		audioOffset = -1LL;
		if (soundDefinition->getOffset() <= 0) {
			sound->play();
		} else {
			audioOffset = soundDefinition->getOffset();
		}
	}
}

void ParticleSystemEditorTabView::stopSound() {
	audio->removeEntity("sound");
}

