#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeWriter.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/misc/GenerateConvexMeshes.h>
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
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::prototypes::PrototypeWriter;
using tdme::engine::model::Model;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::Engine;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::misc::GenerateConvexMeshes;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ModelTools;
using tdme::utilities::StringTools;

namespace tdme {
namespace tools {
namespace cli {

/**
 * Import tmodel application
 * @author andreas.drewke
 */
class ImportTModelApplication final: public Application
{
private:
	string tModelFileName;
	string modelFileName;
	string bvsModelFileName;
	bool useBC7TextureCompression;

public:
	// forbid class copy
	FORBID_CLASS_COPY(ImportTModelApplication)

	/**
	 * Public constructor
	 */
	ImportTModelApplication(const string& tModelFileName, const string& modelFileName, const string& bvsModelFileName, bool useBC7TextureCompression):
		tModelFileName(tModelFileName),
		modelFileName(modelFileName),
		bvsModelFileName(bvsModelFileName),
		useBC7TextureCompression(useBC7TextureCompression) {
	}

	/**
	 * Public denstructor
	 */
	~ImportTModelApplication() {
	}

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 * @returns exit code
	 */
	inline static int main(int argc, char** argv) {
		auto useBC7TextureCompression = true;
		if (string(argv[1]) == "--no-texture-compression") useBC7TextureCompression = false;
		string tModelFileName = argv[1 + (useBC7TextureCompression == false?1:0)];
		string modelFileName = argv[2 + (useBC7TextureCompression == false?1:0)];
		string bvsModelFileName = argc >= 4 + (useBC7TextureCompression == false?1:0)?argv[3 + (useBC7TextureCompression == false?1:0)]:"";
		auto importTModelApplication = new ImportTModelApplication(tModelFileName, modelFileName, bvsModelFileName, useBC7TextureCompression);
		return importTModelApplication->run(argc, argv, "Import TModel Application", nullptr, Application::WINDOW_HINT_INVISIBLE);
	}

	// overridden methods
	void display() override {
		try {
			unique_ptr<Prototype> prototype;
			// load model
			Console::printLine("Loading model: " + modelFileName);
			auto model = unique_ptr<Model>(
				ModelReader::read(
					FileSystem::getInstance()->getPathName(modelFileName),
					FileSystem::getInstance()->getFileName(modelFileName),
					useBC7TextureCompression
				)
			);
			// load tmm
			if (FileSystem::getInstance()->exists(tModelFileName) == false) {
				Console::printLine("Creating tmodel: " + tModelFileName);
				auto pathName = FileSystem::getInstance()->getPathName(tModelFileName);
				auto fileName = FileSystem::getInstance()->getFileName(tModelFileName);
				auto fileNameWithoutExtension = StringTools::substring(fileName, 0, fileName.rfind('.'));
				prototype = make_unique<Prototype>(
					-1,
					Prototype_Type::MODEL,
					fileNameWithoutExtension,
					fileNameWithoutExtension,
					pathName + "/" + fileName,
					FileSystem::getInstance()->getPathName(modelFileName) + "/" + FileSystem::getInstance()->getFileName(modelFileName),
					string(),
					model.release()
				);
			} else {
				Console::printLine("Loading tmodel: " + tModelFileName);
				prototype = unique_ptr<Prototype>(
					PrototypeReader::read(
						FileSystem::getInstance()->getPathName(tModelFileName),
						FileSystem::getInstance()->getFileName(tModelFileName),
						nullptr,
						useBC7TextureCompression
					)
				);
				prototype->setModel(model.release());
			}
			// remove old bv mesh model files
			GenerateConvexMeshes::removeConvexMeshes(prototype.get());
			// load new convex meshes bv model
			if (bvsModelFileName.empty() == false) {
				Console::printLine("Loading convex mesh bounding volumes model: " + bvsModelFileName);
				vector<vector<uint8_t>> convexMeshTMsData;
				if (GenerateConvexMeshes::generateConvexMeshes(
						prototype.get(),
						GenerateConvexMeshes::MODE_IMPORT,
						nullptr,
						FileSystem::getInstance()->getPathName(bvsModelFileName),
						FileSystem::getInstance()->getFileName(bvsModelFileName),
					convexMeshTMsData) == true) {
					for (const auto& convexMeshTMData: convexMeshTMsData) {
						//
						try {
							auto prototypeBoundingVolume = make_unique<PrototypeBoundingVolume>(prototype.get());
							prototypeBoundingVolume->setupConvexMesh(convexMeshTMData);
							prototype->addBoundingVolume(prototypeBoundingVolume.release());
						} catch (Exception& exception) {
							Console::printLine(string("An error occurred: ") + exception.what());
						}
					}
					//
				}
			}
			Console::printLine("Saving tmodel: " + tModelFileName);
			PrototypeWriter::write(
				FileSystem::getInstance()->getPathName(tModelFileName),
				FileSystem::getInstance()->getFileName(tModelFileName),
				prototype.get(),
				useBC7TextureCompression
			);
		} catch (Exception& exception) {
			Console::printLine("An error occurred: " + string(exception.what()));
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
	Console::printLine(string("importtmodel ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();
	if (argc < 3) {
		Console::printLine("Usage: importtmodel [--no-texture-compression] model.tmodel modelfile.ext [bvs-model.ext]");
		Application::exit(1);
	}
	return tdme::tools::cli::ImportTModelApplication::main(argc, argv);
}
