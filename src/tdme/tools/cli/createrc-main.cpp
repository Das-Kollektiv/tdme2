#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::application::Application;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;

int main(int argc, char** argv)
{
	Console::println(string("createrc ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	if (argc != 4) {
		Console::println("Usage: createrc path_to_rc file path_to_generated_rc");
		Application::exit(Application::EXITCODE_FAILURE);
	}

	//
	string rcInFileName = argv[1];
	string fileName = argv[2];
	string rcOutFileName = argv[3];

	//
	try {
		auto rc = FileSystem::getInstance()->getContentAsString(
			FileSystem::getInstance()->getPathName(rcInFileName),
			FileSystem::getInstance()->getFileName(rcInFileName)
		);

		//
		if (StringTools::endsWith(fileName, ".exe") == true) {
			auto executable = StringTools::substring(fileName, fileName.rfind('/') + 1, fileName.find(".exe"));
			auto executableLowerCase = StringTools::toLowerCase(executable);
			rc = StringTools::replace(rc, "{__EXECUTABLE__}", executable);
			if (FileSystem::getInstance()->fileExists("resources/platforms/win32/" + executableLowerCase + "-icon.ico") == true) {
				rc = StringTools::replace(rc, "{__ICON__}", "resources/platforms/win32/" + executableLowerCase + "-icon.ico");
			} else {
				rc = StringTools::replace(rc, "{__ICON__}", "resources/platforms/win32/default-icon.ico");
			}
		} else
		if (StringTools::endsWith(fileName, ".dll") == true) {
			auto library = StringTools::substring(fileName, fileName.rfind('/') + 1, fileName.find(".dll"));
			rc = StringTools::replace(rc, "{__LIBRARY__}", library);
		}

		//
		FileSystem::getInstance()->setContentFromString(
			FileSystem::getInstance()->getPathName(rcOutFileName),
			FileSystem::getInstance()->getFileName(rcOutFileName),
			rc
		);

		Console::println(rc);
	} catch (Exception& exception) {
		Console::println(string() + "An error occurred: " + exception.what());
	}

	//
	Application::exit(Application::EXITCODE_SUCCESS);
}
