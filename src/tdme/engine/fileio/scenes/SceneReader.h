#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/model/Node.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/engine/fileio/fwd-tdme.h>
#include <tdme/engine/fileio/scenes/fwd-tdme.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <rapidjson/document.h>

using std::string;
using std::vector;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Node;
using tdme::math::Matrix4x4;
using tdme::engine::fileio::ProgressCallback;
using tdme::engine::scene::Scene;
using tdme::os::filesystem::FileSystemException;

using rapidjson::Value;

/**
 * Scene reader
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::fileio::scenes::SceneReader final
{

public:
	/**
	 * Reads a scene
	 * @param pathName path name
	 * @param fileName file name
	 * @param scene scene
	 * @param progressCallback progress callback
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static void read(const string& pathName, const string& fileName, Scene& scene, ProgressCallback* progressCallback = nullptr);

	/**
	 * Reads a scene
	 * @param pathName path name
	 * @param fileName file name
	 * @param scene scene
	 * @param objectIdPrefix object id prefix
	 * @param progressCallback progress callback
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static void read(const string& pathName, const string& fileName, Scene& scene, const string& objectIdPrefix, ProgressCallback* progressCallback = nullptr);

	/**
	 * Reads a scene
	 * @param pathName path name
	 * @param fileName file name
	 * @param scene scene
	 * @param progressCallback progress callback
	 * @throws tdme::os::filesystem::FileSystemException
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static void readFromModel(const string& pathName, const string& fileName, Scene& scene, ProgressCallback* progressCallback = nullptr);

private:
	struct PrototypeMeshNode {
		string id;
		string name;
		Matrix4x4 transformationsMatrix;
		Node* node;
	};

	/**
	 * Determine mesh nodes in node hierarchy
	 * @param level level
	 * @param node node
	 * @param parentName parent node
	 * @param parentTransformationsMatrix parent transformations matrix
	 * @param meshNodes mesh nodes
	 */
	static void determineMeshNodes(Scene& level, Node* node, const string& parentName, const Matrix4x4& parentTransformationsMatrix, vector<PrototypeMeshNode>& meshNodes);
};
