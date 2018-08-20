#pragma once

#define FBXSDK_SHARED

#include <fbxsdk.h>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::model::UpVector;
using tdme::engine::model::RotationOrder;
using tdme::os::filesystem::FileSystemException;

/** 
 * FBX reader
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::fileio::models::FBXReader final
{
public:

	/** 
	 * Reads FBX file
	 * @param pathName path name
	 * @param fileName file name
	 * @throws model file IO exception
	 * @throws file system exception
	 * @return model instance
	 */
	static Model* read(const string& pathName, const string& fileName) throw (ModelFileIOException, FileSystemException);

private:

	/**
	 * Get scene up vector
	 * @param fbxScene fbx scene
	 */
	static UpVector* getSceneUpVector(FbxScene* fbxScene) throw (ModelFileIOException);

	/**
	 * Get scene rotation order
	 * @param fbxScene fbx scene
	 */
	static RotationOrder* getSceneRotationOrder(FbxScene* fbxScene) throw (ModelFileIOException);

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
	 */
	static void processScene(FbxScene* fbxScene, Model* model, const string& pathName);

	/**
	 * Process FBX node
	 * @param fbxNode FBX scene
	 * @param model model
	 * @param parentGroup parent group
	 * @param pathName path name
	 */
	static void processNode(FbxNode* fbxNode, Model* model, Group* parentGroup, const string& pathName);

	/**
	 * Process FBX mesh node
	 * @param fbxNode FBX node
	 * @param model model
	 * @param parentGroup parent group
	 * @param pathName path name
	 */
	static Group* processMeshNode(FbxNode* fbxNode, Model* model, Group* parentGroup, const string& pathName);

	/**
	 * Process FBX skeleton node
	 * @param fbxNode FBX node
	 * @param model model
	 * @param parentGroup parent group
	 * @param pathName path name
	 */
	static Group* processSkeletonNode(FbxNode* fbxNode, Model* model, Group* parentGroup, const string& pathName);

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
