#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/StringTools.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using tdme::application::Application;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::models::TMWriter;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ModelTools;
using tdme::utilities::StringTools;

int main(int argc, char** argv)
{
	Console::println(string("optimizemodel ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();
	if (argc < 2) {
		Console::println("Usage: optimizemodel file.tm [exclude_materials_with_specific_filename1] [exclude_materials_with_specific_filenameN]");
		Application::exit(1);
	}
	string fileName = string(argv[1]);
	if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".tm") == false) {
		Console::println("optimizemodel only accepts .tm model files");
		Application::exit(1);
	}
	vector<string> excludeDiffuseTextureFileNamePatterns;
	for (auto i = 2; i < argc; i++) excludeDiffuseTextureFileNamePatterns.push_back(argv[i]);
	try {
		Console::println("Loading model: " + fileName);
		auto model = unique_ptr<Model>(
			ModelReader::read(
				FileSystem::getInstance()->getPathName(fileName),
				FileSystem::getInstance()->getFileName(fileName)
			)
		);
		if (ModelTools::isOptimizedModel(model.get()) == true) {
			Console::println("Already optimized. Skipping.");
		} else {
			Console::println("Optimizing model: " + fileName);
			auto originalModel = model.get();
			auto optimizedModel = unique_ptr<Model>(
				ModelTools::optimizeModel(
					model.release(),
					FileSystem::getInstance()->getPathName(fileName),
					excludeDiffuseTextureFileNamePatterns
				)
			);
			if (originalModel == optimizedModel.get()) {
				Console::println("No optimization was required. Skipping.");
			} else {
				Console::println("Exporting model: " + fileName);
				TMWriter::write(
					optimizedModel.get(),
					FileSystem::getInstance()->getPathName(fileName),
					FileSystem::getInstance()->getFileName(fileName)
				);
			}
		}
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}

	//
	Console::shutdown();
	return 0;
}
