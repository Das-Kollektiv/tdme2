#include <tdme/tools/leveleditor/TDMELevelEditor.h>

#include <cstdlib>
#include <string>

#include <tdme/utils/Time.h>

#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/tools/leveleditor/views/EmptyView.h>
#include <tdme/tools/leveleditor/views/LevelEditorView.h>
#include <tdme/tools/leveleditor/views/ModelViewerView.h>
#include <tdme/tools/leveleditor/views/ParticleSystemView.h>
#include <tdme/tools/leveleditor/views/TriggerView.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/LevelPropertyPresets.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/utils/Console.h>

using std::wstring;

using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::utils::Time;

using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::leveleditor::views::EmptyView;
using tdme::tools::leveleditor::views::LevelEditorView;
using tdme::tools::leveleditor::views::ModelViewerView;
using tdme::tools::leveleditor::views::ParticleSystemView;
using tdme::tools::leveleditor::views::TriggerView;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelPropertyPresets;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::View;
using tdme::utils::Console;

wstring TDMELevelEditor::VERSION = L"0.9.9";

TDMELevelEditor* TDMELevelEditor::instance = nullptr;

TDMELevelEditor::TDMELevelEditor()
{
	TDMELevelEditor::instance = this;
	level = new LevelEditorLevel();
	LevelPropertyPresets::getInstance()->setDefaultLevelProperties(level);
	engine = Engine::getInstance();
	view = nullptr;
	popUps = new PopUps();
	quitRequested = false;

}

void TDMELevelEditor::main(int argc, char** argv)
{
	Console::println(wstring(L"TDMELevelEditor " + VERSION));
	Console::println(wstring(L"Programmed 2014,...,2017 by Andreas Drewke, drewke.net."));
	Console::println();
	auto tdmeLevelEditor = new TDMELevelEditor();
	tdmeLevelEditor->run(argc, argv, L"TDMELevelEditor");
}

TDMELevelEditor* TDMELevelEditor::getInstance()
{
	return instance;
}

LevelEditorEntityLibraryScreenController* TDMELevelEditor::getLevelEditorEntityLibraryScreenController()
{
	return levelEditorEntityLibraryScreenController;
}

LevelEditorEntityLibrary* TDMELevelEditor::getEntityLibrary()
{
	return level->getEntityLibrary();
}

LevelEditorLevel* TDMELevelEditor::getLevel()
{
	return level;
}

void TDMELevelEditor::setView(View* view)
{
	if (this->view != nullptr)
		this->view->deactivate();

	this->view = view;
	if (this->view != nullptr)
		this->view->activate();

}

View* TDMELevelEditor::getView()
{
	return view;
}

void TDMELevelEditor::quit()
{
	quitRequested = true;
}

void TDMELevelEditor::display()
{
	engine->display();
	Engine::getInstance()->initGUIMode();
	if (view != nullptr)
		view->display();

	Engine::getInstance()->doneGUIMode();
	if (quitRequested == true) {
		dispose();
		exit(0);
	}
}

void TDMELevelEditor::dispose()
{
	if (view != nullptr)
		view->deactivate();

	levelEditorView->dispose();
	modelViewerView->dispose();
	triggerView->dispose();
	emptyView->dispose();
	particleSystemView->dispose();
	engine->dispose();
	Tools::oseDispose();
}

void TDMELevelEditor::initialize()
{
	engine->initialize();
	setInputEventHandler(engine->getGUI());
	Tools::oseInit();
	levelEditorEntityLibraryScreenController = new LevelEditorEntityLibraryScreenController(popUps);
	levelEditorEntityLibraryScreenController->initialize();
	engine->getGUI()->addScreen(levelEditorEntityLibraryScreenController->getScreenNode()->getId(), levelEditorEntityLibraryScreenController->getScreenNode());
	popUps->initialize();
	levelEditorView = new LevelEditorView(popUps);
	levelEditorView->initialize();
	modelViewerView = new ModelViewerView(popUps);
	modelViewerView->initialize();
	triggerView = new TriggerView(popUps);
	triggerView->initialize();
	emptyView = new EmptyView(popUps);
	emptyView->initialize();
	particleSystemView = new ParticleSystemView(popUps);
	particleSystemView->initialize();
	setView(levelEditorView);
}

void TDMELevelEditor::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}

void TDMELevelEditor::switchToLevelEditor()
{
	setView(levelEditorView);
}

void TDMELevelEditor::switchToModelViewer()
{
	setView(modelViewerView);
}

void TDMELevelEditor::switchToTriggerView()
{
	setView(triggerView);
}

void TDMELevelEditor::switchToEmptyView()
{
	setView(emptyView);
}

void TDMELevelEditor::switchToParticleSystemView()
{
	setView(particleSystemView);
}

