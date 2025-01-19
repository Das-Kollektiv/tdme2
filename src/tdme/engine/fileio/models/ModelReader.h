#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/audio/decoder/fwd-tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemException.h>

using std::string;
using std::vector;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Model;
using tdme::os::filesystem::FileSystemException;

/**
 * Model reader class
 * @author Andreas Drewke
 */
class tdme::engine::fileio::models::ModelReader final
{
private:
	STATIC_DLL_IMPEXT static vector<string> extensions;
public:
	/**
	 * Get supported model extensions
	 */
	static const vector<string>& getModelExtensions();

	/**
	 * Reads a model
	 * @param pathName path name
	 * @param fileName file name
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @throws tdme::os::filesystem::FileSystemException
	 * @returns texture data instance or null
	 */
	static Model* read(const string& pathName, const string& fileName, bool useBC7TextureCompression = true);
};
