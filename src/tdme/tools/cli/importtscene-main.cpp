#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/scenes/SceneReader.h>
#include <tdme/engine/fileio/scenes/SceneWriter.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/tools/FileSystemTools.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;
using std::unique_ptr;

using tdme::application::Application;
using tdme::engine::fileio::scenes::SceneReader;
using tdme::engine::fileio::scenes::SceneWriter;
using tdme::engine::scene::Scene;
using tdme::engine::tools::FileSystemTools;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;

int main(int argc, char** argv)
{
	Console::printLine(string("importtscene ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	if (argc != 2) {
		Console::printLine("Usage: importtscene scenemodel");
		Application::exit(Application::EXITCODE_FAILURE);
	}
	string sceneModelFileName = string(argv[1]);
	try {
		Console::printLine("Loading scene: " + sceneModelFileName);
		// TODO: this needs some love, does not work correctly right now
		auto scene = SceneReader::readFromModel(
			FileSystem::getInstance()->getPathName(sceneModelFileName),
			FileSystem::getInstance()->getFileName(sceneModelFileName)
		);
		Console::printLine("Saving scene: " + sceneModelFileName);
		SceneWriter::write(
			FileSystem::getInstance()->getPathName(sceneModelFileName),
			FileSystemTools::ensureFileExtension(FileSystem::getInstance()->getFileName(sceneModelFileName), "tscene"),
			scene
		);
	} catch (Exception& exception) {
		Console::printLine("An error occurred: " + string(exception.what()));
	}

	//
	Application::exit(Application::EXITCODE_SUCCESS);
}
