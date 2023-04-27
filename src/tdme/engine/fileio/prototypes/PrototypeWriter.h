#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/prototypes/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>

#include <ext/rapidjson/document.h>

using std::string;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeLODLevel;
using tdme::os::filesystem::FileSystemException;

using rapidjson::Document;
using rapidjson::Value;

/**
 * Prototype writer
 * @author Andreas Drewke
 */
class tdme::engine::fileio::prototypes::PrototypeWriter final
{
private:

	/**
	 * Writes LOD level to JSON
	 * @param jDocument JSON document
	 * @param jLodLevelRoot JSON LOD level root value
	 * @param lodLevel lod level
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @return json root
	 */
	static void writeLODLevelToJSON(Document& jDocument, Value& jLodLevelRoot, PrototypeLODLevel* lodLevel, bool useBC7TextureCompression);

public:

	/**
	 * Writes a prototype to file
	 * @param pathName path name
	 * @param fileName file name
	 * @param prototype prototype
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static void write(const string& pathName, const string& fileName, Prototype* prototype, bool useBC7TextureCompression = true);

	/**
	 * Writes a prototype to JSON
	 * @param document JSON document
	 * @param jPrototypeRoot JSON value to store data in
	 * @param prototype prototype
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static void write(Document& jDocument, Value& jPrototypeRoot, Prototype* prototype, bool useBC7TextureCompression = true);

};
