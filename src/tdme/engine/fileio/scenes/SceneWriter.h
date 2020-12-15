#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/scenes/fwd-tdme.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>

#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>

using std::string;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::os::filesystem::FileSystemException;
using tdme::engine::scene::Scene;

/**
 * Scene writer
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::fileio::scenes::SceneWriter final
{

public:
	/**
	 * Writes a scene
	 * @param pathName path name
	 * @param fileName file name
	 * @param scene scene
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static void write(const string& pathName, const string& fileName, Scene& scene);

};
