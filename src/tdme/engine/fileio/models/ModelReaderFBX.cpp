#include <tdme/engine/fileio/models/ModelReader.h>

#include <string>
#include <vector>

#include <tdme/engine/fileio/models/DAEReader.h>
#include <tdme/engine/fileio/models/FBXReader.h>
#include <tdme/engine/fileio/models/TMReader.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/model/Model.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/StringUtils.h>

using std::string;
using std::vector;

using tdme::engine::fileio::models::DAEReader;
using tdme::engine::fileio::models::FBXReader;
using tdme::engine::fileio::models::TMReader;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::Model;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::StringUtils;
using tdme::utils::Console;
using tdme::utils::Exception;

vector<string> ModelReader::extensions = {{"dae", "dxf", "fbx", "obj", "tm"}};

const vector<string>& ModelReader::getModelExtensions() {
	return extensions;
}

Model* ModelReader::read(const string& pathName, const string& fileName)
{
	try {
		if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".dae") == true) {
			return DAEReader::read(pathName, fileName);
		} else
		if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".dae") == true ||
			StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".dxf") == true ||
			StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".fbx") == true ||
			StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".obj") == true) {
			return FBXReader::read(pathName, fileName);
		} else
		if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".tm") == true) {
			return TMReader::read(pathName, fileName);
		} else {
			throw ModelFileIOException(string("Unsupported mode file: ") + pathName + "/" + fileName);
		}
	} catch (Exception& exception) {
		Console::println("ModelReaderFBX::read(): Could not load model: " + pathName + "/" + fileName + ": " + (exception.what()));
		throw;
	}
	return nullptr;
}

