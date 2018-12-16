#pragma once

#include <map>
#include <vector>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Model.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>

#include <ext/tinyxml/tinyxml.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Color4;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::UpVector;
using tdme::engine::model::Model;
using tdme::os::filesystem::FileSystemException;
using tdme::tools::shared::model::LevelEditorLevel;

using tdme::ext::tinyxml::TiXmlElement;

/** 
 * Collada DAE reader
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::fileio::models::DAEReader final
{
	friend class DAEReader_determineDisplacementFilename_1;

private:
	static const Color4 BLENDER_AMBIENT_NONE;
	static constexpr float BLENDER_AMBIENT_FROM_DIFFUSE_SCALE { 0.7f };
	static constexpr float BLENDER_DIFFUSE_SCALE { 0.8f };

public:

	/** 
	 * Reads Collada DAE file
	 * @param pathName path name
	 * @param fileName file name
	 * @throws model file IO exception
	 * @throws file system exception
	 * @return model instance
	 */
	static Model* read(const string& pathName, const string& fileName) throw (ModelFileIOException, FileSystemException);

private:

	/** 
	 * Get authoring tool
	 * @param xmlRoot xml root
	 * @return authoring tool
	 */
	static Model::AuthoringTool getAuthoringTool(TiXmlElement* xmlRoot);

	/** 
	 * Get Up vector
	 * @param xmlRoot xml root
	 * @return up vector
	 * @throws ModelFileIOException
	 */
	static UpVector* getUpVector(TiXmlElement* xmlRoot) throw (ModelFileIOException);

	/** 
	 * Set up model import rotation matrix
	 * @param xmlRoot xml root
	 * @param model model
	 */
	static void setupModelImportRotationMatrix(TiXmlElement* xmlRoot, Model* model);

	/** 
	 * Set up model import scale matrix
	 * @param xmlRoot xml root
	 * @param model model
	 */
	static void setupModelImportScaleMatrix(TiXmlElement* xmlRoot, Model* model);

	/** 
	 * Read a DAE visual scene node
	 * @param pathName path name
	 * @param model model
	 * @param parentGroup parent group
	 * @param xmlRoot xml node
	 * @param xmlNode xml root
	 * @param fps frames per second
	 * @return group
	 */
	static Group* readVisualSceneNode(const string& pathName, Model* model, Group* parentGroup, TiXmlElement* xmlRoot, TiXmlElement* xmlNode, float fps);

	/** 
	 * Reads a DAE visual scene group node
	 * @param pathName path name
	 * @param model model
	 * @param parentGroup parent group
	 * @param xmlRoot xml node
	 * @param xmlNode xml root
	 * @param fps frames per seconds
	 * @throws model file IO exception
	 * @return group
	 */
	static Group* readNode(const string& pathName, Model* model, Group* parentGroup, TiXmlElement* xmlRoot, TiXmlElement* xmlNode, float fps) throw (ModelFileIOException);

	/** 
	 * Reads a instance controller
	 * @param pathName path name
	 * @param model model
	 * @param parentGroup parent group
	 * @param xmlRoot xml root
	 * @param xmlNode xml node
	 * @throws model file IO exception
	 * @return Group
	 * @throws Exception
	 */
	static Group* readVisualSceneInstanceController(const string& pathName, Model* model, Group* parentGroup, TiXmlElement* xmlRoot, TiXmlElement* xmlNode) throw (ModelFileIOException);

	/** 
	 * Reads a geometry
	 * @param pathName path name
	 * @param model model
	 * @param group group
	 * @param xmlRoot xml root
	 * @param xmlNodeId xml node id
	 * @param materialSymbols material symbols
	 * @throws model file IO exception
	 */
	static void readGeometry(const string& pathName, Model* model, Group* group, TiXmlElement* xmlRoot, const string& xmlNodeId, const map<string, string>* materialSymbols) throw (ModelFileIOException); // TODO: std container: maybe use call by reference

	/** 
	 * Reads a material
	 * @param pathName path name
	 * @param model model
	 * @param xmlRoot xml root
	 * @param xmlNodeId xml node id
	 * @return material
	 */
	static Material* readMaterial(const string& pathName, Model* model, TiXmlElement* xmlRoot, const string& xmlNodeId);

	/** 
	 * Determine displacement filename 
	 * @param path path
	 * @param mapType map type
	 * @param fileName file name
	 * @return displacement file name or null
	 */
	static const string determineDisplacementFilename(const string& path, const string& mapType, const string& fileName);

	/** 
	 * Make file name relative
	 * @param fileName file name
	 * @return file name
	 */
	static const string makeFileNameRelative(const string& fileName);

	/** 
	 * Get texture file name by id
	 * @param xmlRoot xml root
	 * @param xmlTextureId xml texture id
	 * @return xml texture file name
	 */
	static const string getTextureFileNameById(TiXmlElement* xmlRoot, const string& xmlTextureId);

public:

	/** 
	 * Returns immediate children tags by tag name
	 * @param parent parent
	 * @param name name
	 * @return matching elements
	 */
	static const vector<TiXmlElement*> getChildrenByTagName(TiXmlElement* parent, const char* name);

	/**
	 * Returns immediate children tags
	 * @param parent parent
	 * @return elements
	 */
	static const vector<TiXmlElement*> getChildren(TiXmlElement* parent);
};
