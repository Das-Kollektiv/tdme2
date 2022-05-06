#include <cstdlib>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using tdme::application::Application;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::models::TMWriter;
using tdme::engine::Engine;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;

namespace tdme {
namespace tools {
namespace cli {

/**
 * Convert to tm application
 * @author andreas.drewke
 */
class ConvertToTMApplication final
	: public virtual Application
{
private:
	vector<string> modelFileNames;

public:
	/**
	 * Public constructor
	 * @param modelFileNames model file names
	 */
	ConvertToTMApplication(const vector<string>& modelFileNames):
		modelFileNames(modelFileNames) {
	}

	/**
	 * Public denstructor
	 */
	~ConvertToTMApplication() {
	}

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	inline static void main(int argc, char** argv) {
		vector<string> modelFileNames;
		for (auto i = 1; i < argc; i++) modelFileNames.push_back(argv[i]);
		auto convertToTMApplication = new ConvertToTMApplication(modelFileNames);
		convertToTMApplication->run(argc, argv, "Convert to tm Application", nullptr, Application::WINDOW_HINT_INVISIBLE);
	}

	// overriden methods
	void display() override {
		try {
			for (auto inputFileName: modelFileNames) {
				auto outputFileName = StringTools::substring(inputFileName, 0, inputFileName.rfind('.')) + ".tm";
				try {
					Console::println("Loading model: " + inputFileName);
					auto model = ModelReader::read(
						FileSystem::getInstance()->getPathName(inputFileName),
						FileSystem::getInstance()->getFileName(inputFileName)
					);
					Console::println("Exporting model: " + outputFileName);
					TMWriter::write(
						model,
						FileSystem::getInstance()->getPathName(outputFileName),
						FileSystem::getInstance()->getFileName(outputFileName)
					);
				} catch (Exception& exception) {
					Console::println("An error occurred: " + string(exception.what()));
				}
			}
		} catch (Exception& exception) {
			Console::println("An error occurred: " + string(exception.what()));
		}
		Application::exit(0);
	}

	void dispose() override {
		Engine::getInstance()->dispose();
	}

	void initialize() override {
		Engine::getInstance()->initialize();
	}

	void reshape(int32_t width, int32_t height) override {
		Engine::getInstance()->reshape(width, height);
	}
};

};
};
};

int main(int argc, char** argv)
{
	Console::println(string("converttotm ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();
	if (argc < 2) {
		Console::println("Usage: converttotm inputfile1 [inputfileN]");
		Application::exit(1);
	}
	tdme::tools::cli::ConvertToTMApplication::main(argc, argv);
}
