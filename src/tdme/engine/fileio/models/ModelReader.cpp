#include <tdme/engine/fileio/models/ModelReader.h>

#include <string>
#include <vector>

#include <tdme/engine/fileio/models/DAEReader.h>
#include <tdme/engine/fileio/models/GLTFReader.h>
#include <tdme/engine/fileio/models/TMReader.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/model/Model.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::vector;

using tdme::engine::fileio::models::DAEReader;
using tdme::engine::fileio::models::GLTFReader;
using tdme::engine::fileio::models::TMReader;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::Model;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ModelTools;
using tdme::utilities::StringTools;

vector<string> ModelReader::extensions = {"dae", "glb", "tm"};

const vector<string>& ModelReader::getModelExtensions() {
	return extensions;
}

Model* ModelReader::read(const string& pathName, const string& fileName, bool optimizeModel)
{
	try {
		if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".dae") == true) {
			return optimizeModel == true?ModelTools::optimizeModel(DAEReader::read(pathName, fileName)):DAEReader::read(pathName, fileName);
		} else
		if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".glb") == true) {
			return optimizeModel == true?ModelTools::optimizeModel(GLTFReader::read(pathName, fileName)):GLTFReader::read(pathName, fileName);
		} else
		if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".tm") == true) {
			return optimizeModel == true?ModelTools::optimizeModel(TMReader::read(pathName, fileName)):TMReader::read(pathName, fileName);
		} else {
			throw ModelFileIOException(string("Unsupported mode file: ") + pathName + "/" + fileName);
		}
	} catch (Exception& exception) {
		Console::println("ModelLoader::read(): Could not read model: " + pathName + "/" + fileName + ": " + (exception.what()));
		throw;
	}
	return nullptr;
}

