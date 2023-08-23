#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/scenes/SceneReader.h>
#include <tdme/engine/fileio/scenes/SceneWriter.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;
using std::unique_ptr;

using tdme::application::Application;
using tdme::engine::fileio::scenes::SceneReader;
using tdme::engine::fileio::scenes::SceneWriter;
using tdme::engine::scene::Scene;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::misc::Tools;
using tdme::utilities::Console;
using tdme::utilities::Exception;

int main(int argc, char** argv)
{
	Console::println(string("importtscene ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	if (argc != 2) {
		Console::println("Usage: importtscene scenemodel");
		Application::exit(1);
	}
	string sceneModelFileName = string(argv[1]);
	try {
		Console::println("Loading scene: " + sceneModelFileName);
		// TODO: this needs some love, does not work correctly right now
		auto scene = SceneReader::readFromModel(
			FileSystem::getInstance()->getPathName(sceneModelFileName),
			FileSystem::getInstance()->getFileName(sceneModelFileName)
		);
		Console::println("Saving scene: " + sceneModelFileName);
		SceneWriter::write(
			FileSystem::getInstance()->getPathName(sceneModelFileName),
			Tools::ensureFileExtension(FileSystem::getInstance()->getFileName(sceneModelFileName), "tscene"),
			scene
		);
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}
}
