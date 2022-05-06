#include <cstdlib>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;
using std::to_string;

using tdme::application::Application;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Model;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;

int main(int argc, char** argv)
{
	Console::println(string("dumpmodel ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();
	if (argc != 2) {
		Console::println("Usage: dumpmodel sourcefile");
		Application::exit(1);
	}
	string fileName = string(argv[1]);
	try {
		Console::println("Loading source model: " + fileName);
		auto model = ModelReader::read(
			FileSystem::getInstance()->getPathName(fileName),
			FileSystem::getInstance()->getFileName(fileName)
		);
		Console::println("Animation setups:");
		for (auto& animationSetupIt: model->getAnimationSetups()) {
			auto srcAnimationSetup = animationSetupIt.second;
			if (srcAnimationSetup->getOverlayFromNodeId().length() == 0) {
				Console::println(
					"Base animation: id = '" + srcAnimationSetup->getId() + "', " +
					"start frame: " + to_string(srcAnimationSetup->getStartFrame()) + ", " +
					"end frame: " + to_string(srcAnimationSetup->getEndFrame()) + ", " +
					"loop: " + to_string(srcAnimationSetup->isLoop()) + ", " +
					"speed: " + to_string(srcAnimationSetup->getSpeed())
				);
			} else {
				Console::println(
					"Overlay animation: id = '" + srcAnimationSetup->getId() + "', " +
					"overlay node: '" + srcAnimationSetup->getOverlayFromNodeId()  + "', " +
					"start frame: " + to_string(srcAnimationSetup->getStartFrame()) + ", " +
					"end frame: " + to_string(srcAnimationSetup->getEndFrame()) + ", " +
					"loop: " + to_string(srcAnimationSetup->isLoop()) + ", " +
					"speed: " + to_string(srcAnimationSetup->getSpeed())
				);
			}
		}
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}
}
