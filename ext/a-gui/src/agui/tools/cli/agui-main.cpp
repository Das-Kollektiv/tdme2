#include <memory>
#include <string>

#include <agui/agui.h>
#include <agui/application/Application.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <agui/gui/GUIVersion.h>
#include <agui/gui/renderer/GUIRendererBackend.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemInterface.h>
#include <agui/utilities/Console.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using agui::application::Application;
using agui::gui::GUI;
using agui::gui::GUIParser;
using agui::gui::GUIVersion;
using agui::gui::renderer::GUIRendererBackend;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemInterface;
using agui::utilities::Console;

/**
 * TDME editor
 * @author andreas.drewke
 */
class AGUI final
	: public Application
{
public:
	// forbid class copy
	FORBID_CLASS_COPY(AGUI)

	/**
	 * Public constructor
	 */
	AGUI(const string& screenFileName): Application(), screenFileName(screenFileName) {
	}

	/**
	 * Destructor
	 */
	~AGUI() {
	}

	/**
	 * Initialize
	 */
	void initialize() {
		//
		gui = make_unique<GUI>(
			Application::getApplication(),
			Application::getRendererBackend(),
			getWindowWidth(),
			getWindowHeight()
		);
		gui->initialize();
		//
		GUIParser::initialize();
		//
		Application::setEventHandler(gui.get());
		//
		auto screenNode = GUIParser::parse(
			FileSystem::getStandardFileSystem()->getPathName(screenFileName),
			FileSystem::getStandardFileSystem()->getFileName(screenFileName)
		);
		gui->addScreen(
			screenNode->getId(),
			screenNode
		);
		gui->addRenderScreen(screenNode->getId());
	}

	/**
	 * Dispose
	 */
	void dispose() {
		gui->dispose();
		GUIParser::dispose();
	}

	/**
	 * Resize
	 * @param width width
	 * @param height height
	 */
	void reshape(int width, int height) {
		gui->reshape(width, height);
	}

	/**
	 * Display
	 */
	void display() {
		Application::getRendererBackend()->setViewPort(gui->getWidth(), gui->getHeight());
		Application::getRendererBackend()->updateViewPort();
		Application::getRendererBackend()->clear(Application::getRendererBackend()->CLEAR_DEPTH_BUFFER_BIT | Application::getRendererBackend()->CLEAR_COLOR_BUFFER_BIT);
		//
		gui->handleEvents();
		gui->render();
	}

private:
	string screenFileName;
	unique_ptr<GUI> gui;
};

int main(int argc, char** argv)
{
	Console::printLine(string("A-GUI ") + GUIVersion::getVersion());
	Console::printLine(GUIVersion::getCopyright());
	Console::printLine();

	//
	if (argc != 2) {
		Console::printLine("Usage: agui pathtoscreen.xml");
		Application::exit(1);
	}

	auto screenFileName = string(argv[1]);
	auto agui = new AGUI(screenFileName);
	return agui->run(argc, argv, "A-GUI", nullptr, Application::WINDOW_HINT_MAXIMIZED);

	//
	return Application::EXITCODE_SUCCESS;
}
