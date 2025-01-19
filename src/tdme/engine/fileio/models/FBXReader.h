#pragma once

#define FBXSDK_SHARED
#include <fbxsdk.h>
#undef isnan

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/os/filesystem/FileSystemException.h>

using std::vector;

using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::Color4;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::UpVector;
using tdme::os::filesystem::FileSystemException;

namespace tdme {
namespace engine {
namespace fileio {
namespace models {

/**
 * FBX reader stream
 * @author Andreas Drewke
 */
class FBXReaderStream: public FbxStream {
public:

	/**
	 * Constructor
	 * @param fbxManager FBX manager
	 * @param data input data array
	 */
	inline FBXReaderStream(FbxManager *fbxManager, const vector<uint8_t> *data): data(data), position(0) {
		readerID = fbxManager->GetIOPluginRegistry()->FindReaderIDByDescription("FBX (*.fbx)");
	}

	/**
	 * Destructor
	 */
	inline ~FBXReaderStream() {
		Close();
	}

	/**
	 * @returns state
	 */
	virtual EState GetState() {
		return opened?eOpen:eClosed;
	}

	/**
	 * Open stream
	 */
	virtual bool Open(void*) {
		position = 0LL;
		opened = true;
		return true;
	}

	/**
	 * Close stream
	 */
	virtual bool Close() {
		position = -1LL;
		opened = false;
		return true;
	}

	/**
	 * Flush
	 */
	virtual bool Flush() {
		return true;
	}

	/**
	 * Write to stream, which is currently not supported
	 * @param data data
	 * @param size size
	 */
	virtual int Write(const void* data, int size) {
		return 0;
	}

	/**
	 * Read from stream
	 * @param data data
	 * @param size size
	 */
	virtual int Read(void* data, int size) const {
		auto i = 0;
		for (; i < size; i++) {
			static_cast<uint8_t*>(data)[i] = (*this->data)[position++];
		}
		return i;
	}

	/**
	 * @returns reader id
	 */
	virtual int GetReaderID() const {
		return readerID;
	}

	/**
	 * @returns writer id
	 */
	virtual int GetWriterID() const {
		return -1;
	}

	/**
	 * Seek
	 * @param offset offset
	 * @param seekPos seek pos
	 */
	void Seek(const FbxInt64& offset, const FbxFile::ESeekPos& seekPos) {
		switch (seekPos) {
			case FbxFile::eBegin:
				position = offset;
				break;
			case FbxFile::eCurrent:
				position += offset;
				break;
			case FbxFile::eEnd:
				position = data->size() - offset;
				break;
		}
	}

	/**
	 * @returns position
	 */
	virtual long GetPosition() const {
		return position;
	}

	/**
	 * Set position
	 * @param position position
	 */
	virtual void SetPosition(long position) {
		this->position = position;
	}

	/**
	 * @returns error or 0 if no error occurred, we dont support errors, lol
	 */
	virtual int GetError() const {
		return 0;
	}

	/**
	 * Clear errors, which we dont support
	 */
	virtual void ClearError() {
	}

private:
	FbxManager *fbxManager { nullptr };
	bool opened { false };
	int readerID { -1 };
	const vector<uint8_t> *data { nullptr };
	mutable int position { -1LL };
};

};
};
};
};

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
	 * @returns model instance
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
