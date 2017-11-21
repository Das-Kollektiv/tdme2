#pragma once

#include <fbxsdk.h>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::model::Model_UpVector;
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
	 * @param path name
	 * @param file name
	 * @throws model file IO exception
	 * @throws file system exception
	 * @return model instance
	 */
	static Model* read(const string& pathName, const string& fileName) throw (ModelFileIOException, FileSystemException);

private:

	/**
	 * Get scene up vector
	 * @param fbx scene
	 */
	static Model_UpVector* getSceneUpVector(FbxScene* fbxScene) throw (ModelFileIOException);

	/**
	 * Get scene rotation order
	 * @param fbx scene
	 */
	static RotationOrder* getSceneRotationOrder(FbxScene* fbxScene) throw (ModelFileIOException);

	/**
	 * Set up model import rotation maxtrix
	 * @param model
	 */
	static void setupModelImportRotationMatrix(Model* model);

	/**
	 * Set up model import scale maxtrix
	 * @param fbx scene
	 * @param model
	 */
	static void setupModelScaleRotationMatrix(FbxScene* fbxScene, Model* model);

	/**
	 * Process FBX scene
	 * @param FBX scene
	 * @param model
	 */
	static void processScene(FbxScene* fbxScene, Model* model);

	/**
	 * Process FBX node
	 * @param FBX scene
	 * @param model
	 * @param parent group
	 */
	static void processNode(FbxNode* fbxNode, Model* model, Group* parentGroup);

	/**
	 * Process FBX mesh node
	 * @param FBX node
	 * @param model
	 * @param parent group
	 */
	static Group* processMeshNode(FbxNode* fbxNode, Model* model, Group* parentGroup);

	/**
	 * Process animation
	 * @param FBX node
	 * @param FBX animation layer
	 * @param FBX animation index
	 * @param FBX start frame
	 * @param FBX end frame
	 * @param model
	 */
	static void processAnimation(FbxNode* fbxNode, FbxAnimLayer* fbxAnimLayer, int fbxAnimIndex, const FbxTime& fbxStartFrame, const FbxTime& fbxEndFrame, Model* model);
};
