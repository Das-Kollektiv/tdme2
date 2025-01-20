#include <tdme/tools/editor/Editor.h>

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/GUI.h>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/SimplePartition.h>
#include <tdme/engine/Version.h>
#include <tdme/minitscript/EngineMinitScript.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/views/View.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Time.h>

using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

using tdme::tools::editor::Editor;

using tdme::utilities::Time;

using agui::gui::GUI;

using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::Color4;
using tdme::engine::Engine;
using tdme::engine::SimplePartition;
using tdme::engine::Version;
using tdme::minitscript::EngineMinitScript;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::View;
using tdme::utilities::Console;

Editor* Editor::instance = nullptr;

Editor::Editor()
{
	Tools::loadSettings(this);
	Editor::instance = this;
	engine = Engine::getInstance();
	engine->setPartition(new SimplePartition());
	view = nullptr;
	viewInitialized = false;
	viewNew = nullptr;
	popUps = make_unique<PopUps>();
	editorView = nullptr;
	quitRequested = false;
}

Editor::~Editor() {
}

int Editor::main(int argc, char** argv)
{
	Console::printLine(string("Editor ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();
	//
	EngineMinitScript::initialize();
	//
	auto tdmeEditor = new Editor();
	return tdmeEditor->run(argc, argv, "Editor", nullptr, Application::WINDOW_HINT_MAXIMIZED);
}

bool Editor::isFullScreen() {
	if (editorView == nullptr) return false;
	return editorView->getScreenController()->isFullScreen();
}

void Editor::setView(View* view)
{
	viewNew = view;
}

View* Editor::getView()
{
	return view;
}

void Editor::quit()
{
	quitRequested = true;
}

void Editor::display()
{
	if (viewNew != nullptr) {
		if (view != nullptr && viewInitialized == true) {
			view->deactivate();
			view->dispose();
			viewInitialized = false;
		}
		view = viewNew;
		viewNew = nullptr;
	}
	if (view != nullptr) {
		if (viewInitialized == false) {
			view->initialize();
			view->activate();
			viewInitialized = true;
		}
		view->display();
	}
	engine->display();
	engine->getGUI()->render();
	engine->getGUI()->handleEvents();
	if (view != nullptr) view->tick();
	if (quitRequested == true) {
		if (view != nullptr) {
			view->deactivate();
			view->dispose();
		}
		Application::exit(0);
	}
}

void Editor::dispose()
{
	if (view != nullptr && viewInitialized == true) {
		view->deactivate();
		view->dispose();
		view = nullptr;
	}
	popUps->dispose();
	engine->dispose();
	Tools::oseDispose();
}

void Editor::initialize()
{
	engine->initialize();
	// TODO: settings maybe for the next 2
	Application::setVSyncEnabled(true);
	Application::setLimitFPS(true);
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	setEventHandler(engine->getGUI());
	Tools::oseInit();
	popUps->initialize();
	setView((editorView = make_unique<EditorView>(popUps.get())).get());
}

void Editor::reshape(int width, int height)
{
	engine->reshape(width, height);
}

void Editor::onDrop(const vector<string>& paths) {
	editorView->onDrop(paths);
}

void Editor::onClose() {
	editorView->getScreenController()->closeProject();
}
