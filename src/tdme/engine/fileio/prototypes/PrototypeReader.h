#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/prototypes/fwd-tdme.h>
#include <tdme/engine/fileio/scenes/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/os/filesystem/FileSystemException.h>

#include <ext/rapidjson/document.h>

using std::string;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::fileio::prototypes::PrototypeTransformFilter;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::prototype::PrototypeLODLevel;
using tdme::engine::prototype::PrototypeParticleSystem;
using tdme::os::filesystem::FileSystemException;

using rapidjson::Value;

/**
 * Prototype reader
 * @author Andreas Drewke
 */
class tdme::engine::fileio::prototypes::PrototypeReader final
{
	friend class tdme::engine::fileio::scenes::SceneReader;

	STATIC_DLL_IMPEXT static vector<string> extensions;

public:
	/**
	 * Get supported model extensions
	 */
	static const vector<string> getPrototypeExtensions();

	/**
	 * Get supported tmodel extensions
	 */
	static const vector<string> getModelExtensions();

	/**
	 * Read thumbnail from file
	 * @param pathName path name
	 * @param fileName file name
	 * @param pngData PNG data
	 */
	static bool readThumbnail(const string& pathName, const string& fileName, vector<uint8_t>& pngData);

	/**
	 * Reads a prototype from file
	 * @param pathName path name
	 * @param fileName file name
	 * @param transformFilter transform filter or nullptr
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return prototype
	 */
	inline static Prototype* read(const string& pathName, const string& fileName, PrototypeTransformFilter* transformFilter = nullptr, bool useBC7TextureCompression = true) {
		return read(Prototype::ID_NONE, pathName, fileName, transformFilter, useBC7TextureCompression);
	}

	/**
	 * Reads a prototype from file
	 * @param id id or Prototype.ID_NONE
	 * @param pathName path name
	 * @param fileName file name
	 * @param transformFilter transform filter or nullptr
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return prototype
	 */
	static Prototype* read(int id, const string& pathName, const string& fileName, PrototypeTransformFilter* transformFilter = nullptr, bool useBC7TextureCompression = true);

	/**
	 * Get resource path name
	 * @param pathName path name within a TDME2 resource path where parent resource was loaded from
	 * @param fileName file name containing a path and file in a TDME2 resource path
	 * @return model path name
	 */
	static const string getResourcePathName(const string& pathName, const string& fileName);

private:
	/**
	 * Reads a prototype from JSON object
	 * @param id id or Prototype.ID_NONE
	 * @param pathName path name or null
	 * @param jPrototypeRoot JSON entity root
	 * @param transformFilter transform filter or nullptr
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return prototype
	 */
	static Prototype* read(int id, const string& pathName, const Value& jPrototypeRoot, PrototypeTransformFilter* transformFilter = nullptr, bool useBC7TextureCompression = true);

	/**
	 * Parse bounding volume
	 * @param prototype prototype
	 * @param pathName path name
	 * @param jBv JSON bounding volume node
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @return prototype bounding volume
	 */
	static PrototypeBoundingVolume* parseBoundingVolume(Prototype* prototype, const string& pathName, const Value& jBv);

	/**
	 * Parse LOD level
	 * @param pathName path name
	 * @param jLodLevel JSON LOD level
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @return prototype lod level
	 */
	static PrototypeLODLevel* parseLODLevel(const string& pathName, const Value& jLodLevel, bool useBC7TextureCompression);

	/**
	 * Parse LOD level
	 * @param pathName path name
	 * @param jImposterLOD JSON Imposter LOD level
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @return prototype imposter LOD
	 */
	static PrototypeImposterLOD* parseImposterLODLevel(const string& pathName, const Value& jImposterLOD, bool useBC7TextureCompression);

	/**
	 * Parse particle system
	 * @param pathName path name
	 * @param jParticleSystem JSON particle system object
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @return particle system
	 */
	static PrototypeParticleSystem* parseParticleSystem(const string& pathName, const Value& jParticleSystem, bool useBC7TextureCompression);

};
