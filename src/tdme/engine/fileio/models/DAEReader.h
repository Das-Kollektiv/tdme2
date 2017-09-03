// Generated from /tdme/src/tdme/engine/fileio/models/DAEReader.java

#pragma once

#include <map>
#include <vector>
#include <string>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/os/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/_FileSystemException.h>

#include <ext/tinyxml/tinyxml.h>

using std::map;
using std::wstring;
using std::vector;

using java::lang::String;
using tdme::engine::fileio::models::DAEReader_AuthoringTool;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Color4;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::Model_UpVector;
using tdme::engine::model::Model;
using tdme::os::_FileSystemException;
using tdme::tools::shared::model::LevelEditorLevel;

using tdme::ext::tinyxml::TiXmlElement;

/** 
 * Collada DAE reader
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::fileio::models::DAEReader final
{
	friend class DAEReader_AuthoringTool;
	friend class DAEReader_determineDisplacementFilename_1;

private:
	static Color4* BLENDER_AMBIENT_NONE;
	static float BLENDER_AMBIENT_FROM_DIFFUSE_SCALE;
	static float BLENDER_DIFFUSE_SCALE;

public:

	/** 
	 * Reads Collada DAE file
	 * @param path name
	 * @param file name
	 * @throws model file IO exception
	 * @throws file system exception
	 * @return model instance
	 */
	static Model* read(const wstring& pathName, const wstring& fileName) throw (ModelFileIOException, _FileSystemException);

	/** 
	 * Reads Collada DAE file level
	 * @param path name
	 * @param file name
	 * @throws model file IO exception
	 * @throws file system exception
	 * @return model instance
	 */
	static LevelEditorLevel* readLevel(const wstring& pathName, const wstring& fileName) throw (ModelFileIOException, _FileSystemException);

private:

	/** 
	 * Get authoring tool
	 * @param xml root
	 * @return authoring tool
	 */
	static DAEReader_AuthoringTool* getAuthoringTool(TiXmlElement* xmlRoot);

	/** 
	 * Get Up vector
	 * @param xml root
	 * @return up vector
	 * @throws ModelFileIOException
	 */
	static Model_UpVector* getUpVector(TiXmlElement* xmlRoot) throw (ModelFileIOException);

	/** 
	 * Set up model import rotation matrix
	 * @param xml root
	 * @param model
	 */
	static void setupModelImportRotationMatrix(TiXmlElement* xmlRoot, Model* model);

	/** 
	 * Set up model import scale matrix
	 * @param xml root
	 * @param model
	 */
	static void setupModelImportScaleMatrix(TiXmlElement* xmlRoot, Model* model);

	/** 
	 * Read a DAE visual scene node
	 * @param authoring tool
	 * @param path name
	 * @param model
	 * @param parent group
	 * @param xml node
	 * @param xml root
	 * @param frames per second
	 * @return group
	 */
	static Group* readVisualSceneNode(DAEReader_AuthoringTool* authoringTool, const wstring& pathName, Model* model, Group* parentGroup, TiXmlElement* xmlRoot, TiXmlElement* xmlNode, float fps);

	/** 
	 * Reads a DAE visual scene group node
	 * @param authoring tool
	 * @param path name
	 * @param model
	 * @param parent group
	 * @param xml node
	 * @param xml root
	 * @param frames per seconds
	 * @throws model file IO exception
	 * @return group
	 */
	static Group* readNode(DAEReader_AuthoringTool* authoringTool, const wstring& pathName, Model* model, Group* parentGroup, TiXmlElement* xmlRoot, TiXmlElement* xmlNode, float fps) throw (ModelFileIOException);

	/** 
	 * Reads a instance controller
	 * @param authoring tool
	 * @param path name
	 * @param model
	 * @param parent group
	 * @param xml root
	 * @param xml node
	 * @throws model file IO exception
	 * @return Group
	 * @throws Exception
	 */
	static Group* readVisualSceneInstanceController(DAEReader_AuthoringTool* authoringTool, const wstring& pathName, Model* model, Group* parentGroup, TiXmlElement* xmlRoot, TiXmlElement* xmlNode) throw (ModelFileIOException);

	/** 
	 * Reads a geometry
	 * @param authoring tools
	 * @param path name
	 * @param model
	 * @param group
	 * @param xml root
	 * @param xml node id
	 * @param material symbols
	 * @throws model file IO exception
	 */
	static void readGeometry(DAEReader_AuthoringTool* authoringTool, const wstring& pathName, Model* model, Group* group, TiXmlElement* xmlRoot, const wstring& xmlNodeId, const map<wstring, wstring>* materialSymbols) throw (ModelFileIOException);

	/** 
	 * Reads a material
	 * @param authoring tool
	 * @param path name
	 * @param model
	 * @param xml root
	 * @param xml node id
	 * @return material
	 */
	static Material* readMaterial(DAEReader_AuthoringTool* authoringTool, const wstring& pathName, Model* model, TiXmlElement* xmlRoot, const wstring& xmlNodeId);

	/** 
	 * Determine displacement filename 
	 * @param path
	 * @param map type
	 * @param file name
	 * @return displacement file name or null
	 */
	static const wstring determineDisplacementFilename(const wstring& path, const wstring& mapType, const wstring& fileName);

	/** 
	 * Make file name relative
	 * @param file name
	 * @return file name
	 */
	static const wstring makeFileNameRelative(const wstring& fileName);

	/** 
	 * Get texture file name by id
	 * @param xml root
	 * @param xml texture id
	 * @return xml texture file name
	 */
	static const wstring getTextureFileNameById(TiXmlElement* xmlRoot, const wstring& xmlTextureId);

public:

	/** 
	 * Returns immediate children tags by tag name
	 * @param parent
	 * @param name
	 * @return matching elements
	 */
	static const vector<TiXmlElement*> getChildrenByTagName(TiXmlElement* parent, const char* name);

	/**
	 * Returns immediate children tags
	 * @param parent
	 * @return elements
	 */
	static const vector<TiXmlElement*> getChildren(TiXmlElement* parent);
};
