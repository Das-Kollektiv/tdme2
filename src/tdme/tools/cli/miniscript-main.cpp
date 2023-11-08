#include <cstdlib>
#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/EngineMiniScript.h>

using std::string;
using std::unique_ptr;

using tdme::application::Application;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::EngineMiniScript;

static void printInformation() {
	Console::println(string("miniscript ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();
	Console::println("Usage: miniscript [--version] [--verbose] path_to_script");
	Application::exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
	//
	string pathToScript;
	auto verbose = false;
	auto version = false;
	for (auto i = 1; i < argc; i++) {
		string argument = argv[i];
		if (argument == "--help") {
			printInformation();
			Application::exit(EXIT_SUCCESS);
		} else
		if (argument == "--version") {
			version = true;
		} else
		if (argument == "--verbose") {
			verbose = true;
		} else {
			if (pathToScript.empty() == false) {
				Console::println("Path to script already given");
				Application::exit(EXIT_FAILURE);
			} else {
				pathToScript = argument;
			}
		}
	}

	// version
	if (version == true) {
		Console::println(string("miniscript ") + Version::getVersion());
		Console::println(Version::getCopyright());
		Application::exit(EXIT_FAILURE);
	}

	// run script
	unique_ptr<EngineMiniScript> script;
	if (pathToScript.empty() == false) {
		//
		script = unique_ptr<EngineMiniScript>(
			EngineMiniScript::loadScript(
				FileSystem::getInstance()->getPathName(pathToScript),
				FileSystem::getInstance()->getFileName(pathToScript)
			)
		);
		if (script != nullptr) {
			// verbose
			if (verbose == true) Console::println(script->getInformation());
			//
			if (script->isValid() == false) {
				Console::println("Script not valid. Exiting");
			} else {
				while (script->isRunning() == true) {
					script->execute();
				}
			}
		}
	} else
	if (version == false) {
		printInformation();
		Application::exit(EXIT_SUCCESS);
	}

	//
	Application::exit(script == nullptr || script->isValid() == false?EXIT_FAILURE:EXIT_SUCCESS);
}
