#pragma once

#define FBXSDK_SHARED
#include <fbxsdk.h>
#undef isnan

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>

using std::vector;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::UpVector;
using tdme::os::filesystem::FileSystemException;

/**
 * FBX model reader
 * @author Andreas Drewke
 */
class tdme::engine::fileio::models::FBXReader final
{
public:

	/**
	 * Reads FBX file
	 * @param pathName path name
	 * @param fileName file name
	 * @param useBC7TextureCompression use BC7 texture compression
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 * @throws tdme::os::filesystem::FileSystemException
	 * @return model instance
	 */
	static Model* read(const string& pathName, const string& fileName, bool useBC7TextureCompression = true);

private:
	STATIC_DLL_IMPEXT static const Color4 BLENDER_AMBIENT_NONE;
	static constexpr float BLENDER_AMBIENT_FROM_DIFFUSE_SCALE { 0.7f };
	static constexpr float BLENDER_DIFFUSE_SCALE { 0.8f };

	/**
	 * Get scene up vector
	 * @param fbxScene fbx scene
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static UpVector* getSceneUpVector(FbxScene* fbxScene);

	/**
	 * Get scene rotation order
	 * @param fbxScene fbx scene
	 * @throws tdme::engine::fileio::models::ModelFileIOException
	 */
	static RotationOrder* getSceneRotationOrder(FbxScene* fbxScene);

	/**
	 * Set up model import rotation maxtrix
	 * @param model model
	 */
	static void setupModelImportRotationMatrix(Model* model);

	/**
	 * Set up model import scale maxtrix
	 * @param fbxScene fbx scene
	 * @param model model
	 */
	static void setupModelScaleRotationMatrix(FbxScene* fbxScene, Model* model);

	/**
	 * Process FBX scene
	 * @param fbxScene FBX scene
	 * @param model model
	 * @param pathName path name
	 * @param possibleArmatureNodeIds possible armature node ids
	 * @param useBC7TextureCompression use BC7 texture compression
	 */
	static void processScene(FbxScene* fbxScene, Model* model, const string& pathName, vector<string>& possibleArmatureNodeIds, bool useBC7TextureCompression);

	/**
	 * Process FBX node
	 * @param fbxNode FBX scene
	 * @param model model
	 * @param parentNode parent node
	 * @param pathName path name
	 * @param possibleArmatureNodeIds possible armature node ids
	 * @param useBC7TextureCompression use BC7 texture compression
	 */
	static void processNode(FbxNode* fbxNode, Model* model, Node* parentNode, const string& pathName, vector<string>& possibleArmatureNodeIds, bool useBC7TextureCompression);

	/**
	 * Process FBX mesh node
	 * @param fbxNode FBX node
	 * @param model model
	 * @param parentNode parent node
	 * @param pathName path name
	 * @param useBC7TextureCompression use BC7 texture compression
	 */
	static Node* processMeshNode(FbxNode* fbxNode, Model* model, Node* parentNode, const string& pathName, bool useBC7TextureCompression);

	/**
	 * Process FBX skeleton node
	 * @param fbxNode FBX node
	 * @param model model
	 * @param parentNode parent node
	 * @param pathName path name
	 */
	static Node* processSkeletonNode(FbxNode* fbxNode, Model* model, Node* parentNode, const string& pathName);

	/**
	 * Process animation
	 * @param fbxNode FBX node
	 * @param fbxStartFrame FBX start frame
	 * @param fbxEndFrame FBX end frame
	 * @param model model
	 * @param frameOffset frame offset
	 */
	static void processAnimation(FbxNode* fbxNode, const FbxTime& fbxStartFrame, const FbxTime& fbxEndFrame, Model* model, int frameOffset);
};
