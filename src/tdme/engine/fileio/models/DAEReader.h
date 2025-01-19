#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>

#include <ext/tinyxml/tinyxml.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::UpVector;
using tdme::engine::Color4;
using tdme::os::filesystem::FileSystemException;

using tinyxml::TiXmlElement;

/**
 * Collada DAE model reader
 * @author Andreas Drewke
 */
class tdme::engine::fileio::models::DAEReader final
{

private:
	STATIC_DLL_IMPEXT static const Color4 BLENDER_AMBIENT_NONE;
	static constexpr float BLENDER_AMBIENT_FROM_DIFFUSE_SCALE { 0.7f };
	static constexpr float BLENDER_DIFFUSE_SCALE { 0.8f };

public:

	/**
	 * Reads Collada DAE file
	 * @param pathName path name
	 * @param fileName file name
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @throws tdme::os::filesystem::FileSystemException
	 * @returns model instance
	 */
	static Model* read(const string& pathName, const string& fileName, bool useBC7TextureCompression = true);

private:

	/**
	 * Get authoring tool
	 * @param xmlRoot xml root
	 * @returns authoring tool
	 */
	static Model::AuthoringTool getAuthoringTool(TiXmlElement* xmlRoot);

	/**
	 * Get Up vector
	 * @param xmlRoot xml root
	 * @returns up vector
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static UpVector* getUpVector(TiXmlElement* xmlRoot);

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
	 * @param parentNode parent node
	 * @param xmlRoot xml node
	 * @param xmlNode xml root
	 * @param fps frames per second
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @returns node
	 */
	static Node* readVisualSceneNode(const string& pathName, Model* model, Node* parentNode, TiXmlElement* xmlRoot, TiXmlElement* xmlNode, float fps, bool useBC7TextureCompression);

	/**
	 * Reads a DAE visual scene node node
	 * @param pathName path name
	 * @param model model
	 * @param parentNode parent node
	 * @param xmlRoot xml node
	 * @param xmlNode xml root
	 * @param fps frames per seconds
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @returns node
	 */
	static Node* readNode(const string& pathName, Model* model, Node* parentNode, TiXmlElement* xmlRoot, TiXmlElement* xmlNode, float fps, bool useBC7TextureCompression);

	/**
	 * Reads a instance controller
	 * @param pathName path name
	 * @param model model
	 * @param parentNode parent node
	 * @param xmlRoot xml root
	 * @param xmlNode xml node
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @returns Node
	 * @throws tdme::utilities::Exception
	 */
	static Node* readVisualSceneInstanceController(const string& pathName, Model* model, Node* parentNode, TiXmlElement* xmlRoot, TiXmlElement* xmlNode, bool useBC7TextureCompression);

	/**
	 * Reads a geometry
	 * @param pathName path name
	 * @param model model
	 * @param node node
	 * @param xmlRoot xml root
	 * @param xmlNodeId xml node id
	 * @param materialSymbols material symbols
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static void readGeometry(const string& pathName, Model* model, Node* node, TiXmlElement* xmlRoot, const string& xmlNodeId, const map<string, string>& materialSymbols, bool useBC7TextureCompression);

	/**
	 * Reads a material
	 * @param pathName path name
	 * @param model model
	 * @param xmlRoot xml root
	 * @param xmlNodeId xml node id
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @returns material
	 */
	static Material* readMaterial(const string& pathName, Model* model, TiXmlElement* xmlRoot, const string& xmlNodeId, bool useBC7TextureCompression);

	/**
	 * Make file name relative
	 * @param fileName file name
	 * @returns file name
	 */
	static const string makeFileNameRelative(const string& fileName);

	/**
	 * Get texture file name by id
	 * @param xmlRoot xml root
	 * @param xmlTextureId xml texture id
	 * @returns xml texture file name
	 */
	static const string getTextureFileNameById(TiXmlElement* xmlRoot, const string& xmlTextureId);

public:

	/**
	 * Returns immediate children tags by tag name
	 * @param parent parent
	 * @param name name
	 * @returns matching elements
	 */
	static const vector<TiXmlElement*> getChildrenByTagName(TiXmlElement* parent, const char* name);

	/**
	 * Returns immediate children tags
	 * @param parent parent
	 * @returns elements
	 */
	static const vector<TiXmlElement*> getChildren(TiXmlElement* parent);
};
