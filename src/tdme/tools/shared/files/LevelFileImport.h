#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/model/Group.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/tools/shared/files/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <ext/jsonbox/JsonException.h>

using std::string;
using std::vector;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Group;
using tdme::math::Matrix4x4;
using tdme::tools::shared::files::ProgressCallback;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::os::filesystem::FileSystemException;
using tdme::ext::jsonbox::JsonException;

/** 
 * TDME Level Editor File Export
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::files::LevelFileImport final
{

public:

	/** 
	 * Imports a level from a TDME level file to Level Editor
	 * @param pathName path name
	 * @param fileName file name
	 * @param level level
	 * @param progressCallback progress callback
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 */
	static void doImport(const string& pathName, const string& fileName, LevelEditorLevel* level, ProgressCallback* progressCallback = nullptr) throw (FileSystemException, JsonException, ModelFileIOException);

	/** 
	 * Imports a level from a TDME level file to Level Editor
	 * @param pathName path name
	 * @param fileName file name
	 * @param level level
	 * @param objectIdPrefix object id prefix
	 * @param progressCallback progress callback
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 */
	static void doImport(const string& pathName, const string& fileName, LevelEditorLevel* level, const string& objectIdPrefix, ProgressCallback* progressCallback = nullptr) throw (FileSystemException, JsonException, ModelFileIOException);

	/**
	 * Imports a level from a model file to Level Editor
	 * @param pathName path name
	 * @param fileName file name
	 * @param level level
	 * @param progressCallback progress callback
	 * @throws file system exception
	 * @throws json exception
	 * @throws model file io exception
	 */
	static void doImportFromModel(const string& pathName, const string& fileName, LevelEditorLevel* level, ProgressCallback* progressCallback = nullptr) throw (FileSystemException, JsonException, ModelFileIOException);

private:
	struct LevelEditorEntityMeshGroup {
		string id;
		string name;
		Matrix4x4 transformationsMatrix;
		Group* group;
	};

	/**
	 * Determine mesh groups in group hierarchy
	 * @param level level
	 * @param group group
	 * @param parentName parent node
	 * @param parentTransformationsMatrix parent transformations matrix
	 * @param meshGroups mesh groups
	 */
	static void determineMeshGroups(LevelEditorLevel* level, Group* group, const string& parentName, const Matrix4x4& parentTransformationsMatrix, vector<LevelEditorEntityMeshGroup>& meshGroups);
};
