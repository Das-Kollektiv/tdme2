#include <memory>
#include <string>

using std::string;
using std::unique_ptr;

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using tdme::application::Application;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::models::TMWriter;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Model;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;

int main(int argc, char** argv)
{
	Console::println(string("copyanimationsetups ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();
	if (argc != 3) {
		Console::println("Usage: copyanimationsetups sourcefile targetfile.tm");
		Application::exit(1);
	}
	string sourceFileName = string(argv[1]);
	string targetFileName = string(argv[2]);
	//
	try {
		Console::println("Loading source model: " + sourceFileName);
		auto srcModel = unique_ptr<Model>(
			ModelReader::read(
				FileSystem::getInstance()->getPathName(sourceFileName),
				FileSystem::getInstance()->getFileName(sourceFileName)
			)
		);
		Console::println("Loading target model: " + targetFileName);
		auto targetModel = unique_ptr<Model>(
			ModelReader::read(
				FileSystem::getInstance()->getPathName(targetFileName),
				FileSystem::getInstance()->getFileName(targetFileName)
			)
		);
		Console::println("Clearing target animation setups");
		targetModel->clearAnimationSetups();
		for (const auto& [srcAnimationSetupId, srcAnimationSetup]: srcModel->getAnimationSetups()) {
			Console::println("Adding target animation setup: " + srcAnimationSetup->getId());
			if (srcAnimationSetup->getOverlayFromNodeId().length() == 0) {
				targetModel->addAnimationSetup(
					srcAnimationSetup->getId(),
					srcAnimationSetup->getStartFrame(),
					srcAnimationSetup->getEndFrame(),
					srcAnimationSetup->isLoop(),
					srcAnimationSetup->getSpeed()
				);
			} else {
				targetModel->addOverlayAnimationSetup(
					srcAnimationSetup->getId(),
					srcAnimationSetup->getOverlayFromNodeId(),
					srcAnimationSetup->getStartFrame(),
					srcAnimationSetup->getEndFrame(),
					srcAnimationSetup->isLoop(),
					srcAnimationSetup->getSpeed()
				);
			}
		}
		Console::println("Saving target model: " + targetFileName);
		TMWriter::write(
			targetModel.get(),
			FileSystem::getInstance()->getPathName(targetFileName),
			FileSystem::getInstance()->getFileName(targetFileName)
		);
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}

	//
	Console::shutdown();
	return 0;
}
