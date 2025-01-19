#include <tdme/tools/editor/tabviews/SoundTabView.h>

#include <string>
#include <memory>

#include <tdme/tdme.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/AudioEntity.h>
#include <tdme/engine/Engine.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/tabcontrollers/SoundTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using tdme::tools::editor::tabviews::SoundTabView;

using tdme::audio::Audio;
using tdme::audio::AudioEntity;
using tdme::engine::Engine;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::SoundTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

SoundTabView::SoundTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode, AudioEntity* audioEntity)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->screenNode = screenNode;
	this->popUps = editorView->getPopUps();
	engine = unique_ptr<Engine>(Engine::createOffScreenInstance(512, 512, false, false, false));
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());
	this->audio = Audio::getInstance();
	this->audioEntity = audioEntity;
	this->audioEntity->setFixed(true);
}

SoundTabView::~SoundTabView() {
}

void SoundTabView::handleInputEvents()
{
	engine->getGUI()->handleEvents();
}

void SoundTabView::display()
{
	engine->display();
	engine->getGUI()->render();
}

void SoundTabView::initialize()
{
	try {
		soundTabController = make_unique<SoundTabController>(this);
		screenNode->addActionListener(soundTabController.get());
		screenNode->addTooltipRequestListener(soundTabController.get());
		soundTabController->initialize(editorView->getScreenController()->getScreenNode());
	} catch (Exception& exception) {
		Console::printLine("SoundTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings
}

void SoundTabView::dispose()
{
	engine->dispose();
	audio->removeEntity(audioEntity->getId());
}

void SoundTabView::updateRendering() {
}

Engine* SoundTabView::getEngine() {
	return engine.get();
}

void SoundTabView::activate() {
	soundTabController->setOutlinerAddDropDownContent();
	soundTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
	if (audio->getEntity(audioEntity->getId()) == nullptr) audio->addEntity(audioEntity);
}

void SoundTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void SoundTabView::reloadOutliner() {
	soundTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

void SoundTabView::play() {
	audioEntity->rewind();
	audioEntity->play();
}

void SoundTabView::stop() {
	audioEntity->stop();
}
