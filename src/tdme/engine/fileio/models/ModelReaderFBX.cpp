#include <tdme/engine/fileio/models/ModelReader.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/DAEReader.h>
#include <tdme/engine/fileio/models/FBXReader.h>
#include <tdme/engine/fileio/models/GLTFReader.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/fileio/models/TMReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::vector;

using tdme::engine::fileio::models::DAEReader;
using tdme::engine::fileio::models::FBXReader;
using tdme::engine::fileio::models::GLTFReader;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::models::TMReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::model::Model;
using tdme::engine::prototype::Prototype;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;

vector<string> ModelReader::extensions = {{"dae", "dxf", "fbx", "glb", "gltf", "obj", "tm", "tmodel"}};

const vector<string>& ModelReader::getModelExtensions() {
	return extensions;
}

Model* ModelReader::read(const string& pathName, const string& fileName)
{
	try {
		if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".dae") == true) {
			return DAEReader::read(pathName, fileName);
		} else
		if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".dae") == true ||
			StringTools::endsWith(StringTools::toLowerCase(fileName), ".dxf") == true ||
			StringTools::endsWith(StringTools::toLowerCase(fileName), ".fbx") == true ||
			StringTools::endsWith(StringTools::toLowerCase(fileName), ".obj") == true) {
			return FBXReader::read(pathName, fileName);
		} else
		if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".glb") == true) {
			return GLTFReader::read(pathName, fileName);
		} else
		if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".gltf") == true) {
			return GLTFReader::read(pathName, fileName);
		} else
		if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".tm") == true) {
			return TMReader::read(pathName, fileName);
		} else
		if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".tmodel") == true) {
			auto prototype = PrototypeReader::read(pathName, fileName);
			if (prototype != nullptr && prototype->getModel() != nullptr) {
				auto model = prototype->unsetModel();
				delete prototype;
				return model;
			} else {
				delete prototype;
				return nullptr;
			}
		} else {
			throw ModelFileIOException(string("Unsupported mode file: ") + pathName + "/" + fileName);
		}
	} catch (Exception& exception) {
		Console::println("ModelReader::read(): Could not load model: " + pathName + "/" + fileName + ": " + exception.what());
		throw;
	}
	return nullptr;
}

